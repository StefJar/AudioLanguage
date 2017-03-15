
// the include for sem_t
#include <semaphore.h>

// inits the AP
int APinit (
			TAP *				pAP,
			TAPNodeID			nodeID,
			const TAPMsgDrv *	pDrvList,
			const int			driverNumber,
			size_t				messagePoolSize,
			int					sysEndian
		)
{
	gAPendianFlag = sysEndian;

	pAP->nodeID = nodeID;
	pAP->pNodeList = NULL;
	pAP->pDrvList = pDrvList;
	pAP->driverNumber = driverNumber;
	pAP->msgSysMMU = AP_MMU_create(messagePoolSize);
	pAP->IP = APInterpreterCreate(pAP);
	pAP->MS = APMScreate (pAP->msgSysMMU,sysEndian);
	pAP->msgNumber = 0;
	pAP->APstate = eAPstate_idle;

	if(
		(!pAP->msgSysMMU)||
		(!pAP->IP)||
		(!pAP->MS)
		) return -1;
	// init drv
	TAPMsgDrv * pDrv = (TAPMsgDrv *)pDrvList;
	int i;
	for (i = 0; i < driverNumber; i++) {
		pDrv->pfkt_open(pAP, pDrv);
		pDrv++;
	}

	// login the ap to the message system
	return TX_login(pAP);
}

// deletes the AP
void APdelete (TAP * pAP)
{
	TX_logout(pAP);
	// close & destroy drv
	TAPMsgDrv * pDrv = (TAPMsgDrv *)pAP->pDrvList;
	int i;
	for (i = 0; i < pAP->driverNumber; i++) {
		pDrv->pfkt_close(pDrv);
		pDrv->pfkt_destroy(pDrv);
		pDrv++;
	}

	APMSdelete (pAP->MS);
	APInterpreterDelete(pAP->IP);
	AP_MMU_delete(pAP->msgSysMMU);
}

// find a node at the list
TAPNode * APfindNode(TAP * pAP, TAPNodeID nodeID) {
	TAPNode * pN = pAP->pNodeList;
	while (pN) {
		if (pN->nodeID == nodeID) return pN;
		pN = pN->pNext;
	};
	return NULL;
}

// adds a new node to the node list
int APaddNode(TAP * pAP, TAPNodeID newNodeID, const TAPMsgDrv * pDrv) {
	if (APfindNode(pAP,newNodeID)) return 1;
	TAPNode * pN = (TAPNode *) malloc(sizeof(TAPNode));
	if (!pN) return -1;
	pN->nodeID = newNodeID;
	pN->pDrv = pDrv;
	pN->pNext = pAP->pNodeList;
	pAP->pNodeList = pN;
	return 0;
}

// removes a node from the node list
void APremoveNode(TAP * pAP, TAPNodeID nodeID){
	TAPNode * pAntN = pAP->pNodeList; // antecessor node
	TAPNode * pActN = pAP->pNodeList; // actual node

	while (pActN) {
		// compare node id's
		if (pActN->nodeID == nodeID) {
			// unchain

			// check if we at the first position at the list
			if (pAP->pNodeList == pAntN) {
				// reset the pointer
				pAP->pNodeList = pActN->pNext;
			} else {
				// set the antecessor
				pAntN->pNext = pActN->pNext;
			}
			// free node
			free(pActN);
			// and abort
			return;
		}
		// the actual element becomes the precessor element
		pAntN = pActN;
		pActN = pActN->pNext;
	}
}

// get a new message number
unsigned int APgetNewMessageNumber (TAP *pAP) {
	pAP->msgNumber++;
	return pAP->msgNumber;
}

// find the driver associated with der nodeID
const TAPMsgDrv * APfindDrvBySenderID (TAP * pAP, TAPNodeID node) {
	TAPNode * pN = pAP->pNodeList;
	while (pN) {
		if (pN->nodeID == node) {
			return pN->pDrv;
		}
		pN = pN->pNext;
	}
	return NULL;
}

// runs the AP
int APrun(TAP *pAP) {
	pAP->APstate = eAPstate_run;
	return 0;
}

typedef struct SAPrealMMUMemory {
	uint32_t *					pData;			// the data
	int							count;			// amount of data elements
	struct SAPrealMMUMemory *	pNext;			// next element
	struct SAPrealMMUMemory *	pPrev;			// previous element
} TAPrealMMUMemory;

//the mmu type
typedef struct SAPrealMMU {
	uint32_t *				memory;				// the memory block
	TAPrealMMUMemory *		pStart;				// first element
	TAPrealMMUMemory *		pEnd;				// second element
	TAPrealMMUMemory *		pUnusedList;		// list with the unused elements
	uint32_t  * 			pUnusedData;		// pointer to the unused memory
	int						elementsAvailable; 	// amount of elements witch are available without using the garbage collector
	int						totalAvailable;		// total amount of free bytes

} TAPrealMMU;

// ========================================
// memory entry functions
// ========================================

// a little macro for unchaining an element
#define DMemoryEntryUnchain(pM) \
	if (pM->pNext) pM->pNext->pPrev = pM->pPrev; \
	if (pM->pPrev) pM->pPrev->pNext = pM->pNext


//creates an memory entry
TAPrealMMUMemory * MemoryEntry_create () {
	TAPrealMMUMemory * pM = NULL;

	pM = (TAPrealMMUMemory *) malloc(sizeof(TAPrealMMUMemory));
	if (!pM) return NULL;
	pM->pData = NULL;
	pM->count = 0;
	pM->pNext = NULL;
	pM->pPrev = NULL;

	return pM;
}

//deletes an memory Entry
void MemoryEntry_delete (
		TAPrealMMUMemory * pM	// the memory to delete
		)
{
	// put the entry out of the chain
	DMemoryEntryUnchain(pM);
	// now we delete it
	free(pM);
}

// ========================================
// mmu helper
// ========================================

//alloc if needed a new memory entry
TAPrealMMUMemory * MMU_helper_createMemoryEntry (
		TAPrealMMU *	pMMU 		// MMU structure to init
		)
{
	// check if we have to alloc a new memory entry
	if (!pMMU->pUnusedList) return MemoryEntry_create();
	// no there is some left at the list
	TAPrealMMUMemory * pM;
	// take the first one
	pM = pMMU->pUnusedList;
	// reset the list
	pMMU->pUnusedList = pM->pNext;
	// now unchain the element (for sure)
	DMemoryEntryUnchain(pM);
	// set the element pointers
	pM->pNext = NULL;
	pM->pPrev = NULL;
	return pM;
}

//the garbage collector
void MMU_helper_garbageCollector (
		TAPrealMMU *	pMMU 		// MMU structure to init
		)
{
	TAPrealMMUMemory * pM = pMMU->pStart;
	uint32_t * pD = pMMU->memory;
	while (pM) {
		// check if we have to move the data
		if (pD != pM->pData) {
			// move the data
			memmove(pD,pM->pData,pM->count*sizeof(uint32_t));
		}
		// reset the destination pointer
		pD += pM->count;
		pM = pM->pNext;
	}
	// compressing memory finished
	// set the mmu vars new
	pMMU->elementsAvailable = pMMU->totalAvailable;
	pMMU->pUnusedData = pD;
}



// create a mmu
TAPMMU AP_MMU_create (size_t elementsNumber) {
	TAPrealMMU * pMMU;

	pMMU = (TAPrealMMU *) malloc (sizeof(TAPrealMMU));
	if (!pMMU) return NULL;


	pMMU->memory = (uint32_t *) malloc (elementsNumber*sizeof(uint32_t));
	pMMU->pUnusedData = pMMU->memory;

	// setup lists
	pMMU->pStart = NULL;
	pMMU->pEnd = NULL;
	pMMU->pUnusedList = NULL;

	pMMU->elementsAvailable =elementsNumber;

	pMMU->totalAvailable = elementsNumber;
	return pMMU;
}

// destroying the mmu
void AP_MMU_delete (TAPMMU mmu) {
	TAPrealMMU * pMMU = (TAPrealMMU *) mmu;

	TAPrealMMUMemory * pM;
	TAPrealMMUMemory * pMnext;

// 1. delete al mmu entry's
	// 1.1 unused entry
	pM = pMMU->pUnusedList;
	while (pM) {
		pMnext = pM->pNext;
		MemoryEntry_delete(pM);
		pM = pMnext;
	}
	pMMU->pUnusedList = NULL;
	// 1.2 used blocks
	pM = pMMU->pStart;
	while (pM) {
		pMnext = pM->pNext;
		MemoryEntry_delete(pM);
		pM = pMnext;
	}
	pMMU->pStart = NULL;
	pMMU->pEnd = NULL;
// 2. delete mmu memory
	free (pMMU->memory);
}

// getting memmory from the mmu
TAPMMUmemmory AP_MMU_get (TAPMMU mmu, size_t elements) {
	TAPrealMMU * pMMU = (TAPrealMMU *) mmu;

	// check if there is enough space
	if (pMMU->totalAvailable < elements) goto error;
	// check if we have to use the garbage collector
	if (pMMU->elementsAvailable < elements) {
		// start garbage collector
		MMU_helper_garbageCollector(pMMU);
	}
	// we have enough memory so let's allocate some

	// get a new entry
	TAPrealMMUMemory * pM;
	pM = MMU_helper_createMemoryEntry(pMMU);
	if (!pM) return NULL;
	// get some memory
	pM->pData = pMMU->pUnusedData;
	pM->count = elements;
	// refresh data
	pMMU->pUnusedData += elements;
	pMMU->totalAvailable -= elements;
	pMMU->elementsAvailable -= elements;
	// insert memory element at the end of the list and update last element
	pM->pPrev = pMMU->pEnd;
	if (pMMU->pEnd) pMMU->pEnd->pNext = pM;
	if (!pMMU->pStart) pMMU->pStart = pM;
	pMMU->pEnd = pM;
	return pM;
error:
	return NULL;
}

// free memmory from the mmu
void AP_MMU_free (TAPMMU mmu, TAPMMUmemmory memory) {
	TAPrealMMU * pMMU = (TAPrealMMU *) mmu;
	TAPrealMMUMemory * pM = (TAPrealMMUMemory *) memory;

	if (!pM) return;
	// set mmu settings
	if (pMMU->pStart == pM) pMMU->pStart = pM->pNext;
	if (pMMU->pEnd == pM) pMMU->pEnd = pM->pPrev;
	// unchain element
	DMemoryEntryUnchain (pM);
	// and put it to the chain of unused
	pM->pNext = pMMU->pUnusedList;
	pM->pPrev = NULL;
	if (pMMU->pUnusedList) {
		pMMU->pUnusedList->pPrev = pM;
	}
	pMMU->pUnusedList = pM;
	// now set the mmu data new
	pMMU->totalAvailable += pM->count;
}

// getting access to the MMU data
void * AP_MMU_getData (TAPMMUmemmory memory) {
	TAPrealMMUMemory * pM = (TAPrealMMUMemory *) memory;
	return pM->pData;
}

// ========================================
// the AP interpreter (thread save)
// ========================================

// the real interpreter
typedef struct SAPrealInterpreter {
	TAP *						pAP;					// pointer to the audio processor
	int							state;					// state of the IP
	int							nextState;				// the next state of the IP
	TAPInterpreterCPU			cpu;					// the IP core
	TAPInterpreterFuncCall *	code;					// the code
	int32_t						instructionCount;		// number of instructions at the code
	TAPInterpreterVariable *	variables;				// the variables
	int32_t						variableCount;			// number of the variables
	pthread_mutex_t				gM;						// a guarding mutex
} TAPrealInterpreter;

// create a new interpreter
TAPInterpreter APInterpreterCreate (void * pAP) {
	TAPrealInterpreter * pIP = NULL;
	pIP = (TAPrealInterpreter *) malloc (sizeof(TAPrealInterpreter));
	if (!pIP) return NULL;

	pIP->pAP = pAP;
	pIP->state = eAPInterpreterState_idle;
	pIP->nextState = eAPInterpreterState_idle;
	pIP->cpu.IP = pIP;
	pIP->cpu.CF = 0;
	pIP->cpu.EF = 0;
	pIP->cpu.pCodeStart = NULL;
	pIP->cpu.pCodeEnd = NULL;
	pIP->cpu.pIP = NULL;

	pIP->code = NULL;
	pIP->instructionCount = 0;

	pIP->variables = NULL;
	pIP->variableCount = 0;

	pthread_mutex_init(&pIP->gM, NULL);

	return pIP;
}

// cleans the interpreter
void APInterpreterClean (TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;

	// clean code
	if (pIP->code) {
		free (pIP->code);
		pIP->code = NULL;
	}
	pIP->instructionCount = 0;

	// clean variables
	TAPInterpreterVariable * pV = pIP->variables;
	int i;
	for (i = 0; i < pIP->variableCount; i++) {
		if (pV->pVI) pV->pVI->pFkt_delete(pV->pData);
		pV++;
	}
	if (pIP->variables) {
		free (pIP->variables);
		pIP->variables = NULL;
	}
	pIP->variableCount = 0;

}

// deletes the interpreter
void APInterpreterDelete (TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	APInterpreterClean(IP);
	free (pIP);
}

// reset the interpreter
void APInterpreterReset (TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	// setup cpu
	pIP->cpu.CF = 0;
	pIP->cpu.EF = 0;
	pIP->cpu.pIP = pIP->code;
	pIP->cpu.pCodeStart = pIP->code;
	pIP->cpu.pCodeEnd = pIP->code + pIP->instructionCount;
}


int APInterpreterStateRun(TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	TAPInterpreterFuncCall * pFC;

	APInterpreterReset(IP);

	// run code
	while (eAPInterpreterState_run == pIP->state) {

		pthread_mutex_lock(&pIP->gM);

		pFC = pIP->cpu.pIP;
		// check if we reached the end of the code
		if (pFC >= pIP->cpu.pCodeEnd) {
			pthread_mutex_unlock(&pIP->gM);
			return 0;
		}
		// execute command
		pFC->pHALFkt (&(pIP->cpu), pFC->param);
		// check error flags
		if (pIP->cpu.EF) {
			pthread_mutex_unlock(&pIP->gM);
			return -1;
		}
		pthread_mutex_unlock(&pIP->gM);
	}
	return 1;
}


// process the actual state
int APInterpreterProcessState(TAPInterpreter IP){
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	pthread_mutex_lock(&pIP->gM);
	pIP->state = pIP->nextState;
	int rc = 0;

	switch (pIP->state) {
		case eAPInterpreterState_idle:
			break;
		case eAPInterpreterState_loadProgramm:
			break;
		case eAPInterpreterState_run:
			pthread_mutex_unlock(&pIP->gM);
			rc = APInterpreterStateRun(IP);
			pthread_mutex_lock(&pIP->gM);
			if (rc >= 0) pIP->state = eAPInterpreterState_idle;
			break;
		case eAPInterpreterState_oneStep:
			break;
		case eAPInterpreterState_halt:
			break;
		default:
			pthread_mutex_unlock(&pIP->gM);
			return -10;
	}
	pthread_mutex_unlock(&pIP->gM);
	return rc;
}


// set interpreter state
int APInterpreterSetState (TAPInterpreter IP, int msgEndian, int32_t state) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	pthread_mutex_lock(&pIP->gM);
	APendianConversation32Bit((uint32_t *)&state,msgEndian);
	pIP->nextState = (int) state;
	pthread_mutex_unlock(&pIP->gM);
	return 0;
}

// get interpreter state
int32_t APInterpreterGetState (TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	return (int32_t) pIP->state;
}


// setup the interpreter for a new program
int APInterpreterInitNewProgramm (TAPInterpreter IP, int msgEndian, int32_t instructionsNumber, int32_t VariableNumber) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	int i;

	pthread_mutex_lock(&pIP->gM);

	APInterpreterClean (IP);

	APendianConversation32Bit((uint32_t *)&instructionsNumber, msgEndian);
	APendianConversation32Bit((uint32_t *)&VariableNumber, msgEndian);

	pIP->code = (TAPInterpreterFuncCall *) malloc(sizeof(TAPInterpreterFuncCall)*instructionsNumber);
	pIP->instructionCount = instructionsNumber;

	pIP->variables = (TAPInterpreterVariable *) malloc(sizeof(TAPInterpreterVariable) * (VariableNumber));
	for (i = 0; i < VariableNumber;i++) {
		pIP->variables[i].pData = NULL;
		pIP->variables[i].pVI = NULL;
	}
	pIP->variableCount = VariableNumber;

	pthread_mutex_unlock(&pIP->gM);

	return 0;
}

// load a variable/~array to an index
int APInterpreterLoadVar (TAPInterpreter IP, int msgEndian, int32_t index, int32_t varTypeID, int32_t numberOfElements)
{
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;

	pthread_mutex_lock(&pIP->gM);

	APendianConversation32Bit((uint32_t *)&index,msgEndian);
	APendianConversation32Bit((uint32_t *)&varTypeID,msgEndian);
	APendianConversation32Bit((uint32_t *)&numberOfElements, msgEndian);


	if ((index < 0) || (index > pIP->variableCount)) return -1;

	// set pointer to the runtime variable
	TAPInterpreterVariable * pRTV = pIP->variables + index;
	THAL_Variable const * pV = HALfindVar(varTypeID);
	if (!pV) {
		pthread_mutex_unlock(&pIP->gM);
		return -2;
	}

	pRTV->pData = pV->pFkt_create((unsigned int)numberOfElements);
	//if (!pRTV->pData) return -3;

	pRTV->pVI = pV;
	pthread_mutex_unlock(&pIP->gM);
	return 0;
}

// load a single Instruction to an index
int APInterpreterLoadInstr (TAPInterpreter IP,int msgEndian, int32_t index, int32_t * pRawInstr)
{
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;

	pthread_mutex_lock(&pIP->gM);

	APendianConversation32Bit((uint32_t *)&index,msgEndian);

	if ((index < 0) || (index > pIP->instructionCount)){
		pthread_mutex_unlock(&pIP->gM);
		return -1;
	}
	TAPInterpreterFuncCall * pIFC = pIP->code + index;
	memset (pIFC, 0, sizeof(TAPInterpreterFuncCall));

	// get function
	int32_t fid = *pRawInstr;
	APendianConversation32Bit((uint32_t *)&fid,msgEndian);

	THALFunction const * pF = HALfindFunction(fid);
	if (!pF) {
		pthread_mutex_unlock(&pIP->gM);
		return -2;
	}
	pIFC->pHALFkt = pF->pfktHAL;

	// convert parameters
	pRawInstr++; // set to the first parameter
	int i;
	THALFunctionParam const * pP = pF->paramList.pL;
	TuAPInterpreterFunctionParameter * pIFP = pIFC->param;
	for (i = 0; i < pF->paramList.number; i++) {
		if (APconvertRawParamData (msgEndian,pRawInstr,pP,pIFP,pIP->variables)) {
			pthread_mutex_unlock(&pIP->gM);
			return -3;
		}
		pP++;
		pRawInstr++;
		pIFP++;
	}
	pthread_mutex_unlock(&pIP->gM);
	return 0;
}

// gets the varaible by it's index
TAPInterpreterVariable * APInterpreterGetVariableByIndex (TAPInterpreter IP, int index) {
	return &(((TAPrealInterpreter *) IP)->variables[index]);
}

// gets the AP from the IP
void * APInterpreterGetAPfromIP (TAPInterpreter IP) {
	return ((TAPrealInterpreter *) IP)->pAP;
}

// gets the CPU from the IP
TAPInterpreterCPU * APInterpreterGetCPUref (TAPInterpreter IP) {
	return &(((TAPrealInterpreter *) IP)->cpu);
}


// ========================================
// the AP message system (thread save)
// ========================================

typedef struct SAPrealMsgSystem {
	TAPMsg * 			pOldRXMsg;		// pointer to the oldest received messages
	TAPMsg * 			pNewRXMsg;		// pointer to the newest received messages
	TAPMMU				mmu;			// the mmu
	int					sysEndianness;	// the system endianness
	int					messagecounter;	// a counter for checkin if a new message has been received

	sem_t				waitSem;		// a semaphore to wait for a message
	int					getMsgCounter;	// a counter incremented how many threads calling getMsg and are waiting
	pthread_mutex_t		gM;				// a guarding mutex
} TAPrealMsgSystem;


int SMinitial (
		void *			pVoidSM,		// pointer to the statemachine
		uint32_t * 		pD,				// pointer to the data
		int				number			// the number of data elements
	);

int SMdata (
		void *			pVoidSM,		// pointer to the statemachine
		uint32_t * 		pD,				// pointer to the data
		int				number			// the number of data elements
	);

int SMmessageFinished (
		void *			pVoidSM		// pointer to the statemachine
	);



// create AP message system
TAPMsgSystem APMScreate (
		TAPMMU				mmu,			// the mmu
		int					sysEndianness	// the system endianness
	) {
	TAPrealMsgSystem * pMS = (TAPrealMsgSystem *) malloc (sizeof(TAPrealMsgSystem));
	if (!pMS) return NULL;
	pMS->mmu = mmu;
	pMS->sysEndianness = sysEndianness;
	pMS->pOldRXMsg = NULL;
	pMS->pNewRXMsg = NULL;
	pMS->messagecounter = 0;

	pthread_mutex_init(&pMS->gM, NULL);
	sem_init (&pMS->waitSem,0,0);
	pMS->getMsgCounter = 0;

	return pMS;
}

void APMSdelete (
	TAPMsgSystem ms
	) {
	TAPrealMsgSystem * pMS = (TAPrealMsgSystem *) ms;
	sem_destroy(&pMS->waitSem);
	free (pMS);
}


// frees a message from the message system
void APMSdeleteMsg (
	TAPMsgSystem 	ms,
	TAPMsg *		pM
	) {
	TAPrealMsgSystem * pMS = (TAPrealMsgSystem *) ms;
	pthread_mutex_lock(&pMS->gM);

	AP_MMU_free(pMS->mmu,pM->memory);

	pthread_mutex_unlock(&pMS->gM);
}

// get memory for a new message
TAPMsg * APMSgetNewMsg (
		TAPrealMsgSystem *	pMsgSys,
		int					dataElementsNumber,
		const TAPMsgDrv *	pDrv
		) {
	pthread_mutex_lock(&pMsgSys->gM);

	// we go for shure that we get enough memory
	// if mod(sizeof(TAPMsg)/sizeof(uint32_t)) != 0 we need one uint32_t more -> +1
	TAPMMUmemmory m = AP_MMU_get (pMsgSys->mmu,sizeof(TAPMsg)/sizeof(uint32_t) + 1+ eAPMsgHeaderPosition_headerElementNumber + dataElementsNumber);
	if (!m) return NULL;

	// set the pointers
	uint32_t * pRD = (uint32_t *) AP_MMU_getData(m);
	TAPMsg * pM = (TAPMsg *) pRD;
	pM->memory = m;
	pM->extraData.pDrv = pDrv;
	pM->pH = (TAPMsgHeader *)((uint32_t *) pRD + sizeof(TAPMsg)/sizeof(uint32_t)+1);
	pM->pData = (uint32_t *)pM->pH + sizeof(TAPMsgHeader)/sizeof(uint32_t);
	pM->pNext = NULL;

	pthread_mutex_unlock(&pMsgSys->gM);
	return pM;
}

// insert a new message into the message queue
void APMSInsertMsg (
		TAPrealMsgSystem *	pMS,
		TAPMsg *			pM
	) {
	pthread_mutex_lock(&pMS->gM);

	if (pMS->pNewRXMsg) {
		pMS->pNewRXMsg->pNext = pM;
	}
	pMS->pNewRXMsg = pM;
	if (!pMS->pOldRXMsg) {
		pMS->pOldRXMsg = pM;
	}
	pMS->messagecounter++;

	pthread_mutex_unlock(&pMS->gM);
	sem_post(&pMS->waitSem);
}

// get oldest message
TAPMsg * APMSgetMsg (
		TAPMsgSystem 		ms,				// the message system
		TAPMessageID		msgID,			// if 0 all messages are allowed
		TAPNodeID			sender,			// if 0 all senders are allowed
		uint32_t			mNumber,		// if 0 all numbers are allowed
		int					ackMsgAllowed
	) {

	TAPrealMsgSystem * pMS = (TAPrealMsgSystem *) ms;
	// flags
	int senderOK;
	int msgIDok;
	int numberOK;
	// result var
	TAPMsg * res = NULL;

	pthread_mutex_lock(&pMS->gM);
	pMS->getMsgCounter++;
	pthread_mutex_unlock(&pMS->gM);

checkMessages:
	pthread_mutex_lock(&pMS->gM);

	// search msg list
	TAPMsg * pM = pMS->pOldRXMsg;
	TAPMsg * pAntecessorM =  NULL;
	uint32_t * pH;

	if (!pM) goto waitForMessage;


	senderOK = 0;
	msgIDok = 0;
	numberOK = 0;

	pH = *(pM->pH);

	if (!sender) {
		senderOK = 1;
	} else {
		if (pH[eAPMsgHeaderPosition_sender] == sender) senderOK = 1;
	}
	if (!msgID) {
		// filter ack/nack msg
		if (ackMsgAllowed) {
			msgIDok = 1;
		} else {
			if (
					(pH[eAPMsgHeaderPosition_msgTypeID] != eAPMsgTypes_ACK)  &&
					(pH[eAPMsgHeaderPosition_msgTypeID] != eAPMsgTypes_NACK)
				) {
				msgIDok = 1;
			}
		}
	} else {
		if (pH[eAPMsgHeaderPosition_msgTypeID] == msgID) msgIDok = 1;
	}
	if (!mNumber) {
		numberOK = 1;
	} else {
		if (pH[eAPMsgHeaderPosition_msgNumber] == mNumber) numberOK = 1;
	}
	if ((senderOK) && (msgIDok) && (numberOK)) {
		res = pM;
		goto exit;
	}
	pAntecessorM = pM;
	pM = pM->pNext;
	if (pM) goto checkMessages;
waitForMessage:
	pthread_mutex_unlock(&pMS->gM);
	if (sem_wait(&(pMS->waitSem)) == -1) goto error;

	// if other threads are waiting for a message give the sign to them
	pthread_mutex_lock(&pMS->gM);
	if (pMS->getMsgCounter > 1) {
		if (sem_post(&pMS->waitSem) == -1) goto error;
	}
	pthread_mutex_unlock(&pMS->gM);
	goto checkMessages;

exit:
	if (pAntecessorM) {
		pAntecessorM->pNext = pM->pNext;
	} else {
		pMS->pOldRXMsg = pM->pNext;
	}
	if (pM == pMS->pNewRXMsg) {
		pMS->pNewRXMsg = NULL;
	}

	// now there is one message less left
	pMS->messagecounter--;
	// now one thread is less waiting for a message
	pMS->getMsgCounter--;
	pthread_mutex_unlock(&pMS->gM);
	return res;
error:
	pthread_mutex_unlock(&pMS->gM);
	return NULL;
}

// ========================================
// the receive state machine
// ========================================

// the receive state machine state function for receiving the msg header
int SMinitial (
		void *			pVoidSM,		// pointer to the statemachine
		uint32_t * 		pD,				// pointer to the data
		int				number			// the number of data elements
	) {
	TAPReceiveStateMachine * 			pSM = (TAPReceiveStateMachine *) pVoidSM;
	TAPrealMsgSystem *					pMS = (TAPrealMsgSystem *) pSM->pMS;
	int 								copyAmount = number;
	int									i;

	// 1. try to copy the data to the header
	if (pSM->elementsLeft < copyAmount) copyAmount = pSM->elementsLeft;
	// copy
	for (i = 0; i < copyAmount;i++) {
		*pSM->pD = *pD;
		pSM->pD++;
		pD++;
	}
	pSM->elementsLeft -= copyAmount;

	// check if we have to change the statemachine because we received the header
	if (pSM->elementsLeft) return 0;

	// yes! alloc msg buffer and (opt.) transfer data

	// 2. convert endian
	int msgEndian = pSM->header[eAPMsgHeaderPosition_endian];
	for (i = 0; i < eAPMsgHeaderPosition_headerElementNumber;i++) {
		APendianConversation32Bit(&pSM->header[i],msgEndian);
	}
	// 3. now alloc message
	// 3.1 get length
	int msgElementNumber = (int) pSM->header[eAPMsgHeaderPosition_length];
	// 3.2. get memory
	pSM->pMsg = APMSgetNewMsg (pMS,msgElementNumber,pSM->pDrv);
	if (!pSM->pMsg) return -100;

	// 3.3 check getMemory result
	if (!pSM->pMsg) return -1;
	// copy message header
	pSM->pD = (uint32_t *) pSM->pMsg->pH;
	for (i = 0; i < eAPMsgHeaderPosition_headerElementNumber;i++) {
		*pSM->pD = pSM->header[i];
		pSM->pD++;
	}
	pSM->elementsLeft = pSM->header[eAPMsgHeaderPosition_length];
	// set up the data
	// 1. check if there is an data element
	if (!pSM->elementsLeft) {
		// no! now finish the message
		return SMmessageFinished(pVoidSM);
	}
	// 2. yes
	// 2.1 setup the sm for the data receiving
	pSM->state = SMdata;
	// 2.2 now check if we have to copy some data
	number -= copyAmount;
	if (number) {
		// set the data pointer
		pD += copyAmount;
		// and copy the data
		return SMdata (pVoidSM,pD,number);
	}
	return 0;
}


// the receive state machine state function for receiving the data
int SMdata (
		void *			pVoidSM,		// pointer to the statemachine
		uint32_t * 		pD,				// pointer to the data
		int				number			// the number of data elements
	) {
	TAPReceiveStateMachine * 			pSM = (TAPReceiveStateMachine *) pVoidSM;
	int 								copyAmount = number;
	int									i;
	// 1. transfer the data
	// do some clipping
	if (pSM->elementsLeft < copyAmount) copyAmount = pSM->elementsLeft;
	// copy
	for (i = 0; i < copyAmount;i++) {
		*pSM->pD = *pD;
		pSM->pD++;
		pD++;
	}
	// set statemachine work data
	pSM->elementsLeft -= copyAmount;
	// check if we have to change the statemachine
	if (pSM->elementsLeft) return 0;
	int res = SMmessageFinished (pVoidSM);
	if (res) return res;

	// check if there some bytes left to copy
	number -= copyAmount;
	if (number) {
		// set the data pointer
		pD += copyAmount;
		// and copy the data
		return pSM->state (pVoidSM,pD,number);
	}
	return 0;

}

// this function is called when all data have been received
int SMmessageFinished (
		void *			pVoidSM		// pointer to the statemachine
	) {
	TAPReceiveStateMachine * 			pSM = (TAPReceiveStateMachine *) pVoidSM;
	TAPMsg *							pM;
	// 1. reset SM
	// set the helper
	pSM->elementsLeft = eAPMsgHeaderPosition_headerElementNumber;
	pSM->pD = pSM->header;

	// data
	pM = pSM->pMsg; // save msg info for inserting
	pSM->pMsg = NULL;

	// right state function
	pSM->state = SMinitial;		// the state

	// 2. insert message at the message system
	APMSInsertMsg ((TAPrealMsgSystem *)pSM->pMS,pM);
	return 0;
}


// inits the state machine
void APInitReceiveStateMachine (
		TAPReceiveStateMachine * 			pSM,	// pointer to the state machine
		TAPMsgSystem						pMS,	// pointer to the message system
		const TAPMsgDrv  *					pDrv	// the driver associated with the statemachine
	) {
	pSM->state = SMinitial;
	pSM->pMS = pMS;
	pSM->pDrv = pDrv;
	// set the helper
	pSM->elementsLeft = eAPMsgHeaderPosition_headerElementNumber;
	pSM->pD = pSM->header;

	// data
	pSM->pMsg = NULL;
}

int APHandleMsg (
		TAP *		pAP,
		TAPMsg * 	pM
	) {

	TAPMessageID								msgID;
	const THALMsgProcessMessageAssociation *	pMsgIDandFunctAsso;
	int											i;

	// get message id
	msgID = (*(pM->pH))[eAPMsgHeaderPosition_msgTypeID];
	// search handler
	pMsgIDandFunctAsso = gHALMsgProcessRXHandlers.pL;
	for (i = 0; i < gHALMsgProcessRXHandlers.number;i++) {
		if (((TAPMessageID)pMsgIDandFunctAsso->msgID) == msgID) {
			return pMsgIDandFunctAsso->pfktHandle(pAP,pM);
		}
		pMsgIDandFunctAsso++;
	}
	return -1;
}

void APMessageProcessingThread (TAP * pAP) {

	TAPrealMsgSystem *		pMS = (TAPrealMsgSystem *) pAP->MS;
	TAPMsg *				pM;
	TAPNodeID 				recv;
	while (1) {
		// get the message
		pM = APMSgetMsg (pMS,0,0,0,0);
		if (!pM) goto error;
		// search the message handler
		recv = (*(pM->pH))[eAPMsgHeaderPosition_receiver];
		if ((recv == dAPNodeID_ALL) || (recv == pAP->nodeID)) {
			if(APHandleMsg (pAP,pM)) goto exit;
		}
		// free memory
		APMSdeleteMsg (pAP->MS,pM);
	}
exit:
	// free memory
	APMSdeleteMsg (pAP->MS,pM);
error:
	return;
}

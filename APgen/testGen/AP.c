//==================================================
//	AP generator v.0.1 alpha
//	timestamp: 2013-01-23 17:07:35.637000
//==================================================


//#include "AP.h"
//#include <string.h>

#include "AP.h"
#include <pthread.h>


// math defines

#ifndef M_E
	#define M_E		2.7182818284590452354
#endif

#ifndef M_LOG2E
	#define M_LOG2E		1.4426950408889634074
#endif

#ifndef M_LOG10E
	#define M_LOG10E	0.43429448190325182765
#endif

#ifndef M_LN2
	#define M_LN2		0.69314718055994530942
#endif

#ifndef M_LN10
	#define M_LN10		2.30258509299404568402
#endif

#ifndef M_PI
	#define M_PI		3.14159265358979323846
#endif

#ifndef M_PI_2
	#define M_PI_2		1.57079632679489661923
#endif

#ifndef M_PI_4
	#define M_PI_4		0.78539816339744830962
#endif

#ifndef M_1_PI
	#define M_1_PI		0.31830988618379067154
#endif

#ifndef M_2_PI
	#define M_2_PI		0.63661977236758134308
#endif

#ifndef M_2_SQRTPI
	#define M_2_SQRTPI	1.12837916709551257390
#endif

#ifndef M_SQRT2
	#define M_SQRT2		1.41421356237309504880
#endif

#ifndef M_SQRT1_2
	#define M_SQRT1_2	0.70710678118654752440
#endif


// ===============================
// basic type list
// ===============================

// ===============================
// basic type list
// ===============================

// declare the basic io type array
THAL_basicIO const gHALbasicIOtype []= {
	{1,4,0},	//rational
	{2,4,1},	//integer
	{3,1,0},	//char
	{4,4,0}		//raw
};

THAL_basicIOList const gHALbasicIOtypeList = {
	gHALbasicIOtype,
	4
};

// a global variable holding the endianness of the architecture
int gAPendianFlag;

// convert endianness
void APendianConversation32Bit (
		uint32_t * 	pD,				//!< pointer to the data array
		int			srcEndianess	//!< endianness of the data
	) {
    uint32_t res;
    if (srcEndianess != gAPendianFlag) {
		res = (*pD & 0x000000FF) << 24;
		res |= (*pD & 0x0000FF00) << 8;
		res |= (*pD & 0x00FF0000) >> 8;
		res |= (*pD & 0xFF000000) >> 24;
		*pD = res;
    }
}

// converts data
int APconvertRawParamData (int dataEndianes, void * pData, THALFunctionParam const * pPD, TuAPInterpreterFunctionParameter * pP, TAPInterpreterVariable *pIVL) {
    int index;
    
    if (eHALfunctionParamClass_basicIOtype == pPD->paramClass) goto basictypeConv;
    APendianConversation32Bit((uint32_t *)pData, dataEndianes);
    index = (int) *((int32_t *)pData);
    switch (pPD->paramClass) {
        case eHALfunctionParamClass_refVar:
            pP->fp_pV = &pIVL[index];
            break;
        case eHALfunctionParamClass_refDataVar:
            pP->fp_pD = pIVL[index].pVI->pFkt_decodeData(pIVL[index].pData);
            break;
        case eHALfunctionParamClass_VarID:
            pP->fp_VarID = index ;
            break;
        case eHALfunctionParamClass_VarIndex:
            pP->fp_VarIndex = index ;
            break;
    }
    return 0;
basictypeConv:
    switch (pPD->paramTypeID) {
		case 1:
			pP->fp_rational = *((float* )pData);
			break;
		case 2:
			APendianConversation32Bit((uint32_t *)pData, dataEndianes);
			pP->fp_integer = *((int32_t* )pData);
			break;
		case 3:
			pP->fp_char = *((char* )pData);
			break;
		case 4:
			pP->fp_raw = *((uint32_t* )pData);
			break;
		default:
			return -1;
	};
	return 0;
};


// ===============================
// extra code from the groups
// ===============================



// ===============================
// message types
// ===============================

enum eAPMsgTypes {

	eAPMsgTypes_run = 22,
	eAPMsgTypes_ACK = 1,
	eAPMsgTypes_NACK = 2,
	eAPMsgTypes_stop = 20,
	eAPMsgTypes_startPrg = 10,
	eAPMsgTypes_sendVariable = 11,
	eAPMsgTypes_logout = 31,
	eAPMsgTypes_endPrg = 13,
	eAPMsgTypes_sendInstruction = 12,
	eAPMsgTypes_step = 21,
	eAPMsgTypes_login = 30,
	eAPMsgTypes_updateVariable = 23
};


// ===============================
// message driver
// ===============================

// message system driver with uuid=1
// description: winAPdrv

// the driver functions
// ===============================
// driver uuid =1
// ===============================
// ------------------------------
// drv own functions
// ------------------------------

#define dAPClientServerAdminPort (50000)
#define dAPClientInitBuffer (1024)

// struct for the drv data
typedef struct SAPTCPIPdrv {
	TAPClient 					cl;			//!< tcp/ip client
	TAPMsgHeader				txHeader;	//!< transmit header template
	TAPReceiveStateMachine		rxSM;		//!< receive state machine
} TAPTCPIPdrv;

// ------------------------------
// drv own functions
// ------------------------------

int drv_1_sendHeader (
		TAPClient * pCl,
		uint32_t * pH,
		uint32_t msgId,
		uint32_t recv,
		uint32_t num,
		uint32_t length
	) {
	pH[eAPMsgHeaderPosition_msgTypeID] = msgId;
	pH[eAPMsgHeaderPosition_msgNumber] = num;
	pH[eAPMsgHeaderPosition_receiver] = recv;
	pH[eAPMsgHeaderPosition_length] = length;
	if (APclient_send(pCl,sizeof(TAPMsgHeader),(uint8_t *)pH)) return -1;
	return 0;
}

// call back function of the TCP/IP driver
int drv_1_cbAPClient (void *pvDC, uint16_t number, uint8_t * pData) {
	TAPReceiveStateMachine * pSM = pvDC;
	return pSM->state (pSM, (uint32_t *) pData, number / sizeof(uint32_t));
}

//open an existing driver and bind it to the AP
int drv_1_open (void * pAP, struct SAPMsgDrv *pDrv) {
	TAPTCPIPdrv * pDC = NULL;

	pDC = malloc(sizeof(TAPTCPIPdrv));
	if (!pDC) return -1;
	if (APclient_create(&(pDC->cl),dAPClientServerAdminPort,dAPClientInitBuffer,&(pDC->rxSM),drv_1_cbAPClient)) return -2;
	// init header
	pDC->txHeader[eAPMsgHeaderPosition_endian] = (uint32_t) gAPendianFlag;
	pDC->txHeader[eAPMsgHeaderPosition_sender] = ((TAP *) pAP)->nodeID;
	pDC->txHeader[eAPMsgHeaderPosition_receiver] = dAPNodeID_ALL;
	pDC->txHeader[eAPMsgHeaderPosition_msgTypeID] = 0;
	pDC->txHeader[eAPMsgHeaderPosition_msgNumber] = 0;
	pDC->txHeader[eAPMsgHeaderPosition_length] = 0;

	// save driver data
	pDrv->pDrvData = pDC;

	// init receive state machine
	APInitReceiveStateMachine(
			&pDC->rxSM,
			((TAP *)pAP)->MS,
			pDrv
		);
	return 0;
}
//close the driver
int drv_1_close (struct SAPMsgDrv *pDrv) {
	TAPTCPIPdrv * pDC = (TAPTCPIPdrv *)(pDrv->pDrvData);
	if (pDC) {
		APclient_close(&pDC->cl);
	}
	return 0;
}
//destroys the driver
int drv_1_destroy (struct SAPMsgDrv *pDrv) {
	TAPTCPIPdrv * pDC = (TAPTCPIPdrv *)(pDrv->pDrvData);
	if (pDC) {
		free(pDC);
		pDrv->pDrvData = NULL;
	}
	return 0;
}

//sends raw data
int drv_1_sendRaw (struct SAPMsgDrv *pDrv, int amount, uint32_t * pData) {
	TAPTCPIPdrv * pDC = (TAPTCPIPdrv *)(pDrv->pDrvData);
	return APclient_send(&(pDC->cl),amount*sizeof(uint32_t),(uint8_t *)pData);
}

//a AP is going to be logged out of the system
int drv_1_sendInteger32 (struct SAPMsgDrv *pDrv, int amount, int32_t * pData) {
	TAPTCPIPdrv * pDC = (TAPTCPIPdrv *)(pDrv->pDrvData);

	if (gAPendianFlag == eAP_littleEndian) {
		return APclient_send(&(pDC->cl),amount*sizeof(uint32_t),(uint8_t *)pData);
	} else {
		int i;
		int32_t v;
		for (i = 0; i < amount; i++) {
			v = *pData;
			APendianConversation32Bit((uint32_t *)&v,eAP_littleEndian);
			if (APclient_send(&(pDC->cl),sizeof(int32_t),(uint8_t *)&v)) {
				return -1;
			}
			pData++;
		}
	}
	return 0;
}

//a AP is going to be logged out of the system
int drv_1_sendFloat32 (struct SAPMsgDrv *pDrv, int amount, float * pData) {
	TAPTCPIPdrv * pDC = (TAPTCPIPdrv *)(pDrv->pDrvData);

	return APclient_send(&(pDC->cl),amount*sizeof(float),(uint8_t *)pData);
}



//acknowledge
int drv_1_ACK (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_ACK, receiver, mNum, 0);
}
//not acknowledge
int drv_1_NACK (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_NACK, receiver, mNum, 0);
}
//start sending a program
int drv_1_startPrg (void *pDrvData, uint32_t receiver, uint32_t mNum, int32_t globalVariableNumber, int32_t localVariableNumber, int32_t instructionNumber) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;
	if (
			drv_1_sendHeader(pCl, pH, eAPMsgTypes_startPrg, receiver, mNum, 0) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&globalVariableNumber) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&localVariableNumber) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&instructionNumber)
		) return -10;
	return 0;
}

//sends a variable
int drv_1_sendVariable (void *pDrvData, uint32_t receiver, uint32_t mNum, int32_t index, int32_t varTypeID, int32_t num) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;
	if (
			drv_1_sendHeader(pCl, pH, eAPMsgTypes_sendVariable, receiver, mNum, 3) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&index) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&varTypeID) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&num)
		) return -10;
	return 0;
}
//sends an instruction
int drv_1_sendInstruction (void *pDrvData, uint32_t receiver, uint32_t mNum, int32_t index, uint32_t * fbc) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;
	if (
			drv_1_sendHeader(pCl, pH, eAPMsgTypes_sendInstruction, receiver, mNum, dAPInterpreterFuncMaxParams + 1) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&index) ||
			APclient_send(pCl,sizeof(int32_t)*dAPInterpreterFuncMaxParams,(uint8_t *)fbc)
		) return -10;
	return 0;
}
//sings that the program transmission has completed
int drv_1_endPrg (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_endPrg, receiver, mNum, 0);
}
//stops the AP
int drv_1_stop (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_stop, receiver, mNum, 0);
}
//the AP executes one instruction
int drv_1_step (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_step, receiver, mNum, 0);
}
//the AP runs the program
int drv_1_run (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_run, receiver, mNum, 0);
}
//a variable going to be updated
int drv_1_updateVariable (void *pDrvData, uint32_t receiver, uint32_t mNum, int32_t gIndex, int32_t dataElements) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;
	if (
			drv_1_sendHeader(pCl, pH, eAPMsgTypes_updateVariable, receiver, mNum, dataElements + 1) ||
			APclient_send(pCl,sizeof(int32_t),(uint8_t *)&gIndex)
		) return -10;
	return 0;
}
//a AP is going to be logged in to the system
int drv_1_login (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_login, receiver, mNum, 0);
}
//a AP is going to be logged out of the system
int drv_1_logout (void *pDrvData, uint32_t receiver, uint32_t mNum) {
	TAPClient * pCl = &((TAPTCPIPdrv *)(pDrvData))->cl;
	uint32_t * pH = ((TAPTCPIPdrv *)(pDrvData))->txHeader;

	return drv_1_sendHeader(pCl, pH, eAPMsgTypes_logout, receiver, mNum, 0);
}


// the init function for driver 1
void APdriver_1_init (TAPMsgDrv  * pDrv) {
    memset(pDrv,0,sizeof(TAPMsgDrv));
    pDrv->pfkt_open = drv_1_open;
	pDrv->pfkt_close = drv_1_close;
	pDrv->pfkt_destroy = drv_1_destroy;
	pDrv->pfkt_sendRaw = drv_1_sendRaw;
	pDrv->pfkt_sendInteger32 = drv_1_sendInteger32;
	pDrv->pfkt_sendFloat32 = drv_1_sendFloat32;
	pDrv->pfkt_ACK = drv_1_ACK;
	pDrv->pfkt_NACK = drv_1_NACK;
	pDrv->pfkt_startPrg = drv_1_startPrg;
	pDrv->pfkt_sendVariable = drv_1_sendVariable;
	pDrv->pfkt_sendInstruction = drv_1_sendInstruction;
	pDrv->pfkt_endPrg = drv_1_endPrg;
	pDrv->pfkt_stop = drv_1_stop;
	pDrv->pfkt_step = drv_1_step;
	pDrv->pfkt_run = drv_1_run;
	pDrv->pfkt_updateVariable = drv_1_updateVariable;
	pDrv->pfkt_login = drv_1_login;
	pDrv->pfkt_logout = drv_1_logout;
}

// ===============================
// message processes
// ===============================

// msg process :logout descr: log the AP out of the system
int TX_logout( TAP * pAP ){
		TAPNodeID	recv;
		uint32_t	mNum;
		const TAPMsgDrv *	driver;
		int	_generated_lv1;
	
	
	recv=dAPNodeID_ALL;
	driver = pAP->pDrvList;
	for(_generated_lv1=0; _generated_lv1 < pAP->driverNumber; _generated_lv1++) {
		mNum=APgetNewMessageNumber(pAP);
		driver->pfkt_logout ( driver->pDrvData ,recv,mNum );
		driver++;
		}
	
	return 0;
	
	}
// msg process :updateVariable descr: updates a global variable at diffrent systems
int TX_updateVariable( TAP * pAP , uint32_t vi){
		uint32_t	mNum;
		TAPInterpreterVariable *	apV;
		TAPNode *	node;
	
	
	apV=APInterpreterGetVariableByIndex(pAP->IP,vi);
	node = pAP->pNodeList;
	while (node) {
		if ((node->nodeID!=pAP->nodeID) ) {
			mNum=APgetNewMessageNumber(pAP);
			apV->pVI->pFkt_sendUpdate(apV->pData,node->pDrv,dAPNodeID_ALL,mNum,vi);
			if ((APwaitAck (pAP, mNum)) ) {
				return -1;
				}
			
			}
		
		node = node->pNext;
		}
	
	return 0;
	
	}
// msg process :login descr: log in the AP to the system
int TX_login( TAP * pAP ){
		TAPNodeID	recv;
		uint32_t	mNum;
		const TAPMsgDrv *	driver;
		int	_generated_lv1;
	
	
	recv=dAPNodeID_ALL;
	driver = pAP->pDrvList;
	for(_generated_lv1=0; _generated_lv1 < pAP->driverNumber; _generated_lv1++) {
		mNum=APgetNewMessageNumber(pAP);
		driver->pfkt_login ( driver->pDrvData ,recv,mNum );
		driver++;
		}
	
	return 0;
	
	}
// msg process :run descr: runs the audio-processor
int TX_run( TAP * pAP , TAPNodeID dest){
		const TAPMsgDrv *	driver;
		TAPNodeID	sender;
		uint32_t	mNum;
		const TAPMsgDrv *	drv;
		int	_generated_lv1;
	
	
	
	sender=pAP->nodeID;
	if ((dest!=dAPNodeID_ALL) ) {
		mNum=APgetNewMessageNumber(pAP);
		driver=APfindDrvBySenderID(pAP,dest);
		driver->pfkt_run ( driver->pDrvData ,sender,mNum );
		return APwaitAck (pAP, mNum);
		}
	
	drv = pAP->pDrvList;
	for(_generated_lv1=0; _generated_lv1 < pAP->driverNumber; _generated_lv1++) {
		mNum=APgetNewMessageNumber(pAP);
		drv->pfkt_run ( drv->pDrvData ,sender,mNum );
		if ((APwaitAck (pAP, mNum)) ) {
			return -1;
			}
		
		drv++;
		}
	
	return 0;
	
	}
// message RX process

// message RX process handle functions
int RX_run( TAP * pAP , TAPMsg * pMsg ){
		TAPNodeID	sender;
		const TAPMsgDrv *	driver;
		uint32_t	mNum;
	
	
	
	sender=(*(pMsg->pH))[eAPMsgHeaderPosition_sender];
	driver=pMsg->extraData.pDrv;
	mNum=(*(pMsg->pH))[eAPMsgHeaderPosition_msgNumber];
	if ((!(APrun(pAP))) ) {
		return driver->pfkt_ACK ( driver->pDrvData ,sender,mNum );
		
		} else {
		return driver->pfkt_NACK ( driver->pDrvData ,sender,mNum );
		}
	
	
	}

int RX_updateVariable( TAP * pAP , TAPMsg * pMsg ){
		TAPNodeID	sender;
		const TAPMsgDrv *	driver;
		uint32_t	mNum;
		TAPInterpreterVariable *	apV;
		int32_t	gIndex;
	
	
	
	
	
	sender=(*(pMsg->pH))[eAPMsgHeaderPosition_sender];
	driver=pMsg->extraData.pDrv;
	mNum=(*(pMsg->pH))[eAPMsgHeaderPosition_msgNumber];
	gIndex=((uint32_t *)pMsg->pData)[0];
	apV=APInterpreterGetVariableByIndex(pAP->IP,gIndex);
	if ((!(apV)) ) {
		return -1;
		}
	
	apV->pVI->pFkt_recvUpdate(apV->pData,pMsg->pData);
	return driver->pfkt_ACK ( driver->pDrvData ,sender,mNum );
	
	}

int RX_login( TAP * pAP , TAPMsg * pMsg ){
		TAPNodeID	sender;
		const TAPMsgDrv *	driver;
		uint32_t	mNum;
	
	
	
	sender=(*(pMsg->pH))[eAPMsgHeaderPosition_sender];
	driver=pMsg->extraData.pDrv;
	mNum=(*(pMsg->pH))[eAPMsgHeaderPosition_msgNumber];
	if ((!(APaddNode(pAP, sender, driver ))) ) {
		return driver->pfkt_login ( driver->pDrvData ,sender,mNum );
		}
	
	return 0;
	
	}

int RX_logout( TAP * pAP , TAPMsg * pMsg ){
		TAPNodeID	sender;
	
	sender=(*(pMsg->pH))[eAPMsgHeaderPosition_sender];
	APremoveNode(pAP, sender );
	return 0;
	
	}

// rx handler array var
const THALMsgProcessMessageAssociation const gHALMsgProcessRXHandlerArray [] = {
	{22,RX_run},
	{23,RX_updateVariable},
	{30,RX_login},
	{31,RX_logout}
};
// message RX global var
const HALMsgProcessHandlerList const gHALMsgProcessRXHandlers = {
	gHALMsgProcessRXHandlerArray,
	4
};


// ===============================
// HAL helper
// ===============================


// searches the variable list for a variable with the id
THAL_Variable const  * HALfindVar (int varID)
{
	THAL_Variable const * pV = gHALVariableList.pL;
	int i;
	for (i = 0; i < gHALVariableList.number;i++) {
		if (pV->id == varID) return pV;
		pV++;
	}
	return NULL;
}

// searches the function list for a function with the id
THALFunction const * HALfindFunction (int fid)
{
	THALFunction const * pF = gHALFunctionList.pL;
	int i;
	for (i = 0; i < gHALFunctionList.number; i++) {
		if (pF->fid == fid) return pF;
		pF++;
	}
	return NULL;
}
// ===============================
// the AP
// ===============================

// ===========================================
// remote interface audio processor template
// ===========================================

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
TAPMMU AP_MMU_create (int elementsNumber) {
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
TAPMMUmemmory AP_MMU_get (TAPMMU mmu, int elements) {
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

	pIP->gM = PTHREAD_MUTEX_INITIALIZER;

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

int APInterpreterStateRun(TAPInterpreter IP) {
	TAPrealInterpreter * pIP = (TAPrealInterpreter *) IP;
	TAPInterpreterFuncCall * pFC;

	// setup cpu
	pIP->cpu.CF = 0;
	pIP->cpu.EF = 0;
	pIP->cpu.pIP = pIP->code;
	pIP->cpu.pCodeStart = pIP->code;
	pIP->cpu.pCodeEnd = pIP->code + pIP->instructionCount;

	// run code
	while (eAPInterpreterState_run == pIP->state) {

		pthread_mutex_lock(&pIP->gM);

		pFC = pIP->cpu.pIP;
		// check if we reached the end of the code
		if (pFC > pIP->cpu.pCodeEnd) {
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

// ========================================
// the AP message system (thread save)
// ========================================

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

	pMS->gM = PTHREAD_MUTEX_INITIALIZER;
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


// wait for an ack
int APwaitAck (TAP * pAP,uint32_t mNumber) {
	TAPMsg * pM;
	pM = APMSgetMsg (pAP->MS,eAPMsgTypes_ACK,0,mNumber,1);
	// delete msg
	if (pM) {
		APMSdeleteMsg (pAP->MS,pM);
		return 0;
	}
	return -1;
}

// ===============================
// variables
// ===============================

// ===============================
// variable implementation for rational (varID=1)
// ===============================

// element structure for rational
typedef struct SApVar_ele_rational {
	float value;//the value of the number
} TApVar_ele_rational;

// vector structure for rational
typedef struct SApVar_vec_rational {
    TApVar_ele_rational * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_rational;


// updates a variable the AP
int HALimpl_1_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for rational
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_rational * pV =(TApVar_vec_rational *) pVarData;
	TApVar_ele_rational * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a rational vector
		TApVar_vec_rational * pV = (TApVar_vec_rational *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for rational
		pV->pFE = malloc(sizeof(TApVar_ele_rational)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx value
		// no endian conversation
		pE->value=*((float *)pD);
		pD++;
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_1_create ( unsigned int numberOfElements ) {
 // create a new rational vector
	TApVar_vec_rational * pV;
	 
	pV = malloc(sizeof(TApVar_vec_rational));
	if (!pV) {
	    return NULL;
	}
	// create the elements for rational
	pV->pFE = malloc(sizeof(TApVar_ele_rational)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_1_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for rational
	TApVar_vec_rational * pV =(TApVar_vec_rational *) pVarData;
	TApVar_ele_rational * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 1;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendFloat32(pMD,1,&pE->value);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_1_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_1_delete ( void * pVarData ) {
 TApVar_ele_rational * pE;
	int32_t i;// frees a rational vector
	TApVar_vec_rational * pV = (TApVar_vec_rational *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for integer (varID=2)
// ===============================

// element structure for integer
typedef struct SApVar_ele_integer {
	int32_t value;//the value of the number
} TApVar_ele_integer;

// vector structure for integer
typedef struct SApVar_vec_integer {
    TApVar_ele_integer * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_integer;


// updates a variable the AP
int HALimpl_2_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for integer
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_integer * pV =(TApVar_vec_integer *) pVarData;
	TApVar_ele_integer * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a integer vector
		TApVar_vec_integer * pV = (TApVar_vec_integer *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for integer
		pV->pFE = malloc(sizeof(TApVar_ele_integer)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx value
		APendianConversation32Bit(pD,eAP_littleEndian);
		pE->value=*((int32_t *)pD);
		pD++;
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_2_create ( unsigned int numberOfElements ) {
 // create a new integer vector
	TApVar_vec_integer * pV;
	 
	pV = malloc(sizeof(TApVar_vec_integer));
	if (!pV) {
	    return NULL;
	}
	// create the elements for integer
	pV->pFE = malloc(sizeof(TApVar_ele_integer)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_2_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for integer
	TApVar_vec_integer * pV =(TApVar_vec_integer *) pVarData;
	TApVar_ele_integer * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 1;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendInteger32(pMD,1,&pE->value);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_2_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_2_delete ( void * pVarData ) {
 TApVar_ele_integer * pE;
	int32_t i;// frees a integer vector
	TApVar_vec_integer * pV = (TApVar_vec_integer *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for string (varID=3)
// ===============================

// element structure for string
typedef struct SApVar_ele_string {
	int32_t length;//the length of the string
	char * pA_text;// the text of the string (array)
	int32_t num_text;// amount of text elements
} TApVar_ele_string;

// vector structure for string
typedef struct SApVar_vec_string {
    TApVar_ele_string * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_string;


// updates a variable the AP
int HALimpl_3_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for string
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_string * pV =(TApVar_vec_string *) pVarData;
	TApVar_ele_string * pE;
	int i, imax;
	int32_t n, nmax;
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a string vector
		TApVar_vec_string * pV = (TApVar_vec_string *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
					// delete parameter text
					if (pE->pA_text) {
					    free(pE->pA_text);
					    pE->pA_text=NULL;
					    pE->num_text=0;
					}
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for string
		pV->pFE = malloc(sizeof(TApVar_ele_string)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx length
		APendianConversation32Bit(pD,eAP_littleEndian);
		pE->length=*((int32_t *)pD);
		pD++;
		// rx text
		APendianConversation32Bit(pD,eAP_littleEndian);
		nmax = *((int32_t *) pD);
		// resize parameter
		if (nmax != pE->num_text) {
		    if (pE->pA_text) free(pE->pA_text);
		    pE->pA_text = malloc(sizeof(char)*nmax);
		    if (!pE->pA_text) return -2;
		    pE->num_text = nmax;
		}
		
		pD++;
		for (n = 0; n < pE->num_text; n++) {
		    // no endian conversation
		    pE->pA_text[n]=*((char *)pD);
		    pD++;
		}
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_3_create ( unsigned int numberOfElements ) {
 // create a new string vector
	TApVar_vec_string * pV;
	 
	pV = malloc(sizeof(TApVar_vec_string));
	if (!pV) {
	    return NULL;
	}
	// create the elements for string
	pV->pFE = malloc(sizeof(TApVar_ele_string)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_3_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for string
	TApVar_vec_string * pV =(TApVar_vec_string *) pVarData;
	TApVar_ele_string * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 2;
	// calc amount of elements from the params
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    dataAmount += pE->num_text;
	}
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendInteger32(pMD,1,&pE->length);
		pMD->pfkt_sendInteger32(pMD,1,&pE->num_text);
		pMD->pfkt_sendRaw(pMD,pE->num_text,pE->pA_text);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_3_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_3_delete ( void * pVarData ) {
 TApVar_ele_string * pE;
	int32_t i;// frees a string vector
	TApVar_vec_string * pV = (TApVar_vec_string *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
				// delete parameter text
				if (pE->pA_text) {
				    free(pE->pA_text);
				    pE->pA_text=NULL;
				    pE->num_text=0;
				}
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for complex (varID=4)
// ===============================

// element structure for complex
typedef struct SApVar_ele_complex {
	float r;//real part
	int32_t i;//imaginary part
} TApVar_ele_complex;

// vector structure for complex
typedef struct SApVar_vec_complex {
    TApVar_ele_complex * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_complex;


// updates a variable the AP
int HALimpl_4_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for complex
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_complex * pV =(TApVar_vec_complex *) pVarData;
	TApVar_ele_complex * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a complex vector
		TApVar_vec_complex * pV = (TApVar_vec_complex *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
					
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for complex
		pV->pFE = malloc(sizeof(TApVar_ele_complex)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx r
		// no endian conversation
		pE->r=*((float *)pD);
		pD++;
		// rx i
		APendianConversation32Bit(pD,eAP_littleEndian);
		pE->i=*((int32_t *)pD);
		pD++;
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_4_create ( unsigned int numberOfElements ) {
 // create a new complex vector
	TApVar_vec_complex * pV;
	 
	pV = malloc(sizeof(TApVar_vec_complex));
	if (!pV) {
	    return NULL;
	}
	// create the elements for complex
	pV->pFE = malloc(sizeof(TApVar_ele_complex)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_4_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for complex
	TApVar_vec_complex * pV =(TApVar_vec_complex *) pVarData;
	TApVar_ele_complex * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 2;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendFloat32(pMD,1,&pE->r);
		pMD->pfkt_sendInteger32(pMD,1,&pE->i);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_4_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_4_delete ( void * pVarData ) {
 TApVar_ele_complex * pE;
	int32_t i;// frees a complex vector
	TApVar_vec_complex * pV = (TApVar_vec_complex *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
				
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for biquad (varID=10)
// ===============================

// element structure for biquad
typedef struct SApVar_ele_biquad {
	float a0;//enumerator coefficient
	float a1;//enumerator coefficient
	float a2;//enumerator coefficient
	float b0;//numerator coefficient
	float b1;//numerator coefficient
	float b2;//numerator coefficient
} TApVar_ele_biquad;

// vector structure for biquad
typedef struct SApVar_vec_biquad {
    TApVar_ele_biquad * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_biquad;


// updates a variable the AP
int HALimpl_10_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for biquad
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_biquad * pV =(TApVar_vec_biquad *) pVarData;
	TApVar_ele_biquad * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a biquad vector
		TApVar_vec_biquad * pV = (TApVar_vec_biquad *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
					
					
					
					
					
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for biquad
		pV->pFE = malloc(sizeof(TApVar_ele_biquad)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx a0
		// no endian conversation
		pE->a0=*((float *)pD);
		pD++;
		// rx a1
		// no endian conversation
		pE->a1=*((float *)pD);
		pD++;
		// rx a2
		// no endian conversation
		pE->a2=*((float *)pD);
		pD++;
		// rx b0
		// no endian conversation
		pE->b0=*((float *)pD);
		pD++;
		// rx b1
		// no endian conversation
		pE->b1=*((float *)pD);
		pD++;
		// rx b2
		// no endian conversation
		pE->b2=*((float *)pD);
		pD++;
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_10_create ( unsigned int numberOfElements ) {
 // create a new biquad vector
	TApVar_vec_biquad * pV;
	 
	pV = malloc(sizeof(TApVar_vec_biquad));
	if (!pV) {
	    return NULL;
	}
	// create the elements for biquad
	pV->pFE = malloc(sizeof(TApVar_ele_biquad)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_10_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for biquad
	TApVar_vec_biquad * pV =(TApVar_vec_biquad *) pVarData;
	TApVar_ele_biquad * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 6;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendFloat32(pMD,1,&pE->a0);
		pMD->pfkt_sendFloat32(pMD,1,&pE->a1);
		pMD->pfkt_sendFloat32(pMD,1,&pE->a2);
		pMD->pfkt_sendFloat32(pMD,1,&pE->b0);
		pMD->pfkt_sendFloat32(pMD,1,&pE->b1);
		pMD->pfkt_sendFloat32(pMD,1,&pE->b2);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_10_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_10_delete ( void * pVarData ) {
 TApVar_ele_biquad * pE;
	int32_t i;// frees a biquad vector
	TApVar_vec_biquad * pV = (TApVar_vec_biquad *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
				
				
				
				
				
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for noisegate (varID=11)
// ===============================

// element structure for noisegate
typedef struct SApVar_ele_noisegate {
} TApVar_ele_noisegate;

// vector structure for noisegate
typedef struct SApVar_vec_noisegate {
    TApVar_ele_noisegate * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_noisegate;


// updates a variable the AP
int HALimpl_11_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for noisegate
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_noisegate * pV =(TApVar_vec_noisegate *) pVarData;
	TApVar_ele_noisegate * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a noisegate vector
		TApVar_vec_noisegate * pV = (TApVar_vec_noisegate *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for noisegate
		pV->pFE = malloc(sizeof(TApVar_ele_noisegate)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_11_create ( unsigned int numberOfElements ) {
 // create a new noisegate vector
	TApVar_vec_noisegate * pV;
	 
	pV = malloc(sizeof(TApVar_vec_noisegate));
	if (!pV) {
	    return NULL;
	}
	// create the elements for noisegate
	pV->pFE = malloc(sizeof(TApVar_ele_noisegate)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_11_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for noisegate
	TApVar_vec_noisegate * pV =(TApVar_vec_noisegate *) pVarData;
	TApVar_ele_noisegate * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_11_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_11_delete ( void * pVarData ) {
 // frees a noisegate vector
	TApVar_vec_noisegate * pV = (TApVar_vec_noisegate *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for expander (varID=12)
// ===============================

// element structure for expander
typedef struct SApVar_ele_expander {
} TApVar_ele_expander;

// vector structure for expander
typedef struct SApVar_vec_expander {
    TApVar_ele_expander * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_expander;


// updates a variable the AP
int HALimpl_12_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for expander
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_expander * pV =(TApVar_vec_expander *) pVarData;
	TApVar_ele_expander * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a expander vector
		TApVar_vec_expander * pV = (TApVar_vec_expander *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for expander
		pV->pFE = malloc(sizeof(TApVar_ele_expander)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_12_create ( unsigned int numberOfElements ) {
 // create a new expander vector
	TApVar_vec_expander * pV;
	 
	pV = malloc(sizeof(TApVar_vec_expander));
	if (!pV) {
	    return NULL;
	}
	// create the elements for expander
	pV->pFE = malloc(sizeof(TApVar_ele_expander)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_12_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for expander
	TApVar_vec_expander * pV =(TApVar_vec_expander *) pVarData;
	TApVar_ele_expander * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_12_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_12_delete ( void * pVarData ) {
 // frees a expander vector
	TApVar_vec_expander * pV = (TApVar_vec_expander *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for compressor (varID=13)
// ===============================

// element structure for compressor
typedef struct SApVar_ele_compressor {
} TApVar_ele_compressor;

// vector structure for compressor
typedef struct SApVar_vec_compressor {
    TApVar_ele_compressor * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_compressor;


// updates a variable the AP
int HALimpl_13_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for compressor
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_compressor * pV =(TApVar_vec_compressor *) pVarData;
	TApVar_ele_compressor * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a compressor vector
		TApVar_vec_compressor * pV = (TApVar_vec_compressor *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for compressor
		pV->pFE = malloc(sizeof(TApVar_ele_compressor)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_13_create ( unsigned int numberOfElements ) {
 // create a new compressor vector
	TApVar_vec_compressor * pV;
	 
	pV = malloc(sizeof(TApVar_vec_compressor));
	if (!pV) {
	    return NULL;
	}
	// create the elements for compressor
	pV->pFE = malloc(sizeof(TApVar_ele_compressor)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_13_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for compressor
	TApVar_vec_compressor * pV =(TApVar_vec_compressor *) pVarData;
	TApVar_ele_compressor * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_13_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_13_delete ( void * pVarData ) {
 // frees a compressor vector
	TApVar_vec_compressor * pV = (TApVar_vec_compressor *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for limiter (varID=14)
// ===============================

// element structure for limiter
typedef struct SApVar_ele_limiter {
} TApVar_ele_limiter;

// vector structure for limiter
typedef struct SApVar_vec_limiter {
    TApVar_ele_limiter * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_limiter;


// updates a variable the AP
int HALimpl_14_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for limiter
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_limiter * pV =(TApVar_vec_limiter *) pVarData;
	TApVar_ele_limiter * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a limiter vector
		TApVar_vec_limiter * pV = (TApVar_vec_limiter *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for limiter
		pV->pFE = malloc(sizeof(TApVar_ele_limiter)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_14_create ( unsigned int numberOfElements ) {
 // create a new limiter vector
	TApVar_vec_limiter * pV;
	 
	pV = malloc(sizeof(TApVar_vec_limiter));
	if (!pV) {
	    return NULL;
	}
	// create the elements for limiter
	pV->pFE = malloc(sizeof(TApVar_ele_limiter)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_14_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for limiter
	TApVar_vec_limiter * pV =(TApVar_vec_limiter *) pVarData;
	TApVar_ele_limiter * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_14_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_14_delete ( void * pVarData ) {
 // frees a limiter vector
	TApVar_vec_limiter * pV = (TApVar_vec_limiter *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for delay (varID=20)
// ===============================

// element structure for delay
typedef struct SApVar_ele_delay {
} TApVar_ele_delay;

// vector structure for delay
typedef struct SApVar_vec_delay {
    TApVar_ele_delay * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_delay;


// updates a variable the AP
int HALimpl_20_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for delay
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_delay * pV =(TApVar_vec_delay *) pVarData;
	TApVar_ele_delay * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a delay vector
		TApVar_vec_delay * pV = (TApVar_vec_delay *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for delay
		pV->pFE = malloc(sizeof(TApVar_ele_delay)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_20_create ( unsigned int numberOfElements ) {
 // create a new delay vector
	TApVar_vec_delay * pV;
	 
	pV = malloc(sizeof(TApVar_vec_delay));
	if (!pV) {
	    return NULL;
	}
	// create the elements for delay
	pV->pFE = malloc(sizeof(TApVar_ele_delay)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_20_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for delay
	TApVar_vec_delay * pV =(TApVar_vec_delay *) pVarData;
	TApVar_ele_delay * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_20_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_20_delete ( void * pVarData ) {
 // frees a delay vector
	TApVar_vec_delay * pV = (TApVar_vec_delay *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for FFT (varID=30)
// ===============================

// element structure for FFT
typedef struct SApVar_ele_FFT {
	int32_t N;//number of samples
} TApVar_ele_FFT;

// vector structure for FFT
typedef struct SApVar_vec_FFT {
    TApVar_ele_FFT * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_FFT;


// updates a variable the AP
int HALimpl_30_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for FFT
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_FFT * pV =(TApVar_vec_FFT *) pVarData;
	TApVar_ele_FFT * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a FFT vector
		TApVar_vec_FFT * pV = (TApVar_vec_FFT *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for FFT
		pV->pFE = malloc(sizeof(TApVar_ele_FFT)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx N
		APendianConversation32Bit(pD,eAP_littleEndian);
		pE->N=*((int32_t *)pD);
		pD++;
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_30_create ( unsigned int numberOfElements ) {
 // create a new FFT vector
	TApVar_vec_FFT * pV;
	 
	pV = malloc(sizeof(TApVar_vec_FFT));
	if (!pV) {
	    return NULL;
	}
	// create the elements for FFT
	pV->pFE = malloc(sizeof(TApVar_ele_FFT)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_30_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for FFT
	TApVar_vec_FFT * pV =(TApVar_vec_FFT *) pVarData;
	TApVar_ele_FFT * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 1;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendInteger32(pMD,1,&pE->N);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_30_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_30_delete ( void * pVarData ) {
 TApVar_ele_FFT * pE;
	int32_t i;// frees a FFT vector
	TApVar_vec_FFT * pV = (TApVar_vec_FFT *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for sixxx (varID=66)
// ===============================

// element structure for sixxx
typedef struct SApVar_ele_sixxx {
	float * pA_dataL;// the data list (array)
	int32_t num_dataL;// amount of dataL elements
	float keffi;//koefficent
	int32_t indx;//index
	int32_t * pA_array2;// array nummero 2 (array)
	int32_t num_array2;// amount of array2 elements
} TApVar_ele_sixxx;

// vector structure for sixxx
typedef struct SApVar_vec_sixxx {
    TApVar_ele_sixxx * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_sixxx;


// updates a variable the AP
int HALimpl_66_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for sixxx
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_sixxx * pV =(TApVar_vec_sixxx *) pVarData;
	TApVar_ele_sixxx * pE;
	int i, imax;
	int32_t n, nmax;
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a sixxx vector
		TApVar_vec_sixxx * pV = (TApVar_vec_sixxx *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        // go over every element and delete the array paramters
				pE = pV->pFE;
				for (i=0; i<pV->num;i++) { 
					// delete parameter dataL
					if (pE->pA_dataL) {
					    free(pE->pA_dataL);
					    pE->pA_dataL=NULL;
					    pE->num_dataL=0;
					}
					
					
					// delete parameter array2
					if (pE->pA_array2) {
					    free(pE->pA_array2);
					    pE->pA_array2=NULL;
					    pE->num_array2=0;
					}
				    pE++;
				}
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for sixxx
		pV->pFE = malloc(sizeof(TApVar_ele_sixxx)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    // rx dataL
		APendianConversation32Bit(pD,eAP_littleEndian);
		nmax = *((int32_t *) pD);
		// resize parameter
		if (nmax != pE->num_dataL) {
		    if (pE->pA_dataL) free(pE->pA_dataL);
		    pE->pA_dataL = malloc(sizeof(float)*nmax);
		    if (!pE->pA_dataL) return -2;
		    pE->num_dataL = nmax;
		}
		
		pD++;
		for (n = 0; n < pE->num_dataL; n++) {
		    // no endian conversation
		    pE->pA_dataL[n]=*((float *)pD);
		    pD++;
		}
		// rx keffi
		// no endian conversation
		pE->keffi=*((float *)pD);
		pD++;
		// rx indx
		APendianConversation32Bit(pD,eAP_littleEndian);
		pE->indx=*((int32_t *)pD);
		pD++;
		// rx array2
		APendianConversation32Bit(pD,eAP_littleEndian);
		nmax = *((int32_t *) pD);
		// resize parameter
		if (nmax != pE->num_array2) {
		    if (pE->pA_array2) free(pE->pA_array2);
		    pE->pA_array2 = malloc(sizeof(int32_t)*nmax);
		    if (!pE->pA_array2) return -2;
		    pE->num_array2 = nmax;
		}
		
		pD++;
		for (n = 0; n < pE->num_array2; n++) {
		    APendianConversation32Bit(pD,eAP_littleEndian);
		    pE->pA_array2[n]=*((int32_t *)pD);
		    pD++;
		}
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_66_create ( unsigned int numberOfElements ) {
 // create a new sixxx vector
	TApVar_vec_sixxx * pV;
	 
	pV = malloc(sizeof(TApVar_vec_sixxx));
	if (!pV) {
	    return NULL;
	}
	// create the elements for sixxx
	pV->pFE = malloc(sizeof(TApVar_ele_sixxx)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_66_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for sixxx
	TApVar_vec_sixxx * pV =(TApVar_vec_sixxx *) pVarData;
	TApVar_ele_sixxx * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 4;
	// calc amount of elements from the params
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    dataAmount += pE->num_dataL+pE->num_array2;
	}
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    pMD->pfkt_sendInteger32(pMD,1,&pE->num_dataL);
		pMD->pfkt_sendFloat32(pMD,pE->num_dataL,pE->pA_dataL);
		pMD->pfkt_sendFloat32(pMD,1,&pE->keffi);
		pMD->pfkt_sendInteger32(pMD,1,&pE->indx);
		pMD->pfkt_sendInteger32(pMD,1,&pE->num_array2);
		pMD->pfkt_sendInteger32(pMD,pE->num_array2,pE->pA_array2);
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_66_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_66_delete ( void * pVarData ) {
 TApVar_ele_sixxx * pE;
	int32_t i;// frees a sixxx vector
	TApVar_vec_sixxx * pV = (TApVar_vec_sixxx *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        // go over every element and delete the array paramters
			pE = pV->pFE;
			for (i=0; i<pV->num;i++) { 
				// delete parameter dataL
				if (pE->pA_dataL) {
				    free(pE->pA_dataL);
				    pE->pA_dataL=NULL;
				    pE->num_dataL=0;
				}
				
				
				// delete parameter array2
				if (pE->pA_array2) {
				    free(pE->pA_array2);
				    pE->pA_array2=NULL;
				    pE->num_array2=0;
				}
			    pE++;
			}
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for panel (varID=100)
// ===============================

// element structure for panel
typedef struct SApVar_ele_panel {
} TApVar_ele_panel;

// vector structure for panel
typedef struct SApVar_vec_panel {
    TApVar_ele_panel * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_panel;


// updates a variable the AP
int HALimpl_100_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for panel
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_panel * pV =(TApVar_vec_panel *) pVarData;
	TApVar_ele_panel * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a panel vector
		TApVar_vec_panel * pV = (TApVar_vec_panel *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for panel
		pV->pFE = malloc(sizeof(TApVar_ele_panel)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_100_create ( unsigned int numberOfElements ) {
 // create a new panel vector
	TApVar_vec_panel * pV;
	 
	pV = malloc(sizeof(TApVar_vec_panel));
	if (!pV) {
	    return NULL;
	}
	// create the elements for panel
	pV->pFE = malloc(sizeof(TApVar_ele_panel)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_100_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for panel
	TApVar_vec_panel * pV =(TApVar_vec_panel *) pVarData;
	TApVar_ele_panel * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_100_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_100_delete ( void * pVarData ) {
 // frees a panel vector
	TApVar_vec_panel * pV = (TApVar_vec_panel *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for button (varID=101)
// ===============================

// element structure for button
typedef struct SApVar_ele_button {
} TApVar_ele_button;

// vector structure for button
typedef struct SApVar_vec_button {
    TApVar_ele_button * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_button;


// updates a variable the AP
int HALimpl_101_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for button
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_button * pV =(TApVar_vec_button *) pVarData;
	TApVar_ele_button * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a button vector
		TApVar_vec_button * pV = (TApVar_vec_button *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for button
		pV->pFE = malloc(sizeof(TApVar_ele_button)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_101_create ( unsigned int numberOfElements ) {
 // create a new button vector
	TApVar_vec_button * pV;
	 
	pV = malloc(sizeof(TApVar_vec_button));
	if (!pV) {
	    return NULL;
	}
	// create the elements for button
	pV->pFE = malloc(sizeof(TApVar_ele_button)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_101_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for button
	TApVar_vec_button * pV =(TApVar_vec_button *) pVarData;
	TApVar_ele_button * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_101_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_101_delete ( void * pVarData ) {
 // frees a button vector
	TApVar_vec_button * pV = (TApVar_vec_button *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for led (varID=102)
// ===============================

// element structure for led
typedef struct SApVar_ele_led {
} TApVar_ele_led;

// vector structure for led
typedef struct SApVar_vec_led {
    TApVar_ele_led * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_led;


// updates a variable the AP
int HALimpl_102_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for led
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_led * pV =(TApVar_vec_led *) pVarData;
	TApVar_ele_led * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a led vector
		TApVar_vec_led * pV = (TApVar_vec_led *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for led
		pV->pFE = malloc(sizeof(TApVar_ele_led)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_102_create ( unsigned int numberOfElements ) {
 // create a new led vector
	TApVar_vec_led * pV;
	 
	pV = malloc(sizeof(TApVar_vec_led));
	if (!pV) {
	    return NULL;
	}
	// create the elements for led
	pV->pFE = malloc(sizeof(TApVar_ele_led)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_102_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for led
	TApVar_vec_led * pV =(TApVar_vec_led *) pVarData;
	TApVar_ele_led * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_102_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_102_delete ( void * pVarData ) {
 // frees a led vector
	TApVar_vec_led * pV = (TApVar_vec_led *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}
// ===============================
// variable implementation for display (varID=103)
// ===============================

// element structure for display
typedef struct SApVar_ele_display {
} TApVar_ele_display;

// vector structure for display
typedef struct SApVar_vec_display {
    TApVar_ele_display * pFE; // first element at the vector
    int32_t num; // amount of elements at the vector
} TApVar_vec_display;


// updates a variable the AP
int HALimpl_103_recvUpdate ( void * pVarData, void * pMsgData ) {
 // rx function for display
	uint32_t * pD = (uint32_t *) pMsgData;
	TApVar_vec_display * pV =(TApVar_vec_display *) pVarData;
	TApVar_ele_display * pE;
	int i, imax;
	
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
	    // frees a display vector
		TApVar_vec_display * pV = (TApVar_vec_display *) pVarData;
		
		if (pV) {
		    if (pV->pFE) {
		        
		        free(pV->pFE);
		        pV->pFE = NULL;
		        pV->num = 0;
		    }
		}
	    // create the elements for display
		pV->pFE = malloc(sizeof(TApVar_ele_display)*imax);
		if (!pV->pFE) {
		    free(pV);
		    return -1;
		}
		pV->num = imax;
	}
	
	// 2. fill parameters
	pE = pV->pFE;
	
	for (i = 0; i < imax; i++) {
	    
	    // goto next element
	    pE++;
	}
	return 0; 
}
// create a new variable
void * HALimpl_103_create ( unsigned int numberOfElements ) {
 // create a new display vector
	TApVar_vec_display * pV;
	 
	pV = malloc(sizeof(TApVar_vec_display));
	if (!pV) {
	    return NULL;
	}
	// create the elements for display
	pV->pFE = malloc(sizeof(TApVar_ele_display)*numberOfElements);
	if (!pV->pFE) {
	    free(pV);
	    return NULL;
	}
	pV->num = numberOfElements;
	return pV; 
}
// updates the vars at the other APs
int HALimpl_103_sendUpdate ( void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i ) {
  // tx function for display
	TApVar_vec_display * pV =(TApVar_vec_display *) pVarData;
	TApVar_ele_display * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	
	int32_t dataAmount;
	int32_t n;
	
	// calc ammount of transmission bytes 
	dataAmount = (int32_t) 1 + pV->num * 0;
	
	    
	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	        
	// 2 send vector elementwise
	
	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);
	
	// 2.2 send element
	pE = pV->pFE;
	for (n = 0; n < pV->num; n++) {
	    
	    // inc
	    pE++;
	}
	return 0; 
}
// decode data for the HAL functions
void * HALimpl_103_decodeData ( void * pVarData ) {
 return NULL; 
}
// delete the variable
void HALimpl_103_delete ( void * pVarData ) {
 // frees a display vector
	TApVar_vec_display * pV = (TApVar_vec_display *) pVarData;
	
	if (pV) {
	    if (pV->pFE) {
	        
	        free(pV->pFE);
	        }
	    free(pV);
	} 
}

// global HAL variable info variables
const THAL_Variable const gHALvariableInfo [] = {
    // HAL variable info for rational (1)
	{
	    1,
	    HALimpl_1_recvUpdate,
		HALimpl_1_create,
		HALimpl_1_sendUpdate,
		HALimpl_1_decodeData,
		HALimpl_1_delete
	},
	// HAL variable info for integer (2)
	{
	    2,
	    HALimpl_2_recvUpdate,
		HALimpl_2_create,
		HALimpl_2_sendUpdate,
		HALimpl_2_decodeData,
		HALimpl_2_delete
	},
	// HAL variable info for string (3)
	{
	    3,
	    HALimpl_3_recvUpdate,
		HALimpl_3_create,
		HALimpl_3_sendUpdate,
		HALimpl_3_decodeData,
		HALimpl_3_delete
	},
	// HAL variable info for complex (4)
	{
	    4,
	    HALimpl_4_recvUpdate,
		HALimpl_4_create,
		HALimpl_4_sendUpdate,
		HALimpl_4_decodeData,
		HALimpl_4_delete
	},
	// HAL variable info for biquad (10)
	{
	    10,
	    HALimpl_10_recvUpdate,
		HALimpl_10_create,
		HALimpl_10_sendUpdate,
		HALimpl_10_decodeData,
		HALimpl_10_delete
	},
	// HAL variable info for noisegate (11)
	{
	    11,
	    HALimpl_11_recvUpdate,
		HALimpl_11_create,
		HALimpl_11_sendUpdate,
		HALimpl_11_decodeData,
		HALimpl_11_delete
	},
	// HAL variable info for expander (12)
	{
	    12,
	    HALimpl_12_recvUpdate,
		HALimpl_12_create,
		HALimpl_12_sendUpdate,
		HALimpl_12_decodeData,
		HALimpl_12_delete
	},
	// HAL variable info for compressor (13)
	{
	    13,
	    HALimpl_13_recvUpdate,
		HALimpl_13_create,
		HALimpl_13_sendUpdate,
		HALimpl_13_decodeData,
		HALimpl_13_delete
	},
	// HAL variable info for limiter (14)
	{
	    14,
	    HALimpl_14_recvUpdate,
		HALimpl_14_create,
		HALimpl_14_sendUpdate,
		HALimpl_14_decodeData,
		HALimpl_14_delete
	},
	// HAL variable info for delay (20)
	{
	    20,
	    HALimpl_20_recvUpdate,
		HALimpl_20_create,
		HALimpl_20_sendUpdate,
		HALimpl_20_decodeData,
		HALimpl_20_delete
	},
	// HAL variable info for FFT (30)
	{
	    30,
	    HALimpl_30_recvUpdate,
		HALimpl_30_create,
		HALimpl_30_sendUpdate,
		HALimpl_30_decodeData,
		HALimpl_30_delete
	},
	// HAL variable info for sixxx (66)
	{
	    66,
	    HALimpl_66_recvUpdate,
		HALimpl_66_create,
		HALimpl_66_sendUpdate,
		HALimpl_66_decodeData,
		HALimpl_66_delete
	},
	// HAL variable info for panel (100)
	{
	    100,
	    HALimpl_100_recvUpdate,
		HALimpl_100_create,
		HALimpl_100_sendUpdate,
		HALimpl_100_decodeData,
		HALimpl_100_delete
	},
	// HAL variable info for button (101)
	{
	    101,
	    HALimpl_101_recvUpdate,
		HALimpl_101_create,
		HALimpl_101_sendUpdate,
		HALimpl_101_decodeData,
		HALimpl_101_delete
	},
	// HAL variable info for led (102)
	{
	    102,
	    HALimpl_102_recvUpdate,
		HALimpl_102_create,
		HALimpl_102_sendUpdate,
		HALimpl_102_decodeData,
		HALimpl_102_delete
	},
	// HAL variable info for display (103)
	{
	    103,
	    HALimpl_103_recvUpdate,
		HALimpl_103_create,
		HALimpl_103_sendUpdate,
		HALimpl_103_decodeData,
		HALimpl_103_delete
	}
};

const THAL_VariableList const gHALVariableList = {gHALvariableInfo,16};


// ===============================
// HAL functions
// ===============================

// the function info vector 
const THALFunction const gpFunctionInfoVector [] = {
    
};
// the global HAL function info variable
const THALFunctionList gHALFunctionList = {gpFunctionInfoVector,0};



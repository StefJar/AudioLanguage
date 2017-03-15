@headerComment

#ifndef __AP_HEADER__H__
#define __AP_HEADER__H__

#ifdef __cplusplus
extern "C"
{
#endif


#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// ===============================
// basic io types
// ===============================

// define endian constants
enum eAPendianType {
	eAP_littleEndian	= 'l',
	eAP_bigEndian		= 'b'
};

// convert endianness
void APendianConversation32Bit (
		uint32_t * 	pD,				//!< pointer to the data array
		int			srcEndianess	//!< endianness of the data
	);

// a global variable holding the endianness of the architecture
extern int gAPendianFlag;


// basic io type
typedef struct SHAL_basicIO {
	int	const id;				// the id of the basic type
	int	const size;				// the size in bytes of the basic type
	int	const endianMatterFlag;	// if != 0 the endianness matters
} THAL_basicIO;

// define the global variable containing the basic types
// define the structure for the list
typedef struct SHAL_basicIOList {
	const THAL_basicIO *	pL;		// a pointer to a constant array filled with the type informations
	int const				number;	// the amount of elements at the array
} THAL_basicIOList;

// declare the basic IO type list variable
extern THAL_basicIOList const gHALbasicIOtypeList;
// ===============================
// HAL variable interface
// ===============================

// the variable
typedef struct SHAL_Variable {
	// 1.) id
	int	const 						id;		//id of the variable
	// 2.) function pointers
	@VarFunctions
} THAL_Variable;

typedef struct SHAL_VariableList {
	const THAL_Variable  *	pL;		// a reference to the array of the variables
	int const				number;	// number of elements at the array
} THAL_VariableList;

// declare the variable list variable
extern THAL_VariableList const gHALVariableList;

// ===============================
// MMU interface
// ===============================

// the MMU basic data structure
typedef void * TAPMMU;
// the MMU memmory data structure
typedef void * TAPMMUmemmory;

// function prototype for the creation of a mmu
extern TAPMMU AP_MMU_create (size_t elementsNumber);
// function prototype for destroying of the mmu
extern void AP_MMU_delete (TAPMMU mmu);
// function prototype for getting memmory from the mmu
extern TAPMMUmemmory AP_MMU_get (TAPMMU mmu, size_t elements);
// function prototype for free memmory from the mmu
extern void AP_MMU_free (TAPMMU mmu, TAPMMUmemmory memory);
// function prototype for getting access to the MMU data
extern void * AP_MMU_getData (TAPMMUmemmory memory);
// ===============================
// message driver
// ===============================

@msgDrvDeclaration

// ===============================
// message system
// ===============================


// a type for the id of the node/sender/receiver
typedef uint32_t TAPNodeID;

#define dAPNodeID_ALL (0)

#define dAPmsgNumberNext (0)

// a type for the message
typedef uint32_t TAPMessageID;

// define message data type
typedef struct SHALMsgData {
	const THAL_basicIO *	pBT;			// reference to the basic type
	const int				isArrayFlag;	// if not 0 the data is an array
} THALMsgData;

// define message data type list
typedef struct SHALMsgDataList {
	const THALMsgData *	pL;		// reference list
	const int			number;	// amount of elements at the list
} THALMsgDataList;

// define message type
typedef struct SHALMsgType {
	const TAPMessageID			msgID;		// the id of the message
	const THALMsgDataList	dataDescr;	// list with the data description
} THALMsgType;

// define message type list
typedef struct SHALMsgTypeList {
	const THALMsgType *	pL;		// reference to the list
	const int			number;	// number of elements at the list
} THALMsgTypeList;

// define Msg type description
extern const THALMsgTypeList gHALMsgTypeList;

// message layout
// |sender|receiver|msgTypeID|length|
// enumeration with the positions of the data at the message header
enum eAPMsgHeaderPositions {
	eAPMsgHeaderPosition_endian					=	0,
	eAPMsgHeaderPosition_sender					=	1,
	eAPMsgHeaderPosition_receiver				=	2,
	eAPMsgHeaderPosition_msgTypeID				=	3,
	eAPMsgHeaderPosition_msgNumber				=	4,
	eAPMsgHeaderPosition_length					=	5,
	eAPMsgHeaderPosition_headerElementNumber	=	6
};

// the msg header type
typedef uint32_t TAPMsgHeader [eAPMsgHeaderPosition_headerElementNumber];

typedef struct SAPMsgExtraData {
	const TAPMsgDrv  * pDrv;
} TAPMsgExtraData;

typedef struct SAPMsg {
	struct SAPMsg * 	pNext;
	TAPMsgExtraData		extraData;
	TAPMsgHeader *		pH;
	void *				pData;
	TAPMMUmemmory 		memory;
} TAPMsg;

// a type for the message system
typedef void * TAPMsgSystem;

#define dAPGetMsgMemmoryElementNumber(x) (eAPMsgHeaderPosition_headerElementNumber + (sizeof(TAPMsg)/sizeof(uint32_t)+1)+x)

// create AP message system
TAPMsgSystem APMScreate (
		TAPMMU				mmu,			// the mmu
		int					sysEndianness	// the system endianness
	);

// deletes the message system
void APMSdelete (
	TAPMsgSystem ms
	);

// ========================================
// the receive state machine
// ========================================

// the receive state machine state function
typedef int (* TpfktAPReceiveStatefunction) (
		void *			pVoidSM,		// pointer to the statemachine
		uint32_t * 		pD,				// pointer to the data
		int				number			// the number of data elements
	);

// a type for the statemachine
typedef struct SAPReceiveStateMachine {
	TpfktAPReceiveStatefunction		state;			// the state
	TAPMsgSystem					pMS;			// the message system
	const TAPMsgDrv  *				pDrv;			// the driver associated with the statemachine
	// helper
	TAPMsgHeader					header;
	int								elementsLeft;	// the amount of bytes left to copy
	uint32_t *						pD;				// a data pointer
	// data
	TAPMsg *						pMsg;			// the header and msg
} TAPReceiveStateMachine;

// inits the state machine
void APInitReceiveStateMachine (
		TAPReceiveStateMachine * 			pSM,	// pointer to the state machine
		TAPMsgSystem						pMS,	// pointer to the message system
		const TAPMsgDrv  *					pDrv	// the driver associated with the statemachine
	);

// ===============================
// interpreter interface
// ===============================

// define the maximum of parameter count of a function

@functionParamClasses

@IPmaxParams

// define the maximum of variable parameters (typeID, number)
#define dAPInterpreterVariableMaxParams (2)


// the basic type of the interpreter
typedef void * TAPInterpreter;

// enumeration with the states of the interpreter
enum eAPInterpreterStates {
	eAPInterpreterState_idle			= 0,
	eAPInterpreterState_loadProgramm	= 1,
	eAPInterpreterState_run				= 2,
	eAPInterpreterState_oneStep			= 3,
	eAPInterpreterState_halt			= 4,
	eAPInterpreterState_exit			= 5
	};

// the definition for the interpreter variable
typedef struct SAPInterpreterVariable {
	const THAL_Variable *	pVI;	//the pointer to the variable interface
	void *					pData;	//reference to the variables data
} TAPInterpreterVariable;

@funcParamType

// a type for the HAL functions
typedef void (* TpfktHALfunction) (void * pIPcpu, TuAPInterpreterFunctionParameter * pParams);

// the HAL function parameter type
typedef struct SHALFunctionParam {
	const int 	paramClass;		// the class of the parameter
	const int 	paramTypeID;	// the type id of the parameter
} THALFunctionParam;

// the HAL function parameter list
typedef struct SHALFunctionParamList {
	const THALFunctionParam *	pL;			// the list
	int const					number;		// number of list elements
} THALFunctionParamList;

// the HAL function definition
typedef struct SHALFunction {
	int	const						fid;		// function id
	THALFunctionParamList const		paramList; 	// a list with the parameters
	TpfktHALfunction const 			pfktHAL;	// the hall function pointer
} THALFunction;

// the HAL function list
typedef struct SHALFunctionList {
	const THALFunction *	pL;			// the list
	int const				number;		// number of list elements
} THALFunctionList;

// the global list with the definitions of the HAL functions and there parameters
extern THALFunctionList const gHALFunctionList;

// the interpreter function call
typedef struct SAPInterpreterFuncCall {
	TpfktHALfunction 					pHALFkt;
	TuAPInterpreterFunctionParameter 	param[dAPInterpreterFuncMaxParams];
} TAPInterpreterFuncCall;

// the interpreter softcore
typedef struct SAPInterpreterCPU {
	TAPInterpreter				IP;			// reference to the AP interpreter
	int 						CF;			// carray flag
	int							EF;			// error flag
	TAPInterpreterFuncCall *	pCodeStart;	// code start
	TAPInterpreterFuncCall *	pCodeEnd;	// code end
	TAPInterpreterFuncCall *	pIP;		// instruction pointer
} TAPInterpreterCPU;


// create a new interpreter
TAPInterpreter APInterpreterCreate (void * pAP);
// cleans the interpreter
void APInterpreterClean (TAPInterpreter IP);
// deletes the interpreter
void APInterpreterDelete (TAPInterpreter IP);
// resets the interpreter
void APInterpreterReset (TAPInterpreter IP);
// process the actual state
int APInterpreterProcessState(TAPInterpreter IP);

// set interpreter state
int APInterpreterSetState (TAPInterpreter IP, int msgEndian, int32_t state);
// get interpreter state
int32_t APInterpreterGetState (TAPInterpreter IP);
// setup the interpreter for a new programm
int APInterpreterInitNewProgramm (TAPInterpreter IP, int msgEndian, int32_t instructionsNumber, int32_t VariableNumber);
// load a variable/~array to an index
int APInterpreterLoadVar (TAPInterpreter IP, int msgEndian, int32_t index, int32_t varTypeID, int32_t numberOfElements);
// load a single Instruction to an index
int APInterpreterLoadInstr (TAPInterpreter IP, int msgEndian, int32_t index, int32_t * pRawInstr);
// gets the varaible by it's index
TAPInterpreterVariable * APInterpreterGetVariableByIndex (TAPInterpreter IP, int index);
// gets the AP from the IP
void * APInterpreterGetAPfromIP (TAPInterpreter IP);
// gets the CPU from the IP
TAPInterpreterCPU * APInterpreterGetCPUref (TAPInterpreter IP);


// ===============================
// AP genric interface
// ===============================

// a node struct for storing node id an driver
typedef struct SAPNode {
	TAPNodeID			nodeID;	// the node id
	const TAPMsgDrv *	pDrv;	// the driver to reach the node
	struct SAPNode *	pNext;	// the next node at the list
} TAPNode;

enum eAPstate {
	eAPstate_idle		= 0,
	eAPstate_halt		= 1,
	eAPstate_run		= 2,
	eAPstate_error		= 3
};

// the AP main struct
typedef struct SAP {
	TAPNodeID			nodeID;			// the node ID of the AP
	TAPNode *			pNodeList;		// the list of connected AP's
	const TAPMsgDrv *	pDrvList;		//an array with all drivers
	int					driverNumber;	//the number of drivers at the list
	TAPMMU				msgSysMMU;		// the MMU for the messagesystem
	TAPInterpreter		IP;				// the code interpreter for the AP
	TAPMsgSystem		MS;				// the message system
	unsigned int		msgNumber;		// the number of the last message
	int					APstate;		// the state of the audio processor
} TAP;

// inits the AP
int APinit (
			TAP *				pAP,
			TAPNodeID			nodeID,
			const TAPMsgDrv *	pDrvList,
			const int			driverNumber,
			size_t				messagePoolSize,
			int					sysEndian
		);

// deletes the AP
void APdelete (TAP * pAP);

// find a node at the list
TAPNode * APfindNode(TAP * pAP, TAPNodeID nodeID);

// adds a new node to the node list
int APaddNode(TAP * pAP, TAPNodeID newNodeID, const TAPMsgDrv * pDrv);

// removes a node from the node list
void APremoveNode(TAP * pAP, TAPNodeID nodeID);

// get a new message number
unsigned int APgetNewMessageNumber (TAP *pAP);

// find the driver associated with der nodeID
const TAPMsgDrv * APfindDrvBySenderID (TAP * pAP, TAPNodeID node);

// wait for an ack
int APwaitAck (TAP * pAP,uint32_t mNumber);

// runs the AP
int APrun(TAP *pAP);

// if a message is in the queue available it will be processed
void APMessageProcess (TAP * pAP);

// ===============================
// message system processes
// ===============================

// function pointer for handleing received messages
typedef int  (* TpfktHALMsgProcessHandler) (TAP * pAP, TAPMsg * pMsg);

// a type for the msg-type id
typedef int THALmsgID;

// a struct representing the association between messageID and handler
typedef struct SHALMsgProcessMessageAssociation{
	const THALmsgID					msgID;		// the message id
	const TpfktHALMsgProcessHandler	pfktHandle;	// function to handle the message
} THALMsgProcessMessageAssociation;

// a list struct for handling messages
typedef struct SHALMsgProcessHandlerList{
	const THALMsgProcessMessageAssociation *	pL;		// pointer to an array holding the handlers
	const int									number;	// amount of messagehandlers
} HALMsgProcessHandlerList;

// a global variable holding all RX message proccess
extern const HALMsgProcessHandlerList gHALMsgProcessRXHandlers;

@messagedriverHelper


@debugInterface

#ifdef __cplusplus
}
#endif


#endif

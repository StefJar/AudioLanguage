@headerInfo

//#include "AP.h"
//#include <string.h>

@extraIncludes


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

@basictypesImplementation

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

@RawParamDataConverter

// ===============================
// extra code from the groups
// ===============================

@ExtraGroupCode

// ===============================
// message types
// ===============================

@MsgTypeEnum

// ===============================
// message driver
// ===============================

@messageDriver

// ===============================
// message processes
// ===============================

@messageProcesses

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

@APimplemention

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

@varImplmentation

// ===============================
// HAL functions
// ===============================

@functionImplementaion


@debugInterface

/*
 /*
 * main template
 *
 *  Created on: 10.08.2011
 *      Author: StJ
 *      changed: 07.03.2012
 */

#ifdef __cplusplus
using namespace std;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "AP.h"

// some basic file defines
// #define dAPuseFileIO
//#define dAPuseExternalAPCode

#ifdef dAPuseFileIO
// ==================================
// file IO
// ==================================

// endian check
int is_big_endian(void) {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

// loads the alc from a file
int loadALCfromFile (const char * szFilname,int * pEndianness, int32_t *pVarcount, int32_t * pInstrCount, int32_t ** ppVarList, int32_t ** ppInstructions) {
	FILE *		f;
	int32_t		instrSize;

	*ppInstructions = NULL;
	*ppVarList = NULL;
	*pVarcount = 0;
	*pInstrCount = 0;

	f = fopen (szFilname,"rb");

	if (!f) return -1;

	uint8_t	idField[4];
	uint8_t endian, sysEndian;;

	if (1 != fread (&idField,sizeof(int8_t)*4,1,f)) goto error;
	if (1 != fread (&endian,sizeof(int8_t),1,f)) goto error;

	if (1 != fread (pVarcount,sizeof(int32_t),1,f)) goto error;
	if (1 != fread (pInstrCount,sizeof(int32_t),1,f)) goto error;
	if (1 != fread (&instrSize,sizeof(int32_t),1,f)) goto error;


	if (!is_big_endian()) sysEndian = eAP_littleEndian;
		else sysEndian = eAP_bigEndian;
	if (endian != sysEndian) {
		APendianConversation32Bit((uint32_t *)pVarcount);
		APendianConversation32Bit((uint32_t *)pInstrCount);
		APendianConversation32Bit((uint32_t *)&instrSize);
	}

	// check if the size of the instructions saved at the file is equal to the of the engine
	if (((instrSize)-1) != dAPInterpreterFuncMaxParams) {
		goto error;
	}


	*ppVarList = malloc ((sizeof(int32_t)*(dAPInterpreterVariableMaxParams))*(*pVarcount));
	if (!*ppVarList) goto error;

	*ppInstructions = malloc (sizeof(int32_t)*(dAPInterpreterFuncMaxParams+1) *(*pInstrCount));
	if (!*ppInstructions) goto error;

	if (*pVarcount != fread (*ppVarList,sizeof(int32_t)*(dAPInterpreterVariableMaxParams),*pVarcount,f)) goto error;

	if (*pInstrCount != fread (*ppInstructions,sizeof(int32_t)*(dAPInterpreterFuncMaxParams+1),*pInstrCount,f)) goto error;

	fclose (f);

	*pEndianness = endian;
	return 0;

error:
	fclose (f);
	if (*ppInstructions) {
		free (*ppInstructions);
		*ppInstructions = NULL;
	}

	if (*ppVarList) {
		free (*ppVarList);
		*ppVarList = NULL;
	}
	*pVarcount = 0;
	*pInstrCount = 0;
	*pEndianness = 0;
	return -2;
}

// loads the ALC - stored in memory - into the AP
int loadProgrammToTheAP (
		TAPInterpreter	IP,
		int				endianness,
		int32_t 		varCount,
		int32_t			instrCount,
		int32_t *		pVarList,
		int32_t *		pInstructions
		) {
	APInterpreterClean (IP);
	APInterpreterSetState (IP,endianness,eAPInterpreterState_loadProgramm);
	APInterpreterInitNewProgramm (IP,endianness,instrCount,varCount);

	int32_t vc = varCount;
	int32_t ic = instrCount;
	int sysEndian;
	if (!is_big_endian()) sysEndian = eAP_littleEndian;
		else sysEndian = eAP_bigEndian;
	if (endianness != sysEndian) {
		APendianConversation32Bit((uint32_t *)&vc);
		APendianConversation32Bit((uint32_t *)&ic);
	}

	int32_t i;
	typedef int32_t TBinVarData[2];
	TBinVarData * pV = (TBinVarData *) pVarList;
	for (i = 0; i < vc;i++) {
		if (APInterpreterLoadVar (IP,endianness,i,(*pV)[0],(*pV)[1])) return -10;
		pV++;
	}
	int32_t * pInstr = pInstructions;
	for (i = 0; i < ic;i++) {
		if (APInterpreterLoadInstr (IP,endianness,i,pInstr)) return -20;
		pInstr += (dAPInterpreterFuncMaxParams + 1);
	}
	return 0;
}
#endif // of dAPuseFileIO


#ifdef dAPuseExternalAPCode

#include external Header of the code dump

// loads the ALC - stored in memory - into the AP
int loadProgrammToTheAP (TAP * pAP) {
	if (dALCdumpInstrSize != (dAPInterpreterFuncMaxParams + 1)) return -1;

	APInterpreterClean (pAP->IP);
	APInterpreterSetState (pAP->IP,gAPendianFlag,eAPInterpreterState_loadProgramm);
	APInterpreterInitNewProgramm (pAP->IP,gAPendianFlag,dALCdumpInstrCount,dALCdumpVarCount);

	int32_t i;
	for (i = 0; i < dALCdumpVarCount;i++) {
		if (APInterpreterLoadVar (pAP->IP,gAPendianFlag,i,gALCvars[i].type,gALCvars[i].amount)) return -100-i;
	}

	// if the values at the flash or rom we need to make a copy at the RAM to use the AP API functions
	for (i = 0; i < dALCdumpInstrCount;i++) {
		// load instruction
		if (APInterpreterLoadInstr (pAP->IP,gAPendianFlag,i,(int32_t *) &gcInstructions[i])) return -1000-i;
	}
	return 0;
}


#endif


TAP AP;

#ifdef dWithDebugInterface
// ======================
// debug functions
// ======================

// finds a function name by the function call
const char * getFuncName (TAPInterpreterFuncCall * pFC) {
	// first get the fid
	const THALFunction * pHF = gHALFunctionList.pL;
	const TAPFuncDebugInfo * pDI = gDebugInfo_HALFunctionList.pFI;
	int i;
	for (i = 0; i< gHALFunctionList.number; i++) {
		if (pHF->pfktHAL == pFC->pHALFkt) goto findName;
		pHF++;
	}
	return NULL;
findName:
	for (i = 0; i< gDebugInfo_HALFunctionList.num; i++) {
		if (pHF->fid == pDI->fid) {
			return pDI->szName;
		}
		pDI++;
	}
	return NULL;
}

void printCode() {
	TAPInterpreterCPU * pCPU = APInterpreterGetCPUref(AP.IP);
	TAPInterpreterFuncCall * pFC = pCPU->pCodeStart;
	const char * szFname;
	while (pFC < pCPU->pCodeEnd) {
		if (pCPU->pIP == pFC) {
			printf (">\t");
		} else {
			printf ("\t");
		}
		szFname = getFuncName(pFC);
		if (szFname) {
			printf(szFname);
		} else {
			printf("unknown function");
		}
		printf("\n");
		pFC++;
	}
	fflush(stdout);
}

#endif

void ui () {
	TAPNode * pN;

	for (;;) {
		printf("command: ");
		fflush(stdout);
		switch (tolower(getc(stdin))) {
			case 'x':
				APInterpreterSetState (AP.IP,eAP_littleEndian,eAPInterpreterState_halt);
				break;
			case 'e':
				APInterpreterSetState (AP.IP,eAP_littleEndian,eAPInterpreterState_exit);
				return;
			case 'r' :
				APInterpreterSetState (AP.IP,eAP_littleEndian,eAPInterpreterState_run);
				break;
			case 's':
				APInterpreterSetState (AP.IP,eAP_littleEndian,eAPInterpreterState_oneStep);
				break;
			case 'c':
				printf("code:\n");
#ifdef dWithDebugInterface
				printCode();
#else
				printf("debug is disabled");
#endif
				break;
			case 'p':
				printf("own node id: %i\nnode list:\n", (int) AP.nodeID);
				pN = AP.pNodeList;
				while(pN) {
					printf("%i\n", (int)pN->nodeID);
					pN = pN->pNext;
				}
				break;
			case 'h':
				printf("commands:\nx-halt\nr-run\ns-step\nc-show code\np-show nodes\ne-exit");
				break;
		}
		printf("\n");
		fflush(stdout);
	}
}

void * APIPthread(void * pArgs) {
	int rc;
	while (APInterpreterGetState(AP.IP) != eAPInterpreterState_exit) {
		rc = APInterpreterProcessState(AP.IP);
		if (rc != 0) {
			fprintf(stdout,"\ninterpreter processing ended with code=%i",rc);
#ifdef dWithDebugInterface
			fprintf(stdout,"\nCPU registers:\n");
			printCPUregisters();
#endif
			fflush(stdout);
		}
		usleep(0);
	}
	return NULL;
}

void * APMSthread (void * pArgs) {
	APMessageProcessingThread (&AP);
	return NULL;
}

extern int drv_6_feedRecvStateM (uint8_t * pData, size_t amount);

int main()
{
	pthread_t		IPthread;
	pthread_t		MSthread;

	enum eMsgDrvIDs {
		eMsgDrvID_TCP = 0,
		eMsgDrvID_amount = 1
	};

	TAPMsgDrv		msgSysDrv[eMsgDrvID_amount];
	int rc;

	// =======================
	// TCP
	// =======================

	if (TCPcontrolInitFromStdIn(drv_6_feedRecvStateM, 4096, 500)) {
		fprintf(stderr, "init TCVP driver failed!\n");
		return EXIT_FAILURE;
	}
	APdriver_6_init (&(msgSysDrv[eMsgDrvID_UPD]));

	// =======================
	srand(time(NULL));

	rc = APinit(&AP,(TAPNodeID)rand(),msgSysDrv,eMsgDrvID_amount,1000,eAP_littleEndian);
	if (rc) {
		fprintf(stderr, "audio processor init failed with error code %i!",rc);
		goto exit;
	}


#ifdef dAPuseFileIO
	int32_t varC;
	int32_t instrC;

	int32_t * varL;
	int32_t * instrL;
	int endian;

	rc = loadALCfromFile ("../APgen/ALASM/crossOver5Way.alc",&endian,&varC,&instrC,&varL,&instrL);
	if (rc) goto exit;
	rc = loadProgrammToTheAP (AP.IP,endian,varC,instrC,varL,instrL);
#endif

#ifdef dAPuseExternalAPCode
	rc = loadProgrammToTheAP (&AP);
#endif

	pthread_create(&IPthread,NULL,&APIPthread,NULL);
	pthread_create(&MSthread,NULL,&APMSthread,NULL);

	if (rc) goto exit;

	ui();

#ifdef dAPuseFileIO
	free (varL);
	free (instrL);
#endif


exit:
	APdelete(&AP);
	stjUDPSocket_close();
	stjUDPSocket_SysClose();

	return EXIT_SUCCESS;
}

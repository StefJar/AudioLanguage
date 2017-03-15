//==================================================
//	AP generator v.0.1 alpha
//	timestamp: 2016-01-13 12:09:16.755000
//==================================================


//#include "AP.h"
//#include <string.h>

#include <stdio.h>
#include <glib.h>
#include "AP.h"
#include <gtk/gtk.h>
#include <winsock2.h>
#include <math.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <ws2tcpip.h>
#include <string.h>
#include <glib-object.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <pango/pango.h>
#include <semaphore.h>


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
// // extra code for group "rational and integer generic"
// ===============================

// ==============================================
// generic vector interface for integer and
// rational types based on the std. C lib
// ==============================================

// ----------------------------------------------
// generic integer type
// ----------------------------------------------

// transforms the integer to a 'unique form'
inline uint32_t APgenericInteger_ToUniform (uint32_t v) {
	uint32_t u;
	u = v & 0xFF;
	u <<= 8;
	v >>= 8;
	u |= (v & 0xFF);
	u <<= 8;
	v >>= 8;
	u |= (v & 0xFF);
	u <<= 8;
	v >>= 8;
	u |= (v & 0xFF);
	return u;
}

// inverse transformation of the unique integer to the 'local form'
inline uint32_t APgenericInteger_FromUniform (uint32_t v) {
	uint32_t u;
	u = v & 0xFF;
	u <<= 8;
	v >>= 8;
	u |= v & 0xFF;
	u <<= 8;
	v >>= 8;
	u |= v & 0xFF;
	u <<= 8;
	v >>= 8;
	u |= v & 0xFF;
	return u;
}



// type for a generic vector based int type
typedef struct SAPgenericIntegerVector {
	int32_t *	pVal;
	int			num;
} TAPgenericIntegerVector;

// create int vector
TAPgenericIntegerVector * APgenericIntegerVector_create (int num) {
	int i;
	// alloc memory
	TAPgenericIntegerVector * pI = malloc (sizeof(TAPgenericIntegerVector));
	if (!pI) return NULL;
	pI->pVal = malloc (sizeof(int32_t)*num);
	if (!pI->pVal) {
		free (pI);
		return NULL;
	}
	pI->num = num;
	// set memory
	for (i = 0; i< num; i++) {
		pI->pVal[i] = 0;
	}
	return pI;
}

// destroy int vector
void APgenericIntegerVector_destroy (TAPgenericIntegerVector * pV) {
	if (pV) {
		free(pV->pVal);
		free(pV);
	}
}

// resize int vector
int APgenericIntegerVector_resize (TAPgenericIntegerVector * pV, int newNum) {
	int i;

	if (pV->num == newNum) return 0;
	free (pV->pVal);
	pV->pVal = malloc (sizeof(int32_t)*newNum);
	if (!pV->pVal) return -1;
	pV->num = newNum;
	// set memory
	for (i = 0; i< newNum; i++) {
		pV->pVal[i] = 0;
	}
	return 0;
}

// assign a = values
int APgenericIntegerVector_assignConst (TAPgenericIntegerVector * pa, int iStart, int num, int32_t * pVals) {
	int i = iStart;
	int imax = i + num;
	int32_t * pD = pa->pVal + iStart;
	if (imax > pa->num) imax = pa->num;

	for (; i < imax; i++) {
		*pD = *pVals;
		pD++;
		pVals++;
	}
	return 0;
}

// assign a = b
int APgenericIntegerVector_assign (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb) {
	int imax = pa->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		for (i = 0; i < imax; i++) {
			pa->pVal[i] = pb->pVal[i];
		}
	} else {
		for (i = 0; i < imax; i++) {
			pa->pVal[i] = pb->pVal[0];
		}
	}
	return 0;
}


// add c = a + b
int APgenericIntegerVector_add (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, TAPgenericIntegerVector * pc) {
	int imax = pc->num;
	int i;

	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise add
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] + pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha + b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] + pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta + a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] + pb->pVal[0];
			}
			return 0;
		}

	}
	return -1;
}

// sub c = a - b
int APgenericIntegerVector_sub (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, TAPgenericIntegerVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise sub
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] - pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha - b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] - pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = a[i] - beta
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] - pb->pVal[0];
			}
			return 0;
		}

	}
	return -1;
}

// mul c = a * b
int APgenericIntegerVector_mul (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, TAPgenericIntegerVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise mul
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] * pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha * b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] * pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta * a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] * pb->pVal[0];
			}
			return 0;
		}

	}
	return -1;
}

// div c = a * b
int APgenericIntegerVector_div (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, TAPgenericIntegerVector * pc) {
	int imax = pc->num;
	int i;

	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise div
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] / pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha / b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] / pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta / a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] / pb->pVal[0];
			}
			return 0;
		}
	}
	return -1;
}

// modulo c = a mod b
int APgenericIntegerVector_mod (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, TAPgenericIntegerVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise mod
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] % pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha % b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] % pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta % a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] % pb->pVal[0];
			}
			return 0;
		}
	}
	return -1;
}

// cmp Element cmp(a[i],b[j]):
//		res = -1: a < b
//		res = 1 : a > b
//		res = 0: a = b
int APgenericIntegerVector_cmpEle (TAPgenericIntegerVector * pa, TAPgenericIntegerVector * pb, int ia, int ib) {
	int zwv = pa->pVal[ia] - pb->pVal[ib];
	if (!zwv) return 0;
	if (zwv < 0) return -1;
	return 1;
}


// ----------------------------------------------
// generic rational type
// ----------------------------------------------

// type for a generic vector based float type
typedef struct SAPgenericRationalVector {
	float *		pVal;
	int			num;
} TAPgenericRationalVector;

// create float vector
TAPgenericRationalVector * APgenericRationalVector_create (int num) {
	int i;
	// alloc memory
	TAPgenericRationalVector * pR = malloc (sizeof(TAPgenericRationalVector));
	if (!pR) return NULL;
	pR->pVal = malloc (sizeof(float)*num);
	if (!pR->pVal) {
		free (pR);
		return NULL;
	}
	pR->num = num;
	// set memory
	for (i = 0; i< num; i++) {
		pR->pVal[i] = 0.f;
	}
	return pR;
}

// destroy float vector
void APgenericRationalVector_destroy (TAPgenericRationalVector * pV) {
	if (pV) {
		free(pV->pVal);
		free(pV);
	}
}

// resize float vector
int APgenericRationalVector_resize (TAPgenericRationalVector * pV, int newNum) {
	int i;

	if (pV->num == newNum) return 0;
	free (pV->pVal);
	pV->pVal = malloc (sizeof(float)*newNum);
	if (!pV->pVal) return -1;
	pV->num = newNum;
	// set memory
	for (i = 0; i< newNum; i++) {
		pV->pVal[i] = 0.f;
	}
	return 0;
}

// assign a = values
int APgenericRationalVector_assignConst (TAPgenericRationalVector * pa, int iStart, int num, float * pVals) {
	int i = iStart;
	int imax = i + num;
	float * pD = pa->pVal + iStart;
	if (imax > pa->num) imax = pa->num;

	for (; i < imax; i++) {
		*pD = *pVals;
		pD++;
		pVals++;
	}
	return 0;
}

// assign a = b
int APgenericRationalVector_assign (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb) {
	int imax = pa->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		for (i = 0; i < imax; i++) {
			pa->pVal[i] = pb->pVal[i];
		}
	} else {
		for (i = 0; i < imax; i++) {
			pa->pVal[i] = pb->pVal[0];
		}
	}
	return 0;
}


// add c = a + b
int APgenericRationalVector_add (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, TAPgenericRationalVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise add
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] + pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha + b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] + pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta + a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] + pb->pVal[0];
			}
			return 0;
		}

	}
	return -1;
}

// sub c = a - b
int APgenericRationalVector_sub (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, TAPgenericRationalVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise sub
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] - pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha - b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] - pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta - a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] - pb->pVal[0];
			}
			return 0;
		}
	}
	return -1;

}

// mul c = a * b
int APgenericRationalVector_mul (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, TAPgenericRationalVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise mul
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] * pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha * b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] * pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta * a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] * pb->pVal[0];
			}
			return 0;
		}
	}
	return -1;
}

// div c = a * b
int APgenericRationalVector_div (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, TAPgenericRationalVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise div
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = pa->pVal[i] / pb->pVal[i];
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha / b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[0] / pb->pVal[i];
			}
			return 0;
		}
		// no -> special case c[i] = beta / a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = pa->pVal[i] / pb->pVal[0];
			}
			return 0;
		}
	}
	return -1;
}

// modulo c = a mod b
int APgenericRationalVector_mod (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, TAPgenericRationalVector * pc) {
	int imax = pc->num;
	int i;
	// check if vectors have the same size
	if (pb->num == imax) {
		// yes do elementwise mod
		for (i = 0; i < imax; i++) {
			pc->pVal[i] = fmodf(pa->pVal[i],pb->pVal[i]);
		}
		return 0;
	} else {
		// no -> special case c[i] = alpha % b[i]
		if (pa->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = fmodf(pa->pVal[0],pb->pVal[i]);
			}
			return 0;
		}
		// no -> special case c[i] = beta % a[i]
		if (pb->num == 1) {
			for (i = 0; i < imax; i++) {
				pc->pVal[i] = fmodf(pa->pVal[i],pb->pVal[0]);
			}
			return 0;
		}

	}
	return -1;
}

// cmp Element cmp(a[i],b[j]):
//		res = -1: a < b
//		res = 1 : a > b
//		res = 0: a = b
int APgenericRationalVector_cmpEle (TAPgenericRationalVector * pa, TAPgenericRationalVector * pb, int ia, int ib) {
	float zwv = pa->pVal[ia] - pb->pVal[ib];
	if (zwv == 0.f) return 0;
	if (zwv < 0.f) return -1;
	return 1;
}

// ===============================
// // extra code for group "AP client interface useing stjSocket and APclient functions"
// ===============================

// ===========================================================
// socket functions to communicate via UDP
// ===========================================================
// written by Stefan Jaritz -> prefix stj
// part I: defines

enum eAdminMsgTypes {
	eAdminMsgType_login 	= 'i',
	eAdminMsgType_logout	= 'o',
	eAdminMsgType_exit		= 'e',
	eAdminMsgType_ack		= 'a',
	eAdminMsgType_nack		= 'n'
};


typedef struct SstjSocket_addr {
	struct sockaddr_in	Addr;
	int					len;
} TstjSocket_addr;


typedef struct SstjSocket_loginMsg {
	uint8_t		msgID;
	uint16_t	uuid;
	uint16_t	dataOutPort;
	uint16_t	dataInPort;
} TstjSocket_loginMsg;

typedef uint8_t TstjSocket_loginRAWmsg [7];

// creates a addinfo struct with the address of the local
struct addrinfo * stjSocket_getLocalSocketAddress (uint16_t port);

// creates a UPD server
int stjSocket_createServer (
		uint16_t 			port,	//!<(in) port
		SOCKET *			pS,		//!<(out) socket
		TstjSocket_addr	*	pAI		//!<(out) address info
	);


// creates a UDP client witch connects to a local server
int stjSocket_createClient (
		uint16_t 			port,	//!<(in) port
		SOCKET *			pS,		//!<(out) socket
		TstjSocket_addr	*	pAI		//!<(out) address info
	);

// closes socket & address
void stjSocket_close (
		SOCKET				S,		//!<(in) socket
		TstjSocket_addr	*	pAI		//!<(in) address info
	);

// sends some data to an address
int stjSocket_send (
		SOCKET	 			S,			//!< socket
		void *				pData,		//!< data to send
		int					dataSize,	//!< amount of bytes
		TstjSocket_addr	*	pAddr		//!< address
	);

// receives some data and filles the address with the sender
int stjSocket_recv (
		SOCKET 				S,			//!< socket
		void *				pData,		//!< data to send
		int					dataSize,	//!< amount of bytes
		TstjSocket_addr	*	pAddr		//!< address
	);

// ===========================================================
// socket functions to communicate via UDP
// ===========================================================
// written by Stefan Jaritz -> prefix stj
// part II: implementation

// defines
#define dMaxHostNameChars (254)

/*
// creates a addinfo struct with the address of the local
struct addrinfo * stjSocket_getLocalSocketAddress (uint16_t port) {
	char 				szPath[dMaxHostNameChars] = "";
	char				szDummyStr[255] = "";
	struct hostent *	pHostInfo;
	struct addrinfo		hints;
	struct addrinfo	*	pAI;

	memset ( &hints, 0,sizeof(hints));
	hints.ai_family = AF_UNSPEC; // IPv4 and IPv6
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0; // any protocol
	hints.ai_flags = 0;

	// resolve hostname
    if (gethostname(szPath,dMaxHostNameChars)) goto mainErrorWithMsg;

	pHostInfo = gethostbyname(szPath);
	if (!pHostInfo) goto mainErrorWithMsg;

	sprintf(szDummyStr,"%u",(unsigned int)port);

	// build address info
	if (getaddrinfo (pHostInfo->h_name,szDummyStr,&hints,&pAI)) {
		fprintf (stderr,"getting address-information of the TCP port failed (error code %s)!\n",gai_strerror(WSAGetLastError()));
		goto mainError;
	}

	return pAI;

mainErrorWithMsg:
	fprintf (stderr, "error: %s\n",gai_strerror(WSAGetLastError()));
mainError:
    return NULL;

}
*/

// creates a UPD server
int stjSocket_createServer (
		uint16_t 			port,	//!<(in) port
		SOCKET *			pS,		//!<(out) socket
		TstjSocket_addr	*	pAI		//!<(out) address info
	) {
	// create socket
	*pS=socket(AF_INET,SOCK_DGRAM,0);
	if (!*pS) goto mainErrorWithMsg;

	// create address
	pAI->Addr.sin_family=AF_INET; // AF_UNSPEC
	pAI->Addr.sin_port=htons(port);
	pAI->Addr.sin_addr.s_addr=ADDR_ANY;
	pAI->len = sizeof(SOCKADDR_IN);

	// bind socket to adress
	if (SOCKET_ERROR == bind(*pS,(SOCKADDR*)&(pAI->Addr),pAI->len)) goto mainErrorWithMsg;
    return 0;
mainErrorWithMsg:
   	printf ("error: %s\n",gai_strerror(WSAGetLastError()));
   	return -1;
}

// creates a UDP client witch connects to a local server
int stjSocket_createClient (
		uint16_t 			port,	//!<(in) port
		SOCKET *			pS,		//!<(out) socket
		TstjSocket_addr	*	pAI		//!<(out) address info
	) {
	char 				szPath[dMaxHostNameChars] = "";
	struct hostent *	pHostInfo;

	// resolve hostname
    if (gethostname(szPath,dMaxHostNameChars)) goto mainErrorWithMsg;

	pHostInfo = gethostbyname(szPath);
	if (!pHostInfo) goto mainErrorWithMsg;

	// create socket
	*pS=socket(AF_INET,SOCK_DGRAM,0);
	if (!*pS) goto mainErrorWithMsg;

	// get the local ip from the host
	char * szLocalIP;
	szLocalIP = inet_ntoa (*(struct in_addr *)*pHostInfo->h_addr_list);

	unsigned long addr = inet_addr(szLocalIP);
	if ((INADDR_NONE == addr) || (INADDR_ANY == addr)) {
		closesocket(*pS);
		printf ("unknown inet address\nerror: %s\n",gai_strerror(WSAGetLastError()));
		return -2;
	}

	// create address
	pAI->Addr.sin_family=AF_INET; // AF_UNSPEC
	pAI->Addr.sin_port=htons(port);
	pAI->Addr.sin_addr.s_addr= addr;
	pAI->len = sizeof(SOCKADDR_IN);

    return 0;
mainErrorWithMsg:
   	printf ("error: %s\n",gai_strerror(WSAGetLastError()));
   	return -1;
}

// closes socket & address
void stjSocket_close (
		SOCKET				S,		//!<(in) socket
		TstjSocket_addr	*	pAI		//!<(in) address info
	) {
	// pAI is self build so we don't need a free call
	//freeaddrinfo(gMsgServer.aiAdmin);
	closesocket(S);
}

// sends some data to an address
int stjSocket_send (
		SOCKET	 			S,			//!< socket
		void *				pData,		//!< data to send
		int					dataSize,	//!< amount of bytes
		TstjSocket_addr	*	pAddr		//!< address
	) {
	int n;
	n = sendto (S, (const char *) pData, dataSize, 0,(struct sockaddr *)&(pAddr->Addr), pAddr->len);
	if (n != dataSize) {
		fprintf (stderr,"sending data failed (%i bytes send)!(error: %s)!\n",n,gai_strerror(WSAGetLastError()));
		return -1;
	}
	return 0;
}

// receives some data and filles the address with the sender
int stjSocket_recv (
		SOCKET 				S,			//!< socket
		void *				pData,		//!< data to send
		int					dataSize,	//!< amount of bytes
		TstjSocket_addr	*	pAddr		//!< address
	) {
	int n;
	n = recvfrom(S, (char *) pData, dataSize, 0,(struct sockaddr *)&(pAddr->Addr), &pAddr->len);
	if (n != dataSize) {
		fprintf (stderr,"receiving data failed (%i bytes received)!(error: %s)!\n",n,gai_strerror(WSAGetLastError()));
		return -1;
	}
	return 0;
}

// ==========================================
// a TCP/IP client running the RX at an
// own thread and use a callback-function
// to sign that some data are received
// ==========================================
// part I: header defines

typedef int (* TpfktAPClientRecvCallback) (void *pUserData, uint16_t number, uint8_t * pData);

typedef struct SAPClient {
	uint16_t					uuid;			//!< uuid of the client

	SOCKET 						sAdmin;			//!< admin socket
	uint16_t	 				adminPort;		//!< admin port
	TstjSocket_addr				aAdmin;			//!< socket address of the admin

	SOCKET						sDataIn;		//!< data in socket
	uint16_t					dataInPort;		//!< port of the data in socket
	TstjSocket_addr				aDataIn;		//!< socket address of the data port

	SOCKET						sDataOut;		//!< data out socket
	uint16_t					dataOutPort;	//!< port of the data out socket
	TstjSocket_addr				aDataOut;		//!< socket address of the data port

	pthread_t					recvThread;		//!< receive thread
	uint8_t	*					recvBuffer;		//!< temporaly receive buffer
	uint16_t					recvBufferSize;	//!< size in bytes of the receive buffer
	void *						pUserData;		//!< user data (can be NULL)
	TpfktAPClientRecvCallback	fktRecvCB;		//!< receive call back funtion
} TAPClient;

// creates an admin client
int APclient_create (
		TAPClient *					pC,					//!<(in/out) pointer to a client structure to be filled
		uint16_t 					adminPort,			//!<(in) the port of the admin server port
		uint16_t					recvBufferSize,		//!<(in) size in bytes of the receive buffer
		void *						pUserData,			//!<(in) user data
		TpfktAPClientRecvCallback	fktCB				//!<(in) callback function when receiving data
	);

//! free's the client
int APclient_close (
		TAPClient *		pC			//!<(in) pointer to a client structure
	);


int APclient_send (
		TAPClient *		pC,			//!<(in) pointer to a client structure
		uint16_t		num,		//!<(in) amount of bytes to send
		uint8_t *		pData		//!<(in) pointer to the data
	);

// ==========================================
// a TCP/IP client running the RX at an
// own thread and use a callback-function
// to sign that some data are received
// ==========================================
// part II: implementation


// =====================================
// pre defs
// =====================================

// the thread function for receiving data
void * APclient_RecvThread (void *);


// =====================================
// functions
// =====================================


// creates an admin client
int APclient_create (
		TAPClient *					pC,					//!<(in/out) pointer to a client structure to be filled
		uint16_t 					adminPort,			//!<(in) the port of the admin server port
		uint16_t					recvBufferSize,		//!<(in) size in bytes of the receive buffer
		void *						pUserData,			//!<(in) user data
		TpfktAPClientRecvCallback	fktCB				//!<(in) callback function when receiving data
	) {
	uint8_t		msgID;

	// 0. save the user data
	pC->pUserData = pUserData;

	// 1. create a socket to communicate with the admin port
	if (stjSocket_createClient(
			adminPort,
			&(pC->sAdmin),
			&(pC->aAdmin)
		)) {
		return -1;
	}

	pC->adminPort = adminPort;
	// 2. setup
	// request login
	msgID = eAdminMsgType_login;
	if (stjSocket_send(pC->sAdmin,&msgID,1,&(pC->aAdmin))) goto sendFailed;
	// get the ports
	if (stjSocket_recv(pC->sAdmin,(char *)&msgID,1,&(pC->aAdmin))) goto receivedFailed;
	if (msgID != eAdminMsgType_login) {
		fprintf(stderr,"admin send wrong message back\n");
		goto abortAndError;
	}

	if (stjSocket_recv(pC->sAdmin,(char *)&(pC->uuid),2,&(pC->aAdmin))) goto receivedFailed;
	if (stjSocket_recv(pC->sAdmin,(char *)&(pC->dataInPort),2,&(pC->aAdmin))) goto receivedFailed;
	if (stjSocket_recv(pC->sAdmin,(char *)&(pC->dataOutPort),2,&(pC->aAdmin))) goto receivedFailed;


	printf("data in: %u\ndata out: %u\n",(unsigned int)pC->dataInPort,(unsigned int)pC->dataOutPort);

	// create data sockets
	if (stjSocket_createServer(
			pC->dataInPort,
			&(pC->sDataIn),
			&(pC->aDataIn)
		)) goto DataSocketCreationError;

	// create recv buffer & threads
	pC->recvBuffer = malloc((size_t)recvBufferSize);
	if (!pC) goto abortAndError;
	pC->recvBufferSize = recvBufferSize;
	pC->fktRecvCB = fktCB;

	// now we can start the handling thread
	pthread_create(&pC->recvThread,NULL,APclient_RecvThread,pC);

	// send ack to server
	msgID = eAdminMsgType_ack;
	if (stjSocket_send(pC->sAdmin,&msgID,1,&(pC->aAdmin))) goto sendFailed;

	// wait till server is ready
	if (stjSocket_recv(pC->sAdmin,&msgID,1,&(pC->aAdmin))) goto receivedFailed;
	if (eAdminMsgType_ack != msgID) {
		fprintf(stderr,"admin error\n");
		return -10;
	}

	// now open the client data port
	if (stjSocket_createClient(
			pC->dataOutPort,
			&(pC->sDataOut),
			&(pC->aDataOut)
		)) goto DataSocketCreationError;

	// some info
    printf ("client setup with uuid=%u data-in port:%u data-out port:%u\n",(unsigned int)pC->uuid,(unsigned int)pC->dataInPort,(unsigned int)pC->dataOutPort);
    fflush(stdout);
	return 0;

abortAndError:
	msgID = eAdminMsgType_nack;
	stjSocket_send(pC->sAdmin,&msgID,1,&(pC->aAdmin));
	return -2;

sendFailed:
	fprintf(stderr,"sending to admin failed\n");
	fprintf (stderr,"error: %s\n",gai_strerror(WSAGetLastError()));
	return -3;

receivedFailed:
	fprintf(stderr,"receiving from admin failed\n");
	fprintf (stderr,"error: %s\n",gai_strerror(WSAGetLastError()));
	return -4;

DataSocketCreationError:
	fprintf(stderr,"creating data sockets failed\n");
	fprintf (stderr,"error: %s\n",gai_strerror(WSAGetLastError()));
	return -4;
}

//! free's the client
int APclient_close (
		TAPClient *		pC			//!<(in/out) pointer to a client structure to be filled
	) {
	// vars
	uint8_t				msgID;

	// request logout
	msgID = eAdminMsgType_logout;
	if (stjSocket_send(pC->sAdmin,(char *)&msgID,1,&(pC->aAdmin))) goto sendFailed;
	if (stjSocket_send(pC->sAdmin,(char *)&(pC->uuid),2,&(pC->aAdmin))) goto sendFailed;
	// wait till server finished it
	if (stjSocket_recv(pC->sAdmin,(char *)&msgID,1,&(pC->aAdmin))) goto receivedFailed;
	if (msgID != eAdminMsgType_ack) {
		fprintf(stderr,"logout failed\n");
	}

	stjSocket_close(pC->sAdmin,&(pC->aAdmin));
	stjSocket_close(pC->sDataIn,&(pC->aDataIn));
	stjSocket_close(pC->sDataOut,&(pC->aDataOut));

	// wait till thread is gone
	pthread_join(pC->recvThread,NULL);


	return 0;
sendFailed:
	fprintf(stderr,"sending to admin failed\n");
	return -3;

receivedFailed:
	fprintf(stderr,"receiving from admin failed\n");
	return -4;
}

// the thread function for receiving data
void * APclient_RecvThread (
		void *	pArg
	) {
	uint16_t			msgLen;
	uint8_t *			pNB;

	TAPClient *			pC = pArg;

	// get data
	for (;;) {
		// read amount of data to be received
		if (stjSocket_recv(pC->sDataIn,&msgLen,2,&(pC->aDataIn))) goto recvError;
		// check if we have enough memory allocated at the buffer
		if (msgLen > pC->recvBufferSize) {
			pNB = realloc(pC->recvBuffer,msgLen);
			if (pNB) {
				pC->recvBuffer = pNB;
				pC->recvBufferSize = msgLen;
			} else {
				fprintf (stderr,"realloc memory failed");
				goto recvError;
			}
		}
		// transmit data
		if (stjSocket_recv(pC->sDataIn,pC->recvBuffer,msgLen,&(pC->aDataIn))) goto recvError;
		// and handle the data
		pC->fktRecvCB(pC->pUserData, msgLen, pC->recvBuffer);

	}
	pthread_exit((void *)0);
	return NULL;

recvError:
	// close data connections
	fprintf (stderr,"receiving data failed!");
	pthread_exit((void *)-3);
	return NULL;
}


int APclient_send (
		TAPClient *		pC,			//!<(in) pointer to a client structure
		uint16_t		num,		//!<(in) amount of bytes to send
		uint8_t *		pData		//!<(in) pointer to the data
	) {
	if (stjSocket_send(pC->sDataOut,&pC->uuid,2,&(pC->aDataOut))) goto sendFailed;
	if (stjSocket_send(pC->sDataOut,&num,2,&(pC->aDataOut))) goto sendFailed;
	if (stjSocket_send(pC->sDataOut,pData,(int)num,&(pC->aDataOut))) goto sendFailed;

	return 0;
sendFailed:
	fprintf(stderr,"sending data to server failed\n");
	return -1;

}

// ===============================
// // extra code for group "pthreads and semaphores"
// ===============================


// ===============================
// // extra code for group "gtk+ for Windows"
// ===============================

// -------------------------------------------
// AP gtk helper
// -------------------------------------------

PangoFontDescription * gAPgtkMonoSpaceFont = NULL;


// a helper for destroying "undestroyed" UI's
void APgtk_helper_destroy (GtkWidget * pWG) {
	if (pWG) {
//		if (pWG->object.parent_instance.ref_count) {
			gtk_widget_destroy(pWG);
//		}
	}
}

// -------------------------------------------
// AP panel
// -------------------------------------------

// struct for a panel
typedef struct SAPgtkPanel {
	GtkWidget *		pWnd;		//!< pointer to the window
	GtkWidget *		pBox;		//!< placement box
} TAPgtkPanel;


// create a panel
int gtkAP_local_PanelCreate (
		TAPgtkPanel * 	pP,		//!<(in/out) structure to be filled
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {
	// Create a new window
	pP->pWnd = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	if (!pP->pWnd) return -1;

	// UI's are at fixed positions
	pP->pBox = gtk_fixed_new();
	if (!pP->pBox) return -2;

	gtk_container_add(GTK_CONTAINER(pP->pWnd), pP->pBox);

	// setup main wnd
	gtk_window_set_title (GTK_WINDOW (pP->pWnd), "AP Panel");
	gtk_window_set_default_size (GTK_WINDOW (pP->pWnd),xle, yle);
	gtk_window_move(GTK_WINDOW (pP->pWnd),x, y);

	// It's a good idea to do this for all windows
	//gtk_signal_connect (GTK_OBJECT (pP->pWnd), "destroy", GTK_SIGNAL_FUNC (gtk_exit), NULL);
	g_signal_connect (G_OBJECT (pP->pWnd), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);

	//gtk_signal_connect (GTK_OBJECT (pP->pWnd), "delete_event", GTK_SIGNAL_FUNC (gtk_exit), NULL);
	g_signal_connect (G_OBJECT (pP->pWnd), "delete_event", G_CALLBACK (gtk_widget_destroy), NULL);

	// Sets the border width of the window
	gtk_container_set_border_width (GTK_CONTAINER (pP->pWnd), 1);

	gtk_widget_realize(pP->pWnd);

	gtk_widget_show_all(pP->pWnd);

	return(0);
}


// destroys a panel
void gtkAP_local_PanelDestroy (
		TAPgtkPanel * 	pP
	) {
	APgtk_helper_destroy(pP->pWnd);
	APgtk_helper_destroy(pP->pBox);
	pP->pWnd = NULL;
	pP->pBox = NULL;
}

// -------------------------------------------
// AP button
// -------------------------------------------

// struct for a AP button
typedef struct SAPgtkButton {
	GtkWidget *		pB;				//!< pointer to the button
	int				pressCounter;	//!< counter of the press event
} TAPgtkButton;

// call back to handle click calls
void gtkAP_cb_ButtonClicked (GtkWidget *widget, gpointer data) {
	TAPgtkButton * pB = (TAPgtkButton *) data;
	pB->pressCounter++;
}

// creates a AP button
int gtkAP_local_ButtonCreate (
		TAPgtkButton * 	pB,		//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {


	pB->pressCounter = 0;
	// create button
	pB->pB = gtk_button_new_with_label  ("");
	if (!pB->pB) return -1;

	// bind it to the window
	gtk_fixed_put(GTK_FIXED(pP->pBox), pB->pB, x, y);
	gtk_widget_set_size_request(pB->pB, xle, yle);

	gtk_widget_modify_font(gtk_bin_get_child (GTK_BIN(pB->pB)),gAPgtkMonoSpaceFont);

	gtk_widget_show (pB->pB);

	// set msg handler
	g_signal_connect(G_OBJECT(pB->pB), "clicked", G_CALLBACK(gtkAP_cb_ButtonClicked), pB);


	return 0;
}

// destroys a button
void gtkAP_local_ButtonDestroy (
		TAPgtkButton * 	pB
	) {
	APgtk_helper_destroy(pB->pB);

	pB->pB = NULL;
	pB->pressCounter = 0;
}

// -------------------------------------------
// AP LED
// -------------------------------------------

// struct for a AP led
typedef struct SAPgtkLED {
	GtkWidget *		pLED;				//!< pointer to the LED
	int				onFlag;
	double			onColor[3];
	double			offColor[3];
} TAPgtkLED;


static gboolean APgtk_cb_LEDexpose (
		GtkWidget *			da,
		GdkEventExpose *	event,
		gpointer        	data
	)
{
  cairo_t *		cr;
  TAPgtkLED	* 	pLED = (TAPgtkLED	*) data;
  double 		r;
  cr = gdk_cairo_create (gtk_widget_get_window(da));
  gdk_cairo_rectangle (cr, &event->area);
  cairo_clip (cr);
  if (pLED->onFlag) {
	  cairo_set_source_rgb (cr, pLED->onColor[0], pLED->onColor[1], pLED->onColor[2]);
  } else {
	  cairo_set_source_rgb (cr, pLED->offColor[0], pLED->offColor[1], pLED->offColor[2]);
  }
  //cairo_rectangle(cr, event->area.x, event->area.y, event->area.width, event->area.height);
  r = (event->area.width > event->area.height) ? event->area.width : event->area.height;
  r /= 2.f;
  cairo_arc (cr,event->area.x+r, event->area.y+r,r, 0.f, 2.f * M_PI);

  cairo_fill(cr);
  cairo_destroy (cr);
  return TRUE;
}

// creates a AP button
int gtkAP_local_LEDCreate (
		TAPgtkLED * 	pLED,	//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	pLED->onFlag = 0;
	pLED->offColor[0] = 0.0;
	pLED->offColor[1] = 0.0;
	pLED->offColor[2] = 0.0;
	pLED->onColor[0] = 1.0;
	pLED->onColor[1] = 1.0;
	pLED->onColor[2] = 1.0;


	pLED->pLED = gtk_drawing_area_new ();
	if (!pLED->pLED) return -1;
	gtk_widget_set_size_request (pLED->pLED, xle, yle);

	gtk_fixed_put(GTK_FIXED(pP->pBox), pLED->pLED, x, y);

	g_signal_connect (pLED->pLED, "expose-event",  G_CALLBACK (APgtk_cb_LEDexpose), pLED);

	gtk_widget_show (pLED->pLED);

	return 0;
}

// destroys a button
void gtkAP_local_LEDDestroy (
		TAPgtkLED * 	pLED
	) {
	APgtk_helper_destroy(pLED->pLED);

	pLED->pLED = NULL;
	pLED->onFlag = 0;
	pLED->offColor[0] = 0.0;
	pLED->offColor[1] = 0.0;
	pLED->offColor[2] = 0.0;
	pLED->onColor[0] = 0.0;
	pLED->onColor[1] = 0.0;
	pLED->onColor[2] = 0.0;
}


// -------------------------------------------
// AP Display
// -------------------------------------------

// struct for a AP led
typedef struct SAPgtkDisplay {
	GtkWidget *		pD;				//!< pointer to the display
	GtkWidget *		pF;				//!< frame around the label
	int				charsPerLine;
	int				lineCount;
} TAPgtkDisplay;


// creates a AP display
int gtkAP_local_DisplayCreate (
		TAPgtkDisplay *	pD,		//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	pD->pD = NULL;
	pD->charsPerLine = 10;
	pD->lineCount = 4;

	pD->pD = gtk_label_new ("");
	if (!pD->pD) return -1;
	pD->pF = gtk_frame_new(NULL);
	if (!pD->pF) return -2;

	//gtk_widget_set_size_request (pD->pD, xle-2, yle-2);
	gtk_widget_set_size_request (pD->pF, xle, yle);

	//gtk_fixed_put(GTK_FIXED(pP->pBox), pD->pD, x, y);
	gtk_fixed_put(GTK_FIXED(pP->pBox), pD->pF, x, y);
	gtk_container_add(GTK_CONTAINER(pD->pF), pD->pD);

	//gtk_widget_modify_font(gtk_bin_get_child (GTK_BIN(pD->pD)),gAPgtkMonoSpaceFont);
	gtk_widget_modify_font(pD->pD,gAPgtkMonoSpaceFont);

	/*
	// change colors
	GdkColor color;
	gdk_color_parse ("yellow", &color);
	gtk_widget_modify_fg (pD->pD, GTK_STATE_NORMAL, &color);
	// background only works for the main wnd!
	gdk_color_parse ("green", &color);
	gtk_widget_modify_bg(pP->pWnd, GTK_STATE_NORMAL, &color);
	 */

	gtk_widget_show (pD->pD);
	gtk_widget_show (pD->pF);

	return 0;
}

// destroys a display
void gtkAP_local_DisplayDestroy (
		TAPgtkDisplay * 	pD
	) {
	APgtk_helper_destroy(pD->pD);

	pD->pD = NULL;
	pD->charsPerLine = 10;
	pD->lineCount = 2;
}

// sets a display text
void gtkAP_local_DisplaySetTextDim(
		TAPgtkDisplay * 	pD,
		int					charsPerLine,
		int					lineCount
	) {
	pD->charsPerLine = charsPerLine;
	pD->lineCount = lineCount;
}


// sets a display text
void gtkAP_local_DisplaySetText(
		TAPgtkDisplay * 	pD,
		char *				szTxt
	) {
	const char const cLF = 0xA;
	char szdummyBuffer[pD->lineCount*pD->charsPerLine+1];
	char * pC = szdummyBuffer;
	int x = 0;
	int y = 0;

	while (*szTxt) {
		// check if we have a line break
		if (*szTxt == cLF) {
			y++;
			x = 0;
			// check if we reached the end
			if (y == pD->lineCount) {
				*pC = 0;
				goto printLines;
			}
		}

		// copy char
		*pC = *szTxt;
		szTxt++;
		pC++;
		x++;

		// check if we reached the end of the line
		if (x == pD->charsPerLine) {
			y++;
			x=0;
			// check if we reached the end
			if (y < pD->lineCount) {
				*pC = cLF;
				pC++;
			} else {
				*pC = 0;
				goto printLines;
			}
		}

	}
	*pC = 0;
printLines:
	gtk_label_set_text(GTK_LABEL(pD->pD),szdummyBuffer);
}

// ===========================================
// AP gtk+ interface
// ===========================================

enum eAPgtkActionID {
	eAPgtkActionID_exit				= 1,
	eAPgtkActionID_redrawUI			= 10,
	eAPgtkActionID_setDisplayText	= 11,
	eAPgtkActionID_createPanel		= 20,
	eAPgtkActionID_deletePanel		= 21,
	eAPgtkActionID_createButton		= 30,
	eAPgtkActionID_deleteButton		= 31,
	eAPgtkActionID_createLED		= 40,
	eAPgtkActionID_deleteLED		= 41,
	eAPgtkActionID_createDisplay	= 50,
	eAPgtkActionID_deleteDisplay	= 51,

};

typedef struct SAPgtk_command {
	sem_t		ps;			//!< process finsh semaphore
	GMutex *	gm;			//!< guarding mutex
	int			newCmdFlag;	//!< is set to indicate that there is a new command

	int 		cmd; 		//!< command
	void *		pData1;
	void *		pData2;
	int 		x;
	int			y;
	int			xle;
	int			yle;


} TAPgtk_command;


TAPgtk_command			gAPgtkMsg;
GThread *				gAPgtkThread;

void APgtk_setMsg (
		int		id,
		void *	pD1,
		void *	pD2,
		int		x,
		int		y,
		int		xle,
		int		yle
) {
	g_mutex_lock(gAPgtkMsg.gm);
	// set the command
	gAPgtkMsg.cmd = id;
	gAPgtkMsg.pData1 = pD1;
	gAPgtkMsg.pData2 = pD2;
	gAPgtkMsg.x = x;
	gAPgtkMsg.y = y;
	gAPgtkMsg.xle = xle;
	gAPgtkMsg.yle = yle;
	gAPgtkMsg.newCmdFlag = 1;
	g_mutex_unlock(gAPgtkMsg.gm);

	sem_wait(&gAPgtkMsg.ps);
}

gpointer APgtk_threadFunc (gpointer Args) {
	// init gtk and bind it to the thread
	if (FALSE ==  gtk_init_check(NULL, NULL)) return ((gpointer)-1);

	gAPgtkMonoSpaceFont = pango_font_description_from_string("monospace");

	// process messages & user actions
	for (;;) {
		// check for message
		g_mutex_lock(gAPgtkMsg.gm);
		if (gAPgtkMsg.newCmdFlag) {
			switch (gAPgtkMsg.cmd) {
				case eAPgtkActionID_exit:
					goto exit;
					break;
				case eAPgtkActionID_redrawUI:
					gtk_widget_queue_draw (GTK_WIDGET(gAPgtkMsg.pData1));
					break;

				case eAPgtkActionID_setDisplayText:
					gtkAP_local_DisplaySetText(gAPgtkMsg.pData1,gAPgtkMsg.pData2);
					break;

				case eAPgtkActionID_createPanel:
					gtkAP_local_PanelCreate (
							gAPgtkMsg.pData1,
							gAPgtkMsg.x,
							gAPgtkMsg.y,
							gAPgtkMsg.xle,
							gAPgtkMsg.yle
						);
					break;
				case eAPgtkActionID_deletePanel:
					gtkAP_local_PanelDestroy(gAPgtkMsg.pData1);
					break;

				case eAPgtkActionID_createButton:
					gtkAP_local_ButtonCreate(
							gAPgtkMsg.pData1,
							gAPgtkMsg.pData2,
							gAPgtkMsg.x,
							gAPgtkMsg.y,
							gAPgtkMsg.xle,
							gAPgtkMsg.yle
						);
					break;
				case eAPgtkActionID_deleteButton:
					gtkAP_local_ButtonDestroy(gAPgtkMsg.pData1);
					break;

				case eAPgtkActionID_createLED:
					gtkAP_local_LEDCreate(
							gAPgtkMsg.pData1,
							gAPgtkMsg.pData2,
							gAPgtkMsg.x,
							gAPgtkMsg.y,
							gAPgtkMsg.xle,
							gAPgtkMsg.yle
						);
					break;
				case eAPgtkActionID_deleteLED:
					gtkAP_local_LEDDestroy(gAPgtkMsg.pData1);
					break;

				case eAPgtkActionID_createDisplay:
					gtkAP_local_DisplayCreate(
							gAPgtkMsg.pData1,
							gAPgtkMsg.pData2,
							gAPgtkMsg.x,
							gAPgtkMsg.y,
							gAPgtkMsg.xle,
							gAPgtkMsg.yle
						);
					break;
				case eAPgtkActionID_deleteDisplay:
					gtkAP_local_DisplayDestroy(gAPgtkMsg.pData1);
					break;
			}
			gAPgtkMsg.newCmdFlag = 0;
			sem_post(&gAPgtkMsg.ps);
		}
		g_mutex_unlock(gAPgtkMsg.gm);

		// message handling
		if (TRUE == gtk_events_pending ()) {
			gtk_main_iteration ();
		}

	}
	goto end;
exit:
	sem_post(&gAPgtkMsg.ps);
	g_mutex_unlock(gAPgtkMsg.gm);
end:
	pango_font_description_free(gAPgtkMonoSpaceFont);
	gAPgtkMonoSpaceFont = NULL;
	return NULL;
}

int APgtk_start () {

	if (!g_thread_supported ()) g_thread_init (NULL);

	gAPgtkMsg.newCmdFlag = 0; // no cmd ready
	gAPgtkMsg.gm = g_mutex_new ();
	sem_init(&gAPgtkMsg.ps,0,0);

	gAPgtkThread = g_thread_create(APgtk_threadFunc, NULL,TRUE, NULL);
	return 0;
}


void APgtk_end () {
	APgtk_setMsg(eAPgtkActionID_exit, NULL, NULL, 0, 0, 0, 0);
	g_thread_join(gAPgtkThread);
	g_mutex_free(gAPgtkMsg.gm);
	sem_destroy(&gAPgtkMsg.ps);
}

// ----------------------------
// AP interface
// ----------------------------

// create a panel
int gtkAP_PanelCreate (
		TAPgtkPanel * 	pP,		//!<(in/out) structure to be filled
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	APgtk_setMsg (eAPgtkActionID_createPanel, pP, NULL, x, y, xle, yle);

	return(0);
}


// destroys a panel
void gtkAP_PanelDestroy (
		TAPgtkPanel * 	pP
	) {
	APgtk_setMsg (eAPgtkActionID_deletePanel, pP, NULL, 0,0,0,0);
}


// create a button
int gtkAP_ButtonCreate (
		TAPgtkButton * 	pB,		//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	APgtk_setMsg (eAPgtkActionID_createButton, pB, pP, x, y, xle, yle);

	return(0);
}


// destroys a button
void gtkAP_ButtonDestroy (
		TAPgtkButton * 	pB
	) {
	APgtk_setMsg (eAPgtkActionID_deleteButton, pB, NULL, 0,0,0,0);
}

// create a LED
int gtkAP_LEDCreate (
		TAPgtkLED * 	pLED,	//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	APgtk_setMsg (eAPgtkActionID_createLED, pLED, pP, x, y, xle, yle);

	return(0);
}


// destroys a LED
void gtkAP_LEDDestroy (
		TAPgtkLED * 	pLED
	) {
	APgtk_setMsg (eAPgtkActionID_deleteLED, pLED, NULL, 0,0,0,0);
}


// create a display
int gtkAP_DisplayCreate (
		TAPgtkDisplay * pD,		//!<(in/out) structure to be filled
		TAPgtkPanel * 	pP,		//!<(in) panel witch holds the button
		int				x,		//!<(in) x position of the window
		int				y,		//!<(in) y position of the window
		int				xle,	//!<(in) x length of the window
		int				yle		//!<(in) x length of the window
	) {

	APgtk_setMsg (eAPgtkActionID_createDisplay, pD, pP, x, y, xle, yle);

	return(0);
}


// destroys a display
void gtkAP_DisplayDestroy (
		TAPgtkDisplay * 	pD
	) {
	APgtk_setMsg (eAPgtkActionID_deleteDisplay, pD, NULL, 0,0,0,0);
}

// destroys a display
void gtkAP_DisplaySetText (
		TAPgtkDisplay * 	pD,
		char *				pT
	) {
	APgtk_setMsg (eAPgtkActionID_setDisplayText, pD, pT, 0,0,0,0);
}


// ===========================================
// AP gtk general types and interface
// ===========================================

// AP gtk+ type enums
enum eAPgtkUItypes {
	eAPgtkUItype_unknown	= 0,
	eAPgtkUItype_panel		= 1,
	eAPgtkUItype_button		= 2,
	eAPgtkUItype_LED		= 3,
	eAPgtkUItype_display	= 4
};

// AP UI type
typedef struct SAPgtkUI {
	int		uuid;
	int 	x;
	int		y;
	int		xle;
	int		yle;
	int		typeID;
	union 	uAPgtkUI {
		TAPgtkPanel		panel;
		TAPgtkButton	button;
		TAPgtkDisplay	display;
		TAPgtkLED		led;
	} ui;
} TAPgtkUI;

// set the coordinates of the ui
void APgtkUI_setCoordinates (
		TAPgtkUI *	pUI,
		int 		x,
		int			y,
		int			xle,
		int			yle
	) {
	pUI->x = x;
	pUI->y = y;
	pUI->xle = xle;
	pUI->yle = yle;
}

// creates visible ui
int APgtkUI_createUI (
		TAPgtkUI *	pUI,
		TAPgtkUI *	pParentUI,
		int			uuid,
		int			typeID
	) {
	pUI->typeID = typeID;
	pUI->uuid = uuid;
	switch (typeID) {
		case eAPgtkUItype_panel:
			return gtkAP_PanelCreate(
					&(pUI->ui.panel),
					pUI->x,
					pUI->y,
					pUI->xle,
					pUI->yle
				);
		case eAPgtkUItype_button:
			return gtkAP_ButtonCreate(
					&(pUI->ui.button),
					&(pParentUI->ui.panel),
					pUI->x,
					pUI->y,
					pUI->xle,
					pUI->yle
				);
		case eAPgtkUItype_LED:
			return gtkAP_LEDCreate(
					&(pUI->ui.led),
					&(pParentUI->ui.panel),
					pUI->x,
					pUI->y,
					pUI->xle,
					pUI->yle
				);
		case eAPgtkUItype_display:
			return gtkAP_DisplayCreate(
					&(pUI->ui.display),
					&(pParentUI->ui.panel),
					pUI->x,
					pUI->y,
					pUI->xle,
					pUI->yle
				);
	}
	return -100;
}

// destroy visible ui
void APgtkUI_destroyUI (
		TAPgtkUI *	pUI
	) {
	switch (pUI->typeID) {
		case eAPgtkUItype_panel:
			gtkAP_PanelDestroy(&(pUI->ui.panel));
			break;
		case eAPgtkUItype_button:
			gtkAP_ButtonDestroy(&(pUI->ui.button));
			break;
		case eAPgtkUItype_LED:
			gtkAP_LEDDestroy(&(pUI->ui.led));
			break;
		case eAPgtkUItype_display:
			gtkAP_DisplayDestroy(&(pUI->ui.display));
			break;
	}
	pUI->typeID = eAPgtkUItype_unknown;
	pUI->uuid = 0;
}

// redraws a ui
void APgtkUI_redrawUI (
		TAPgtkUI *	pUI
	) {
	switch (pUI->typeID) {
		case eAPgtkUItype_panel:
			APgtk_setMsg (eAPgtkActionID_redrawUI, pUI->ui.panel.pWnd, NULL, 0,0,0,0);
			break;
		case eAPgtkUItype_button:
			APgtk_setMsg (eAPgtkActionID_redrawUI, pUI->ui.button.pB, NULL, 0,0,0,0);
			break;
		case eAPgtkUItype_LED:
			APgtk_setMsg (eAPgtkActionID_redrawUI, pUI->ui.led.pLED, NULL, 0,0,0,0);
			break;
		case eAPgtkUItype_display:
			APgtk_setMsg (eAPgtkActionID_redrawUI, pUI->ui.display.pD, NULL, 0,0,0,0);
			break;
	}
}


// AP UI array type
typedef struct SAPgtkUIvector {
	TAPgtkUI * 	pUI;
	int			number;
} TAPgtkUIvector;


TAPgtkUIvector * APgtkUI_createVector (
		int number,
		int uiType
	) {
	TAPgtkUIvector * 	pV;
	int					i;

	pV = malloc (sizeof(TAPgtkUIvector));
	if (!pV) return NULL;
	pV->pUI = malloc (sizeof(TAPgtkUI)*number);
	if (!pV->pUI) {
		free (pV);
		return NULL;
	}
	memset (pV->pUI,0,sizeof(TAPgtkUI)*number);

	pV->number = number;
	for (i = 0; i < number; i++) {
		pV->pUI[i].typeID = uiType;
	}

	return pV;
}

void APgtkUI_destroyVector (
		TAPgtkUIvector * pUIv
	) {
	int i;
	for (i = 0; i < pUIv->number; i++) {
		APgtkUI_destroyUI(&(pUIv->pUI[i]));
	}
	free (pUIv->pUI);;
	free (pUIv);
}

// ===============================
// // extra code for group "ANSI C strings"
// ===============================

// --------------------------------------
// TAPstringVector
// --------------------------------------

// ap string
typedef struct SAPstring {
	char *	szTxt;	//!< pointer to char buffer
	size_t	maxLen;	//!< length of the char buffer(without the zero at the end)
} TAPstring;

// vector of strings type
typedef struct SAPstringVector {
	TAPstring *		sv;		//!< string vector
	unsigned int	num;	//!< amount of strings at the vector
} TAPstringVector;

// creates a AP string
TAPstringVector * APstringVector_create (
		int		num		//!<(in) number of strings at the vector
	) {
	TAPstringVector * pR;
	int i;

	pR = malloc(sizeof(TAPstringVector));
	if (!pR) return NULL;
	pR->sv = malloc(sizeof(TAPstring)*num);
	if (!pR->sv){
		free (pR);
		return NULL;
	}
	// init str
	TAPstring * ps = pR->sv;
	for (i = 0; i < num; i++) {
		ps->szTxt = NULL;
		ps->maxLen = 0;
		ps++;
	}
	pR->num = num;
	return pR;
}

// frees a AP string
void APstringVector_free (
		TAPstringVector * 	pSV	//!<(in) pointer to the string vector
	) {
	unsigned int i;
	if (pSV->sv) {
		TAPstring * ps = pSV->sv;
		for (i = 0; i < pSV->num; i++) {
			if (ps->szTxt){
				free(ps->szTxt);
			}
		}
		free(pSV->sv);
	}
	free(pSV);
}

// resizes the amount of strings at the string vector
int APstringVector_resizeVector (
		TAPstringVector * 	pSV,	//!<(in) pointer to the string vector
		int					num		//!<(in) number of strings at the vector
	) {
	if (pSV->num == num) return 0;
	unsigned int	i;
	TAPstring * 	ps;

	if (pSV->sv) {
		ps = pSV->sv;
		for (i = 0; i < pSV->num; i++) {
			if (ps->szTxt){
				free(ps->szTxt);
			}
		}
		free(pSV->sv);
	}
	pSV->sv = malloc(sizeof(TAPstring)*num);
	if (!pSV->sv){
		return -1;
	}
	// init str
	ps = pSV->sv;
	for (i = 0; i < num; i++) {
		ps->szTxt = NULL;
		ps->maxLen = 0;
		ps++;
	}
	pSV->num = num;
	return 0;
}

// resizes a string at the vector
int APstringVector_resize (
		TAPstringVector * 	pSV,	//!<(in) pointer to the string vector
		int					index,	//!<(in) index of the string at the stringarray
		size_t				newLen	//!<(in) new length of the string
	) {
	TAPstring * ps = pSV->sv + index;
	if (ps->maxLen < newLen) {
		// allocate new string
		char * nsz = malloc(sizeof(char) * (newLen +1));
		if (!nsz) return -1;
		if (ps->szTxt) {
			// copy old string
			strcpy(nsz,ps->szTxt);
			// release old string
			free(ps->szTxt);
			ps->szTxt = NULL;
		} else {
			*nsz = 0;
		}
		// set the new string
		ps->szTxt =nsz;
		// remember the length
		ps->maxLen = newLen;
	} else {
		if(ps->szTxt) {
			// trail old string
			ps->szTxt[newLen] = 0;
		}
	}
	return 0;
}

// fills the string from an extern source
void APstringVector_fill(
		TAPstringVector * 	pSV,	//!<(in) pointer to the string vector
		int					index,	//!<(in) index of the string at the stringarray
		int					iStart,	//!<(in) start index at the string
		int					iEnd,	//!<(in) end index of the string
		char *				pSource	//!<(in) source from where the chars are copied
	) {
	int i, imax;
	char * pDest = pSV->sv[index].szTxt;
	pDest += iStart;
	// clip str
	imax = pSV->sv[index].maxLen;
	if (iEnd > imax) {
		iEnd = imax;
	}

	for (i = iStart;i < iEnd; i++) {
		*pDest = *pSource;
		pDest++;
		pSource++;
	}
	*pDest = 0;
}


// concat string 2 with string 1
int APstringVector_concat(
		TAPstringVector * 	pSV1,		//!<(in) pointer to the first string vector
		int					indexSV1,	//!<(in) index of the string at the stringarray
		TAPstringVector * 	pSV2,		//!<(in) pointer to the second string vector
		int					indexSV2	//!<(in) index of the string at the stringarray
	) {
	TAPstring * ps1 = pSV1->sv + indexSV1;
	TAPstring * ps2 = pSV2->sv + indexSV2;
	// get new size
	size_t sl1;
	size_t sl2;
	sl1 = ps1->szTxt ? strlen(ps1->szTxt) : 0;
	sl2 = ps2->szTxt ? strlen(ps2->szTxt) : 0;
	size_t newL = sl1 + sl2;
	// reallocate?
	if (ps1->maxLen < newL) {
		if (APstringVector_resize(pSV1, indexSV1, newL)) return -1;
	}
	if (ps2->szTxt) {
		// copy string 2 at the end of string 1
		strcpy(ps1->szTxt + sl1,ps2->szTxt);
	}
	return 0;
}


// assigns string 2 to string 1
int APstringVector_assign(
		TAPstringVector * 	pSV1,		//!<(in) pointer to the first string vector
		int					indexSV1,	//!<(in) index of the string at the stringarray
		TAPstringVector * 	pSV2,		//!<(in) pointer to the second string vector
		int					indexSV2	//!<(in) index of the string at the stringarray
	) {
	TAPstring * ps1 = pSV1->sv + indexSV1;
	TAPstring * ps2 = pSV2->sv + indexSV2;
	// get new size
	size_t sl2 = strlen(ps2->szTxt);
	// reallocate?
	if (ps1->maxLen < sl2) {
		if (APstringVector_resize(pSV1, indexSV1, sl2)) return -1;
	}
	// copy string 2 at the end of string 1
	strcpy(ps1->szTxt,ps2->szTxt);

	return 0;
}


// print a floating point number into the string
void APstringVector_printFloat(
		TAPstringVector * 	pSV,			//!<(in) pointer to the first string vector
		int					indexSV,		//!<(in) index of the string at the stringarray
		float				number			//!<(in) number to be printed
	) {
	APstringVector_resize(pSV,indexSV, 20);
	TAPstring * ps = pSV->sv + indexSV;
	snprintf(ps->szTxt, ps->maxLen+1, "%f", (double)number);

}

// print a integer number into the string
void APstringVector_printInt(
		TAPstringVector * 	pSV,			//!<(in) pointer to the first string vector
		int					indexSV,		//!<(in) index of the string at the stringarray
		int					number			//!<(in) number to be printed
	) {
	APstringVector_resize(pSV,indexSV, 20);
	TAPstring * ps = pSV->sv + indexSV;
	snprintf(ps->szTxt, ps->maxLen+1, "%i", number);
}

// ===============================
// // extra code for group "biquad filters (generic)"
// ===============================

// =================================================
// a generic biquad filter lib based on the math.h
// part I - defines
// =================================================
//        a0 + a1 *z-1 + a2*z-2
// H(z) = ---------------------
//        1 + b1 *z-1 + b2*z-2
//
// y(n)   a0 + a1 *z-1 + a2*z-2
// ---- = ---------------------
// x(n)   1 + b1 *z-1 + b2*z-2
//
// y(n) + b1 *y(n-1) + b2*y(n-2) = a0 * x(n) + a1 *x(n-1) + a2*x(n-2)
// y(n) = a0 * x(n) + a1 *x(n-1) + a2*x(n-2) - b1 *y(n-1) + b2*y(n-2)

#define dstjBQF_implementPrintFunctions

#define dstjBQF_implementUseDoubleForCoeff

#ifdef dstjBQF_implementUseDoubleForCoeff
	typedef double TstjBQF_BiquadFloat;
#else
	#define dBQF_UseFloatMath
	typedef float TstjBQF_BiquadFloat;
#endif
// the biquad structure at the direct form II
typedef struct SstjBiquad {
    float a [3]; // numerator
	float b [2]; // denumerator
	float x [2];
	float y [2];
} TstjBiquad;

// a cascade of biquad filters
typedef struct SstjBiquadCascade {
	int				num;
	TstjBiquad *	pB;
} TstjBiquadCascade;

//! creates a cascade of biquad filters
int stjBQF_cascadeCreate (
		TstjBiquadCascade *	pBQC,	//!< (in/out) pointer to a struct to be filled
		int 				num		//!< amount of filters
	);

//! deletes a cascade of biquad filters
void stjBQF_cascadeDelete (
		TstjBiquadCascade *	pBQC	//!< (in) pointer to a struct to be freed
	);

//! convolut the input with the biquad filter cascade and generate the output (y = BQFc * x)
void stjBQF_cascadeConvolute (
		TstjBiquadCascade *	pBQC,	//!< (in) the biquad cascade
		float * 			px,		//!< (in) input signal vector
		unsigned int		xNum,	//!< (in) amount of elements at the input vector
		float * 			py		//!< (out) output signal vector (size must be more or equal to px)
	);

//! Initializes a element of the biquad cascade as high-pass(HP) filter
int stjBQF_cascadeInitHP (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biquad cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as HP
		float  				fs,		//!< (in) sample frequency
		float  				fc		//!< (in) cut off frequency
	);

//! initializes a element of the biquad cascade as low-pass(LP) filter
int stjBQF_cascadeInitLP (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biquad cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as LP
		float  				fs,		//!< (in) sample frequency
		float  				fc		//!< (in) cut off frequency
	);

//! initializes a element of the biquad cascade as peak boost/cut filter
int stjBQF_cascadeInitPeak (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biquad cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as peak filter
		float  				fs,		//!< (in) sample frequency
		float  				fc,		//!< (in) center frequency
		float				g,		//!< (in) gain
		float				q		//!< (in) quality
	);

//! initializes a element of the biquad cascade as low frequency shelving filter
int stjBQF_cascadeInitLowFreqShelving (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biquad cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as peak filter
		float  				fs,		//!< (in) sample frequency
		float  				f,		//!< (in) cut/boost frequency
		float				g		//!< (in) gain
	);

//! initializes a element of the biquad cascade as high frequency shelving filter
int stjBQF_cascadeInitHighFreqShelving (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biquad cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as peak filter
		float  				fs,		//!< (in) sample frequency
		float  				f,		//!< (in) cut/boost frequency
		float				g		//!< (in) gain
	);

//! initializes a element of the biquad cascade from a array with the coefficients
void stjBQF_initFromCoefficents (
		TstjBiquadCascade *	pBQC,			//!< (in/out) the biquad cascade
		int					index,			//!< (in) the index of the filter witch should be used as peak filter
		float				numerator [3],	//!< (in) n0 to n2
		float				denominator [3] //!< (in) d0 to d2
	);

//! gets from an element of the biquad cascade the coefficients
void stjBQF_getNumAndDenom (
		TstjBiquadCascade *	pBQC,			//!< (in/out) the biquad cascade
		int					index,			//!< (in) the index of the filter witch should be used as peak filter
		float *				pNumerator,		//!< (in) n0 to n2
		float *				pDenominator	//!< (in) d0 to d2
	);

#ifdef dstjBQF_implementPrintFunctions

#include <stdio.h>

// a simple print function (n0, n1, n2, d0, d1, d2)
void stjBQF_printBiquad(TstjBiquadCascade *pBC, FILE * stream);
#endif

// =================================================
// a generic biquad filter lib based on the math.h
// part II - implementations
// =================================================

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



#ifdef dstjBQF_UseFloatMath
	#define dStjBQFsqrt sqrtf
#else
	#define dStjBQFsqrt sqrt
#endif


TstjBQF_BiquadFloat _stjBQF_getK (float fs, float fc) {
#ifdef dstjBQF_UseFloatMath
	return tanf(M_PI*fc/fs);
#else
	return  tan(M_PI*fc/fs);
#endif
}

void _stjBQF_resetMemory(TstjBiquad * pBQ) {
	int i;
	for (i = 0; i < 2; i++) {
		pBQ->x[i] = 0.0f;
		pBQ->y[i] = 0.0f;
	}
}

//! creates a cascade of biquad filters
int stjBQF_cascadeCreate (
		TstjBiquadCascade *	pBQC,	//!< (in/out) pointer to a struct to be filled
		int 					num		//!< amount of filters
	) {
	int i, j;

	// alloc / realloc the biquad
	if (pBQC->num != num) {
		if (pBQC->pB) {
			free(pBQC->pB);
		}
		pBQC->pB = malloc (sizeof(TstjBiquad) * num);
		if (!pBQC->pB) {
			pBQC->num = 0;
			return -1;
		}
		pBQC->num = num;
	}

	// init data fields
	for (i = 0; i < num; i++) {
		for (j =0; j < 3; j++) pBQC->pB[i].a[j] = 0.0f;
		for (j =0; j < 2; j++) pBQC->pB[i].b[j] = 0.0f;
		for (j =0; j < 2; j++) pBQC->pB[i].x[j] = 0.0f;
		for (j =0; j < 2; j++) pBQC->pB[i].y[j] = 0.0f;
	}
	return 0;
}

//! deletes a cascade of biquad filters
void stjBQF_cascadeDelete (
		TstjBiquadCascade *	pBQC	//!< (in) pointer to a struct to be freed
	) {
	free (pBQC->pB);
	pBQC->pB = NULL;
	pBQC->num = 0;
}

//! convolut the input with the biquad filter cascade and generate the output (y = BQFc * x)
void stjBQF_cascadeConvolute (
		TstjBiquadCascade *	pBQC,	//!< (in) the biqaud cascade
		float * 				px,		//!< (in) input signal vector
		unsigned int			xNum,	//!< (in) amount of elements at the input vector
		float * 				py		//!< (out) output signal vector (size must be more or equal to px)
	) {
	int 		i, j;
	float 		y, x;
	TstjBiquad *pF;

	for (i = 0; i < xNum; i++) {
		x = *px;
		pF = pBQC->pB;
		for (j = 0; j < pBQC->num; j++) {
            y = pF->a[0] * x + pF->a[1] * pF->x[0] + pF->a[2]*pF->x[1] - pF->b[0] *pF->y[0] - pF->b[1]*pF->y[1];
            pF->x[1] = pF->x[0];
            pF->x[0] = x;
            pF->y[1] = pF->y[0];
            pF->y[0] = y;
			// output is input for the next filter
            x = y;
			pF++;
		}
		// save result to the output
		*py = y;
		px++;
		py++;
	}
}

//! initializes a element of the biquad cascade as high-pass(HP) filter
int stjBQF_cascadeInitHP (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biqaud cascade
		unsigned int		index,	//!< (in) the index of the filter witch should be used as HP
		float  				fs,		//!< (in) sample frequency
		float  				fc		//!< (in) cut off frequency
	) {
	TstjBQF_BiquadFloat K, denum;
	int i;

	if (index >= pBQC->num) {
		return -1;
	}

	K = _stjBQF_getK(fs, fc);
    denum = 1.0f + M_SQRT2*K + K*K;
    pBQC->pB[index].a[0] = 1.0f;
    pBQC->pB[index].a[1] = -2.0f;
    pBQC->pB[index].a[2] = 1.0f;
    for (i = 0; i < 3; i ++) {
    	pBQC->pB[index].a[i] /= denum;
    }

    pBQC->pB[index].b[0] = 2.0f * (K * K - 1.0f);
	pBQC->pB[index].b[1] = 1.0f - M_SQRT2 *K  + K * K;
    for (i = 0; i < 2; i ++) {
    	pBQC->pB[index].b[i] /= denum;
    }

    _stjBQF_resetMemory(&pBQC->pB[index]);
	return 0;
}

//! initializes a element of the biquad cascade as low-pass(LP) filter
int stjBQF_cascadeInitLP (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biqaud cascade
		unsigned int			index,	//!< (in) the index of the filter witch should be used as LP
		float  					fs,		//!< (in) sample frequency
		float  					fc		//!< (in) cut off frequency
	) {
	TstjBQF_BiquadFloat K, denum;
	int i;

	if (index >= pBQC->num) {
		return -1;
	}

	K = _stjBQF_getK(fs, fc);

    denum = 1.0f + M_SQRT2*K + K*K;
    pBQC->pB[index].a[0] = K * K;
    pBQC->pB[index].a[1] = 2.0f * K * K;
    pBQC->pB[index].a[2] = K * K;
    for (i = 0; i < 3; i ++) {
    	pBQC->pB[index].a[i] /= denum;
    }

    pBQC->pB[index].b[0] = 2.0f * (K * K - 1.0f);
    pBQC->pB[index].b[1] = 1.0f - M_SQRT2 *K  + K * K;
    for (i = 0; i < 2; i ++) {
    	pBQC->pB[index].b[i] /= denum;
    }

	_stjBQF_resetMemory(&pBQC->pB[index]);

	return 0;
}

//! initializes a element of the biquad cascade as peak boost/cut filter
int stjBQF_cascadeInitPeak (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biqaud cascade
		unsigned int			index,	//!< (in) the index of the filter witch should be used as peak filter
		float  					fs,		//!< (in) sample frequency
		float  					fc,		//!< (in) center frequency
		float					g,		//!< (in) gain
		float					q		//!< (in) quality
	) {
	TstjBQF_BiquadFloat K, V0, denum;
	int i;

	if (index >= pBQC->num) {
		return -1;
	}

	K = _stjBQF_getK(fs, fc);

	if (g > 0.0f) {
		V0 = (TstjBQF_BiquadFloat) g;
		denum = 1.0f + 1.0f / q * K + K * K;
		pBQC->pB[index].a[0] = 1.0f + V0 / q * K + K * K;
		pBQC->pB[index].a[1] = 2.0f * (K * K - 1.0f);
		pBQC->pB[index].a[2] = 1.0f - V0 / q * K + K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

		pBQC->pB[index].b[0] = 2.0f * (K * K - 1.0f);
		pBQC->pB[index].b[1] = 1.0f - 1.0f / q * K  + K * K;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }

	} else {
		V0 = -(TstjBQF_BiquadFloat)g;
		denum = 1.0f + V0 / q * K + K * K;
		pBQC->pB[index].a[0] = 1.0f +  1.0 / q * K + K * K;
		pBQC->pB[index].a[1] = 2.0f * (K * K - 1.0f);
		pBQC->pB[index].a[2] = 1.0f - 1.0f / q * K + K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

		pBQC->pB[index].b[0] = 2.0f * ( K * K - 1.0f);
		pBQC->pB[index].b[1] = 1.0f - V0 / q * K  + K * K;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }
	}
	_stjBQF_resetMemory(&pBQC->pB[index]);
	return 0;
}

//! initializes a element of the biquad cascade as low frequency shelving filter
int stjBQF_cascadeInitLowFreqShelving (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biqaud cascade
		unsigned int			index,	//!< (in) the index of the filter witch should be used as peak filter
		float  					fs,		//!< (in) sample frequency
		float  					f,		//!< (in) cut/boost frequency
		float					g		//!< (in) gain
	) {
	TstjBQF_BiquadFloat K, V0, denum;
	int i;

	if (index >= pBQC->num) {
		return -1;
	}

	K = _stjBQF_getK(fs, f);
	if (g > 0.0f) {
		V0 = (TstjBQF_BiquadFloat) g;
		denum = 1.0 + M_SQRT2* K + K * K;
		pBQC->pB[index].a[0] = 1.0f + dStjBQFsqrt(2.0f * V0) * K + V0 * K * K;
		pBQC->pB[index].a[1] = 2.0f * (V0 * K * K - 1.0f);
		pBQC->pB[index].a[2] = 1.0f - sqrt(2.0f * V0) * K + V0 * K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

		pBQC->pB[index].b[0] = 2.0f * (K * K - 1.0f);
		pBQC->pB[index].b[1] = 1.0f - M_SQRT2 * K  + K * K;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }

	} else {
		V0 = -(TstjBQF_BiquadFloat)g;
		denum = 1.0 + dStjBQFsqrt(2.0f * V0)* K + K * K;
		pBQC->pB[index].a[0] = 1.0f + M_SQRT2 * K + K * K;
		pBQC->pB[index].a[1] = 2.0f * (K * K - 1.0f);
		pBQC->pB[index].a[2] = 1.0f - M_SQRT2 * K + K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

		pBQC->pB[index].b[0] = 2.0f * (V0 * K * K - 1.0f);
		pBQC->pB[index].b[1] = 1.0f - dStjBQFsqrt(2.0f * V0) * K  + V0 * K * K;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }
	}

	_stjBQF_resetMemory(&pBQC->pB[index]);
	return 0;
}

//! initializes a element of the biquad cascade as high frequency shelving filter
int stjBQF_cascadeInitHighFreqShelving (
		TstjBiquadCascade *	pBQC,	//!< (in/out) the biqaud cascade
		unsigned int			index,	//!< (in) the index of the filter witch should be used as peak filter
		float  					fs,		//!< (in) sample frequency
		float  					f,		//!< (in) cut/boost frequency
		float					g		//!< (in) gain
	) {
	TstjBQF_BiquadFloat K, V0, denum;
	int i;

	if (index >= pBQC->num) {
		return -1;
	}

	K = _stjBQF_getK(fs, f);
	if (g > 0.0f) {
        V0 = (TstjBQF_BiquadFloat) g;
        denum = 1.0f + M_SQRT2* K + K * K;
        pBQC->pB[index].a[0] = V0 + dStjBQFsqrt(2.0f * V0) * K + K * K;
        pBQC->pB[index].a[1] = 2.0f * (K * K - V0);
        pBQC->pB[index].a[2] = V0 - dStjBQFsqrt(2.0f * V0) * K + K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

        pBQC->pB[index].b[0] = 2.0f * (K * K - 1.0f);
        pBQC->pB[index].b[1] = 1.0f - M_SQRT2 * K  + K * K;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }

	} else {
        V0 = -(TstjBQF_BiquadFloat)g;
        denum = V0 + dStjBQFsqrt(2.0f * V0)* K + K * K;
        pBQC->pB[index].a[0] = 1.0f + M_SQRT2 * K + K * K;
        pBQC->pB[index].a[1] = 2.0f * (K * K - 1.0);
        pBQC->pB[index].a[2] = 1.0f - M_SQRT2 * K + K * K;
	    for (i = 0; i < 3; i ++) {
	    	pBQC->pB[index].a[i] /= denum;
	    }

        denum = 1.0f + dStjBQFsqrt(2.0f / V0)* K + K * K / V0;
        pBQC->pB[index].b[0] = 2.0f * ( K * K / V0 - 1.0f);
        pBQC->pB[index].b[1] = 1.0f - dStjBQFsqrt(2.0f / V0) * K  + K * K / V0;
	    for (i = 0; i < 2; i ++) {
	    	pBQC->pB[index].b[i] /= denum;
	    }
	}
	_stjBQF_resetMemory(&pBQC->pB[index]);
	return 0;

}
#ifdef dstjBQF_implementPrintFunctions

// a simple print function (n0, n1, n2, d0, d1, d2)
void stjBQF_printBiquad(TstjBiquadCascade *pBC, FILE * stream) {
	int i,j;

	fprintf(stream,"BQC:\n");
	for (i = 0; i < pBC->num; i++) {
		fprintf(stream,"[%i]:\n",i);
		for (j = 0; j < 3; j++) {
			fprintf(stream,"\ta%i = %f\n",j,pBC->pB[i].a[j]);
		}
		fprintf(stream,"\tb0 = 1.0\n");
		for (j = 0; j < 2; j++) {
			fprintf(stream,"\tb%i = %f\n",j+1,pBC->pB[i].b[j]);
		}
	}
	fflush(stream);
}

#endif

// ===============================
// // extra code for group "delay (generic)"
// ===============================

// ============================================================================
// generic delay implementation (start)
// ============================================================================

// ============================================================================
// a generic i/o optimized implementation of a delayline
//
// it relies on the idea of a ringbuffer
// it is implemented by the use of read/write pointers
// features:
// - full ANSI C89 compatible
// - it doesn't use memmove, memcpy, malloc, free etc
// - it minimizes the amount of local variables
// - it precalculates wrapings and avoids if clauses (instruction cache friendly)
// - it minimizes read/write operation on the same memory cells and only
//  access the memory cells only once (data cache friendly)
// ============================================================================

// activate pointer check
#define dgenDelay_CheckPointer

//! a delay
typedef struct SgenDelay {
	float * pStart;	//!< starting pointer
	float *	pEnd;	//!< end pointer
	int		amount;	//!< amount of elements
	float * pR;		//!< read pointer
	float * pW;		//!< write pointer
} TgenDelay;

//! a enum type for the read / write flags
typedef enum EgenDelayRWflag {
	EgenDelayRWflag_readPointer = 0,			//!< only read pointer
	EgenDelayRWflag_writePointer = 1,			//!< only write pointer
	EgenDelayRWflag_readAndWritePointer = 2		//!< read & write pointer
} TgenDelayRWflag;

//! inits the delay
void genDelay_init (
		TgenDelay * 	pD,					//!< (in/out) pointer to a delay struct which is filled
		float * 		pStart,				//!< (in) pointer to the memory used to store the values
		int				amount,				//!< (in) amount of elements at the memory
		int				clearBufferFlag		//!< if not zero the buffer get overwritten with 0.0f
	) {
	// set pointers
	pD->pStart = pStart;
	pD->amount = amount;
	pD->pEnd = pStart + amount;
	pD->pW = pStart;
	pD->pR = pStart;
	if (clearBufferFlag) {
		// and the buffer to 0.0f
		float * pB = pStart;
		while (amount) {
			*pB = 0.0f;
			pB++;
			amount--;
		}
	}
}

//! creates the structure and the buffer for a delay
TgenDelay * genDelay_create (int amountOfSamples) {
	// malloc structure
	TgenDelay * pD = malloc(sizeof(TgenDelay));
	if (!pD) return NULL;
	if (amountOfSamples > 0) {
		// malloc data buffer
		pD->pStart = malloc(sizeof(float)*amountOfSamples);
		if (!pD->pStart) {
			free (pD);
			return NULL;
		}
		// reset structure
		genDelay_init(pD,pD->pStart,amountOfSamples, 1);
	} else {
		genDelay_init(pD,NULL,0, 0);
	}
	return pD;
}

//! deletes the delay structure and the contained data
void genDelay_delete (TgenDelay * pD) {
	if (!pD) return;
	if (pD->pStart) free(pD->pStart);
	free(pD);
}

//!
int genDelay_resize (TgenDelay * pD, int newBufferSize) {
	// null pointer exception
	if (!pD) return -1;
	// have we realy to alloc new memory?
	if (pD->amount == newBufferSize) goto init;
	// ok lets free the old one
	free (pD->pStart);
	// and alloc a new one
	pD->pStart = malloc(sizeof(float)*newBufferSize);
	// check if it worked
	if (!pD->pStart) {
		// no - ok lets make stable state and report an error
		genDelay_init(pD,NULL,0, 0);
		return -2;
	}
	// it worked lets init
init:
	genDelay_init(pD,pD->pStart,newBufferSize, 1);
	return 0;

}

// shuffle the read and/or write pointer
void genDelay_shuffle (
		TgenDelay * 	pD,			//!< (in/out) pointer to a delay struct
		TgenDelayRWflag	what,		//!< what defines what pointer is affected
		int				offset		//!< the offset of the R/W pointer
	) {
	int modf = offset % pD->amount;
	// read pointer
	if ((what == EgenDelayRWflag_readPointer) || (what == EgenDelayRWflag_readAndWritePointer)) {
		pD->pR += modf;
		if (pD->pR > pD->pEnd) {
			pD->pR = pD->pStart + (pD->pR - pD->pEnd);
		} else {
			if (pD->pR < pD->pStart) {
				pD->pR = pD->pEnd - (pD->pStart - pD->pR);
			}
		}
	}

	// write pointer
	if ((what == EgenDelayRWflag_writePointer) || (what == EgenDelayRWflag_readAndWritePointer)) {
		pD->pW += modf;
		if (pD->pW > pD->pEnd) {
			pD->pW = pD->pStart + (pD->pW - pD->pEnd);
		} else {
			if (pD->pW < pD->pStart) {
				pD->pW = pD->pEnd - (pD->pStart - pD->pW);
			}
		}
	}

}

//! writes a grain of values to the buffer
void genDelay_write (
		TgenDelay * 	pD,		//!< (in/out) pointer to a delay struct
		float * 		pSrc,	//!< (in) pointer to the values put into the delay
		int				N		//!< (in) amount of values to be stored
	) {
#ifdef dgenDelay_CheckPointer
	if ((!pD) || (!pD->pW) || (!pSrc)){
		return;
	}
#endif

	while (N) {
		// copy value
		*pD->pW = *pSrc;
		// inc src pointer
		pSrc++;
		// inc write pointer
		pD->pW++;
		// does we extends the border?
		if (pD->pW >= pD->pEnd) {
			// yes - ok lets wrap
			pD->pW = pD->pStart;
		}
		N--;
	}
}

//! reads a grain of values form the buffer
void genDelay_read (
		TgenDelay * 	pD,		//!< (in) pointer to a delay struct
		float * 		pDest,	//!< (in/out) pointer to which the values are stored
		int				N		//!< (in) amount of values to be stored
	) {
#ifdef dgenDelay_CheckPointer
	if ((!pD) || (!pD->pR) || (!pDest)){
		return;
	}
#endif

	while (N) {
		// copy value
		*pDest = *pD->pR;
		// inc src pointer
		pDest++;
		// inc read pointer
		pD->pR++;
		// does we extends the border?
		if (pD->pR >= pD->pEnd) {
			// yes - ok lets wrap
			pD->pR = pD->pStart;
		}
		N--;
	}
}

//! reads a grain of values form the buffer and copies the same amount into the buffer
void genDelay_readWrite (
		TgenDelay * 	pD,		//!< (in) pointer to a delay struct
		float *			pSrc,	//!< (in) a pointer from which the values should be copied
		float * 		pDest,	//!< (in/out) pointer to which the values are stored
		int				N		//!< (in) amount of values to be stored
	) {
	// 3 state approach to minimize the amount of i/o operations
	// 1st state read till we reach the write pointer or N is 0
	// 2nd state read & write till we read all data needed
	// 3th state write till all data is written

#ifdef dgenDelay_CheckPointer
	if ((!pD) || (!pD->pR) || (!pD->pW) || (!pDest) || (!pSrc)){
		return;
	}
#endif


	// wrap counter
	int wc;

	// read number
	int rn, rn2;
	// lets calculate how many read operations are needed to reach the write pointer
	// first check the position of the write pointer
	if (pD->pW >= pD->pR) {
		// the write pointer is in front of the read pointer
		rn = pD->pW - pD->pR;
	} else {
		// the write pointer stands after the read pointer
		rn = pD->amount - (pD->pR - pD->pW);
	}
	// trim
	if (rn > N) rn = N;
	rn2 = N - rn;

	// 1st state
	// 1.1. read till it wraps
	wc = pD->pEnd - pD->pR;
	if (wc > rn) wc = rn;
	rn -= wc;
	while (wc) {
		wc--;
		*pDest = *pD->pR;
		pDest++;
		pD->pR++;
	}
	// wrap if needed
	if (pD->pR >= pD->pEnd) pD->pR = pD->pStart;
	// 1.2 and read on
	while (rn) {
		rn --;
		*pDest = *pD->pR;
		pDest++;
		pD->pR++;
	}

	// 2nd state
	// the read/write operation
	// we use only the pD->pW pointer for the operation and increment the pD->pR only once
	// in rn2 are the remaining numbers stored
	pD->pR += rn2;
	N -= rn2;
	// wrap pR if needed
	if (pD->pR >= pD->pEnd) pD->pR = pD->pStart + (pD->pR - pD->pEnd);

	// get the wrap counter
	wc = pD->pEnd - pD->pW;
	if (wc > rn2) wc = rn2;

	// get the remaining number
	rn = rn2 - wc;

	// write & read
	while (wc) {
		wc--;
		*pDest = *pD->pW;
		*pD->pW = *pSrc;
		pDest++;
		pSrc++;
		pD->pW++;
	}
	// warp
	if (pD->pW >= pD->pEnd) pD->pW = pD->pStart;
	// write & read
	while (rn) {
		rn--;
		*pDest = *pD->pW;
		*pD->pW = *pSrc;
		pDest++;
		pSrc++;
		pD->pW++;
	}

	// 3th state
	// write the data
	// at N are the number of the remaining data

	// get the wrap counter
	wc = pD->pEnd - pD->pW;
	if (wc > N) wc = N;
	N -= wc;
	// write the data
	while (wc) {
		wc--;
		*pD->pW = *pSrc;
		pSrc++;
		pD->pW++;
	}
	// wrap
	if (pD->pW >= pD->pEnd) pD->pW = pD->pStart;
	// write the remaining data
	while (N) {
		N--;
		*pD->pW = *pSrc;
		pSrc++;
		pD->pW++;
	}

}

// ============================================================================
// generic delay implementation (end)
// ============================================================================



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
THALMsgProcessMessageAssociation const gHALMsgProcessRXHandlerArray [] = {
	{.msgID = 22, .pfktHandle = RX_run},
	{.msgID = 23, .pfktHandle = RX_updateVariable},
	{.msgID = 30, .pfktHandle = RX_login},
	{.msgID = 31, .pfktHandle = RX_logout}
};
// message RX global var
HALMsgProcessHandlerList const gHALMsgProcessRXHandlers = {
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

// audio processor blueprint with uuid=10
// description: a super generic AP with multiple threads

// ===============================
// AP uuid = 10
// ===============================


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
	// logout form all other devices
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

	pthread_mutex_init ( &(pIP->gM), NULL);

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

	// setup cpu
	APInterpreterReset(IP);
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

// HAL variable implementation for integer
// HAL descr: a integer number
// implementation descr: super generic integer
// here goes the implementation
// ===============================
// variable implementation for a integer number(var id = 2)
// ===============================

// updates a variable the AP
int HALimpl_2_recvUpdate (void * pVarData, void * pMsgData) {
	uint32_t * pD = (uint32_t *) pMsgData;
	TAPgenericIntegerVector * pIV = pVarData;
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	int imax = (int) *((int32_t *)pD);

	int i;

	if (APgenericIntegerVector_resize(pIV,imax)) {
		return -1;
	}

	pD++;

	for (i = 0; i < imax; i++) {
		APendianConversation32Bit(pD,eAP_littleEndian);
		pIV->pVal[i] = *((int32_t *)pD);
		pD++;
	}
	return 0;
}

// create a new variable
void * HALimpl_2_create (unsigned int numberOfElements) {
	return APgenericIntegerVector_create((int)numberOfElements);
}
// updates the vars at the other APs
int HALimpl_2_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
	TAPgenericIntegerVector * pIV = pVarData;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	int32_t dataAmount = 1 + pIV->num;
	int32_t dummy;
	int indx;
	// send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	// send amount of elements
	dummy = (int32_t) pIV->num;
	pMD->pfkt_sendInteger32(pMD,1,&dummy);
	// send elements
	for (indx = 0; indx < pIV->num; indx++) {
		pMD->pfkt_sendInteger32(pMD,1,&pIV->pVal[indx]);
	}
	return 0;
}
// decode data for the HAL functions
void * HALimpl_2_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_2_delete (void * pVarData) {
	APgenericIntegerVector_destroy(pVarData);
}

// HAL variable implementation for rational
// HAL descr: a rational number
// implementation descr: super generic rational
// here goes the implementation
// ===============================
// variable implementation for a rational number(var id = 1)
// ===============================

// updates a variable the AP
int HALimpl_1_recvUpdate (void * pVarData, void * pMsgData) {
	uint32_t * pD = (uint32_t *) pMsgData;
	TAPgenericRationalVector * pIV = pVarData;
	
	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	APendianConversation32Bit(pD,eAP_littleEndian);
	int imax = (int) *((int32_t *)pD);
	int i;

	if (APgenericRationalVector_resize(pIV,imax)) {
		return -1;
	}

	pD++;

	for (i = 0; i < imax; i++) {
		pIV->pVal[i] = *((float *)pD);
		pD++;
	}
	return 0;
}
// create a new variable
void * HALimpl_1_create (unsigned int numberOfElements) {
	return APgenericRationalVector_create((int)numberOfElements);
}
// updates the vars at the other APs
int HALimpl_1_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
	TAPgenericRationalVector * pRV = pVarData;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;
	int32_t dataAmount = (int32_t) 1 + pRV->num;
	int32_t dummy;
	// send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
	// send amount of elements
	dummy = (int32_t) pRV->num;
	pMD->pfkt_sendInteger32(pMD,1,&dummy);
	// send elements
	pMD->pfkt_sendFloat32(pMD,pRV->num,pRV->pVal);
	return 0;
}
// decode data for the HAL functions
void * HALimpl_1_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_1_delete (void * pVarData) {
	APgenericRationalVector_destroy(pVarData);
}

// HAL variable implementation for string
// HAL descr: a string
// implementation descr: string based on stdlib
// here goes the implementation
// ===============================
// variable implementation for a string(var id = 3)
// ===============================

// updates a variable the AP
int HALimpl_3_recvUpdate (void * pVarData, void * pMsg) {
	int32_t *			pD = (int32_t *) pMsg;
	TAPstringVector *	pSV = pVarData;
	TAPstring *			ps;
	int					i, num,imax;

	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	//1. get amount of strings at the string vector
	APendianConversation32Bit((uint32_t *)pD,eAP_littleEndian);
	num = (int) *pD;

	if (APstringVector_resizeVector(pSV,num)) {
		return -1;
	}

	pD++;
	ps = pSV->sv;
	//2. resize and fill the strings
	for (i = 0; i < num; i++) {
		// get length
		APendianConversation32Bit((uint32_t *)pD,eAP_littleEndian);
		if (APstringVector_resize(pSV,i,(size_t)*pD)) {
			return -2;
		}
		imax = (int) *pD;
		pD++;
		for (i = 0;i <imax; i++)  {
			ps->szTxt[i] = (char) *pD;
			pD++;
		}
		ps->szTxt[i] = 0;
		ps++;
	}
	return 0;
}
// create a new variable
void * HALimpl_3_create (unsigned int numberOfElements) {
	return APstringVector_create((int)numberOfElements);
}
// updates the vars at the other APs
int HALimpl_3_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
	// msgdata = (stringAmount)[(strlen)(string + fill byes), ...]
	// some vars
	unsigned int		indx;
	int 				stl;
	TAPstring * 		ps;
	TAPstringVector * 	pSV = (TAPstringVector *)pVarData;
	TAPMsgDrv * 		pMD = (TAPMsgDrv *) pDrv;
	int32_t 			uint32Amount = 1; // vector size
	int32_t				sendVal;
	char *				psz;
	// ok get the size of the message
	ps = pSV->sv;
	for (indx = 0;indx < pSV->num; indx++) {
		// one element for the length
		uint32Amount++;
		// the string data
		stl = ps->szTxt ? strlen(ps->szTxt) : 0;
		uint32Amount+=stl;
		// next string
		ps++;
	}
	// send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, uint32Amount);
	// send amount of elements
	sendVal = (int32_t) pSV->num;
	pMD->pfkt_sendInteger32(pMD,1,&sendVal);
	ps = pSV->sv;
	for (indx = 0; indx < pSV->num; indx++) {
		if (ps->szTxt) {
			// get length
			sendVal = (int32_t) strlen(ps->szTxt);
			// send length
			pMD->pfkt_sendInteger32(pMD,1,&sendVal);
			// send string
			psz = ps->szTxt;
			while (*psz) {
				sendVal = (int32_t) *psz;
				pMD->pfkt_sendInteger32(pMD,1,&sendVal);
				psz++;
			}
		} else {
			sendVal = 0;
			// send length
			pMD->pfkt_sendInteger32(pMD,1,&sendVal);
		}
		ps++;
	}
	return 0;
}
// decode data for the HAL functions
void * HALimpl_3_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_3_delete (void * pVarData) {
	APstringVector_free(pVarData);
}

// HAL variable implementation for biquad
// HAL descr: a biquad filter
// implementation descr: super generic biquad
// here goes the implementation
// ===============================
// variable implementation for a biquad filter(var id = 10)
// ===============================

// updates a variable the AP
int HALimpl_10_recvUpdate (void * pVarData, void * pMsgData) {
	uint32_t * pD = (uint32_t *) pMsgData;
	TstjBiquadCascade * pV =(TstjBiquadCascade *) pVarData;
	TstjBiquad * pE;
	int i,j, imax;


	// at the first possion at the message is the global var index
	pD++; // skip it (it's the varindex)
	// and now we are at amount of values
	if (gAPendianFlag != eAP_littleEndian) {
		APendianConversation32Bit(pD,eAP_littleEndian);
	}
	imax = (int) *((int32_t *)pD);
	pD++;
	// 1. resize vector if needed
	if (pV->num != imax) {
		if (stjBQF_cascadeCreate(pV,imax)) {
			return -1;
		}
	}

	// 2. fill parameters
	pE = pV->pB;
	for (i = 0; i < imax; i++) {
		// read a
		for (j = 0; j < 3; j++) {
			pE->a[j] = *((float *)pD);
			pD++;
		}
		// read b
		for (j = 0; j < 2; j++) {
			pE->b[j] = *((float *)pD);
			pD++;
		}
		// reset memory
		for (j = 0; j < 2; j++) {
			pE->x[j] = 0.0f;
			pE->y[j] = 0.0f;
		}
		pE++;
	}
#ifdef dBQF_implementPrintFunctions
	fprintf(stdout,"rx biquad:\n")
	BQF_PrintBiquad(pV,stdout);
	fflush(stdout);
#endif
	return 0;
}

// create a new variable
void * HALimpl_10_create (unsigned int numberOfElements) {
	TstjBiquadCascade * pBC = malloc(sizeof(TstjBiquadCascade));
	if (!pBC) return NULL;
	pBC->num = 0;
	pBC->pB = NULL;
	if (stjBQF_cascadeCreate(pBC, numberOfElements)) {
		free(pBC);
		return NULL;
	}
	return pBC;
}

// updates the vars at the other APs
int HALimpl_10_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
	TstjBiquadCascade * pV =(TstjBiquadCascade *) pVarData;
	TstjBiquad * pE;
	TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;

	int32_t dataAmount;
	int32_t n;

	// calc amount of transmission bytes
	dataAmount = (int32_t) 1 + pV->num * 5;

	// 1 send header
	pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);

	// 2 send vector elementwise

	// 2.1 send amount of elements at the vector
	pMD->pfkt_sendInteger32(pMD,1,&pV->num);

	// 2.2 send element
	pE = pV->pB;
	for (n = 0; n < pV->num; n++) {
		pMD->pfkt_sendFloat32(pMD,3,pE->a);
		pMD->pfkt_sendFloat32(pMD,2,pE->b);
		// inc
		pE++;
	}
#ifdef dBQF_implementPrintFunctions
	fprintf(stdout,"tx biquad:\n")
	stjBQF_printBiquad(pV,stdout);
	fflush(stdout);
#endif

	return 0;
}
// decode data for the HAL functions
void * HALimpl_10_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_10_delete (void * pVarData) {
	TstjBiquadCascade * pBC = (TstjBiquadCascade *) pVarData;
	if (pBC) {
		stjBQF_cascadeDelete(pBC);
		free (pBC);
	}
}
// HAL variable implementation for panel
// HAL descr: panel UI
// implementation descr: panel type in gtk+ style
// here goes the implementation
// ===============================
// variable implementation for panel UI(var id = 100)
// ===============================

// updates a variable the AP
int HALimpl_100_recvUpdate (void * pVarData, void * pMsg) {
	return -1;
}
// create a new variable
void * HALimpl_100_create (unsigned int numberOfElements) {
	return APgtkUI_createVector(numberOfElements, eAPgtkUItype_panel);
}
// updates the vars at the other APs
int HALimpl_100_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
	return -1;
}
// decode data for the HAL functions
void * HALimpl_100_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_100_delete (void * pVarData) {
	APgtkUI_destroyVector(pVarData);
}

// HAL variable implementation for button
// HAL descr: button UI
// implementation descr: button type in gtk+ style
// here goes the implementation
// ===============================
// variable implementation for button UI(var id = 101)
// ===============================

// updates a variable the AP
int HALimpl_101_recvUpdate (void * pVarData, void * pMsg) {
return -1;
}
// create a new variable
void * HALimpl_101_create (unsigned int numberOfElements) {
	return APgtkUI_createVector(numberOfElements, eAPgtkUItype_button);
}

// updates the vars at the other APs
int HALimpl_101_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
return -1;
}
// decode data for the HAL functions
void * HALimpl_101_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_101_delete (void * pVarData) {
	APgtkUI_destroyVector(pVarData);
}
// HAL variable implementation for led
// HAL descr: led UI
// implementation descr: LED type in gtk+ style
// here goes the implementation
// ===============================
// variable implementation for led UI(var id = 102)
// ===============================

// updates a variable the AP
int HALimpl_102_recvUpdate (void * pVarData, void * pMsg) {
return -1;
}
// create a new variable
void * HALimpl_102_create (unsigned int numberOfElements) {
	return APgtkUI_createVector(numberOfElements, eAPgtkUItype_LED);
}
// updates the vars at the other APs
int HALimpl_102_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
return -1;
}
// decode data for the HAL functions
void * HALimpl_102_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_102_delete (void * pVarData) {
	APgtkUI_destroyVector(pVarData);
}

// HAL variable implementation for display
// HAL descr: display UI
// implementation descr: display type in gtk+ style
// here goes the implementation
// ===============================
// variable implementation for display UI(var id = 103)
// ===============================

// updates a variable the AP
int HALimpl_103_recvUpdate (void * pVarData, void * pMsg) {
return -1;
}
// create a new variable
void * HALimpl_103_create (unsigned int numberOfElements) {
	return APgtkUI_createVector(numberOfElements, eAPgtkUItype_display);
}
// updates the vars at the other APs
int HALimpl_103_sendUpdate (void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i) {
return -1;
}
// decode data for the HAL functions
void * HALimpl_103_decodeData (void * pVarData) {
	return pVarData;
}
// delete the variable
void HALimpl_103_delete (void * pVarData) {
	APgtkUI_destroyVector(pVarData);
}
// global HAL variable info variables
THAL_Variable const gHALvariableInfo [] = {
    // HAL variable info for integer (2)
	{
	    .id = 2,
	    .pFkt_recvUpdate = HALimpl_2_recvUpdate,
		.pFkt_create = HALimpl_2_create,
		.pFkt_sendUpdate = HALimpl_2_sendUpdate,
		.pFkt_decodeData = HALimpl_2_decodeData,
		.pFkt_delete = HALimpl_2_delete
	},
	// HAL variable info for rational (1)
	{
	    .id = 1,
	    .pFkt_recvUpdate = HALimpl_1_recvUpdate,
		.pFkt_create = HALimpl_1_create,
		.pFkt_sendUpdate = HALimpl_1_sendUpdate,
		.pFkt_decodeData = HALimpl_1_decodeData,
		.pFkt_delete = HALimpl_1_delete
	},
	// HAL variable info for string (3)
	{
	    .id = 3,
	    .pFkt_recvUpdate = HALimpl_3_recvUpdate,
		.pFkt_create = HALimpl_3_create,
		.pFkt_sendUpdate = HALimpl_3_sendUpdate,
		.pFkt_decodeData = HALimpl_3_decodeData,
		.pFkt_delete = HALimpl_3_delete
	},
	// HAL variable info for biquad (10)
	{
	    .id = 10,
	    .pFkt_recvUpdate = HALimpl_10_recvUpdate,
		.pFkt_create = HALimpl_10_create,
		.pFkt_sendUpdate = HALimpl_10_sendUpdate,
		.pFkt_decodeData = HALimpl_10_decodeData,
		.pFkt_delete = HALimpl_10_delete
	},
	// HAL variable info for panel (100)
	{
	    .id = 100,
	    .pFkt_recvUpdate = HALimpl_100_recvUpdate,
		.pFkt_create = HALimpl_100_create,
		.pFkt_sendUpdate = HALimpl_100_sendUpdate,
		.pFkt_decodeData = HALimpl_100_decodeData,
		.pFkt_delete = HALimpl_100_delete
	},
	// HAL variable info for button (101)
	{
	    .id = 101,
	    .pFkt_recvUpdate = HALimpl_101_recvUpdate,
		.pFkt_create = HALimpl_101_create,
		.pFkt_sendUpdate = HALimpl_101_sendUpdate,
		.pFkt_decodeData = HALimpl_101_decodeData,
		.pFkt_delete = HALimpl_101_delete
	},
	// HAL variable info for led (102)
	{
	    .id = 102,
	    .pFkt_recvUpdate = HALimpl_102_recvUpdate,
		.pFkt_create = HALimpl_102_create,
		.pFkt_sendUpdate = HALimpl_102_sendUpdate,
		.pFkt_decodeData = HALimpl_102_decodeData,
		.pFkt_delete = HALimpl_102_delete
	},
	// HAL variable info for display (103)
	{
	    .id = 103,
	    .pFkt_recvUpdate = HALimpl_103_recvUpdate,
		.pFkt_create = HALimpl_103_create,
		.pFkt_sendUpdate = HALimpl_103_sendUpdate,
		.pFkt_decodeData = HALimpl_103_decodeData,
		.pFkt_delete = HALimpl_103_delete
	}
};

THAL_VariableList const gHALVariableList = {gHALvariableInfo,8};


// ===============================
// HAL functions
// ===============================

// HAL function implementation for setStringSize
// HAL descr: resets the size of a string
// implementation descr: setup string
// here goes the implementation
// ===============================
// function implementation for setStringSize(var id = 5)
// description: resets the size of a string
// ===============================

void HALfunc_ID5_setStringSize(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s descr: the string
	TAPstringVector * pSV = (TAPstringVector *) pParams[0].fp_pV;
// parameter i descr: index of the string at the array
	int32_t i = pParams[1].fp_integer;
// parameter length descr: length of the string
	int32_t length = pParams[2].fp_integer;

	if (APstringVector_resize(pSV,(int) i, length)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for setStringSize (5)
THALFunctionParam const gpHALFunctionParam_5_setStringSize [] = { // name: s descr: the string
	{.paramClass = 3, .paramTypeID = 3},
	// name: i descr: index of the string at the array
	{.paramClass = 1, .paramTypeID = 2},
	// name: length descr: length of the string
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for setStringValues
// HAL descr: set the string
// implementation descr: set string chars
// here goes the implementation
// ===============================
// function implementation for setStringValues(var id = 6)
// description: set the string
// ===============================

void HALfunc_ID6_setStringValues(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s descr: the string
	TAPstringVector * pSV = (TAPstringVector *) pParams[0].fp_pV;
// parameter i descr: index of the string at the array
	int i = (int) pParams[1].fp_integer;
// parameter p descr: position at the string where to start from
	int p = (int) pParams[2].fp_integer;

	char * pSrc =(char *) &pParams[3].fp_raw;

	int pe = p + (dAPInterpreterFuncMaxParams-3) * sizeof(int32_t);
	
	APstringVector_fill(pSV,i,p,pe,pSrc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for setStringValues (6)
THALFunctionParam const gpHALFunctionParam_6_setStringValues [] = { // name: s descr: the string
	{.paramClass = 3, .paramTypeID = 3},
	// name: i descr: index of the string at the array
	{.paramClass = 1, .paramTypeID = 2},
	// name: p descr: position at the string where to start from
	{.paramClass = 1, .paramTypeID = 2},
	// name: v1 descr: chars coded as 4 byte integer
	{.paramClass = 1, .paramTypeID = 4},
	// name: v2 descr: chars coded as 4 byte integer
	{.paramClass = 1, .paramTypeID = 4},
	// name: v3 descr: chars coded as 4 byte integer
	{.paramClass = 1, .paramTypeID = 4},
	// name: v4 descr: chars coded as 4 byte integer
	{.paramClass = 1, .paramTypeID = 4}
};
// HAL function implementation for concatStrings
// HAL descr: concat two strings
// implementation descr: concat two strings s1 & s2 -> s1
// here goes the implementation
// ===============================
// function implementation for concatStrings(var id = 7)
// description: concat two strings
// ===============================
void HALfunc_ID7_concatStrings(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s1 descr: the string at its end the other string is concated
	TAPstringVector * s1 = (TAPstringVector *) pParams[0].fp_pD;
// parameter i1 descr: index of the string 1
	int i1 = (int) pParams[1].fp_integer;
// parameter s2 descr: the concat string
	TAPstringVector * s2 = (TAPstringVector *) pParams[2].fp_pD;
// parameter i2 descr: index of the string 2
	int i2 = (int) pParams[3].fp_integer;

	if (APstringVector_concat(s1,i1,s2,i2)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for concatStrings (7)
THALFunctionParam const gpHALFunctionParam_7_concatStrings [] = { // name: s1 descr: the string at its end the other string is concated
	{.paramClass = 3, .paramTypeID = 3},
	// name: i1 descr: index of the string 1
	{.paramClass = 1, .paramTypeID = 2},
	// name: s2 descr: the concat string
	{.paramClass = 3, .paramTypeID = 3},
	// name: i2 descr: index of the string 2
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for rationalToString
// HAL descr: converts a rational to a string
// implementation descr: converts a rational to a string(size of the string is keept untouched)
// here goes the implementation
// ===============================
// function implementation for rationalToString(var id = 8)
// description: converts a rational to a string
// ===============================
void HALfunc_ID8_rationalToString(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s descr: the string
	TAPstringVector * s = (TAPstringVector *) pParams[0].fp_pD;
// parameter sIndex descr: index of the string at the array
	int sIndex = (int) pParams[1].fp_integer;
// parameter r descr: rational vector
	TAPgenericRationalVector * r = (TAPgenericRationalVector *) pParams[2].fp_pD;
// parameter rIndx descr: rational vector index
	int rIndx = (int) pParams[3].fp_integer;

	APstringVector_printFloat(s, sIndex, r->pVal[rIndx]);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for rationalToString (8)
THALFunctionParam const gpHALFunctionParam_8_rationalToString [] = { // name: s descr: the string
	{.paramClass = 3, .paramTypeID = 3},
	// name: sIndex descr: index of the string at the array
	{.paramClass = 1, .paramTypeID = 2},
	// name: r descr: rational vector
	{.paramClass = 3, .paramTypeID = 1},
	// name: rIndx descr: rational vector index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for integerToString
// HAL descr: converts an integer to a string
// implementation descr: converts a integer to a string(size of the string is keept untouched)
// here goes the implementation
// ===============================
// function implementation for integerToString(var id = 9)
// description: converts an integer to a string
// ===============================
void HALfunc_ID9_integerToString(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s descr: the string
	TAPstringVector * s = (TAPstringVector *) pParams[0].fp_pD;
// parameter sIndex descr: index of the string at the array
	int sIndex = (int) pParams[1].fp_integer;
// parameter i descr: integer vector
	TAPgenericIntegerVector * i = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter iIndex descr: integer vector indx
	int iIndex = (int) pParams[3].fp_integer;

	APstringVector_printInt(s, sIndex, i->pVal[iIndex]);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for integerToString (9)
THALFunctionParam const gpHALFunctionParam_9_integerToString [] = { // name: s descr: the string
	{.paramClass = 3, .paramTypeID = 3},
	// name: sIndex descr: index of the string at the array
	{.paramClass = 1, .paramTypeID = 2},
	// name: i descr: integer vector
	{.paramClass = 3, .paramTypeID = 2},
	// name: iIndex descr: integer vector indx
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for assignString
// HAL descr: assigns a string to an other
// implementation descr: assigns a string to an other
// here goes the implementation
// ===============================
// function implementation for assignString(var id = 10)
// description: assigns a string to an other
// ===============================
void HALfunc_ID10_assignString(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter s1 descr: the string at its end the other string is concated
	TAPstringVector * s1 = (TAPstringVector *) pParams[0].fp_pD;
// parameter i1 descr: index of the string 1
	int i1 = (int) pParams[1].fp_integer;
// parameter s2 descr: the concat string
	TAPstringVector * s2 = (TAPstringVector *) pParams[2].fp_pD;
// parameter i2 descr: index of the string 2
	int i2 = (int) pParams[3].fp_integer;

	if (APstringVector_assign(s1,i1,s2,i2)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}

};

// function info for assignString (10)
THALFunctionParam const gpHALFunctionParam_10_assignString [] = { // name: s1 descr: the source string
	{.paramClass = 3, .paramTypeID = 3},
	// name: i1 descr: index of the string 1
	{.paramClass = 1, .paramTypeID = 2},
	// name: s2 descr: the destination string
	{.paramClass = 3, .paramTypeID = 3},
	// name: i2 descr: index of the string 2
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for assignConstInteger
// HAL descr: a = values
// implementation descr: a = const val
// here goes the implementation
// ===============================
// function implementation for assignConstInteger(var id = 20)
// description: a = values
// ===============================

void HALfunc_ID20_assignConstInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter iv descr: integer vector
	TAPgenericIntegerVector * piv = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter iStart descr: start index
	int32_t iStart = pParams[1].fp_integer;
// parameter num descr: number of values
	int32_t num = pParams[2].fp_integer;

	int32_t * pSrc =(int32_t *) &pParams[3].fp_raw;

	APgenericIntegerVector_assignConst(piv, (int)iStart, (int)num, pSrc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for assignConstInteger (20)
THALFunctionParam const gpHALFunctionParam_20_assignConstInteger [] = { // name: iv descr: integer vector
	{.paramClass = 3, .paramTypeID = 2},
	// name: iStart descr: start index
	{.paramClass = 1, .paramTypeID = 2},
	// name: num descr: amount of values used
	{.paramClass = 1, .paramTypeID = 2},
	// name: v1 descr: value 1
	{.paramClass = 1, .paramTypeID = 2},
	// name: v2 descr: value 2
	{.paramClass = 1, .paramTypeID = 2},
	// name: v3 descr: value 3
	{.paramClass = 1, .paramTypeID = 2},
	// name: v4 descr: value 4
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for assignInteger
// HAL descr: a = b
// implementation descr: a = b
// here goes the implementation
// ===============================
// function implementation for assignInteger(var id = 21)
// description: a = b
// ===============================

void HALfunc_ID21_assignInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;

	APgenericIntegerVector_assign(pa, pb);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for assignInteger (21)
THALFunctionParam const gpHALFunctionParam_21_assignInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for addInteger
// HAL descr: c = a + b
// implementation descr: c = a + b
// here goes the implementation
// ===============================
// function implementation for addInteger(var id = 22)
// description: c = a + b
// ===============================

void HALfunc_ID22_addInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericIntegerVector* pc = (TAPgenericIntegerVector *)pParams[2].fp_pD;

	APgenericIntegerVector_add(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for addInteger (22)
THALFunctionParam const gpHALFunctionParam_22_addInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for subInteger
// HAL descr: c = a - b
// implementation descr: c = a - b
// here goes the implementation
// ===============================
// function implementation for subInteger(var id = 23)
// description: c = a - b
// ===============================

void HALfunc_ID23_subInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericIntegerVector* pc = (TAPgenericIntegerVector *)pParams[2].fp_pD;

	APgenericIntegerVector_sub(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for subInteger (23)
THALFunctionParam const gpHALFunctionParam_23_subInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for mulInteger
// HAL descr: c = a * b
// implementation descr: c = a * b
// here goes the implementation
// ===============================
// function implementation for mulInteger(var id = 24)
// description: c = a * b
// ===============================

void HALfunc_ID24_mulInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericIntegerVector* pc = (TAPgenericIntegerVector *)pParams[2].fp_pD;

	APgenericIntegerVector_mul(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for mulInteger (24)
THALFunctionParam const gpHALFunctionParam_24_mulInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for divInteger
// HAL descr: c = a / b
// implementation descr: c = a / b
// here goes the implementation
// ===============================
// function implementation for divInteger(var id = 25)
// description: c = a / b
// ===============================

void HALfunc_ID25_divInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericIntegerVector* pc = (TAPgenericIntegerVector *)pParams[2].fp_pD;

	APgenericIntegerVector_div(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for divInteger (25)
THALFunctionParam const gpHALFunctionParam_25_divInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for modInteger
// HAL descr: c = mod(a,b)
// implementation descr: c = modulo(a ,b)
// here goes the implementation
// ===============================
// function implementation for modInteger(var id = 26)
// description: c = mod(a,b)
// ===============================

void HALfunc_ID26_modInteger(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericIntegerVector* pb = (TAPgenericIntegerVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericIntegerVector* pc = (TAPgenericIntegerVector *)pParams[2].fp_pD;

	APgenericIntegerVector_mod(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for modInteger (26)
THALFunctionParam const gpHALFunctionParam_26_modInteger [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 2},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 2},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerLess
// HAL descr: a < b ? CF = 1 : CF = 0
// implementation descr: a<b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerLess(var id = 40)
// description: a < b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID40_compareIntegerLess(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) < 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareIntegerLess (40)
THALFunctionParam const gpHALFunctionParam_40_compareIntegerLess [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerMore
// HAL descr: a > b ? CF = 1 : CF = 0
// implementation descr: a>b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerMore(var id = 41)
// description: a > b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID41_compareIntegerMore(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) > 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareIntegerMore (41)
THALFunctionParam const gpHALFunctionParam_41_compareIntegerMore [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerEqual
// HAL descr: a == b ? CF = 1 : CF = 0
// implementation descr: a==b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerEqual(var id = 42)
// description: a == b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID42_compareIntegerEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) == 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareIntegerEqual (42)
THALFunctionParam const gpHALFunctionParam_42_compareIntegerEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerNEqual
// HAL descr: a != b ? CF = 1 : CF = 0
// implementation descr: a<>b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerNEqual(var id = 43)
// description: a != b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID43_compareIntegerNEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) != 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;

};

// function info for compareIntegerNEqual (43)
THALFunctionParam const gpHALFunctionParam_43_compareIntegerNEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerLessEqual
// HAL descr: a <= b ? CF = 1 : CF = 0
// implementation descr: a<=b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerLessEqual(var id = 44)
// description: a <= b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID44_compareIntegerLessEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) > 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareIntegerLessEqual (44)
THALFunctionParam const gpHALFunctionParam_44_compareIntegerLessEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareIntegerMoreEqual
// HAL descr: a >= b ? CF = 1 : CF = 0
// implementation descr: a=>b
// here goes the implementation
// ===============================
// function implementation for comparaIntegerMoreEqual(var id = 45)
// description: a >= b ? CF = 1 : CF = 0
// ===============================

void HALfunc_ID45_compareIntegerMoreEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: a vector
	TAPgenericIntegerVector * pa = (TAPgenericIntegerVector *) pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: b vector
	TAPgenericIntegerVector * pb = (TAPgenericIntegerVector *) pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericIntegerVector_cmpEle(pa, pb, ia, ib) < 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareIntegerMoreEqual (45)
THALFunctionParam const gpHALFunctionParam_45_compareIntegerMoreEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 2},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for assignConstRational
// HAL descr: a = values
// implementation descr: a = const val
// here goes the implementation
// ===============================
// function implementation for assignConstRational(var id = 27)
// description: a = values
// ===============================
void HALfunc_ID27_assignConstRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter iv descr: rational vector
	TAPgenericRationalVector * piv = (TAPgenericRationalVector *) pParams[0].fp_pD;
// parameter iStart descr: start index
	int32_t iStart = pParams[1].fp_integer;
// parameter num descr: amount of values used
	int32_t num = pParams[2].fp_integer;

	float * pSrc =(float *) &pParams[3].fp_raw;

	APgenericRationalVector_assignConst (piv, (int)iStart, (int)num, pSrc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for assignConstRational (27)
THALFunctionParam const gpHALFunctionParam_27_assignConstRational [] = { // name: iv descr: rational vector
	{.paramClass = 3, .paramTypeID = 1},
	// name: iStart descr: start index
	{.paramClass = 1, .paramTypeID = 2},
	// name: num descr: amount of values used
	{.paramClass = 1, .paramTypeID = 2},
	// name: v1 descr: value 1
	{.paramClass = 1, .paramTypeID = 1},
	// name: v2 descr: value 2
	{.paramClass = 1, .paramTypeID = 1},
	// name: v3 descr: value 3
	{.paramClass = 1, .paramTypeID = 1},
	// name: v4 descr: value 4
	{.paramClass = 1, .paramTypeID = 1}
};
// HAL function implementation for assignRational
// HAL descr: a = b
// implementation descr: a = b
// here goes the implementation
// ===============================
// function implementation for assignRational(var id = 28)
// description: a = b
// ===============================
void HALfunc_ID28_assignRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[1].fp_pD;

	APgenericRationalVector_assign(pa, pb);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;

};

// function info for assignRational (28)
THALFunctionParam const gpHALFunctionParam_28_assignRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for addRational
// HAL descr: c = a + b
// implementation descr: c = a + b
// here goes the implementation
// ===============================
// function implementation for addRational(var id = 29)
// description: c = a + b
// ===============================
void HALfunc_ID29_addRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector * pb = (TAPgenericRationalVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericRationalVector * pc = (TAPgenericRationalVector *)pParams[2].fp_pD;

	APgenericRationalVector_add(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for addRational (29)
THALFunctionParam const gpHALFunctionParam_29_addRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for subRational
// HAL descr: c = a - b
// implementation descr: c = a - b
// here goes the implementation
// ===============================
// function implementation for subRational(var id = 30)
// description: c = a - b
// ===============================
void HALfunc_ID30_subRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector * pb = (TAPgenericRationalVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericRationalVector * pc = (TAPgenericRationalVector *)pParams[2].fp_pD;

	APgenericRationalVector_sub(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for subRational (30)
THALFunctionParam const gpHALFunctionParam_30_subRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for mulRational
// HAL descr: c = a * b
// implementation descr: c = a * b
// here goes the implementation
// ===============================
// function implementation for mulRational(var id = 31)
// description: c = a * b
// ===============================
void HALfunc_ID31_mulRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector * pb = (TAPgenericRationalVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericRationalVector * pc = (TAPgenericRationalVector *)pParams[2].fp_pD;

	APgenericRationalVector_mul(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for mulRational (31)
THALFunctionParam const gpHALFunctionParam_31_mulRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for divRational
// HAL descr: c = a / b
// implementation descr: c = a / b
// here goes the implementation
// ===============================
// function implementation for divRational(var id = 32)
// description: c = a / b
// ===============================
void HALfunc_ID32_divRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector * pb = (TAPgenericRationalVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericRationalVector * pc = (TAPgenericRationalVector *)pParams[2].fp_pD;

	APgenericRationalVector_div(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for divRational (32)
THALFunctionParam const gpHALFunctionParam_32_divRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for modRational
// HAL descr: c = mod(a,b)
// implementation descr: c = modulo(a ,b)
// here goes the implementation
// ===============================
// function implementation for modRational(var id = 33)
// description: c = mod(a,b)
// ===============================
void HALfunc_ID33_modRational(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter b descr: vector b
	TAPgenericRationalVector * pb = (TAPgenericRationalVector *)pParams[1].fp_pD;
// parameter c descr: vector c
	TAPgenericRationalVector * pc = (TAPgenericRationalVector *)pParams[2].fp_pD;

	APgenericRationalVector_mod(pa, pb, pc);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for modRational (33)
THALFunctionParam const gpHALFunctionParam_33_modRational [] = { // name: a descr: vector a
	{.paramClass = 3, .paramTypeID = 1},
	// name: b descr: vector b
	{.paramClass = 3, .paramTypeID = 1},
	// name: c descr: vector c
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for compareRationalLess
// HAL descr: a < b ? CF = 1 : CF = 0
// implementation descr: a<b
// here goes the implementation
// ===============================
// function implementation for compareRationalLess(var id = 34)
// description: a < b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID34_compareRationalLess(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib) < 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;


};

// function info for compareRationalLess (34)
THALFunctionParam const gpHALFunctionParam_34_compareRationalLess [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareRationalMore
// HAL descr: a > b ? CF = 1 : CF = 0
// implementation descr: a>b
// here goes the implementation
// ===============================
// function implementation for compareRationalMore(var id = 35)
// description: a > b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID35_compareRationalMore(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib) > 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareRationalMore (35)
THALFunctionParam const gpHALFunctionParam_35_compareRationalMore [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareRationalEqual
// HAL descr: a == b ? CF = 1 : CF = 0
// implementation descr: a==b
// here goes the implementation
// ===============================
// function implementation for compareRationalEqual(var id = 36)
// description: a == b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID36_compareRationalEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib) == 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareRationalEqual (36)
THALFunctionParam const gpHALFunctionParam_36_compareRationalEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareRationalNEqual
// HAL descr: a != b ? CF = 1 : CF = 0
// implementation descr: a<>b
// here goes the implementation
// ===============================
// function implementation for compareRationalNEqual(var id = 37)
// description: a != b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID37_compareRationalNEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib)  != 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareRationalNEqual (37)
THALFunctionParam const gpHALFunctionParam_37_compareRationalNEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareRationalLessEqual
// HAL descr: a <= b ? CF = 1 : CF = 0
// implementation descr: a<=b
// here goes the implementation
// ===============================
// function implementation for compareRationalLessEqual(var id = 38)
// description: a <= b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID38_compareRationalLessEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib)  > 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareRationalLessEqual (38)
THALFunctionParam const gpHALFunctionParam_38_compareRationalLessEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for compareRationalMoreEqual
// HAL descr: a >= b ? CF = 1 : CF = 0
// implementation descr: a=>b
// here goes the implementation
// ===============================
// function implementation for compareRationalMoreEqual(var id = 39)
// description: a >= b ? CF = 1 : CF = 0
// ===============================
void HALfunc_ID39_compareRationalMoreEqual(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter a descr: vector a
	TAPgenericRationalVector * pa = (TAPgenericRationalVector *)pParams[0].fp_pD;
// parameter ia descr: a index
	int32_t ia = pParams[1].fp_integer;
// parameter b descr: vector b
	TAPgenericRationalVector* pb = (TAPgenericRationalVector *)pParams[2].fp_pD;
// parameter ib descr: b index
	int32_t ib = pParams[3].fp_integer;

	if (APgenericRationalVector_cmpEle(pa, pb, ia, ib)  < 0) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for compareRationalMoreEqual (39)
THALFunctionParam const gpHALFunctionParam_39_compareRationalMoreEqual [] = { // name: a descr: left side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ia descr: index at a vector
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: right side number
	{.paramClass = 3, .paramTypeID = 1},
	// name: ib descr: index at b vector
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for jump
// HAL descr: jumps n instructions
// implementation descr: increment / decrement instruction pointer
// here goes the implementation
// ===============================
// function implementation for jump(var id = 50)
// description: jumps n instructions
// ===============================

void HALfunc_ID50_jump(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter number descr: amount of instructions to jump
//	int32_t* pnumber = &( pParams[0].fp_integer);
	((TAPInterpreterCPU *)pIPcpu)->pIP += pParams[0].fp_integer;
};

// function info for jump (50)
THALFunctionParam const gpHALFunctionParam_50_jump [] = { // name: number descr: amount of instructions to jump
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for jumpCF
// HAL descr: jumps if the carry flag is set n instructions
// implementation descr: increment / decrement instruction pointer if the CF is set
// here goes the implementation
// ===============================
// function implementation for jumpCF(var id = 51)
// description: jumps if the carry flag is set n instructions
// ===============================

void HALfunc_ID51_jumpCF(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
	if (((TAPInterpreterCPU *)pIPcpu)->CF) {
		((TAPInterpreterCPU *)pIPcpu)->pIP += pParams[0].fp_integer;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for jumpCF (51)
THALFunctionParam const gpHALFunctionParam_51_jumpCF [] = { // name: number descr: amount of instructions to jump
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for jumpNCF
// HAL descr: jumps if the carry flag is not set n instructions
// implementation descr: increment / decrement instruction pointer if the CF is not set
// here goes the implementation
// ===============================
// function implementation for jumpNCF(var id = 52)
// description: jumps if the carry flag is not set n instructions
// ===============================

void HALfunc_ID52_jumpNCF(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
	if (!((TAPInterpreterCPU *)pIPcpu)->CF) {
		((TAPInterpreterCPU *)pIPcpu)->pIP += pParams[0].fp_integer;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for jumpNCF (52)
THALFunctionParam const gpHALFunctionParam_52_jumpNCF [] = { // name: number descr: amount of instructions to jump
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for setCF
// HAL descr: sets the carry flag
// implementation descr: sets the CF
// here goes the implementation
// ===============================
// function implementation for setCF(var id = 55)
// description: sets the carry flag
// ===============================

void HALfunc_ID55_setCF(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter value descr: the value of the CF
	if (pParams[0].fp_integer) {
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for setCF (55)
THALFunctionParam const gpHALFunctionParam_55_setCF [] = { // name: value descr: the value of the CF
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for update
// HAL descr: updates a global variable
// implementation descr: updates a variable
// here goes the implementation
// ===============================
// function implementation for update(var id = 56)
// description: updates a global variable
// ===============================

void HALfunc_ID56_update(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
	if (TX_updateVariable(APInterpreterGetAPfromIP(((TAPInterpreterCPU *)pIPcpu)->IP),(uint32_t)pParams[0].fp_VarIndex)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -100;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for update (56)
THALFunctionParam const gpHALFunctionParam_56_update [] = { // name: var descr: the variable (internally the index of the variable)
	{.paramClass = 5, .paramTypeID = 0}
};
// HAL function implementation for initBiquadAsHP
// HAL descr: inits a biquad filter as an high pass filter
// implementation descr: inits a biquad at the cascade as high pass filter
// here goes the implementation
// ===============================
// function implementation for initBiquadAsHP(var id = 100)
// description: inits a biquad filter as an high pass filter
// ===============================

void HALfunc_ID100_initBiquadAsHP(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int32_t index = *((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;
// parameter fs descr: sample frequnecy
	float fs = *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter fc descr: cut off frequency
	float fc = *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;

	if (stjBQF_cascadeInitHP(pbqc, (unsigned int) index, fs, fc)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -100;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for initBiquadAsHP (100)
THALFunctionParam const gpHALFunctionParam_100_initBiquadAsHP [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: fs descr: sample frequnecy
	{.paramClass = 3, .paramTypeID = 1},
	// name: fc descr: cut off frequency
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initBiquadAsLP
// HAL descr: inits a biquad filter as a low pass filter
// implementation descr: inits a biquad at the cascade as low pass filter
// here goes the implementation
// ===============================
// function implementation for initBiquadAsLP(var id = 101)
// description: inits a biquad filter as a low pass filter
// ===============================
void HALfunc_ID101_initBiquadAsLP(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int32_t index =*((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;
// parameter fs descr: sample frequnecy
	float fs = *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter fc descr: cut off frequency
	float fc = *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;

	if (stjBQF_cascadeInitLP(pbqc, (unsigned int) index, fs, fc)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -101;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for initBiquadAsLP (101)
THALFunctionParam const gpHALFunctionParam_101_initBiquadAsLP [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: fs descr: sample frequnecy
	{.paramClass = 3, .paramTypeID = 1},
	// name: fc descr: cut off frequency
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initBiquadAsPeakFilter
// HAL descr: inits a biquad filter as peak filter
// implementation descr: inits a biquad at the cascade as boost/cut peak filter
// here goes the implementation
// ===============================
// function implementation for initBiquadAsPeakFilter(var id = 102)
// description: inits a biquad filter as peak filter
// ===============================
void HALfunc_ID102_initBiquadAsPeakFilter(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int32_t index = *((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;
// parameter fs descr: sample frequnecy
	float fs = *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter fc descr: center frequency
	float fc = *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;
// parameter q descr: quality
	float q = *((TAPgenericRationalVector *) pParams[4].fp_pD)->pVal;
// parameter g descr: gain (not in dB)
	float g = *((TAPgenericRationalVector *) pParams[5].fp_pD)->pVal;

	if (stjBQF_cascadeInitPeak(pbqc, (unsigned int) index, fs, fc, g, q)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -102;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for initBiquadAsPeakFilter (102)
THALFunctionParam const gpHALFunctionParam_102_initBiquadAsPeakFilter [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: fs descr: sample frequnecy
	{.paramClass = 3, .paramTypeID = 1},
	// name: fc descr: center frequency
	{.paramClass = 3, .paramTypeID = 1},
	// name: q descr: quality
	{.paramClass = 3, .paramTypeID = 1},
	// name: g descr: gain (not in dB)
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initBiquadAsLowFreqShelvFilter
// HAL descr: inits a biquad filter as low ferquency shelving filter
// implementation descr: inits a biquad at the cascade as low frequency boost/cut shelving filter
// here goes the implementation
// ===============================
// function implementation for initBiquadAsLowFreqShelvFilter(var id = 103)
// description: inits a biquad filter as low ferquency shelving filter
// ===============================
void HALfunc_ID103_initBiquadAsLowFreqShelvFilter(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int32_t index =*((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;
// parameter fs descr: sample frequnecy
	float fs = *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter f descr: cut/boost frequency
	float f = *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;
// parameter g descr: gain (not in dB)
	float g = *((TAPgenericRationalVector *) pParams[4].fp_pD)->pVal;

	if (stjBQF_cascadeInitLowFreqShelving(pbqc, (unsigned int) index, fs, f, g)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -103;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for initBiquadAsLowFreqShelvFilter (103)
THALFunctionParam const gpHALFunctionParam_103_initBiquadAsLowFreqShelvFilter [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: fs descr: sample frequnecy
	{.paramClass = 3, .paramTypeID = 1},
	// name: f descr: cut/boost frequency
	{.paramClass = 3, .paramTypeID = 1},
	// name: g descr: gain (not in dB)
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initBiquadAsHighFreqShelvFilter
// HAL descr: inits a biquad filter as high ferquency shelving filter
// implementation descr: inits a biquad at the cascade as low frequency boost/cut shelving filter
// here goes the implementation
// ===============================
// function implementation for initBiquadAsHighFreqShelvFilter(var id = 104)
// description: inits a biquad filter as high ferquency shelving filter
// ===============================
void HALfunc_ID104_initBiquadAsHighFreqShelvFilter(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int32_t index = *((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;
// parameter fs descr: sample frequnecy
	float fs = *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter f descr: cut/boost frequency
	float f = *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;
// parameter g descr: gain (not in dB)
	float g = *((TAPgenericRationalVector *) pParams[4].fp_pD)->pVal;

	if (stjBQF_cascadeInitHighFreqShelving(pbqc, (unsigned int) index, fs, f, g)) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -104;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->pIP++;
	}
};

// function info for initBiquadAsHighFreqShelvFilter (104)
THALFunctionParam const gpHALFunctionParam_104_initBiquadAsHighFreqShelvFilter [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: fs descr: sample frequnecy
	{.paramClass = 3, .paramTypeID = 1},
	// name: f descr: cut/boost frequency
	{.paramClass = 3, .paramTypeID = 1},
	// name: g descr: gain (not in dB)
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for convoluteBiquad
// HAL descr: convolute biquad with an input and generate an output
// implementation descr: convolutes a vector of samples with a biquad cascade
// here goes the implementation
// ===============================
// function implementation for convoluteBiquad(var id = 110)
// description: convolute biquad with an input and generate an output
// ===============================
void HALfunc_ID110_convoluteBiquad(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter x descr: input
	TAPgenericRationalVector * pXvec = (TAPgenericRationalVector *) pParams[0].fp_pD;
// parameter bqa descr: biquad cascade
	TstjBiquadCascade * pbqc = (TstjBiquadCascade *) pParams[1].fp_pD;
// parameter y descr: output
	TAPgenericRationalVector * pYvec = (TAPgenericRationalVector *) pParams[2].fp_pD;

	stjBQF_cascadeConvolute(pbqc,pXvec->pVal, pXvec->num, pYvec->pVal);

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for convoluteBiquad (110)
THALFunctionParam const gpHALFunctionParam_110_convoluteBiquad [] = { // name: x descr: input
	{.paramClass = 3, .paramTypeID = 1},
	// name: bqa descr: biquad cascade
	{.paramClass = 3, .paramTypeID = 10},
	// name: y descr: output
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initBiquad
// HAL descr: inits a biquad of h(z) = y(z)/x(z) = (a0*z0 + a1*z-1+ a2*z-2) / (1*z0 + b1*z-1+ b2*z-2)
// implementation descr: inits a generic biquad with it coefficients
// here goes the implementation
// ===============================
// function implementation for initBiquad(var id = 105)
// description: inits a biquad of h(z) = y(z)/x(z) = (a0*z0 + a1*z-1+ a2*z-2) / (1*z0 + b1*z-1+ b2*z-2)
// ===============================
void HALfunc_ID105_initBiquad(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter bq descr: biquad cascade
	TstjBiquadCascade * pbqc = ((TAPInterpreterVariable *) pParams[0].fp_pV)->pData;
// parameter index descr: index at the cascade
	int index = (int)*((TAPgenericIntegerVector *) pParams[1].fp_pD)->pVal;

// a temporal set of the vector for the numerator / denumerator values
// parameter a0 descr: a0 coefficient
	pbqc->pB[index].a[0] = (float) *((TAPgenericRationalVector *) pParams[2].fp_pD)->pVal;
// parameter a1 descr: a1 coefficient
	pbqc->pB[index].a[1] = (float) *((TAPgenericRationalVector *) pParams[3].fp_pD)->pVal;
// parameter a2 descr: a2 coefficient
	pbqc->pB[index].a[2] = (float) *((TAPgenericRationalVector *) pParams[4].fp_pD)->pVal;
// parameter b1 descr: b1 coefficient
	pbqc->pB[index].b[0] = (float) *((TAPgenericRationalVector *) pParams[5].fp_pD)->pVal;
// parameter b2 descr: b2 coefficient
	pbqc->pB[index].b[1] = (float) *((TAPgenericRationalVector *) pParams[6].fp_pD)->pVal;

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for initBiquad (105)
THALFunctionParam const gpHALFunctionParam_105_initBiquad [] = { // name: bq descr: biquad cascade
	{.paramClass = 2, .paramTypeID = 10},
	// name: index descr: index at the cascade
	{.paramClass = 3, .paramTypeID = 2},
	// name: a0 descr: a0 coefficient
	{.paramClass = 3, .paramTypeID = 1},
	// name: a1 descr: a1 coefficient
	{.paramClass = 3, .paramTypeID = 1},
	// name: a2 descr: a2 coefficient
	{.paramClass = 3, .paramTypeID = 1},
	// name: b1 descr: b1 coefficient
	{.paramClass = 3, .paramTypeID = 1},
	// name: b2 descr: b2 coefficient
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for uiSetDim
// HAL descr: sets the dimension of a UI
// implementation descr: sets the dimension of the UI
// here goes the implementation
// ===============================
// function implementation for uiSetDim(var id = 200)
// description: sets the dimension of a UI
// ===============================

void HALfunc_ID200_uiSetDim(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter xPos descr: x position in pixel
	int32_t xPos = pParams[0].fp_integer;
// parameter yPos descr: y position in pixel
	int32_t yPos = pParams[1].fp_integer;
// parameter xLen descr: x width
	int32_t xLen = pParams[2].fp_integer;
// parameter yLen descr: y height
	int32_t yLen = pParams[3].fp_integer;
// parameter ui descr: UI element
	TAPgtkUIvector * puiVec = (TAPgtkUIvector *) pParams[4].fp_pV;
// parameter uiIndex descr: UI element index
	int32_t uiIndex = pParams[5].fp_integer;
	
	APgtkUI_setCoordinates (
			&(puiVec->pUI[uiIndex]),
			xPos,
			yPos,
			xLen,
			yLen
		);
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiSetDim (200)
THALFunctionParam const gpHALFunctionParam_200_uiSetDim [] = { // name: x descr: x position
	{.paramClass = 1, .paramTypeID = 2},
	// name: y descr: y position
	{.paramClass = 1, .paramTypeID = 2},
	// name: xle descr: x length
	{.paramClass = 1, .paramTypeID = 2},
	// name: yle descr: y length
	{.paramClass = 1, .paramTypeID = 2},
	// name: ui descr: ui
	{.paramClass = 3, .paramTypeID = 0},
	// name: uiIndex descr: ui index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiInitPanel
// HAL descr: inits a panel
// implementation descr: inits a panel
// here goes the implementation
// ===============================
// function implementation for uiInitPanel(var id = 201)
// description: inits a panel
// ===============================

void HALfunc_ID201_uiInitPanel(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter uiUUID descr: uuid of the pannel
	int32_t uiUUID = pParams[0].fp_integer;
// parameter p descr: pannel
	TAPgtkUIvector * puiVec = (TAPgtkUIvector *) pParams[1].fp_pD;
// parameter pIndex descr: pannel index
	int32_t pIndex = pParams[2].fp_integer;

	if (APgtkUI_createUI (
			&(puiVec->pUI[pIndex]),
			NULL,
			uiUUID,
			eAPgtkUItype_panel
		)
	) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -10;
	}

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiInitPanel (201)
THALFunctionParam const gpHALFunctionParam_201_uiInitPanel [] = { // name: uiUUID descr: uuid of the pannel
	{.paramClass = 1, .paramTypeID = 2},
	// name: p descr: panel
	{.paramClass = 3, .paramTypeID = 100},
	// name: pIndex descr: panel index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiInitButton
// HAL descr: inits a button
// implementation descr: inits a button
// here goes the implementation
// ===============================
// function implementation for uiInitButton(var id = 202)
// description: inits a button
// ===============================

void HALfunc_ID202_uiInitButton(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter uiUUID descr: uuid of the pannel
	int32_t uiUUID = pParams[0].fp_integer;
// parameter b descr: button
	TAPgtkUIvector * puiB = (TAPgtkUIvector *)  pParams[1].fp_pD;
// parameter bIndex descr: button index
	int32_t bIndex = pParams[2].fp_integer;
// parameter p descr: panel
	TAPgtkUIvector * puiP = (TAPgtkUIvector *) pParams[3].fp_pD;
// parameter pIndex descr: panel index
	int32_t pIndex = pParams[4].fp_integer;

	if (APgtkUI_createUI (
			&(puiB->pUI[bIndex]),
			&(puiP->pUI[pIndex]),
			uiUUID,
			eAPgtkUItype_button
		)
	) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -10;
	}

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiInitButton (202)
THALFunctionParam const gpHALFunctionParam_202_uiInitButton [] = { // name: uiUUID descr: uuid of the button
	{.paramClass = 1, .paramTypeID = 2},
	// name: b descr: button
	{.paramClass = 3, .paramTypeID = 101},
	// name: bIndex descr: button index
	{.paramClass = 1, .paramTypeID = 2},
	// name: p descr: panel
	{.paramClass = 3, .paramTypeID = 100},
	// name: pIndex descr: panel index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiInitDisplay
// HAL descr: inits a display
// implementation descr: inits a display
// here goes the implementation
// ===============================
// function implementation for uiInitDisplay(var id = 203)
// description: inits a display
// ===============================

void HALfunc_ID203_uiInitDisplay(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter uiUUID descr: uuid of the panel
	int32_t uiUUID = pParams[0].fp_integer;
// parameter b descr: display
	TAPgtkUIvector * puiD = (TAPgtkUIvector *)  pParams[1].fp_pD;
// parameter bIndex descr: display index
	int32_t dIndex = pParams[2].fp_integer;
// parameter p descr: panel
	TAPgtkUIvector * puiP = (TAPgtkUIvector *) pParams[3].fp_pD;
// parameter pIndex descr: panel index
	int32_t pIndex = pParams[4].fp_integer;

	if (APgtkUI_createUI (
			&(puiD->pUI[dIndex]),
			&(puiP->pUI[pIndex]),
			uiUUID,
			eAPgtkUItype_display
		)
	) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -10;
	}

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiInitDisplay (203)
THALFunctionParam const gpHALFunctionParam_203_uiInitDisplay [] = { // name: uiUUID descr: uuid of the display
	{.paramClass = 1, .paramTypeID = 2},
	// name: d descr: display
	{.paramClass = 3, .paramTypeID = 103},
	// name: dIndex descr: display index
	{.paramClass = 1, .paramTypeID = 2},
	// name: p descr: panel
	{.paramClass = 3, .paramTypeID = 100},
	// name: pIndex descr: panel index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiInitLED
// HAL descr: inits a LED
// implementation descr: inits a LED
// here goes the implementation
// ===============================
// function implementation for uiInitLED(var id = 204)
// description: inits a LED
// ===============================

void HALfunc_ID204_uiInitLED(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter uiUUID descr: uuid of the LED
	int32_t uiUUID = pParams[0].fp_integer;
// parameter l descr: LED
	TAPgtkUIvector * puiL = (TAPgtkUIvector *)  pParams[1].fp_pD;
// parameter lIndex descr: LED index
	int32_t lIndex = pParams[2].fp_integer;
// parameter p descr: panel
	TAPgtkUIvector * puiP = (TAPgtkUIvector *) pParams[3].fp_pD;
// parameter pIndex descr: panel index
	int32_t pIndex = pParams[4].fp_integer;

	if (APgtkUI_createUI (
			&(puiL->pUI[lIndex]),
			&(puiP->pUI[pIndex]),
			uiUUID,
			eAPgtkUItype_LED
		)
	) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -10;
	}

	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiInitLED (204)
THALFunctionParam const gpHALFunctionParam_204_uiInitLED [] = { // name: uiUUID descr: uuid of the LED
	{.paramClass = 1, .paramTypeID = 2},
	// name: l descr: LED
	{.paramClass = 3, .paramTypeID = 102},
	// name: lIndex descr: LED index
	{.paramClass = 1, .paramTypeID = 2},
	// name: p descr: panel
	{.paramClass = 3, .paramTypeID = 100},
	// name: pIndex descr: panel index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiCheckButtonPressed
// HAL descr: if the button was pressed the CF is set
// implementation descr: check button state
// here goes the implementation
// ===============================
// function implementation for uiCheckButtonPressed(var id = 210)
// description: if the button was pressed the CF is set
// ===============================

void HALfunc_ID210_uiCheckButtonPressed(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter b descr: button
	TAPgtkUIvector * puiB = (TAPgtkUIvector *)  pParams[0].fp_pD;
// parameter bIndex descr: button index
	int32_t bIndex = pParams[1].fp_integer;
// parameter p descr: panel

	if (puiB->pUI[bIndex].ui.button.pressCounter) {
		puiB->pUI[bIndex].ui.button.pressCounter--;
		((TAPInterpreterCPU *)pIPcpu)->CF = 1;
	} else {
		((TAPInterpreterCPU *)pIPcpu)->CF = 0;
	}
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiCheckButtonPressed (210)
THALFunctionParam const gpHALFunctionParam_210_uiCheckButtonPressed [] = { // name: b descr: button
	{.paramClass = 3, .paramTypeID = 101},
	// name: bIndex descr: button index
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiSetLED
// HAL descr: set the LED state
// implementation descr: set LED state
// here goes the implementation
// ===============================
// function implementation for uiSetLED(var id = 211)
// description: set the LED state
// ===============================

void HALfunc_ID211_uiSetLED(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter l descr: LED
	TAPgtkUIvector * puiL = (TAPgtkUIvector *)  pParams[0].fp_pD;
// parameter lIndex descr: LED index
	int32_t lIndex = pParams[1].fp_integer;
// parameter onFlag descr: if the flag is not zero the LED is turned on
	int32_t  onFlag = pParams[2].fp_integer;

	puiL->pUI[lIndex].ui.led.onFlag = (!onFlag) ? 0 : 1;
	APgtkUI_redrawUI(&(puiL->pUI[lIndex]));
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiSetLED (211)
THALFunctionParam const gpHALFunctionParam_211_uiSetLED [] = { // name: l descr: LED
	{.paramClass = 3, .paramTypeID = 102},
	// name: lIndex descr: LED index
	{.paramClass = 1, .paramTypeID = 2},
	// name: onFlag descr: if the flag is not zero the LED is turned on
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiSetDisplay
// HAL descr: set the text of a display
// implementation descr: set display text
// here goes the implementation
// ===============================
// function implementation for uiSetDisplay(var id = 212)
// description: set the text of a display
// ===============================

void HALfunc_ID212_uiSetDisplay(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter d descr: display
	TAPgtkUIvector * puiD = (TAPgtkUIvector *)  pParams[0].fp_pD;
// parameter dIndex descr: display index
	int32_t dIndex = pParams[1].fp_integer;
// parameter s descr: the string
	TAPstringVector * pSV = (TAPstringVector *) pParams[2].fp_pD;
// parameter iString descr: index of the string at the array
	int32_t iString = pParams[3].fp_integer;

	gtkAP_DisplaySetText (
			&(puiD->pUI[dIndex].ui.display),
			pSV->sv[iString].szTxt
		);
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiSetDisplay (212)
THALFunctionParam const gpHALFunctionParam_212_uiSetDisplay [] = { // name: d descr: display
	{.paramClass = 3, .paramTypeID = 103},
	// name: dIndex descr: display index
	{.paramClass = 1, .paramTypeID = 2},
	// name: s descr: the string
	{.paramClass = 3, .paramTypeID = 3},
	// name: iString descr: index of the string at the array
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for uiSetDisplayTextDim
// HAL descr: sets the dimension of the text display
// implementation descr: set display text dimenions
// here goes the implementation
// ===============================
// function implementation for uiSetDisplayTextDim(var id = 213)
// description: sets the dimension of the text display
// ===============================
void HALfunc_ID213_uiSetDisplayTextDim(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter d descr: display
	TAPgtkUIvector * puiD = (TAPgtkUIvector *)  pParams[0].fp_pD;
// parameter dIndex descr: display index
	int32_t dIndex = pParams[1].fp_integer;
// parameter charsPerLine descr: amount of characters per line
	int32_t charsPerLine = pParams[2].fp_integer;
// parameter lines descr: amout of characters-lines
	int32_t lines = pParams[3].fp_integer;

	gtkAP_local_DisplaySetTextDim (
			&(puiD->pUI[dIndex].ui.display),
			(int) charsPerLine,
			(int) lines
		);
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for uiSetDisplayTextDim (213)
THALFunctionParam const gpHALFunctionParam_213_uiSetDisplayTextDim [] = { // name: d descr: display
	{.paramClass = 3, .paramTypeID = 103},
	// name: dIndex descr: display index
	{.paramClass = 1, .paramTypeID = 2},
	// name: charsPerLine descr: amount of characters per line
	{.paramClass = 1, .paramTypeID = 2},
	// name: lines descr: amout of characters-lines
	{.paramClass = 1, .paramTypeID = 2}
};
// HAL function implementation for calcDelay
// HAL descr: stream a vector of samples in and a vector of exactly the same size out 
// implementation descr: sends a stream of values into the delay and reads them out of it
// here goes the implementation
// ===============================
// function implementation for calcDelay(var id = 150)
// description: shifts the content of the delay
// ===============================
void HALfunc_ID150_calcDelay(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
// parameter x descr: input
	TAPgenericRationalVector * x = (TAPgenericRationalVector *) pParams[0].fp_pD;
// parameter delay descr: the delay
	TgenDelay * delay = (TgenDelay *) pParams[1].fp_pD;
// parameter y descr: output
	TAPgenericRationalVector * y = (TAPgenericRationalVector *) pParams[2].fp_pD;

	genDelay_readWrite(delay, x->pVal, y->pVal, y->num);
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for calcDelay (150)
THALFunctionParam const gpHALFunctionParam_150_calcDelay [] = { // name: x descr: input
	{.paramClass = 3, .paramTypeID = 1},
	// name: delay descr: the delay
	{.paramClass = 3, .paramTypeID = 20},
	// name: y descr: output
	{.paramClass = 3, .paramTypeID = 1}
};
// HAL function implementation for initDelay
// HAL descr: inits the delay
// implementation descr: inits the delay
// here goes the implementation
// ===============================
// function implementation for initDelay(var id = 151)
// description: inits the delay
// ===============================
void HALfunc_ID151_initDelay(void * pIPcpu, TuAPInterpreterFunctionParameter * pParams) {
	// parameter d descr: the delay
	TgenDelay * d = (TgenDelay *) pParams[0].fp_pD;
	// parameter N descr: number of samples which correspond to the delay time (Tdelay = N * Ta)
	TAPgenericIntegerVector * pN = (TAPgenericIntegerVector *)pParams[1].fp_pD;
	// parameter Nindex descr: the index at the vector of N
	int Nindex = (int)*((TAPgenericIntegerVector *)pParams[2].fp_pD)->pVal;

	// resize delay
	if (genDelay_resize(d, pN->pVal[Nindex])) {
		((TAPInterpreterCPU *)pIPcpu)->EF = -1;
		return;
	}
	// inc IP
	((TAPInterpreterCPU *)pIPcpu)->pIP++;
};

// function info for initDelay (151)
THALFunctionParam const gpHALFunctionParam_151_initDelay [] = { // name: d descr: the delay
	{.paramClass = 3, .paramTypeID = 20},
	// name: N descr: number of samples which correspond to the delay time (Tdelay = N * Ta)
	{.paramClass = 3, .paramTypeID = 2},
	// name: Nindex descr: the index at the vector of N
	{.paramClass = 3, .paramTypeID = 2}
};// the function info vector 
THALFunction const gpFunctionInfoVector [] = {
    // HAL function info for setStringSize
	{
	    .fid = 5,
	    .paramList = {gpHALFunctionParam_5_setStringSize,3},
	    .pfktHAL = HALfunc_ID5_setStringSize
	},
	// HAL function info for setStringValues
	{
	    .fid = 6,
	    .paramList = {gpHALFunctionParam_6_setStringValues,7},
	    .pfktHAL = HALfunc_ID6_setStringValues
	},
	// HAL function info for concatStrings
	{
	    .fid = 7,
	    .paramList = {gpHALFunctionParam_7_concatStrings,4},
	    .pfktHAL = HALfunc_ID7_concatStrings
	},
	// HAL function info for rationalToString
	{
	    .fid = 8,
	    .paramList = {gpHALFunctionParam_8_rationalToString,4},
	    .pfktHAL = HALfunc_ID8_rationalToString
	},
	// HAL function info for integerToString
	{
	    .fid = 9,
	    .paramList = {gpHALFunctionParam_9_integerToString,4},
	    .pfktHAL = HALfunc_ID9_integerToString
	},
	// HAL function info for assignString
	{
	    .fid = 10,
	    .paramList = {gpHALFunctionParam_10_assignString,4},
	    .pfktHAL = HALfunc_ID10_assignString
	},
	// HAL function info for assignConstInteger
	{
	    .fid = 20,
	    .paramList = {gpHALFunctionParam_20_assignConstInteger,7},
	    .pfktHAL = HALfunc_ID20_assignConstInteger
	},
	// HAL function info for assignInteger
	{
	    .fid = 21,
	    .paramList = {gpHALFunctionParam_21_assignInteger,2},
	    .pfktHAL = HALfunc_ID21_assignInteger
	},
	// HAL function info for addInteger
	{
	    .fid = 22,
	    .paramList = {gpHALFunctionParam_22_addInteger,3},
	    .pfktHAL = HALfunc_ID22_addInteger
	},
	// HAL function info for subInteger
	{
	    .fid = 23,
	    .paramList = {gpHALFunctionParam_23_subInteger,3},
	    .pfktHAL = HALfunc_ID23_subInteger
	},
	// HAL function info for mulInteger
	{
	    .fid = 24,
	    .paramList = {gpHALFunctionParam_24_mulInteger,3},
	    .pfktHAL = HALfunc_ID24_mulInteger
	},
	// HAL function info for divInteger
	{
	    .fid = 25,
	    .paramList = {gpHALFunctionParam_25_divInteger,3},
	    .pfktHAL = HALfunc_ID25_divInteger
	},
	// HAL function info for modInteger
	{
	    .fid = 26,
	    .paramList = {gpHALFunctionParam_26_modInteger,3},
	    .pfktHAL = HALfunc_ID26_modInteger
	},
	// HAL function info for compareIntegerLess
	{
	    .fid = 40,
	    .paramList = {gpHALFunctionParam_40_compareIntegerLess,4},
	    .pfktHAL = HALfunc_ID40_compareIntegerLess
	},
	// HAL function info for compareIntegerMore
	{
	    .fid = 41,
	    .paramList = {gpHALFunctionParam_41_compareIntegerMore,4},
	    .pfktHAL = HALfunc_ID41_compareIntegerMore
	},
	// HAL function info for compareIntegerEqual
	{
	    .fid = 42,
	    .paramList = {gpHALFunctionParam_42_compareIntegerEqual,4},
	    .pfktHAL = HALfunc_ID42_compareIntegerEqual
	},
	// HAL function info for compareIntegerNEqual
	{
	    .fid = 43,
	    .paramList = {gpHALFunctionParam_43_compareIntegerNEqual,4},
	    .pfktHAL = HALfunc_ID43_compareIntegerNEqual
	},
	// HAL function info for compareIntegerLessEqual
	{
	    .fid = 44,
	    .paramList = {gpHALFunctionParam_44_compareIntegerLessEqual,4},
	    .pfktHAL = HALfunc_ID44_compareIntegerLessEqual
	},
	// HAL function info for compareIntegerMoreEqual
	{
	    .fid = 45,
	    .paramList = {gpHALFunctionParam_45_compareIntegerMoreEqual,4},
	    .pfktHAL = HALfunc_ID45_compareIntegerMoreEqual
	},
	// HAL function info for assignConstRational
	{
	    .fid = 27,
	    .paramList = {gpHALFunctionParam_27_assignConstRational,7},
	    .pfktHAL = HALfunc_ID27_assignConstRational
	},
	// HAL function info for assignRational
	{
	    .fid = 28,
	    .paramList = {gpHALFunctionParam_28_assignRational,2},
	    .pfktHAL = HALfunc_ID28_assignRational
	},
	// HAL function info for addRational
	{
	    .fid = 29,
	    .paramList = {gpHALFunctionParam_29_addRational,3},
	    .pfktHAL = HALfunc_ID29_addRational
	},
	// HAL function info for subRational
	{
	    .fid = 30,
	    .paramList = {gpHALFunctionParam_30_subRational,3},
	    .pfktHAL = HALfunc_ID30_subRational
	},
	// HAL function info for mulRational
	{
	    .fid = 31,
	    .paramList = {gpHALFunctionParam_31_mulRational,3},
	    .pfktHAL = HALfunc_ID31_mulRational
	},
	// HAL function info for divRational
	{
	    .fid = 32,
	    .paramList = {gpHALFunctionParam_32_divRational,3},
	    .pfktHAL = HALfunc_ID32_divRational
	},
	// HAL function info for modRational
	{
	    .fid = 33,
	    .paramList = {gpHALFunctionParam_33_modRational,3},
	    .pfktHAL = HALfunc_ID33_modRational
	},
	// HAL function info for compareRationalLess
	{
	    .fid = 34,
	    .paramList = {gpHALFunctionParam_34_compareRationalLess,4},
	    .pfktHAL = HALfunc_ID34_compareRationalLess
	},
	// HAL function info for compareRationalMore
	{
	    .fid = 35,
	    .paramList = {gpHALFunctionParam_35_compareRationalMore,4},
	    .pfktHAL = HALfunc_ID35_compareRationalMore
	},
	// HAL function info for compareRationalEqual
	{
	    .fid = 36,
	    .paramList = {gpHALFunctionParam_36_compareRationalEqual,4},
	    .pfktHAL = HALfunc_ID36_compareRationalEqual
	},
	// HAL function info for compareRationalNEqual
	{
	    .fid = 37,
	    .paramList = {gpHALFunctionParam_37_compareRationalNEqual,4},
	    .pfktHAL = HALfunc_ID37_compareRationalNEqual
	},
	// HAL function info for compareRationalLessEqual
	{
	    .fid = 38,
	    .paramList = {gpHALFunctionParam_38_compareRationalLessEqual,4},
	    .pfktHAL = HALfunc_ID38_compareRationalLessEqual
	},
	// HAL function info for compareRationalMoreEqual
	{
	    .fid = 39,
	    .paramList = {gpHALFunctionParam_39_compareRationalMoreEqual,4},
	    .pfktHAL = HALfunc_ID39_compareRationalMoreEqual
	},
	// HAL function info for jump
	{
	    .fid = 50,
	    .paramList = {gpHALFunctionParam_50_jump,1},
	    .pfktHAL = HALfunc_ID50_jump
	},
	// HAL function info for jumpCF
	{
	    .fid = 51,
	    .paramList = {gpHALFunctionParam_51_jumpCF,1},
	    .pfktHAL = HALfunc_ID51_jumpCF
	},
	// HAL function info for jumpNCF
	{
	    .fid = 52,
	    .paramList = {gpHALFunctionParam_52_jumpNCF,1},
	    .pfktHAL = HALfunc_ID52_jumpNCF
	},
	// HAL function info for setCF
	{
	    .fid = 55,
	    .paramList = {gpHALFunctionParam_55_setCF,1},
	    .pfktHAL = HALfunc_ID55_setCF
	},
	// HAL function info for update
	{
	    .fid = 56,
	    .paramList = {gpHALFunctionParam_56_update,1},
	    .pfktHAL = HALfunc_ID56_update
	},
	// HAL function info for initBiquadAsHP
	{
	    .fid = 100,
	    .paramList = {gpHALFunctionParam_100_initBiquadAsHP,4},
	    .pfktHAL = HALfunc_ID100_initBiquadAsHP
	},
	// HAL function info for initBiquadAsLP
	{
	    .fid = 101,
	    .paramList = {gpHALFunctionParam_101_initBiquadAsLP,4},
	    .pfktHAL = HALfunc_ID101_initBiquadAsLP
	},
	// HAL function info for initBiquadAsPeakFilter
	{
	    .fid = 102,
	    .paramList = {gpHALFunctionParam_102_initBiquadAsPeakFilter,6},
	    .pfktHAL = HALfunc_ID102_initBiquadAsPeakFilter
	},
	// HAL function info for initBiquadAsLowFreqShelvFilter
	{
	    .fid = 103,
	    .paramList = {gpHALFunctionParam_103_initBiquadAsLowFreqShelvFilter,5},
	    .pfktHAL = HALfunc_ID103_initBiquadAsLowFreqShelvFilter
	},
	// HAL function info for initBiquadAsHighFreqShelvFilter
	{
	    .fid = 104,
	    .paramList = {gpHALFunctionParam_104_initBiquadAsHighFreqShelvFilter,5},
	    .pfktHAL = HALfunc_ID104_initBiquadAsHighFreqShelvFilter
	},
	// HAL function info for convoluteBiquad
	{
	    .fid = 110,
	    .paramList = {gpHALFunctionParam_110_convoluteBiquad,3},
	    .pfktHAL = HALfunc_ID110_convoluteBiquad
	},
	// HAL function info for initBiquad
	{
	    .fid = 105,
	    .paramList = {gpHALFunctionParam_105_initBiquad,7},
	    .pfktHAL = HALfunc_ID105_initBiquad
	},
	// HAL function info for uiSetDim
	{
	    .fid = 200,
	    .paramList = {gpHALFunctionParam_200_uiSetDim,6},
	    .pfktHAL = HALfunc_ID200_uiSetDim
	},
	// HAL function info for uiInitPanel
	{
	    .fid = 201,
	    .paramList = {gpHALFunctionParam_201_uiInitPanel,3},
	    .pfktHAL = HALfunc_ID201_uiInitPanel
	},
	// HAL function info for uiInitButton
	{
	    .fid = 202,
	    .paramList = {gpHALFunctionParam_202_uiInitButton,5},
	    .pfktHAL = HALfunc_ID202_uiInitButton
	},
	// HAL function info for uiInitDisplay
	{
	    .fid = 203,
	    .paramList = {gpHALFunctionParam_203_uiInitDisplay,5},
	    .pfktHAL = HALfunc_ID203_uiInitDisplay
	},
	// HAL function info for uiInitLED
	{
	    .fid = 204,
	    .paramList = {gpHALFunctionParam_204_uiInitLED,5},
	    .pfktHAL = HALfunc_ID204_uiInitLED
	},
	// HAL function info for uiCheckButtonPressed
	{
	    .fid = 210,
	    .paramList = {gpHALFunctionParam_210_uiCheckButtonPressed,2},
	    .pfktHAL = HALfunc_ID210_uiCheckButtonPressed
	},
	// HAL function info for uiSetLED
	{
	    .fid = 211,
	    .paramList = {gpHALFunctionParam_211_uiSetLED,3},
	    .pfktHAL = HALfunc_ID211_uiSetLED
	},
	// HAL function info for uiSetDisplay
	{
	    .fid = 212,
	    .paramList = {gpHALFunctionParam_212_uiSetDisplay,4},
	    .pfktHAL = HALfunc_ID212_uiSetDisplay
	},
	// HAL function info for uiSetDisplayTextDim
	{
	    .fid = 213,
	    .paramList = {gpHALFunctionParam_213_uiSetDisplayTextDim,4},
	    .pfktHAL = HALfunc_ID213_uiSetDisplayTextDim
	},
	// HAL function info for calcDelay
	{
	    .fid = 150,
	    .paramList = {gpHALFunctionParam_150_calcDelay,3},
	    .pfktHAL = HALfunc_ID150_calcDelay
	},
	// HAL function info for initDelay
	{
	    .fid = 151,
	    .paramList = {gpHALFunctionParam_151_initDelay,3},
	    .pfktHAL = HALfunc_ID151_initDelay
	}
};
// the global HAL function info variable
THALFunctionList const gHALFunctionList = {gpFunctionInfoVector,55};



// not selected

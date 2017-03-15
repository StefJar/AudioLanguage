/*
 * ADSPinterface.h
 *
 *  Created on: 05.03.2012
 *      Author: StJ
 */

#ifndef ADSPINTERFACE_H_
#define ADSPINTERFACE_H_


typedef struct TCodecChannel {
	unsigned int	indx;	//!< index of the buffer
	unsigned int 	size;	//!< size of the channel
} TCodecChannel;

void readSamplesFromChannel (TCodecChannel * pIC, float * pBuffer, unsigned int amount);

void writesSamplesFromChannel (TCodecChannel * pOC, float * pBuffer, unsigned int amount);

void initADSP();

#endif /* ADSPINTERFACE_H_ */

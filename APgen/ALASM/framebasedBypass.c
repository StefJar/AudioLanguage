// Audio Language Code dump
#include <stdint.h>

#define dALCdumpVarCount (5)
#define dALCdumpInstrCount (7)
#define dALCdumpInstrSize (5)

// a constant global variable holding the values for the variables
const int32_t gcVars[] = {
	// rational amount: 1024
	1,1024,
	// rational amount: 1024
	1,1024,
	// complex amount: 1024
	4,1024,
	// FFT amount: 1
	30,1,
	// FFT amount: 1
	30,1,
	};
// a constant global variable holding the values for the instructions
const int32_t gcInstructions[] = {
	// initRFFT
	130,1024,0,2,3,
	// initIFFT
	131,1024,2,1,4,
	// readSampleFrame
	62,1,0,0,0,
	// processRFFT
	132,3,0,0,0,
	// processIFFT
	133,4,0,0,0,
	// writeSampleFrame
	63,2,1,0,0,
	// jump
	50,-4,0,0,0,
	};

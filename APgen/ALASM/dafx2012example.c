// Audio Language Code dump
#include <stdint.h>

int const gALCdumpEndian = 'l';
int const gALCdumpVarCount =3;
int const gALCdumpInstrCount =12;
int const gALCdumpInstrSize =5;

// a constant global variable holding the values for the variables
const int32_t gcVars[] = {
	// rational amount: 512
	0X000001,0X000200,
	// rational amount: 512
	0X000001,0X000200,
	// biquad amount: 8
	0X00000A,0X000008,
	};
// a constant global variable holding the values for the instructions
const int32_t gcInstructions[] = {
	// initBiquadAsHP
	0X000064,0X000000,0X473B8000,0X42B40000,0X000002,
	// initBiquadAsHP
	0X000064,0X000001,0X473B8000,0X42B40000,0X000002,
	// initBiquadAsHP
	0X000064,0X000002,0X473B8000,0X42B40000,0X000002,
	// initBiquadAsHP
	0X000064,0X000003,0X473B8000,0X42B40000,0X000002,
	// initBiquadAsLP
	0X000065,0X000004,0X473B8000,0X447A0000,0X000002,
	// initBiquadAsLP
	0X000065,0X000005,0X473B8000,0X447A0000,0X000002,
	// initBiquadAsLP
	0X000065,0X000006,0X473B8000,0X447A0000,0X000002,
	// initBiquadAsLP
	0X000065,0X000007,0X473B8000,0X447A0000,0X000002,
	// readSampleFrame
	0X00003E,0X000001,0X000000,0X000000,0X000000,
	// convoluteVectorBiquad
	0X00006F,0X000000,0X000002,0X000001,0X000000,
	// writeSampleFrame
	0X00003F,0X000002,0X000001,0X000000,0X000000,
	// jump
	0X000032,-0X00003,0X000000,0X000000,0X000000,
	};

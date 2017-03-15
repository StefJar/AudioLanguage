// Audio Language Code dump
#include <stdint.h>

int const gALCdumpEndian = 'l';
int const gALCdumpVarCount =1;
int const gALCdumpInstrCount =3;
int const gALCdumpInstrSize =7;

// a constant global variable holding the values for the variables
const int32_t gcVars[] = {
	// rational amount: 512
	0X000001,0X000200,
	};
// a constant global variable holding the values for the instructions
const int32_t gcInstructions[] = {
	// readSampleFrame
	0X00003E,0X000001,0X000000,0X000000,0X000000,0X000000,0X000000,
	// writeSampleFrame
	0X00003F,0X000002,0X000000,0X000000,0X000000,0X000000,0X000000,
	// jump
	0X000032,-0X00002,0X000000,0X000000,0X000000,0X000000,0X000000,
	};

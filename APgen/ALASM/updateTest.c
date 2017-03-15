// Audio Language Code dump
#include <stdint.h>

int const gALCdumpEndian = 'l';
int const gALCdumpVarCount =8;
int const gALCdumpInstrCount =33;
int const gALCdumpInstrSize =7;

// a constant global variable holding the values for the variables
const int32_t gcVars[] = {
	// integer amount: 1
	0X000002,0X000001,
	// panel amount: 1
	0X000064,0X000001,
	// button amount: 1
	0X000065,0X000001,
	// button amount: 1
	0X000065,0X000001,
	// display amount: 1
	0X000067,0X000001,
	// string amount: 2
	0X000003,0X000002,
	// integer amount: 1
	0X000002,0X000001,
	// integer amount: 1
	0X000002,0X000001,
	};
// a constant global variable holding the values for the instructions
const int32_t gcInstructions[] = {
	// setStringSize
	0X000005,0X000005,0X000000,0X00000E,0X000000,0X000000,0X000000,
	// setStringValues
	0X000006,0X000005,0X000000,0X000000,0X74747562,0X70206E6F,0X73736572,
	// setStringValues
	0X000006,0X000005,0X000000,0X00000C,0X20206465,0X20202020,0X20202020,
	// setStringSize
	0X000005,0X000005,0X000001,0X000004,0X000000,0X000000,0X000000,
	// setStringValues
	0X000006,0X000005,0X000001,0X000000,0X74696177,0X20202020,0X20202020,
	// assignConstInteger
	0X000014,0X000000,0X000000,0X000001,0X000000,0X000000,0X000000,
	// assignConstInteger
	0X000014,0X000006,0X000000,0X000001,0X000000,0X000000,0X000000,
	// assignConstInteger
	0X000014,0X000007,0X000000,0X000001,0X000001,0X000000,0X000000,
	// uiSetDim
	0X0000C8,0X000000,0X000000,0X00012C,0X0000C8,0X000001,0X000000,
	// uiInitPanel
	0X0000C9,0X000001,0X000001,0X000000,0X000000,0X000000,0X000000,
	// uiSetDim
	0X0000C8,0X00000A,0X00000A,0X000118,0X000096,0X000004,0X000000,
	// uiInitDisplay
	0X0000CB,0X00000B,0X000004,0X000000,0X000001,0X000000,0X000000,
	// uiSetDim
	0X0000C8,0X00000A,0X0000A0,0X00008C,0X000032,0X000002,0X000000,
	// uiInitButton
	0X0000CA,0X000015,0X000002,0X000000,0X000001,0X000000,0X000000,
	// uiSetDim
	0X0000C8,0X000096,0X0000A0,0X00008C,0X000032,0X000003,0X000000,
	// uiInitButton
	0X0000CA,0X000016,0X000003,0X000000,0X000001,0X000000,0X000000,
	// uiSetDisplay
	0X0000D4,0X000004,0X000000,0X000005,0X000001,0X000000,0X000000,
	// uiCheckButtonPressed
	0X0000D2,0X000002,0X000000,0X000000,0X000000,0X000000,0X000000,
	// jumpNCF
	0X000034,0X000004,0X000000,0X000000,0X000000,0X000000,0X000000,
	// setCF
	0X000037,0X000000,0X000000,0X000000,0X000000,0X000000,0X000000,
	// assignInteger
	0X000015,0X000000,0X000007,0X000000,0X000000,0X000000,0X000000,
	// update
	0X000038,0X000000,0X000000,0X000000,0X000000,0X000000,0X000000,
	// uiCheckButtonPressed
	0X0000D2,0X000003,0X000000,0X000000,0X000000,0X000000,0X000000,
	// jumpNCF
	0X000034,0X000004,0X000000,0X000000,0X000000,0X000000,0X000000,
	// setCF
	0X000037,0X000000,0X000000,0X000000,0X000000,0X000000,0X000000,
	// assignInteger
	0X000015,0X000000,0X000006,0X000000,0X000000,0X000000,0X000000,
	// uiSetDisplay
	0X0000D4,0X000004,0X000000,0X000005,0X000001,0X000000,0X000000,
	// comparaIntegerEqual
	0X00002A,0X000000,0X000000,0X000007,0X000000,0X000000,0X000000,
	// jumpNCF
	0X000034,0X000004,0X000000,0X000000,0X000000,0X000000,0X000000,
	// setCF
	0X000037,0X000000,0X000000,0X000000,0X000000,0X000000,0X000000,
	// uiSetDisplay
	0X0000D4,0X000004,0X000000,0X000005,0X000000,0X000000,0X000000,
	// assignInteger
	0X000015,0X000000,0X000006,0X000000,0X000000,0X000000,0X000000,
	// jump
	0X000032,-0X0000F,0X000000,0X000000,0X000000,0X000000,0X000000,
	};

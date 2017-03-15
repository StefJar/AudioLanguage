// audio language code file
// generated 2013-07-03 08:46:34

#include "ALTypeTest.h"

//! list containing the variables
const TALCvar gALCvars [7] = {
    // type: biquad amount: 6 
    {.type=10,.amount=6},
    // type: rational amount: 3 
    {.type=1,.amount=3},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: rational amount: 9 
    {.type=1,.amount=9},
    // type: biquad amount: 2 
    {.type=10,.amount=2},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[4] = {
	//PC:1 assignConstRational
	{{.ival=27},{.ival=5},{.ival=0},{.ival=1},{.fval=48000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:2 assignConstRational
	{{.ival=27},{.ival=6},{.ival=0},{.ival=1},{.fval=2000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:3 assignConstRational
	{{.ival=27},{.ival=2},{.ival=0},{.ival=1},{.fval=123.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:4 initBiquadAsLP
	{{.ival=101},{.ival=4},{.ival=0},{.ival=5},{.ival=6},{.ival=0},{.ival=0},{.ival=0},	},
};

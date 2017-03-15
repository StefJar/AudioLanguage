// audio language code file
// generated 2015-01-29 10:18:24

#include "DAFx2012.h"

//! list containing the variables
const TALCvar gALCvars [6] = {
    //VarIndx:0 type: rational amount: 1 
    {.type=1,.amount=1},
    //VarIndx:1 type: rational amount: 1 
    {.type=1,.amount=1},
    //VarIndx:2 type: rational amount: 1 
    {.type=1,.amount=1},
    //VarIndx:3 type: biquad amount: 8 
    {.type=10,.amount=8},
    //VarIndx:4 type: rational amount: 512 
    {.type=1,.amount=512},
    //VarIndx:5 type: rational amount: 512 
    {.type=1,.amount=512}
};
//! list containing the instructions
const TALCinstr gcInstructions[15] = {
	//PC:1 assignConstRational
	{{.ival=27},{.ival=0},{.ival=0},{.ival=1},{.fval=48000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:2 assignConstRational
	{{.ival=27},{.ival=2},{.ival=0},{.ival=1},{.fval=1000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:3 assignConstRational
	{{.ival=27},{.ival=1},{.ival=0},{.ival=1},{.fval=90.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:4 initBiquadAsHP
	{{.ival=100},{.ival=3},{.ival=0},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:5 initBiquadAsHP
	{{.ival=100},{.ival=3},{.ival=1},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:6 initBiquadAsHP
	{{.ival=100},{.ival=3},{.ival=2},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:7 initBiquadAsHP
	{{.ival=100},{.ival=3},{.ival=3},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:8 initBiquadAsLP
	{{.ival=101},{.ival=3},{.ival=4},{.ival=0},{.ival=2},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:9 initBiquadAsLP
	{{.ival=101},{.ival=3},{.ival=5},{.ival=0},{.ival=2},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:10 initBiquadAsLP
	{{.ival=101},{.ival=3},{.ival=6},{.ival=0},{.ival=2},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:11 initBiquadAsLP
	{{.ival=101},{.ival=3},{.ival=7},{.ival=0},{.ival=2},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:12 readSampleFrame
	{{.ival=62},{.ival=1},{.ival=5},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:13 convoluteBiquad
	{{.ival=110},{.ival=5},{.ival=3},{.ival=4},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:14 writeSampleFrame
	{{.ival=63},{.ival=2},{.ival=4},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:15 jump
	{{.ival=50},{.ival=-3},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
};

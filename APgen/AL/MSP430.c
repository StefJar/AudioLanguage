// audio language code file
// generated 2013-03-15 13:29:20

#include "MSP430.h"

//! list containing the variables
const TALCvar gALCvars [14] = {
    // type: biquad amount: 2 
    {.type=10,.amount=2},
    // type: led amount: 1 
    {.type=102,.amount=1},
    // type: button amount: 1 
    {.type=101,.amount=1},
    // type: string amount: 1 
    {.type=3,.amount=1},
    // type: panel amount: 1 
    {.type=100,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: led amount: 1 
    {.type=102,.amount=1},
    // type: button amount: 1 
    {.type=101,.amount=1},
    // type: display amount: 1 
    {.type=103,.amount=1},
    // type: button amount: 1 
    {.type=101,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1},
    // type: rational amount: 1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[50] = {
	//PC:1 uiSetDim
	{{.ival=200},{.ival=0},{.ival=0},{.ival=550},{.ival=500},{.ival=4},{.ival=0},{.ival=0},	},
	//PC:2 uiInitPanel
	{{.ival=201},{.ival=1},{.ival=4},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:3 uiSetDim
	{{.ival=200},{.ival=10},{.ival=10},{.ival=500},{.ival=300},{.ival=10},{.ival=0},{.ival=0},	},
	//PC:4 uiInitDisplay
	{{.ival=203},{.ival=11},{.ival=10},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:5 uiSetDim
	{{.ival=200},{.ival=50},{.ival=400},{.ival=50},{.ival=50},{.ival=11},{.ival=0},{.ival=0},	},
	//PC:6 uiInitButton
	{{.ival=202},{.ival=21},{.ival=11},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:7 uiSetDim
	{{.ival=200},{.ival=150},{.ival=400},{.ival=50},{.ival=50},{.ival=8},{.ival=0},{.ival=0},	},
	//PC:8 uiInitLED
	{{.ival=204},{.ival=31},{.ival=8},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:9 uiSetDim
	{{.ival=200},{.ival=250},{.ival=400},{.ival=50},{.ival=50},{.ival=9},{.ival=0},{.ival=0},	},
	//PC:10 uiInitButton
	{{.ival=202},{.ival=22},{.ival=9},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:11 uiSetDim
	{{.ival=200},{.ival=350},{.ival=400},{.ival=50},{.ival=50},{.ival=1},{.ival=0},{.ival=0},	},
	//PC:12 uiInitLED
	{{.ival=204},{.ival=31},{.ival=1},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:13 uiSetDim
	{{.ival=200},{.ival=450},{.ival=400},{.ival=50},{.ival=50},{.ival=2},{.ival=0},{.ival=0},	},
	//PC:14 uiInitButton
	{{.ival=202},{.ival=23},{.ival=2},{.ival=0},{.ival=4},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:15 setStringSize
	{{.ival=5},{.ival=3},{.ival=0},{.ival=35},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:16 setStringValues
	{{.ival=6},{.ival=3},{.ival=0},{.ival=0},{.rawVal=1952867692},{.rawVal=542133309},{.rawVal=1832603724},{.rawVal=1818518633},	},
	//PC:17 setStringValues
	{{.ival=6},{.ival=3},{.ival=0},{.ival=16},{.rawVal=1346911589},{.rawVal=995118112},{.rawVal=1751607666},{.rawVal=1346911604},	},
	//PC:18 setStringValues
	{{.ival=6},{.ival=3},{.ival=0},{.ival=32},{.rawVal=542132256},{.rawVal=538976288},{.rawVal=538976288},{.rawVal=538976288},	},
	//PC:19 assignConstRational
	{{.ival=27},{.ival=5},{.ival=0},{.ival=1},{.fval=48000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:20 assignConstRational
	{{.ival=27},{.ival=7},{.ival=0},{.ival=1},{.fval=1.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:21 assignConstRational
	{{.ival=27},{.ival=13},{.ival=0},{.ival=1},{.fval=2.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:22 uiSetDisplay
	{{.ival=212},{.ival=10},{.ival=0},{.ival=3},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:23 uiSetLED
	{{.ival=211},{.ival=8},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:24 uiSetLED
	{{.ival=211},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:25 uiCheckButtonPressed
	{{.ival=210},{.ival=11},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:26 jumpNCF
	{{.ival=52},{.ival=7},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:27 assignConstRational
	{{.ival=27},{.ival=12},{.ival=0},{.ival=1},{.fval=70.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:28 initBiquadAsLP
	{{.ival=101},{.ival=0},{.ival=0},{.ival=5},{.ival=12},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:29 initBiquadAsLP
	{{.ival=101},{.ival=0},{.ival=1},{.ival=5},{.ival=12},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:30 uiSetLED
	{{.ival=211},{.ival=8},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:31 uiSetLED
	{{.ival=211},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:32 update
	{{.ival=56},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:33 uiCheckButtonPressed
	{{.ival=210},{.ival=9},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:34 jumpNCF
	{{.ival=52},{.ival=8},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:35 assignConstRational
	{{.ival=27},{.ival=12},{.ival=0},{.ival=1},{.fval=1000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:36 assignConstRational
	{{.ival=27},{.ival=6},{.ival=0},{.ival=1},{.fval=2000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:37 initBiquadAsHP
	{{.ival=100},{.ival=0},{.ival=0},{.ival=5},{.ival=12},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:38 initBiquadAsLP
	{{.ival=101},{.ival=0},{.ival=1},{.ival=5},{.ival=6},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:39 uiSetLED
	{{.ival=211},{.ival=8},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:40 uiSetLED
	{{.ival=211},{.ival=1},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:41 update
	{{.ival=56},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:42 uiCheckButtonPressed
	{{.ival=210},{.ival=2},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:43 jumpNCF
	{{.ival=52},{.ival=7},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:44 assignConstRational
	{{.ival=27},{.ival=12},{.ival=0},{.ival=1},{.fval=4000.0},{.fval=0.0},{.fval=0.0},{.fval=0.0},	},
	//PC:45 initBiquadAsHP
	{{.ival=100},{.ival=0},{.ival=0},{.ival=5},{.ival=12},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:46 initBiquadAsHP
	{{.ival=100},{.ival=0},{.ival=1},{.ival=5},{.ival=12},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:47 uiSetLED
	{{.ival=211},{.ival=8},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:48 uiSetLED
	{{.ival=211},{.ival=1},{.ival=0},{.ival=1},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:49 update
	{{.ival=56},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
	//PC:50 jump
	{{.ival=50},{.ival=-25},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},{.ival=0},	},
};

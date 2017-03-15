// audio language code file
// generated 2015-03-25 21:23:00

#include "DAP26_ADSP.h"

//! list containing the variables
const TALCvar gALCvars [51] = {
    //0: name="oChan4_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //1: name="oChan4_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //2: name="oChan4_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //3: name="oChan4_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //4: name="oChan4_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //5: name="oChan3_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //6: name="oChan3_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //7: name="oChan3_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //8: name="oChan3_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //9: name="oChan3_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //10: name="oChan2_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //11: name="oChan2_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //12: name="oChan2_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //13: name="oChan2_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //14: name="oChan2_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //15: name="oChan1_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //16: name="oChan1_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //17: name="oChan1_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //18: name="oChan1_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //19: name="oChan1_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //20: name="iChan1_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //21: name="iChan1_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //22: name="iChan1_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //23: name="iChan2_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //24: name="iChan2_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //25: name="iChan2_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //26: name="in1" type="rational" amount=256 
    {.type=1,.amount=256},
    //27: name="in2" type="rational" amount=256 
    {.type=1,.amount=256},
    //28: name="out" type="rational" amount=256 
    {.type=1,.amount=256},
    //29: name="#fv_initInputChannel_ichannel_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //30: name="#fv_initInputChannel_ichannel_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //31: name="#fv_initInputChannel_ichannel_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //32: name="#const16" type="rational" amount=1 
    {.type=1,.amount=1},
    //33: name="#const17" type="integer" amount=1 
    {.type=2,.amount=1},
    //34: name="#fv_initOutputChannel_ochannel_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //35: name="#fv_initOutputChannel_ochannel_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //36: name="#fv_initOutputChannel_ochannel_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //37: name="#fv_initOutputChannel_ochannel_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //38: name="#fv_initOutputChannel_ochannel_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //39: name="#fv_processInputChannel_y" type="rational" amount=256 
    {.type=1,.amount=256},
    //40: name="#fv_processInputChannel_x" type="rational" amount=256 
    {.type=1,.amount=256},
    //41: name="#fv_processInputChannel_ichannel_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //42: name="#fv_processInputChannel_ichannel_d" type="delay" amount=1 
    {.type=20,.amount=1},
    //43: name="#fv_processInputChannel_ichannel_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //44: name="#fv_processOutputChannel_y" type="rational" amount=256 
    {.type=1,.amount=256},
    //45: name="#fv_processOutputChannel_x" type="rational" amount=256 
    {.type=1,.amount=256},
    //46: name="#fv_processOutputChannel_ochannel_xo" type="biquad" amount=3 
    {.type=10,.amount=3},
    //47: name="#fv_processOutputChannel_ochannel_eq" type="biquad" amount=5 
    {.type=10,.amount=5},
    //48: name="#fv_processOutputChannel_ochannel_l" type="limiter" amount=1 
    {.type=14,.amount=1},
    //49: name="#fv_processOutputChannel_ochannel_g" type="rational" amount=1 
    {.type=1,.amount=1},
    //50: name="#fv_processOutputChannel_ochannel_d" type="delay" amount=1 
    {.type=20,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[91] = {
    /* PC 0: assignConstRational (#const16, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=32}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 1: assignConstInteger (#const17, 0, 1, 1)*/
    {{.ival=20}, {.ival=33}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 2: assignRational (#fv_initInputChannel_ichannel, #const16)*/
    {{.ival=28}, {.ival=31}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 3: initDelay (#fv_initInputChannel_ichannel, #const17, 0, 0)*/
    {{.ival=151}, {.ival=30}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 4: initBiquad (#fv_initInputChannel_ichannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 5: initBiquad (#fv_initInputChannel_ichannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 6: initBiquad (#fv_initInputChannel_ichannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 7: initBiquad (#fv_initInputChannel_ichannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 8: initBiquad (#fv_initInputChannel_ichannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 9: assignRational (#fv_initInputChannel_ichannel, #const16)*/
    {{.ival=28}, {.ival=31}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 10: initDelay (#fv_initInputChannel_ichannel, #const17, 0, 0)*/
    {{.ival=151}, {.ival=30}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 11: initBiquad (#fv_initInputChannel_ichannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 12: initBiquad (#fv_initInputChannel_ichannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 13: initBiquad (#fv_initInputChannel_ichannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 14: initBiquad (#fv_initInputChannel_ichannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 15: initBiquad (#fv_initInputChannel_ichannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=29}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 16: initDelay (#fv_initOutputChannel_ochannel, #const17 = "1"(integer), 0, 0)*/
    {{.ival=151}, {.ival=38}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 17: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 18: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 19: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 20: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 21: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 22: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 23: initBiquad (#fv_initOutputChannel_ochannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 24: initBiquad (#fv_initOutputChannel_ochannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 25: assignRational (#fv_initOutputChannel_ochannel, #const16 = "1.0"(rational))*/
    {{.ival=28}, {.ival=37}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: initLimiter (#fv_initOutputChannel_ochannel, 0.9, 0.7, 0.045, 0.056, 0.045, 0.0465)*/
    {{.ival=114}, {.ival=36}, {.fval=0.9}, {.fval=0.7}, {.fval=0.045}, {.fval=0.056}, {.fval=0.045}, {.fval=0.0465}},
    /* PC 27: initDelay (#fv_initOutputChannel_ochannel, #const17 = "1"(integer), 0, 0)*/
    {{.ival=151}, {.ival=38}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 28: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 29: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 30: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 31: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 32: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 33: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 34: initBiquad (#fv_initOutputChannel_ochannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 35: initBiquad (#fv_initOutputChannel_ochannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 36: assignRational (#fv_initOutputChannel_ochannel, #const16 = "1.0"(rational))*/
    {{.ival=28}, {.ival=37}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: initLimiter (#fv_initOutputChannel_ochannel, 0.9, 0.7, 0.045, 0.056, 0.045, 0.0465)*/
    {{.ival=114}, {.ival=36}, {.fval=0.9}, {.fval=0.7}, {.fval=0.045}, {.fval=0.056}, {.fval=0.045}, {.fval=0.0465}},
    /* PC 38: initDelay (#fv_initOutputChannel_ochannel, #const17 = "1"(integer), 0, 0)*/
    {{.ival=151}, {.ival=38}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 40: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 41: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 42: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 43: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 44: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 45: initBiquad (#fv_initOutputChannel_ochannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 46: initBiquad (#fv_initOutputChannel_ochannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 47: assignRational (#fv_initOutputChannel_ochannel, #const16 = "1.0"(rational))*/
    {{.ival=28}, {.ival=37}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: initLimiter (#fv_initOutputChannel_ochannel, 0.9, 0.7, 0.045, 0.056, 0.045, 0.0465)*/
    {{.ival=114}, {.ival=36}, {.fval=0.9}, {.fval=0.7}, {.fval=0.045}, {.fval=0.056}, {.fval=0.045}, {.fval=0.0465}},
    /* PC 49: initDelay (#fv_initOutputChannel_ochannel, #const17 = "1"(integer), 0, 0)*/
    {{.ival=151}, {.ival=38}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 51: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 52: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=34}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 53: initBiquad (#fv_initOutputChannel_ochannel, 0, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 54: initBiquad (#fv_initOutputChannel_ochannel, 1, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=1}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 55: initBiquad (#fv_initOutputChannel_ochannel, 2, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=2}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 56: initBiquad (#fv_initOutputChannel_ochannel, 3, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=3}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 57: initBiquad (#fv_initOutputChannel_ochannel, 4, 0.0, 0.0, 0.0, 0.0, 0.0)*/
    {{.ival=105}, {.ival=35}, {.ival=4}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}, {.ival=0.0}},
    /* PC 58: assignRational (#fv_initOutputChannel_ochannel, #const16 = "1.0"(rational))*/
    {{.ival=28}, {.ival=37}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 59: initLimiter (#fv_initOutputChannel_ochannel, 0.9, 0.7, 0.045, 0.056, 0.045, 0.0465)*/
    {{.ival=114}, {.ival=36}, {.fval=0.9}, {.fval=0.7}, {.fval=0.045}, {.fval=0.056}, {.fval=0.045}, {.fval=0.0465}},
    /* PC 60: label ID:40*/
    /* PC 60: readSampleFrame (1, in1, 1)*/
    {{.ival=62}, {.ival=1}, {.ival=26}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 61: readSampleFrame (2, in2, 0)*/
    {{.ival=62}, {.ival=2}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 62: calcDelay (#fv_processInputChannel_y, #fv_processInputChannel_ichannel, #fv_processInputChannel_x)*/
    {{.ival=150}, {.ival=39}, {.ival=42}, {.ival=40}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 63: mulRational (#fv_processInputChannel_y, #fv_processInputChannel_y, #fv_processInputChannel_ichannel)*/
    {{.ival=31}, {.ival=39}, {.ival=39}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 64: convoluteBiquad (#fv_processInputChannel_y, #fv_processInputChannel_ichannel, #fv_processInputChannel_y)*/
    {{.ival=110}, {.ival=39}, {.ival=41}, {.ival=39}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 65: calcDelay (#fv_processInputChannel_y, #fv_processInputChannel_ichannel, #fv_processInputChannel_x)*/
    {{.ival=150}, {.ival=39}, {.ival=42}, {.ival=40}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 66: mulRational (#fv_processInputChannel_y, #fv_processInputChannel_y, #fv_processInputChannel_ichannel)*/
    {{.ival=31}, {.ival=39}, {.ival=39}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 67: convoluteBiquad (#fv_processInputChannel_y, #fv_processInputChannel_ichannel, #fv_processInputChannel_y)*/
    {{.ival=110}, {.ival=39}, {.ival=41}, {.ival=39}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 68: calcDelay (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_x)*/
    {{.ival=150}, {.ival=44}, {.ival=50}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 69: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=46}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 70: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=47}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 71: mulRational (#fv_processOutputChannel_y, #fv_processOutputChannel_y, #fv_processOutputChannel_ochannel)*/
    {{.ival=31}, {.ival=44}, {.ival=44}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 72: calcLimiter (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=118}, {.ival=44}, {.ival=48}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 73: writeSampleFrame (1, out)*/
    {{.ival=63}, {.ival=1}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 74: calcDelay (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_x)*/
    {{.ival=150}, {.ival=44}, {.ival=50}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 75: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=46}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 76: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=47}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 77: mulRational (#fv_processOutputChannel_y, #fv_processOutputChannel_y, #fv_processOutputChannel_ochannel)*/
    {{.ival=31}, {.ival=44}, {.ival=44}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 78: calcLimiter (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=118}, {.ival=44}, {.ival=48}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 79: writeSampleFrame (2, out)*/
    {{.ival=63}, {.ival=2}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 80: calcDelay (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_x)*/
    {{.ival=150}, {.ival=44}, {.ival=50}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 81: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=46}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 82: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=47}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 83: mulRational (#fv_processOutputChannel_y, #fv_processOutputChannel_y, #fv_processOutputChannel_ochannel)*/
    {{.ival=31}, {.ival=44}, {.ival=44}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 84: calcLimiter (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=118}, {.ival=44}, {.ival=48}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 85: calcDelay (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_x)*/
    {{.ival=150}, {.ival=44}, {.ival=50}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 86: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=46}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 87: convoluteBiquad (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=110}, {.ival=44}, {.ival=47}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 88: mulRational (#fv_processOutputChannel_y, #fv_processOutputChannel_y, #fv_processOutputChannel_ochannel)*/
    {{.ival=31}, {.ival=44}, {.ival=44}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 89: calcLimiter (#fv_processOutputChannel_y, #fv_processOutputChannel_ochannel, #fv_processOutputChannel_y)*/
    {{.ival=118}, {.ival=44}, {.ival=48}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 90: jump (label ID:40)*/
    {{.ival=50}, {.ival=-30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

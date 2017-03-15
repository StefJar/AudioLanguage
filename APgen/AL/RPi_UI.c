// audio language code file
// generated 2015-03-27 16:17:11

#include "RPi_UI.h"

//! list containing the variables
const TALCvar gALCvars [21] = {
    //0: name="bqf1" type="biquad" amount=2 
    {.type=10,.amount=2},
    //1: name="bqf2" type="biquad" amount=2 
    {.type=10,.amount=2},
    //2: name="f2" type="rational" amount=1 
    {.type=1,.amount=1},
    //3: name="fs" type="rational" amount=1 
    {.type=1,.amount=1},
    //4: name="d" type="display" amount=1 
    {.type=103,.amount=1},
    //5: name="g" type="rational" amount=1 
    {.type=1,.amount=1},
    //6: name="f" type="rational" amount=1 
    {.type=1,.amount=1},
    //7: name="q" type="rational" amount=1 
    {.type=1,.amount=1},
    //8: name="p" type="panel" amount=1 
    {.type=100,.amount=1},
    //9: name="bRight" type="button" amount=1 
    {.type=101,.amount=1},
    //10: name="bLeft" type="button" amount=1 
    {.type=101,.amount=1},
    //11: name="bMiddle" type="button" amount=1 
    {.type=101,.amount=1},
    //12: name="tstr" type="string" amount=1 
    {.type=3,.amount=1},
    //13: name="#const1" type="string" amount=1 
    {.type=3,.amount=1},
    //14: name="#const2" type="rational" amount=1 
    {.type=1,.amount=1},
    //15: name="#const3" type="rational" amount=1 
    {.type=1,.amount=1},
    //16: name="#const4" type="rational" amount=1 
    {.type=1,.amount=1},
    //17: name="#const5" type="rational" amount=1 
    {.type=1,.amount=1},
    //18: name="#const6" type="rational" amount=1 
    {.type=1,.amount=1},
    //19: name="#const7" type="rational" amount=1 
    {.type=1,.amount=1},
    //20: name="#const8" type="rational" amount=1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[55] = {
    /* PC 0: setStringSize (#const1, 0, 35)*/
    {{.ival=5}, {.ival=13}, {.ival=0}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: setStringValues (#const1, 0, 0, 1952867692, 542133309, 1832603724, 1818518633)*/
    {{.ival=6}, {.ival=13}, {.ival=0}, {.ival=0}, {.rawVal=1952867692}, {.rawVal=542133309}, {.rawVal=1832603724}, {.rawVal=1818518633}},
    /* PC 2: setStringValues (#const1, 0, 16, 1346911589, 995118112, 1751607666, 1346911604)*/
    {{.ival=6}, {.ival=13}, {.ival=0}, {.ival=16}, {.rawVal=1346911589}, {.rawVal=995118112}, {.rawVal=1751607666}, {.rawVal=1346911604}},
    /* PC 3: setStringValues (#const1, 0, 32, 542132256, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=13}, {.ival=0}, {.ival=32}, {.rawVal=542132256}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 4: assignConstRational (#const2, 0, 1, 44100.0)*/
    {{.ival=27}, {.ival=14}, {.ival=0}, {.ival=1}, {.fval=44100.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 5: assignConstRational (#const3, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=15}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 6: assignConstRational (#const4, 0, 1, 2.0)*/
    {{.ival=27}, {.ival=16}, {.ival=0}, {.ival=1}, {.fval=2.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 7: assignConstRational (#const5, 0, 1, 70.0)*/
    {{.ival=27}, {.ival=17}, {.ival=0}, {.ival=1}, {.fval=70.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 8: assignConstRational (#const6, 0, 1, 1000.0)*/
    {{.ival=27}, {.ival=18}, {.ival=0}, {.ival=1}, {.fval=1000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 9: assignConstRational (#const7, 0, 1, 2000.0)*/
    {{.ival=27}, {.ival=19}, {.ival=0}, {.ival=1}, {.fval=2000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 10: assignConstRational (#const8, 0, 1, 4000.0)*/
    {{.ival=27}, {.ival=20}, {.ival=0}, {.ival=1}, {.fval=4000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 11: uiSetDim (0, 0, 550, 500, p, 0)*/
    {{.ival=200}, {.ival=0}, {.ival=0}, {.ival=550}, {.ival=500}, {.ival=8}, {.ival=0}, {.ival=0}},
    /* PC 12: uiInitPanel (1, p, 0)*/
    {{.ival=201}, {.ival=1}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 13: uiSetDim (10, 10, 500, 300, d, 0)*/
    {{.ival=200}, {.ival=10}, {.ival=10}, {.ival=500}, {.ival=300}, {.ival=4}, {.ival=0}, {.ival=0}},
    /* PC 14: uiInitDisplay (1, d, 0, p, 0)*/
    {{.ival=203}, {.ival=1}, {.ival=4}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 15: uiSetDim (50, 400, 50, 50, bLeft, 0)*/
    {{.ival=200}, {.ival=50}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=10}, {.ival=0}, {.ival=0}},
    /* PC 16: uiInitButton (1, bLeft, 0, p, 0)*/
    {{.ival=202}, {.ival=1}, {.ival=10}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 17: uiSetDim (250, 400, 50, 50, bMiddle, 0)*/
    {{.ival=200}, {.ival=250}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=11}, {.ival=0}, {.ival=0}},
    /* PC 18: uiInitButton (2, bMiddle, 0, p, 0)*/
    {{.ival=202}, {.ival=2}, {.ival=11}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 19: uiSetDim (450, 400, 50, 50, bRight, 0)*/
    {{.ival=200}, {.ival=450}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=9}, {.ival=0}, {.ival=0}},
    /* PC 20: uiInitButton (3, bRight, 0, p, 0)*/
    {{.ival=202}, {.ival=3}, {.ival=9}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 21: assignString (tstr, 0, #const1, 0)*/
    {{.ival=10}, {.ival=12}, {.ival=0}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 22: assignRational (fs, #const2)*/
    {{.ival=28}, {.ival=3}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 23: assignRational (q, #const3)*/
    {{.ival=28}, {.ival=7}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 24: assignRational (g, #const4)*/
    {{.ival=28}, {.ival=5}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 25: uiSetDisplay (d, 0, tstr, 0)*/
    {{.ival=212}, {.ival=4}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: label ID:5*/
    /* PC 26: uiCheckButtonPressed (bLeft, 0)*/
    {{.ival=210}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 27: jumpNCF (label ID:2)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 28: assignRational (f, #const5)*/
    {{.ival=28}, {.ival=6}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 29: initBiquadAsLP (bqf1, 0, fs, f)*/
    {{.ival=101}, {.ival=0}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 30: initBiquadAsLP (bqf1, 1, fs, f)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 31: initBiquadAsLP (bqf2, 0, fs, f)*/
    {{.ival=101}, {.ival=1}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: initBiquadAsLP (bqf2, 1, fs, f)*/
    {{.ival=101}, {.ival=1}, {.ival=1}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 33: update (bqf1)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: update (bqf2)*/
    {{.ival=56}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 35: label ID:2*/
    /* PC 35: uiCheckButtonPressed (bMiddle, 0)*/
    {{.ival=210}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: jumpNCF (label ID:3)*/
    {{.ival=52}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: assignRational (f, #const6)*/
    {{.ival=28}, {.ival=6}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: assignRational (f2, #const7)*/
    {{.ival=28}, {.ival=2}, {.ival=19}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: initBiquadAsHP (bqf1, 0, fs, f)*/
    {{.ival=100}, {.ival=0}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: initBiquadAsLP (bqf1, 1, fs, f2)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=3}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 41: initBiquadAsHP (bqf2, 0, fs, f)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: initBiquadAsLP (bqf2, 1, fs, f2)*/
    {{.ival=101}, {.ival=1}, {.ival=1}, {.ival=3}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 43: update (bqf1)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: update (bqf2)*/
    {{.ival=56}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 45: label ID:3*/
    /* PC 45: uiCheckButtonPressed (bRight, 0)*/
    {{.ival=210}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: jumpNCF (label ID:4)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 47: assignRational (f, #const8)*/
    {{.ival=28}, {.ival=6}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: initBiquadAsHP (bqf1, 0, fs, f)*/
    {{.ival=100}, {.ival=0}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 49: initBiquadAsHP (bqf1, 1, fs, f)*/
    {{.ival=100}, {.ival=0}, {.ival=1}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: initBiquadAsHP (bqf2, 0, fs, f)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 51: initBiquadAsHP (bqf2, 1, fs, f)*/
    {{.ival=100}, {.ival=1}, {.ival=1}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 52: update (bqf1)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 53: update (bqf2)*/
    {{.ival=56}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 54: label ID:4*/
    /* PC 54: jump (label ID:5)*/
    {{.ival=50}, {.ival=-28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

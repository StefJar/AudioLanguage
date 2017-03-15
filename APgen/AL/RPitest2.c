// audio language code file
// generated 2015-07-16 15:39:25

#include "RPitest2.h"

//! list containing the variables
const TALCvar gALCvars [42] = {
    //0: name="bqf1" type="biquad" amount=2 
    {.type=10,.amount=2},
    //1: name="bqf2" type="biquad" amount=2 
    {.type=10,.amount=2},
    //2: name="gaintext" type="string" amount=1 
    {.type=3,.amount=1},
    //3: name="gainStr" type="string" amount=1 
    {.type=3,.amount=1},
    //4: name="bHP" type="button" amount=1 
    {.type=101,.amount=1},
    //5: name="p" type="panel" amount=1 
    {.type=100,.amount=1},
    //6: name="fLP" type="rational" amount=1 
    {.type=1,.amount=1},
    //7: name="bDown" type="button" amount=1 
    {.type=101,.amount=1},
    //8: name="bReset" type="button" amount=1 
    {.type=101,.amount=1},
    //9: name="fHP" type="rational" amount=1 
    {.type=1,.amount=1},
    //10: name="fs" type="rational" amount=1 
    {.type=1,.amount=1},
    //11: name="byPassFlag" type="integer" amount=1 
    {.type=2,.amount=1},
    //12: name="in1" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //13: name="in2" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //14: name="gain" type="rational" amount=1 
    {.type=1,.amount=1},
    //15: name="out1" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //16: name="out2" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //17: name="d" type="display" amount=1 
    {.type=103,.amount=1},
    //18: name="g" type="rational" amount=1 
    {.type=1,.amount=1},
    //19: name="bUp" type="button" amount=1 
    {.type=101,.amount=1},
    //20: name="bLP" type="button" amount=1 
    {.type=101,.amount=1},
    //21: name="q" type="rational" amount=1 
    {.type=1,.amount=1},
    //22: name="bBypass" type="button" amount=1 
    {.type=101,.amount=1},
    //23: name="bBP" type="button" amount=1 
    {.type=101,.amount=1},
    //24: name="#const1" type="rational" amount=1 
    {.type=1,.amount=1},
    //25: name="#const2" type="rational" amount=1 
    {.type=1,.amount=1},
    //26: name="#const3" type="rational" amount=1 
    {.type=1,.amount=1},
    //27: name="#const4" type="rational" amount=1 
    {.type=1,.amount=1},
    //28: name="#const5" type="rational" amount=1 
    {.type=1,.amount=1},
    //29: name="#const6" type="integer" amount=1 
    {.type=2,.amount=1},
    //30: name="#const7" type="string" amount=1 
    {.type=3,.amount=1},
    //31: name="#const8" type="string" amount=1 
    {.type=3,.amount=1},
    //32: name="#const9" type="rational" amount=1 
    {.type=1,.amount=1},
    //33: name="#const10" type="rational" amount=1 
    {.type=1,.amount=1},
    //34: name="#const11" type="string" amount=1 
    {.type=3,.amount=1},
    //35: name="#const12" type="rational" amount=1 
    {.type=1,.amount=1},
    //36: name="#const13" type="string" amount=1 
    {.type=3,.amount=1},
    //37: name="#const14" type="string" amount=1 
    {.type=3,.amount=1},
    //38: name="#const15" type="integer" amount=1 
    {.type=2,.amount=1},
    //39: name="#const16" type="string" amount=1 
    {.type=3,.amount=1},
    //40: name="#const17" type="string" amount=1 
    {.type=3,.amount=1},
    //41: name="#const18" type="string" amount=1 
    {.type=3,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[117] = {
    /* PC 0: assignConstRational (#const1, 0, 1, 44100.0)*/
    {{.ival=27}, {.ival=24}, {.ival=0}, {.ival=1}, {.fval=44100.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 1: assignConstRational (#const2, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=25}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 2: assignConstRational (#const3, 0, 1, 2.0)*/
    {{.ival=27}, {.ival=26}, {.ival=0}, {.ival=1}, {.fval=2.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 3: assignConstRational (#const4, 0, 1, 8000.0)*/
    {{.ival=27}, {.ival=27}, {.ival=0}, {.ival=1}, {.fval=8000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 4: assignConstRational (#const5, 0, 1, 1000.0)*/
    {{.ival=27}, {.ival=28}, {.ival=0}, {.ival=1}, {.fval=1000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 5: assignConstInteger (#const6, 0, 1, 1)*/
    {{.ival=20}, {.ival=29}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 6: setStringSize (#const7, 0, 31)*/
    {{.ival=5}, {.ival=30}, {.ival=0}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 7: setStringValues (#const7, 0, 0, 1701602675, 540701795, 2036477233, 1936941424)*/
    {{.ival=6}, {.ival=30}, {.ival=0}, {.ival=0}, {.rawVal=1701602675}, {.rawVal=540701795}, {.rawVal=2036477233}, {.rawVal=1936941424}},
    /* PC 8: setStringValues (#const7, 0, 16, 1278030346, 758325328, 874532930, 542132269)*/
    {{.ival=6}, {.ival=30}, {.ival=0}, {.ival=16}, {.rawVal=1278030346}, {.rawVal=758325328}, {.rawVal=874532930}, {.rawVal=542132269}},
    /* PC 9: setStringSize (#const8, 0, 5)*/
    {{.ival=5}, {.ival=31}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 10: setStringValues (#const8, 0, 0, 1702061426, 538976372, 538976288, 538976288)*/
    {{.ival=6}, {.ival=31}, {.ival=0}, {.ival=0}, {.rawVal=1702061426}, {.rawVal=538976372}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 11: assignConstRational (#const9, 0, 1, 10.0)*/
    {{.ival=27}, {.ival=32}, {.ival=0}, {.ival=1}, {.fval=10.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 12: assignConstRational (#const10, 0, 1, 0.1)*/
    {{.ival=27}, {.ival=33}, {.ival=0}, {.ival=1}, {.fval=0.1}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 13: setStringSize (#const11, 0, 14)*/
    {{.ival=5}, {.ival=34}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 14: setStringValues (#const11, 0, 0, 1852399975, 175142176, 1970037078, 538983013)*/
    {{.ival=6}, {.ival=34}, {.ival=0}, {.ival=0}, {.rawVal=1852399975}, {.rawVal=175142176}, {.rawVal=1970037078}, {.rawVal=538983013}},
    /* PC 15: assignConstRational (#const12, 0, 1, 0.0)*/
    {{.ival=27}, {.ival=35}, {.ival=0}, {.ival=1}, {.fval=0.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 16: setStringSize (#const13, 0, 16)*/
    {{.ival=5}, {.ival=36}, {.ival=0}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 17: setStringValues (#const13, 0, 0, 1852399975, 2003788832, 1633028718, 979727724)*/
    {{.ival=6}, {.ival=36}, {.ival=0}, {.ival=0}, {.rawVal=1852399975}, {.rawVal=2003788832}, {.rawVal=1633028718}, {.rawVal=979727724}},
    /* PC 18: setStringSize (#const14, 0, 24)*/
    {{.ival=5}, {.ival=37}, {.ival=0}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 19: setStringValues (#const14, 0, 0, 2036473918, 1936941392, 758123040, 824201292)*/
    {{.ival=6}, {.ival=37}, {.ival=0}, {.ival=0}, {.rawVal=2036473918}, {.rawVal=1936941392}, {.rawVal=758123040}, {.rawVal=824201292}},
    /* PC 20: setStringValues (#const14, 0, 16, 542130733, 1346907442, 538976288, 538976288)*/
    {{.ival=6}, {.ival=37}, {.ival=0}, {.ival=16}, {.rawVal=542130733}, {.rawVal=1346907442}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 21: assignConstInteger (#const15, 0, 1, 0)*/
    {{.ival=20}, {.ival=38}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 22: setStringSize (#const16, 0, 20)*/
    {{.ival=5}, {.ival=39}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 23: setStringValues (#const16, 0, 0, 1347166270, 758123040, 824201292, 542130733)*/
    {{.ival=6}, {.ival=39}, {.ival=0}, {.ival=0}, {.rawVal=1347166270}, {.rawVal=758123040}, {.rawVal=824201292}, {.rawVal=542130733}},
    /* PC 24: setStringValues (#const16, 0, 16, 1346907442, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=39}, {.ival=0}, {.ival=16}, {.rawVal=1346907442}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 25: setStringSize (#const17, 0, 20)*/
    {{.ival=5}, {.ival=40}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: setStringValues (#const17, 0, 0, 1346510910, 758123040, 824201292, 542130733)*/
    {{.ival=6}, {.ival=40}, {.ival=0}, {.ival=0}, {.rawVal=1346510910}, {.rawVal=758123040}, {.rawVal=824201292}, {.rawVal=542130733}},
    /* PC 27: setStringValues (#const17, 0, 16, 1346907442, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=40}, {.ival=0}, {.ival=16}, {.rawVal=1346907442}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 28: setStringSize (#const18, 0, 20)*/
    {{.ival=5}, {.ival=41}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 29: setStringValues (#const18, 0, 0, 1346904126, 758123040, 824201292, 542130733)*/
    {{.ival=6}, {.ival=41}, {.ival=0}, {.ival=0}, {.rawVal=1346904126}, {.rawVal=758123040}, {.rawVal=824201292}, {.rawVal=542130733}},
    /* PC 30: setStringValues (#const18, 0, 16, 1346907442, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=41}, {.ival=0}, {.ival=16}, {.rawVal=1346907442}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 31: uiInitPanel (1, p, 0)*/
    {{.ival=201}, {.ival=1}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: uiInitDisplay (1, d, 0, p, 0)*/
    {{.ival=203}, {.ival=1}, {.ival=17}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 33: uiInitButton (1, bBypass, 0, p, 0)*/
    {{.ival=202}, {.ival=1}, {.ival=22}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: uiInitButton (2, bLP, 0, p, 0)*/
    {{.ival=202}, {.ival=2}, {.ival=20}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 35: uiInitButton (3, bBP, 0, p, 0)*/
    {{.ival=202}, {.ival=3}, {.ival=23}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: uiInitButton (4, bHP, 0, p, 0)*/
    {{.ival=202}, {.ival=4}, {.ival=4}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: uiInitButton (8, bUp, 0, p, 0)*/
    {{.ival=202}, {.ival=8}, {.ival=19}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: uiInitButton (7, bDown, 0, p, 0)*/
    {{.ival=202}, {.ival=7}, {.ival=7}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: uiInitButton (6, bReset, 0, p, 0)*/
    {{.ival=202}, {.ival=6}, {.ival=8}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: assignRational (fs, #const1)*/
    {{.ival=28}, {.ival=10}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 41: assignRational (q, #const2)*/
    {{.ival=28}, {.ival=21}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: assignRational (g, #const3)*/
    {{.ival=28}, {.ival=18}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 43: assignRational (fLP, #const4)*/
    {{.ival=28}, {.ival=6}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: assignRational (fHP, #const5)*/
    {{.ival=28}, {.ival=9}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 45: assignRational (gain, #const2)*/
    {{.ival=28}, {.ival=14}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: initBiquadAsLP (bqf1, 0, fs, fLP)*/
    {{.ival=101}, {.ival=0}, {.ival=0}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 47: initBiquadAsLP (bqf1, 1, fs, fLP)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: initBiquadAsHP (bqf2, 0, fs, fHP)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 49: initBiquadAsHP (bqf2, 1, fs, fHP)*/
    {{.ival=100}, {.ival=1}, {.ival=1}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: assignInteger (byPassFlag, #const6)*/
    {{.ival=21}, {.ival=11}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 51: uiSetDisplay (d, 0, #const7, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 52: label ID:13*/
    /* PC 52: uiCheckButtonPressed (bReset, 0)*/
    {{.ival=210}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 53: jumpNCF (label ID:2)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 54: uiSetDisplay (d, 0, #const8, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 55: assignRational (gain, #const2)*/
    {{.ival=28}, {.ival=14}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 56: label ID:2*/
    /* PC 56: uiCheckButtonPressed (bUp, 0)*/
    {{.ival=210}, {.ival=19}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 57: jumpNCF (label ID:4)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 58: compareRationalLess (gain, 0, #const9, 0)*/
    {{.ival=34}, {.ival=14}, {.ival=0}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 59: jumpNCF (label ID:3)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 60: addRational (gain, #const10, gain)*/
    {{.ival=29}, {.ival=14}, {.ival=33}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 61: label ID:3*/
    /* PC 61: assignString (gaintext, 0, #const11, 0)*/
    {{.ival=10}, {.ival=2}, {.ival=0}, {.ival=34}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 62: rationalToString (gainStr, 0, gain, 0)*/
    {{.ival=8}, {.ival=3}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 63: concatStrings (gaintext, 0, gainStr, 0)*/
    {{.ival=7}, {.ival=2}, {.ival=0}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 64: uiSetDisplay (d, 0, gaintext, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 65: label ID:4*/
    /* PC 65: uiCheckButtonPressed (bDown, 0)*/
    {{.ival=210}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 66: jumpNCF (label ID:6)*/
    {{.ival=52}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 67: subRational (gain, #const10, gain)*/
    {{.ival=30}, {.ival=14}, {.ival=33}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 68: compareRationalLess (gain, 0, #const12, 0)*/
    {{.ival=34}, {.ival=14}, {.ival=0}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 69: jumpNCF (label ID:5)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 70: assignRational (gain, #const12)*/
    {{.ival=28}, {.ival=14}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 71: label ID:5*/
    /* PC 71: assignString (gaintext, 0, #const13, 0)*/
    {{.ival=10}, {.ival=2}, {.ival=0}, {.ival=36}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 72: rationalToString (gainStr, 0, gain, 0)*/
    {{.ival=8}, {.ival=3}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 73: concatStrings (gaintext, 0, gainStr, 0)*/
    {{.ival=7}, {.ival=2}, {.ival=0}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 74: uiSetDisplay (d, 0, gaintext, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 75: label ID:6*/
    /* PC 75: uiCheckButtonPressed (bBypass, 0)*/
    {{.ival=210}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 76: jumpNCF (label ID:7)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 77: uiSetDisplay (d, 0, #const14, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=37}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 78: assignInteger (byPassFlag, #const6)*/
    {{.ival=21}, {.ival=11}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 79: label ID:7*/
    /* PC 79: uiCheckButtonPressed (bLP, 0)*/
    {{.ival=210}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 80: jumpNCF (label ID:8)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 81: assignInteger (byPassFlag, #const15)*/
    {{.ival=21}, {.ival=11}, {.ival=38}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 82: uiSetDisplay (d, 0, #const16, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=39}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 83: initBiquadAsLP (bqf1, 0, fs, fLP)*/
    {{.ival=101}, {.ival=0}, {.ival=0}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 84: initBiquadAsLP (bqf1, 1, fs, fLP)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 85: initBiquadAsLP (bqf2, 0, fs, fLP)*/
    {{.ival=101}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 86: initBiquadAsLP (bqf2, 1, fs, fLP)*/
    {{.ival=101}, {.ival=1}, {.ival=1}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 87: label ID:8*/
    /* PC 87: uiCheckButtonPressed (bBP, 0)*/
    {{.ival=210}, {.ival=23}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 88: jumpNCF (label ID:9)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 89: assignInteger (byPassFlag, #const15)*/
    {{.ival=21}, {.ival=11}, {.ival=38}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 90: uiSetDisplay (d, 0, #const17, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=40}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 91: initBiquadAsHP (bqf1, 0, fs, fHP)*/
    {{.ival=100}, {.ival=0}, {.ival=0}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 92: initBiquadAsLP (bqf1, 1, fs, fLP)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 93: initBiquadAsHP (bqf2, 0, fs, fHP)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 94: initBiquadAsLP (bqf2, 1, fs, fLP)*/
    {{.ival=101}, {.ival=1}, {.ival=1}, {.ival=10}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 95: label ID:9*/
    /* PC 95: uiCheckButtonPressed (bHP, 0)*/
    {{.ival=210}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 96: jumpNCF (label ID:10)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 97: assignInteger (byPassFlag, #const15)*/
    {{.ival=21}, {.ival=11}, {.ival=38}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 98: uiSetDisplay (d, 0, #const18, 0)*/
    {{.ival=212}, {.ival=17}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 99: initBiquadAsHP (bqf1, 0, fs, fHP)*/
    {{.ival=100}, {.ival=0}, {.ival=0}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 100: initBiquadAsHP (bqf1, 1, fs, fHP)*/
    {{.ival=100}, {.ival=0}, {.ival=1}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 101: initBiquadAsHP (bqf2, 0, fs, fHP)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 102: initBiquadAsHP (bqf2, 1, fs, fHP)*/
    {{.ival=100}, {.ival=1}, {.ival=1}, {.ival=10}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 103: label ID:10*/
    /* PC 103: readSampleFrame (0, in1, 1)*/
    {{.ival=62}, {.ival=0}, {.ival=12}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 104: readSampleFrame (1, in2, 0)*/
    {{.ival=62}, {.ival=1}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 105: mulRational (in1, gain, in1)*/
    {{.ival=31}, {.ival=12}, {.ival=14}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 106: mulRational (in2, gain, in2)*/
    {{.ival=31}, {.ival=13}, {.ival=14}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 107: compareIntegerEqual (byPassFlag, 0, #const6, 0)*/
    {{.ival=42}, {.ival=11}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 108: jumpNCF (label ID:12)*/
    {{.ival=52}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 109: assignRational (out1, in1)*/
    {{.ival=28}, {.ival=15}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 110: assignRational (out2, in2)*/
    {{.ival=28}, {.ival=16}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 111: jump (label ID:11)*/
    {{.ival=50}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 112: label ID:12*/
    /* PC 112: convoluteBiquad (in1, bqf1, out1)*/
    {{.ival=110}, {.ival=12}, {.ival=0}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 113: convoluteBiquad (in2, bqf2, out2)*/
    {{.ival=110}, {.ival=13}, {.ival=1}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 114: label ID:11*/
    /* PC 114: writeSampleFrame (0, out1)*/
    {{.ival=63}, {.ival=0}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 115: writeSampleFrame (1, out2)*/
    {{.ival=63}, {.ival=1}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 116: jump (label ID:13)*/
    {{.ival=50}, {.ival=-64}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

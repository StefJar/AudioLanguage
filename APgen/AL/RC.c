// audio language code file
// generated 2015-09-03 15:42:09

#include "RC.h"

//! list containing the variables
const TALCvar gALCvars [24] = {
    //0: name="uiState" type="integer" amount=1 
    {.type=2,.amount=1},
    //1: name="ub1" type="button" amount=1 
    {.type=101,.amount=1},
    //2: name="ub2" type="button" amount=1 
    {.type=101,.amount=1},
    //3: name="ub3" type="button" amount=1 
    {.type=101,.amount=1},
    //4: name="gain" type="rational" amount=1 
    {.type=1,.amount=1},
    //5: name="db1" type="button" amount=1 
    {.type=101,.amount=1},
    //6: name="db3" type="button" amount=1 
    {.type=101,.amount=1},
    //7: name="db2" type="button" amount=1 
    {.type=101,.amount=1},
    //8: name="db5" type="button" amount=1 
    {.type=101,.amount=1},
    //9: name="db4" type="button" amount=1 
    {.type=101,.amount=1},
    //10: name="pan" type="panel" amount=1 
    {.type=100,.amount=1},
    //11: name="dis" type="display" amount=1 
    {.type=103,.amount=1},
    //12: name="#const11" type="integer" amount=1 
    {.type=2,.amount=1},
    //13: name="#fv_checkUI_gainStr" type="string" amount=1 
    {.type=3,.amount=1},
    //14: name="#fv_checkUI_gaintext" type="string" amount=1 
    {.type=3,.amount=1},
    //15: name="#const1" type="string" amount=1 
    {.type=3,.amount=1},
    //16: name="#const2" type="rational" amount=1 
    {.type=1,.amount=1},
    //17: name="#const3" type="integer" amount=1 
    {.type=2,.amount=1},
    //18: name="#const4" type="rational" amount=1 
    {.type=1,.amount=1},
    //19: name="#const5" type="rational" amount=1 
    {.type=1,.amount=1},
    //20: name="#const6" type="rational" amount=1 
    {.type=1,.amount=1},
    //21: name="#const8" type="string" amount=1 
    {.type=3,.amount=1},
    //22: name="#const9" type="integer" amount=1 
    {.type=2,.amount=1},
    //23: name="#const10" type="string" amount=1 
    {.type=3,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[72] = {
    /* PC 0: assignConstInteger (#const11, 0, 1, 1)*/
    {{.ival=20}, {.ival=12}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: setStringSize (#const1, 0, 5)*/
    {{.ival=5}, {.ival=15}, {.ival=0}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 2: setStringValues (#const1, 0, 0, 1702061426, 538976372, 538976288, 538976288)*/
    {{.ival=6}, {.ival=15}, {.ival=0}, {.ival=0}, {.rawVal=1702061426}, {.rawVal=538976372}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 3: assignConstRational (#const2, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=16}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 4: assignConstInteger (#const3, 0, 1, 2)*/
    {{.ival=20}, {.ival=17}, {.ival=0}, {.ival=1}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 5: assignConstRational (#const4, 0, 1, 10.0)*/
    {{.ival=27}, {.ival=18}, {.ival=0}, {.ival=1}, {.fval=10.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 6: assignConstRational (#const5, 0, 1, 0.1)*/
    {{.ival=27}, {.ival=19}, {.ival=0}, {.ival=1}, {.fval=0.1}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 7: assignConstRational (#const6, 0, 1, 0.0)*/
    {{.ival=27}, {.ival=20}, {.ival=0}, {.ival=1}, {.fval=0.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 8: setStringSize (#const8, 0, 22)*/
    {{.ival=5}, {.ival=21}, {.ival=0}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 9: setStringValues (#const8, 0, 0, 1377847637, 1953459557, 1866670181, 1869771886)*/
    {{.ival=6}, {.ival=21}, {.ival=0}, {.ival=0}, {.rawVal=1377847637}, {.rawVal=1953459557}, {.rawVal=1866670181}, {.rawVal=1869771886}},
    /* PC 10: setStringValues (#const8, 0, 16, 1698957932, 538996589, 538976288, 538976288)*/
    {{.ival=6}, {.ival=21}, {.ival=0}, {.ival=16}, {.rawVal=1698957932}, {.rawVal=538996589}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 11: assignConstInteger (#const9, 0, 1, 0)*/
    {{.ival=20}, {.ival=22}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 12: setStringSize (#const10, 0, 7)*/
    {{.ival=5}, {.ival=23}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 13: setStringValues (#const10, 0, 0, 1852399975, 537534522, 538976288, 538976288)*/
    {{.ival=6}, {.ival=23}, {.ival=0}, {.ival=0}, {.rawVal=1852399975}, {.rawVal=537534522}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 14: uiSetDim (0, 0, 520, 260, pan, 0)*/
    {{.ival=200}, {.ival=0}, {.ival=0}, {.ival=520}, {.ival=260}, {.ival=10}, {.ival=0}, {.ival=0}},
    /* PC 15: uiSetDim (380, 10, 50, 50, ub1, 0)*/
    {{.ival=200}, {.ival=380}, {.ival=10}, {.ival=50}, {.ival=50}, {.ival=1}, {.ival=0}, {.ival=0}},
    /* PC 16: uiSetDim (430, 10, 50, 50, ub2, 0)*/
    {{.ival=200}, {.ival=430}, {.ival=10}, {.ival=50}, {.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}},
    /* PC 17: uiSetDim (480, 10, 50, 50, ub3, 0)*/
    {{.ival=200}, {.ival=480}, {.ival=10}, {.ival=50}, {.ival=50}, {.ival=3}, {.ival=0}, {.ival=0}},
    /* PC 18: uiSetDim (25, 70, 500, 100, dis, 0)*/
    {{.ival=200}, {.ival=25}, {.ival=70}, {.ival=500}, {.ival=100}, {.ival=11}, {.ival=0}, {.ival=0}},
    /* PC 19: uiSetDim (10, 190, 50, 50, db1, 0)*/
    {{.ival=200}, {.ival=10}, {.ival=190}, {.ival=50}, {.ival=50}, {.ival=5}, {.ival=0}, {.ival=0}},
    /* PC 20: uiSetDim (70, 190, 50, 50, db2, 0)*/
    {{.ival=200}, {.ival=70}, {.ival=190}, {.ival=50}, {.ival=50}, {.ival=7}, {.ival=0}, {.ival=0}},
    /* PC 21: uiSetDim (130, 190, 50, 50, db3, 0)*/
    {{.ival=200}, {.ival=130}, {.ival=190}, {.ival=50}, {.ival=50}, {.ival=6}, {.ival=0}, {.ival=0}},
    /* PC 22: uiSetDim (190, 190, 50, 50, db4, 0)*/
    {{.ival=200}, {.ival=190}, {.ival=190}, {.ival=50}, {.ival=50}, {.ival=9}, {.ival=0}, {.ival=0}},
    /* PC 23: uiSetDim (320, 190, 50, 50, db5, 0)*/
    {{.ival=200}, {.ival=320}, {.ival=190}, {.ival=50}, {.ival=50}, {.ival=8}, {.ival=0}, {.ival=0}},
    /* PC 24: uiInitPanel (0, pan, 0)*/
    {{.ival=201}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 25: uiInitButton (6, ub1, 0, pan, 0)*/
    {{.ival=202}, {.ival=6}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: uiInitButton (7, ub2, 0, pan, 0)*/
    {{.ival=202}, {.ival=7}, {.ival=2}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 27: uiInitButton (8, ub3, 0, pan, 0)*/
    {{.ival=202}, {.ival=8}, {.ival=3}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 28: uiInitDisplay (0, dis, 0, pan, 0)*/
    {{.ival=203}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 29: uiSetDisplayTextDim (dis, 0, 16, 2)*/
    {{.ival=213}, {.ival=11}, {.ival=0}, {.ival=16}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 30: uiInitButton (1, db1, 0, pan, 0)*/
    {{.ival=202}, {.ival=1}, {.ival=5}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 31: uiInitButton (2, db2, 0, pan, 0)*/
    {{.ival=202}, {.ival=2}, {.ival=7}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: uiInitButton (3, db3, 0, pan, 0)*/
    {{.ival=202}, {.ival=3}, {.ival=6}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 33: uiInitButton (4, db4, 0, pan, 0)*/
    {{.ival=202}, {.ival=4}, {.ival=9}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: uiInitButton (5, db5, 0, pan, 0)*/
    {{.ival=202}, {.ival=5}, {.ival=8}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 35: assignInteger (uiState, #const11)*/
    {{.ival=21}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: label ID:9*/
    /* PC 36: uiCheckButtonPressed (ub2, 0)*/
    {{.ival=210}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: jumpNCF (label ID:18)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: uiSetDisplay (dis, 0, #const1, 0)*/
    {{.ival=212}, {.ival=11}, {.ival=0}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: assignRational (gain, #const2)*/
    {{.ival=28}, {.ival=4}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: assignInteger (uiState, #const3)*/
    {{.ival=21}, {.ival=0}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 41: update (gain)*/
    {{.ival=56}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: update (uiState)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 43: label ID:18*/
    /* PC 43: uiCheckButtonPressed (ub3, 0)*/
    {{.ival=210}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: jumpNCF (label ID:20)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 45: compareRationalLess (gain, 0, #const4, 0)*/
    {{.ival=34}, {.ival=4}, {.ival=0}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: jumpNCF (label ID:19)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 47: addRational (gain, #const5, gain)*/
    {{.ival=29}, {.ival=4}, {.ival=19}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: label ID:19*/
    /* PC 48: assignInteger (uiState, #const3)*/
    {{.ival=21}, {.ival=0}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 49: update (gain)*/
    {{.ival=56}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: update (uiState)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 51: label ID:20*/
    /* PC 51: uiCheckButtonPressed (ub1, 0)*/
    {{.ival=210}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 52: jumpNCF (label ID:22)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 53: subRational (gain, #const5, gain)*/
    {{.ival=30}, {.ival=4}, {.ival=19}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 54: compareRationalLess (gain, 0, #const6, 0)*/
    {{.ival=34}, {.ival=4}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 55: jumpNCF (label ID:21)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 56: assignRational (gain, #const6)*/
    {{.ival=28}, {.ival=4}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 57: label ID:21*/
    /* PC 57: assignInteger (uiState, #const3)*/
    {{.ival=21}, {.ival=0}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 58: update (gain)*/
    {{.ival=56}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 59: update (uiState)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 60: label ID:22*/
    /* PC 60: compareIntegerEqual (uiState, 0, #const11 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=0}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 61: jumpNCF (label ID:23)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 62: uiSetDisplay (dis, 0, #const8, 0)*/
    {{.ival=212}, {.ival=11}, {.ival=0}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 63: assignInteger (uiState, #const9)*/
    {{.ival=21}, {.ival=0}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 64: label ID:23*/
    /* PC 64: compareIntegerEqual (uiState, 0, #const3, 0)*/
    {{.ival=42}, {.ival=0}, {.ival=0}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 65: jumpNCF (label ID:24)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 66: assignString (#fv_checkUI_gaintext, 0, #const10, 0)*/
    {{.ival=10}, {.ival=14}, {.ival=0}, {.ival=23}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 67: rationalToString (#fv_checkUI_gainStr, 0, gain, 0)*/
    {{.ival=8}, {.ival=13}, {.ival=0}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 68: concatStrings (#fv_checkUI_gaintext, 0, #fv_checkUI_gainStr, 0)*/
    {{.ival=7}, {.ival=14}, {.ival=0}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 69: uiSetDisplay (dis, 0, #fv_checkUI_gaintext, 0)*/
    {{.ival=212}, {.ival=11}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 70: assignInteger (uiState, #const9)*/
    {{.ival=21}, {.ival=0}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 71: label ID:24*/
    /* PC 71: jump (label ID:9)*/
    {{.ival=50}, {.ival=-35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

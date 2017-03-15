// audio language code file
// generated 2015-07-15 17:47:49

#include "GUI.h"

//! list containing the variables
const TALCvar gALCvars [30] = {
    //0: name="impactNoiseBypass" type="integer" amount=1 
    {.type=2,.amount=1},
    //1: name="compressor" type="compressor" amount=1 
    {.type=13,.amount=1},
    //2: name="noiseG" type="noisegate" amount=1 
    {.type=11,.amount=1},
    //3: name="gain" type="rational" amount=1 
    {.type=1,.amount=1},
    //4: name="impactNoiseF" type="biquad" amount=1 
    {.type=10,.amount=1},
    //5: name="sens" type="rational" amount=1 
    {.type=1,.amount=1},
    //6: name="EQ" type="biquad" amount=3 
    {.type=10,.amount=3},
    //7: name="panLeft" type="rational" amount=1 
    {.type=1,.amount=1},
    //8: name="#fv_UI_txtOpening" type="string" amount=1 
    {.type=3,.amount=1},
    //9: name="#fv_UI_lGreen" type="led" amount=1 
    {.type=102,.amount=1},
    //10: name="#fv_UI_d" type="display" amount=1 
    {.type=103,.amount=1},
    //11: name="#fv_UI_txtFloorNoiseFon" type="string" amount=1 
    {.type=3,.amount=1},
    //12: name="#fv_UI_txtFloorNoiseFoff" type="string" amount=1 
    {.type=3,.amount=1},
    //13: name="#fv_UI_state" type="integer" amount=1 
    {.type=2,.amount=1},
    //14: name="#fv_UI_p" type="panel" amount=1 
    {.type=100,.amount=1},
    //15: name="#fv_UI_bRight" type="button" amount=1 
    {.type=101,.amount=1},
    //16: name="#fv_UI_txtFloorNoiseSelect" type="string" amount=1 
    {.type=3,.amount=1},
    //17: name="#fv_UI_bLeft" type="button" amount=1 
    {.type=101,.amount=1},
    //18: name="#fv_UI_lRed" type="led" amount=1 
    {.type=102,.amount=1},
    //19: name="#fv_UI_bMiddle" type="button" amount=1 
    {.type=101,.amount=1},
    //20: name="#fv_UI_dispalyStr" type="string" amount=3 
    {.type=3,.amount=3},
    //21: name="#fv_UI_tstr" type="string" amount=1 
    {.type=3,.amount=1},
    //22: name="#const8" type="string" amount=1 
    {.type=3,.amount=1},
    //23: name="#const9" type="string" amount=1 
    {.type=3,.amount=1},
    //24: name="#const10" type="string" amount=1 
    {.type=3,.amount=1},
    //25: name="#const11" type="string" amount=1 
    {.type=3,.amount=1},
    //26: name="#const12" type="string" amount=1 
    {.type=3,.amount=1},
    //27: name="#const13" type="integer" amount=1 
    {.type=2,.amount=1},
    //28: name="#const14" type="string" amount=1 
    {.type=3,.amount=1},
    //29: name="#const15" type="integer" amount=1 
    {.type=2,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[53] = {
    /* PC 0: setStringSize (#const8, 0, 33)*/
    {{.ival=5}, {.ival=22}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: setStringValues (#const8, 0, 0, 1093487681, 1702043728, 1952671084, 1953068832)*/
    {{.ival=6}, {.ival=22}, {.ival=0}, {.ival=0}, {.rawVal=1093487681}, {.rawVal=1702043728}, {.rawVal=1952671084}, {.rawVal=1953068832}},
    /* PC 2: setStringValues (#const8, 0, 16, 1701585000, 1646294118, 1869902965, 1651255406)*/
    {{.ival=6}, {.ival=22}, {.ival=0}, {.ival=16}, {.rawVal=1701585000}, {.rawVal=1646294118}, {.rawVal=1869902965}, {.rawVal=1651255406}},
    /* PC 3: setStringValues (#const8, 0, 32, 538976297, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=22}, {.ival=0}, {.ival=32}, {.rawVal=538976297}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 4: setStringSize (#const9, 0, 35)*/
    {{.ival=5}, {.ival=23}, {.ival=0}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 5: setStringValues (#const9, 0, 0, 1936289646, 1818632293, 1718775663, 1702128745)*/
    {{.ival=6}, {.ival=23}, {.ival=0}, {.ival=0}, {.rawVal=1936289646}, {.rawVal=1818632293}, {.rawVal=1718775663}, {.rawVal=1702128745}},
    /* PC 6: setStringValues (#const9, 0, 16, 1313808498, 543321098, 1663070068, 1769238127)*/
    {{.ival=6}, {.ival=23}, {.ival=0}, {.ival=16}, {.rawVal=1313808498}, {.rawVal=543321098}, {.rawVal=1663070068}, {.rawVal=1769238127}},
    /* PC 7: setStringValues (#const9, 0, 32, 543520110, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=23}, {.ival=0}, {.ival=32}, {.rawVal=543520110}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 8: setStringSize (#const10, 0, 36)*/
    {{.ival=5}, {.ival=24}, {.ival=0}, {.ival=36}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 9: setStringValues (#const10, 0, 0, 1936289646, 1818632293, 1718775663, 1702128745)*/
    {{.ival=6}, {.ival=24}, {.ival=0}, {.ival=0}, {.rawVal=1936289646}, {.rawVal=1818632293}, {.rawVal=1718775663}, {.rawVal=1702128745}},
    /* PC 10: setStringValues (#const10, 0, 16, 1179590770, 1651247686, 544175136, 1953394531)*/
    {{.ival=6}, {.ival=24}, {.ival=0}, {.ival=16}, {.rawVal=1179590770}, {.rawVal=1651247686}, {.rawVal=544175136}, {.rawVal=1953394531}},
    /* PC 11: setStringValues (#const10, 0, 32, 1702194793, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=24}, {.ival=0}, {.ival=32}, {.rawVal=1702194793}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 12: setStringSize (#const11, 0, 30)*/
    {{.ival=5}, {.ival=25}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 13: setStringValues (#const11, 0, 0, 1936289646, 1818632293, 1718775663, 1702128745)*/
    {{.ival=6}, {.ival=25}, {.ival=0}, {.ival=0}, {.rawVal=1936289646}, {.rawVal=1818632293}, {.rawVal=1718775663}, {.rawVal=1702128745}},
    /* PC 14: setStringValues (#const11, 0, 16, 1651313266, 544108349, 1866293874, 538994278)*/
    {{.ival=6}, {.ival=25}, {.ival=0}, {.ival=16}, {.rawVal=1651313266}, {.rawVal=544108349}, {.rawVal=1866293874}, {.rawVal=538994278}},
    /* PC 15: setStringSize (#const12, 0, 7)*/
    {{.ival=5}, {.ival=26}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 16: setStringValues (#const12, 0, 0, 1952804896, 538997349, 538976288, 538976288)*/
    {{.ival=6}, {.ival=26}, {.ival=0}, {.ival=0}, {.rawVal=1952804896}, {.rawVal=538997349}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 17: assignConstInteger (#const13, 0, 1, 0)*/
    {{.ival=20}, {.ival=27}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 18: setStringSize (#const14, 0, 0)*/
    {{.ival=5}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 19: assignConstInteger (#const15, 0, 1, 1)*/
    {{.ival=20}, {.ival=29}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 20: uiSetDim (0, 0, 550, 500, #fv_UI_p, 0)*/
    {{.ival=200}, {.ival=0}, {.ival=0}, {.ival=550}, {.ival=500}, {.ival=14}, {.ival=0}, {.ival=0}},
    /* PC 21: uiInitPanel (1, #fv_UI_p, 0)*/
    {{.ival=201}, {.ival=1}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 22: uiSetDim (10, 10, 500, 300, #fv_UI_d, 0)*/
    {{.ival=200}, {.ival=10}, {.ival=10}, {.ival=500}, {.ival=300}, {.ival=10}, {.ival=0}, {.ival=0}},
    /* PC 23: uiInitDisplay (11, #fv_UI_d, 0, #fv_UI_p, 0)*/
    {{.ival=203}, {.ival=11}, {.ival=10}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 24: uiSetDim (50, 400, 50, 50, #fv_UI_bLeft, 0)*/
    {{.ival=200}, {.ival=50}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=17}, {.ival=0}, {.ival=0}},
    /* PC 25: uiInitButton (21, #fv_UI_bLeft, 0, #fv_UI_p, 0)*/
    {{.ival=202}, {.ival=21}, {.ival=17}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: uiSetDim (150, 400, 50, 50, #fv_UI_lRed, 0)*/
    {{.ival=200}, {.ival=150}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=18}, {.ival=0}, {.ival=0}},
    /* PC 27: uiInitLED (31, #fv_UI_lRed, 0, #fv_UI_p, 0)*/
    {{.ival=204}, {.ival=31}, {.ival=18}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 28: uiSetDim (250, 400, 50, 50, #fv_UI_bMiddle, 0)*/
    {{.ival=200}, {.ival=250}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=19}, {.ival=0}, {.ival=0}},
    /* PC 29: uiInitButton (22, #fv_UI_bMiddle, 0, #fv_UI_p, 0)*/
    {{.ival=202}, {.ival=22}, {.ival=19}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 30: uiSetDim (350, 400, 50, 50, #fv_UI_lGreen, 0)*/
    {{.ival=200}, {.ival=350}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=9}, {.ival=0}, {.ival=0}},
    /* PC 31: uiInitLED (31, #fv_UI_lGreen, 0, #fv_UI_p, 0)*/
    {{.ival=204}, {.ival=31}, {.ival=9}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: uiSetDim (450, 400, 50, 50, #fv_UI_bRight, 0)*/
    {{.ival=200}, {.ival=450}, {.ival=400}, {.ival=50}, {.ival=50}, {.ival=15}, {.ival=0}, {.ival=0}},
    /* PC 33: uiInitButton (23, #fv_UI_bRight, 0, #fv_UI_p, 0)*/
    {{.ival=202}, {.ival=23}, {.ival=15}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: assignString (#fv_UI_txtOpening, 0, #const8, 0)*/
    {{.ival=10}, {.ival=8}, {.ival=0}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 35: assignString (#fv_UI_txtFloorNoiseFon, 0, #const9, 0)*/
    {{.ival=10}, {.ival=11}, {.ival=0}, {.ival=23}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: assignString (#fv_UI_txtFloorNoiseFoff, 0, #const10, 0)*/
    {{.ival=10}, {.ival=12}, {.ival=0}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: assignString (#fv_UI_txtFloorNoiseSelect, 0, #const11, 0)*/
    {{.ival=10}, {.ival=16}, {.ival=0}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: assignString (#fv_UI_tstr, 0, #const12, 0)*/
    {{.ival=10}, {.ival=21}, {.ival=0}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: uiSetDisplay (#fv_UI_d, 0, #fv_UI_txtOpening, 0)*/
    {{.ival=212}, {.ival=10}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: assignInteger (#fv_UI_state, #const13)*/
    {{.ival=21}, {.ival=13}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 41: assignString (#fv_UI_txtFloorNoiseSelect, 0, #const14, 0)*/
    {{.ival=10}, {.ival=16}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: label ID:9*/
    /* PC 42: uiCheckButtonPressed (#fv_UI_bLeft, 0)*/
    {{.ival=210}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 43: jumpNCF (label ID:12)*/
    {{.ival=52}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: compareIntegerEqual (#fv_UI_state, 0, #const13, 0)*/
    {{.ival=42}, {.ival=13}, {.ival=0}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 45: jumpNCF (label ID:10)*/
    {{.ival=52}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: uiSetDisplay (#fv_UI_d, 0, #fv_UI_txtFloorNoiseSelect, 0)*/
    {{.ival=212}, {.ival=10}, {.ival=0}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 47: concatStrings (#fv_UI_txtFloorNoiseSelect, 0, #fv_UI_tstr, 0)*/
    {{.ival=7}, {.ival=16}, {.ival=0}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: assignInteger (#fv_UI_state, #const15)*/
    {{.ival=21}, {.ival=13}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 49: jump (label ID:11)*/
    {{.ival=50}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: label ID:10*/
    /* PC 50: uiSetDisplay (#fv_UI_d, 0, #fv_UI_txtOpening, 0)*/
    {{.ival=212}, {.ival=10}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 51: assignInteger (#fv_UI_state, #const13)*/
    {{.ival=21}, {.ival=13}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 52: label ID:11*/
    /* PC 52: label ID:12*/
    /* PC 52: jump (label ID:9)*/
    {{.ival=50}, {.ival=-10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

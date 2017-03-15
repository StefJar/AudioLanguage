// audio language code file
// generated 2016-01-13 11:04:07

#include "ADSP.h"

//! list containing the variables
const TALCvar gALCvars [36] = {
    //0: name="uiUpdate" type="integer" amount=1 
    {.type=2,.amount=1},
    //1: name="uiFilterTypeSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //2: name="uiFilterIndex" type="integer" amount=1 
    {.type=2,.amount=1},
    //3: name="LoutFilter" type="biquad" amount=3 
    {.type=10,.amount=3},
    //4: name="RoutInpSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //5: name="RinFilter" type="biquad" amount=3 
    {.type=10,.amount=3},
    //6: name="bDown" type="button" amount=1 
    {.type=101,.amount=1},
    //7: name="uiFilterBankSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //8: name="fquality" type="rational" amount=1 
    {.type=1,.amount=1},
    //9: name="fs" type="rational" amount=1 
    {.type=1,.amount=1},
    //10: name="uiSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //11: name="volume" type="rational" amount=1 
    {.type=1,.amount=1},
    //12: name="RoutFilter" type="biquad" amount=3 
    {.type=10,.amount=3},
    //13: name="ffreq" type="rational" amount=1 
    {.type=1,.amount=1},
    //14: name="LoutInpSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //15: name="d" type="display" amount=1 
    {.type=103,.amount=1},
    //16: name="bUp" type="button" amount=1 
    {.type=101,.amount=1},
    //17: name="bSelect" type="button" amount=1 
    {.type=101,.amount=1},
    //18: name="LinFilter" type="biquad" amount=3 
    {.type=10,.amount=3},
    //19: name="uiMenuSel" type="integer" amount=1 
    {.type=2,.amount=1},
    //20: name="p" type="panel" amount=1 
    {.type=100,.amount=1},
    //21: name="fgain" type="rational" amount=1 
    {.type=1,.amount=1},
    //22: name="uiSelChannel" type="integer" amount=1 
    {.type=2,.amount=1},
    //23: name="uiState" type="integer" amount=1 
    {.type=2,.amount=1},
    //24: name="inL" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //25: name="outR" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //26: name="outL" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //27: name="inR" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //28: name="#const37" type="integer" amount=1 
    {.type=2,.amount=1},
    //29: name="#const38" type="integer" amount=1 
    {.type=2,.amount=1},
    //30: name="#const39" type="integer" amount=1 
    {.type=2,.amount=1},
    //31: name="#const40" type="rational" amount=1 
    {.type=1,.amount=1},
    //32: name="#fv_dspInit_i" type="integer" amount=1 
    {.type=2,.amount=1},
    //33: name="#const98" type="integer" amount=1 
    {.type=2,.amount=1},
    //34: name="#const99" type="rational" amount=1 
    {.type=1,.amount=1},
    //35: name="#const102" type="rational" amount=1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[47] = {
    /* PC 0: assignConstInteger (#const37, 0, 1, 0)*/
    {{.ival=20}, {.ival=28}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: assignConstInteger (#const38, 0, 1, 1)*/
    {{.ival=20}, {.ival=29}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 2: assignConstInteger (#const39, 0, 1, 2)*/
    {{.ival=20}, {.ival=30}, {.ival=0}, {.ival=1}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 3: assignConstRational (#const40, 0, 1, 0.0)*/
    {{.ival=27}, {.ival=31}, {.ival=0}, {.ival=1}, {.fval=0.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 4: assignConstInteger (#const98, 0, 1, 3)*/
    {{.ival=20}, {.ival=33}, {.ival=0}, {.ival=1}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 5: assignConstRational (#const99, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=34}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 6: assignConstRational (#const102, 0, 1, 48000.0)*/
    {{.ival=27}, {.ival=35}, {.ival=0}, {.ival=1}, {.fval=48000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 7: assignInteger (#fv_dspInit_i, #const37 = "0"(integer))*/
    {{.ival=21}, {.ival=32}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 8: label ID:213*/
    /* PC 8: compareIntegerLess (#fv_dspInit_i, 0, #const98, 0)*/
    {{.ival=40}, {.ival=32}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 9: jumpNCF (label ID:214)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 10: initBiquad (LinFilter, #fv_dspInit_i, #const99, #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 11: initBiquad (RinFilter, #fv_dspInit_i, #const99, #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 12: initBiquad (LoutFilter, #fv_dspInit_i, #const99, #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 13: initBiquad (RoutFilter, #fv_dspInit_i, #const99, #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational), #const40 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 14: addInteger (#fv_dspInit_i, #const38 = "1"(integer), #fv_dspInit_i)*/
    {{.ival=22}, {.ival=32}, {.ival=29}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 15: jump (label ID:213)*/
    {{.ival=50}, {.ival=-7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 16: label ID:214*/
    /* PC 16: assignInteger (LoutInpSel, #const37 = "0"(integer))*/
    {{.ival=21}, {.ival=14}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 17: assignInteger (RoutInpSel, #const38 = "1"(integer))*/
    {{.ival=21}, {.ival=4}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 18: assignRational (fs, #const102)*/
    {{.ival=28}, {.ival=9}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 19: assignRational (volume, #const99)*/
    {{.ival=28}, {.ival=11}, {.ival=34}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 20: label ID:55*/
    /* PC 20: readSampleFrame (0, inL, 1)*/
    {{.ival=62}, {.ival=0}, {.ival=24}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 21: readSampleFrame (1, inR, 0)*/
    {{.ival=62}, {.ival=1}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 22: convoluteBiquad (inL, LinFilter, inL)*/
    {{.ival=110}, {.ival=24}, {.ival=18}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 23: convoluteBiquad (inR, RinFilter, inR)*/
    {{.ival=110}, {.ival=27}, {.ival=5}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 24: compareIntegerEqual (LoutInpSel, 0, #const37, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 25: jumpNCF (label ID:49)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 26: convoluteBiquad (inL, LoutFilter, outL)*/
    {{.ival=110}, {.ival=24}, {.ival=3}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 27: label ID:49*/
    /* PC 27: compareIntegerEqual (LoutInpSel, 0, #const38, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 28: jumpNCF (label ID:50)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 29: convoluteBiquad (inR, LoutFilter, outL)*/
    {{.ival=110}, {.ival=27}, {.ival=3}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 30: label ID:50*/
    /* PC 30: compareIntegerEqual (LoutInpSel, 0, #const39, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 31: jumpNCF (label ID:51)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: assignRational (outL, #const40)*/
    {{.ival=28}, {.ival=26}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 33: label ID:51*/
    /* PC 33: compareIntegerEqual (RoutInpSel, 0, #const37, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: jumpNCF (label ID:52)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 35: convoluteBiquad (inL, RoutFilter, outR)*/
    {{.ival=110}, {.ival=24}, {.ival=12}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: label ID:52*/
    /* PC 36: compareIntegerEqual (RoutInpSel, 0, #const38, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 37: jumpNCF (label ID:53)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: convoluteBiquad (inR, RoutFilter, outR)*/
    {{.ival=110}, {.ival=27}, {.ival=12}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 39: label ID:53*/
    /* PC 39: compareIntegerEqual (RoutInpSel, 0, #const39, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: jumpNCF (label ID:54)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 41: assignRational (outR, #const40)*/
    {{.ival=28}, {.ival=25}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: label ID:54*/
    /* PC 42: mulRational (outL, volume, outL)*/
    {{.ival=31}, {.ival=26}, {.ival=11}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 43: mulRational (outR, volume, outR)*/
    {{.ival=31}, {.ival=25}, {.ival=11}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: writeSampleFrame (0, outL)*/
    {{.ival=63}, {.ival=0}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 45: writeSampleFrame (1, outR)*/
    {{.ival=63}, {.ival=1}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: jump (label ID:55)*/
    {{.ival=50}, {.ival=-26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

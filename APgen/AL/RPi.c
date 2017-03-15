// audio language code file
// generated 2016-01-07 10:24:17

#include "RPi.h"

//! list containing the variables
const TALCvar gALCvars [90] = {
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
    //28: name="#const97" type="integer" amount=1 
    {.type=2,.amount=1},
    //29: name="#const98" type="integer" amount=1 
    {.type=2,.amount=1},
    //30: name="#const99" type="integer" amount=1 
    {.type=2,.amount=1},
    //31: name="#const100" type="rational" amount=1 
    {.type=1,.amount=1},
    //32: name="#fv_dspInit_i" type="integer" amount=1 
    {.type=2,.amount=1},
    //33: name="#const102" type="integer" amount=1 
    {.type=2,.amount=1},
    //34: name="#const103" type="rational" amount=1 
    {.type=1,.amount=1},
    //35: name="#const106" type="rational" amount=1 
    {.type=1,.amount=1},
    //36: name="#const109" type="rational" amount=1 
    {.type=1,.amount=1},
    //37: name="#fv_uiDisplay_headerText" type="string" amount=1 
    {.type=3,.amount=1},
    //38: name="#fv_uiDisplay_dispText" type="string" amount=1 
    {.type=3,.amount=1},
    //39: name="#fv_uiDisplay_selText" type="string" amount=1 
    {.type=3,.amount=1},
    //40: name="#fv_uiDisplay_stateChange" type="integer" amount=1 
    {.type=2,.amount=1},
    //41: name="#const42" type="integer" amount=1 
    {.type=2,.amount=1},
    //42: name="#const44" type="integer" amount=1 
    {.type=2,.amount=1},
    //43: name="#const45" type="integer" amount=1 
    {.type=2,.amount=1},
    //44: name="#const47" type="integer" amount=1 
    {.type=2,.amount=1},
    //45: name="#const48" type="integer" amount=1 
    {.type=2,.amount=1},
    //46: name="#const49" type="integer" amount=1 
    {.type=2,.amount=1},
    //47: name="#const50" type="integer" amount=1 
    {.type=2,.amount=1},
    //48: name="#const52" type="integer" amount=1 
    {.type=2,.amount=1},
    //49: name="#const53" type="integer" amount=1 
    {.type=2,.amount=1},
    //50: name="#const54" type="integer" amount=1 
    {.type=2,.amount=1},
    //51: name="#const55" type="integer" amount=1 
    {.type=2,.amount=1},
    //52: name="#const56" type="integer" amount=1 
    {.type=2,.amount=1},
    //53: name="#const57" type="rational" amount=1 
    {.type=1,.amount=1},
    //54: name="#const58" type="rational" amount=1 
    {.type=1,.amount=1},
    //55: name="#const59" type="rational" amount=1 
    {.type=1,.amount=1},
    //56: name="#const60" type="rational" amount=1 
    {.type=1,.amount=1},
    //57: name="#const61" type="rational" amount=1 
    {.type=1,.amount=1},
    //58: name="#const62" type="rational" amount=1 
    {.type=1,.amount=1},
    //59: name="#const64" type="string" amount=1 
    {.type=3,.amount=1},
    //60: name="#const95" type="integer" amount=1 
    {.type=2,.amount=1},
    //61: name="#const66" type="string" amount=1 
    {.type=3,.amount=1},
    //62: name="#const68" type="string" amount=1 
    {.type=3,.amount=1},
    //63: name="#const70" type="string" amount=1 
    {.type=3,.amount=1},
    //64: name="#const72" type="string" amount=1 
    {.type=3,.amount=1},
    //65: name="#const74" type="string" amount=1 
    {.type=3,.amount=1},
    //66: name="#const76" type="string" amount=1 
    {.type=3,.amount=1},
    //67: name="#const78" type="string" amount=1 
    {.type=3,.amount=1},
    //68: name="#const80" type="string" amount=1 
    {.type=3,.amount=1},
    //69: name="#const82" type="string" amount=1 
    {.type=3,.amount=1},
    //70: name="#const84" type="string" amount=1 
    {.type=3,.amount=1},
    //71: name="#const86" type="string" amount=1 
    {.type=3,.amount=1},
    //72: name="#const88" type="string" amount=1 
    {.type=3,.amount=1},
    //73: name="#fv_uiDisplay_#fv_getSelText_valToStr" type="string" amount=1 
    {.type=3,.amount=1},
    //74: name="#const2" type="string" amount=1 
    {.type=3,.amount=1},
    //75: name="#const4" type="string" amount=1 
    {.type=3,.amount=1},
    //76: name="#const5" type="string" amount=1 
    {.type=3,.amount=1},
    //77: name="#const12" type="string" amount=1 
    {.type=3,.amount=1},
    //78: name="#const13" type="string" amount=1 
    {.type=3,.amount=1},
    //79: name="#const14" type="string" amount=1 
    {.type=3,.amount=1},
    //80: name="#const16" type="string" amount=1 
    {.type=3,.amount=1},
    //81: name="#const18" type="string" amount=1 
    {.type=3,.amount=1},
    //82: name="#const20" type="string" amount=1 
    {.type=3,.amount=1},
    //83: name="#const21" type="string" amount=1 
    {.type=3,.amount=1},
    //84: name="#const22" type="string" amount=1 
    {.type=3,.amount=1},
    //85: name="#const23" type="string" amount=1 
    {.type=3,.amount=1},
    //86: name="#const25" type="string" amount=1 
    {.type=3,.amount=1},
    //87: name="#const27" type="string" amount=1 
    {.type=3,.amount=1},
    //88: name="#const29" type="string" amount=1 
    {.type=3,.amount=1},
    //89: name="#const35" type="string" amount=1 
    {.type=3,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[1033] = {
    /* PC 0: assignConstInteger (#const97, 0, 1, 0)*/
    {{.ival=20}, {.ival=28}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: assignConstInteger (#const98, 0, 1, 1)*/
    {{.ival=20}, {.ival=29}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 2: assignConstInteger (#const99, 0, 1, 2)*/
    {{.ival=20}, {.ival=30}, {.ival=0}, {.ival=1}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 3: assignConstRational (#const100, 0, 1, 0.0)*/
    {{.ival=27}, {.ival=31}, {.ival=0}, {.ival=1}, {.fval=0.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 4: assignConstInteger (#const102, 0, 1, 3)*/
    {{.ival=20}, {.ival=33}, {.ival=0}, {.ival=1}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 5: assignConstRational (#const103, 0, 1, 1.0)*/
    {{.ival=27}, {.ival=34}, {.ival=0}, {.ival=1}, {.fval=1.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 6: assignConstRational (#const106, 0, 1, 44100.0)*/
    {{.ival=27}, {.ival=35}, {.ival=0}, {.ival=1}, {.fval=44100.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 7: assignConstRational (#const109, 0, 1, 7500.0)*/
    {{.ival=27}, {.ival=36}, {.ival=0}, {.ival=1}, {.fval=7500.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 8: assignConstInteger (#const42, 0, 1, 10)*/
    {{.ival=20}, {.ival=41}, {.ival=0}, {.ival=1}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 9: assignConstInteger (#const44, 0, 1, 20)*/
    {{.ival=20}, {.ival=42}, {.ival=0}, {.ival=1}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 10: assignConstInteger (#const45, 0, 1, 40)*/
    {{.ival=20}, {.ival=43}, {.ival=0}, {.ival=1}, {.ival=40}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 11: assignConstInteger (#const47, 0, 1, 30)*/
    {{.ival=20}, {.ival=44}, {.ival=0}, {.ival=1}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 12: assignConstInteger (#const48, 0, 1, 21)*/
    {{.ival=20}, {.ival=45}, {.ival=0}, {.ival=1}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 13: assignConstInteger (#const49, 0, 1, 22)*/
    {{.ival=20}, {.ival=46}, {.ival=0}, {.ival=1}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 14: assignConstInteger (#const50, 0, 1, 23)*/
    {{.ival=20}, {.ival=47}, {.ival=0}, {.ival=1}, {.ival=23}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 15: assignConstInteger (#const52, 0, 1, 24)*/
    {{.ival=20}, {.ival=48}, {.ival=0}, {.ival=1}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 16: assignConstInteger (#const53, 0, 1, 5)*/
    {{.ival=20}, {.ival=49}, {.ival=0}, {.ival=1}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 17: assignConstInteger (#const54, 0, 1, 25)*/
    {{.ival=20}, {.ival=50}, {.ival=0}, {.ival=1}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 18: assignConstInteger (#const55, 0, 1, 41)*/
    {{.ival=20}, {.ival=51}, {.ival=0}, {.ival=1}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 19: assignConstInteger (#const56, 0, 1, 42)*/
    {{.ival=20}, {.ival=52}, {.ival=0}, {.ival=1}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 20: assignConstRational (#const57, 0, 1, 15000.0)*/
    {{.ival=27}, {.ival=53}, {.ival=0}, {.ival=1}, {.fval=15000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 21: assignConstRational (#const58, 0, 1, 100.0)*/
    {{.ival=27}, {.ival=54}, {.ival=0}, {.ival=1}, {.fval=100.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 22: assignConstRational (#const59, 0, 1, 5.0)*/
    {{.ival=27}, {.ival=55}, {.ival=0}, {.ival=1}, {.fval=5.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 23: assignConstRational (#const60, 0, 1, 0.1)*/
    {{.ival=27}, {.ival=56}, {.ival=0}, {.ival=1}, {.fval=0.1}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 24: assignConstRational (#const61, 0, 1, -5.0)*/
    {{.ival=27}, {.ival=57}, {.ival=0}, {.ival=1}, {.fval=-5.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 25: assignConstRational (#const62, 0, 1, 10.0)*/
    {{.ival=27}, {.ival=58}, {.ival=0}, {.ival=1}, {.fval=10.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 26: setStringSize (#const64, 0, 1)*/
    {{.ival=5}, {.ival=59}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 27: setStringValues (#const64, 0, 0, 538976266, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=59}, {.ival=0}, {.ival=0}, {.rawVal=538976266}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 28: assignConstInteger (#const95, 0, 1, 4)*/
    {{.ival=20}, {.ival=60}, {.ival=0}, {.ival=1}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 29: setStringSize (#const66, 0, 14)*/
    {{.ival=5}, {.ival=61}, {.ival=0}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 30: setStringValues (#const66, 0, 0, 543772754, 1093618753, 1701060688, 538996589)*/
    {{.ival=6}, {.ival=61}, {.ival=0}, {.ival=0}, {.rawVal=543772754}, {.rawVal=1093618753}, {.rawVal=1701060688}, {.rawVal=538996589}},
    /* PC 31: setStringSize (#const68, 0, 11)*/
    {{.ival=5}, {.ival=62}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 32: setStringValues (#const68, 0, 0, 1701602675, 1881175139, 544502369, 538976288)*/
    {{.ival=6}, {.ival=62}, {.ival=0}, {.ival=0}, {.rawVal=1701602675}, {.rawVal=1881175139}, {.rawVal=544502369}, {.rawVal=538976288}},
    /* PC 33: setStringSize (#const70, 0, 11)*/
    {{.ival=5}, {.ival=63}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 34: setStringValues (#const70, 0, 0, 1953261926, 1646293605, 543911521, 538976288)*/
    {{.ival=6}, {.ival=63}, {.ival=0}, {.ival=0}, {.rawVal=1953261926}, {.rawVal=1646293605}, {.rawVal=543911521}, {.rawVal=538976288}},
    /* PC 35: setStringSize (#const72, 0, 12)*/
    {{.ival=5}, {.ival=64}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 36: setStringValues (#const72, 0, 0, 1953261926, 1763734117, 2019910766, 538976288)*/
    {{.ival=6}, {.ival=64}, {.ival=0}, {.ival=0}, {.rawVal=1953261926}, {.rawVal=1763734117}, {.rawVal=2019910766}, {.rawVal=538976288}},
    /* PC 37: setStringSize (#const74, 0, 11)*/
    {{.ival=5}, {.ival=65}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 38: setStringValues (#const74, 0, 0, 1953261926, 1948283493, 543518841, 538976288)*/
    {{.ival=6}, {.ival=65}, {.ival=0}, {.ival=0}, {.rawVal=1953261926}, {.rawVal=1948283493}, {.rawVal=543518841}, {.rawVal=538976288}},
    /* PC 39: setStringSize (#const76, 0, 9)*/
    {{.ival=5}, {.ival=66}, {.ival=0}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 40: setStringValues (#const76, 0, 0, 1902473830, 1668179317, 538976377, 538976288)*/
    {{.ival=6}, {.ival=66}, {.ival=0}, {.ival=0}, {.rawVal=1902473830}, {.rawVal=1668179317}, {.rawVal=538976377}, {.rawVal=538976288}},
    /* PC 41: setStringSize (#const78, 0, 4)*/
    {{.ival=5}, {.ival=67}, {.ival=0}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 42: setStringValues (#const78, 0, 0, 1852399975, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=67}, {.ival=0}, {.ival=0}, {.rawVal=1852399975}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 43: setStringSize (#const80, 0, 7)*/
    {{.ival=5}, {.ival=68}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 44: setStringValues (#const80, 0, 0, 1818326385, 544830569, 538976288, 538976288)*/
    {{.ival=6}, {.ival=68}, {.ival=0}, {.ival=0}, {.rawVal=1818326385}, {.rawVal=544830569}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 45: setStringSize (#const82, 0, 6)*/
    {{.ival=5}, {.ival=69}, {.ival=0}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 46: setStringValues (#const82, 0, 0, 1970040694, 538994029, 538976288, 538976288)*/
    {{.ival=6}, {.ival=69}, {.ival=0}, {.ival=0}, {.rawVal=1970040694}, {.rawVal=538994029}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 47: setStringSize (#const84, 0, 7)*/
    {{.ival=5}, {.ival=70}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 48: setStringValues (#const84, 0, 0, 1953853298, 543649385, 538976288, 538976288)*/
    {{.ival=6}, {.ival=70}, {.ival=0}, {.ival=0}, {.rawVal=1953853298}, {.rawVal=543649385}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 49: setStringSize (#const86, 0, 11)*/
    {{.ival=5}, {.ival=71}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 50: setStringValues (#const86, 0, 0, 1952867692, 1953853216, 544503152, 538976288)*/
    {{.ival=6}, {.ival=71}, {.ival=0}, {.ival=0}, {.rawVal=1952867692}, {.rawVal=1953853216}, {.rawVal=544503152}, {.rawVal=538976288}},
    /* PC 51: setStringSize (#const88, 0, 12)*/
    {{.ival=5}, {.ival=72}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 52: setStringValues (#const88, 0, 0, 1751607666, 1970217076, 1953853556, 538976288)*/
    {{.ival=6}, {.ival=72}, {.ival=0}, {.ival=0}, {.rawVal=1751607666}, {.rawVal=1970217076}, {.rawVal=1953853556}, {.rawVal=538976288}},
    /* PC 53: setStringSize (#const2, 0, 12)*/
    {{.ival=5}, {.ival=74}, {.ival=0}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 54: setStringValues (#const2, 0, 0, 1936028272, 1702043763, 1952671084, 538976288)*/
    {{.ival=6}, {.ival=74}, {.ival=0}, {.ival=0}, {.rawVal=1936028272}, {.rawVal=1702043763}, {.rawVal=1952671084}, {.rawVal=538976288}},
    /* PC 55: setStringSize (#const4, 0, 2)*/
    {{.ival=5}, {.ival=75}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 56: setStringValues (#const4, 0, 0, 538976318, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=75}, {.ival=0}, {.ival=0}, {.rawVal=538976318}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 57: setStringSize (#const5, 0, 2)*/
    {{.ival=5}, {.ival=76}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 58: setStringValues (#const5, 0, 0, 538976288, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=76}, {.ival=0}, {.ival=0}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 59: setStringSize (#const12, 0, 7)*/
    {{.ival=5}, {.ival=77}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 60: setStringValues (#const12, 0, 0, 1952867692, 544106784, 538976288, 538976288)*/
    {{.ival=6}, {.ival=77}, {.ival=0}, {.ival=0}, {.rawVal=1952867692}, {.rawVal=544106784}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 61: setStringSize (#const13, 0, 8)*/
    {{.ival=5}, {.ival=78}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 62: setStringValues (#const13, 0, 0, 1751607666, 1852383348, 538976288, 538976288)*/
    {{.ival=6}, {.ival=78}, {.ival=0}, {.ival=0}, {.rawVal=1751607666}, {.rawVal=1852383348}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 63: setStringSize (#const14, 0, 8)*/
    {{.ival=5}, {.ival=79}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 64: setStringValues (#const14, 0, 0, 1952867692, 1953853216, 538976288, 538976288)*/
    {{.ival=6}, {.ival=79}, {.ival=0}, {.ival=0}, {.rawVal=1952867692}, {.rawVal=1953853216}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 65: setStringSize (#const16, 0, 9)*/
    {{.ival=5}, {.ival=80}, {.ival=0}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 66: setStringValues (#const16, 0, 0, 1751607666, 1970217076, 538976372, 538976288)*/
    {{.ival=6}, {.ival=80}, {.ival=0}, {.ival=0}, {.rawVal=1751607666}, {.rawVal=1970217076}, {.rawVal=538976372}, {.rawVal=538976288}},
    /* PC 67: setStringSize (#const18, 0, 6)*/
    {{.ival=5}, {.ival=81}, {.ival=0}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 68: setStringValues (#const18, 0, 0, 1701080681, 538976376, 538976288, 538976288)*/
    {{.ival=6}, {.ival=81}, {.ival=0}, {.ival=0}, {.rawVal=1701080681}, {.rawVal=538976376}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 69: setStringSize (#const20, 0, 6)*/
    {{.ival=5}, {.ival=82}, {.ival=0}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 70: setStringValues (#const20, 0, 0, 1634761058, 538997619, 538976288, 538976288)*/
    {{.ival=6}, {.ival=82}, {.ival=0}, {.ival=0}, {.rawVal=1634761058}, {.rawVal=538997619}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 71: setStringSize (#const21, 0, 7)*/
    {{.ival=5}, {.ival=83}, {.ival=0}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 72: setStringValues (#const21, 0, 0, 1886875500, 544437089, 538976288, 538976288)*/
    {{.ival=6}, {.ival=83}, {.ival=0}, {.ival=0}, {.rawVal=1886875500}, {.rawVal=544437089}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 73: setStringSize (#const22, 0, 8)*/
    {{.ival=5}, {.ival=84}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 74: setStringValues (#const22, 0, 0, 1751607656, 1936941424, 538976288, 538976288)*/
    {{.ival=6}, {.ival=84}, {.ival=0}, {.ival=0}, {.rawVal=1751607656}, {.rawVal=1936941424}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 75: setStringSize (#const23, 0, 9)*/
    {{.ival=5}, {.ival=85}, {.ival=0}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 76: setStringValues (#const23, 0, 0, 544698220, 1818585203, 538976358, 538976288)*/
    {{.ival=6}, {.ival=85}, {.ival=0}, {.ival=0}, {.rawVal=544698220}, {.rawVal=1818585203}, {.rawVal=538976358}, {.rawVal=538976288}},
    /* PC 77: setStringSize (#const25, 0, 10)*/
    {{.ival=5}, {.ival=86}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 78: setStringValues (#const25, 0, 0, 1751607656, 1701344032, 538994284, 538976288)*/
    {{.ival=6}, {.ival=86}, {.ival=0}, {.ival=0}, {.rawVal=1751607656}, {.rawVal=1701344032}, {.rawVal=538994284}, {.rawVal=538976288}},
    /* PC 79: setStringSize (#const27, 0, 4)*/
    {{.ival=5}, {.ival=87}, {.ival=0}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 80: setStringValues (#const27, 0, 0, 1801545072, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=87}, {.ival=0}, {.ival=0}, {.rawVal=1801545072}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 81: setStringSize (#const29, 0, 3)*/
    {{.ival=5}, {.ival=88}, {.ival=0}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 82: setStringValues (#const29, 0, 0, 544884768, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=88}, {.ival=0}, {.ival=0}, {.rawVal=544884768}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 83: setStringSize (#const35, 0, 4)*/
    {{.ival=5}, {.ival=89}, {.ival=0}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 84: setStringValues (#const35, 0, 0, 1702131053, 538976288, 538976288, 538976288)*/
    {{.ival=6}, {.ival=89}, {.ival=0}, {.ival=0}, {.rawVal=1702131053}, {.rawVal=538976288}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 85: assignInteger (#fv_dspInit_i, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=32}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 86: label ID:726*/
    /* PC 86: compareIntegerLess (#fv_dspInit_i, 0, #const102, 0)*/
    {{.ival=40}, {.ival=32}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 87: jumpNCF (label ID:727)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 88: initBiquad (LinFilter, #fv_dspInit_i, #const103, #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 89: initBiquad (RinFilter, #fv_dspInit_i, #const103, #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 90: initBiquad (LoutFilter, #fv_dspInit_i, #const103, #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 91: initBiquad (RoutFilter, #fv_dspInit_i, #const103, #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=32}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 92: addInteger (#fv_dspInit_i, #const98 = "1"(integer), #fv_dspInit_i)*/
    {{.ival=22}, {.ival=32}, {.ival=29}, {.ival=32}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 93: jump (label ID:726)*/
    {{.ival=50}, {.ival=-7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 94: label ID:727*/
    /* PC 94: assignInteger (LoutInpSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=14}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 95: assignInteger (RoutInpSel, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=4}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 96: assignRational (fs, #const106)*/
    {{.ival=28}, {.ival=9}, {.ival=35}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 97: assignRational (volume, #const103)*/
    {{.ival=28}, {.ival=11}, {.ival=34}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 98: uiInitPanel (1, p, 0)*/
    {{.ival=201}, {.ival=1}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 99: uiInitDisplay (1, d, 0, p, 0)*/
    {{.ival=203}, {.ival=1}, {.ival=15}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 100: uiSetDisplayTextDim (d, 0, 16, 2)*/
    {{.ival=213}, {.ival=15}, {.ival=0}, {.ival=16}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 101: uiInitButton (8, bUp, 0, p, 0)*/
    {{.ival=202}, {.ival=8}, {.ival=16}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 102: uiInitButton (7, bDown, 0, p, 0)*/
    {{.ival=202}, {.ival=7}, {.ival=6}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 103: uiInitButton (6, bSelect, 0, p, 0)*/
    {{.ival=202}, {.ival=6}, {.ival=17}, {.ival=0}, {.ival=20}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 104: assignInteger (uiState, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=23}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 105: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 106: assignInteger (uiUpdate, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 107: assignInteger (uiSelChannel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=22}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 108: assignInteger (uiMenuSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=19}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 109: assignInteger (uiFilterBankSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=7}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 110: assignInteger (uiFilterIndex, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=2}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 111: assignInteger (uiFilterTypeSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=1}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 112: assignRational (ffreq, #const109)*/
    {{.ival=28}, {.ival=13}, {.ival=36}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 113: assignRational (fgain, #const103 = "1.0"(rational))*/
    {{.ival=28}, {.ival=21}, {.ival=34}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 114: assignRational (fquality, #const103 = "1.0"(rational))*/
    {{.ival=28}, {.ival=8}, {.ival=34}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 115: label ID:217*/
    /* PC 115: uiCheckButtonPressed (bSelect, 0)*/
    {{.ival=210}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 116: jumpNCF (label ID:904)*/
    {{.ival=52}, {.ival=536}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 117: compareIntegerEqual (uiState, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 118: jumpNCF (label ID:728)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 119: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 120: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 121: label ID:728*/
    /* PC 121: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 122: jumpNCF (label ID:733)*/
    {{.ival=52}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 123: compareIntegerEqual (uiState, 0, #const42, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 124: jumpNCF (label ID:732)*/
    {{.ival=52}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 125: assignInteger (uiMenuSel, uiSel)*/
    {{.ival=21}, {.ival=19}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 126: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 127: jumpNCF (label ID:729)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 128: assignInteger (uiState, #const44)*/
    {{.ival=21}, {.ival=23}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 129: label ID:729*/
    /* PC 129: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 130: jumpNCF (label ID:730)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 131: assignInteger (uiState, #const45)*/
    {{.ival=21}, {.ival=23}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 132: assignInteger (uiSel, uiSelChannel)*/
    {{.ival=21}, {.ival=10}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 133: label ID:730*/
    /* PC 133: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 134: jumpNCF (label ID:731)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 135: assignInteger (uiState, #const47)*/
    {{.ival=21}, {.ival=23}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 136: label ID:731*/
    /* PC 136: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 137: update (uiMenuSel)*/
    {{.ival=56}, {.ival=19}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 138: label ID:732*/
    /* PC 138: label ID:733*/
    /* PC 138: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 139: jumpNCF (label ID:735)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 140: compareIntegerEqual (uiState, 0, #const44, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 141: jumpNCF (label ID:734)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 142: assignInteger (uiFilterBankSel, uiSel)*/
    {{.ival=21}, {.ival=7}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 143: assignInteger (uiSel, uiFilterIndex)*/
    {{.ival=21}, {.ival=10}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 144: assignInteger (uiState, #const48)*/
    {{.ival=21}, {.ival=23}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 145: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 146: update (uiFilterBankSel)*/
    {{.ival=56}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 147: label ID:734*/
    /* PC 147: label ID:735*/
    /* PC 147: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 148: jumpNCF (label ID:737)*/
    {{.ival=52}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 149: compareIntegerEqual (uiState, 0, #const48, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 150: jumpNCF (label ID:736)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 151: assignInteger (uiFilterIndex, uiSel)*/
    {{.ival=21}, {.ival=2}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 152: assignInteger (uiSel, uiFilterTypeSel)*/
    {{.ival=21}, {.ival=10}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 153: assignInteger (uiState, #const49)*/
    {{.ival=21}, {.ival=23}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 154: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 155: update (uiFilterIndex)*/
    {{.ival=56}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 156: label ID:736*/
    /* PC 156: label ID:737*/
    /* PC 156: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 157: jumpNCF (label ID:775)*/
    {{.ival=52}, {.ival=108}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 158: compareIntegerEqual (uiState, 0, #const49, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 159: jumpNCF (label ID:774)*/
    {{.ival=52}, {.ival=106}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 160: assignInteger (uiFilterTypeSel, uiSel)*/
    {{.ival=21}, {.ival=1}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 161: update (uiFilterTypeSel)*/
    {{.ival=56}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 162: compareIntegerEqual (uiFilterTypeSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 163: jumpNCF (label ID:772)*/
    {{.ival=52}, {.ival=100}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 164: compareIntegerEqual (uiFilterTypeSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 165: jumpNCF (label ID:742)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 166: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 167: jumpNCF (label ID:738)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 168: initBiquad (LinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 169: label ID:738*/
    /* PC 169: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 170: jumpNCF (label ID:739)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 171: initBiquad (RinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 172: label ID:739*/
    /* PC 172: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 173: jumpNCF (label ID:740)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 174: initBiquad (LoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 175: label ID:740*/
    /* PC 175: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 176: jumpNCF (label ID:741)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 177: initBiquad (RoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 178: label ID:741*/
    /* PC 178: label ID:742*/
    /* PC 178: compareIntegerEqual (uiFilterTypeSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 179: jumpNCF (label ID:747)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 180: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 181: jumpNCF (label ID:743)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 182: initBiquadAsLP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 183: label ID:743*/
    /* PC 183: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 184: jumpNCF (label ID:744)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 185: initBiquadAsLP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 186: label ID:744*/
    /* PC 186: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 187: jumpNCF (label ID:745)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 188: initBiquadAsLP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 189: label ID:745*/
    /* PC 189: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 190: jumpNCF (label ID:746)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 191: initBiquadAsLP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 192: label ID:746*/
    /* PC 192: label ID:747*/
    /* PC 192: compareIntegerEqual (uiFilterTypeSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 193: jumpNCF (label ID:752)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 194: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 195: jumpNCF (label ID:748)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 196: initBiquadAsHP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 197: label ID:748*/
    /* PC 197: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 198: jumpNCF (label ID:749)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 199: initBiquadAsHP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 200: label ID:749*/
    /* PC 200: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 201: jumpNCF (label ID:750)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 202: initBiquadAsHP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 203: label ID:750*/
    /* PC 203: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 204: jumpNCF (label ID:751)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 205: initBiquadAsHP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 206: label ID:751*/
    /* PC 206: label ID:752*/
    /* PC 206: compareIntegerEqual (uiFilterTypeSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 207: jumpNCF (label ID:757)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 208: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 209: jumpNCF (label ID:753)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 210: initBiquadAsLowFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 211: label ID:753*/
    /* PC 211: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 212: jumpNCF (label ID:754)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 213: initBiquadAsLowFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 214: label ID:754*/
    /* PC 214: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 215: jumpNCF (label ID:755)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 216: initBiquadAsLowFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 217: label ID:755*/
    /* PC 217: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 218: jumpNCF (label ID:756)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 219: initBiquadAsLowFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 220: label ID:756*/
    /* PC 220: label ID:757*/
    /* PC 220: compareIntegerEqual (uiFilterTypeSel, 0, #const95, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=60}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 221: jumpNCF (label ID:762)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 222: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 223: jumpNCF (label ID:758)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 224: initBiquadAsHighFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 225: label ID:758*/
    /* PC 225: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 226: jumpNCF (label ID:759)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 227: initBiquadAsHighFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 228: label ID:759*/
    /* PC 228: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 229: jumpNCF (label ID:760)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 230: initBiquadAsHighFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 231: label ID:760*/
    /* PC 231: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 232: jumpNCF (label ID:761)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 233: initBiquadAsHighFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 234: label ID:761*/
    /* PC 234: label ID:762*/
    /* PC 234: compareIntegerEqual (uiFilterTypeSel, 0, #const53, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 235: jumpNCF (label ID:767)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 236: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 237: jumpNCF (label ID:763)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 238: initBiquadAsPeakFilter (LinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 239: label ID:763*/
    /* PC 239: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 240: jumpNCF (label ID:764)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 241: initBiquadAsPeakFilter (RinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 242: label ID:764*/
    /* PC 242: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 243: jumpNCF (label ID:765)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 244: initBiquadAsPeakFilter (LoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 245: label ID:765*/
    /* PC 245: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 246: jumpNCF (label ID:766)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 247: initBiquadAsPeakFilter (RoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 248: label ID:766*/
    /* PC 248: label ID:767*/
    /* PC 248: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 249: jumpNCF (label ID:768)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 250: update (LinFilter)*/
    {{.ival=56}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 251: label ID:768*/
    /* PC 251: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 252: jumpNCF (label ID:769)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 253: update (RinFilter)*/
    {{.ival=56}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 254: label ID:769*/
    /* PC 254: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 255: jumpNCF (label ID:770)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 256: update (LoutFilter)*/
    {{.ival=56}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 257: label ID:770*/
    /* PC 257: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 258: jumpNCF (label ID:771)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 259: update (RoutFilter)*/
    {{.ival=56}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 260: label ID:771*/
    /* PC 260: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 261: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 262: jump (label ID:773)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 263: label ID:772*/
    /* PC 263: assignInteger (uiState, #const50)*/
    {{.ival=21}, {.ival=23}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 264: label ID:773*/
    /* PC 264: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 265: label ID:774*/
    /* PC 265: label ID:775*/
    /* PC 265: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 266: jumpNCF (label ID:813)*/
    {{.ival=52}, {.ival=107}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 267: compareIntegerEqual (uiState, 0, #const50, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 268: jumpNCF (label ID:812)*/
    {{.ival=52}, {.ival=105}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 269: compareIntegerLess (uiFilterTypeSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=40}, {.ival=1}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 270: jumpNCF (label ID:810)*/
    {{.ival=52}, {.ival=100}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 271: compareIntegerEqual (uiFilterTypeSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 272: jumpNCF (label ID:780)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 273: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 274: jumpNCF (label ID:776)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 275: initBiquad (LinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 276: label ID:776*/
    /* PC 276: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 277: jumpNCF (label ID:777)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 278: initBiquad (RinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 279: label ID:777*/
    /* PC 279: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 280: jumpNCF (label ID:778)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 281: initBiquad (LoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 282: label ID:778*/
    /* PC 282: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 283: jumpNCF (label ID:779)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 284: initBiquad (RoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 285: label ID:779*/
    /* PC 285: label ID:780*/
    /* PC 285: compareIntegerEqual (uiFilterTypeSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 286: jumpNCF (label ID:785)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 287: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 288: jumpNCF (label ID:781)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 289: initBiquadAsLP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 290: label ID:781*/
    /* PC 290: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 291: jumpNCF (label ID:782)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 292: initBiquadAsLP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 293: label ID:782*/
    /* PC 293: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 294: jumpNCF (label ID:783)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 295: initBiquadAsLP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 296: label ID:783*/
    /* PC 296: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 297: jumpNCF (label ID:784)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 298: initBiquadAsLP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 299: label ID:784*/
    /* PC 299: label ID:785*/
    /* PC 299: compareIntegerEqual (uiFilterTypeSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 300: jumpNCF (label ID:790)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 301: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 302: jumpNCF (label ID:786)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 303: initBiquadAsHP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 304: label ID:786*/
    /* PC 304: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 305: jumpNCF (label ID:787)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 306: initBiquadAsHP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 307: label ID:787*/
    /* PC 307: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 308: jumpNCF (label ID:788)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 309: initBiquadAsHP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 310: label ID:788*/
    /* PC 310: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 311: jumpNCF (label ID:789)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 312: initBiquadAsHP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 313: label ID:789*/
    /* PC 313: label ID:790*/
    /* PC 313: compareIntegerEqual (uiFilterTypeSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 314: jumpNCF (label ID:795)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 315: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 316: jumpNCF (label ID:791)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 317: initBiquadAsLowFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 318: label ID:791*/
    /* PC 318: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 319: jumpNCF (label ID:792)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 320: initBiquadAsLowFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 321: label ID:792*/
    /* PC 321: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 322: jumpNCF (label ID:793)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 323: initBiquadAsLowFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 324: label ID:793*/
    /* PC 324: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 325: jumpNCF (label ID:794)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 326: initBiquadAsLowFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 327: label ID:794*/
    /* PC 327: label ID:795*/
    /* PC 327: compareIntegerEqual (uiFilterTypeSel, 0, #const95, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=60}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 328: jumpNCF (label ID:800)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 329: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 330: jumpNCF (label ID:796)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 331: initBiquadAsHighFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 332: label ID:796*/
    /* PC 332: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 333: jumpNCF (label ID:797)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 334: initBiquadAsHighFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 335: label ID:797*/
    /* PC 335: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 336: jumpNCF (label ID:798)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 337: initBiquadAsHighFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 338: label ID:798*/
    /* PC 338: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 339: jumpNCF (label ID:799)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 340: initBiquadAsHighFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 341: label ID:799*/
    /* PC 341: label ID:800*/
    /* PC 341: compareIntegerEqual (uiFilterTypeSel, 0, #const53, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 342: jumpNCF (label ID:805)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 343: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 344: jumpNCF (label ID:801)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 345: initBiquadAsPeakFilter (LinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 346: label ID:801*/
    /* PC 346: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 347: jumpNCF (label ID:802)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 348: initBiquadAsPeakFilter (RinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 349: label ID:802*/
    /* PC 349: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 350: jumpNCF (label ID:803)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 351: initBiquadAsPeakFilter (LoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 352: label ID:803*/
    /* PC 352: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 353: jumpNCF (label ID:804)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 354: initBiquadAsPeakFilter (RoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 355: label ID:804*/
    /* PC 355: label ID:805*/
    /* PC 355: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 356: jumpNCF (label ID:806)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 357: update (LinFilter)*/
    {{.ival=56}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 358: label ID:806*/
    /* PC 358: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 359: jumpNCF (label ID:807)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 360: update (RinFilter)*/
    {{.ival=56}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 361: label ID:807*/
    /* PC 361: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 362: jumpNCF (label ID:808)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 363: update (LoutFilter)*/
    {{.ival=56}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 364: label ID:808*/
    /* PC 364: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 365: jumpNCF (label ID:809)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 366: update (RoutFilter)*/
    {{.ival=56}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 367: label ID:809*/
    /* PC 367: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 368: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 369: jump (label ID:811)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 370: label ID:810*/
    /* PC 370: assignInteger (uiState, #const52)*/
    {{.ival=21}, {.ival=23}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 371: label ID:811*/
    /* PC 371: update (ffreq)*/
    {{.ival=56}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 372: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 373: label ID:812*/
    /* PC 373: label ID:813*/
    /* PC 373: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 374: jumpNCF (label ID:851)*/
    {{.ival=52}, {.ival=107}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 375: compareIntegerEqual (uiState, 0, #const52, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 376: jumpNCF (label ID:850)*/
    {{.ival=52}, {.ival=105}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 377: compareIntegerLess (uiFilterTypeSel, 0, #const53, 0)*/
    {{.ival=40}, {.ival=1}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 378: jumpNCF (label ID:848)*/
    {{.ival=52}, {.ival=100}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 379: compareIntegerEqual (uiFilterTypeSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 380: jumpNCF (label ID:818)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 381: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 382: jumpNCF (label ID:814)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 383: initBiquad (LinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 384: label ID:814*/
    /* PC 384: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 385: jumpNCF (label ID:815)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 386: initBiquad (RinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 387: label ID:815*/
    /* PC 387: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 388: jumpNCF (label ID:816)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 389: initBiquad (LoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 390: label ID:816*/
    /* PC 390: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 391: jumpNCF (label ID:817)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 392: initBiquad (RoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 393: label ID:817*/
    /* PC 393: label ID:818*/
    /* PC 393: compareIntegerEqual (uiFilterTypeSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 394: jumpNCF (label ID:823)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 395: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 396: jumpNCF (label ID:819)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 397: initBiquadAsLP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 398: label ID:819*/
    /* PC 398: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 399: jumpNCF (label ID:820)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 400: initBiquadAsLP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 401: label ID:820*/
    /* PC 401: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 402: jumpNCF (label ID:821)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 403: initBiquadAsLP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 404: label ID:821*/
    /* PC 404: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 405: jumpNCF (label ID:822)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 406: initBiquadAsLP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 407: label ID:822*/
    /* PC 407: label ID:823*/
    /* PC 407: compareIntegerEqual (uiFilterTypeSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 408: jumpNCF (label ID:828)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 409: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 410: jumpNCF (label ID:824)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 411: initBiquadAsHP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 412: label ID:824*/
    /* PC 412: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 413: jumpNCF (label ID:825)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 414: initBiquadAsHP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 415: label ID:825*/
    /* PC 415: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 416: jumpNCF (label ID:826)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 417: initBiquadAsHP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 418: label ID:826*/
    /* PC 418: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 419: jumpNCF (label ID:827)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 420: initBiquadAsHP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 421: label ID:827*/
    /* PC 421: label ID:828*/
    /* PC 421: compareIntegerEqual (uiFilterTypeSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 422: jumpNCF (label ID:833)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 423: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 424: jumpNCF (label ID:829)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 425: initBiquadAsLowFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 426: label ID:829*/
    /* PC 426: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 427: jumpNCF (label ID:830)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 428: initBiquadAsLowFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 429: label ID:830*/
    /* PC 429: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 430: jumpNCF (label ID:831)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 431: initBiquadAsLowFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 432: label ID:831*/
    /* PC 432: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 433: jumpNCF (label ID:832)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 434: initBiquadAsLowFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 435: label ID:832*/
    /* PC 435: label ID:833*/
    /* PC 435: compareIntegerEqual (uiFilterTypeSel, 0, #const95, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=60}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 436: jumpNCF (label ID:838)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 437: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 438: jumpNCF (label ID:834)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 439: initBiquadAsHighFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 440: label ID:834*/
    /* PC 440: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 441: jumpNCF (label ID:835)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 442: initBiquadAsHighFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 443: label ID:835*/
    /* PC 443: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 444: jumpNCF (label ID:836)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 445: initBiquadAsHighFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 446: label ID:836*/
    /* PC 446: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 447: jumpNCF (label ID:837)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 448: initBiquadAsHighFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 449: label ID:837*/
    /* PC 449: label ID:838*/
    /* PC 449: compareIntegerEqual (uiFilterTypeSel, 0, #const53, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 450: jumpNCF (label ID:843)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 451: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 452: jumpNCF (label ID:839)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 453: initBiquadAsPeakFilter (LinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 454: label ID:839*/
    /* PC 454: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 455: jumpNCF (label ID:840)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 456: initBiquadAsPeakFilter (RinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 457: label ID:840*/
    /* PC 457: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 458: jumpNCF (label ID:841)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 459: initBiquadAsPeakFilter (LoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 460: label ID:841*/
    /* PC 460: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 461: jumpNCF (label ID:842)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 462: initBiquadAsPeakFilter (RoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 463: label ID:842*/
    /* PC 463: label ID:843*/
    /* PC 463: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 464: jumpNCF (label ID:844)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 465: update (LinFilter)*/
    {{.ival=56}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 466: label ID:844*/
    /* PC 466: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 467: jumpNCF (label ID:845)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 468: update (RinFilter)*/
    {{.ival=56}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 469: label ID:845*/
    /* PC 469: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 470: jumpNCF (label ID:846)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 471: update (LoutFilter)*/
    {{.ival=56}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 472: label ID:846*/
    /* PC 472: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 473: jumpNCF (label ID:847)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 474: update (RoutFilter)*/
    {{.ival=56}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 475: label ID:847*/
    /* PC 475: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 476: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 477: jump (label ID:849)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 478: label ID:848*/
    /* PC 478: assignInteger (uiState, #const54)*/
    {{.ival=21}, {.ival=23}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 479: label ID:849*/
    /* PC 479: update (fgain)*/
    {{.ival=56}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 480: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 481: label ID:850*/
    /* PC 481: label ID:851*/
    /* PC 481: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 482: jumpNCF (label ID:887)*/
    {{.ival=52}, {.ival=103}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 483: compareIntegerEqual (uiState, 0, #const54, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 484: jumpNCF (label ID:886)*/
    {{.ival=52}, {.ival=101}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 485: compareIntegerEqual (uiFilterTypeSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 486: jumpNCF (label ID:856)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 487: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 488: jumpNCF (label ID:852)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 489: initBiquad (LinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=18}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 490: label ID:852*/
    /* PC 490: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 491: jumpNCF (label ID:853)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 492: initBiquad (RinFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=5}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 493: label ID:853*/
    /* PC 493: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 494: jumpNCF (label ID:854)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 495: initBiquad (LoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=3}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 496: label ID:854*/
    /* PC 496: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 497: jumpNCF (label ID:855)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 498: initBiquad (RoutFilter, uiFilterIndex, #const103 = "1.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational), #const100 = "0.0"(rational))*/
    {{.ival=105}, {.ival=12}, {.ival=2}, {.ival=34}, {.ival=31}, {.ival=31}, {.ival=31}, {.ival=31}},
    /* PC 499: label ID:855*/
    /* PC 499: label ID:856*/
    /* PC 499: compareIntegerEqual (uiFilterTypeSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 500: jumpNCF (label ID:861)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 501: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 502: jumpNCF (label ID:857)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 503: initBiquadAsLP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 504: label ID:857*/
    /* PC 504: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 505: jumpNCF (label ID:858)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 506: initBiquadAsLP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 507: label ID:858*/
    /* PC 507: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 508: jumpNCF (label ID:859)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 509: initBiquadAsLP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 510: label ID:859*/
    /* PC 510: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 511: jumpNCF (label ID:860)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 512: initBiquadAsLP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=101}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 513: label ID:860*/
    /* PC 513: label ID:861*/
    /* PC 513: compareIntegerEqual (uiFilterTypeSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 514: jumpNCF (label ID:866)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 515: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 516: jumpNCF (label ID:862)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 517: initBiquadAsHP (LinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 518: label ID:862*/
    /* PC 518: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 519: jumpNCF (label ID:863)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 520: initBiquadAsHP (RinFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 521: label ID:863*/
    /* PC 521: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 522: jumpNCF (label ID:864)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 523: initBiquadAsHP (LoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 524: label ID:864*/
    /* PC 524: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 525: jumpNCF (label ID:865)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 526: initBiquadAsHP (RoutFilter, uiFilterIndex, fs, ffreq)*/
    {{.ival=100}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 527: label ID:865*/
    /* PC 527: label ID:866*/
    /* PC 527: compareIntegerEqual (uiFilterTypeSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 528: jumpNCF (label ID:871)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 529: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 530: jumpNCF (label ID:867)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 531: initBiquadAsLowFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 532: label ID:867*/
    /* PC 532: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 533: jumpNCF (label ID:868)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 534: initBiquadAsLowFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 535: label ID:868*/
    /* PC 535: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 536: jumpNCF (label ID:869)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 537: initBiquadAsLowFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 538: label ID:869*/
    /* PC 538: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 539: jumpNCF (label ID:870)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 540: initBiquadAsLowFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=103}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 541: label ID:870*/
    /* PC 541: label ID:871*/
    /* PC 541: compareIntegerEqual (uiFilterTypeSel, 0, #const95, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=60}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 542: jumpNCF (label ID:876)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 543: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 544: jumpNCF (label ID:872)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 545: initBiquadAsHighFreqShelvFilter (LinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 546: label ID:872*/
    /* PC 546: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 547: jumpNCF (label ID:873)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 548: initBiquadAsHighFreqShelvFilter (RinFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 549: label ID:873*/
    /* PC 549: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 550: jumpNCF (label ID:874)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 551: initBiquadAsHighFreqShelvFilter (LoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 552: label ID:874*/
    /* PC 552: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 553: jumpNCF (label ID:875)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 554: initBiquadAsHighFreqShelvFilter (RoutFilter, uiFilterIndex, fs, ffreq, fgain)*/
    {{.ival=104}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=21}, {.ival=0}, {.ival=0}},
    /* PC 555: label ID:875*/
    /* PC 555: label ID:876*/
    /* PC 555: compareIntegerEqual (uiFilterTypeSel, 0, #const53, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 556: jumpNCF (label ID:881)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 557: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 558: jumpNCF (label ID:877)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 559: initBiquadAsPeakFilter (LinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=18}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 560: label ID:877*/
    /* PC 560: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 561: jumpNCF (label ID:878)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 562: initBiquadAsPeakFilter (RinFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=5}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 563: label ID:878*/
    /* PC 563: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 564: jumpNCF (label ID:879)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 565: initBiquadAsPeakFilter (LoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=3}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 566: label ID:879*/
    /* PC 566: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 567: jumpNCF (label ID:880)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 568: initBiquadAsPeakFilter (RoutFilter, uiFilterIndex, fs, ffreq, fquality, fgain)*/
    {{.ival=102}, {.ival=12}, {.ival=2}, {.ival=9}, {.ival=13}, {.ival=8}, {.ival=21}, {.ival=0}},
    /* PC 569: label ID:880*/
    /* PC 569: label ID:881*/
    /* PC 569: compareIntegerEqual (uiFilterBankSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 570: jumpNCF (label ID:882)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 571: update (LinFilter)*/
    {{.ival=56}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 572: label ID:882*/
    /* PC 572: compareIntegerEqual (uiFilterBankSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 573: jumpNCF (label ID:883)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 574: update (RinFilter)*/
    {{.ival=56}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 575: label ID:883*/
    /* PC 575: compareIntegerEqual (uiFilterBankSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 576: jumpNCF (label ID:884)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 577: update (LoutFilter)*/
    {{.ival=56}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 578: label ID:884*/
    /* PC 578: compareIntegerEqual (uiFilterBankSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 579: jumpNCF (label ID:885)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 580: update (RoutFilter)*/
    {{.ival=56}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 581: label ID:885*/
    /* PC 581: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 582: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 583: update (fquality)*/
    {{.ival=56}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 584: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 585: label ID:886*/
    /* PC 585: label ID:887*/
    /* PC 585: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 586: jumpNCF (label ID:889)*/
    {{.ival=52}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 587: compareIntegerEqual (uiState, 0, #const47, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 588: jumpNCF (label ID:888)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 589: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 590: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 591: label ID:888*/
    /* PC 591: label ID:889*/
    /* PC 591: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 592: jumpNCF (label ID:893)*/
    {{.ival=52}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 593: compareIntegerEqual (uiState, 0, #const45, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 594: jumpNCF (label ID:892)*/
    {{.ival=52}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 595: assignInteger (uiSelChannel, uiSel)*/
    {{.ival=21}, {.ival=22}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 596: compareIntegerEqual (uiSelChannel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=22}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 597: jumpNCF (label ID:890)*/
    {{.ival=52}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 598: assignInteger (uiState, #const55)*/
    {{.ival=21}, {.ival=23}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 599: assignInteger (uiSel, LoutInpSel)*/
    {{.ival=21}, {.ival=10}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 600: assignInteger (uiSelChannel, LoutInpSel)*/
    {{.ival=21}, {.ival=22}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 601: jump (label ID:891)*/
    {{.ival=50}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 602: label ID:890*/
    /* PC 602: assignInteger (uiState, #const56)*/
    {{.ival=21}, {.ival=23}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 603: assignInteger (uiSel, RoutInpSel)*/
    {{.ival=21}, {.ival=10}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 604: assignInteger (uiSelChannel, RoutInpSel)*/
    {{.ival=21}, {.ival=22}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 605: label ID:891*/
    /* PC 605: update (uiSelChannel)*/
    {{.ival=56}, {.ival=22}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 606: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 607: label ID:892*/
    /* PC 607: label ID:893*/
    /* PC 607: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 608: jumpNCF (label ID:898)*/
    {{.ival=52}, {.ival=19}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 609: compareIntegerEqual (uiState, 0, #const55, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 610: jumpNCF (label ID:897)*/
    {{.ival=52}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 611: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 612: jumpNCF (label ID:894)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 613: assignInteger (LoutInpSel, uiSel)*/
    {{.ival=21}, {.ival=14}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 614: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 615: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 616: assignInteger (uiSelChannel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=22}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 617: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 618: jump (label ID:896)*/
    {{.ival=50}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 619: label ID:894*/
    /* PC 619: compareIntegerNEqual (RoutInpSel, 0, uiSel, 0)*/
    {{.ival=43}, {.ival=4}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 620: jumpNCF (label ID:895)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 621: assignInteger (LoutInpSel, uiSel)*/
    {{.ival=21}, {.ival=14}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 622: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 623: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 624: assignInteger (uiSelChannel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=22}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 625: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 626: label ID:895*/
    /* PC 626: label ID:896*/
    /* PC 626: update (LoutInpSel)*/
    {{.ival=56}, {.ival=14}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 627: label ID:897*/
    /* PC 627: label ID:898*/
    /* PC 627: compareIntegerEqual (#fv_uiDisplay_stateChange, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=40}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 628: jumpNCF (label ID:903)*/
    {{.ival=52}, {.ival=19}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 629: compareIntegerEqual (uiState, 0, #const56, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 630: jumpNCF (label ID:902)*/
    {{.ival=52}, {.ival=17}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 631: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 632: jumpNCF (label ID:899)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 633: assignInteger (RoutInpSel, uiSel)*/
    {{.ival=21}, {.ival=4}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 634: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 635: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 636: assignInteger (uiSelChannel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=22}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 637: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 638: jump (label ID:901)*/
    {{.ival=50}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 639: label ID:899*/
    /* PC 639: compareIntegerNEqual (LoutInpSel, 0, uiSel, 0)*/
    {{.ival=43}, {.ival=14}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 640: jumpNCF (label ID:900)*/
    {{.ival=52}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 641: assignInteger (RoutInpSel, uiSel)*/
    {{.ival=21}, {.ival=4}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 642: assignInteger (#fv_uiDisplay_stateChange, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 643: assignInteger (uiState, #const42)*/
    {{.ival=21}, {.ival=23}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 644: assignInteger (uiSelChannel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=22}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 645: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 646: label ID:900*/
    /* PC 646: label ID:901*/
    /* PC 646: update (RoutInpSel)*/
    {{.ival=56}, {.ival=4}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 647: label ID:902*/
    /* PC 647: label ID:903*/
    /* PC 647: assignInteger (uiUpdate, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 648: update (uiState)*/
    {{.ival=56}, {.ival=23}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 649: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 650: update (uiUpdate)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 651: assignInteger (#fv_uiDisplay_stateChange, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=40}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 652: label ID:904*/
    /* PC 652: uiCheckButtonPressed (bUp, 0)*/
    {{.ival=210}, {.ival=16}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 653: jumpNCF (label ID:937)*/
    {{.ival=52}, {.ival=89}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 654: compareIntegerEqual (uiState, 0, #const42, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 655: jumpNCF (label ID:907)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 656: compareIntegerLess (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 657: jumpNCF (label ID:905)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 658: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 659: jump (label ID:906)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 660: label ID:905*/
    /* PC 660: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 661: label ID:906*/
    /* PC 661: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 662: label ID:907*/
    /* PC 662: compareIntegerEqual (uiState, 0, #const44, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 663: jumpNCF (label ID:910)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 664: compareIntegerLess (uiSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 665: jumpNCF (label ID:908)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 666: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 667: jump (label ID:909)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 668: label ID:908*/
    /* PC 668: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 669: label ID:909*/
    /* PC 669: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 670: label ID:910*/
    /* PC 670: compareIntegerEqual (uiState, 0, #const48, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 671: jumpNCF (label ID:913)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 672: compareIntegerLess (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 673: jumpNCF (label ID:911)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 674: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 675: jump (label ID:912)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 676: label ID:911*/
    /* PC 676: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 677: label ID:912*/
    /* PC 677: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 678: label ID:913*/
    /* PC 678: compareIntegerEqual (uiState, 0, #const49, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 679: jumpNCF (label ID:916)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 680: compareIntegerLess (uiSel, 0, #const53, 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 681: jumpNCF (label ID:914)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 682: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 683: jump (label ID:915)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 684: label ID:914*/
    /* PC 684: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 685: label ID:915*/
    /* PC 685: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 686: label ID:916*/
    /* PC 686: compareIntegerEqual (uiState, 0, #const50, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 687: jumpNCF (label ID:919)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 688: compareRationalLess (ffreq, 0, #const57, 0)*/
    {{.ival=34}, {.ival=13}, {.ival=0}, {.ival=53}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 689: jumpNCF (label ID:917)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 690: addRational (ffreq, #const58, ffreq)*/
    {{.ival=29}, {.ival=13}, {.ival=54}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 691: jump (label ID:918)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 692: label ID:917*/
    /* PC 692: assignRational (ffreq, #const58)*/
    {{.ival=28}, {.ival=13}, {.ival=54}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 693: label ID:918*/
    /* PC 693: update (ffreq)*/
    {{.ival=56}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 694: label ID:919*/
    /* PC 694: compareIntegerEqual (uiState, 0, #const52, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 695: jumpNCF (label ID:922)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 696: compareRationalLess (fgain, 0, #const59, 0)*/
    {{.ival=34}, {.ival=21}, {.ival=0}, {.ival=55}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 697: jumpNCF (label ID:920)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 698: addRational (fgain, #const60, fgain)*/
    {{.ival=29}, {.ival=21}, {.ival=56}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 699: jump (label ID:921)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 700: label ID:920*/
    /* PC 700: assignRational (fgain, #const61)*/
    {{.ival=28}, {.ival=21}, {.ival=57}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 701: label ID:921*/
    /* PC 701: update (fgain)*/
    {{.ival=56}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 702: label ID:922*/
    /* PC 702: compareIntegerEqual (uiState, 0, #const54, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 703: jumpNCF (label ID:925)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 704: compareRationalLess (fquality, 0, #const59, 0)*/
    {{.ival=34}, {.ival=8}, {.ival=0}, {.ival=55}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 705: jumpNCF (label ID:923)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 706: addRational (fquality, #const60, fquality)*/
    {{.ival=29}, {.ival=8}, {.ival=56}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 707: jump (label ID:924)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 708: label ID:923*/
    /* PC 708: assignRational (fquality, #const60)*/
    {{.ival=28}, {.ival=8}, {.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 709: label ID:924*/
    /* PC 709: update (fquality)*/
    {{.ival=56}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 710: label ID:925*/
    /* PC 710: compareIntegerEqual (uiState, 0, #const47, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 711: jumpNCF (label ID:927)*/
    {{.ival=52}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 712: compareRationalLess (volume, 0, #const62, 0)*/
    {{.ival=34}, {.ival=11}, {.ival=0}, {.ival=58}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 713: jumpNCF (label ID:926)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 714: addRational (volume, #const60, volume)*/
    {{.ival=29}, {.ival=11}, {.ival=56}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 715: update (volume)*/
    {{.ival=56}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 716: label ID:926*/
    /* PC 716: label ID:927*/
    /* PC 716: compareIntegerEqual (uiState, 0, #const45, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 717: jumpNCF (label ID:930)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 718: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 719: jumpNCF (label ID:928)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 720: assignInteger (uiSel, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 721: jump (label ID:929)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 722: label ID:928*/
    /* PC 722: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 723: label ID:929*/
    /* PC 723: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 724: label ID:930*/
    /* PC 724: compareIntegerEqual (uiState, 0, #const55, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 725: jumpNCF (label ID:933)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 726: compareIntegerLess (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 727: jumpNCF (label ID:931)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 728: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 729: jump (label ID:932)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 730: label ID:931*/
    /* PC 730: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 731: label ID:932*/
    /* PC 731: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 732: label ID:933*/
    /* PC 732: compareIntegerEqual (uiState, 0, #const56, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 733: jumpNCF (label ID:936)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 734: compareIntegerLess (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=40}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 735: jumpNCF (label ID:934)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 736: addInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=22}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 737: jump (label ID:935)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 738: label ID:934*/
    /* PC 738: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 739: label ID:935*/
    /* PC 739: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 740: label ID:936*/
    /* PC 740: assignInteger (uiUpdate, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 741: update (uiUpdate)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 742: label ID:937*/
    /* PC 742: uiCheckButtonPressed (bDown, 0)*/
    {{.ival=210}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 743: jumpNCF (label ID:970)*/
    {{.ival=52}, {.ival=89}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 744: compareIntegerEqual (uiState, 0, #const42, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 745: jumpNCF (label ID:940)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 746: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 747: jumpNCF (label ID:938)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 748: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 749: jump (label ID:939)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 750: label ID:938*/
    /* PC 750: assignInteger (uiSel, #const99 = "2"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 751: label ID:939*/
    /* PC 751: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 752: label ID:940*/
    /* PC 752: compareIntegerEqual (uiState, 0, #const44, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 753: jumpNCF (label ID:943)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 754: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 755: jumpNCF (label ID:941)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 756: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 757: jump (label ID:942)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 758: label ID:941*/
    /* PC 758: assignInteger (uiSel, #const102 = "3"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 759: label ID:942*/
    /* PC 759: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 760: label ID:943*/
    /* PC 760: compareIntegerEqual (uiState, 0, #const48, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 761: jumpNCF (label ID:946)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 762: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 763: jumpNCF (label ID:944)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 764: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 765: jump (label ID:945)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 766: label ID:944*/
    /* PC 766: assignInteger (uiSel, #const99 = "2"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 767: label ID:945*/
    /* PC 767: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 768: label ID:946*/
    /* PC 768: compareIntegerEqual (uiState, 0, #const49, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 769: jumpNCF (label ID:949)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 770: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 771: jumpNCF (label ID:947)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 772: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 773: jump (label ID:948)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 774: label ID:947*/
    /* PC 774: assignInteger (uiSel, #const53)*/
    {{.ival=21}, {.ival=10}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 775: label ID:948*/
    /* PC 775: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 776: label ID:949*/
    /* PC 776: compareIntegerEqual (uiState, 0, #const50, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 777: jumpNCF (label ID:952)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 778: compareRationalMore (ffreq, 0, #const58, 0)*/
    {{.ival=35}, {.ival=13}, {.ival=0}, {.ival=54}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 779: jumpNCF (label ID:950)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 780: subRational (ffreq, #const58, ffreq)*/
    {{.ival=30}, {.ival=13}, {.ival=54}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 781: jump (label ID:951)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 782: label ID:950*/
    /* PC 782: assignRational (ffreq, #const57)*/
    {{.ival=28}, {.ival=13}, {.ival=53}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 783: label ID:951*/
    /* PC 783: update (ffreq)*/
    {{.ival=56}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 784: label ID:952*/
    /* PC 784: compareIntegerEqual (uiState, 0, #const52, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 785: jumpNCF (label ID:955)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 786: compareRationalMore (fgain, 0, #const61, 0)*/
    {{.ival=35}, {.ival=21}, {.ival=0}, {.ival=57}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 787: jumpNCF (label ID:953)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 788: subRational (fgain, #const60, fgain)*/
    {{.ival=30}, {.ival=21}, {.ival=56}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 789: jump (label ID:954)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 790: label ID:953*/
    /* PC 790: assignRational (fgain, #const59)*/
    {{.ival=28}, {.ival=21}, {.ival=55}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 791: label ID:954*/
    /* PC 791: update (fgain)*/
    {{.ival=56}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 792: label ID:955*/
    /* PC 792: compareIntegerEqual (uiState, 0, #const54, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 793: jumpNCF (label ID:958)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 794: compareRationalMore (fquality, 0, #const60, 0)*/
    {{.ival=35}, {.ival=8}, {.ival=0}, {.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 795: jumpNCF (label ID:956)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 796: subRational (fquality, #const60, fquality)*/
    {{.ival=30}, {.ival=8}, {.ival=56}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 797: jump (label ID:957)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 798: label ID:956*/
    /* PC 798: assignRational (fquality, #const59)*/
    {{.ival=28}, {.ival=8}, {.ival=55}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 799: label ID:957*/
    /* PC 799: update (fquality)*/
    {{.ival=56}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 800: label ID:958*/
    /* PC 800: compareIntegerEqual (uiState, 0, #const47, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 801: jumpNCF (label ID:960)*/
    {{.ival=52}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 802: compareRationalMore (volume, 0, #const100 = "0.0"(rational), 0)*/
    {{.ival=35}, {.ival=11}, {.ival=0}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 803: jumpNCF (label ID:959)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 804: subRational (volume, #const60, volume)*/
    {{.ival=30}, {.ival=11}, {.ival=56}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 805: update (volume)*/
    {{.ival=56}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 806: label ID:959*/
    /* PC 806: label ID:960*/
    /* PC 806: compareIntegerEqual (uiState, 0, #const45, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 807: jumpNCF (label ID:963)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 808: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 809: jumpNCF (label ID:961)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 810: assignInteger (uiSel, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 811: jump (label ID:962)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 812: label ID:961*/
    /* PC 812: assignInteger (uiSel, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 813: label ID:962*/
    /* PC 813: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 814: label ID:963*/
    /* PC 814: compareIntegerEqual (uiState, 0, #const55, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 815: jumpNCF (label ID:966)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 816: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 817: jumpNCF (label ID:964)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 818: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 819: jump (label ID:965)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 820: label ID:964*/
    /* PC 820: assignInteger (uiSel, #const99 = "2"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 821: label ID:965*/
    /* PC 821: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 822: label ID:966*/
    /* PC 822: compareIntegerEqual (uiState, 0, #const56, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 823: jumpNCF (label ID:969)*/
    {{.ival=52}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 824: compareIntegerMore (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=41}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 825: jumpNCF (label ID:967)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 826: subInteger (uiSel, #const98 = "1"(integer), uiSel)*/
    {{.ival=23}, {.ival=10}, {.ival=29}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 827: jump (label ID:968)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 828: label ID:967*/
    /* PC 828: assignInteger (uiSel, #const99 = "2"(integer))*/
    {{.ival=21}, {.ival=10}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 829: label ID:968*/
    /* PC 829: update (uiSel)*/
    {{.ival=56}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 830: label ID:969*/
    /* PC 830: assignInteger (uiUpdate, #const98 = "1"(integer))*/
    {{.ival=21}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 831: update (uiUpdate)*/
    {{.ival=56}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 832: label ID:970*/
    /* PC 832: compareIntegerEqual (uiUpdate, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=0}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 833: jumpNCF (label ID:1030)*/
    {{.ival=52}, {.ival=173}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 834: compareIntegerEqual (uiState, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 835: jumpNCF (label ID:971)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 836: assignString (#fv_uiDisplay_headerText, 0, #const66, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=61}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 837: label ID:971*/
    /* PC 837: compareIntegerEqual (uiState, 0, #const42, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 838: jumpNCF (label ID:972)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 839: assignString (#fv_uiDisplay_headerText, 0, #const68, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=62}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 840: label ID:972*/
    /* PC 840: compareIntegerEqual (uiState, 0, #const44, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 841: jumpNCF (label ID:973)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 842: assignString (#fv_uiDisplay_headerText, 0, #const70, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=63}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 843: label ID:973*/
    /* PC 843: compareIntegerEqual (uiState, 0, #const48, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 844: jumpNCF (label ID:974)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 845: assignString (#fv_uiDisplay_headerText, 0, #const72, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=64}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 846: label ID:974*/
    /* PC 846: compareIntegerEqual (uiState, 0, #const49, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 847: jumpNCF (label ID:975)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 848: assignString (#fv_uiDisplay_headerText, 0, #const74, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=65}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 849: label ID:975*/
    /* PC 849: compareIntegerEqual (uiState, 0, #const50, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 850: jumpNCF (label ID:976)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 851: assignString (#fv_uiDisplay_headerText, 0, #const76, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=66}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 852: label ID:976*/
    /* PC 852: compareIntegerEqual (uiState, 0, #const52, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 853: jumpNCF (label ID:977)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 854: assignString (#fv_uiDisplay_headerText, 0, #const78, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=67}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 855: label ID:977*/
    /* PC 855: compareIntegerEqual (uiState, 0, #const54, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 856: jumpNCF (label ID:978)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 857: assignString (#fv_uiDisplay_headerText, 0, #const80, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=68}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 858: label ID:978*/
    /* PC 858: compareIntegerEqual (uiState, 0, #const47, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 859: jumpNCF (label ID:979)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 860: assignString (#fv_uiDisplay_headerText, 0, #const82, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=69}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 861: label ID:979*/
    /* PC 861: compareIntegerEqual (uiState, 0, #const45, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 862: jumpNCF (label ID:980)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 863: assignString (#fv_uiDisplay_headerText, 0, #const84, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=70}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 864: label ID:980*/
    /* PC 864: compareIntegerEqual (uiState, 0, #const55, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 865: jumpNCF (label ID:981)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 866: assignString (#fv_uiDisplay_headerText, 0, #const86, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=71}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 867: label ID:981*/
    /* PC 867: compareIntegerEqual (uiState, 0, #const56, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 868: jumpNCF (label ID:982)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 869: assignString (#fv_uiDisplay_headerText, 0, #const88, 0)*/
    {{.ival=10}, {.ival=37}, {.ival=0}, {.ival=72}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 870: label ID:982*/
    /* PC 870: compareIntegerEqual (uiState, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 871: jumpNCF (label ID:983)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 872: assignString (#fv_uiDisplay_selText, 0, #const2, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=74}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 873: label ID:983*/
    /* PC 873: compareIntegerEqual (uiState, 0, #const42, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=41}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 874: jumpNCF (label ID:989)*/
    {{.ival=52}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 875: compareIntegerEqual (uiMenuSel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=19}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 876: jumpNCF (label ID:984)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 877: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 878: jump (label ID:985)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 879: label ID:984*/
    /* PC 879: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 880: label ID:985*/
    /* PC 880: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 881: jumpNCF (label ID:986)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 882: concatStrings (#fv_uiDisplay_selText, 0, #const70, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=63}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 883: label ID:986*/
    /* PC 883: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 884: jumpNCF (label ID:987)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 885: concatStrings (#fv_uiDisplay_selText, 0, #const84, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=70}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 886: label ID:987*/
    /* PC 886: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 887: jumpNCF (label ID:988)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 888: concatStrings (#fv_uiDisplay_selText, 0, #const82, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=69}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 889: label ID:988*/
    /* PC 889: label ID:989*/
    /* PC 889: compareIntegerEqual (uiState, 0, #const44, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=42}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 890: jumpNCF (label ID:996)*/
    {{.ival=52}, {.ival=18}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 891: compareIntegerEqual (uiFilterBankSel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=7}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 892: jumpNCF (label ID:990)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 893: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 894: jump (label ID:991)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 895: label ID:990*/
    /* PC 895: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 896: label ID:991*/
    /* PC 896: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 897: jumpNCF (label ID:992)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 898: concatStrings (#fv_uiDisplay_selText, 0, #const12, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=77}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 899: label ID:992*/
    /* PC 899: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 900: jumpNCF (label ID:993)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 901: concatStrings (#fv_uiDisplay_selText, 0, #const13, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=78}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 902: label ID:993*/
    /* PC 902: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 903: jumpNCF (label ID:994)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 904: concatStrings (#fv_uiDisplay_selText, 0, #const14, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=79}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 905: label ID:994*/
    /* PC 905: compareIntegerEqual (uiSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 906: jumpNCF (label ID:995)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 907: concatStrings (#fv_uiDisplay_selText, 0, #const16, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=80}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 908: label ID:995*/
    /* PC 908: label ID:996*/
    /* PC 908: compareIntegerEqual (uiState, 0, #const48, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=45}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 909: jumpNCF (label ID:999)*/
    {{.ival=52}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 910: compareIntegerEqual (uiFilterIndex, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=2}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 911: jumpNCF (label ID:997)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 912: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 913: jump (label ID:998)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 914: label ID:997*/
    /* PC 914: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 915: label ID:998*/
    /* PC 915: concatStrings (#fv_uiDisplay_selText, 0, #const18, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=81}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 916: integerToString (#fv_uiDisplay_#fv_getSelText_valToStr, 0, uiSel, 0)*/
    {{.ival=9}, {.ival=73}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 917: concatStrings (#fv_uiDisplay_selText, 0, #fv_uiDisplay_#fv_getSelText_valToStr, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=73}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 918: label ID:999*/
    /* PC 918: compareIntegerEqual (uiState, 0, #const49, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=46}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 919: jumpNCF (label ID:1008)*/
    {{.ival=52}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 920: compareIntegerEqual (uiFilterTypeSel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=1}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 921: jumpNCF (label ID:1000)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 922: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 923: jump (label ID:1001)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 924: label ID:1000*/
    /* PC 924: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 925: label ID:1001*/
    /* PC 925: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 926: jumpNCF (label ID:1002)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 927: concatStrings (#fv_uiDisplay_selText, 0, #const20, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=82}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 928: label ID:1002*/
    /* PC 928: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 929: jumpNCF (label ID:1003)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 930: concatStrings (#fv_uiDisplay_selText, 0, #const21, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=83}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 931: label ID:1003*/
    /* PC 931: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 932: jumpNCF (label ID:1004)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 933: concatStrings (#fv_uiDisplay_selText, 0, #const22, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=84}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 934: label ID:1004*/
    /* PC 934: compareIntegerEqual (uiSel, 0, #const102 = "3"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=33}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 935: jumpNCF (label ID:1005)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 936: concatStrings (#fv_uiDisplay_selText, 0, #const23, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=85}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 937: label ID:1005*/
    /* PC 937: compareIntegerEqual (uiSel, 0, #const95, 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=60}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 938: jumpNCF (label ID:1006)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 939: concatStrings (#fv_uiDisplay_selText, 0, #const25, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=86}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 940: label ID:1006*/
    /* PC 940: compareIntegerEqual (uiSel, 0, #const53, 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=49}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 941: jumpNCF (label ID:1007)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 942: concatStrings (#fv_uiDisplay_selText, 0, #const27, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=87}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 943: label ID:1007*/
    /* PC 943: label ID:1008*/
    /* PC 943: compareIntegerEqual (uiState, 0, #const50, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=47}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 944: jumpNCF (label ID:1009)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 945: rationalToString (#fv_uiDisplay_selText, 0, ffreq, 0)*/
    {{.ival=8}, {.ival=39}, {.ival=0}, {.ival=13}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 946: concatStrings (#fv_uiDisplay_selText, 0, #const29, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=88}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 947: label ID:1009*/
    /* PC 947: compareIntegerEqual (uiState, 0, #const52, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=48}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 948: jumpNCF (label ID:1010)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 949: rationalToString (#fv_uiDisplay_selText, 0, fgain, 0)*/
    {{.ival=8}, {.ival=39}, {.ival=0}, {.ival=21}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 950: label ID:1010*/
    /* PC 950: compareIntegerEqual (uiState, 0, #const54, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=50}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 951: jumpNCF (label ID:1011)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 952: rationalToString (#fv_uiDisplay_selText, 0, fquality, 0)*/
    {{.ival=8}, {.ival=39}, {.ival=0}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 953: label ID:1011*/
    /* PC 953: compareIntegerEqual (uiState, 0, #const47, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=44}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 954: jumpNCF (label ID:1012)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 955: rationalToString (#fv_uiDisplay_selText, 0, volume, 0)*/
    {{.ival=8}, {.ival=39}, {.ival=0}, {.ival=11}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 956: label ID:1012*/
    /* PC 956: compareIntegerEqual (uiState, 0, #const45, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=43}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 957: jumpNCF (label ID:1017)*/
    {{.ival=52}, {.ival=12}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 958: compareIntegerEqual (uiSelChannel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=22}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 959: jumpNCF (label ID:1013)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 960: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 961: jump (label ID:1014)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 962: label ID:1013*/
    /* PC 962: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 963: label ID:1014*/
    /* PC 963: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 964: jumpNCF (label ID:1015)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 965: concatStrings (#fv_uiDisplay_selText, 0, #const12, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=77}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 966: label ID:1015*/
    /* PC 966: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 967: jumpNCF (label ID:1016)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 968: concatStrings (#fv_uiDisplay_selText, 0, #const13, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=78}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 969: label ID:1016*/
    /* PC 969: label ID:1017*/
    /* PC 969: compareIntegerEqual (uiState, 0, #const55, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=51}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 970: jumpNCF (label ID:1023)*/
    {{.ival=52}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 971: compareIntegerEqual (uiSelChannel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=22}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 972: jumpNCF (label ID:1018)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 973: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 974: jump (label ID:1019)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 975: label ID:1018*/
    /* PC 975: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 976: label ID:1019*/
    /* PC 976: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 977: jumpNCF (label ID:1020)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 978: concatStrings (#fv_uiDisplay_selText, 0, #const14, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=79}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 979: label ID:1020*/
    /* PC 979: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 980: jumpNCF (label ID:1021)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 981: concatStrings (#fv_uiDisplay_selText, 0, #const16, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=80}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 982: label ID:1021*/
    /* PC 982: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 983: jumpNCF (label ID:1022)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 984: concatStrings (#fv_uiDisplay_selText, 0, #const35, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=89}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 985: label ID:1022*/
    /* PC 985: label ID:1023*/
    /* PC 985: compareIntegerEqual (uiState, 0, #const56, 0)*/
    {{.ival=42}, {.ival=23}, {.ival=0}, {.ival=52}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 986: jumpNCF (label ID:1029)*/
    {{.ival=52}, {.ival=15}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 987: compareIntegerEqual (uiSelChannel, 0, uiSel, 0)*/
    {{.ival=42}, {.ival=22}, {.ival=0}, {.ival=10}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 988: jumpNCF (label ID:1024)*/
    {{.ival=52}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 989: assignString (#fv_uiDisplay_selText, 0, #const4, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=75}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 990: jump (label ID:1025)*/
    {{.ival=50}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 991: label ID:1024*/
    /* PC 991: assignString (#fv_uiDisplay_selText, 0, #const5, 0)*/
    {{.ival=10}, {.ival=39}, {.ival=0}, {.ival=76}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 992: label ID:1025*/
    /* PC 992: compareIntegerEqual (uiSel, 0, #const97 = "0"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 993: jumpNCF (label ID:1026)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 994: concatStrings (#fv_uiDisplay_selText, 0, #const14, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=79}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 995: label ID:1026*/
    /* PC 995: compareIntegerEqual (uiSel, 0, #const98 = "1"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 996: jumpNCF (label ID:1027)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 997: concatStrings (#fv_uiDisplay_selText, 0, #const16, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=80}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 998: label ID:1027*/
    /* PC 998: compareIntegerEqual (uiSel, 0, #const99 = "2"(integer), 0)*/
    {{.ival=42}, {.ival=10}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 999: jumpNCF (label ID:1028)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1000: concatStrings (#fv_uiDisplay_selText, 0, #const35, 0)*/
    {{.ival=7}, {.ival=39}, {.ival=0}, {.ival=89}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1001: label ID:1028*/
    /* PC 1001: label ID:1029*/
    /* PC 1001: assignString (#fv_uiDisplay_dispText, 0, #fv_uiDisplay_headerText, 0)*/
    {{.ival=10}, {.ival=38}, {.ival=0}, {.ival=37}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1002: concatStrings (#fv_uiDisplay_dispText, 0, #const64, 0)*/
    {{.ival=7}, {.ival=38}, {.ival=0}, {.ival=59}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1003: concatStrings (#fv_uiDisplay_dispText, 0, #fv_uiDisplay_selText, 0)*/
    {{.ival=7}, {.ival=38}, {.ival=0}, {.ival=39}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1004: uiSetDisplay (d, 0, #fv_uiDisplay_dispText, 0)*/
    {{.ival=212}, {.ival=15}, {.ival=0}, {.ival=38}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1005: assignInteger (uiUpdate, #const97 = "0"(integer))*/
    {{.ival=21}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1006: label ID:1030*/
    /* PC 1006: readSampleFrame (0, inL, 1)*/
    {{.ival=62}, {.ival=0}, {.ival=24}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1007: readSampleFrame (1, inR, 0)*/
    {{.ival=62}, {.ival=1}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1008: convoluteBiquad (inL, LinFilter, inL)*/
    {{.ival=110}, {.ival=24}, {.ival=18}, {.ival=24}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1009: convoluteBiquad (inR, RinFilter, inR)*/
    {{.ival=110}, {.ival=27}, {.ival=5}, {.ival=27}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1010: compareIntegerEqual (LoutInpSel, 0, #const97, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1011: jumpNCF (label ID:211)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1012: convoluteBiquad (inL, LoutFilter, outL)*/
    {{.ival=110}, {.ival=24}, {.ival=3}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1013: label ID:211*/
    /* PC 1013: compareIntegerEqual (LoutInpSel, 0, #const98, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1014: jumpNCF (label ID:212)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1015: convoluteBiquad (inR, LoutFilter, outL)*/
    {{.ival=110}, {.ival=27}, {.ival=3}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1016: label ID:212*/
    /* PC 1016: compareIntegerEqual (LoutInpSel, 0, #const99, 0)*/
    {{.ival=42}, {.ival=14}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1017: jumpNCF (label ID:213)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1018: assignRational (outL, #const100)*/
    {{.ival=28}, {.ival=26}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1019: label ID:213*/
    /* PC 1019: compareIntegerEqual (RoutInpSel, 0, #const97, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=28}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1020: jumpNCF (label ID:214)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1021: convoluteBiquad (inL, RoutFilter, outR)*/
    {{.ival=110}, {.ival=24}, {.ival=12}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1022: label ID:214*/
    /* PC 1022: compareIntegerEqual (RoutInpSel, 0, #const98, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=29}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1023: jumpNCF (label ID:215)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1024: convoluteBiquad (inR, RoutFilter, outR)*/
    {{.ival=110}, {.ival=27}, {.ival=12}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1025: label ID:215*/
    /* PC 1025: compareIntegerEqual (RoutInpSel, 0, #const99, 0)*/
    {{.ival=42}, {.ival=4}, {.ival=0}, {.ival=30}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1026: jumpNCF (label ID:216)*/
    {{.ival=52}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1027: assignRational (outR, #const100)*/
    {{.ival=28}, {.ival=25}, {.ival=31}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1028: label ID:216*/
    /* PC 1028: mulRational (outL, volume, outL)*/
    {{.ival=31}, {.ival=26}, {.ival=11}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1029: mulRational (outR, volume, outR)*/
    {{.ival=31}, {.ival=25}, {.ival=11}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1030: writeSampleFrame (0, outL)*/
    {{.ival=63}, {.ival=0}, {.ival=26}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1031: writeSampleFrame (1, outR)*/
    {{.ival=63}, {.ival=1}, {.ival=25}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1032: jump (label ID:217)*/
    {{.ival=50}, {.ival=-917}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

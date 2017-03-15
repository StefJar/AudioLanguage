// audio language code file
// generated 2015-04-16 16:08:51

#include "ALstringTest.h"

//! list containing the variables
const TALCvar gALCvars [3] = {
    //0: name="s2" type="string" amount=1 
    {.type=3,.amount=1},
    //1: name="s1" type="string" amount=1 
    {.type=3,.amount=1},
    //2: name="#const1" type="string" amount=1 
    {.type=3,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[7] = {
    /* PC 0: setStringSize (#const1, 0, 54)*/
    {{.ival=5}, {.ival=2}, {.ival=0}, {.ival=54}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 1: setStringValues (#const1, 0, 0, 1819043144, 1750343791, 1763734377, 543236211)*/
    {{.ival=6}, {.ival=2}, {.ival=0}, {.ival=0}, {.rawVal=1819043144}, {.rawVal=1750343791}, {.rawVal=1763734377}, {.rawVal=543236211}},
    /* PC 2: setStringValues (#const1, 0, 16, 1818322290, 1869357177, 1931503470, 1852404340)*/
    {{.ival=6}, {.ival=2}, {.ival=0}, {.ival=16}, {.rawVal=1818322290}, {.rawVal=1869357177}, {.rawVal=1931503470}, {.rawVal=1852404340}},
    /* PC 3: setStringValues (#const1, 0, 32, 1769414759, 1629513844, 1953459308, 543584032)*/
    {{.ival=6}, {.ival=2}, {.ival=0}, {.ival=32}, {.rawVal=1769414759}, {.rawVal=1629513844}, {.rawVal=1953459308}, {.rawVal=543584032}},
    /* PC 4: setStringValues (#const1, 0, 48, 1918986339, 538976627, 538976288, 538976288)*/
    {{.ival=6}, {.ival=2}, {.ival=0}, {.ival=48}, {.rawVal=1918986339}, {.rawVal=538976627}, {.rawVal=538976288}, {.rawVal=538976288}},
    /* PC 5: assignString (s1, 0, #const1, 0)*/
    {{.ival=10}, {.ival=1}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 6: assignString (s2, 0, s1, 0)*/
    {{.ival=10}, {.ival=0}, {.ival=0}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

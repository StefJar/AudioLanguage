// audio language code file
// generated 2015-06-24 14:10:05

#include "simple.h"

//! list containing the variables
const TALCvar gALCvars [3] = {
    //0: name="y" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //1: name="x" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //2: name="#const1" type="rational" amount=1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[5] = {
    /* PC 0: assignConstRational (#const1, 0, 1, 2.0)*/
    {{.ival=27}, {.ival=2}, {.ival=0}, {.ival=1}, {.fval=2.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 1: label ID:2*/
    /* PC 1: readSampleFrame (0, x, 1)*/
    {{.ival=62}, {.ival=0}, {.ival=1}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 2: mulRational (x, #const1, y)*/
    {{.ival=31}, {.ival=1}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 3: writeSampleFrame (0, y)*/
    {{.ival=63}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 4: jump (label ID:2)*/
    {{.ival=50}, {.ival=-3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

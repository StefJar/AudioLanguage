// audio language code file
// generated 2015-03-27 16:17:11

#include "RPi_DSP.h"

//! list containing the variables
const TALCvar gALCvars [10] = {
    //0: name="bqf1" type="biquad" amount=2 
    {.type=10,.amount=2},
    //1: name="bqf2" type="biquad" amount=2 
    {.type=10,.amount=2},
    //2: name="out1" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //3: name="out2" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //4: name="fs" type="rational" amount=1 
    {.type=1,.amount=1},
    //5: name="f" type="rational" amount=1 
    {.type=1,.amount=1},
    //6: name="in1" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //7: name="in2" type="rational" amount=1024 
    {.type=1,.amount=1024},
    //8: name="#const9" type="rational" amount=1 
    {.type=1,.amount=1},
    //9: name="#const10" type="rational" amount=1 
    {.type=1,.amount=1}
};
//! list containing the instructions
const TALCinstr gcInstructions[15] = {
    /* PC 0: assignConstRational (#const9, 0, 1, 44100.0)*/
    {{.ival=27}, {.ival=8}, {.ival=0}, {.ival=1}, {.fval=44100.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 1: assignConstRational (#const10, 0, 1, 1000.0)*/
    {{.ival=27}, {.ival=9}, {.ival=0}, {.ival=1}, {.fval=1000.0}, {.fval=0}, {.fval=0}, {.fval=0}},
    /* PC 2: assignRational (fs, #const9)*/
    {{.ival=28}, {.ival=4}, {.ival=8}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 3: assignRational (f, #const10)*/
    {{.ival=28}, {.ival=5}, {.ival=9}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 4: initBiquadAsLP (bqf1, 0, fs, f)*/
    {{.ival=101}, {.ival=0}, {.ival=0}, {.ival=4}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 5: initBiquadAsLP (bqf1, 1, fs, f)*/
    {{.ival=101}, {.ival=0}, {.ival=1}, {.ival=4}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 6: initBiquadAsHP (bqf2, 0, fs, f)*/
    {{.ival=100}, {.ival=1}, {.ival=0}, {.ival=4}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 7: initBiquadAsHP (bqf2, 1, fs, f)*/
    {{.ival=100}, {.ival=1}, {.ival=1}, {.ival=4}, {.ival=5}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 8: label ID:6*/
    /* PC 8: readSampleFrame (0, in1, 1)*/
    {{.ival=62}, {.ival=0}, {.ival=6}, {.ival=1}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 9: readSampleFrame (1, in2, 0)*/
    {{.ival=62}, {.ival=1}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 10: convoluteBiquad (out1, bqf1, in1)*/
    {{.ival=110}, {.ival=2}, {.ival=0}, {.ival=6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 11: convoluteBiquad (out2, bqf2, in2)*/
    {{.ival=110}, {.ival=3}, {.ival=1}, {.ival=7}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 12: writeSampleFrame (0, out1)*/
    {{.ival=63}, {.ival=0}, {.ival=2}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 13: writeSampleFrame (0, out2)*/
    {{.ival=63}, {.ival=0}, {.ival=3}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
    /* PC 14: jump (label ID:6)*/
    {{.ival=50}, {.ival=-6}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}, {.ival=0}},
};

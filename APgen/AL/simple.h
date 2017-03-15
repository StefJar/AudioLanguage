 // audio language code file
// generated 2015-06-24 14:10:05

#include <stdint.h>

// a type for the audio language code variable
typedef struct SALCvar {
    int32_t    type;      //!< variable type
    int32_t    amount;    //!< amount of elements at the vector
} TALCvar;

// the type for the audio language code instruction
typedef union UALCinstructionParameter {
    int32_t    ival;    //!< integer value
    float      fval;    //!< floating point value
    uint32_t   rawVal;  //!< raw value
} TALCinstr [8];

// some global variables

//! amount of variables
#define dALCdumpVarCount (3)

//! amount of instructions
#define dALCdumpInstrCount (5)

//! size of one instruction
#define dALCdumpInstrSize (8)

//! list containing the variables
extern const TALCvar gALCvars [3];

//! list containing the instructions
extern const TALCinstr gcInstructions[5];

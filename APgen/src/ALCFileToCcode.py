'''
Created on 23.02.2012

@author: StJ

@descr: converts a AL binary file to C code 
'''

import argparse
import sys
import os
import ctypes
import struct
import array
import time
import copy

# for arrays

import APDB
import codeGen

def loadALCFile (iFileName):
    f = open(iFileName, 'rb')
    if (f == None):
        sys.exit('can not open input file')

    # read header
    # part 1 ID's and endianes
    binHeaderStruct = struct.Struct('=5c') 
    data = f.read(binHeaderStruct.size)
    idALC0,idALC1,idALC2,idALC3, endianFlag = binHeaderStruct.unpack(data)
    if endianFlag == 'l':
        ef = '<'
    elif endianFlag != 'b':
        ef = '>'
    else:
        sys.exit('unknown endian format at the ALC file')
    
    binHeaderStruct = struct.Struct(ef+'3i')    
    data = f.read(binHeaderStruct.size)
    varCount, instrCount, instrSize = binHeaderStruct.unpack(data)
    dbInstrParamCount = db.HAL_DefFunctions_maxParamCount()
    if ((instrSize-1) != (dbInstrParamCount)):
        sys.exit('instruction size of the file is not equal to the size defined at the database')
    
#    varStruct = struct.Struct(ef+str(varCount*2)+'i')
#    data = f.read(varStruct.size)
#    varList = varStruct.unpack(data)
    varStruct = struct.Struct(ef+'2i')
    varList = []
    for i in range(0,varCount):
        data = f.read(varStruct.size)
        varList.append(varStruct.unpack(data))
    
    instrList = []
    for i in range(0,instrCount):
        instrParamL = []
        for j in range(dbInstrParamCount+1):
            instrParamL.append(f.read(4))
        instrList.append(instrParamL)

    f.close()
    return ef, instrSize, varList, instrList  

class ALbinCodeToCconverter (object):
    def __init__(self):
        pass
    
    def genHeaderFileText (self, paramsAmmount,amountOfVariables,amountOfInstructions):
        pass

    def genCFileText (self, headerFile, vL, iL, endianFlag):
        pass
    
class ALbinToCbinaryConv (ALbinCodeToCconverter):
    def __init__(self):
        pass

    def genHeaderFileText (self, paramsAmmount,amountOfVariables,amountOfInstructions):
        return """ // audio language code file
// generated {timeStmp}

#include <stdint.h>

// a type for the audio language code variable
typedef struct SALCvar {{
    int32_t    type;      //!< variable type
    int32_t    amount;    //!< amount of elements at the vector
}} TALCvar;

// the type for the audio language code instruction
typedef union UALCinstructionParameter {{
    int32_t    ival;    //!< integer value
    float      fval;    //!< floating point value
    uint32_t   rawVal;  //!< raw value
}} TALCinstr [{paramsAmmount}];

// some global variables

//! amount of variables
#define dALCdumpVarCount ({amountOfVariables})

//! amount of instructions
#define dALCdumpInstrCount ({amountOfInstructions})

//! size of one instruction
#define dALCdumpInstrSize ({paramsAmmount})

//! list containing the variables
extern const TALCvar gALCvars [{amountOfVariables}];

//! list containing the instructions
extern const TALCinstr gcInstructions[{amountOfInstructions}];
""".format(
           timeStmp=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
           paramsAmmount=paramsAmmount,
           amountOfVariables=amountOfVariables,
           amountOfInstructions=amountOfInstructions
           )

    def genParamToValueMapping (self):
        resDict = {
                   (db.dFuncClass_refVar, None) : 'ival',
                   (db.dFuncClass_refDataVar, None): 'ival',
                   (db.dFuncClass_VarID, None): 'ival',
                   (db.dFuncClass_VarIndex, None): 'ival',
                   }
        btL = db.HAL_basicIOTypes_getList()
        cTypeToVarDict = {
                          'float' : 'fval',
                          'int'   : 'ival',
                          'int32_t': 'ival',
                          'char' : 'rawVal',
                          'uint32_t' : 'rawVal'
        }
        for bt in btL:
            resDict[(db.dFuncClass_basicIOtype, bt[1])] =  cTypeToVarDict.get(bt[4], 'unknown c type({unt})'.format(unt=bt[4]))
        return resDict
    
    def genCFileText (self, headerFile, vL, iL, endianFlag):
    
        cT = """// audio language code file
// generated {timeStmp}

#include "{headerFile}"

//! list containing the variables
const TALCvar gALCvars [{amountOfVariables}] = {{
""".format(
           timeStmp=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
           headerFile=headerFile,
           amountOfVariables=len(vL)
           )
        i = 0
        for vType,vAmount in vL:
            vInfo, vParams = db.HAL_VariableDefinition_getByVariableID(vType)
            if i <> 0:
                cT += ',\n'
            cT += """    //VarIndx:{indx} type: {vname} amount: {vAmount} 
    {{.type={varType},.amount={vAmount}}}""".format(indx=i, vname=vInfo[2], varType=vType, vAmount=vAmount)
            i += 1
        cT += "\n};"        
    
        # build translation structure for instruction values
        pMapL = self.genParamToValueMapping()
        ParamMax = db.HAL_DefFunctions_maxParamCount()
        ParamMax += 1
    
        formatDict = {
            'ival': 'i',
            'fval': 'f',
            'rawVal': 'I'
        }

        transHALfL = {}
        
        dbHalFL = db.HAL_DefFunctions_getList()
            
        for dbHalF in dbHalFL:
            pL = db.HAL_DefFunctions_getParamList(dbHalF[1])
            # lets start with the function id
            npL = ['ival']
            i = 0
            for p in pL:
                i += 1
                mV = pMapL.get((p[4],p[5]),None)
                if mV is None:
                    mV = pMapL.get((p[4],None),None)
                if mV is None:
                    sys.exit('can not map parameter {index} of {halF}'.format(index=i, halF=dbHalF[2]))
                npL.append(mV)
    
            while i < (ParamMax-1):
                npL.append('ival')
                i += 1
            packStr = ''
            for p in npL:
                packStr += formatDict[p]
            
            transHALfL[dbHalF[1]] = (dbHalF[2],npL,packStr)
        # build instruction table
        cT += """
//! list containing the instructions
const TALCinstr gcInstructions[{amountOfInstructions}] = {{
""".format(amountOfInstructions=len(iL))
        i = 0
        for instr in iL:
            i += 1
            fid = struct.unpack(endianFlag+'i',instr[0])[0]
            transL = transHALfL.get(fid, None)
            if transL is None:
                sys.exit('function id {fid} of the {i}th instruction is not defined at the HAL'.format(fid=fid, i=i))
            # ok lets translate
            instrName, pL,packStr = transL
            j = 0
            cT += '\t//PC:{i} {instrName}\n\t{{'.format(i=i,instrName=instrName)
            for j in range(len(instr)):
                val = struct.unpack(endianFlag+packStr[j],instr[j])[0]
                cT += '{{.{subVal}={val}}},'.format(subVal=pL[j],val=val)
            cT += '\t},\n' 
                     
        cT += "};\n"
        return cT
    
class ALbinCodeToCfunction (object):
    def __init__(self, db, callsTillMessageSystemCheck=None):
        hfL = db.HAL_DefFunctions_getList()
        hvL = db.HAL_VariableDefinition_getList()
        if isinstance(callsTillMessageSystemCheck, str):
            self.callsTillMessageSystemCheck = int(callsTillMessageSystemCheck)
        elif isinstance(callsTillMessageSystemCheck, int):
            self.callsTillMessageSystemCheck = callsTillMessageSystemCheck
        else:
            self.callsTillMessageSystemCheck = None
        self.cg =  codeGen.codeGenerator(db, '')
        self.db = db
        
        # HAL functions
        (fHeaderDef, pIPcpu, pParam) = self.cg.getHALFunctionParameterDef()
        # key = HAL fid
        # data = function declaration, function name, parms struct, 
        self.hfD = {}
        for hf in hfL:
            fname = self.cg.getFunctionNameFromFIDandName(hf[1], hf[2])
            pInfo = []
            fparamsL = db.HAL_DefFunctions_getParamList(hf[1])
            for fparam in fparamsL:  
                paramClass = fparam[4]
                paramTypeID = fparam[5]
                pInfo.append((paramClass, paramTypeID))
            
            self.hfD[hf[1]] = ('extern void {fname} ({fHeaderDef});'.format(fname=fname, fHeaderDef=fHeaderDef), fname, copy.copy(pInfo))

        
        
    def genHeaderFileText (self, paramsAmmount,amountOfVariables,amountOfInstructions):
        return """// audio language code file
// generated {timeStmp}

#include "AP.h"

// inits the variables of the program
int ALprogram_initVars ();

// inits and prepares the instructions of the program 
void ALprogram_prepareInstructions ();

// executes the program
int ALprogram_executeProgram (void *pAP);
""".format(timeStmp=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()))

    def genCFileText (self, headerFile, vL, iL, endianFlag):
        varAmount = len(vL)
        
        # build an list containing the HALid with the jump commands
        jumpHALIDs = {
            50 : 'jump',
            51 : 'jumpCF',
            52 : 'jumpNCF'
        }
                
        cT = """// audio language code file
// generated {timeStmp}

#include "{headerFile}"
#include "AP.h"
""".format(timeStmp=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),headerFile=headerFile)

        # some forward declarations 
        
        cT += '// forward declaration of the HAL functions\n'
        for (fid, (extDecl, HALfidName, fParams)) in sorted(self.hfD.items(), key=lambda x: x[0]):
            cT += extDecl + '\n'
        
        # build variable list
        cT += '\n// the list with the variables (not initialized)\n'
        cT += "TAPInterpreterVariable gVars [{varCount}] = {{".format(varCount=varAmount)
        i = 0
        for v in vL:
            cT += '\n\t// index {i}\n\t{{.pVI=NULL, .pData=NULL}},'.format(i=i)
            i += 1
        cT +='\n};\n'
        
        # lets build the code
        cT += '\n// function which inits the vars\n'
        cT  += """int ALprogram_initVars () {{
""".format(varAmount=varAmount)
        i = 0
        for vType, vAmount in vL:
            cT += """    // index {i} is initialized
    gVars[{i}].pVI = HALfindVar({vType});
    if (!gVars[{i}].pVI) return -100 - {i};
    gVars[{i}].pData = pV->pFkt_create({vAmount});
    if (!gVars[{i}].pData) return -1000 - {i};
""".format(i=i,vType=vType,vAmount=vAmount)
            i += 1
        
        cT += '\treturn 0;\n\t}\n'
        
        #build the program first as list, resolve the jump comments
        
        # decoding structs
        instrRead_HALfid = struct.Struct(endianFlag+'i')
        instrRead_index = struct.Struct(endianFlag+'i')
        
        # basic var decode dict
        # key = type id
        # data = c text, endianess, python type
        basicParamDict = {
            1 : ('fp_rational',struct.Struct('f')),
            2 : ('fp_integer',struct.Struct(endianFlag+'i')),
            3 : ('fp_char',struct.Struct('i')),
            4 : ('fp_raw',struct.Struct('i'))
        }
        
        # key = class
        # data = c text, ref to variable, call function of the variable 
        classTypeDict = {
            self.db.dFuncClass_refVar   : ('fp_pV', True, None),
            self.db.dFuncClass_refDataVar  : ('fp_pD', True, 'pFkt_decodeData'),
            self.db.dFuncClass_VarID       : ('fp_VarID', False, None),
            self.db.dFuncClass_VarIndex    : ('fp_VarIndex', False, None),
            self.db.dFuncClass_basicIOtype : None
        }

        # new instruction list
        # item = [label, cfunction call]
        iLn = []
        # ok lets create a set of empty lists
        for i in range(0,len(iL)):
            iLn.append([[], None])

        
        prepateInstrCcode = ''
        labelCounter = 1
        
        # jump calls replacements
        jumpHALfuncReplacements = {
            50: '',
            51: 'if (IPcpu->CF) ',
            52: 'if (!IPcpu->CF) ',
            }

        
        i = 0
        j = 0
        cT += '\n// create parameter lists for the calls\n'
        for instr in iL:
            HALfid = instrRead_HALfid.unpack(instr[0])[0]
            handler = jumpHALIDs.get(HALfid)
            if handler is None:
                # no jump
                (extHalFCdecl, cHALf, HALfParams) = self.hfD[HALfid]
                cT += '\n//parameter for instruction {i}\nTuAPInterpreterFunctionParameter instrParamL_{i} [{amount}];\n'.format(i=i, amount=len(HALfParams))
                prepateInstrCcode += '\n//parameter for instruction {i} ({instrName})\n'.format(i=i, instrName=cHALf)
                j = 1
                for paramClass, paramTypeID in HALfParams:
                    if j > 1:
                        prepateInstrCcode += '\n'
                    prepateInstrCcode += '\tinstrParamL_{i}[{indx}].'.format(i=i, indx=(j-1))
                    handler = classTypeDict.get(paramClass, None)
                    if handler is not None:
                        (cText, refVar, callFunc) = handler
                        indx = instrRead_index.unpack(instr[j])[0]
                        prepateInstrCcode += '{cText} = '.format(cText=cText)
                        if refVar is None:
                            prepateInstrCcode += str(indx)
                        else:
                            prepateInstrCcode += 'gVar[{indx}]'.format(indx=indx)
                        if callFunc is not None:
                            prepateInstrCcode += '.pVI->{callFunc}(gVar[{indx}].pData)'.format(callFunc=callFunc, indx=indx)
                    else:
                        handler = basicParamDict.get(paramTypeID, None)
                        if handler is None:
                            print 'error'
                            return ''
                        else:
                            (cText, decoder) = handler
                            prepateInstrCcode += '{cText} = {val}'.format(cText=cText, val=decoder.unpack(instr[j])[0])
                    prepateInstrCcode += ';' 
                    j += 1
                iLn[i][1] = '{cHALf}(&IPcpu, instrParamL_{i});'.format(cHALf=cHALf,i=i)
            else:
                # jump
                cT += '\n//parameter for instruction({handler}) {i} are skipped and replaced by gotos\n'.format(handler=handler, i=i)
                label = 'label_{labelCounter}'.format(labelCounter=labelCounter)
                labelCounter += 1
                IPdelta = instrRead_index.unpack(instr[1])[0]
                iLn[i][1] = '{prefix}goto {label};'.format(prefix=jumpHALfuncReplacements.get(HALfid),label=label)
                iLn[i+IPdelta][0].append(label)
            i += 1


        
        # dump the peparation for the instructions into a function
        cT += '\n// prepares the instructions of a program\n void ALprogram_prepareInstructions () {{\n{code}\n}}\n'.format(code=prepateInstrCcode)
        
        # dump the instructions into a function
        i = 0
        cT += '\n// executes the program\n int ALprogram_executeProgram (void *pAP) {\n'
        cT += '\tTAPInterpreterCPU IPcpu = {NULL, 0, 0, NULL, NULL};\n\n'
        
        for instr in iLn:
            if instr is not None:
                labelL, call = instr
                for label in labelL:
                    cT += '{label}:\n'.format(label=label)
                if call is not None:
                    cT += '\t{call}'.format(call=call)
                cT += '\n'
            
            if i == self.callsTillMessageSystemCheck:
                cT += '\tAPMessageProcess(pAP);\n'
                i = 0
            else:
                i += 1
        cT += '\n\treturn 0;\n}\n'
        
        return cT


def main(argv):
    parser = argparse.ArgumentParser(description='the audio language code to C code converter')
    parser.add_argument('-i', help='the audio language code input file')
    parser.add_argument('-o', help='the C code output file')
    parser.add_argument('-b', help='if b is set a binary output is generated ', default=False, action='store_const', const=True)
    parser.add_argument('-a', help='if a is set, it stands for the amount of instructions executed before checking the message system for new messages (only necessary if -b paramter is not set)', default=None)
    args = parser.parse_args()
    return (args.i, args.o, args.b, args.a)

if __name__ == '__main__':    
    # setup db connection
    db = APDB.APDB('APdbCreate.sql','dbInit.xml')

    # file work
    (iFileName, oFileName, binFlag, messageSystemInstrCount) = main(sys.argv[1:])
    oFileName = os.path.splitext(oFileName)[0]
    
    hFileName = oFileName + '.h'
    cFileName = oFileName + '.c'

    if binFlag is True:
        converter = ALbinToCbinaryConv()
    else:
        if messageSystemInstrCount is None:
            sys.exit('the -a parameter is missing')
        converter = ALbinCodeToCfunction(db, int(messageSystemInstrCount))

    print ('convert "{iFileName}" to "{hFileName}" and "{cFileName}" ...'.format(iFileName=iFileName,hFileName=hFileName,cFileName=cFileName))

    # read file
    endianFlag, instructionParamAmount, vL, iL = loadALCFile(iFileName)
    
    amountOfVariables = len(vL)
    amountOfInstructions = len(iL)
        
    # open header file
    f = open(hFileName, 'wb')
    if (f == None):
        sys.exit('can not create header output file')
    f.write(converter.genHeaderFileText(instructionParamAmount, amountOfVariables, amountOfInstructions))
    f.close()
    
    p, hFileN = os.path.split(hFileName)
    # open header file
    f = open(cFileName, 'wb')
    if (f == None):
        sys.exit('can not create c output file')
    f.write(converter.genCFileText(hFileN,vL, iL, endianFlag))
    f.close()
    
    print('finished!')
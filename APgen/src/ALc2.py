'''
Created on 20.08.2013

@author: StJ
'''
import argparse
import sys
import os
import ply.lex as lex
import ply.yacc as yacc
import ctypes
import struct

import re
import copy
import subprocess
import logging
import exceptions
import math
import time

import APDB
from binhex import FInfo
#from numpy.matrixlib.defmatrix import trow

# ==============================================
# DB & HAL variables, function and classes
# ==============================================

# some global data

# a dict associate the function name with the functionID and the list with parameters
# key = fname
# item = (fid, paramL, translation)
# paramL = (name, idParameterClass, idParameterType)
# idParameterClass = from APDB :
#    dFuncClass_basicIOtype = 1
#    dFuncClass_refVar      = 2
#    dFuncClass_refDataVar  = 3
#    dFuncClass_VarID       = 4
#    dFuncClass_VarIndex    = 5
# translation = fid, p0, p1, ..., pN
#    used to translate into binary
gHALfidD = {
    None : (None, [], []),
    'unknown function' : (None, [], [])
    }


# a dict associate the variable name with the variableID
# key = var name
# item = (varID,)
gHALvidD = {
    None : (None,),
    'unknown variable type' : (None,)
    }

# a dict with all basic i/o types
# key = typeID
# data = (name , c type, endianness)
gBasicIOTypesD = {
    None : ('unknown basic i/o type', None, None)
    }

# a dict mapping c types to python types
gCTypeToPythonD = {
    'int' : int,
    'uint32_t' : int,
    'int32_t' : int,
    'raw' : int,
    'char' : int,
    'float' : float,
    }

# a dict mapping python types to AL types
gAssoConstPythonTypesToALDict = {
    int : 'integer',
    float : 'rational',
    str : 'string'
}

gHALtoC89_ParamFormatDict = None


# maximum parameters per instruction
gHALInstrMaxParams = 0

# the subvariable delimiter 
gSubVarDelim = '_'

# search HAL function list by the function name
def _HAL_findFunctionByName (fname):
    return gHALfidD.get(fname, None)

# search HAL function list by the function id
def _HAL_findFunctionByID (fid):
    for key, item in gHALfidD.items():
        (HALFid, HALfParamL, HALfTransl) = item
        if HALFid == fid:
            return item
    return None

# search HAL variable type list by the type name
def _HAL_findVarTypeByName (vtname):
    return gHALvidD.get(vtname, None)

# search HAL function list by the function id
def _HAL_findVarTypeByID (vid):
    for key, item in gHALvidD.items():
        (itemVID, ) = item
        if itemVID == vid:
            return item
    return None

# search HAL function list by the function id
def _HAL_findBasicTypeByID (btid):
    return gBasicIOTypesD.get(btid, None)


# setup HAL vars
def _HAL_setup():
    global gHALInstrMaxParams
    global gBasicIOTypesD
    global gHALvidD
    global gHALfidD
    global gHALtoC89_ParamFormatDict
    
    cTypeToStructDict = {
        'float' : 'f', # float
        'int'   : 'i', # int
        'int32_t': 'i', # int
        'char' : 'I', # unsigned int
        'uint32_t' : 'I' # unsigned int
    }

    
    logging.info ('setup')
    logging.info ('open database')
    db = APDB.APDB('APdbCreate.sql','dbInit.xml')
    
    gHALInstrMaxParams = db.HAL_DefFunctions_maxParamCount()
    
    logging.info ('populate basic i/o type list and generate HAL parameter to C89 mapping')

    gHALtoC89_ParamFormatDict = {
        (db.dFuncClass_refVar, None) : 'i',
        (db.dFuncClass_refDataVar, None): 'i',
        (db.dFuncClass_VarID, None): 'i',
        (db.dFuncClass_VarIndex, None): 'i',
    }

    
    dbBIOL = db.HAL_basicIOTypes_getList()
    for (idHAL_IOTypesDefinition, TypeID, TypeName, description, cType, endianType, sizeInBytes) in dbBIOL:
        gBasicIOTypesD[TypeID] = (TypeName, cType, endianType)
        # extend parameter list by the basic types 
        gHALtoC89_ParamFormatDict[(db.dFuncClass_basicIOtype, TypeID)] =  cTypeToStructDict.get(cType, 'unknown c type({unt})'.format(unt=cType))

    logging.info ('populate function HAL list')

    
    dbfL = db.HAL_DefFunctions_getList()
    for (fuuid, fid, fname, fdescr) in dbfL:
        dbfpL = db.HAL_DefFunctions_getParamList(fid)
        fpL = []
        tL = ['i'] * (gHALInstrMaxParams + 1) # fid, p1, p2, p3, ..., pN
        i = 1
        for (idHAL_FunctionsParameter, pfid, name, descr, idParameterClass, idParameterType) in dbfpL:
            fpL.append((name, idParameterClass, idParameterType))
            if idParameterClass == db.dFuncClass_basicIOtype:
                tL[i] = gHALtoC89_ParamFormatDict.get((idParameterClass, idParameterType),'None')
            else:
                tL[i] = gHALtoC89_ParamFormatDict.get((idParameterClass, None),'None')
            i += 1
        gHALfidD[fname] = (fid, fpL, tL)
    logging.info ('populate variable HAL list')
    dbvL = db.HAL_VariableDefinition_getList()
    for (idHAL_VariableDefinition, VariableID, varName, description) in dbvL:
        gHALvidD[varName] = (VariableID,)


    logging.info ('setup finished')


# ==============================================
# variable type operation translation dict
# ==============================================

#key = class
#item = subclass key, subclassDict
#subclassDict:
#key = switch parameter
#item = (HALfunction, ParamList)
#ParamList = (name, variable/constant flag, default value)
#variable/constant flag = v - variable, c- constant
#
#example: sampleIO[operation=read ,dest=in1, channel=1, wait=1];
# key = sampleIO
# subclass key = operation
# dest, channel, wait = params
gVariableTypeOperationD = {
        # biquad
        'biquad' : ('type',{
            'coeff' : ('initBiquad',[('obj', 'v', None) ,('index', 'v', int(0)),('a0', 'v', float(0.0)),('a1', 'v', float(0.0)),('a2', 'v', float(0.0)),('b1', 'v', float(0.0)),('b2', 'v', float(0.0)) ]),
            'HP' : ('initBiquadAsHP',[('obj', 'v', None) ,('index', 'v', int(0)),('fs', 'v', None) ,('fc', 'v', None)]),
            'LP' : ('initBiquadAsLP',[('obj', 'v', None) ,('index', 'v', int(0)),('fs', 'v', None) ,('fc', 'v', None)]),
            'Peak': ('initBiquadAsPeakFilter',[('obj', 'v', None) ,('index', 'v', int(0)),('fs', 'v', None) ,('fc', 'v', None),('q', 'v', None) ,('g', 'v', None)]),
            'lowShelv': ('initBiquadAsLowFreqShelvFilter',[('obj', 'v', None) ,('index', 'v', int(0)),('fs', 'v', None) ,('fc', 'v', None),('g', 'v', None)]),
            'highShelv': ('initBiquadAsHighFreqShelvFilter',[('obj', 'v', None) ,('index', 'v', int(0)),('fs', 'v', None) ,('fc', 'v', None),('g', 'v', None)]),
            }),
        # dynamics
        'noisegate' : (None,('initNoisegate',[('obj', 'v', None),('TAV', 'c', None),('AT', 'c', None),('RT', 'c', None),('NT', 'c', None),('NS', 'c', None)])),        
        'compressor' : (None,('initCompressor',[('obj','v', None),('TAV', 'c', None),('AT', 'c', None),('RT', 'c', None),('CT', 'c', None),('CS', 'c', None)])),
        'expander' : (None,('initExpander',[('obj', 'v', None),('TAV', 'c', None),('AT', 'c', None),('RT', 'c', None),('ET', 'c', None),('ES', 'c', None)])),
        'limiter' : (None,('initLimiter',[('obj', 'v', None),('ATpeak', 'c', None),('RTpeak', 'c', None),('ATsmooth', 'c', None),('RTsmooth', 'c', None),('LT', 'c', None),('LS', 'c', None)])),
        # delay
        'delay': (None,('initDelay',[('obj', 'v', None),('N', 'v', None),('index', 'v', None)])),
        # smaple i/o
        'sampleIO' : ('operation', {
            'read' : ('readSampleFrame', [('channel', 'c', None),('dest', 'v', None),('wait', 'c', int(1))]),
            'write' : ('writeSampleFrame', [('channel', 'c', None),('src', 'v', None)])
            }),
        # ui
        'ui' : ('func',{
            'dim' : ('uiSetDim',[('x', 'c', None),('y', 'c', None), ('xle', 'c', None),('yle', 'c', None), ('obj',  'v', None) , ('index', 'c', int(0))]),
            'initPanel': ('uiInitPanel', [('uuid', 'c', None),('obj', 'v', None) ,('index', 'c', int(0))]),            
            'initDisplay': ('uiInitDisplay',[('uuid', 'c', None), ('obj', 'v', None), ('index', 'c', int(0)), ('parent', 'v', None) , ('pIndex', 'c', int(0))]),
            'initButton': ('uiInitButton',[('uuid', 'c', None), ('obj', 'v', None), ('index', 'c', int(0)), ('parent', 'v', None), ('pIndex', 'c', int(0))]),
            'initLED': ('uiInitLED',[('uuid', 'c', None), ('obj', 'v', None) , ('index', 'c', int(0)), ('parent', 'v', None), ('pIndex', 'c', int(0))]),
            'checkButton' : ('uiCheckButtonPressed', [('obj', 'v', None), ('index', 'c', int(0))]),
            'print' : ('uiSetDisplay', [('obj', 'v', None) , ('index', 'c', int(0)), ('text', 'v', None), ('tindex', 'c', int(0))]),
            'LED' : ('uiSetLED', [('obj', 'v', None), ('index', 'c', int(0)), ('on', 'c', int(1))]),
            'setTextDim': ('uiSetDisplayTextDim',[('obj', 'v', None), ('index', 'c', int(0)), ('charsPerLine', 'c', int(16)),('lines', 'c', int(2))]),
            })
    }

# ==============================================
# expression translation dict
# ==============================================
# key = arithmetic / boolean operation
# item = (dict of possibilities)
# dict of possibilities:
# key = (touple of the type of parameters)
# item = (HAL function, Parameter List)
# Parameter List:
# element = (sourceIndex, destIndex, typeID, typeData)
# type = (
#     v - variable name -> typeData = AL type of the parameter
#     e - can be variable or constant -> typeData = AL type of the parameter
#     c - constant: sourceIndex does not matter, typeID = paramtype, typeData = value
gOperationTranslationD = {
    # c = a+ b -> addInteger a,b,c
    'add' : {
        ('integer','integer','integer') :       ('addInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
        ('rational','rational','rational') :    ('addRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
        },
    'sub' : {
        ('integer','integer','integer') :       ('subInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
        ('rational','rational','rational') :    ('subRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
        },
    'mul' : {
        ('integer','integer','integer') :       ('mulInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
        ('rational','rational','rational') :    ('mulRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')]),
    # y = bqa * x -> convoluteBiquad x, bqa, y
        ('rational','biquad','rational') :      ('convoluteBiquad',[(0,2,'v','rational'),(1,1,'v','biquad'),(2,0,'e','rational')]),
        ('rational','rational','biquad') :      ('convoluteBiquad',[(0,2,'v','rational'),(2,1,'v','biquad'),(1,0,'e','rational')]),
    # y = delay * x -> calcDelay x, delay, y
        ('rational','delay','rational') :      ('calcDelay',[(0,2,'v','rational'),(1,1,'v','delay'),(2,0,'e','rational')]),
        ('rational','rational','delay') :      ('calcDelay',[(0,2,'v','rational'),(2,1,'v','delay'),(1,0,'e','rational')]),
    # y = dynEffect * x -> calcNoisegate x, dyneff, y
        ('rational','noisegate','rational') :   ('calcNoisegate',[(0,2,'v','rational'),(1,1,'v','noisegate'),(2,0,'e','rational')]),
        ('rational','rational','noisegate') :   ('calcNoisegate',[(0,2,'v','rational'),(2,1,'v','noisegate'),(1,0,'e','rational')]),
        ('rational','expander','rational') :    ('calcExpander',[(0,2,'v','rational'),(1,1,'v','expander'),(2,0,'e','rational')]),
        ('rational','rational','expander') :    ('calcExpander',[(0,2,'v','rational'),(2,1,'v','expander'),(1,0,'e','rational')]),
        ('rational','compressor','rational') :  ('calcCompressor',[(0,2,'v','rational'),(1,1,'v','compressor'),(2,0,'e','rational')]),
        ('rational','rational','compressor') :  ('calcCompressor',[(0,2,'v','rational'),(2,1,'v','compressor'),(1,0,'e','rational')]),
        ('rational','limiter','rational') :     ('calcLimiter',[(0,2,'v','rational'),(1,1,'v','limiter'),(2,0,'e','rational')]),
        ('rational','rational','limiter') :     ('calcLimiter',[(0,2,'v','rational'),(2,1,'v','limiter'),(1,0,'e','rational')])
        },
    'div' : {
        ('integer','integer','integer') :       ('divInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
        ('rational','rational','rational') :    ('divRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
        },
    'mod' : {
        ('integer','integer','integer') :       ('modInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
        ('rational','rational','rational') :    ('modRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
        },
    'assign' : {
        # a = b -> assign a,b
        ('integer','integer') :     ('assignInteger',[(0,0,'v','integer'),(1,1,'e','integer')]),
        ('rational','rational') :   ('assignRational',[(0,0,'v','rational'),(1,1,'e','rational')]),
        # a[ai] = b[bi] -> assign a,ai,b, bi
        ('string','string') :  ('assignString',[(0,0,'v','string'),(None,1,'c', 0),(1,2,'e','string'),(None,3,'c',0)]),
        # a[ai] = str(b[bi]) -> integerToString a,ai,b, bi
        ('string','integer') :      ('integerToString',[(0,0,'v','string'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('string','rational') :     ('rationalToString',[(0,0,'v','string'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    'addAssign' : {
         ('string','string') :      ('concatStrings',[(0,0,'v','string'),(None,1,'c',0),(1,2,'e','string'),(None,3,'c',0)]),
         ('integer','integer') :    ('addInteger',[(0,0,'v','integer'),(1,1,'e','integer'),(0,2,'e','integer')]),
         ('rational','rational') :  ('addRational',[(0,0,'v','rational'),(1,1,'e','rational'),(0,2,'e','rational')])
        },
    '==' : {
        ('integer', 'integer') :     ('compareIntegerEqual',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalEqual',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    '!=' : {
        ('integer','integer') :     ('compareIntegerNEqual',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalNEqual',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    '>' : {
        ('integer','integer') :     ('compareIntegerMore',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalMore',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    '<' : {
        ('integer','integer') :     ('compareIntegerLess',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalLess',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    '>=' : {
        ('integer','integer') :     ('compareIntegerMoreEqual',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalMoreEqual',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
    '<=' : {
        ('integer','integer') :     ('compareIntegerLessEqual',[(0,0,'e','integer'),(None,1,'c',0),(1,2,'e','integer'),(None,3,'c',0)]),
        ('rational','rational') :   ('compareRationalLessEqual',[(0,0,'e','rational'),(None,1,'c',0),(1,2,'e','rational'),(None,3,'c',0)])
        },
}

# ==============================================
# AST classes
# ==============================================

# the basic AST class object
class ASTobject(object):
    def __init__(self, line ,column):
        self.line = line 
        self.column = column
    
    def getPosStr(self):
        return 'line: {line} column: {column}'.format(line=self.line,column=self.column)
    
    def __repr__ (self):
        return self.getPosStr()
    
# the basic AST comment class
class ASTcomment (ASTobject):
    def __init__(self, line, column, comment):
        super(ASTcomment, self).__init__(line ,column)
        self.comment = comment
    
    def __repr__ (self):
        return 'comment: "{comment}" at {pos}'.format(comment=self.comment,pos=super(ASTcomment,self).__repr__())

# list holing a ASTobjects
class ASTobjList (ASTobject):
    def __init__(self, astObjList):
        super(ASTobjList, self).__init__(0 ,0)
        self.astObjList = astObjList
    
    def __repr__ (self):
        rStr = ''
        for o in self.astObjList:
            rStr += str(o)
            rStr += '\n' 
        return rStr
    
    def append (self, astObj):
        self.astObjList.append(astObj)

    def getList (self):
        return self.astObjList
    
    def searchListForVariableOperationParam(self,key):
        for p in self.astObjList:
            if isinstance(p, ASTvariableOperationParam) is True:
                if (p.operationParam == key):
                    return p
        return None

# the AST object for type defs
class ASTtypedef (ASTobject):
    def __init__(self, line ,column, typeName, typedefASTInstrL):
        super(ASTtypedef, self).__init__(line ,column)
        self.typeName = typeName
        self.typedefASTInstrL = typedefASTInstrL
    
    def __repr__ (self):
        return 'typedef of "{typeName}" at {pos}'.format(typeName=self.typeName,pos=super(ASTtypedef,self).__repr__())

# the AST type for a variable declaration
class ASTvariableDef(ASTobject):
    def __init__(self, line ,column, varName, varType, amount):
        super(ASTvariableDef, self).__init__(line ,column)
        self.varName = varName
        self.varType = varType
        self.amount = amount
        
    def __repr__ (self):
        return 'variable name:"{name}" with type:"{type}" and an amount of {amount} at {pos}'.format(name=self.varName,type=self.varType,amount=self.amount, pos=super(ASTvariableDef,self).__repr__())

# the AST type for function parameters
class ASTfuncParameter(ASTobject):
    def __init__(self, line ,column, varName, varType, amount, ioType):
        super(ASTfuncParameter, self).__init__(line ,column)
        self.varName = varName
        self.varType = varType
        self.amount = amount
        self.ioType = ioType
        
    def __repr__ (self):
        return 'func param:"{name}" type:"{type}" amount:{amount} i/o:{io} at {pos}'.format(name=self.varName,type=self.varType,amount=self.amount,io=self.ioType, pos=super(ASTfuncParameter,self).__repr__())

# abstract parameter class
class ASTinstructionParam (ASTobject):
    # gets the type of the parameter
    def getType (self, vD, tvUnrolledD):
        return None

class ASTinstructionParamConst (ASTinstructionParam):
    def __init__(self, line, column, Const, ConstType):
        super(ASTinstructionParamConst, self).__init__(line ,column)
        self.const = Const
        self.constType = ConstType
        
    def __repr__ (self):
        return 'const. instrParam value:"{const}" type:"{type}" at {pos}'.format(const=self.const,type=self.getType(None, None), pos=super(ASTinstructionParamConst,self).__repr__())

    def getType (self, varDefL, typeD):
        return gAssoConstPythonTypesToALDict.get(self.constType, None)
    
    def getName (self):
        return 'constant({value})'.format(value=self.const)

    def getStrTypeName (self):
        return '{type} {const}'.format(const=self.const,type=self.getType(None, None))
    
    def getValue (self):
        return self.const 

class ASTinstructionParamRefVar (ASTobject):
    def __init__(self, line, column, varRef, subValueRefList = [], index = 0):
        super(ASTinstructionParamRefVar, self).__init__(line ,column)
        self.varRef = varRef
        self.subValueRefList = subValueRefList
        self.index = index
        
    def __repr__ (self):
        return 'ref.Var.: "{vName}"[{index}] at {pos}'.format(vName=self.getName(), index=self.index,pos=self.getPosStr())

    def addSubValue(self, sv):
        self.subValueRefList.append(sv)
    
    def setIndex (self, indx):
        self.index = indx
        
    def getNameWithSubVal(self, name, subValSep):
        refStr = '{name}'.format(name=name)
        for r in self.subValueRefList:
            refStr += subValSep + r
        return refStr
        
        
    def getName (self, subValSep='.'):
        return self.getNameWithSubVal(self.varRef, subValSep)
            
    
    # gets the type of the 
    def getType (self, varDefL, typeD):
        vdItem = varDefL.findVariable(self.varRef)
        if vdItem is None:
            raise exceptions.SyntaxError('at {pos}: variable "{varName}" is unknown'.format(pos=self.getPosStr(), varName=self.varRef))
        rType = vdItem.getType()
        userType = typeD.get(rType, None)
        errorStr = '{varRef}'.format(varRef=self.varRef)
        # iterate through the subtypes
        for sv in self.subValueRefList:
            errorStr += '.{sv}'.format(sv=sv)
            r = userType.get(sv, None)
            if r is None:
                raise exceptions.SyntaxError('at {pos}: sub variable "{errorStr}" is not defined at user type "{rType}"'.format(pos=self.getPosStr(), errorStr=errorStr, rType=rType))
            elif isinstance(r, dict):
                userType = r
            elif isinstance(r, ASTvariableDef):
                rType = r.varType
                break 
        return rType
        

# a abstract class for translating AST objects
class ASTtranslatable (ASTobject):
    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        return []
    
# the AST type for an instruction
class ASTinstruction(ASTtranslatable):
    def __init__(self, line ,column, instrName, instrParamsL):
        super(ASTinstruction, self).__init__(line ,column)
        self.instrName = instrName
        self.instrParamsL = instrParamsL
        
    def __repr__ (self):
        paramLstr = ''
        if self.instrParamsL is not None:
            j = 0
            for i in self.instrParamsL:
                if j != 0:
                    paramLstr += ', '
                paramLstr += str(i)
                j+=1
        return 'instr.: {name}({params}) at {pos}'.format(name=self.instrName,params=paramLstr, pos=super(ASTinstruction,self).__repr__())

    # transforms the AST into a instruction call
    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        fInfo = _HAL_findFunctionByName(self.instrName)
        if fInfo is None:
            raise exceptions.SyntaxError('at {pos}: function "{fname}" is not defined at the HAL'.format(pos=self.getPosStr(), fname=self.instrName))
        fid, fParamL, transL = fInfo
        # create a new function call obj
        instrObj = InstructionCall(self.instrName, self, deepness)
        # parameter amount check
        i = 0
        givenParamCount = len(self.instrParamsL)
        defFuncParamCount = len(fParamL) 
        if (defFuncParamCount != givenParamCount):
            raise exceptions.SyntaxError('at {pos}: definition of the HAL function "{fname}" has {defFuncParamCount}. The given function has {givenParamCount} parameters'.format(pos=self.getPosStr(), fname=self.instrName,defFuncParamCount=defFuncParamCount, givenParamCount=givenParamCount))
        # start to set the parameters
        for p in self.instrParamsL:
            (pName, idParameterClass, idParameterType) = fParamL[i]
            # try to match the parameter against it definition
            # a basic type param
            if idParameterClass == APDB.APDB.dFuncClass_basicIOtype:
                # decode type
                btInfo = _HAL_findBasicTypeByID(idParameterType)
                if btInfo is None:
                    raise exceptions.StandardError('at function "{fName}" is the parameter type of "{pName}" unknown ({idParameterType}).'.format(fName=self.instrName,pName=pName,idParameterType=idParameterType))
                # ok we got the basic type
                btName , btCtype, btEndianness = btInfo
                # ok build the translator
                btTransL = gCTypeToPythonD.get(btCtype, None)
                if btTransL is None:
                    raise exceptions.StandardError('basic type translation for "{btCtype}" is not defined.'.format(btCtype=btCtype))
                # ok lets add the parameter
                instrObj.addParamConst(RefConst(p))
            # something dealing with a variable
            elif ((idParameterClass == APDB.APDB.dFuncClass_refVar) or (idParameterClass == APDB.APDB.dFuncClass_refDataVar) or (idParameterClass == APDB.APDB.dFuncClass_VarID)):
                if isinstance(p, ASTinstructionParamRefVar) is True:
                    # lets check if the variable exists
                    assocVar = varDefL.findVariable(p)
                    if assocVar is None:
                        raise exceptions.SyntaxError('at {pos}: the variable "{varName}" has not been declared'.format(pos=p.getPosStr(), varName=p.varRef))
                    instrObj.addParamRefVariable(RefVar(assocVar, p))
                elif isinstance(p, ASTinstructionParamConst) is True:
                    # lets make a entry at the constant dict
                    ncv = varDefL.createConst(p.const, p.constType)
                    instrObj.addParamRefConst(RefVar(ncv, p))
                else:
                    raise exceptions.StandardError('error: unknown parameter type for the functions')
            # variable index
            elif idParameterClass == APDB.APDB.dFuncClass_VarIndex:
                if isinstance(p, ASTinstructionParamRefVar) is True:
                    # lets check if the variable exists
                    assocVar = varDefL.findVariable(p)
                    if assocVar is None:
                        raise exceptions.SyntaxError('at {pos}: the variable "{varName}" has not been declared'.format(pos=p.getPosStr(), varName=p.varRef))
                    instrObj.addParamVariableIndex(RefVar(assocVar, p))
                elif isinstance(p, ASTinstructionParamConst) is True:
                    instrObj.addParamVariableIndex(RefConst(p))
                else:
                    raise exceptions.StandardError('error: unknown parameter type for the functions')
            else:
                raise exceptions.StandardError('at function "{fName}" is the parameter class of "{pName}" given with "{idParameterClass}". This id is unknown.'.format(fName=self.instrName,pName=pName,idParameterClass=idParameterClass))            
            i += 1
        
        return instrObj

# the AST type for an instruction
class ASTConditionalBlock(ASTtranslatable):
    def __init__(self, line, column, condInstrList, TrueCode, FalseCode, loopFlag, loopExtraCode):
        super(ASTConditionalBlock, self).__init__(line ,column)
        self.condInstrList = condInstrList
        self.TrueCode = TrueCode
        self.FalseCode = FalseCode
        self.loopFlag = loopFlag
        self.loopExtraCode = loopExtraCode
        
    def __repr__ (self):
        return 'condition block at {pos}'.format(pos=super(ASTConditionalBlock,self).__repr__())

    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        retFcL = []
        retFcDep = []
        
        # translate code
        if self.condInstrList != None:
            cond_FcL, cond_FcDep =_process_translateASTFunctionCall(self.condInstrList, varDefL, typedefD, deepness)
            
        if self.TrueCode != None:
            true_FcL, true_FcDep =_process_translateASTFunctionCall(self.TrueCode, varDefL, typedefD, deepness + 1)
            
        if self.FalseCode != None:
            false_FcL, false_FcDep =_process_translateASTFunctionCall(self.FalseCode, varDefL, typedefD, deepness + 1)
            
        
        if self.loopExtraCode != None:
            loop_FcL, loop_FcDep =_process_translateASTFunctionCall(self.loopExtraCode, varDefL, typedefD, deepness)
        else:
            loop_FcL, loop_FcDep = [], []
        
        # ok find out what we have
        
        # loop check
        if self.loopFlag is True:
            # endless loop check
            if self.condInstrList is None:
                loopJumpLabel = InstructionLabel(deepness)
                instr = InstructionCall('jump', self, deepness)
                instr.addParamJump(loopJumpLabel)
                
                retFcL.append(loopJumpLabel)
                retFcL += true_FcL
                retFcL += loop_FcL
                retFcL.append (instr)
            else:
                loopStartLabel = InstructionLabel(deepness)
                endJumpLabel = InstructionLabel(deepness)
                # jump if loop cond is not fulfilled
                instr = InstructionCall('jumpNCF', self, deepness)
                instr.addParamJump (endJumpLabel)
                
                retFcL.append(loopStartLabel)
                retFcL += cond_FcL
                retFcL.append(instr)
                retFcL += true_FcL
                retFcL += loop_FcL

                instr = InstructionCall('jump', self, deepness)
                instr.addParamJump (loopStartLabel)
                
                retFcL.append(instr)
                retFcL.append(endJumpLabel)

        # if then else
        else:
            if (self.TrueCode is not None) and (self.FalseCode is None):
                endCodeLabel = InstructionLabel(deepness)
                # check condition
                retFcL += cond_FcL
                # jump if condition is NOT fulfilled (CF is set)
                # because we have a true path
                instr = InstructionCall('jumpNCF', self, deepness)
                instr.addParamJump(endCodeLabel)
                retFcL.append(instr)
                # the true path
                retFcL += true_FcL
                # and add label for not CF 
                retFcL.append(endCodeLabel)
            elif (self.TrueCode is None) and (self.FalseCode is not None):
                endCodeLabel = InstructionLabel()
                # check condition
                retFcL += cond_FcL
                # jump if condition is fulfilled
                # because we are at the false condition
                # CF is set 
                instr = InstructionCall('jumpCF', self, deepness)
                instr.addParamJump(endCodeLabel)
                
                retFcL.append(instr)
                retFcL += false_FcL
                retFcL.append(endCodeLabel)
            elif (self.TrueCode is not None) and (self.FalseCode is not None):
                # labels
                endCodeLabel = InstructionLabel(deepness)
                falsePathLabel = InstructionLabel(deepness)
                # check cond
                retFcL += cond_FcL
                # if not fullfilled go to false path
                instr = InstructionCall('jumpNCF', self, deepness)
                instr.addParamJump(falsePathLabel)
                retFcL.append(instr)
                # true path
                retFcL += true_FcL
                # and jump to the end of the block
                instr = InstructionCall('jump', self, deepness)
                instr.addParamJump(endCodeLabel)
                retFcL.append(instr)
                # start of the false path
                retFcL.append(falsePathLabel)
                # false path
                retFcL += false_FcL
                # end of code
                retFcL.append(endCodeLabel)
        return retFcL 

# the AST type for an function call
class ASTinstructionFunctionCall(ASTtranslatable):
    def __init__(self, line ,column, functionName, outputL, inputL):
        super(ASTinstructionFunctionCall, self).__init__(line ,column)
        self.functionName = functionName
        self.outputL = outputL
        self.inputL = inputL
        
    def __repr__ (self):
        paramLstr = '['
        j = 0
        for i in self.outputL:
            if j != 0:
                paramLstr += ', '
            paramLstr += str(i)
            j+=1
        paramLstr += '] {callF} ['.format(callF=self.functionName)
        j = 0
        for i in self.inputL:
            if j != 0:
                paramLstr += ', '
            paramLstr += str(i)
            j+=1
        paramLstr += '] at {pos}'.format(pos=super(ASTinstructionFunctionCall,self).__repr__())
        return paramLstr

    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        return InstructionCallFunction(self.functionName, self.inputL.getList(), self.outputL.getList(), deepness, self)


# the AST type for an function call
class ASTvariableTypeOperation(ASTtranslatable):
    def __init__(self, line ,column, varOpName, ParamList):
        super(ASTvariableTypeOperation, self).__init__(line ,column)
        self.varOpName = varOpName
        self.ParamList = ParamList
        
    def __repr__ (self):
        return 'ASTvariableTypeOperation: {varOpName} {paramList} at pos: {pos}'.format(varOpName=self.varOpName, paramList=self.ParamList, pos=self.getPosStr())
        
    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        # find main template
        mainTemplate = gVariableTypeOperationD.get(self.varOpName, None)
        if mainTemplate is None:
            raise exceptions.SyntaxError('at {pos}: variable operation "{varOpName}" is unknown.'.format(pos=self.getPosStr(),varOpName=self.varOpName))
        # get if needed the sub class template    
        if mainTemplate[0] is None:
            template = mainTemplate[1]
        else:
            keyName, templateDict = mainTemplate
            subKeyParam = self.ParamList.searchListForVariableOperationParam(keyName)
            if subKeyParam is None:
                raise exceptions.SyntaxError('at {pos}: the operation parameter "{keyName}" is missing.'.format(pos=self.getPosStr(),keyName=keyName))
            template = templateDict.get(subKeyParam.expRef.varRef)
            if template is None:
                raise exceptions.SyntaxError('at {pos}: the value of operation parameter "{keyName}"="{val}" is not valid.'.format(pos=self.getPosStr(),keyName=keyName,val=subKeyParam.expRef.varRef))
        # ****
        # now try to build a instruction
        # ****        
        HALfuncName, ParamDescrL = template
        
        instr = InstructionCall(HALfuncName, self, deepness)
        # ok lets build the parameter list
        paramList = [None]*len(ParamDescrL)
        # lets populate the list
        i = 0
        for (keyName, paramType, defaultValue) in ParamDescrL:
            p = self.ParamList.searchListForVariableOperationParam(keyName)
            if (p is None) and (defaultValue is None):
                raise exceptions.SyntaxError('at {pos}: the operation parameter "{keyName}" is missing.'.format(pos=self.getPosStr(),keyName=keyName))
            elif (p is None):
                if paramType == 'v':
                    var = varDefL.createConst(defaultValue, type(defaultValue), self)
                    paramList[i] = RefVar(var, self) 
                elif paramType == 'c':
                    paramList[i] = RefConst(ASTinstructionParamConst(self.line, self.column, defaultValue, type(defaultValue)))
                else:
                    raise exceptions.SyntaxError('internal error: unknown parameter type "{paramType}"'.format(paramType=paramType))
            else:
                param = p.expRef
                # check what kind of parameter is allowed
                if (paramType == 'v') and (isinstance(param, ASTinstructionParamConst) is True):
                    # a constant but a varaiable is needed
                    # create a variable attached to the constant
                    val = param.getValue()
                    var = varDefL.createConst(val,type(val),param)
                    paramList[i] = RefVar(var, param)
                elif (paramType == 'v') and (isinstance(param, ASTinstructionParamRefVar) is True):
                    # parameter should be a varaible and given parameter is a reference to a variable 
                    var = varDefL.findVariable(param)
                    paramList[i] = RefVar(var, param)
                elif (paramType == 'c') and (isinstance(param, ASTinstructionParamConst) is True):
                    paramList[i] = RefConst(param)
                else:
                    raise exceptions.SyntaxError('at {pos}: parameter type error'.format(pos=p.getPosStr()))                    
            i += 1
        # check if all parameters are set
        for p in paramList:
            if p is None:
                raise exceptions.SyntaxError('at {pos}: the operation parameter "{keyName}" is missing.'.format(pos=self.getPosStr(),keyName=ParamDescrL[i][0]))
        # ok lets bring the parameter list to the instruction
        HALinfo = _HAL_findFunctionByName(HALfuncName)
        if HALinfo is None: 
            raise exceptions.SyntaxError('at {pos}: HAL function for variable type operation "{opName}"("{HALfuncName}") is not defined'.format(pos=self.getPosStr(),opName=self.varOpName,HALfuncName=HALfuncName))
        (HALfid, HALparamL, HALtransl) = HALinfo
        i = 0
        for p in paramList:
            # type check
            (HALname, HALidParameterClass, HALidParameterType) = HALparamL[i]
            # get type name
            paramHALType = p.getType(varDefL, typedefD)
            # get vid to the type name
            r = _HAL_findVarTypeByName(paramHALType)
            idHALvidParam = r[0]
            # check vid's agianst each other
            if (HALidParameterType != idHALvidParam) and (HALidParameterType != 0):
                # fail
                r = _HAL_findVarTypeByID(HALidParameterType)
                if r is not None:
                    HALtypeName = r[0]
                else:
                    HALtypeName = 'not defined'
                raise exceptions.SyntaxError('at {pos}: parameter type "{paramHALType}" is different from the type at the HAL definition("{HALtypeName}")'.format(pos=self.getPosStr(),paramHALType=paramHALType,HALtypeName=HALtypeName))
            # ok - vid's equal
            
            # add to instruction
            if HALidParameterClass == APDB.APDB.dFuncClass_basicIOtype:
                instr.addParamConst(p)
            elif HALidParameterClass == APDB.APDB.dFuncClass_refVar:
                instr.addParamRefVariable(p)
            elif HALidParameterClass == APDB.APDB.dFuncClass_refDataVar:
                instr.addParamRefVariable(p)
            elif HALidParameterClass == APDB.APDB.dFuncClass_VarID:
                instr.addParamRefVariable(p)
            elif HALidParameterClass == APDB.APDB.dFuncClass_VarIndex:
                instr.addParamVariableIndex(p)
            else:
                raise exceptions.StandardError('HAL DB error: unknown parameter class ')
            i += 1
        return instr
        
        
class ASTvariableOperationParam(ASTobject):
    def __init__(self, line, column, operationParam, expRef):
        super(ASTvariableOperationParam, self).__init__(line ,column)
        self.operationParam = operationParam
        self.expRef = expRef
        
    def __repr__ (self):
        paramLstr = 'var op param "{opParam}"="{exp}" at {pos}'.format(opParam=self.operationParam, exp=self.expRef, pos=super(ASTvariableOperationParam,self).__repr__())
        return paramLstr


# the AST type for functions
class ASTfunction(ASTobject):
    def __init__(self, line ,column, fName, inpOutpL, localVarL, instructionL):
        super(ASTfunction, self).__init__(line ,column)
        self.fName = fName
        self.inpOutpL = inpOutpL
        self.localVarL = localVarL
        self.instructionL = instructionL

    def __repr__ (self):
        rStr = 'function definition of "{fName}" at {pos}'.format(fName=self.fName, pos=super(ASTfunction,self).__repr__())
        return rStr

# the AST type for functions
class ASTmain(ASTfunction):
    def __init__(self, line ,column, mainName, localVarL, instructionL):
        super(ASTmain, self).__init__(line ,column, mainName, ASTobjList([]), localVarL, instructionL)

    def __repr__ (self):
        return super(ASTmain,self).__repr__()

# the AST type for an instruction
class ASTinstructionArithmeticBool(ASTtranslatable):
    def __init__(self, line ,column, arithmBoolOperation, paramsL):
        super(ASTinstructionArithmeticBool, self).__init__(line ,column)
        self.operation = arithmBoolOperation
        self.paramsL = paramsL
        
    def __repr__ (self):
        paramLstr = ''
        j = 0
        for i in self.paramsL:
            if j != 0:
                paramLstr += ', '
            paramLstr += str(i)
            j+=1
        return 'arithm./bool. instr.: {name} ({params}) at {pos}'.format(name=self.operation,params=paramLstr, pos=self.getPosStr())

    def transformASTtoInstructionCall (self, varDefL, typedefD, deepness):
        # check the expression type and get the instruction dict
        arithTranslTempl = gOperationTranslationD.get(self.operation, None)

        if arithTranslTempl is None:
            raise exceptions.StandardError('at {pos}: expression operator "{operation}" is not known'.format(operation=self.operation, pos=self.getPosStr()))
        # build serach tuple
        searchTypes = [None] * len (self.paramsL)
        i = 0
        for p in self.paramsL:
            searchTypes[i] = p.getType(varDefL, typedefD)
            i += 1
        funcT = arithTranslTempl.get(tuple(searchTypes),None)
        # check if the operation is applyable
        if funcT is None:
            raise exceptions.SyntaxError('at {pos}: there is no valid operation("{opName}") for the variables. The types of the variables are {varTypes}.'.format(opName=self.operation, pos=self.getPosStr(), varTypes=searchTypes))
        
        # ok lets build the stuff
        (strHALfunction, HALParameterList) = funcT
        
        instr = InstructionCall(strHALfunction, self, deepness)
        instrParamsL = [None]*len(HALParameterList)
        
        # 1st. sort the params into the right order
        for (sourceIndex, destIndex, typeID, typeData) in HALParameterList:
            if sourceIndex != None:
                instrParamsL[destIndex] = self.paramsL[sourceIndex]
            else:
                instrParamsL[destIndex] = ASTinstructionParamConst(self.line, self.column, typeData, int)
            
        # 2nd add them to the instruction
        i = 0
        for p in instrParamsL:
            # get typeID and typeData to the parameter
            sourceIndex = None
            typeID = None
            typeData = None
            for pHAL in HALParameterList:
                # (sourceIndex, destIndex, typeID, typeData)
                if pHAL[1] == i:
                    sourceIndex = pHAL[0]
                    typeID = pHAL[2]
                    typeData = pHAL[3]
                    break                     
                
            # type check (except constants)
            if (sourceIndex is not None) and (searchTypes[sourceIndex] != typeData) and (typeData is not None):
                raise exceptions.SyntaxError('at {pos}: the type("{pType}") of parameter "{p}" doesn\'t match the forced type "{typeData}".'.format(pos=self.getPosStr(), pType=searchTypes[sourceIndex], p=p.getName(), typeData=typeData))                    
            # v - variable name -> typeData = AL type of the parameter
            if typeID == 'v':
                varDef = varDefL.findVariable(p)
                instr.addParamRefVariable(RefVar(varDef,p))
            # i - index of variable  -> typeData = None            
            elif typeID == 'i':
                varDef = varDefL.findVariable(p)
                instr.addParamVariableIndex(RefVar(varDef,p))
            # c - constant-> typeData = AL type of the parameter
            elif typeID == 'c':
                if isinstance(p, ASTinstructionParamConst) is False:
                    raise exceptions.SyntaxError('at {pos}: parameter "{p}" must be a constant.'.format(pos=self.getPosStr(), p=p.getName()))
                instr.addParamConst(RefConst(p))
            # e - can be variable or constant -> typeData = AL type of the parameter
            elif typeID == 'e':
                # check if we have to create a constant variable
                if isinstance(p, ASTinstructionParamConst) is True:
                    varDef = varDefL.createConst(p.const, p.constType, p)
                else:
                    varDef = varDefL.findVariable(p)
                instr.addParamRefVariable(RefVar(varDef,p))
            else:
                raise exceptions.StandardError('in gOperationTranslationD at {opName} is at {varTypes} an invalid type entry'.format(opName=self.operation, varTypes=searchTypes))
            # increment param index
            i += 1                
        return instr


class InstructionBase (object):
    def __init__(self, deepness):
        self.deepness = deepness
        
    def getDeepnessStr(self, repeatStr='\t'):
        return repeatStr * self.deepness
    
    def addDeepness (self, val=+1):
        self.deepness =+ val
    
    def getAsText (self):
        return 'instruction base'

# a class for instruction calls
# param= (id, ASTitem)
class InstructionCall (InstructionBase):
    idParams = {
        1 : 'reference to variable',
        2 : 'reference to constant',
        3 : 'constant',
        4 : 'variable index',
        5 : 'jump to instruction'
        }
    def __init__(self, fname, ASTitem, deepness):
        super(InstructionCall, self).__init__(deepness)
        self.fname = fname
        self.parameterList = []
        self.ASTitem = ASTitem
        self.labelFlag = False
     
    def getParamList(self):
        return self.parameterList

    def addParamRefVariable (self, refVar):
        self.parameterList.append([1, refVar])

    def addParamRefConst (self, refConst):
        self.parameterList.append([2, refConst])

    def addParamConst (self, ASTitem):
        self.parameterList.append([3, ASTitem])

    def addParamVariableIndex (self, ASTitem):
        self.parameterList.append([4, ASTitem])

    def addParamJump (self, loopInstr):
        self.parameterList.append([5, loopInstr])

    def getAsText (self):
        txt = self.getDeepnessStr() + '{fname} ('.format(fname=self.fname)
        i = 0
        for p in self.getParamList():
            if i != 0:
                txt += ', '
            txt += '{param}'.format(param=p[1])
            i += 1
        txt += ')'
        return txt
    
    def getAsShortText (self):
        txt = '{fname} ('.format(fname=self.fname)
        i = 0
        for p in self.getParamList():
            if i != 0:
                txt += ', '
            if isinstance(p[1], RefVar) is True:
                ptxt = p[1].getVarDefName()
            elif isinstance(p[1], RefConst) is True:
                ptxt = p[1].getValueStr()
            else:
                ptxt = p[1] 
            txt += '{param}'.format(param=ptxt)
            i += 1
        txt += ')'
        return txt
        

    def __repr__ (self):
        txt = '{fname} ('.format(fname=self.fname)
        i = 0
        for p in self.getParamList():
            if i != 0:
                txt += ', '
            txt += '{param}'.format(param=p[1])
            i += 1
        txt += ')'
        return txt

# label instruction

# a global counter for the labels
_gInstrLabelIDcounter = 1

# the label class
class InstructionLabel(InstructionBase):
    def __init__ (self, deepness, labelNumber=None):
        super(InstructionLabel, self).__init__(deepness)
        global _gInstrLabelIDcounter
        if labelNumber is None:
            _gInstrLabelIDcounter += 1
            self.labelID = _gInstrLabelIDcounter
        else:
            self.labelID = labelNumber
             
    def getName (self):
        return 'label_{id}:'.format(id=self.labelID)

    def getAsText (self):
        return self.getDeepnessStr() + 'label {id}:'.format(id=self.labelID)

    def __repr__ (self):
        return 'label ID:{id}'.format(id=self.labelID)
    
    def __cmp__(self, other):
        return cmp(self.labelID,other.labelID)

    def getAsShortText(self):
        return self.__repr__()


class InstructionCallFunction (InstructionBase):
    def __init__ (self, funcName, inputs, outputs, deepness, ASTobj):
        super(InstructionCallFunction, self).__init__(deepness)
        self.funcName = funcName
        self.inputs = inputs
        self.outputs = outputs
        self.ASTobj = ASTobj

    def getName (self):
        outT = '['
        i = 0
        for p in self.outputs:
            if i != 0:
                outT +=' ,'
            outT += p.getName()
            i += 1
        outT += ']'

        inT = '['
        i = 0
        for p in self.inputs:
            if i != 0:
                inT +=' ,'
            inT += p.getName()
            i += 1
        inT += ']'
        
        return '{outT} = {name} {inT}'.format(name=self.funcName,outT=outT, inT=inT)

    def getAsText (self):
        return self.getDeepnessStr() + self.getName()
        
    def __repr__ (self):
        return self.getName()

# a class holding the definition of a variable
class VarDef (object):
    def __init__ (self, ASTobj, isGlobalVar):
        self.ASTobj = ASTobj
        self.vName = ASTobj.varName
        self.vType = ASTobj.varType
        self.vAmount = ASTobj.amount
        self.isGlobalVar = isGlobalVar
        
    def __repr__ (self):
        if self.isGlobalVar is True:
            gvarPfx = 'g'
        else:
            gvarPfx = 'l'
        return '[{gvarPfx}] {vType} {vName}[{vAmount}]'.format(gvarPfx=gvarPfx, vType=self.vType, vName=self.vName, vAmount=self.vAmount)

    def __cmp__(self, other):
        if isinstance(other, VarDef) is True:
            return cmp(self.vName,other.vName)
        elif isinstance(other, RefVar) is True:
            return cmp(self.vName,other.varDef.vName)
        elif isinstance(other, ASTinstructionParamRefVar) is True:
            return cmp(self.vName,other.varRef)
        elif isinstance(other, str) is True:
            return cmp(self.vName, other)
        elif isinstance(other, ASTinstructionParamConst) is True:
            if isinstance(self, VarDefConstVariable) is True:
                # type missmatch
                if self.vType != gAssoConstPythonTypesToALDict.get(other.constType, None):
                    return 1
                return cmp(self.value, other.const)
            else:
                return 1
        elif (other is None):
            return 1
        else:
            raise exceptions.SyntaxError('internal error: at VarDef unknown item to compare. Item: {item}'.format(item=other))
    
    def getType(self):
        return self.vType
    
    def getName(self):
        return self.vName
    
    def isGlobal(self):
        return self.isGlobalVar
    
    def getAmount(self):
        return self.vAmount
    

_const_prefix = '#const'
_const_uuid = 1

class VarDefConstVariable (VarDef):
    def __init__ (self, value, vtype, ASTobj):
        global _const_prefix
        global _const_uuid  
        HALtype = gAssoConstPythonTypesToALDict.get(vtype, None)
        if HALtype == None:
            raise exceptions.SyntaxError('internal error: unknown constant type "{vtype}"'.format(vtype=vtype))
        self.value = value
        # std var def
        self.ASTobj = ASTobj
        self.vName = '{prefix}{uuid}'.format(prefix=_const_prefix, uuid=_const_uuid)
        self.vType = HALtype
        self.vAmount = 1
        
        _const_uuid += 1
         
    def isGlobal(self):
        return False

    def __repr__ (self):
        return '{name} = "{value}"({ctype})'.format(name=self.vName, value=self.value, ctype=self.vType)

    def createSetupCode (self, deepness):
        setupCodeL = []
        if self.vType == 'rational':
            # create init code
            localVar = ASTinstructionParamRefVar(self.ASTobj.line, self.ASTobj.column, self.vName)
            instr = InstructionCall('assignConstRational',self.ASTobj, deepness)
            instr.addParamRefVariable(RefVar(self, localVar))
            constIndex = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 0, int)
            instr.addParamConst(RefConst(constIndex))
            constAmount = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 1, int)
            instr.addParamConst(RefConst(constAmount))
            constValue = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, self.value, float)
            instr.addParamConst(RefConst(constValue))
            # append it to list
            setupCodeL.append(instr)

        elif self.vType == 'integer':
            # create init code
            localVar = ASTinstructionParamRefVar(self.ASTobj.line, self.ASTobj.column, self.vName)
            instr = InstructionCall('assignConstInteger',self.ASTobj, deepness)
            instr.addParamRefVariable(RefVar(self, localVar))
            constIndex = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 0, int)
            instr.addParamConst(RefConst(constIndex))
            constAmount = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 1, int)
            instr.addParamConst(RefConst(constAmount))
            constValue = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, self.value, int)
            instr.addParamConst(RefConst(constValue))
            # append it to list
            setupCodeL.append(instr)

        elif self.vType == 'string':
            strLength = len(self.value)
            localVar = ASTinstructionParamRefVar(self.ASTobj.line, self.ASTobj.column, self.vName)
            #init string with the length
            instr = InstructionCall('setStringSize',self.ASTobj, deepness)
            instr.addParamRefVariable(RefVar(self, localVar))
            constIndex = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 0, int)
            instr.addParamConst(RefConst(constIndex))
            constStrLength = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, strLength, int)
            instr.addParamConst(RefConst(constStrLength))
            setupCodeL.append(instr)

            # now build a array holding the chucks of the string
            amountOfInstElementsToUse = gHALInstrMaxParams - 3
            strElementsPerInstr = amountOfInstElementsToUse * 4 
            
            amountOfInitInstr = int(math.ceil( strLength / float(strElementsPerInstr)))
            c = 0
            cs = 0
            for i in range(0, amountOfInitInstr):
                pParams = [0] * amountOfInstElementsToUse
                for k in range(0, amountOfInstElementsToUse):
                    strChunk = ''
                    for j in range(0, 4):
                        if c < strLength:
                            strChunk += self.value[c]
                            c+=1
                        else:
                            strChunk += ' '
                    pParams[k] = struct.unpack('i',strChunk)[0]
                
                instr = InstructionCall('setStringValues',self.ASTobj, deepness)
                instr.addParamRefVariable(RefVar(self, localVar))
                constIndex = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, 0, int)
                instr.addParamConst(RefConst(constIndex))
                posStart = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, cs, int)
                cs = c
                instr.addParamConst(RefConst(posStart))
                for p in pParams:
                    val = ASTinstructionParamConst(self.ASTobj.line, self.ASTobj.column, p, int)
                    instr.addParamConst(RefConst(val))
                # add the instruction
                setupCodeL.append(instr)
        else:
            raise exceptions.SyntaxError('internal error: unknown type for creating a start code: {et}'.format(et=self))

        return setupCodeL
# a List of variable defintions 
class VarDefList(object):
    def __init__ (self):
        self.vL = []
    
    def varExits(self, varDef):
        return varDef in self.vL

    def getList(self):
        return self.vL

    def findVariable (self, searchItem):
        indx = self.vL.index(searchItem) if searchItem in self.vL else None
        if indx is None:
            return None
        else:
            return self.vL[indx]
    
    def addVar(self, varDef):
        if not self.varExits(varDef):
            self.vL.append(varDef)
        else:
            v2 = self.findVariable(varDef)
            raise exceptions.SyntaxError('at {pos}: variable {var1Name} already declared at {pos2}'.format(pos=varDef.ASTobj.getPosStr(), var1Name=varDef.vName, pos2=v2.ASTobj.getPosStr()))
            
    
    def findConst (self, value, constType, exceptConst = None):
        # 1st get HAL type
        HALtype = gAssoConstPythonTypesToALDict.get(constType, None)
        if HALtype == None:
            raise exceptions.SyntaxError('internal error: unknown constant type "{vtype}"'.format(vtype=constType))
        return self.findConstWithHALtype(value, HALtype, exceptConst)
        
    def findConstWithHALtype (self, value, constHALType, exceptConst):
        for v in self.vL:
            if (v != exceptConst) and (isinstance(v, VarDefConstVariable) is True):
                if (v.vType == constHALType) and (v.value == value):
                    return v
        return None
        
    
    def createConst(self, value, constType, ASTitem):
        # search for the value
        r = self.findConst(value, constType, None)
        if r is not None:
            return r
        # we did not found a value of that type
        # ok let's create some
        ncv = VarDefConstVariable(value, constType, ASTitem)
        self.vL.append(ncv)
        return ncv
    
    # mergeing lists -> every duplicate value throws an error
    def mergeLists(self, vdL):
        for vd in vdL.vL:
            self.addVar(vd)
    
    #unites lists (wihtout error calles by double elements), returns a compressed variable list 
    def uniteLists(self, VarDefList2):
        for p in VarDefList2.getList():
            if self.findVariable(p) is None:
                self.addVar(p) 
        return self.compressConstants()
    
    def cloneListWithPrefix (self, prefix, excludeList):
        cvl = VarDefList()
        changeDict = {}
        for v in self.vL:
            if (v in excludeList):
                # cvl.vL.append(v)
                changeDict[v] = v
            elif (v.isGlobal() is True) or (isinstance(v, VarDefConstVariable) is True):
                cvl.vL.append(v)
                changeDict[v] = v
            else:
                nv = copy.copy(v)
                nv.vName = prefix + nv.vName
                cvl.vL.append(nv)
                changeDict[v] = nv 
        return cvl, changeDict

    # eleminates constants which are decclared 2 times
    def compressConstants(self):
        ConstMap = {}
        nVL = VarDefList()
        for v in self.vL:
            if isinstance(v, VarDefConstVariable) is True:
                r = nVL.findConstWithHALtype(v.value, v.vType, v)
                if r is not None:
                    ConstMap[v] = r
                else:
                    nVL.vL.append(v)
            else:
                nVL.vL.append(v)
        return nVL, ConstMap
    
        
        
# a class holding the reference to a variable
# defintion and the usage of it
class RefVar (object):
    def __init__ (self, varDef, ASTobj):
        self.varDef = varDef
        self.ASTobj = ASTobj
        
    def getVarDefName(self):
        return self.varDef.vName
    
    def getType(self, varDefL, typedefD):
        return self.ASTobj.getType(varDefL,typedefD)
    
    def getASTobj(self):
        return self.ASTobj
    
    def getVarDef(self):
        return self.varDef
    
    def __repr__ (self):
        var = self.ASTobj.getName()
        if self.varDef is None:
            varDef = 'None'
        else:
            varDef = self.varDef.getName()
        return '{var} -> {varDef}'.format(var=var, varDef=varDef)
    

class RefConst (object):
    def __init__ (self, ASTobj):
        self.ASTobj = ASTobj
        
    def getType(self, varDefL, typedefD):
        return gAssoConstPythonTypesToALDict.get(self.ASTobj.constType, None)

    def __repr__ (self):
        return '-> {refConst}'.format(refConst=self.ASTobj.getStrTypeName())
    
    def getValueStr (self):
        return str(self.ASTobj.getValue())
    
# ==========================================================
# lets create the tokenizer
# ==========================================================

reserved = {
    'typedef'       :   'typedef',
    'global'        :   'global',
    'local'         :   'local',
    'code'          :   'code',
    'function'      :   'function',
    'interface'     :   'interface',
    'main'          :   'main',
    'if'            :   'if',
    'else'          :   'else',
    'for'           :   'for',
    'while'         :   'while',
    'checkButtonPressed': 'checkButtonPressed',
    'update'        :   'update',
    }
    
tokens = [
    'lBrace',
    'rBrace',
    'lSoftBrace',
    'rSoftBrace',
    'lBracket',
    'rBracket',
    'comma',
    'semicolon',
    'name',
    'iNumber',
    'fNumber',
    'arrowLeft',
    'arrowRight',
    'not',
    'add',
    'sub',
    'mul',
    'div',
    'mod',
    'nEqual',
    'equal',
    'assign',
    'comment',
    'less',
    'lessEqual',
    'greater',
    'greaterEqual',
    'inc',
    'dec',
    'string',
    'addAssign',
    'point'        
    ] + list(reserved.values())

t_lBrace = '{' 
t_rBrace = '}'
t_lSoftBrace = '\(' 
t_rSoftBrace = '\)'
t_lBracket = '\['
t_rBracket = '\]'
t_nEqual = '!='
t_equal = '=='
t_assign = '='
t_comma = ','
t_semicolon = ';' 
t_ignore = ' \t'
t_arrowLeft = '>>'
t_arrowRight = '<<'
t_not = '!'
t_div = '/'
t_mul = '\*'
t_lessEqual = '<='
t_less = '<'
t_greaterEqual = '>='
t_greater = '>'
t_inc = '\+\+'
t_add = '\+'
t_dec = '--'
t_sub = '-'
t_addAssign = '\+='
t_point = '\.'
t_mod = '%'

def t_comment (t):
    r'(/\*(.|\n)*?\*/)|(//.*)'
    t.type = 'comment'
    l = len(t.value)
    if (t.value[0:2] == '//') :
        t.value = t.value[2:l]
    else :
        t.value = t.value[2:l-2]
    t.lexer.lineno += t.value.count('\n') 
    return t
    
def t_string (t):
    r'\"([^\\\n]|(\\.))*?\"'
    t.lexer.lineno += t.value.count('\n')
    # cut of the quotation mark
    l = len(t.value)
    t.value = t.value[1:l-1]
    # ok replace escape chars
    t.value = t.value.replace('\\n','\n')
    t.value = t.value.replace('\\t','\t')
    return t

def t_name(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = reserved.get(t.value,'name')    # Check for reserved words
    return t

def t_fNumber(t):
    r'[-+]?\d+\.\d+([eE][-+]?\d+)?'
    try:
        t.value = float(t.value)
    except ValueError:
        print("Integer value too large %d", t.value)
        t.value = 0
    return t

def t_iNumber(t):
    r'[-+]?\d+'
    try:
        t.value = int(t.value)
    except ValueError:
        print("Integer value too large %d", t.value)
        t.value = 0
    return t
    
# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# =====================================================
# the parser
# =====================================================

# Parsing rules

precedence = (
#         ('left', 'LOR'),
#         ('left', 'LAND'),
#         ('left', 'OR'),
#         ('left', 'XOR'),
#         ('left', 'AND'),
        ('left', 'equal', 'nEqual'),
        ('left', 'greater', 'greaterEqual', 'less', 'lessEqual'),
#        ('left', 'RSHIFT', 'LSHIFT'),
        ('left', 'add', 'sub'),
        ('left', 'mul', 'div', 'mod'),
        ('right', 'not'),
        ('nonassoc', 'assign'),
    )


# 1. start rules
def p_startElements(p):
    """start :
        | startElements"""
    p[0] = p[1]
        
def p_startElementsList(p):
    """startElements : startEle
        | startElements startEle"""
    l = len(p)
    if (l == 2) :
        p[0] = ASTobjList([p[1]])
    else:
        p[1].append(p[2])
        p[0] = p[1] 

def p_startComment (p):
    'startEle : comment'
    p[0] = ASTcomment (p.lineno(1) ,p.lexpos(1), p[1])


def p_startGlobVar(p):
    'startEle : global lBrace varDeclList rBrace'
    p[0] = p[3]
    
def p_startTypedef(p):
    'startEle : typedef name lBrace varDeclList rBrace'
    p[0] = ASTtypedef (p.lineno(1) ,p.lexpos(1), p[2], p[4])

def p_startFunction(p):
    'startEle : function name lBrace interfaceVarListStm localVarListStm codeListStm rBrace'
    p[0] = ASTfunction(p.lineno(1) ,p.lexpos(1), p[2], p[4], p[5], p[6])

def p_mainStm (p):
    'startEle : main lSoftBrace name rSoftBrace lBrace localVarListStm codeListStm rBrace'
    p[0] = ASTmain(p.lineno(1) ,p.lexpos(1), p[3], p[6] ,p[7])

# 2. variable declaration

def p_varDeclList_Empty(p):
    'varDeclList :'
    p[0] = ASTobjList([])

def p_varDeclList_List(p):
    'varDeclList : varDeclListElementL'
    p[0] = p[1]


def p_varDecl_list(p):
    """varDeclListElementL : varDecl
        | varDeclListElementL varDecl"""
    l = len(p)
    if (l == 2) :
        p[0] = ASTobjList([p[1]])
    else:
        p[1].append(p[2])
        p[0] = p[1] 

  
def p_varDecl_Easy(p):
    'varDecl : name name semicolon'
    p[0] = ASTvariableDef (p.lineno(1) ,p.lexpos(1), p[2], p[1], 1)

def p_varDecl_Amount(p):
    'varDecl : name name lBracket iNumber rBracket semicolon'
    p[0] = ASTvariableDef (p.lineno(1) ,p.lexpos(1), p[2], p[1], p[4])

def p_varDecl_Comment(p):
    'varDecl : comment'
    p[0] = ASTcomment (p.lineno(1) ,p.lexpos(1), p[1])

# 3. function declaration

# 3.1. interface rules
def p_interfaceVarListStm (p):
    'interfaceVarListStm : interface lBrace interfaceVarListDeclList rBrace'
    p[0] = p[3]

def p_interfaceVarListDeclList_Lempty(p):
    'interfaceVarListDeclList :'
    p[0] = ASTobjList([])

def p_interfaceVarListDeclList_LtoList(p):
    'interfaceVarListDeclList : interfaceVarListDeclL'
    p[0] = p[1]


def p_interfaceVarListDeclList_list(p):
    """interfaceVarListDeclL : interfaceVarListDecl
        | interfaceVarListDeclL interfaceVarListDecl"""
    l = len(p)
    if (l == 2) :
        p[0] = ASTobjList([p[1]])
    else:
        p[1].append(p[2])
        p[0] = p[1] 

def p_interfaceVarListDecl_interfaceVarEasy(p):
    'interfaceVarListDecl : name name name semicolon'
    p[0] = ASTfuncParameter(p.lineno(1) ,p.lexpos(1), p[3], p[2], 1, p[1])

def p_interfaceVarListDecl_interfaceVarComplete(p):
    'interfaceVarListDecl : name name name lBracket iNumber rBracket semicolon'
    p[0] = ASTfuncParameter(p.lineno(1) ,p.lexpos(1), p[3], p[2], p[5], p[1])


def p_interfaceVarListDecl_comment(p):
    'interfaceVarListDecl : comment'
    p[0] = ASTcomment (p.lineno(1) ,p.lexpos(1), p[1])

# 3.2 local variables
def p_localVarStm(p):
    'localVarListStm : local lBrace varDeclList rBrace'
    p[0] = p[3]

# 3.3 code
def p_codeListStm (p):
    'codeListStm : code lBrace instrStatementList rBrace'
    p[0] = p[3]

# 4. main declaration

# instructions
def p_instrStatemenetsList_empty(p):
    'instrStatementList :'
    p[0] = ASTobjList([])

def p_instrStatemenetsList_List(p):
    'instrStatementList : instrStatementListL'
    p[0] = p[1]


def p_instrStatemenetsList_ListList(p):
    """instrStatementListL : statement
            | instrStatementListL statement"""
    l = len(p)
    if (l == 2) :
        p[0] = ASTobjList([p[1]])
    else:
        p[1].append(p[2])
        p[0] = p[1] 

#3.2) statements

#3.2.1) expressions

# variables

def p_varDefWithoutIndx(p):
    'var : varDef'
    p[0] = p[1]
    
def p_varDefWithIndx(p):
    'var : varDef lBracket iNumber rBracket'
    p[1].setIndex(p[3])
    p[0] = p[1]
    

def p_varDef(p):
    'varDef : name subVarVals'
    p[0] = ASTinstructionParamRefVar(p.lineno(1) ,p.lexpos(1), p[1], p[2], 0)

def p_varSubValues_empty(p):
    'subVarVals :'
    p[0] = []

def p_varSubValues_list(p):
    'subVarVals : varSubValuesList'
    p[0] = p[1]
    
def p_varSubValuesList(p):
    """varSubValuesList : point name
        | varSubValuesList point name"""
    l = len(p)
    if l == 3:
        p[0] = [p[2]]
    else:
        p[1].append(p[3])
        p[0] = p[1]


# numbers
def p_constINumber (p):
    'constINumber : iNumber'
    p[0] = ASTinstructionParamConst(p.lineno(1) ,p.lexpos(1), p[1], int)

def p_constFNumber (p):
    'constFNumber : fNumber'
    p[0] = ASTinstructionParamConst(p.lineno(1) ,p.lexpos(1), p[1], float)

# literals
def p_constString (p):
    'constString : string'
    p[0] = ASTinstructionParamConst(p.lineno(1) ,p.lexpos(1), p[1], str)

def p_const(p):
    """const : constINumber
        | constFNumber
        | constString"""
    p[0] = p[1]

def p_argument (p):
    """argument : var
            | const"""
    p[0] = p[1]


# operations on variables and numbers    
def p_stmAdd (p):
    'statement : var assign argument add argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'add', [p[1], p[3], p[5]])

def p_stmSub (p):
    'statement : var assign argument sub argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'sub', [p[1], p[3], p[5]])

def p_stmMul (p):
    'statement : var assign argument mul argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'mul', [p[1], p[3], p[5]])

def p_stmDiv (p):
    'statement : var assign argument div argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'div', [p[1], p[3], p[5]])

def p_stmMod (p):
    'statement : var assign argument mod argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'mod', [p[1], p[3], p[5]])

def p_stmInc (p):
    'statement : var inc semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'inc', [p[1]])

def p_stmDec (p):
    'statement : var dec semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'dec', [p[1]])

def p_stmAddAssign (p):
    'statement : var addAssign argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'addAssign', [p[1], p[3]])

def p_stmAssign (p):
    'statement : var assign argument semicolon'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'assign', [p[1], p[3]])

    
# boolean expressions
def p_expbNot (p):
    'expb : not argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), 'not', [p[1]])

def p_expbNequal(p):
    'expb : argument nEqual argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '!=', [p[1], p[3]])

def p_expbEqual(p):
    'expb : argument equal argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '==', [p[1], p[3]])

def p_expbLess(p):
    'expb : argument less argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '<', [p[1], p[3]])

def p_expbLessEqual(p):
    'expb : argument lessEqual argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '<=', [p[1], p[3]])

def p_expbGreater(p):
    'expb : argument greater argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '>', [p[1], p[3]])

def p_expbGreaterEqual(p):
    'expb : argument greaterEqual argument'
    p[0] = ASTinstructionArithmeticBool(p.lineno(1) ,p.lexpos(1), '>=', [p[1], p[3]])

# 3.2.3) conditions
def p_stmIfElse (p):
    'statement : if lBracket expb rBracket lBrace instrStatementListL rBrace else lBrace instrStatementListL rBrace'
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), p[3], p[6], p[10], False, None)

def p_stmIf (p):
    'statement : if lBracket expb rBracket lBrace instrStatementListL rBrace'
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), p[3], p[6], None, False, None)


    
# 3.2.5) for loop
def p_stmForLoop (p):
    'statement : for lBracket statement expb semicolon statement rBracket lBrace instrStatementListL rBrace'
    p[0] = [
            p[3],
            ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), p[5], p[10], None, True, p[7])
        ]

# 3.2.5.2) for loop endless
def p_stmForLoopEndless (p):
    'statement : for lBracket semicolon semicolon rBracket lBrace instrStatementListL rBrace'
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), None , p[7], None, True, None)

#3.2.5.3 while loop
def p_stmWhileLoop (p):
    'statement : while lBracket expb rBracket lBrace instrStatementListL rBrace'
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), p[3] ,p[6], None, True, None)

#3.2.5.4 while loop endless
def p_stmWhileLoopEndless (p):
    'statement : while lBracket rBracket lBrace instrStatementListL rBrace'
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), None ,p[5], None, True, None)

# 3.2.6) function call
def p_stmFunctionCall (p):
    'statement : lBracket fcParamListCompl rBracket assign name lBracket fcParamListCompl rBracket semicolon'
    p[0] = ASTinstructionFunctionCall(p.lineno(1) ,p.lexpos(1), p[5], p[2], p[7])

def p_fcParamListCompl_empty(p):
    'fcParamListCompl :'
    p[0] = ASTobjList([])

def p_fcParamListCompl_list(p):
    'fcParamListCompl : fcParamList'
    p[0] = p[1]

def p_fcParamList (p):
    """fcParamList : argument
            | fcParamList comma argument 
    """
    l = len(p)
    if (l == 2) :
        p[0] = ASTobjList([p[1]])
    else:
        p[1].append(p[3])
        p[0] = p[1] 

# 3.2.7 comment
def p_stmComment (p):
    'statement : comment'
    p[0] = ASTcomment(p.lineno(1) ,p.lexpos(1), p[1])

# 3.2.8 variable operations
def p_stmVariableTypeOperation (p):
    'statement : name lBracket operationParamListL rBracket semicolon'
    p[0] = ASTvariableTypeOperation(p.lineno(1) ,p.lexpos(1), p[1],p[3])

def p_operationParamListL_empty(p):
    'operationParamListL :'
    p[0] = ASTobjList([])

def p_operationParamListL_list(p):
    'operationParamListL : operationParamList'
    p[0] = p[1]

def p_operationParamList (p):
    """operationParamList : name assign argument
        | operationParamList comma name assign argument
    """ 
    l = len(p)
    if (l == 4) :
        p[0] = ASTobjList([ASTvariableOperationParam(p.lineno(1) ,p.lexpos(1), p[1], p[3])])
    else:
        p[1].append(ASTvariableOperationParam(p.lineno(3) ,p.lexpos(3), p[3], p[5]))
        p[0] = p[1]

def p_checkButtonPressed (p):
    'statement : checkButtonPressed lSoftBrace var rSoftBrace lBrace instrStatementListL rBrace'
    instrCBparams = ASTobjList([
            ASTvariableOperationParam(p.lineno(1) ,p.lexpos(1), 'func' , ASTinstructionParamRefVar(p.lineno(1) ,p.lexpos(1),'checkButton')),
            ASTvariableOperationParam(p.lineno(1) ,p.lexpos(1), 'obj' , p[3])
        ])
    
    instrCheckBP = ASTvariableTypeOperation(p.lineno(1) ,p.lexpos(1), 'ui', instrCBparams)
    p[0] = ASTConditionalBlock(p.lineno(1) ,p.lexpos(1), instrCheckBP ,p[6], None, False, None)

def p_update (p):
    'statement : update lSoftBrace var rSoftBrace semicolon'
    p[0] = ASTinstruction(p.lineno(1) ,p.lexpos(1), 'update', [p[3]])


# error rule
def p_error(p):
    text = 'Syntax error at Line: {line} pos: {pos} at symbol "{symb}"'.format(line= p.lineno, pos=p.lexpos, symb=p.type)
    raise exceptions.SyntaxError(text)


# =============================================
# AST transformations
# =============================================

# create a variable dict
# recursive function
def _AST_buildVariableDict (astElement, vDict):
    # stop condition
    if isinstance(astElement, ASTvariableDef) is True:
        r = vDict.get(astElement.varName, None)
        if r is not None:
            raise exceptions.SyntaxError('at {pos}: variable "{varName}" has been declared before({posPrev}) .'.format(varName=astElement.varName,pos=astElement.getPosStr(),posPrev=r.getPosStr()))
        else:
            vDict[astElement.varName] = astElement
    #recursive part
    elif isinstance(astElement, ASTobjList) is True:
        for astItem in astElement.getList():
            _AST_buildVariableDict(astItem, vDict)


# transfer the AST Variables into an internal list
def _VariableDeclaration_TransferIntoList (ASTvarDict, globalFlag):
    vdl = VarDefList()
    for key, ASTitem in ASTvarDict.items():
        varDef = VarDef(ASTitem, globalFlag)
        vdl.addVar(varDef)
    return vdl

#
def _AST_buildFunctionVariableMapping (inOutL):
    inD = {}
    outD = {}
    ic = 0
    oc = 0
    L = inOutL.getList()
    for p in L:
        if isinstance(p, ASTfuncParameter) is True:
            if p.ioType == 'in':
                inD[ic] = p
                ic += 1
            elif p.ioType == 'out':
                outD[oc] = p
                oc += 1
            else:
                raise exceptions.SyntaxError('at {pos}: function parameter class "{cl}" is not (in/out) .'.format(pos=p.getPosStr(),cl = p.ioType))
    return inD, outD

# create a dict with function parameters
# recursive function
def _AST_buildFuncParamterDict (astElement, vDict):
    # stop condition
    if isinstance(astElement, ASTfuncParameter) is True:
        r = vDict.get(astElement.varName, None)
        if r is not None:
            raise exceptions.SyntaxError('at {pos}: function parameter "{varName}" has been declared before({posPrev}) .'.format(varName=astElement.varName,pos=astElement.getPosStr(),posPrev=r.getPosStr()))
        else:
            vDict[astElement.varName] = astElement
    #recursive part
    elif isinstance(astElement, ASTobjList) is True:
        for astItem in astElement.getList():
            _AST_buildFuncParamterDict(astItem, vDict)



# create the type dict
# recursive function
def _AST_buildTypes (astElement, tvDict):
    # stop condition
    if isinstance(astElement, ASTtypedef) is True:
        # check if there is an HAL type
        r = _HAL_findVarTypeByName(astElement.typeName)
        if r is not None:
            raise exceptions.SyntaxError('at {pos}: type "{varName}" exists already as HAL variable type.'.format(varName=astElement.typeName,pos=astElement.getPosStr()))
        r = tvDict.get(astElement.typeName, None)
        if r is not None:
            raise exceptions.SyntaxError('at {pos}: type "{varName}" has been declared before({posPrev}) .'.format(varName=astElement.typeName,pos=astElement.getPosStr(),posPrev=r.getPosStr()))
        else:
            tvDict[astElement.typeName] = astElement
    #recursive part
    elif isinstance(astElement, ASTobjList) is True:
        for astItem in astElement.getList():
            _AST_buildTypes(astItem, tvDict)

# create the function dict
# recursive function
def _AST_buildFunctions (astElement, fDict):
    # stop condition
    if isinstance(astElement, ASTfunction) is True:
        r = fDict.get(astElement.fName, None)
        if r is not None:
            raise exceptions.SyntaxError('at {pos}: function "{fName}"has been declared before({beforePos}).'.format(pos=astElement.getPosStr(), fName=astElement.fName, beforePos=r.getPosStr()))
        else:
            fDict[astElement.fName] = astElement
    #recursive part
    elif isinstance(astElement, ASTobjList) is True:
        for astItem in astElement.getList():
            _AST_buildFunctions(astItem, fDict)

# creates a instruction list
# recursive function
def _AST_buildInstructions (astElement, varDefL, typedefD, deepness):
    # stop condition
    if isinstance(astElement, ASTtranslatable) is True:
        r = astElement.transformASTtoInstructionCall(varDefL, typedefD, deepness)
        if isinstance(r, list) is True:
            return r
        else:
            return [r]
    #recursive part
    elif isinstance(astElement, ASTobjList) is True:
        tL = []
        for astItem in astElement.getList():
            r = _AST_buildInstructions(astItem, varDefL, typedefD, deepness)
            tL = tL + r
        return tL
    # handle other items == ignore
    return []


# =============================================
# type definition operations
# =============================================

# compiles the typedef into a dict
# return dict structure
# key = type name
# item = ASTitem, subKeyDict
# subKeyDict:
# key = name
# item = ASTitem
def _compile_typedefsIntoDict (tvDict):
    ctd = {}
    for key, item in tvDict.items():
        subValL = item.typedefASTInstrL.getList()
        subValD = {}
        for sv in subValL:
            if isinstance(sv, ASTvariableDef) is True:
                r = subValD.get(sv.varName, None)
                if r is not None:
                    raise exceptions.SyntaxError('at {pos}: sub value "{varName}" has been declared before({posPrev}) .'.format(varName=sv.varName,pos=sv.getPosStr(),posPrev=r.getPosStr()))
                else:
                    subValD[sv.varName] = sv
        ctd[key] = (item, subValD)
    return ctd

# recursive function to unroll the type
def _compile_typedefUnrollVarDef(ASTitem, tvDict):
    # break condition
    # check if it a basic type
    r = _HAL_findVarTypeByName(ASTitem.varType)
    if r is not None:
        return ASTitem
    # recursive condition
    # check if there is an typedef for the name
    r = tvDict.get(ASTitem.varType, None)
    if r is None:
        raise exceptions.SyntaxError('at {pos}: type of the sub value "{varName}" is not a basic type or a user defined type.'.format(varName=ASTitem.varName,pos=ASTitem.getPosStr()))
    # ok lets iterate
    item, SubValD = r
    urD = {}
    for svN, svItem in SubValD.items():
        urD[svN] = _compile_typedefUnrollVarDef(svItem, tvDict)
    return urD

# roll out the subvalues
def _compile_typedefBuildSubstitutionPath (tvSubTypesD):
    spd = {}
    for key, item in tvSubTypesD.items():
        keyAstItem, subvalD = item
        unrollD = {}
        for subvalName, subvalItem in subvalD.items(): 
            unrollD[subvalName] = _compile_typedefUnrollVarDef(subvalItem, tvSubTypesD)
        spd[key] = unrollD
    return spd

# compiles the function calls in one function
# cfL - compiled function list
# variablePrefix - variable prefix
# pfD - precompiled function dict
# fname- function name
def _compile_functionCallsByReplaceing (pfD, fname, enrolledFunctionsD):
    nfcL = []
    # get the function data
    (ASTitem, varmap, varDefL, fcL, fcLDependencies) = pfD[fname]
    # varprefix count
    varPreFixCounter = 1
    
    # now iterate through the function call list
    for fc in fcL:
        if isinstance(fc, InstructionCallFunction) is True:
            # find the enrolled function
            funcTempl = enrolledFunctionsD.get(fc.funcName ,None)
            if funcTempl is None:
                raise exceptions.SyntaxError('at {pos}: function "{fname}" is not defined.'.format(pos=ASTitem.getPosStr(), fname=fname))
            # transfom the inputs
            iL = []
            for p in fc.inputs:
                if isinstance(p, ASTinstructionParamRefVar) is True:
                    # find variable definition
                    vardef = varDefL.findVariable(p)
                    # build reference
                    varRef = RefVar(vardef, p)
                    # add to list
                    iL.append (varRef)
                elif isinstance (p, ASTinstructionParamConst) is True:
                    iL.append (RefConst(p))
                else:
                    raise exceptions.SyntaxError('internal error! type of input parameter is unknown ({p})'.format(p=p))
            # transform the outputs
            oL = []
            for p in fc.outputs:
                if isinstance(p, ASTinstructionParamRefVar) is True:
                    # find variable definition
                    vardef = varDefL.findVariable(p)
                    # build reference
                    varRef = RefVar(vardef, p)
                    # add to list
                    oL.append (varRef)
                elif isinstance (p, ASTinstructionParamConst) is True:
                    oL.append (RefConst(p))
                else:
                    raise exceptions.SyntaxError('internal error! type of output parameter is unknown ({p})'.format(p=p))
            # create a varaible prefix
            variablePrefix = '#fv_{fname}_'.format(fname=fc.funcName)
            # transform the instructions
            funcInstrL, nVL = _process_substitudeFunctionCall(enrolledFunctionsD, fc.funcName, variablePrefix, iL, oL, fc.ASTobj)
             
            # add the variable list
            nVL, mapping = varDefL.uniteLists(nVL)
            _process_functionCallListReplaceConstants(funcInstrL, nVL, mapping)
            
            nfcL += funcInstrL
        else:
            nfcL.append(fc)
    
    # now compress constants
    varDefL, mapping  = varDefL.compressConstants()
    _process_functionCallListReplaceConstants(nfcL, varDefL, mapping)
    
    return nfcL, varDefL
    

# =============================================
# compile processes of type defs 
# =============================================

# recursive function crawling throuth the types and checking it against the match type
def _process_checkRingReferencesInTypeDefs_CrawlerFunc (tvSubTypes, subTypeDict, matchTypeStr):
    for subTypeName, subTypeItem in subTypeDict.items():
        # check if a subvalue has the type of the match string
        if subTypeItem.varType == matchTypeStr:
            return (True, subTypeItem)
        # no -> lets check if the subtype is a typedef
        r = tvSubTypes.get(subTypeItem.varType, None)
        if r is not None:
            # ok is a user type def
            # lets check this type against the match type str
            (ASTitem, subItemDict) = r
            return _process_checkRingReferencesInTypeDefs_CrawlerFunc(tvSubTypes, subItemDict, matchTypeStr)
    return (False, None)

# checks for ring references in types
def _process_checkRingReferencesInTypeDefs (tvSubTypes):
    for typeName, (ASTitem, subItemDict) in tvSubTypes.items():
        r, errorItem = _process_checkRingReferencesInTypeDefs_CrawlerFunc(tvSubTypes, subItemDict, typeName)
        if r == True:
            raise exceptions.SyntaxError('at {pos}: circular refernce in type definition of "{typeName}" at "{errorItem}"({errorPos}).'.format(typeName=typeName,pos=ASTitem.getPosStr(),errorItem=errorItem.varName, errorPos=errorItem.getPosStr()))

# creates the type dict and unrolles it
def _process_createTypeDictAndunrollTypes (AST):
    logging.info ('build user defined types')

    logging.log (10, 'collect all types into one dict')
    tvDict = {}
    _AST_buildTypes(AST, tvDict)
    logging.log (10, 'build subtype dict')
    tvSubTypes = _compile_typedefsIntoDict(tvDict)
    logging.log (10, 'check type ring references')
    # this functions throws an syntax error if it fails
    _process_checkRingReferencesInTypeDefs (tvSubTypes)
    
    logging.log (10, 'unroll subtypes')
    tvUnrolled = _compile_typedefBuildSubstitutionPath(tvSubTypes)
    logging.log (10, 'finished to build type tree')
    return tvUnrolled

# create a varaible defintion from a type entry 
def _process_createVarDefsFromTypeDict (varName, typeName, amount, td, varSubnameDelemitter):
    tde = td.get(typeName, None)
    subvarL = []
    for key, item in tde.items():
        if isinstance(item, ASTvariableDef) is True:
            subvarName = '{varname}{delm}{subvarname}'.format(varname=varName, delm=varSubnameDelemitter, subvarname=item.varName)
            subvarAmount = amount * item.amount
            subvarType = item.varType
            subvarL.append((subvarName, subvarAmount, subvarType))
        else:
            raise 'Error'
    return subvarL

# =============================================
# compile processes of functions 
# =============================================

# runs through the AST picking the variable entries
# check the types and if they have been declared before
def _process_checkVariableAgainstTypes (varDict, typedefD):
    for key, ASTitem in varDict.items():
        if (isinstance(ASTitem, ASTvariableDef) is True) or (isinstance(ASTitem, ASTfuncParameter)):
            typeDefCh = typedefD.get(ASTitem.varType, None)
            varTypeCh = _HAL_findVarTypeByName(ASTitem.varType)
            if (typeDefCh is None) and (varTypeCh is None):
                raise exceptions.SyntaxError('at {pos}: unknown type "{varType} for variable "{varName}".'.format(pos=ASTitem.getPosStr(), varType=ASTitem.varType, varName=ASTitem.varName))

# # join variable dictionary
# def _process_joinVariableDict (vd1, vd2):
#     for key, item in vd1.items():
#         r = vd2.get(key, None)
#         if r is not None:
#             raise exceptions.SyntaxError('at {pos}: variable "{varName}"has been declared before({beforePos}).'.format(pos=item.getPosStr(), varName=item.varName, beforePos=r.getPosStr()))
#     return dict(vd1.items() + vd2.items())

# transform AST function calls
def _process_translateASTFunctionCall (ASTfcL, varL, typedefD, deepness):
    fcL = []
    fcLDependencies = []
    # build code
    fcL = _AST_buildInstructions(ASTfcL, varL, typedefD, deepness)
    # build depenencies
    for item in fcL:
        if isinstance(item, InstructionCallFunction) is True:
            fcLDependencies.append(item.funcName)
    return fcL, set(fcLDependencies)


# creates a function dictionaray with variable dictionaries
def _process_preprocessASTFunctionDict (fd, typedefD, gVL):
    pfd = {}
    i = 1
    for key, ASTitem in fd.items():
        if isinstance(ASTitem, ASTfunction) is True:
            # build varaible dicts
            ioParamD = {}
            _AST_buildFuncParamterDict(ASTitem.inpOutpL, ioParamD)
            locVarD = {}
            _AST_buildVariableDict(ASTitem.localVarL, locVarD)
            
            varMapping = _AST_buildFunctionVariableMapping(ASTitem.inpOutpL)
            
            _process_checkVariableAgainstTypes(ioParamD, typedefD)
            _process_checkVariableAgainstTypes(locVarD, typedefD)
            
            locVarL = _VariableDeclaration_TransferIntoList(locVarD, False)
            ioParamL = _VariableDeclaration_TransferIntoList(ioParamD, False)
            
            # and merge the dicts
            locVarL.mergeLists(ioParamL)
            locVarL.mergeLists(gVL)
                        
            fcL, fcLDependencies = _process_translateASTFunctionCall(ASTitem.instructionL, locVarL, typedefD, 0)
            pfd[key] = (ASTitem, varMapping, locVarL, fcL, fcLDependencies)
    return pfd


def _process_crawlCallingTree (pfd, fname, subName):
    callingL = pfd[subName]
    if fname in callingL:
        return True, [fname]
    for call in callingL:
        r, cL = _process_crawlCallingTree(pfd, fname, call)
        if r == True:
            # insert the calling function at the start
            cL.insert(0, call)
            return True, cL
    return (False, None) 

# enrol dependencies: means the calling tree is resolved for each function
def _process_resolveCallingTree(pfD):
    # first make copy
    solveD = {}
    for fname, (ASTitem, varMapping, varDict, codeL, dependenciesL) in pfD.items():
        solveD[fname] = list(set(dependenciesL))
    # now work with the copied list
    
    # cross reference check
    resolvedD = {}
    for fname, depL in solveD.items():
        resolvedD[fname] = []

    # reference checks
    for fname, depL in solveD.items():
        r, cL = _process_crawlCallingTree(solveD, fname, fname)
        if r == True:
            errorPath = '"{p}"'.format(p=fname)
            for p in cL:
                errorPath += '->"{p}"'.format(p=p)
            raise exceptions.SyntaxError('function "{fname}" calls it self directly/indirectly. This is not allowed. The call list is: {cl}.'.format(fname=fname, cl=errorPath))

    # build reference lists
    while solveD != {}:
        removeL = []
        # 1st check witch elements have no more references
        for fname, depL in solveD.items():
            if not depL:
                removeL.append(fname)
        # 2nd remove the dependencies in the other lists
        for removeName in removeL: 
            for fname, depL in solveD.items():
                if removeName in depL:
                    # remove it from the source list
                    depL.remove(removeName)
                    # add it to the function depending on it
                    resolvedD[fname].append(removeName)
                    # add the dependencies of the function added to the list
                    resolvedD[fname] += resolvedD[removeName]
                    # remove all double entries
                    resolvedD[fname] = list(set(resolvedD[fname]))
        # 3rd remove elements from the solve list
        for removeName in removeL:
            del solveD[removeName]
    # return the solved dependencies dict
    return resolvedD

# builds a list which contains the names of the functions in order to solve theire function calls    
def _process_BuildSolvingStragegy(ctD, fD):
    # the solving list
    sL = []
    while ctD != {}:
        for fname, depL in ctD.items():
            # check if the function is calling it self
            if fname in depL:
                astI = fd[fname][0]
                raise exceptions.SyntaxError('at {pos}: the function "{fname}" calls it self directly or via a call of an other function.'.format(pos=astI.getPosStr(), fname=fname))
            # if the depL is empty remove put the function to the solving list and delete all references at the dictionary to the function
            if depL == []:
                # solved!
                sL.append(fname)
                # remove it
                del ctD[fname]
                # remove all references
                for fname2, depL2 in ctD.items():
                    if fname in depL2: depL2.remove(fname)
    return sL


# clones a function (same code but other variables, lables)
def _process_substitudeFunctionCall (enrolledFunctionsD, funcName, varPrefix, inpParams, outpParams, ASTfuncCall):
    (ASTitem, (InVarDm, OutVarDm), varDefL, fcL) = enrolledFunctionsD[funcName]
    
    # 1.) variable defs
    # clone variable def list and add a prefix
    excludeList = []
    for (pos, var) in InVarDm.items():
        p = varDefL.findVariable(var.varName)
        excludeList.append(p)

    for (pos, var) in OutVarDm.items():
        p = varDefL.findVariable(var.varName)
        excludeList.append(p)
        
    enrolledVL, ReplD = varDefL.cloneListWithPrefix(varPrefix, excludeList)
    
    # 2.) Paramreference Replacement dict
    # replacement list for the inputs / ouputs
    # 2.1) for the inputs

    i = 0
    for p in inpParams:
        v = varDefL.findVariable(InVarDm[i].varName)
        ReplD[v] = p
        i += 1
    # 2.2) for the outputs        
    i = 0
    for p in outpParams:
        v = varDefL.findVariable(OutVarDm[i].varName)
        ReplD[v] = p
        i += 1
    
    # 2.) create new label dict
    labelAssoD = {}
    for fc in fcL:
        if isinstance(fc, InstructionLabel):
            if fc not in labelAssoD:
                labelAssoD[fc] = InstructionLabel(fc.deepness)
    # 3.) copy instructions
    # new function call list
    nfcL =[]
    for fc in fcL:
        if isinstance(fc, InstructionCall) is True:
            # 'copy' old instruction
            instr = InstructionCall(fc.fname, fc.ASTitem, fc.deepness)
            # and reset the parameters
            for (pid, pASTitem) in fc.getParamList():
                # check if we have to replace the reference to the variable defintion
                if isinstance(pASTitem,RefVar) is True: 
                    newVarDef = ReplD.get(pASTitem.getVarDef(), None)
                    if newVarDef is None:
                        newPastItem = enrolledVL.findVariable(pASTitem)
                    else:
                        if isinstance(newVarDef, RefVar):
                            newPastItem = newVarDef
                        elif isinstance(newVarDef, VarDef):
                            newPastItem = RefVar(newVarDef, pASTitem.getASTobj())
                        else:
                            raise exceptions.SyntaxError('internal error: replacement type unknown')
                elif isinstance(pASTitem,RefConst) is True:
                    newPastItem = pASTitem
                # if it is a label -> lookup at the label dict
                elif isinstance(pASTitem,InstructionLabel) is True:
                    newPastItem = labelAssoD[pASTitem]
                # check for 'unconverted parameters'
                elif isinstance(pASTitem, ASTinstructionParamRefVar) is True:
                    varDef = enrolledVL.findVariable(pASTitem)
                    newPastItem = RefVar(varDef, pASTitem)
                elif isinstance(pASTitem, ASTinstructionParamConst) is True:
                    newPastItem = RefConst(pASTitem)
                elif isinstance(pASTitem, VarDefConstVariable) is True:
                    varDefConst = enrolledVL.findVariable(pASTitem)
                    newPastItem = RefVar(varDefConst, pASTitem)
                else:
                    raise exceptions.SyntaxError('internal error: unknown function parameter')
                # and add the transformed parameterto the instruction params
                instr.getParamList().append([pid, newPastItem])
            # instruction building is finished    
            nfcL.append(instr)
                
        elif isinstance(fc, InstructionCallFunction) is True:
            raise exceptions.SyntaxError('internal error: there should be no function call left')

        elif isinstance(fc, InstructionLabel) is True:
            # substitude label
            nfcL.append(labelAssoD[fc])
        else:
            raise exceptions.SyntaxError('internal error: unknown function call class "{fc}"'.format(fc))
    
       
    return nfcL, enrolledVL

# replaces constants at the replacement mapping dict by MUTAING the fcunction call (at the fcL)
def _process_functionCallListReplaceConstants(fcL, vL, repLMapping):
    if len(repLMapping) > 0:
        for fc in fcL:
            if isinstance(fc, InstructionCall) is True:
                i = 0
                for pid, param in fc.getParamList():
                    if isinstance(param, RefVar) is True:
                        varDefObj = param.getVarDef()
                        if isinstance(varDefObj,VarDefConstVariable) is True:
                            newVarDef = repLMapping.get(varDefObj, None)
                            if newVarDef is not None:
                                fc.getParamList()[i][1] = newVarDef
                    i += 1


def _process_orderVariableList(vL):
    ovL = []
    dummyL = []
    # first add all global variables
    for v in vL.getList():
        if v.isGlobal() is True:
            ovL.append(v)
        else:
            dummyL.append(v)
    
    ovL += dummyL
    return ovL
    
        

# processes the functions
def _process_functions (AST, typedefD, gVL):
    logging.info ('build functions')

    # flaten AST tree
    logging.log (10, 'flaten AST')
    fd = {}
    _AST_buildFunctions(AST, fd)
    # preprocess
    logging.log (10, 'preprocess functions')
    pfD = _process_preprocessASTFunctionDict(fd, typedefD, gVL)
    
    # solve depenenies
    ctD = _process_resolveCallingTree(pfD)
    ssL = _process_BuildSolvingStragegy(ctD, pfD)

    # now create the functions
    # compilied function list
    enrolledFunctionsD = {}
    for ss in ssL:
        logging.log (10, 'enrole function "{fname}"'.format(fname=ss))
        (ASTitem, varmap, vd, fcL, fcLDependencies) = pfD[ss]

        enrolledFCL, enrolledVL = _compile_functionCallsByReplaceing(pfD, ss, enrolledFunctionsD)
        enrolledFunctionsD[ss] = (ASTitem, varmap, enrolledVL, enrolledFCL)

    logging.log (10, 'get main targets')
    # get the main functions
    mfL = []
    for ASTitem in AST.getList():
        if isinstance(ASTitem,ASTmain) is True:
            mfL.append(ASTitem.fName)
    
    # finalie the functions
    logging.log (10, 'finalize main functions')
    targetD = {}
    for mf in mfL:
        # get the data
        (ASTitem, varmap, enrolledVL, enrolledFCL) = enrolledFunctionsD[mf]
        # 
        vL = _process_orderVariableList(enrolledVL)

        # build extra constant code
        extraStartCode = []
        for v in enrolledVL.getList():
            if isinstance(v, VarDefConstVariable) is True:
                extraStartCode += v.createSetupCode(0)
        # enrole types in the var list
        evL = []
        gVamount = 0
        for v in vL:
            (vtid,) = gHALvidD.get(v.getType(), (None, ))
            if vtid is None:
                # get the list
                vdl = _process_createVarDefsFromTypeDict(v.getName(), v.getType(), v.getAmount(), typedefD, gSubVarDelim)
                # now iterate
                for svName, svAmount, svType in vdl:
                    evL.append((svName, svType, svAmount))
                if v.isGlobal() is True:
                    gVamount = len(vdl)
            else:
                evL.append((v.getName(), v.getType(), v.getAmount()))
                if v.isGlobal() is True:
                    gVamount += 1
        
        
        targetD[mf] = (extraStartCode + enrolledFCL, evL, gVamount)
        
    return targetD


# =============================================
# sinks for translated functions
# =============================================

# print code to an I/O device
def _sink_print(fname, fcL, vL, dest=sys.stdout):
    dest.write('function "{fname}"\nvariables:\n'.format(fname=fname))
    indx = 0
    for item in vL:
        dest.write('{indx}: {item}'.format(indx=indx, item=item))
        dest.write('\n')
        indx += 1
    
    indx = 0
    dest.write('code:\n'.format(fname=fname))
    for item in fcL:
        dest.write('{indx}: {item}\n'.format(indx=indx, item=item.getAsText()))
        if isinstance(item, InstructionCall) is True:
            indx += 1
    dest.flush()

# searches a in the varaible list for the ref var and retuns it's index
def _sink_findVarIndex(sv, vL, subVarDelimiter):
    if isinstance(sv, VarDefConstVariable) is True:
        searchName = sv.getName()
    elif isinstance(sv.varDef, VarDefConstVariable):
        searchName = sv.varDef.getName()
    else:
        defObj = sv.varDef
        ASTObj = sv.ASTobj
    
        if isinstance(ASTObj, ASTinstructionParamRefVar) is True:
            searchName = ASTObj.getNameWithSubVal(defObj.getName(), subVarDelimiter)
        else:
            searchName = defObj.getName()
    i = 0        
    for v in vL:
        if v[0] == searchName:
            return i
        i += 1
    print 'error at ref'
    print sv
    print searchName
    print type(sv)

    return None

def _sink_findLabelIndex (fcL, label):
    indx = 0
    for fc in fcL:
        if isinstance(fc, InstructionLabel) is True:
            if label == fc:
                return indx
        elif isinstance(fc, InstructionCall) is True:
            indx += 1
    print 'error at label'
    print label
    return None

# resolve code to number representation
def _sink_resolve(td, vL, fcL):
    numVarL = []
    for vName, vType, vAmount in vL:
        (vtid,) = gHALvidD.get(vType, (None, ))
        numVarL.append((vName, vtid, vAmount))

    numInstrL = []
    instrcallIndx = 0
    for f in fcL:
        if isinstance(f, InstructionCall) is True:
            instr = [0]*(gHALInstrMaxParams+1)
            (fid, PDL, paramTransL) = gHALfidD.get(f.fname, (None, []))
            instr[0]= fid
            i = 1
            for ptype, p in f.getParamList():
                if isinstance(p, RefConst) is True:
                    value = p.ASTobj.const
                elif isinstance(p, RefVar) is True:
                    value = _sink_findVarIndex(p, vL, gSubVarDelim)
                elif isinstance(p, InstructionLabel) is True:
                    value = _sink_findLabelIndex(fcL, p)
                elif isinstance(p, VarDefConstVariable) is True:
                    value = _sink_findVarIndex(p, vL, gSubVarDelim) 

                else:
                    print 'error'
                    print type(p)
                if value is None:
                    print f

                
                #ref to var
                if ptype == 1:
                    instr[i] = value
                # ref to const -> indx
                elif ptype == 2:
                    instr[i] = value
                # const  
                elif ptype == 3:
                    instr[i] = value
                # var indx
                elif ptype == 4:
                    instr[i] = value
                # jmp
                elif ptype == 5:
                    # calc formular
                    # instr Index: instrStart -> Instr = 0 -> instrcallIndx = 0A
                    # label Index: instrStart -> Label = 0 -> label = 0B
                    # search index to label distance AB: AB = 0B - 0A 
                    instr[i] = value - instrcallIndx
                else:
                    raise 'verry bad error'
                
                i += 1
            numInstrL.append (instr)
            # incr index
            instrcallIndx += 1
            
    return numVarL, numInstrL



def _sink_createC89code (td, vL, fcL, headerFile, ioSinkHeader=sys.stdout, ioSinkCFile=sys.stdout):
    decVarL, decInstrL = _sink_resolve(td, vL, fcL)
    ioSinkHeader.write(""" // audio language code file
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
           paramsAmmount=gHALInstrMaxParams+1,
           amountOfVariables=len(decVarL),
           amountOfInstructions=len(decInstrL)
           )
    )

    ioSinkCFile.write("""// audio language code file
// generated {timeStmp}

#include "{headerFile}"

//! list containing the variables
const TALCvar gALCvars [{amountOfVariables}] = {{
""".format(
           timeStmp=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
           headerFile=headerFile,
           amountOfVariables=len(vL)
           )
    )
    
    i = 0 
    for vName, vTypeID, vAmount in decVarL:
        vTypeName = vL[i][1]
        if i <> 0:
            ioSinkCFile.write(',\n')
        ioSinkCFile.write("""    //{indx}: name="{vname}" type="{tname}" amount={vAmount} 
    {{.type={vTypeID},.amount={vAmount}}}""".format(indx=i, vname=vName, tname= vTypeName, vTypeID=vTypeID, vAmount=vAmount)
            )
        i += 1
    ioSinkCFile.write("\n};")        

    # build instruction table
    
    subVarStr = {
        'i' : 'ival',
        'I' : 'rawVal',
        'f' : 'fval'
    }
    
    ioSinkCFile.write("""
//! list containing the instructions
const TALCinstr gcInstructions[{amountOfInstructions}] = {{
""".format(amountOfInstructions=len(decInstrL))
    )
    indx = 0
    for fc in fcL:
        # first the text
        ioSinkCFile.write('    /* PC {indx}: {item}*/\n'.format(indx=indx, item=fc.getAsShortText()))
        # ok check if we have an instruction ok
        if isinstance(fc, InstructionCall) is True:
            # get binary data
            instrData = decInstrL[indx]
            # get function hall id
            fid = instrData[0]
            # get translator
            (HALfID, HALfParamL, HALfuncTransL) = _HAL_findFunctionByID(fid)
            i = 0
            ioSinkCFile.write('    {')
            for tanslParam in HALfuncTransL:
                if i != 0:
                    ioSinkCFile.write(', ')
                ioSinkCFile.write('{{.{subVal}={val}}}'.format(subVal=subVarStr.get(tanslParam,'*None*'), val=instrData[i]))
                i += 1
            ioSinkCFile.write('},\n')
            indx += 1
    ioSinkCFile.write('};\n')
    
def _sink_createBinaryCode (td, vL, fcL, ioSink=sys.stdout):
    decVarL, decInstrL = _sink_resolve(td, vL, fcL)
    # create header
    # header layout
    # <id1 - 1byte><id2 - 1byte><endian - 1byte><amount vars- 4byte><amount instr - 4byte><instr. size - 4byte>
    # 
    endianNess = '?'
    if (sys.byteorder == 'little'):
        endianNess = 'l'
    if (sys.byteorder == 'big'):
        endianNess = 'b'

    dataHeader = struct.Struct('=4cciii')
    varStruct = struct.Struct('=ii')
    instrStruct = struct.Struct('={am}i'.format(am=gHALInstrMaxParams+1))
    ioSink.write (dataHeader.pack('A','C','0','1', endianNess,len(decVarL),len(decInstrL),(gHALInstrMaxParams+1)))
    for vName, vTypeID, vAmount in decVarL:
        ioSink.write (varStruct.pack(vTypeID, vAmount))
    for instr in decInstrL:
        ioSink.write (instrStruct.pack(*instr))


def _sink_createVarInfoBinary(vL, f=sys.stdout):
    endianNess = '?'
    if (sys.byteorder == 'little'):
        endianNess = 'l'
    if (sys.byteorder == 'big'):
        endianNess = 'b'
    
    dataHeader = struct.Struct('=6cci')
    header = dataHeader.pack('E','A','C','I','0','1', endianNess,len(vL))
    f.write (header)
    for vname, typeStr, amount in vL:
        vname = vname.encode("utf-8")
        vnameLen = len(vname)
        typeID = _HAL_findVarTypeByName(typeStr)[0]
        dataS = struct.Struct('=ii{strlen}s'.format(strlen=vnameLen))
        f.write (dataS.pack(typeID,vnameLen,vname))

def _sink_createVarInfoC89(vL, f=sys.stdout):
    f.write ("""// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
""")
    for vname, typeStr, amount in vL:
        vname = vname.encode("utf-8")
        typeID = _HAL_findVarTypeByName(typeStr)[0]
        
        f.write ('\t{{.szName="{szName}", .typeID={typeID}}}, \n'.format(szName=vname, typeID=typeID));
        
    f.write ('};\n');
    

def _sink_createALCtextual (vL, fcL, ioSink=sys.stdout):
    ioSink.write("Variables\n")
    ioSink.write("Layout: <Variable index> <name> <type> [<amount>]\n")
    i = 0
    for (vname, vtype, vamount) in vL:
        ioSink.write('{indx}\t{vname}\t{vtype}\t[{vamount}]\n'.format(indx=i, vtype=vtype, vname=vname, vamount=vamount))
        i += 1

    ioSink.write("Code\n")
    ioSink.write("Layout: <programm counter> function (parameter1, parameter2, ..., parameterN)  \n")
    i = 0
    for f in fcL:
        ioSink.write('{indx}\t{ffunc}\n'.format(indx=i, ffunc=f.getAsShortText()))
        if isinstance(f, InstructionCall):
            i += 1


# =============================================
# main functions
# =============================================



# reads a textfile into a buffer and return it
def readFile (filename):
    logging.info ('try to open file "{fn}"'.format(fn=filename))
    file = open(filename, 'r')
    logging.info ('read data')
    text = file.read()
    logging.info ('close file')
    file.close()
    return text


def main(argv):
    parser = argparse.ArgumentParser(description='the audio language compiler v. 0.2')
    parser.add_argument('-i', help='the audio language code input file')
    parser.add_argument('-o', help='output dir', default=os.curdir)
    args = parser.parse_args()
    return (args.i, args.o)

if __name__ == '__main__':    
    # setup logger
    logging.basicConfig(filename='ALClog.txt',filemode='w',format='%(name)s [%(levelname)s] : %(message)s',level=logging.NOTSET)
    #logging.basicConfig(filename='ALClog.txt',filemode='w',format='%(name)s [%(levelname)s] : %(message)s',level=logging.DEBUG)
    logging.info ('start logger')

    # get cmdline arguments
    (iFile, oDir) = main(sys.argv[1:])
    
    # setup compiler
    _HAL_setup()
    
    # read AL file
    try:
        ALtxt = readFile(iFile)

        # create lexer
        lexer = lex.lex()
        lexer.input(ALtxt)
    
        p = yacc.yacc(
            start='start',
            debugfile='ALC2dbg.txt',
            tabmodule='ALC2tab.txt',
            debug=10
        )
        logging.info ('create AST tree')
        AST = p.parse(ALtxt,lexer=lexer,tracking=True)

        td = _process_createTypeDictAndunrollTypes(AST)
        
        logging.info ('build global vars')
        gVD = {}
        _AST_buildVariableDict(AST, gVD)
        gVL = _VariableDeclaration_TransferIntoList(gVD, True)
        
        
        logging.info ('build functions')

        fd = _process_functions(AST, td, gVL)
        for key, (fcL, vL, gvAmount) in fd.items():
            # generate filenames
            headerFile = os.path.join(os.curdir, oDir,key + '.h')
            codeFile = os.path.join(os.curdir, oDir,key+'.c')
            binCodeFile = os.path.join(os.curdir, oDir,key+'.alc')
            varInfoFile = os.path.join(os.curdir, oDir,key + '_VarInfo.h')
            binVarInfoFile = os.path.join(os.curdir, oDir,key + '.info')
            infoFile = os.path.join(os.curdir, oDir,key + '_info.txt')
            
            # open/create files
            fheader = open(headerFile, 'w')
            fcode = open(codeFile, 'w')
            fbincode = open(binCodeFile, 'wb')
            fvarInfo = open(varInfoFile, 'w')
            fbinVarInfo = open(binVarInfoFile, 'wb')
            finfo = open(infoFile, 'w')
            
            # dump code
            _sink_createALCtextual(vL, fcL, finfo)
            _sink_createC89code(td, vL, fcL, key+'.h', fheader, fcode)
            _sink_createBinaryCode(td, vL, fcL, fbincode)
            _sink_createVarInfoBinary(vL, fbinVarInfo)
            _sink_createVarInfoC89(vL, fvarInfo)
            
            fheader.close()
            fcode.close()
            fbincode.close()
            fbinVarInfo.close()
            fvarInfo.close()
            finfo.close()
            
        print "finished!"
    except IOError as e:
        print "I/O error({0}): {1}".format(e.errno, e.strerror)
#     except ValueError as v:
#         print "Could not convert data to an integer."
#         print v
#     except TypeError as te:
#         print "type error "+str(te)
#     except exceptions.SyntaxError as se:
#         print se
#     except:
#         print "Unexpected error:", sys.exc_info()[0]
#         raise
    pass

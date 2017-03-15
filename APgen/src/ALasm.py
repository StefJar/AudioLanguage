'''
Created on 13.07.2011

@author: StJ
'''

import argparse
import sys
import os
import ply.lex as lex
import ply.yacc as yacc
#from numpy.f2py.auxfuncs import throw_error
import ctypes
import struct
import copy
import re

import APDB
import codeGen

import subprocess

class ALASMParser(object):
    """
    Base class for a lexer/parser that has the rules defined as methods
    """
    tokens = ()
    precedence = ()
    start = ''

    def __init__(self, **kw):
        self.debug = kw.get('debug', 0)
        self.names = { }
        try:
            modname = os.path.split(os.path.splitext(__file__)[0])[1] + "_" + self.__class__.__name__
        except:
            modname = "parser"+"_"+self.__class__.__name__
        self.debugfile = modname + ".dbg"
        self.tabmodule = modname + "_" + "parsetab"
    

    def run(self, text):
        #print self.debugfile, self.tabmodule

        # Build the lexer and parser
        lex.lex(module=self, debug=self.debug)
        yacc.yacc(module=self,
                  debug=self.debug,
                  debugfile=self.debugfile,
                  tabmodule=self.tabmodule,
                  start=self.start
                  )
        ##return yacc.parse(text,tracking=True)
        return yacc.parse(text,tracking=False)

    
class ALASMGrammar(ALASMParser):
    maxFunctParams =  0
    
    reserved = {
        'globals'           : 'globals',
        'locals'            : 'locals',
        'code'              : 'code',
        'function'          : 'function',
        'ALASMsetStr'       : 'ALASMsetStr',
        'ALASMsetInt'       : 'ALASMsetInt',
        'ALASMsetRational'  : 'ALASMsetRational',
        'label'             : 'labelKeyword'
        }
    
    tokens = [
        'lBrace',
        'rBrace',
        'lSoftBrace',
        'rSoftBrace',
        'lBracket',
        'rBracket',
        'assign',
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
        'string',
        'comment',
        'labelKeyWord',
        'label'
    ] + list(reserved.values())

    t_lBrace = '{' 
    t_rBrace = '}'
    t_lSoftBrace = '\(' 
    t_rSoftBrace = '\)'
    t_lBracket = '\['
    t_rBracket = '\]'
    t_assign = '='
    t_comma = ','
    t_semicolon = ';' 
    t_ignore = ' \t'
    t_arrowLeft = '>>'
    t_arrowRight = '<<'
    t_not = '!'
    t_add = '\+'
    t_sub = '-'
    t_div = '/'
    t_mul = '\*' 
    
    def t_comment (self, t):
        r'(/\*(.|\n)*?\*/)|(//.*)'
        t.type = 'comment'
        l = len(t.value)
        if (t.value[0:2] == '//') :
            t.value = t.value[2:l]
        else :
            t.value = t.value[2:l-2]
        return t
    
    def t_string (self, t):
        r'\"([^\\\n]|(\\.))*?\"'
        # remove " at the beginning and at the end
        l = len(t.value)
        if l >= 2:
            t.value = t.value[1:l-1]
        # un format special char sequences
        t.value = re.sub (r'\\"','"',t.value);
        t.value = re.sub (r'\\n','\n',t.value);
        return t

    def t_label(self, t):
        r'@[a-zA-Z_][a-zA-Z0-9_]*'
        return t
    
    def t_name(self, t):
        r'[a-zA-Z_][a-zA-Z0-9_]*'
        t.type = self.reserved.get(t.value,'name')    # Check for reserved words
        return t

    def t_fNumber(self, t):
        r'[-+]?\d+\.\d+([eE][-+]?\d+)?'
        try:
            t.value = float(t.value)
        except ValueError:
            print("Integer value too large %d", t.value)
            t.value = 0
        return t

    def t_iNumber(self, t):
        r'[-+]?\d+'
        try:
            t.value = int(t.value)
        except ValueError:
            print("Integer value too large %d", t.value)
            t.value = 0
        return t

    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += t.value.count("\n")
    
    def t_error(self, t):
        print("Illegal character '%s'" % t.value[0])
        t.lexer.skip(1)

    # Parsing rules

    precedence = (
        ('nonassoc', 'assign'),
        ('left', 'add', 'sub'),
        ('left', 'mul', 'div'),
        ('right', 'not')            # Unary minus operator
        )

    #define start rule
    start = 'start'
    
    def resetParser (self):
        self.globalVars = []
        self.functions = []
    
    def p_start (self, p):
        """start :
            | brick
            | start brick
        """
        p[0] = None
        
    def p_brick (self, p):
        """brick : globalVarStm
            | functionStm
            | commentStm
        """
        v = p[1]
        if v[0] == 'g':
            self.globalVars += v[1]
        else:
            self.functions.append(v[1])
        p[0] = None

    def p_globalVarStm (self, p):
        'globalVarStm : globals lBrace varListStm rBrace'
        p[0] = ('g' , p[3])

    def p_CommentStm (self, p):
        'commentStm : comment'
        p[0] = ('c' , p[1])

        
    def p_varListStm (self,p):
        """varListStm :
            | varDecl
            | varListStm varDecl
        """
        l = len(p)
        if 1 == l:
            p[0] = []
        
        if 2 == l :
            p[0] = []
            p[0].append(p[1])
        
        if 3 == l :
            p[0] = p[1]
            p[0].append(p[2])
             

    def p_varDecl (self, p):
        'varDecl : name name semicolon'
        # type name
        p[0] = (p[1], p[2], int(1))

    def p_varDeclArray (self, p):
        'varDecl : name name lBracket iNumber rBracket semicolon'
        # type name [amount]
        p[0] = (p[1], p[2], int(p[4]))
        
    def p_function (self, p):
        'functionStm : function name localVarStm codeStm'
        p[0] = ('f',(p[2], p[3], p[4]))
        
    def p_localVarStm (self, p):
        'localVarStm : locals lBrace varListStm rBrace'
        p[0] = p[3]
        
    def p_codeStm (self, p):
        'codeStm : code lBrace instrListStm rBrace'
        p[0] = p[3]

    def p_instrListStm (self, p):
        """instrListStm :
            | instrStm
            | instrListStm instrStm 
            """
        l = len(p)
        if 1 == l:
            p[0] = []
                
        if 2 == l :
            if p[1]  != None:
                if isinstance(p[1], tuple) :
                    p[0] = [p[1]]
                else:
                    p[0] = []
                    for pe in p[1]:
                        p[0].append(pe)
            else:
                p[0] = []
        if 3 == l :
            p[0] = p[1]
            if p[2] != None:
                if isinstance(p[2], tuple) :
                    p[0].append(p[2])
                else:
                    for pe in p[2]:
                        p[0].append(pe)
              
                    
    def p_commentStmInstr (self, p):
        'instrStm : commentStm'
        p[0] = None

    def p_instrStm (self, p):
        'instrStm : name paramListStm semicolon'
        p[0] = (p[1], p[2])
    
    def p_param (self,p):
        """
        param : iNumber
            | fNumber
            | name
            | label
        """
        p[0] = p[1]
        
    def p_paramListStm (self, p):
        """paramListStm :
            | param
            | paramListStm comma param 
        """
        l = len(p)
        if 1 == l:
            p[0] = []
                
        if 2 == l :
            p[0] = [p[1]]
               
        if 4 == l :
            p[0] = p[1]
            p[0].append(p[3])
    
    def p_ALASMsetStrStm (self, p):
        'instrStm : ALASMsetStr name comma iNumber comma string semicolon'
        strName = p[2]
        strIndex = int(p[4])
        strL = len(p[6])
        text = p[6]
        Nele = (self.maxFunctParams - 3)
        N = Nele * 4 
        
        p[0] = [('setStringSize', [strName, strIndex, strL])]
        imax = strL / N
        if strL % N:
            imax += 1
        strLi = imax * N
        # fill string with spaces
        for i in range(strL, strLi):
            text += ' '
        idx = 0
        for i in range (imax):
            pa = [strName, strIndex, idx]
            for j in range(Nele):
                pa.append (struct.unpack_from('I',text,idx)[0])
                idx += 4
            p[0].append(('setStringValues', pa))

    def p_ALASMsetInt (self, p):
        'instrStm : ALASMsetInt name comma lBracket iValueList rBracket semicolon'
        ivName = p[2]
        vL = p[5]
        vLen = len(vL)
        p[0] = []
        
        N = (self.maxFunctParams - 3)
        
        
        imax = vLen / N
        if vLen % N:
            imax += 1

        # fill empty values with 0
        for i in range(vLen,imax*N):
            vL.append(int(0))
        idx = 0
        itemsLeft = vLen
        for i in range (imax):
            if (itemsLeft > N):
                Ns = N
                itemsLeft -= N
            else :
                Ns = itemsLeft
                itemsLeft = 0
            pa = [ivName, idx, Ns]
            for j in range(N):
                pa.append (vL[idx])
                idx += 1
            p[0].append(('assignConstInteger', pa))

    def p_ALASMsetRational (self, p):
        'instrStm : ALASMsetRational name comma lBracket fValueList rBracket semicolon'
        ivName = p[2]
        vL = p[5]
        vLen = len(vL)
        p[0] = []
        
        N = (self.maxFunctParams - 3)
        
        
        imax = vLen / N
        if vLen % N:
            imax += 1

        # fill empty values with 0
        for i in range(vLen,imax*N):
            vL.append(float(0.0))
        idx = 0
        itemsLeft = vLen
        for i in range (imax):
            if (itemsLeft > N):
                Ns = N
                itemsLeft -= N
            else :
                Ns = itemsLeft
                itemsLeft = 0
            pa = [ivName, idx, Ns]
            for j in range(N):
                pa.append (vL[idx])
                idx += 1
            p[0].append(('assignConstRational', pa))

    def p_Label (self, p):
        'instrStm : labelKeyword label semicolon'
        p[0] = ('label',p[2])

    def p_iValueList (self, p):
        """iValueList :
                    | iNumber
                    | iValueList iNumber
        """
        l = len(p)
        if 1 == l:
            p[0] = []
                
        if 2 == l :
            p[0] = [p[1]]
               
        if 4 == l :
            p[0] = p[1]
            p[0].append(p[3])

    def p_fValueList (self, p):
        """fValueList :
                    | fNumber
                    | fValueList fNumber
        """
        l = len(p)
        if 1 == l:
            p[0] = []
                
        if 2 == l :
            p[0] = [p[1]]
               
        if 4 == l :
            p[0] = p[1]
            p[0].append(p[3])


    def p_error(self, p):
        if p:
            text = 'Syntax error at ' + str(p.value) +'\nLine ' + str(p.lineno)
        else:
            text = 'Syntax error at EOF'
        raise SyntaxError(text)

    def createLoopVarName(self):
        return '_generated_lv' + str(self.nestingDeep)

    def translate(self, text):
        try:
            self.resetParser()
            res = self.run(text)
        except SyntaxError as txt:
            return (False,txt)
        return (True, res)
    
    def translateFile (self, filename):
        try:
            with open(filename, 'r') as file:
                text = file.read()
        except IOError:
            return (False, 'can not open file {filename}'.format(filename=filename))
        finally:
            file.close() 

        return self.translate(text)

class TranslationConverter_ALASMtoBin(object):
    def __init__(self, db, maxFunctParams):
        self.db = db
        
        self.cTypesAssos = {
            'integer'       : (ctypes.c_int32   ,4, int),
            'int'           : (ctypes.c_int32   ,4, int),
            'int32_t'       : (ctypes.c_int32   ,4, int),
            'uint32_t'      : (ctypes.c_uint32  ,4, int),
            'raw'           : (ctypes.c_uint32  ,4, int),
            'char'          : (ctypes.c_char    ,1, str),
            'float'         : (ctypes.c_float   ,4, float),
            'rational'      : (ctypes.c_float   ,4, float)
            }
        
        self.maxFunctParams = maxFunctParams 
    
    def getVarData (self, varList, varname):
        i = 0
        for v in varList:
            if v[1] == varname:
                HALvar = self.db.HAL_VariableDefinition_getByName(v[0])
                if HALvar == None:
                    return (False, i, None, 'variable type '+str(v[0])+'don\'t exists!')
                return (True, i, HALvar, None) 
            i += 1
        return (False, -1, None, 'variable with the name "'+str(varname)+'" don\'t exists!')
    
    def run(self, globalVars, functionList):
        #resolve labels
        nFL =[]
        for f in functionList:
            (res, nInstrL) = self.resolveLabels(f[2]);
            if res == False:
                return (res, functionList)
            nFL.append((f[0],f[1],nInstrL))
    
        translationList = []
        for f in nFL:
            # setup
            instrBinaryList = []
            varBinaryList = []
            # build var list
            vars = copy.deepcopy(globalVars)
            vars += f[1]
            for v in vars:
                halVarTypeID = self.db.HAL_VariableDefinition_getByName(v[0])
                if halVarTypeID == None :
                    return (False, 'variable type '+str(v[0])+' is unknown')
                # save type & amount
                varBinaryList.append([ctypes.c_int32(halVarTypeID[1]), ctypes.c_int32(v[2])])

            # now check code
            for inst in f[2]:
                # ask the db
                halFdef = self.db.HAL_DefFunctions_getByName(inst[0])
                if halFdef == None :
                    return (False,inst[0] + ' is not function defined at the HAL!')
                fid = halFdef[1] 
                # get the parameters
                halFparams = self.db.HAL_DefFunctions_getParamList(fid)
                lHALparam = len(halFparams)
                lInstrParam = len (inst[1])
                if lHALparam != lInstrParam :
                    return (False, 'the HAL function "%s" defined %i parameters. The instruction contained %s parameters.' % (halFdef[2],lHALparam,lInstrParam))
                # now check the parameter types
                paramList = []
                i = 0
                for p in inst[1]:
                    pClass = halFparams[i][4]
                    pType = halFparams[i][5]
                    if pClass == self.db.dFuncClass_basicIOtype :
                        halBasicType = self.db.HAL_basicIOTypes_getByTypeID(pType)
                        btTempl = self.cTypesAssos[halBasicType[2]]
                        if (btTempl[1] != halBasicType[6]):
                            return (False, 'parameter c-type size('+str(halBasicType[6])+') is not equal to the std. c type('+str(btTempl[1])+')',p)
                        if (type(p) != btTempl[2]) :
                            return (False, 'parameter type mismatch @'+str(p)+' in '+str(inst))
                        # convert to c type
                        val = btTempl[0](p)
                    else :
                        (res, index, halVar, errorStr) = self.getVarData(vars,p)
                        if (False == res) :
                            estr2 = errorStr + ' ' + str(inst) 
                            return (False,estr2)
                        val = ctypes.c_int32(index)
                    paramList.append(val)
                    i += 1
                instrBinary = [ctypes.c_int32(fid)]
                # fill the not used parameters with 0
                fillElements = self.maxFunctParams - len(paramList)
                paramList += [ctypes.c_int32(0)]*fillElements
                instrBinary += paramList 
                instrBinaryList.append(instrBinary)
                
            translationList.append((f[0],varBinaryList,instrBinaryList))
        return (True, translationList)    

    def findLabel(self, functionList, label):
        i = 0;
        for f in functionList:
            if f[0] == 'label':
                if f[1] == label :
                    return i;
            else:
                i += 1;
        return None;

    def resolveLabels(self, instrList):
        resFL = []
        i = 0;
        for inst in instrList:
            if inst[0] != 'label':
                nf = (inst[0], [])
                # scan params for lables
                for p in inst[1]:
                    # ident param as label
                    if isinstance(p, str):
                        if len(p) > 2 and p[0] == '@':
                            labelIndex = self.findLabel(instrList, p)
                            if labelIndex == None:
                                return (False, 'label %s could not resolved!' % p)
                            else:
                                jmpOfs = labelIndex - i
                                nf[1].append(jmpOfs)
                        else:
                            nf[1].append(p)
                    else:
                        nf[1].append(p)
                resFL.append(nf)
                #print ('%i %s' % (i,str(nf)))
                i += 1;
            else:
                # we sort the labels out
                pass
        return (True, resFL)


def dumpConvertedToFiles (translationList, db,outputDir, pythonProgPath, cFileEmbeeded, cFileTransl, cFileInstrAmountBeforeMS):
    maxFunctParams = db.HAL_DefFunctions_maxParamCount()
    endianNess = '?'
    if (sys.byteorder == 'little'):
        endianNess = 'l'
    if (sys.byteorder == 'big'):
        endianNess = 'b'
        
    for t in translationList:
        # create and open file
        filenameBin = os.path.join(outputDir,t[0]+'.alc')
        print 'dump code into '+filenameBin
        f = open (filenameBin,'wb')
        # create header
        # header layout
        # <id1 - 1byte><id2 - 1byte><endian - 1byte><amount vars- 4byte><amount instr - 4byte><instr. size - 4byte>
        # 
        dataHeader = struct.Struct('=4cciii')
        header = dataHeader.pack('A','C','0','1', endianNess,len(t[1]),len(t[2]),(maxFunctParams+1))
        data = []
        # flaten vars
        for d in t[1]:
            data += d
        # flaten instr
        for d in t[2]:
            data += d
        # dump data to file
        f.write (header)
        for e in data:
            f.write (e)
        f.close()
        
        filenameCfile = os.path.join(outputDir,t[0]+'.c')
        pycmd = os.path.join(pythonProgPath,'ALCFileToCcode.py')

        cmdCall =None
        if (cFileEmbeeded is True) and (cFileTransl is False):
            cmdCall = 'python {pycmd} -i="{binFileName}" -o="{cFilename}" -b'.format(pycmd=pycmd, binFileName=filenameBin, cFilename=filenameCfile, cFileInstrAmountBeforeMS=cFileInstrAmountBeforeMS)
                
        if (cFileEmbeeded is False) and (cFileTransl is True):
            cmdCall = 'python {pycmd} -i="{binFileName}" -o="{cFilename}" -a={cFileInstrAmountBeforeMS}'.format(pycmd=pycmd, binFileName=filenameBin, cFilename=filenameCfile, cFileInstrAmountBeforeMS=cFileInstrAmountBeforeMS)
        
        if cmdCall is not None:
            print 'execute ' + cmdCall    
            p = subprocess.Popen(cmdCall, shell=True)
            if p is not None:
                p.wait()
        


def dumpGlobalVarInfoToFile (db, gvL, filename):
    endianNess = '?'
    if (sys.byteorder == 'little'):
        endianNess = 'l'
    if (sys.byteorder == 'big'):
        endianNess = 'b'
    
    dataHeader = struct.Struct('=6cci')
    header = dataHeader.pack('E','A','C','I','0','1', endianNess,len(gvL))
    
    f = open (filename,'wb')
    f.write (header)

    for type, vname, amount in gvL:
        vUUID, varID, vtname, descr = db.HAL_VariableDefinition_getByName(type)
        vname = vname.encode("utf-8")
        vnameLen = len(vname)
        dataS = struct.Struct('=ii{strlen}s'.format(strlen=vnameLen))
        f.write (dataS.pack(varID,vnameLen,vname))
    f.close()
            
def main(argv):
    parser = argparse.ArgumentParser(description='the audio language assembler')
    parser.add_argument('-i', help='the audio language assembler input file')
    parser.add_argument('-o', help='the audio language code output directory')
    parser.add_argument('-p', help='python program path (there are the tool scripts located. Like "ALCFileToCcode.py")', default='')
    parser.add_argument('-ce', help='generate additional c-files with the embeeded binary code', default=False, action='store_const', const=True)
    parser.add_argument('-cf', help='generate additional c-files with the binary code translated into HAL functions', default=False, action='store_const', const=True)
    parser.add_argument('-cfai', help='amount of instructions before the message system is checked (only valid if -cf is set)', default='5')
    args = parser.parse_args()
    return (args.i, args.o, args.p, args.ce, args.cf, args.cfai)

if __name__ == '__main__':
    # setup db connection
    db = APDB.APDB('APdbCreate.sql','dbInit.xml')
    
    maxFunctParams = db.HAL_DefFunctions_maxParamCount()
    
    (iFile, oDir, pythonProgPath, cFileEmbeeded, cFileTransl, cFileInstrAmountBeforeMS) = main(sys.argv[1:])
    print ('assemble "'+iFile+'" to dir "'+oDir+'" ...')
    
    myP = ALASMGrammar()
    myP.maxFunctParams = maxFunctParams 

    (res, errTxt) = myP.translateFile(iFile)
    if res == False:
        sys.stderr.write(str(errTxt))
        sys.exit(-1)
    tc = TranslationConverter_ALASMtoBin(db, maxFunctParams)
    (res, tl) = tc.run(myP.globalVars, myP.functions)
    
    if (True == res):
        dumpConvertedToFiles (tl,db,oDir, pythonProgPath, cFileEmbeeded, cFileTransl, cFileInstrAmountBeforeMS)
        
        # create global info file
        dumpGlobalVarInfoToFile(db, myP.globalVars,os.path.join(oDir,'globalVar.info'))

        print ('alasm code successfully translated')    
    else :
        sys.stderr.write(tl)
        print ('error: '+ tl)
        sys.exit(-2)
        
        
    sys.exit(0)



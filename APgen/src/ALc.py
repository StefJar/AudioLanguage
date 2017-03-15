# -*- coding: utf-8 -*-

'''
Created on 13.07.2011

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

import APdocgen

class ALParser(object):
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
        # print self.debugfile, self.tabmodule

        # Build the lexer and parser
        #lex.lex(module=self, debug=self.debug)
        lex.lex(module=self, debug=None)
                           
        yacc.yacc(module=self,
                  debug=self.debug,
                  debugfile=self.debugfile,
                  tabmodule=self.tabmodule,
                  start=self.start,
                  )
        #return yacc.parse(text,tracking=True, debug=1)
        return yacc.parse(text,tracking=True, debug=None)

class ASTtype:
    globalVar = 1
    localVar = 2
    function = 3
    main = 4
    typedef = 5
    comment = 6

class ASTfunctionInterface:
    input = 1
    output = 2
    inout = 3
    names = {
        'in' : input,
        'out' : output,
        'io' : inout
        }

class ASTstatementtype:
    comment         = -1
    math_add        = 1
    math_sub        = 2
    math_mul        = 3
    math_div        = 4
    assign          = 5
    brace           = 6
    equal           = 7
    nEqual          = 8
    less            = 9
    more            = 10
    lessEqual       = 11
    moreEqual       = 12
    notStm          = 13
    ifStm           = 14
    ifelseStm       = 15
    forStm          = 16
    funcCall        = 17
    infLoop         = 18
    varOperations   = 19
    checkButton     = 20
    update          = 21
    addAssign       = 22
    whileStm        = 23
    
    stmStr = {
        math_add        : ('math add'),
        math_sub        : ('math sub'),
        math_mul        : ('math mul'),
        math_div        : ('math div'),
        assign          : ('assign'),
        brace           : ('brace'),
        equal           : ('equal'),
        nEqual          : ('not equal'),
        less            : ('less'),
        more            : ('more'),
        lessEqual       : ('less equal'),
        moreEqual       : ('more equal'),
        notStm          : ('not'),
        ifStm           : ('if'),
        ifelseStm       : ('if else'),
        forStm          : ('for'),
        funcCall        : ('call'),
        infLoop         : ('infinity loop'),
        comment         : ('comment'),
        varOperations   : ('variable specific operation'),
        checkButton     : ('check button sequence'),
        update          : ('update'),
        addAssign       : ('add with assignment'),
        whileStm        : ('while')
        }
    
class ASTpos:
    def __init__(self, p, indx):
        self.pos = p.lineno(indx)
        self.lineno = p.lexpos(indx)
    def __repr__ (self):
        return 'position=%s, line number=%s' % (self.pos, self.lineno)

class ASTstatement:
    def __init__ (self, stmType, params, srcPos):
        self.stmType = stmType
        self.params = params
        self.srcPos = srcPos
    def __repr__ (self):
        return 'stm=%s, params=%s, pos=%s' % (ASTstatementtype.stmStr.get(self.stmType,'unknown'),  self.params, self.srcPos)



class ASTvartype:
    variable = 1
    inumber = 2
    fnumber = 3
    string = 4
    strAsso = {
      inumber : 'integer',
      fnumber : 'rational',
      string : 'string'
    }
    numberAsso = {
      'integer' : inumber,
      'rational' : fnumber,
      'string' : string                  
    }

class ALGrammar(ALParser):
    # constants
    
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
        'nEqual',
        'equal',
        'assign',
        'comment',
        'less',
        'lessEqual',
        'more',
        'moreEqual',
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
    t_moreEqual = '>='
    t_more = '>'
    t_inc = '\+\+'
    t_add = '\+'
    t_dec = '--'
    t_sub = '-'
    t_addAssign = '\+='
    t_point = '\.'
      
    def translate(self, text):
        try:
            self.resetParser()
            res = self.run(text)
        except SyntaxError as txt:
            return (False,txt)
        return (True, res)
    
    def translateFile (self, filename):
        file = open(filename, 'r')
        text = file.read()
        file.close()
        return self.translate(text)

    
    def resetParser (self):
        pass
    
    def YACC_printErrorAndAbort (self, errorMsg, linenum, pos):
        text = 'Syntax error at ' + str(pos) +' Line ' + str(linenum)
        if errorMsg:
            text += '\nerror text: ' + errorMsg
        print (text)
        raise SyntaxError(text)
    
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
    
    
    #1.) entry rules
    def p_startElements (self, p):
        """startElements : globalVarStm
                | functionStm
                | mainStm
                | typedefStm
                | commentStm
        """
        p[0] = p[1]
        
    def p_start (self, p):
        """start :
            | startElements
            | start startElements
        """
        l = len(p)
        if l == 1:
            p[0] = []
        elif l == 2:
            p[0] = [p[1]]
        else:
            p[1].append(p[2])
            p[0] = p[1]
    
    def p_globalStm (self, p):
        'globalVarStm : globalVarListStm'
        p[0] = [ASTtype.globalVar, p[1], ASTpos(p, 1)]
    
    def p_functionStm (self, p):
        'functionStm : function name lBrace interfaceVarListStm localVarListStm codeListStm rBrace'
        p[0] = [ASTtype.function, [p[2] ,p[4], p[5], p[6]], ASTpos(p, 1)]
    
    def p_mainStm (self, p):
        'mainStm : main lSoftBrace name rSoftBrace lBrace localVarListStm codeListStm rBrace'
        p[0] = [ASTtype.main, [p[6] ,p[7]], ASTpos(p, 1),p[3]]
    
    def p_typedefStm (self, p):
        'typedefStm : typedef name lBrace varListDecl rBrace'
        p[0] = [ASTtype.typedef, [p[2], p[4]], ASTpos(p, 1)]
    
    def p_commentStm (self, p):
        'commentStm : comment'
        p[0] = [ASTtype.comment, [p[1]], ASTpos(p, 1)]
    
    #2.) variable rules
    
    #2.1) element rules
    def p_varDeclaration (self, p):
        'varDeclaration : name name'
        p[0] = [p[1], p[2], int(1)]

    def p_varDeclarationWithNumber (self, p):
        'varDeclaration : name name lBracket iNumber rBracket'
        p[0] = [p[1], p[2], int(p[4])]

    def p_varDeclStm (self, p):
        'varDeclStm : varDeclaration semicolon'
        p[0] = [p[1], ASTpos(p, 1)]

    def p_commentAtTheVarDeclStm (self, p):
        'varDeclStm : commentStm'
        p[0] = p[1]


    def p_interfaceVarStm (self, p):
        'interfaceVarStm : name varDeclaration semicolon'
        vt = ASTfunctionInterface.names.get(p[1],None)
        if vt == None:
            self.YACC_printErrorAndAbort('interface variables need a direction definition (in, out, io)',p.lineno(1),p.lexpos(1));
        else:
            p[0] = [vt, p[2], ASTpos(p, 1)]
    
    def p_commentAtTheInterfaceVarDeclStm (self, p):
        'interfaceVarStm : commentStm'
        p[0] = p[1]

        
    #2.2) list rules
    def p_varListDecl (self, p):
        """varListDecl :
            | varDeclStm
            | varListDecl varDeclStm
        """
        l = len(p)
        if l == 1:
            p[0] = []
        elif l == 2:
            if len(p[1]) != 3:
                p[0] = [p[1]]
            else:
                p[0] = []
        else:
            if len(p[2]) != 3:
                if p[1] is None:
                    p[1] = []
                p[1].append(p[2])
                p[0] = p[1]


    def p_interfaceVarListDecl (self, p):
        """interfaceVarListDecl :
            | interfaceVarStm
            | interfaceVarListDecl interfaceVarStm
        """
        l = len(p)
        if l == 1:
            p[0] = []
        elif l == 2:
            p[0] = [p[1]]
        else:
            p[1].append(p[2])
            p[0] = p[1]

    #2.3) final statements
    def p_globalVarListStm (self, p):
        'globalVarListStm : global lBrace varListDecl rBrace'
        p[0] = p[3]

    def p_localVarListStm (self, p):
        'localVarListStm : local lBrace varListDecl rBrace'
        p[0] = p[3]

    def p_interfaceVarListStm (self, p):
        'interfaceVarListStm : interface lBrace interfaceVarListDecl rBrace'
        p[0] = p[3]

    #3.) code
    
    #3.1) basics
    def p_codeListStm (self, p):
        'codeListStm : code lBrace statements rBrace'
        p[0] = p[3]
        
    def p_statements (self, p):
        """statements :
                | statement
                | statements statement
        """
        l = len(p)
        if l == 1:
            p[0] = []
        elif l == 2:
            p[0] = [p[1]]
        else:
            p[1].append(p[2])
            p[0] = p[1]

    
    #3.2) statements
    
    #3.2.1) expressions
    
    # variables
    def p_varVariableExp (self, p):
        """varExp : name
            | varExp point name
        """
        l = len(p)
        if l == 2:
            p[0] = VariableAtExpression(p[1], None, None, None)
        else:
            var = p[1]
            var.addSubValue(p[3])
            p[0] = var


    def p_varVariable (self, p):
        'var : varExp'
        # variable with index 0
        p[0] = [ASTvartype.variable, p[1], int(0)]
        

    def p_varVariableArray (self, p):
        'var : varExp lBracket iNumber rBracket'
        # varaible with index at p[3]
        p[0] = [ASTvartype.variable, p[1], p[3]]

    # numbers
    def p_expiNumber (self, p):
        'expiNumber : iNumber'
        p[0] = [ASTvartype.inumber, p[1]]

    def p_expfNumber (self, p):
        'expfNumber : fNumber'
        p[0] = [ASTvartype.fnumber, p[1]]

    # literals
    def p_expString (self, p):
        'expString : string'
        p[0] = [ASTvartype.string, p[1]]


    def p_expVariable (self, p):
        """exp : var
                | expiNumber
                | expfNumber
                | expString
        """
        p[0] = p[1]


    # operations on variables and numbers    
    def p_expNumberAdd (self, p):
        'exp : exp add exp'
        p[0] = ASTstatement(ASTstatementtype.math_add, [p[1], p[3]], ASTpos(p, 1))

    def p_expNumberSub (self, p):
        'exp : exp sub exp'
        p[0] = ASTstatement(ASTstatementtype.math_sub, [p[1], p[3]], ASTpos(p, 1))

    def p_expNumberMul (self, p):
        'exp : exp mul exp'
        p[0] = ASTstatement(ASTstatementtype.math_mul, [p[1], p[3]], ASTpos(p, 1))

    def p_expNumberDiv (self, p):
        'exp : exp div exp'
        p[0] = ASTstatement(ASTstatementtype.math_div, [p[1], p[3]], ASTpos(p, 1))

    
    def p_expBraces (self,p):
        'exp : lSoftBrace exp rSoftBrace'
        p[0] = ASTstatement(ASTstatementtype.brace, [p[2]], ASTpos(p, 1))

    def p_expInc (self,p):
        'exp : exp inc'
        p[0] = ASTstatement(ASTstatementtype.math_add, [p[1], p[1], [ASTvartype.inumber, int(1)]], ASTpos(p, 1))

    def p_expDec (self,p):
        'exp : exp dec'
        p[0] = ASTstatement(ASTstatementtype.math_sub, [p[1], p[1], [ASTvartype.inumber, int(1)]], ASTpos(p, 1))

    def p_expbParam (self, p):
        'expbParam : exp'
        p[0] = p[1]
        
    # boolean expressions
    def p_expbNot (self,p):
        'expb : not expbParam'
        p[0] = ASTstatement(ASTstatementtype.notStm, [p[2]], ASTpos(p, 1))

    def p_expbNequal(self,p):
        'expb : expbParam nEqual expbParam'
        p[0] = ASTstatement(ASTstatementtype.nEqual, [p[1], p[3]], ASTpos(p, 1))

    def p_expbEqual(self,p):
        'expb : expbParam equal expbParam'
        p[0] = ASTstatement(ASTstatementtype.equal, [p[1], p[3]], ASTpos(p, 1))

    def p_expbLess(self,p):
        'expb : expbParam less expbParam'
        p[0] = ASTstatement(ASTstatementtype.less, [p[1], p[3]], ASTpos(p, 1))

    def p_expbLessEqual(self,p):
        'expb : expbParam lessEqual expbParam'
        p[0] = ASTstatement(ASTstatementtype.lessEqual, [p[1], p[3]], ASTpos(p, 1))

    def p_expbMore(self,p):
        'expb : expbParam more expbParam'
        p[0] = ASTstatement(ASTstatementtype.more, [p[1], p[3]], ASTpos(p, 1))

    def p_expbMoreEqual(self,p):
        'expb : expbParam moreEqual expbParam'
        p[0] = ASTstatement(ASTstatementtype.moreEqual, [p[1], p[3]], ASTpos(p, 1))


    # 3.2.2) assigns
    def p_expAssign(self,p):
        'exp : var assign exp'
        # set varaiable
        c = p[1]
        if (isinstance(p[3], ASTstatement) == True):
            stm = p[3]
            a = stm.params[0]
            b = stm.params[1]
            p[0] = ASTstatement(stm.stmType, [c, a, b], ASTpos(p, 1))
        else:
            p[0] = ASTstatement(ASTstatementtype.assign, [c ,p[3]], ASTpos(p, 1))

    def p_expAddAssign (self, p):
        'exp : var addAssign exp'
        p[0] = ASTstatement(ASTstatementtype.addAssign, [p[1], p[3]], ASTpos(p, 1))


    # 3.2.3) conditions
    def p_stmIf (self,p):
        'statement : if lBracket expb rBracket lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.ifStm, [p[3] ,p[6]], ASTpos(p, 1))
    
    def p_stmIfElse (self,p):
        'statement : if lBracket expb rBracket lBrace statements rBrace else lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.ifelseStm, [p[3] ,p[6], p[10]], ASTpos(p, 1))
        
    # 3.2.4) stand alone expr
    def p_stmExp (self,p):
        'statement : exp semicolon'
        p[0] = p[1]

    # 3.2.5) for loop
    def p_stmForLoop (self, p):
        'statement : for lBracket exp semicolon expb semicolon exp rBracket lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.forStm, [p[3] ,p[5] ,p[7], p[10]], ASTpos(p, 1))

    # 3.2.5.2) for loop endless
    def p_stmForLoopEndless (self, p):
        'statement : for lBracket semicolon semicolon rBracket lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.infLoop, [p[7]], ASTpos(p, 1))


    #3.2.5.3 while loop
    def p_stmWhileLoop (self, p):
        'statement : while lBracket expb rBracket lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.whileStm, [p[3] ,p[6]], ASTpos(p, 1))

    #3.2.5.4 while loop endless
    def p_stmWhileLoopEndless (self, p):
        'statement : while lBracket rBracket lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.infLoop, [p[5]], ASTpos(p, 1))


    # 3.2.6) function call
    def p_fcParamList (self, p):
        """fcParamList :
                | exp
                | fcParamList comma exp 
        """
        l = len(p)
        if l == 1:
            p[0] = []
        elif l == 2:
            p[0] = [p[1]]
        else:
            p[1].append(p[3])
            p[0] = p[1]
    
    def p_fcParamListCompl (self, p):
        'fcParamListCompl : lBracket fcParamList rBracket'
        p[0] = p[2]
    
    def p_stmFunctionCall (self, p):
        'statement : fcParamListCompl assign name fcParamListCompl semicolon'
        # look if there is still an entry of that function
        p[0] = ASTstatement(ASTstatementtype.funcCall, [p[1] ,p[3] ,p[4]], ASTpos(p, 1))

    # 3.2.7 comment
    def p_stmComment (self, p):
        'statement : comment'
        p[0] = ASTstatement(ASTstatementtype.comment, [p[1]], ASTpos(p, 1))

    # 3.2.8 variable operations
    def p_stmVariableOperation (self, p):
        'statement : name lBracket operationParamList rBracket semicolon'
        p[0] = ASTstatement(ASTstatementtype.varOperations, [p[1],p[3]], ASTpos(p, 1))

    def p_operationParamList (self, p):
        """operationParamList :
            | name assign exp
            | operationParamList comma name assign exp
        """ 
        l = len(p)
        if l <= 1:
            p[0] = {}
        elif l == 4:
            p[0] = {p[1] : p[3]}
        else:
            p[1][p[3]] = p[5]
            p[0] = p[1]
    
    def p_checkButtonPressed (self, p):
        'statement : checkButtonPressed lSoftBrace var rSoftBrace lBrace statements rBrace'
        p[0] = ASTstatement(ASTstatementtype.checkButton, [p[3], p[6]], ASTpos(p, 1))

    def p_update (self, p):
        'statement : update lSoftBrace var rSoftBrace semicolon'
        p[0] = ASTstatement(ASTstatementtype.update, p[3], ASTpos(p, 1))
        
    # error rule
    def p_error(self, p):
        self.YACC_printErrorAndAbort(str(p.value), p.lineno, p.lexpos)            


# create a dict with the name as key from a variable list
# dict = (name) = (type, number, pos)
def createVarDictFromVarlist (vl):
    vd = {}
    for v in vl:
        vd[v[0][1]] = (v[0][0], v[1], v[0][2])
    return vd

# create a dict with the name as key from a variable list
def createVarDictFromParamlist (pl):
    vd = {}
    for p in pl:
        if (p[0] == ASTtype.globalVar) or (p[0] == ASTtype.localVar) :
            vd[p[1][1]] = (p[1][0], p[2], p[1][2])
    return vd


# unify varDict1 and varlist2 and check double occurrence
def unifyVariables  (vd1, vd2):
    vud = {}
    for name, info in vd1.items():
        cv = vd2.get(name, None)
        if (cv != None) :
            return (False, (name, info))
        vud[name] = info
    for name, info in vd2.items():
        vud[name] = info
    return (True, vud)

# the base class for translated objects
class translatedElement (object):
    filePos = None
    level = 0
    def __init__(self, filePos, level = 0):
        self.filePos = copy.deepcopy(filePos)
        self.level = copy.deepcopy(level)

    def __repr__ (self):
        return 'fpos=%s level=%s' % (str(self.filePos), str(self.level))
    
    def __str__ (self):
        return self.__repr__()
    
    def dumpIntoFile (self, f):
        pass

# a translated function
class translatedStm (translatedElement):
    def __init__(self, name, params, filePos, level = 0):
        super(translatedStm, self).__init__(filePos, level)
        self.ALasm_fname = copy.deepcopy(name)
        self.ALasm_params = copy.deepcopy(params)

    def __repr__ (self):
        return '%s p=%s %s' % (self.ALasm_fname, str(self.ALasm_params), super(translatedStm, self).__repr__())

    def __str__(self):
        return '{name} {params}'.format(name=self.ALasm_fname, params=self.ALasm_params)
    
    def dumpIntoFile (self, f):
        i = 0
        while (i < self.level):
            f.write ('\t')
            i += 1
        f.write (self.ALasm_fname)
        f.write (' ')
        i = 0
        for p in self.ALasm_params:
            if i != 0:
                f.write (', ')
            if isinstance(p, VariableAtExpression):
                f.write (p.getName())
            else:
                f.write (str(p))
            i += 1
        f.write (';\n')


# a translated function
class translatedCall (translatedElement):
    def __init__(self, fname, inputV, outputV, filePos, level = 0):
        super(translatedCall, self).__init__(filePos, level)
        self.fname = copy.deepcopy(fname)
        self.iV = copy.deepcopy(inputV)
        self.oV = copy.deepcopy(outputV)

    def __repr__ (self):
        return '[%s] %s [%s]' % (str(self.oV), self.fname, str(self.iV))

    def dumpIntoFile (self, f):
        raise 'tra'

# a translated variable
class translatedVariable (translatedElement):
    def __init__(self, typeName, name, amount, filePos, level = 0):
        super(translatedVariable, self).__init__(filePos, level)
        self.name = name
        self.typeName = typeName
        self.amount = amount
        
    def dumpIntoFile (self, f):
        i = 0
        while (i < self.level):
            f.write ('\t')
            i += 1
        f.write (self.typeName)
        f.write (' ')
        f.write (self.name)
        if (self.amount > 1):
            f.write ('[')
            f.write(str(self.amount))
            f.write (']')
        f.write(';\n')

# a translated variable
class translatedComment (translatedElement):
    def __init__(self, comment, filePos, level = 0):
        super(translatedComment, self).__init__(filePos, level)
        self.comment = comment

    def __repr__ (self):
        return 'comment="%s" %s' % (self.comment, super(translatedComment, self).__repr__())
        
    def dumpIntoFile (self, f):
        i = 0
        while (i < self.level):
            f.write ('\t')
            i += 1
        if (self.comment.count('\n') > 0):
            f.write ('/*')
            f.write (self.comment.replace('\n','\n'+self.levelprefix))
            f.write ('*/')
        else:
            f.write ('//')
            f.write (self.comment)
        f.write('\n')

class VariableAtExpression(object):
    def __init__(self, varName, varType, RefListSubValues, value):
        self.vname = varName
        self.vtype = varType
        self.value = value
        if RefListSubValues is not None:
            self.refSub = RefListSubValues
        else:
            self.refSub = []
             
    def __repr__ (self):
        return 'name = "{name}" type = "{type}"'.format(name=self.getName(), type=self.vtype)
    
    def getType(self):
        return self.vtype 
    
    def addSubValue (self, sv):
        self.refSub.append(sv)
        
    def getName (self):
        svt = ''
        for sv in self.refSub:
            svt += '{sep}{sv}'.format(sep=gCD.typeSeperator, sv=sv)
        return '{name}{subval}'.format(name=self.getBaseName(), subval=svt)
    
    def getBaseName (self):
        return self.vname

    def setBaseName (self, newName):
        self.vname = newName

    
    # searches the actual variable declaration dict for the type of the variable 
    def associateType (self):
        # first find the type
        (t, pos, amount) = gCD.vD.get(self.getBaseName(), (None, None, None))
        (tD, amount, pos) = gCD.typedef.get(t, (None, None, None))
        # look if we have an subtype
        for sv in self.refSub:
            #gCD.typedef
            (t, pos, amount) = tD.get(sv, (None, None, None))
            if t is None:
                return (False, 'at variable "{vname}": the subvalue "{subval}"is not defined or has no associated type'.format(vname=self.getBaseName(), subval=sv))
        # ok we found a type -> lets save it
        self.vtype = t
        return (True, None)
    
    # gets the value of the variable
    def getValue(self):
        return self.value

class CompilerData (object):
    def __init__(self):
        # compile mode
        self.cCompileMode_preCompile     = 1
        self.cCompileMode_compile        = 2
        
        self.compileMode = self.cCompileMode_preCompile
        # the label counter    
        self.labelCounter = 1
        # the level counter
        self.level = 0
        # global var dict
        self.gVD = {}
        # variable dictionary (joined from global, local and function params)
        self.vD = {}
        # the dict of the expanded variables (the user types are expanded) 
        self.expVD = {}
        # variable prefix
        self.functionVarPreFix = 1
        # constant lists
        self.constVarList = {}
        self.constPreFix = 'genConst_'
        self.constCounter = 1
        # types
        self.typedef = {}
        self.typeSeperator = '_'
        
        # AST stuff
        self.AST = None
        self.ASTmainDict = {} 
        self.ASTfunctionDict = {}
    
        # compilemode vars
        self.preCompiledFunctions = {}
        
        # name association
        self.cALcToALasmVarname = {
            'rational':  ('rational', None),
            'integer': ('integer', None),
            'string' : ('string', None),
            'complex': ('complex', None),
            'biquad' : ('biquad', None),
            'delay' : ('delay', None),
            'FFT': ('FFT', None),
            'panel' : ('panel', None),
            'button' : ('button', None),
            'led' : ('led', None),
            'display': ('display', None),
            # extend types
            'lp' : ('biquad', 'initBiquadAsLP <index>,<fs>,<fc>,<BQA>'),
            'hp' : ('biquad', 'initBiquadAsHP <index>,<fs>,<fc>,<BQA>')
            }
        # stm handler association
        self.cStmTranslateFunction = {}
        
        # id -> ALAsm name, index, conversion string
        self.ALvartypeToConstFunctionD = {
                ASTvartype.fnumber : ('ALASMsetRational', False, '[%f]', float),
                ASTvartype.inumber : ('ALASMsetInt', False, '[%i]', int),
                ASTvartype.string  : ('ALASMsetStr', True, '%s', str)
            }
        
    def __repr__ (self):
        return 'labelCounter=%s variable dict=%s)' % (self.labelCounter, self.vD)
    
    def reset(self):
        self.labelCounter = 1
        self.level = 0
        self.vD = {}
        self.expVD = {}
        self.gVD = {}
        self.constVarList = {}
        self.constCounter = 1
        self.typedef = {}
        self.AST = None
        self.ASTmainDict = {}
        self.ASTfunctionDict = {}
        self.compileMode = self.cCompileMode_compile
        self.preCompiledFunctions = {}
        self.functionVarPreFix = 1
        
    def createLabel (self):
        r = '@labelNr'+str(self.labelCounter)
        self.labelCounter += 1
        return r

    def isParamLabel (self, p):
        if isinstance(p, str) == False :
            return False;
        if p[0] == '@':
            return True
        else:
            return False;

    def getFunctionVarPreFix (self):
        r = self.functionVarPreFix
        self.functionVarPreFix += 1
        return 'vpfx%i' % (r)

    def setGlobalVarDict (self, gVD):
        self.gVD = gVD
    
    def resetVarDict (self):
        self.vD = self.gVD 
                
    def joinVariableDicts(self, nVD):
        (res, ret) = unifyVariables(self.vD, nVD)
        if (res == True):
            self.vD = ret
        else:
            print (ret)
        return res
    
    def findConstant (self, constName):
        for (ctype, tD) in self.constVarList.items():
            for (value, var) in tD.items():
                if (var.getName() == constName):
                    return value
        return None

    def findVariableOrConst (self, v):
        # get name
        if isinstance(v, VariableAtExpression):
            vn = v.getName()
        else:
            vn = v
        # look up at the working varaible dict
        var = self.vD.get(vn, None)
        if var is not None:
            return var
        # look at the constants
        for (ctype, tD) in self.constVarList.items():
            for (value, var) in tD.items():
                if (var.getName() == vn):
                    return var
        return None


    # resolve the types
    def setTypedefReplaces(self, typDefs):
        self.typedef = {}
        for (typename, subvalues, position) in typDefs:
            self.typedef[typename] = (self.typedefSubvalueReplace(subvalues, 1), int(1),position)
        return (True, None)
    
    # replaces the sub types of the type 
    def typedefSubvalueReplace (self, lsv, numberOfElements):
        translSV = {}
        # lsv = list sub values as AST
        for (utype, name, amount), pos in lsv:
            # take the varaible type an make a look up at the list
            td = self.typedef.get(utype, None)
            if td is not None:
                translSV[name] = (td, amount * numberOfElements, pos)
            else:
                translSV[name] = (utype, amount * numberOfElements, pos)
        return translSV
    
    # expandes a varaible
    # example:
    # type point {
    #    rational x;
    #    rational y;
    # }
    #
    # point a
    #
    # is transformed
    #
    # rational a_x
    # rational a_y
    def expandVariable (self, vname, vtype, vamount):
        # get the replace pattern
        replpattern, amount, pos = self.typedef.get(vtype, (None, None, None))
        if replpattern is None:
            return (False, 'type "{type}" of variable "{vname}"'.format(type=type, vname=vname))
        # ok let's replace
        vL = self._expandVarFromDict(vname, vamount, replpattern)
        # and return
        return (True, vL)

    def _expandVarFromDict (self, varname, amount ,vd):
        vL = []
        for subvalName, (type, subamount, pos) in vd.items():
            newName = '{varname}{sep}{subval}'.format(varname=varname, sep=self.typeSeperator, subval=subvalName)
            newAmount = amount * subamount
            if isinstance(type, dict):
                vL += self._expandVarFromDict(newName, newAmount, type)
            else:
                vL.append((newName, type, pos, newAmount))
        return vL

    # expands the varaibels with a user defined type at a dict    
    def expandVarDict (self, vd):
        nvd = {}
        for vname, (type, pos, amount) in vd.items():
            # check if the varaible has a user type
            if type in self.typedef:
                # expand
                res, expVL = self.expandVariable(vname, type, amount)
                if res is False:
                    return (False, 'error expand variable dictionary. Error:\n{err}'.format(err=expVL))
                # ok let's add the varaibles to the dict
                for ev_name, ev_type, ev_Pos, ev_amount in expVL:
                    nvd[ev_name] = (ev_type, ev_Pos, ev_amount)
            else:
                nvd[vname] = (type, pos, amount)
        return (True, nvd)
    
    # create the var dict with the expanded types
    def updateExpandedVarDict (self):
        r, nvd = self.expandVarDict(self.vD)
        if r is True:
            self.expVD = nvd
            return (True, None)
        else:
            self.expVD = {}
            return (False, nvd)
        
    def setStmTranslateFunction (self, dStmTranslFunc):
        self.cStmTranslateFunction = dStmTranslFunc
        
    def setVariableOperationTranslations (self, varOPtrans):
        self.varOperationTranslation = varOPtrans

    def setArithOpTranslations (self, arithTrans):
        self.ArithOpTranslation = arithTrans


    def translateASTstm (self, ASTstm):
        tf = self.cStmTranslateFunction.get(ASTstm.stmType, None)
        if (tf == None):
            return (False, 'skip '+str(ASTstm)+'\n')
        else :
            return tf(ASTstm)

    def createConstant(self, constType, value):
        # check if an entry still exists
        classEntry = self.constVarList.get(constType, None)
        if classEntry == None:
            self.constVarList[constType] = {}
        # ok entry now exits
        # check if we get a value
        for vn, var in self.constVarList[constType].items():
            if var.getValue() == value:
                return var
        constName = '%s%i' % (self.constPreFix, self.constCounter)
        var = VariableAtExpression(constName, constType, None, value)
        self.constVarList[constType][value] = var 
        self.constCounter += 1
        return var
    
    def createConstantInitCode (self, var, value):
        if (isinstance(value, list) == True) or (isinstance(value, tuple) == True) :
            value = value[1]
        # find id to the type
        vtID = ASTvartype.numberAsso.get(var.getType(), None)
        if (vtID == None):
            return [translatedComment('type %s of the variable "%s" is not supported for constant code generation' %(var.getType(), var.getName()), None , 0)]
        # get generation template
        gt = self.ALvartypeToConstFunctionD.get(vtID, None)
        if (gt == None):
            return [translatedComment('there is no constant generation template for the type %s of the variable "%s" ' %(var.getType(), var.getName()), None , 0)]
        # build param list
        # 1st name
        pL = [var]
        if gt[1] == True:
            pL.append('0')
        val = gt[3](value)
        pL.append(gt[2] % (val,))
        return [translatedStm(gt[0],pL, None, 0)]
    
    def start (self, ast):
        self.reset()
        #1.) build function dict and find main function
        index = 0
        self.ASTfunctionDict = {}
        for f in ast:
            if f[0] == ASTtype.function:
                self.ASTfunctionDict[f[1][0]] = index
            elif f[0] == ASTtype.main:
                if None == self.ASTmainDict.get(f[3], None):
                    self.ASTmainDict[f[3]] = index
                else:
                    return (False, 'main target "%s" is multiple declared' % (f[3]))
            index += 1
        #2.) create typedef replacements
        typeDefRepl = []
        for f in ast:
            if f[0] == ASTtype.typedef:
                (typename, values) = f[1]
                position = f[2]
                # check if type already exists
                if len([res for res in typeDefRepl if res[0] == typename]) > 0:
                    return (False, 'type {typename} was allready declared before @{pos}'.format(typename=typename, pos=position))
                typeDefRepl.append((typename, values, position))
        #2.1) resolve the inner typedef declarations
        self.setTypedefReplaces(typeDefRepl)
        
        #3.) building global varList
        gVL = []
        for f in ast:
            if f[0] == ASTtype.globalVar:
                gVL += f[1]
        
        # and translate into a dict
        gCD.setGlobalVarDict(createVarDictFromVarlist(gVL))
        
        #4.) save ast
        self.AST = ast 
        
        return (True, None)

    def translateCodeList (self, ASTstmL):
        translCode = []
        # gen code
        for ASTstm in ASTstmL:
            tf = self.cStmTranslateFunction.get(ASTstm.stmType, None)
            if (tf == None):
                print('skip '+str(ASTstm)+'\n')
                tf = []
            else :
                (r, tc) = tf(ASTstm)
                if (r == False):
                    return (False, tc)
                else:
                    if (type(tc) is list):
                        translCode += tc
                    else:
                        translCode.append(tc)
        return (True, translCode)
    
    def createfunctionCode (self, lD, pD, ASTstmL):
        # reset
        self.resetVarDict()
        # local vars
        # join global and local vars
        if (False == self.joinVariableDicts(lD)):
            return (False, 'joining local and global vars failed')

        # parameter vars
        # build params list
        # join global & local vars with the parameters
        if (False == self.joinVariableDicts(pD)):
            return (False, 'joining parameters to the vars failed')
        
        self.updateExpandedVarDict()
        # translate code
        return self.translateCodeList(ASTstmL)
        
    
    def translateASTtoALASM (self, ast, oDir):
        #0.) return list
        fileDumpL = []        
        
        #1.) setups & resets
        print ('start ...')
        self.start(ast)
        
        #2.) pre compile
        print ('pre compile ...')
        (res, fc) = self.preCompile()
        if res == False:
            return (res, fc)
        
        #3.) create code for the main function
        print ('compile mains ...')
        for (mname, mfindx) in self.ASTmainDict.items():
            print('build %s ...' % mname)
            # get the AST containing the statements
            ASTmain = self.AST[mfindx]
            # get the AST containing the local vars
            ASTmainLocVar = ASTmain[1][0]
            
            # make a dict from varaible list
            mainLocVarD = createVarDictFromVarlist(ASTmainLocVar)
            
            (res, fc) = self.createfunctionCode (mainLocVarD , {}, ASTmain[1][1])
            if res == False:
                return (res, fc)
            (res, mainVarD) = unifyVariables(self.gVD, mainLocVarD)
            if res == False:
                return (res, mainVarD)
            
            # search const list and create const vars
            cvD = {}
            startupCode = []
            for (constType, cVD) in self.constVarList.items():
                for (value, constVar) in cVD.items():
                    # insert constant into variable list (name) = (type, NO POSITION, amount=1)
                    cvD[constVar.getName()] = (constType, None, 1)
                    startupCode += self.createConstantInitCode(constVar, value)
            
            (res, mainVarD) = unifyVariables(mainVarD, cvD)
            if res == False:
                return (res, mainVarD)


            fc = startupCode + fc
            # resolve functions
            loopProt = 100
            i = 0
            print('resolve links of %s ...' % mname)
            unresfc = self.getUnresolvedFunctioncallsNumber(fc)
            while (unresfc):
                (res ,mainVarD, fc) = self.resolveFunctionCalls(mainVarD, fc)
                if res == False:
                    return (False, mainVarD)
                unresfc = self.getUnresolvedFunctioncallsNumber(fc)
                i += 1
                if (i == loopProt):
                    return (False, 'loop protection at main with target="%s"' % (mname))
            # ok all is translated
            # lets expand the variables with a user defined type
            res, mainVarD = self.expandVarDict(mainVarD)
            if res is False:
                return (False, mainVarD)
            
            # open file and write code
            nameFile = os.path.join(oDir ,mname)
            fileDumpL.append(nameFile)
            tfn = os.path.join(nameFile + '.alasm')
            print('dump into %s ...' % tfn)
            df = open(tfn,'w')
            self.dumpTranslatedCode (df, mname, mainVarD, fc)
            df.close ()
            print('finished!')
            
        return(True, fileDumpL)

    
    def preCompile (self):
        # set the mode to pre compile
        self.compileMode = self.cCompileMode_preCompile
        # translate function
        for (n, ASTindx) in self.ASTfunctionDict.items():
            # AST stuff
            fAST = self.AST[ASTindx]
            localVarList = fAST[1][2]
            paramVarList = fAST[1][1]
            stmList = fAST[1][3]
            
            # varaiable List -> variable dict
            lvD = createVarDictFromVarlist(localVarList)
            pvD = createVarDictFromParamlist(paramVarList)
            
            # code creation
            (r, c) = self.createfunctionCode(lvD, pvD, stmList);
            if r == False:
                return (r, c)
            self.preCompiledFunctions[n] = c 
        self.compileMode = self.cCompileMode_compile
        return (True, None)
    
    def resolveFunctionCalls (self, vD, fcL):
        nfcL = []
        nvD = copy.deepcopy(vD)
        for f in fcL:
            if not(isinstance(f, translatedCall)):
                nfcL.append(f)
            else:
                fname = f.fname
                # build search an replace list
                ASTfuncIndex = self.ASTfunctionDict.get(fname ,None)
                if (ASTfuncIndex == None):
                    return (False, 'unknwon function "%s"'%(fname))
                ASTf = self.AST[ASTfuncIndex]
                fTranslCode = self.preCompiledFunctions.get(fname ,None)
                if (fTranslCode == None):
                    return (False, 'function "%s" wasn\'t compiled' %(fname))
                
                assoDict = {}
                # create the parameter var list by kicking the comments
                pV = []
                for p in ASTf[1][1]:
                    if (p[0] == ASTtype.globalVar) or (p[0] == ASTtype.localVar) :
                        pV.append(p)
                
                # create the local var list
                lV = ASTf[1][2]
                
                localVarPrefix = self.getFunctionVarPreFix()
                # first add local vars
                for v in lV:
                    assoDict[v[0][1]] = localVarPrefix + v[0][1] 

                inpL = []
                outpL = []
                for v in pV:
                    if v[0] == ASTfunctionInterface.input:
                        inpL.append(v[1])
                    elif v[0] == ASTfunctionInterface.output:
                        outpL.append(v[1])
                    elif v[0] == ASTfunctionInterface.inout:
                        inpL.append(v[1])
                        outpL.append(v[1])
                    else:
                        return (False, 'unknown paramter class in function "%s"' % (fname) ,None)

                # check the lists
                fiL = f.iV
                foL = f.oV
                # number check
                if (len(fiL) != len(inpL)):
                    return (False, 'input parameter number is not equal of the defined one at function "%s"' % (fname),None)
                if (len(foL) != len(outpL)):
                    return (False, 'output parameter number is not equal of the defined one at function "%s"' % (fname),None)
                # type and var check
                # 1st input
                i = 0
                for v in fiL:
                    # check if name exists
                    var = v[1]
                    vName = var.getBaseName()
                    vt = nvD.get(vName, None)
                    inpType = inpL[i][0]
                    if None == vt:
                        return (False, 'input variable %s at function %s is not defined' % (vName, fname), None)
                    vt = vt[0]
                    # check type
                    if (inpType != vt):
                        return (False, 'input variable %s at function %s: type differs %s vs. %s' % (vName, fname, inpType, vt), None)
                    # ok add to asso list
                    assoDict[inpL[i][1]] = vName
                    i += 1
                # 2nd output
                i = 0
                for v in foL:
                    # check if name exists
                    var = v[1]
                    vName = var.getBaseName()
                    vt = nvD.get(vName, None)
                    outpType = outpL[i][0]
                    
                    if None == vt:
                        return (False, 'output variable "%s" at function "%s" is not defined' % (vName, fname), None)
                    vt = vt[0]
                    # check type
                    if (outpType != vt):
                        return (False, 'output variable "%s" at function "%s": type differs %s vs. %s' % (vName, fname, outpType, vt), None)
                    # ok add to asso list
                    assoDict[outpL[i][1]] = vName
                    i += 1
                # find labels
                i = 0
                labelReplacement = {}
                for fc in fTranslCode:
                    if isinstance(fc, translatedStm):
                        j = 0
                        for p in fc.ALasm_params:
                            if (self.isParamLabel(p) == True) :
                                labelReplacement[p] = self.createLabel()
                            j += 1
                    i += 1    
                # ready
                # start appending code
                nfcL.append(translatedComment('function inline for "%s"' % (fname), None, self.level))
                # search the translated code for the names of the variables & labels and replace them
                i = 0
                for fc in fTranslCode:
                    nfc = copy.deepcopy(fc)
                    nfc.level += 1
                    if isinstance(nfc, translatedStm):
                        j = 0
                        for p in nfc.ALasm_params:
                            # variable?
                            if isinstance(p, VariableAtExpression):
                                replP = assoDict.get(p.getBaseName(), None)
                                if (replP != None):
                                    nfc.ALasm_params[j].setBaseName(replP)
                            # label?
                            elif self.isParamLabel(p) == True:
                                nfc.ALasm_params[j] = labelReplacement[p]
                            # something other lets leave untuched
                            else:
                                nfc.ALasm_params[j] = p
                            j += 1
                    nfcL.append(nfc)
                    i += 1    
                # insert code
                # add local vars
                for v in lV:
                    nn = assoDict[v[0][1]]
                    vtype = v[0][0]
                    vamount = v[0][2]
                    nvD[nn] = (vtype, v[1], vamount)
        return (True, nvD, nfcL)
    
    def getUnresolvedFunctioncallsNumber (self, fcL):
        i = 0
        for f in fcL:
            if isinstance(f, translatedCall):
                i += 1
        return i

    def createDumpVarlist (self, lVD):
        gvl = []
        lvl = []
        for vn, vv in lVD.items():
            (vtype,pos,amount) = vv
            if None != self.gVD.get(vn, None):
                gvl.append(translatedVariable(vtype, vn, amount, pos, 0))
            else:
                lvl.append(translatedVariable(vtype, vn, amount, pos, 1))
        return (gvl, lvl)

    def dumpTranslatedCode (self, df, mainName, mainVarD, fc):
        (gvl, lvl) = self.createDumpVarlist(mainVarD)
        df.write ('globals {\n')
        for v in gvl:
            v.level += 1
            v.dumpIntoFile(df)        
        df.write ('}\n\n')
        
        df.write ('function %s\n' % (mainName))
        df.write ('locals {\n')
        for v in lvl:
            v.level += 1
            v.dumpIntoFile(df)               
        df.write ('}\n')        
        df.write ('code {\n')
        for f in fc:
            f.level += 1
            f.dumpIntoFile(df)
        df.write ('}\n')
    
# global instance
gCD = CompilerData()


# result = (var exists, is variable, type)
def translateParameterFromALcToALasm (p):
    if len(p) == 3:
        ASTident, var, pos = p
    else:
        ASTident, var, pos = (p[0], p[1], None)
        
    if ASTident == ASTvartype.variable:
        r, err = var.associateType()
        if r is False:
            return (False, False, 'unknown type "{vtype}" for variable "{var}"'.format(vtype=var.vtype, var=var.vname))
        else:
            return (True, True, var.vtype)
    elif ASTident == ASTvartype.inumber:
        return (True, False, 'integer')
    elif ASTident == ASTvartype.fnumber:
        return (True, False, 'rational')
    elif ASTident == ASTvartype.string:
        return (True, False, 'string')
    else :
        return (False, False, 'unknown AST variable type (%s)' % (p))

def translateFunction_assign (ASTstm):
    # check what kind of assignment
    # type 1: a = const
    # or type 2: a = b
    if ASTstm.params[1][0] == ASTvartype.variable:
        return translateFunction_mathExp (ASTstm,'=')
    # use the constant init code creation function to generate some code
    var = ASTstm.params[0][1]
    var.associateType()
    constVal = ASTstm.params[1][1]

    return (True, gCD.createConstantInitCode(var, constVal))

def translateFunction_addAssign (ASTstm):
    return translateFunction_mathExp (ASTstm,'+=')


def translateFunction_mathExp (ASTstm, mathOpName):
    # find main math operation
    opFuncDict = gCD.ArithOpTranslation.get(mathOpName, None)
    fParams = ASTstm.params
    
    # params layout
    # p = (AST typeID, constant) or (AST typeID, variable, variable index) 
    
    # collect parameter types and match them against the templates
    searchTuple = []
    for p in fParams:
        # variables
        if len(p) == 3:
            (pType, pVar, pVarIndex) = p
        else:
        # constants
            (pType, pVar) = p
            pVarIndex = None
            
        (rParams, isVar, vType) = translateParameterFromALcToALasm((pType, pVar))
        if (rParams == False):
            return (False, vType)
        searchTuple.append(vType)
    
    searchTuple = tuple(searchTuple);

    
    targetFunctionTempl = opFuncDict.get(searchTuple, None)
    if targetFunctionTempl == None:
        return (False, 'math expression %s with %s is unknown' %(mathOpName,str(searchTuple)))
    
    # ok lets geht some template data
    (alasmFuncN, ParamTemplL) = targetFunctionTempl
    # 1. setup phase
    # build up dest parameter list with no entries
    DestParamL = [None] * len(ParamTemplL)
    
    # 2. generate src parameter list
    # typeID = (
    #     v - variable name -> typeData = AL type of the parameter
    #     i - index of variable  -> typeData = None
    #     c - constant-> typeData = AL type of the parameter
    #     e - expression = can be variable or constant
    # )
    for (srcIndx, destIndx, typeID, typeData) in ParamTemplL:
        pValue = fParams[srcIndx]
        # check if we have as target not an index
        if typeID is not 'i':
            # check if there is an variable in it
            if pValue[0] == ASTvartype.variable:
                # yes!
                DestParamL[destIndx] = pValue[1]
            else:
                # no -> lets try to create an constant
                DestParamL[destIndx] = gCD.createConstant(typeData,pValue[1])
        else:
            # index
            # lets check if we have an varaible or expression
            if len(pValue) is 3:
                DestParamL[destIndx] = pValue[2]
            else:
                DestParamL[destIndx] = int(0)
    return (True, translatedStm(alasmFuncN,DestParamL, ASTstm.srcPos, gCD.level)
)

def translateFunction_add (ASTstm):
    return translateFunction_mathExp (ASTstm,'+')
    
def translateFunction_sub (ASTstm):
    return translateFunction_mathExp (ASTstm,'-')

def translateFunction_mul (ASTstm):
    return translateFunction_mathExp (ASTstm,'*')

def translateFunction_div (ASTstm):
    return translateFunction_mathExp (ASTstm,'/')

def translateFunction_mod (ASTstm):
    return translateFunction_mathExp (ASTstm,'%')

def translateFunction_less (ASTstm):
    return translateFunction_mathExp (ASTstm,'<')

def translateFunction_more (ASTstm):
    return translateFunction_mathExp (ASTstm,'>')

def translateFunction_lessEqual (ASTstm):
    return translateFunction_mathExp (ASTstm,'<=')

def translateFunction_moreEqual (ASTstm):
    return translateFunction_mathExp (ASTstm,'>=')

def translateFunction_equal (ASTstm):
    return translateFunction_mathExp (ASTstm,'==')

def translateFunction_nEqual (ASTstm):
    return translateFunction_mathExp (ASTstm,'!=')


def translateFunction_for (ASTstm):
    forInitCode = ASTstm.params[0]
    forExitCond = ASTstm.params[1]
    forLoopCode = ASTstm.params[2]
    forInnerCode = ASTstm.params[3]
    transLC = []
    # startup
    (r, tcL) = gCD.translateCodeList([forInitCode])
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    
    # create loop label
    loopLabel = gCD.createLabel()
    labelLoopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    labelLoopInstr.ALasm_fname =  'label'
    labelLoopInstr.ALasm_params = [loopLabel]
    transLC.append(labelLoopInstr)

    # generate loop instr
    loopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    loopInstr.ALasm_fname = 'jump'
    loopInstr.ALasm_params = [loopLabel] 


    
    # create condition code
    (r, tc) = gCD.translateCodeList([forExitCond])
    if (r == False):
        return (r, tc)
    transLC += tc

    # create loop end label
    exitLabel = gCD.createLabel()
    labelExitInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    labelExitInstr.ALasm_fname = 'label'
    labelExitInstr.ALasm_params = [exitLabel] 

    # generate condition check instr
    condCheckInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    condCheckInstr.ALasm_fname = 'jumpNCF'
    condCheckInstr.ALasm_params = [exitLabel] 
    transLC.append(condCheckInstr)
    
    #generate inner for loop code
    (r, tc) = gCD.translateCodeList(forInnerCode)
    if (r == False):
        return (r, tc)
    transLC += tc
    
    #generate loop code
    (r, tc) = gCD.translateCodeList([forLoopCode])
    if (r == False):
        return (r, tc)
    transLC += tc

    # addjump label
    transLC.append(loopInstr)
    # and add loop label
    transLC.append(labelExitInstr)
    return (True, transLC)

def translateFunction_while (ASTstm):
    condExp = ASTstm.params[0]
    loopCode = ASTstm.params[1]
    
    transLC = []
    
    # create loop label
    loopLabel = gCD.createLabel()
    labelLoopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    labelLoopInstr.ALasm_fname =  'label'
    labelLoopInstr.ALasm_params = [loopLabel]
    transLC.append(labelLoopInstr)

    # generate loop instr
    loopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    loopInstr.ALasm_fname = 'jump'
    loopInstr.ALasm_params = [loopLabel] 


    
    # create condition code
    (r, tc) = gCD.translateCodeList([condExp])
    if (r == False):
        return (r, tc)
    transLC += tc

    # create loop end label
    exitLabel = gCD.createLabel()
    labelExitInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    labelExitInstr.ALasm_fname = 'label'
    labelExitInstr.ALasm_params = [exitLabel] 

    # generate condition check instr
    condCheckInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    condCheckInstr.ALasm_fname = 'jumpNCF'
    condCheckInstr.ALasm_params = [exitLabel] 
    transLC.append(condCheckInstr)
    
    #generate inner for loop code
    (r, tc) = gCD.translateCodeList(loopCode)
    if (r == False):
        return (r, tc)
    transLC += tc
    
    # addjump label
    transLC.append(loopInstr)
    # and add loop label
    transLC.append(labelExitInstr)
    
    return (True, transLC)


def translateFunction_call (ASTstm):
    resParam = ASTstm.params[0]
    functionName = ASTstm.params[1]
    inpParam = ASTstm.params[2]
    
    ASTindx = gCD.ASTfunctionDict.get(functionName, None)
    if (ASTindx == None):
        return (False, '"%s" function doesn\'t exists' % (functionName))
    
    return (True, translatedCall(functionName, inpParam, resParam, ASTstm.srcPos, gCD.level + 1))

def translateFunction_infLoop (ASTstm):
    loopCode = ASTstm.params[0]
    # create loop label
    loopLabel = gCD.createLabel()
    labelLoopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    labelLoopInstr.ALasm_fname =  'label'
    labelLoopInstr.ALasm_params = [loopLabel]
    transLC = [labelLoopInstr]
        
    # startup
    (r, tcL) = gCD.translateCodeList(loopCode)
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    
    # generate loop instr
    loopInstr = translatedStm('',[], ASTstm.srcPos, gCD.level)
    loopInstr.ALasm_fname = 'jump'
    loopInstr.ALasm_params = [loopLabel] 
    transLC.append (loopInstr)
    return (True, transLC)

def translateFunction_comment (ASTstm):
    comment = ASTstm.params[0]
    if (comment.count('\n') <= 0) :
        Instr = translatedStm('//'+comment,[], ASTstm.srcPos, gCD.level)
    else:
        Instr = translatedStm('/*'+comment+'*/',[], ASTstm.srcPos, gCD.level)
    return (True, Instr)

def translateFunction_varOperations (ASTstm):
    operationClass = ASTstm.params[0]
    operationParams = ASTstm.params[1]

    opC = gCD.varOperationTranslation.get(operationClass,None)
    if (opC is None):
        return (False, 'variable operation "'+str(opC)+'" is unknown')
    if (opC[0] is not None) :
        opCsubKey = opC[0]
        opCOperationsDict = opC[1]
        
        paramKey = operationParams.get(opCsubKey, None)
        paramExpTypeID = paramKey[0]
        if (paramExpTypeID != ASTvartype.variable):
            return (False, 'operation parameter "'+str(opCsubKey)+'" must be associated with a variable')
        param = paramKey[1]
        if (param is None):
            return (False, 'variable operation parameter "'+str(opCsubKey)+'" is not defined')
        
        if isinstance(param, VariableAtExpression):
            paramName = param.getName()
        else:
            paramName = param
        
        instrTemplate = opCOperationsDict.get(paramName, None)
        if instrTemplate is None:
            return (False,'no instruction template for parameter "{paramName}"'.format(paramName=paramName))
    else:
        instrTemplate = opC[1]

    # substitude
    funcParam = []
    for (pName, pALtype, ptype, pDefaultValue) in instrTemplate[1]:
        pValue = operationParams.get(pName, None)
        # handle unknown keywords
        if (pValue is None) and (ptype == 'v') and (pDefaultValue is None):
            return (False, 'the parameter {pName} must be associated with a variable. Error at:\n{AST}'.format(pName=pName,AST=ASTstm))
        # check if a value for paramter is entered
        if pValue is not None:
            # yes!
            # check if the value is a number
            if len(pValue) == 2:
                # ok number
                if ptype == 'c':
                    # the paramteris a number -> ok lets save it
                    funcParam.append(pValue[1])
                else:
                    # the parameter is varaible
                    # create a constant
                    cv = gCD.createConstant(pALtype,pValue[1])
                    funcParam.append(cv)
            else:
            # ok value is variable
            # lets check if the function wants a variable
                if ptype == 'v':
                    # super! lets save it
                    funcParam.append(pValue[1])
                else:
                    return (False, 'function require a variable (name={vname} type={vtype}) and a constant({constVal}) is entered'.format(vname=pName,vtype=pALtype,constVal=pValue[1]))            
        else:
            # no!
            if ptype == 'c':
                # the paramteris a number -> ok lets save it
                funcParam.append(pDefaultValue)
            else:
                # the parameter is varaible
                # create a constant
                if pDefaultValue == None:
                    return (False, 'default parameter is None. Therefore a constant varaible can not be created. The operation class is "{opclass}". The template parameters are {tmplParam}.'.format(opclass=operationClass,tmplParam=operationParams) )
                cv = gCD.createConstant(pALtype,pDefaultValue)
                funcParam.append(cv)
    # lets check the parameter list
    j = 0;
    for f in funcParam:
        if f is None:
            (pName, pALtype, ptype, pDefaultValue) = instrTemplate[1][j]
            return (False, 'function parameter {pName}(type {altype}) has not been set. @{pos}'.format(pName=pName, altype=pALtype, pos=ASTstm.srcPos))
        j += 1;
        
    Instr = translatedStm(instrTemplate[0], funcParam, ASTstm.srcPos, gCD.level)
    return (True, Instr)

def translateFunction_ifStm(ASTstm):
    boolExp = ASTstm.params[0]
    TrueCode = ASTstm.params[1]
    
    transLC = []
    # create condition code
    (r, tcL) = gCD.translateCodeList([boolExp])
    if (r == False):
        return (r, tcL)
    transLC += tcL

    # create condition labels
    ExitLabel = gCD.createLabel()

    # generate condition check instr
    transLC.append(translatedStm('jumpNCF',[ExitLabel], ASTstm.srcPos, gCD.level))
    # True path
    #generate the true code
    (r, tcL) = gCD.translateCodeList(TrueCode)
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    # add jump to the end of the code
    transLC.append(translatedStm('label',[ExitLabel], ASTstm.srcPos, gCD.level))
    return (True, transLC)

def translateFunction_ifelseStm (ASTstm):
    boolExp = ASTstm.params[0]
    TrueCode = ASTstm.params[1]
    FalseCode = ASTstm.params[2]
    
    transLC = []
    # create condition code
    (r, tcL) = gCD.translateCodeList([boolExp])
    if (r == False):
        return (r, tcL)
    transLC += tcL

    # create condition labels
    FalseLabel = gCD.createLabel()
    EndofFalseLabel = gCD.createLabel()

    # generate condition check instr
    transLC.append(translatedStm('jumpNCF',[FalseLabel], ASTstm.srcPos, gCD.level))
    # a) True path
    #generate the true code
    (r, tcL) = gCD.translateCodeList(TrueCode)
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    # add jump to the end of the code
    transLC.append(translatedStm('jump',[EndofFalseLabel], ASTstm.srcPos, gCD.level))
    
    #b) False path
    # and add false code label
    transLC.append(translatedStm('label',[FalseLabel], ASTstm.srcPos, gCD.level))
    (r, tcL) = gCD.translateCodeList(FalseCode)
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    transLC.append(translatedStm('label',[EndofFalseLabel], ASTstm.srcPos, gCD.level))
    return (True, transLC)


def translateFunction_checkButton(ASTstm):
    checkButtonTarget = ASTstm.params[0]
    innerCode = ASTstm.params[1]
    
    (res, transLC) = translateFunction_varOperations(
            ASTstatement(ASTstatementtype.varOperations, ['ui',{'func':[1,'checkButton'], 'obj' : checkButtonTarget}], ASTstm.srcPos)
        )
    
    if (res == False) :
        return (False, transLC)
    
    transLC =[transLC]
    
    jmpLabel = gCD.createLabel()
    transLC.append(translatedStm('jumpNCF',[jmpLabel], ASTstm.srcPos, gCD.level))
    (r, tcL) = gCD.translateCodeList(innerCode)
    if (r == False):
        return (r, tcL)
    for tc in tcL:
        tc.level += 1
        transLC.append(tc)
    transLC.append(translatedStm('label',[jmpLabel], ASTstm.srcPos, gCD.level))
    return (True, transLC)

def translateFunction_update(ASTstm):
    updateTarget = ASTstm.params[0]
    uTName = updateTarget[1]
    
    gv = gCD.gVD.get(uTName , None)
    if (gv == None):
        return (False, 'Update functions needs as parameter a global variable. The given variable %s is not declared as global.'% (uTName,))
    
    return (True, translatedStm('update',[uTName], ASTstm.srcPos, gCD.level))
    

def setup ():
    gCD.setStmTranslateFunction ({
        ASTstatementtype.comment :      translateFunction_comment,
        ASTstatementtype.math_add :     translateFunction_add,
        ASTstatementtype.math_sub :     translateFunction_sub,
        ASTstatementtype.math_mul :     translateFunction_mul,
        ASTstatementtype.math_div :     translateFunction_div,
        ASTstatementtype.assign :       translateFunction_assign,
        ASTstatementtype.brace :        None,
        ASTstatementtype.equal :        translateFunction_equal,
        ASTstatementtype.nEqual :       translateFunction_nEqual,
        ASTstatementtype.less :         translateFunction_less,
        ASTstatementtype.more :         translateFunction_more,
        ASTstatementtype.lessEqual :    translateFunction_lessEqual,
        ASTstatementtype.moreEqual :    translateFunction_moreEqual,
        ASTstatementtype.notStm :       None,
        ASTstatementtype.ifStm :        translateFunction_ifStm,
        ASTstatementtype.ifelseStm :    translateFunction_ifelseStm,
        ASTstatementtype.forStm :       translateFunction_for,
        ASTstatementtype.whileStm :     translateFunction_while,
        ASTstatementtype.funcCall :     translateFunction_call,
        ASTstatementtype.infLoop :      translateFunction_infLoop,
        ASTstatementtype.varOperations: translateFunction_varOperations,
        ASTstatementtype.checkButton :  translateFunction_checkButton,
        ASTstatementtype.update :       translateFunction_update,
        ASTstatementtype.addAssign :    translateFunction_addAssign
        
    })
    
    # infos:
    # <function class> -> <selction key> -> (
    #                                    <ALASM function>,
    #                                    [<params>] @ right order,
    #                                    [param preset] if the parameter is not given at the expression,
    #                                    [param type] -> (<type>,<'c' / 'v'>) c = constant, v = variable
    #                                    )
    gCD.setVariableOperationTranslations ( {
        # biquad
        'biquad' : ('type',{
            'coeff' : ('initBiquad',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('a0','rational','v', float(0.0)),('a1','rational','v', float(0.0)),('a2','rational','v', float(0.0)),('b1','rational','v', float(0.0)),('b2','rational','v', float(0.0)) ]),
            'HP' : ('initBiquadAsHP',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('fs','rational','v', None) ,('fc','rational','v', None)]),
            'LP' : ('initBiquadAsLP',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('fs','rational','v', None) ,('fc','rational','v', None)]),
            'Peak': ('initBiquadAsPeakFilter',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('fs','rational','v', None) ,('fc','rational','v', None),('q','rational','v', None) ,('g','rational','v', None)]),
            'lowShelv': ('initBiquadAsLowFreqShelvFilter',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('fs','rational','v', None) ,('fc','rational','v', None),('q','rational','v', None) ,('g','rational','v', None)]),
            'highShelv': ('initBiquadAsHighFreqShelvFilter',[('obj','biquad','v', None) ,('index','integer','c', int(0)),('fs','rational','v', None) ,('fc','rational','v', None),('q','rational','v', None) ,('g','rational','v', None)]),
            }),
        # dynamics
        'noisegate' : (None,('initNoisegate',[('obj','noisegate','v', None),('TAV','rational','c', None),('AT','rational','c', None),('RT','rational','c', None),('NT','rational','c', None),('NS','rational','c', None)])),        
        'compressor' : (None,('initCompressor',[('obj','compressor','v',None),('TAV','rational','c', None),('AT','rational','c', None),('RT','rational','c', None),('CT','rational','c', None),('CS','rational','c', None)])),
        'expander' : (None,('initExpander',[('obj','expander','v',None),('TAV','rational','c', None),('AT','rational','c', None),('RT','rational','c', None),('ET','rational','c', None),('ES','rational','c', None)])),
        'limiter' : (None,('initLimiter',[('obj','limiter','v',None),('ATpeak','rational','c', None),('RTpeak','rational','c', None),('ATsmooth','rational','c', None),('RTsmooth','rational','c', None),('LT','rational','c', None),('LS','rational','c', None)])),
        # delay
        'delay': (None,('initDelay',[('obj','delay','v', None),('N','integer','v', None),('Nindx','integer','c', int(0)),('offset','integer','c', None)])),
        # smaple i/o
        'sampleIO' : ('operation', {
            'read' : ('readSampleFrame', [('channel','integer','c', None),('dest','rational','v', None),('wait','integer','c', int(1))]),
            'write' : ('writeSampleFrame', [('channel','integer','c', None),('src','rational','v', None)])
            }),
        # ui
        'ui' : ('func',{
            'dim' : ('uiSetDim',[('x','integer','c', None),('y','integer','c', None), ('xle','integer','c', None),('yle','integer','c', None), ('obj',None, 'v', None) , ('index','integer','c', None)]),
            'initPanel': ('uiInitPanel', [('uuid','integer','c', None),('obj','panel','v',None) ,('index','integer','c', int(0))]),            
            'initDisplay': ('uiInitDisplay',[('uuid','integer','c', None), ('obj','display','v',None), ('index','integer','c', int(0)), ('parent','panel','v',None) , ('pIndex','integer','c', int(0))]),
            'initButton': ('uiInitButton',[('uuid','integer','c', None), ('obj','button','v',None), ('index','integer','c', int(0)), ('parent','panel','v',None), ('pIndex','integer','c', int(0))]),
            'initLED': ('uiInitLED',[('uuid','integer','c', None), ('obj','LED','v',None) , ('index','integer','c', int(0)), ('parent','panel','v',None), ('pIndex','integer','c', int(0))]),
            'checkButton' : ('uiCheckButtonPressed', [('obj','button','v',None), ('index','integer','c', int(0))]),
            'print' : ('uiSetDisplay', [('obj','display','v',None) , ('index','integer','c', int(0)), ('text','string','v', None), ('tindex','integer','c', int(0))]),
            'LED' : ('uiSetLED', [('obj','LED','v',None), ('index','integer','c', int(0)), ('on','integer','c', int(1))])
            })
    })
    
    # infos:
    # <operation>-> <function dict>
    # function dict entry:
    #    match touple : ALAsm name, ALASM parameter = [ element]
    #        element = (sourceIndex, destIndex, typeID, typeData)
    #        type = (
    #                v - variable name -> typeData = AL type of the parameter
    #                i - index of variable  -> typeData = None
    #                c - constant-> typeData = AL type of the parameter
    #                e - expression = can be variable or constant
    #            )
    gCD.setArithOpTranslations({
        # c = a+ b -> addInteger a,b,c
        '+' : {
            ('integer','integer','integer') :       ('addInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
            ('rational','rational','rational') :    ('addRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
            },
        '-' : {
            ('integer','integer','integer') :       ('subInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
            ('rational','rational','rational') :    ('subRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
            },
        '*' : {
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
        '/' : {
            ('integer','integer','integer') :       ('divInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
            ('rational','rational','rational') :    ('divRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
            },
        '%' : {
            ('integer','integer','integer') :       ('modInteger',[(0,2,'v','integer'),(1,0,'e','integer'),(2,1,'e','integer')]),
            ('rational','rational','rational') :    ('modRational',[(0,2,'v','rational'),(1,0,'e','rational'),(2,1,'e','rational')])
            },
        '=' : {
            # a = b -> assign a,b
            ('integer','integer') :     ('assignInteger',[(0,0,'v','integer'),(1,1,'e','integer')]),
            ('rational','rational') :   ('assignRational',[(0,0,'v','rational'),(1,1,'e','rational')]),
            # a[ai] = b[bi] -> assign a,ai,b, bi
            ('string','string') :       ('assignString',[(0,0,'v','string'),(0,1,'i',None),(1,2,'e','string'),(1,3,'i',None)]),
            # a[ai] = str(b[bi]) -> integerToString a,ai,b, bi
            ('string','integer') :      ('integerToString',[(0,0,'v','string'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('string','rational') :     ('rationalToString',[(0,0,'v','string'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '+=' : {
             ('string','string') :      ('concatStrings',[(0,0,'v','string'),(0,1,'i',None),(1,2,'e','string'),(1,3,'i',None)]),
             ('integer','integer') :    ('addInteger',[(0,0,'v','integer'),(1,1,'e','integer'),(0,2,'e','integer')]),
             ('rational','rational') :  ('addRational',[(0,0,'v','rational'),(1,1,'e','rational'),(0,2,'e','rational')])
            },
        '==' : {
            ('integer', 'integer') :     ('compareIntegerEqual',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalEqual',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '!=' : {
            ('integer','integer') :     ('compareIntegerNEqual',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalNEqual',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '>' : {
            ('integer','integer') :     ('compareIntegerMore',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalMore',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '<' : {
            ('integer','integer') :     ('compareIntegerLess',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalLess',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '>=' : {
            ('integer','integer') :     ('compareIntegerMoreEqual',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalMoreEqual',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
        '<=' : {
            ('integer','integer') :     ('compareIntegerLessEqual',[(0,0,'e','integer'),(0,1,'i',None),(1,2,'e','integer'),(1,3,'i',None)]),
            ('rational','rational') :   ('compareRationalLessEqual',[(0,0,'e','rational'),(0,1,'i',None),(1,2,'e','rational'),(1,3,'i',None)])
            },
    })

def generateDoc_VariableOperationElementDoc (e, fclass, prefix):
    (HALfunc, ParamL) = e
    exampleParamsT = ''
    HALALasm = ''
    t = APdocgen.texTableStart.format('|p{3cm}|p{3cm}|p{4cm}|p{2cm}|')
    t += APdocgen.texTableHLine
    t += 'name & HAL type & I/O type & default\\\\\n'
    t += APdocgen.texTableHLine
    for (name, type, IOtype, defaultVal) in ParamL: 
        if IOtype == 'v':
            IOtype = 'reference to variable'
            exampleValue = '<ref {name}>'.format(name=name);
        elif IOtype == 'c':
            IOtype = 'constant value'
            if defaultVal is not None:
                exampleValue = str(defaultVal)
            else:
                exampleValue = 'constant'
        else:
            IOtype = 'unknown'
            exampleValue = '?'

        if defaultVal is None:
            defaultVal = '---'

        
        t += '{name} & {htype} & {IOtype} & {default}\\\\\n'.format(name=name, htype=type, IOtype=IOtype, default=defaultVal)
        t += APdocgen.texTableHLine
        # create a example
        if exampleParamsT != '':
            exampleParamsT += ', '
        exampleParamsT += name
        exampleParamsT += '='
        exampleParamsT += exampleValue
        if HALALasm != '':
            HALALasm += ', '
        HALALasm += name
        
    t += APdocgen.texTableEnd
    t += '\\\\\\\\example:\\\\ \\textit{{{fclass}[{prefix}{params}];}}\\\\\n'.format(fclass=fclass, prefix=prefix, params=exampleParamsT)
    t += 'mapped to Audio Language Assembler:\\\\ \\textit{{{HALfunc} {params};}}\\\\\n'.format(HALfunc=HALfunc, params=HALALasm)
    return t

def generateDoc_VariableOperationTranslations ():
    t = APdocgen.texChapter.format('special operations on variables')
    
    t += APdocgen.buildLatexStr('Special operations are used to map HAL functions directly into the Audio Language. For better usebilty they are grouped in to "operation classes". Some parameters are optional and have default values.')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Syntax: <operation class>[<parameter 1>=<value 1>,<parameter 1>=<value 1>, ... ]')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Example: sampleIO[operation=write ,src=out, channel=1];')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Explanation: Form the sample class "sampeIO" the operation "write" is choosen. As source "src" the varaible out is used and the channel is set to 1.')
    
    for (operationClass, classDict) in gCD.varOperationTranslation.items():
        t += APdocgen.texSection.format(operationClass)
        if classDict[0] is None: 
            t += generateDoc_VariableOperationElementDoc(classDict[1], operationClass, '')
        else:
            for (subkey, subKT) in classDict[1].items():
                t += APdocgen.texSubSection.format(subkey)
                t += generateDoc_VariableOperationElementDoc(subKT, operationClass, classDict[0]+'='+subkey+', ')    
    return t

def generateDoc_ArithmeticOp():
    t = APdocgen.texChapter.format('arithmetic and boolean operations on variables')
    t += APdocgen.buildLatexStr('Two variables can be connected via operator. Sometimes a thrid variable can receive the result. To simplify the use the operators the order of the varaibles connected by operators can be variated.')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Syntax for 3 variables: <c> = <a> <operator> <b>;')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Example: c = a + b;')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Syntax for 2 variables: <a> <operator> <b>')
    t += APdocgen.texNewParagraph
    t += APdocgen.buildLatexStr('Example: if (a < b) { ... }')
    
    t += '\\\\Legend:\\\\'
    t += APdocgen.texTableStart.format('|p{3cm}|p{6cm}|')
    t += APdocgen.texTableHLine
    t += 'symbol & explanation\\\\' 
    t += APdocgen.texTableHLine
    t += 'v & variable\\\\' 
    t += APdocgen.texTableHLine
    t += 'i & index of the variable \\\\' 
    t += APdocgen.texTableHLine
    t += 'c & constant value \\\\' 
    t += APdocgen.texTableHLine
    t += 'c/v & constant value or variable \\\\' 
    t += APdocgen.texTableHLine
    t += APdocgen.texTableEnd


    for (opcode, OPDict) in gCD.ArithOpTranslation.items():
        t += APdocgen.texSection.format(APdocgen.buildLatexStr(opcode))
        amountOfVars = len(OPDict.items()[0][0])
        
        if amountOfVars == 2:
            tabledef = 'p{2cm}|p{2cm}'
            tabledefH = 'a & b'
            assoIndxVarName = {
                0 : 'a',
                1 : 'b'
                }
        elif amountOfVars == 3:
            tabledef = 'p{2cm}|p{2cm}|p{2cm}'
            tabledefH = 'c & a & b'
            assoIndxVarName = {
                0 : 'c',
                1 : 'a',
                2 : 'b'
                }
        else:
            tabledef = 'p{6cm}'
            tabledefH = 'unknown'
            assoIndxVarName = {}
            
        t += APdocgen.texTableStart.format('||'+tabledef+'||p{6cm}||')
        t += APdocgen.texTableHLine
        t += tabledefH + ' & HAL function\\\\' 
        t += APdocgen.texTableHLine
        
        for (inputTypesL, (HALfunc, outputL)) in OPDict.items():
            outpL = [None]*len(outputL)
            inpLtext = ''
            for i in inputTypesL:
                if inpLtext != '':
                    inpLtext += ' &'
                inpLtext += APdocgen.buildLatexStr(i)
            i = 0
            for o in outputL:
                if o[2] == 'v':
                    outpL[i] = '(v) '
                elif o[2] == 'i':
                    outpL[i] = '(i) '
                elif o[2] == 'c':
                    outpL[i] = '(c) '
                elif o[2] == 'e':
                    outpL[i] = '(v/c) '
                outpL[i] += assoIndxVarName.get(o[0], '')
                i += 1
            outpLtext = ''
            for o in outpL:
                if outpLtext != '':
                    outpLtext += ', '
                outpLtext += o
                    
            
            t += inpLtext + ' & '+HALfunc+ ' '+ outpLtext +';\\\\' 
            
            t += APdocgen.texTableHLine
        t += APdocgen.texTableEnd

    return t
    
def generateDocumentation():
    # get template
    fd = open(os.path.join(os.curdir,'templ','ALcTempl.tex'), 'r')
    tmpl = fd.read()
    fd.close()
    
    filename = os.path.join(os.curdir,'ALcompilierDoc.pdf')
    lstr = APdocgen.texTmplStart.format(title='Audio Language Compiler Documentation')
    lstr += tmpl
    lstr += generateDoc_ArithmeticOp()
    lstr += generateDoc_VariableOperationTranslations()
    lstr += APdocgen.texTmplEnd
    return APdocgen.genPDFfileFromLatexStr(lstr, filename)

#creates a call tree from the AST
def createCallTree(AST):
    cT = []
    for eAST in AST:
        chf = True
        if eAST[0] == ASTtype.function:
            name = eAST[1][0]
            instrL = eAST[1][3]
        elif eAST[0] == ASTtype.main:
            name = eAST[3]
            instrL = eAST[1][1]
        else:
            name = None
            instrL = []
            chf = False
        if chf == True:
            fcL = []
            for instr in instrL:
                if instr.stmType == ASTstatementtype.funcCall:
                    callfName = instr.params[1]
                    if callfName not in fcL:
                        fcL.append(callfName)
            cT.append([name, fcL])
    print cT
    return cT
            
            
    

# creates a compiling stragegy by the use of the call tree
def createCompileStrategy(cT):
    compilingList = []
    while cT:
        print cT
        for callInfo in cT:
            fname, fDependencies = callInfo
            # try resolve the calls in the function
            # if they are already compiled before, we can remove them from the list
            for fc in fDependencies:
                if fc in compilingList:
                    fDependencies.remove(fc)
    
            # check if the list is emty
            if not fDependencies:
                compilingList.append(fname)
                cT.remove(callInfo)
        
    print compilingList

def main(argv):
    parser = argparse.ArgumentParser(description='the audio language compiler')
    parser.add_argument('-i', help='the audio language code input file')
    parser.add_argument('-o', help='the audio language assembler output dir', default=os.curdir)
    parser.add_argument('-asm', help='if set the ALASM files are translated', default=False, action='store_const', const=True)
    parser.add_argument('-c', help='if asm and this flag is set c-files are generated', default=False, action='store_const', const=True)
    parser.add_argument('-cb', help='if -c is set -cb means that an embeeded binary file is generated(otherwise a c file with HAL function calls is generated)', default=False, action='store_const', const=True)
    parser.add_argument('-ca', help='if -c is set and -cb is not set or false -ca<number> gives the number of instructions after the messagesystem is called', default='5')
    parser.add_argument('-p', help='python program path', default='')
    parser.add_argument('-doc', help='creates the documentation', default=False, action='store_const', const=True)
    
    args = parser.parse_args()
    return (args.i, args.o, args.asm, args.c, args.cb, args.ca, args.p, args.doc)

if __name__ == '__main__':
    setup ()

    (iFile, oDir, asmFlag, cFlag, cBinFlag, cAmountFlag, pathPyPrg, docgenFlag) = main(sys.argv[1:])
    if docgenFlag == True:
        print 'generate documentation'
        generateDocumentation()
        print 'finished'
    
    print ('compile "'+iFile+'" to "'+oDir+'" dir ...')
    
    myP = ALGrammar()
    (res, val) = myP.translateFile(iFile)
    if (res != True) :
        print (val)
        sys.exit(-1)
    
    ASTcallTree = createCallTree(val)
    compileStrategy = createCompileStrategy(ASTcallTree)

    (res, val) = gCD.translateASTtoALASM(val, oDir)
    if res == False:
        print(str(val))
        sys.exit(-2)

    # check if we should translate some files from alasm to alc and c
    if asmFlag == True:
        for f in val:
            asmFile = os.path.join(f + '.alasm')
            pycmd = os.path.join(pathPyPrg,'ALasm.py')
             
            if cFlag == True:
                if cBinFlag == True:
                    cGenStuf = '-ce'
                else:
                    cGenStuf = '-cf -cfai={num}'.format(num=cAmountFlag)
            else:
                cGenStuf = ''
            cmdStr = 'python {cmd} -i="{asmFile}" -o="{oDir}" {cGenStuf} -p="{pathPyPrg}"'.format(cmd=pycmd, asmFile=asmFile, oDir=oDir, cGenStuf=cGenStuf, pathPyPrg=pathPyPrg)
            print 'execute ' + cmdStr
            pipe = subprocess.Popen(cmdStr, shell=True)
            pipe.wait()

    sys.exit(0)
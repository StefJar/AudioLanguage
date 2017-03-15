'''
Created on 21.10.2011

@author: StJ
'''

import os
import datetime
import ply.lex as lex
import ply.yacc as yacc
import re

def indentCCode (text, startlevel = 0):
    res = ''
    braceCounter = startlevel
    for c in text:
        if c == '{' :
            braceCounter += 1
        if c == '}' :
            braceCounter -= 1
        if c == '\n' :
            res += '\n'
            for i in range(braceCounter):
                res += '\t'
        else :
            res += c
    return res


class MsgProcessParser(object):
    """
    Base class for a lexer/parser that has the rules defined as methods
    """
    tokens = ()
    precedence = ()
    start = ''

    def __init__(self, debug):
        self.debug = debug
        self.names = { }
        try:
            modname = os.path.split(os.path.splitext(__file__)[0])[1] + "_" + self.__class__.__name__
        except:
            modname = "parser"+"_"+self.__class__.__name__
        self.debugfile = modname + ".dbg"
        self.tabmodule = modname + "_" + "parsetab"
        #print self.debugfile, self.tabmodule

        # Build the lexer and parser
        lex.lex(
            module=self,
            debug=self.debug
        )
        
        yacc.yacc(
                  module=self,
                  debug=self.debug,
                  debugfile=self.debugfile,
                  tabmodule=self.tabmodule,
                  start=self.start
                  )

    def run(self, text):
        #return yacc.parse(text,tracking=True,debug=1)
        return yacc.parse(text,debug=self.debug,tracking=0)

    
class MsgProcessGrammar(MsgProcessParser):
    varTypes = {
        'Node'      :   'TAPNodeID',
        'Driver'    :   'const TAPMsgDrv *',
        'mNum'      :   'uint32_t',
        'mID'       :   'uint32_t',
        'VarIndex'  :   'uint32_t',
        'Variable'  :   'TAPInterpreterVariable *',
        'int'       :   'int32_t'
        }
    
    ackEnum = 'eAPMsgTypes_ACK'
    
    reserved = {
        'loopAll'          : 'loopAll',
        'nodes'             : 'nodes',
        'drivers'           : 'drivers',
        'declare'           : 'declare',
        'return'            : 'return',
        'if'                : 'if',
        'else'              : 'else',

        'send'              : 'send',
        'receive'           : 'receive',
        'call'              : 'call',


        'addNode'           : 'addNode',
        'removeNode'        : 'removeNode',
      
        'getSelfSenderID'   : 'getSelfSenderID',
        'getSender'         : 'getSender',
        'getDriver'         : 'getDriver',
        'getDriverFromNode' : 'getDriverFromNode',
        'getNodeIDfromNode' : 'getNodeIDfromNode',
        'getMsgNum'         : 'getMsgNum',
        'getMsgID'          : 'getMsgID',
        'getNewMsgNum'      : 'getNewMsgNum',
        'runAP'             : 'runAP',
        'waitACK'           : 'waitACK',
        'getVariableByIndex': 'getVariableByIndex',
        'getVariableData'   : 'getVariableData',
        'getMsgDataRef'     : 'getMsgDataRef',
        'getMsgDataToInt'   : 'getMsgDataToInt',
        
        'ALL'               : 'ALL'
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
        'number',
        'arrowLeft',
        'arrowRight',
        'not',
        'add',
        'sub',
        'mul',
        'div',
        'nEqual',
        'equal',
        'assign'
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
    t_add = '\+'
    t_sub = '-'
    t_div = '/'
    t_mul = '\*'
    
    def t_name(self, t):
        r'[a-zA-Z_][a-zA-Z0-9_]*'
        t.type = self.reserved.get(t.value,'name')    # Check for reserved words
        return t

    def t_fNumber(self, t):
        r'[-+]?\d+\.\d+([eE][-+]?\d+)?'
        try:
            t.value = float(t.value)
        except ValueError:
            print("float value too large %d", t.value)
            t.value = 0.0
        t.type = 'number'
        return t

    def t_iNumber(self, t):
        r'[-+]?\d+'
        try:
            t.value = int(t.value)
        except ValueError:
            print("Integer value too large %d", t.value)
            t.value = 0
        t.type = 'number'
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
    start = 'process'

    def p_process(self, p):
        'process : name lBracket name assign name rBracket lSoftBrace extparams rSoftBrace lBrace code rBrace'
        if p[8] != '' :
            p[8] = ', ' + p[8]
            
        extraVars = ''
        for v in self.Vars:
            extraVars += '\t' + v[0] + '\t' + v[1] + ';\n'

        #handler
        if p[3] != 'handle' :
            raise SyntaxError
        if p[5] == 'none':
            self.msgHandler = (False, None)
        else:
            self.msgHandler = (True, p[5])
            p[8] = ', TAPMsg * pMsg ' + p[8]

        self.declaration = 'int ' + p[1] + '( TAP * pAP ' + p[8] + ')' 
            
        p[0] = self.declaration +  '{\n' + extraVars + p[11] + '\n}\n'
        
        self.declaration = self.declaration + ';\n'
        self.functionName = p[1]
        

    def p_code (self, p):
        """
        code :
            | stm
            | code stm
        """
        if (len(p) == 1) :
            p[0] = ''
        
        if (len(p) == 2) :
            p[0] = p[1] + '\n'
            
        if (len(p) == 3) :
            p[0] = p[1] + p[2] + '\n'
   
    def p_paramList (self, p):
        """params :
                | exp
                | params comma exp
        """
        if (len(p) == 1):
            p[0] = ''
        elif (len(p) == 2):
            p[0] = p[1]
        else:
            p[0] = p[1] + ',' + p[3]

    def p_extParamList (self, p):
        """extparams :
            | name name
            | extparams comma name name
        """
        if (len(p) == 1) :
            p[0] = ''

        if (len(p) == 3) :
            p[0] = self.varTypes.get(p[1],'error') + ' '+ str(p[2])
        
        if  (len(p) == 4) :
            p[0] = p[1] + self.varTypes.get(p[2],'error') + ' '+ str(p[4])
        
    def p_loopDriver (self,p):
        'loopDriver : loopAll drivers lBracket name rBracket'
        self.Vars.append(('const TAPMsgDrv *',p[4]))
        self.loopVar.append(p[4])
        self.nestingDeep += 1
    
    def p_loopNode (self,p):
        'loopNode : loopAll nodes lBracket name rBracket'
        self.Vars.append(('TAPNode *',p[4]))
        self.loopVar.append(p[4])
        self.nestingDeep += 1
                
    def p_codeSeq(self,p):
        'codeSeq : lBrace code rBrace'
        p[0] = p[2]
    
    def p_expNumber(self,p):
        'exp : number'
        p[0] = p[1]
    
    def p_expName (self,p):
        'exp : name'
        p[0] = p[1]
        
    def p_expALL (self,p):
        'exp : ALL'
        p[0] = 'dAPNodeID_ALL'

        
    def p_expArithMOP (self,p):
        """exp : exp add exp
            | exp sub exp
            | exp mul exp
            | exp div exp
        """
        if ((type(p[1]) is float) and (type(p[3]) is float)) :
            if p[2] == '+' :
                p[0] = p[1] + p[3]
                
            if p[2] == '-' :
                p[0] = p[1] - p[3]
                
            if p[2] == '*' :
                p[0] = p[1] * p[3]
            
            if p[2] == '/' :
                p[0] = p[1] / p[3]
        else :
            p[0] = str(p[1]) + str(p[2]) + str(p[3])

    def p_expBraces (self,p):
        'exp : lSoftBrace exp rSoftBrace'
        if (type(p[2]) is float):
            p[0] = p[2]
        else :
            p[0] = '(' + str(p[2]) + ')'

    def p_expNot (self,p):
        'exp : not exp'
        p[0] = '!(' + str(p[2]) + ')'

    def p_expNequal(self,p):
        'exp : exp nEqual exp'
        p[0] = str(p[1]) + '!=' + str(p[3])

    def p_expEqual(self,p):
        'exp : exp equal exp'
        p[0] = str(p[1]) + '==' + str(p[3])


    def p_expSend(self,p):
        'exp : name arrowLeft send lSoftBrace name lSoftBrace params rSoftBrace rSoftBrace'
        p[0] = p[1] + '->pfkt_' +p[5] + ' ( '+ p[1] +'->pDrvData ,' + p[7] + ' )'

    def p_expReceive(self,p):
        'exp : name arrowRight receive lSoftBrace name lSoftBrace params rSoftBrace rSoftBrace'
        p[0] = p[1] + '->pfkt_' +p[5] + ' ( '+ p[1] +'->pDrvData ,' + p[7] + ' )'

    def p_expWaitACK(self,p):
        'exp : waitACK lSoftBrace name rSoftBrace'
        p[0] = 'APwaitAck (pAP, '+p[3]+')'

    def p_expGetDriver(self,p):
        'exp : getDriver lSoftBrace rSoftBrace'
        p[0] = 'pMsg->extraData.pDrv'

    def p_expGetDriverFromNode(self,p):
        'exp : getDriverFromNode lSoftBrace exp rSoftBrace'
        p[0] = str(p[3])+'->pDrv'

    def p_expGetNodeIDfromNode(self,p):
        'exp : getNodeIDfromNode lSoftBrace exp rSoftBrace'
        p[0] = str(p[3])+'->nodeID'

    def p_expGetDriverFromSenderID(self,p):
        'exp : getDriver lSoftBrace name rSoftBrace'
        p[0] = 'APfindDrvBySenderID(pAP,'+str(p[3])+')'


    def p_expGetSenderID(self,p):
        'exp : getSender lSoftBrace rSoftBrace'
        p[0] = '(*(pMsg->pH))[eAPMsgHeaderPosition_sender]'


    def p_expGetSelfSenderID(self,p):
        'exp : getSelfSenderID lSoftBrace rSoftBrace'
        p[0] = 'pAP->nodeID'

    def p_expGetNewMsgNum(self,p):
        'exp : getNewMsgNum lSoftBrace rSoftBrace'
        p[0] = 'APgetNewMessageNumber(pAP)'


    def p_expAddNode(self,p):
        'exp : addNode lSoftBrace name comma name rSoftBrace'
        p[0] = 'APaddNode(pAP, ' + p[3] +', ' + p[5] + ' )'
        
    def p_removeNode (self, p):
        'exp : removeNode lSoftBrace name rSoftBrace'
        p[0] = 'APremoveNode(pAP, ' + p[3] +' )'

    def p_getMsgNum(self,p):
        'exp : getMsgNum lSoftBrace rSoftBrace'
        p[0] = '(*(pMsg->pH))[eAPMsgHeaderPosition_msgNumber]'

    def p_getMsgID(self,p):
        'exp : getMsgID lSoftBrace rSoftBrace'
        p[0] = '(*(pMsg->pH))[eAPMsgHeaderPosition_msgTypeID]'

    def p_expRunAP(self,p):
        'exp : runAP lSoftBrace rSoftBrace'
        p[0] = 'APrun(pAP)'

    def p_stmloopDrvStm (self,p):
        'stm : loopDriver codeSeq'
        loopVar = self.loopVar.pop()
        dummyVar = self.createLoopVarName()
        self.Vars.append(('int',dummyVar))
        p[0] = loopVar + ' = pAP->pDrvList;\nfor('+dummyVar+'=0; '+dummyVar+' < pAP->driverNumber; '+dummyVar+'++) {\n'
        p[0] += p[2]
        p[0] += loopVar + '++;\n}\n'
        self.nestingDeep -= 1

    def p_stmloopNodeStm (self,p):
        'stm : loopNode codeSeq'
        loopVar = self.loopVar.pop()
        p[0] = loopVar + ' = pAP->pNodeList;\nwhile ('+loopVar+') {\n'
        p[0] += p[2]
        p[0] += loopVar + ' = ' + loopVar +'->pNext;\n}\n'
        self.nestingDeep -= 1
        
    def p_stmDeclareVar (self,p):
        'stm : declare name name semicolon'
        type = self.varTypes.get(p[3],'error')
        self.Vars.append((type,p[2]))
        p[0] = ''

    def p_stmIf (self,p):
        'stm : if exp codeSeq'
        p[0] = 'if (' + str(p[2]) + ' ) {\n' + p[3] + '}\n'
    
    def p_stmIfElse (self,p):
        'stm : if exp codeSeq else codeSeq'
        p[0] = 'if (' + str(p[2]) + ' ) {\n' + p[3] + '\n} else {\n' + p[5] + '}\n'
        
    def p_stmReturn (self,p):
        'stm : return exp semicolon'
        if type(p[2]) is float:
            if (0.0 == p[2]) :
                p[2] = int(0)
            else:
                p[2] = '((int) ' + str(p[2]) + ')'
        p[0] = 'return ' + str(p[2]) + ';'

    def p_stmAssign(self,p):
        'stm : name assign exp semicolon'
        p[0] = p[1] + '=' + str(p[3]) + ';'

    
    def p_expStm (self,p):
        'stm : exp semicolon'
        p[0] = str(p[1]) + ';'
    
    def p_expGetVariableByIndex(self, p):
        'exp : getVariableByIndex lSoftBrace name rSoftBrace'
        p[0] = 'APInterpreterGetVariableByIndex(pAP->IP,'+p[3]+')'
        
    def p_stmCallVar (self, p):
        'exp : name arrowLeft call lSoftBrace name lSoftBrace params rSoftBrace rSoftBrace'
        p[0] = p[1] +'->pVI->pFkt_'+p[5] + '('+p[7]+')'
        
    def p_expVarData (self, p):
        'exp : getVariableData lSoftBrace name rSoftBrace'
        p[0] = p[3] + '->pData'
        
    def p_expGetMsgDataToInt (self, p):
        'exp : getMsgDataToInt lSoftBrace exp rSoftBrace'
        p[0] = '((uint32_t *)pMsg->pData)['+str(p[3])+']'

    def p_expGetMsgDataRef (self, p):
        'exp : getMsgDataRef lSoftBrace rSoftBrace'
        p[0] = 'pMsg->pData'


    def p_error(self, p):
        if p:
            print("Syntax error at '%s'" % p.value)
            print("Line %i" % p.lineno)
            print (p)
        else:
            print("Syntax error at EOF")

    def saveStmContext(self, context):
        self.context.append(context)

    def removeStmContext(self):
        self.context.pop()

    def createLoopVarName(self):
        return '_generated_lv' + str(self.nestingDeep)

    def translate(self, text):
        self.nestingDeep = 0
        self.Vars = []
        self.loopVar = []
        self.flag_isMsgHandler = False
        self.msgHandler = (False, None)
        self.declaration =''
        self.functionName = ''
        res = self.run(text)
        if (res != None) :
            return indentCCode (res,0)
        else:
            return None

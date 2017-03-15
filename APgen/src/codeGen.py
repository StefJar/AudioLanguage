'''
Created on 02.02.2011

@author: StJ
'''

import APDB
import os
import datetime
import re

import codeGenXML
import DBwindows
import APlogger

import APmsgProcessCompilier

def readTextFromFile (filename):
    f = open(filename, "r+b")
    txt = f.read()
    f.close()
    return txt
 

class codeGenerator(object):
    def __init__(self,db,targetDir):
        self.db = db
        self.workingPath = os.getcwd()
        self.workingPath = os.path.join(self.workingPath,targetDir)
        # const
        self.strVersion = '0.1 alpha'
        self.HALskeletonHeaderFilename = 'AP'
        self.HALskeletonCFileFilename = 'AP'
        self.APmainCFileFilename = 'mainAP'
        self.hExt = '.h'
        self.cExt = '.cpp'
        self.remoteInterfaceAPinterfaceTemplate = os.path.join(os.getcwd(),'templ' ,'remoteInterfaceAPTempl.c')
        
        self.staticData = codeGenXML.CodeGenXMLparseFile('APgenTemplates.xml')
        
        
        self.dtypePreFix = 'ApVar'
        self.dtypeElementStr = '_ele_'
        self.dtypeVectorStr = '_vec_'
        self.dtypeArrayPrefix = 'pA_'
        self.dtypeArrayNumPrefix = 'num_'
        self.dtypeVectNumName = 'num'
        self.dtypeVectFirstElementName = 'pFE'
        

    
    def getAPSourceFile (self):
        return self.getCompleteFileName(self.HALskeletonCFileFilename + self.cExt)

    def getAPmainSourceFile (self):
        return self.getCompleteFileName(self.APmainCFileFilename + self.cExt)

    def removeDoubleIncludeEntries (self, inclL):
        myListD = {}
        for includefile, lib, syslib in inclL:
            myListD[includefile] = (includefile, lib, syslib)
        res = []
        for k,e in myListD.items():
            res.append(e)    
        return res
        
    def genCCodeFromDBIncludeList (self,iL):
        res = ''
        for includefile, lib, syslib in iL:
            if (syslib == True):
                sep1 = '<'
                sep2 = '>'
            else:
                sep1 = '"'
                sep2 = '"'
            if res != '':
                res += '\n'
            res += '#include {sep1}{includefile}{sep2}'.format(sep1=sep1,sep2=sep2,includefile=includefile)
        return res

    def genCCodeHeaderComment (self):
        t = datetime.datetime.now()
        res = '//==================================================\n//\tAP generator v.'
        res += self.strVersion
        res += '\n//\ttimestamp: '
        res += str(t)
        res += '\n//==================================================\n'
        return res
    
    def getEndianMatter(self,itMatter):
        if itMatter == True:
            return 1
        else :
            return 0
    
    def getIndexBasicIOTypeIndex (self,biotID,bitl):
        counter = 0
        for btio in bitl:
            if btio[1] == biotID:
                return (counter, btio[2])
            counter += 1
        return (-1,'error')

    def getFunctionDefParamName (self,f):
        return 'gFuncDefParam_' + str(f[1]) + '_'+ f[2] 

    def getFunctionNameFromFIDandName (self,fid, fname):
        return 'HALfunc_ID{fid}_{fname}'.format(fid=fid,fname=fname)

    def getFunctionName (self,f):
        return self.getFunctionNameFromFIDandName(f[1], f[2])

    def getMsgTypeNames (self,mt):
        return 'gMsgDataDefinition_' + str(mt[1])+ '_' + mt[2]
    
    def getMsgTypeListName (self):
        return 'gHALMsgTypeList'

    def getMsgTypeArrayName (self):
        return 'gHALMsgTypeArray'
    
    def getAPMsgSystem_msgProcessStdValues(self):
        return 'TAP * pAP'
    
    def getBasicIOTypeVariableName (self, t):
        return 'ip_' + t
    
    def getDrvMsgFunctionsStdParams (self):
        return 'void *pDrvData, uint32_t receiver, uint32_t mNum'
    
    def getVarFunctName (self, varID):
        if varID != None:
            preFix = 'HALimpl_'+str(varID)
        else :
            preFix = 'pFkt'
        # dict tuple = (
        #    0 - descr
        #    1 - func name
        #    2 - return type
        #    3 - params
        #    4 - std. c - code
        #    )
        
        res = {
            'create'        :   ('create a new variable', preFix+'_create','void *','unsigned int numberOfElements','return NULL;'),
            'delete'        :   ('delete the variable',preFix+'_delete','void','void * pVarData',''),
            'decodeData' :      ('decode data for the HAL functions',preFix+'_decodeData','void *','void * pVarData','return NULL;'),
            'sendUpdate'    :   ('updates the vars at the other APs',preFix+'_sendUpdate','int','void * pVarData, const void * pDrv, uint32_t receiver, uint32_t mNum, int32_t i','return -1;'),
            'recvUpdate'    :   ('updates a variable the AP',preFix+'_recvUpdate','int','void * pVarData, void * pMsgData','return -1;'),
            }
        return res
    
    def getInterpreterFunctionsParams(self):
        res = {}
        bdtl = self.db.HAL_basicIOTypes_getList()
        for bdt in bdtl:
            res[bdt[1]] = (bdt[4], 'fp_' + bdt[2], bdt[3])
        # the buildin types are negative
        res [-self.db.dFuncClass_refVar] = ('TAPInterpreterVariable *','fp_pV','reference to the variable')
        res [-self.db.dFuncClass_refDataVar] = ('void *','fp_pD','reference to the data of the variable')
        res [-self.db.dFuncClass_VarID] = ('int','fp_VarID','type id of the variable')
        res [-self.db.dFuncClass_VarIndex] = ('int', 'fp_VarIndex','index of the variable')
        return res

    def getHALFunctionParameterDef (self):
        return ('void * pIPcpu, TuAPInterpreterFunctionParameter * pParams', 'pIPcpu', 'pParams') 
    
    def genHALVarHeaderFunctions (self):
        fd = self.getVarFunctName(None)
        fblock = ''
        for k,f in fd.items():
            fblock += '\t// ' +f[0]+ '\n\t'+ f[2] + ' (* ' + f[1] +') (' + f[3] + ');\n'
        return fblock
    
    def getMsgDrvFunctionsAndCommentsHeader (self):
        msgDrvFunct = self.db.HAL_gen_MsgTypeList()
        # <comment>,<c code>=<res><name><params>,<P/F> P parameter F Function
        resP = [('driver specific data','void * pDrvData')]
        resF = [
                ('open an existing driver and bind it to the AP','int', 'open', 'void * pAP, struct SAPMsgDrv *pDrv'),
                ('close the driver','int', 'close', 'struct SAPMsgDrv *pDrv'),
                ('destroys the driver','int', 'destroy', 'struct SAPMsgDrv *pDrv'),
                ('sends raw data in uint32_t chunks','int', 'sendRaw', 'struct SAPMsgDrv *pDrv, int amount, uint32_t * pData'),
                ('sends integer data in int32_t chunks in the sequence (LB0,HB0,LB1,HB1,LB2,HB2,LB3,HB3)','int', 'sendInteger32', 'struct SAPMsgDrv *pDrv, int amount, int32_t * pData'),
                ('sends float data in float chunks','int', 'sendFloat32', 'struct SAPMsgDrv *pDrv, int amount, float * pData')
                ]
        for drvF in msgDrvFunct:
            comment = drvF[0][3]
            cFunc_res = 'int'
            cFunc_name = drvF[0][2]
            cFunc_param = self.getDrvMsgFunctionsStdParams()
            for functParam in drvF[1]:
                cFunc_param += ', '
                cFunc_param += self.db.HAL_basicIOType_getCTypeNameByTypeID(functParam[5])
                if True == functParam[6]:
                    cFunc_param += ' *'
                cFunc_param += ' '
                cFunc_param += functParam[3]
            resF.append((comment,cFunc_res,cFunc_name,cFunc_param))
        return (resP,resF)
    
    def getMsgDrvVarParameterToFunctionAsso (self):
        res = {
            'uint32_t'  : 'sendRaw',
            'int32_t'   : 'sendInteger32',
            'float'     : 'sendFloat32'
        }
        return res
        
    def genMsgDrvStruct (self):
        drvPL,drvFL = self.getMsgDrvFunctionsAndCommentsHeader()
        th = 'typedef struct SAPMsgDrv {\n'
        th += '\t//1.) data\n'
        for p in drvPL:
            # print comment
            th += '\t// ' + p[0] + '\n'
            # print function/data define
            th += '\t' + p[1] + ';\n'
        th += '\t//2.) functions\n'
        
        for f in drvFL:
            # print comment
            th += '\t// ' + f[0] + '\n'
            # print function/data define
            th += '\t' + f[1] + ' (* pfkt_' + f[2] +') ('+f[3]+');\n'
        th += '} TAPMsgDrv;\n\n'
        return th

    def genFunctionParamClasses (self):
        hText = '// define parameter class types\n'
        hText += 'enum eHALfunctionParamClasses {\n'
        hText += '\teHALfunctionParamClass_basicIOtype = ' + str(self.db.dFuncClass_basicIOtype) + ',\n'
        hText += '\teHALfunctionParamClass_refVar = ' + str(self.db.dFuncClass_refVar) + ',\n'
        hText += '\teHALfunctionParamClass_refDataVar = ' + str(self.db.dFuncClass_refDataVar) + ',\n'
        hText += '\teHALfunctionParamClass_VarID = ' + str(self.db.dFuncClass_VarID) + ',\n'
        hText += '\teHALfunctionParamClass_VarIndex = ' + str(self.db.dFuncClass_VarIndex) + '\n'
        hText += '};\n'
        return hText
        
    def genIPmaxParams(self):
        hText = '// define the maximum of parameter count of a function\n'
        maxParams = self.db.HAL_DefFunctions_maxParamCount()
        hText += '#define dAPInterpreterFuncMaxParams (' + str(maxParams) + ')\n'
        return hText
    
    def genFuncParamType (self):
        cParam = '// define function parameter union\n'
        cParam += 'typedef union uAPInterpreterFunctionParameter {\n'
        fpl = self.getInterpreterFunctionsParams()
        for k,fp in fpl.items():
            cParam += '\t' + fp[0] +'\t' + fp[1] + ';\t// ' + fp[2] + '\n' 
        cParam += '} TuAPInterpreterFunctionParameter;'
        return cParam

    def genBreakComment (self, breakName):
        dstr = '// ===============================\n'
        dstr += '// ' + breakName + '\n'
        dstr += '// ===============================\n\n'
        return dstr

    def genMsgTypeEnum (self):
        dict = {} 
        msgTL = self.db.HAL_Msg_Type_getList()
        for msgT in msgTL:
            dict[msgT[2]] = ('eAPMsgTypes_'+str(msgT[2]),msgT[1])
        return dict

    def getCompleteFileName (self,fileName):
        return os.path.join(self.workingPath,fileName)

    def setup (self):
        # del old dir
        print ('try to delete old files an directories')
        for root, dirs, files in os.walk(self.workingPath):
            for name in files:
                os.remove(os.path.join(root, name))
            for name in dirs:
                os.rmdir(os.path.join(root, name))
        try:
            os.rmdir(self.workingPath)
        except os.error as e:
            print ('error :')
            print (e)
        
        # make new dir
        print ('create new directory')
        os.mkdir(self.workingPath)        



    def searchList (self, list1, list1IDindex, value):
        for e in list1:
            if e[list1IDindex] == value: return e 
        return None

    def _depr_buildCodeListFromAPtableWithID (self, HALlist, APImplList, tableNameImpl, halIdIndex, APImplUuidIndex, ImplCodeIDindex, ImplIDindex, nameIndex):
        newList = []
        # 1. iterate through the implementation list
        for iDef in APImplList:
            impl = self.db.generic_get(tableNameImpl, iDef[APImplUuidIndex])
            halDef = self.searchList(HALlist, 1, impl[ImplIDindex]) 
            if impl != None:
                code = self.db.Code_getCode(impl[ImplCodeIDindex])[0]
                incl = self.db.Code_getIncludes(impl[ImplCodeIDindex])
                newList.append((impl[ImplIDindex], halDef[nameIndex], incl, code))
        # 2. now check the implemenation list against the HAL list and add emty functionns
        for halDef in HALlist:
            impl = self.searchList(newList, 0, halDef[halIdIndex])
            if impl == None:
                newList.append((halDef[halIdIndex], halDef[nameIndex], None, None))
        # 3. resort list by the id
        newList.sort(key=lambda impl: impl[0])
        return newList
    
    def _depr_buildCodeListFromAPtable (self, APtableList, ImplTableName, APtableUUIDindex , ImplTableCodeIDindex):
        newList = []
        for apE in APtableList:
            impl = self.db.generic_get(ImplTableName,apE[APtableUUIDindex])
            if impl != None:
                code = self.db.Code_getCode(impl[ImplTableCodeIDindex])
                incl = self.db.Code_getIncludes(impl[ImplTableCodeIDindex])
                newList.append((incl,code,impl[0]))
        return newList
    
    def _depr_getAPLists (self, uuidAP):
        # 1. get variable datatype list
        impl_Vars = self.buildCodeListFromAPtableWithID(
                    self.db.HAL_VariableDefinition_getList(),
                    self.db.AP_implTable_getList('VariableList',uuidAP),
                    'ImplHALVariable',
                    1,
                    2,
                    2,
                    1,
                    2
            )

        # 2. get function datatype list
        impl_Func = self.buildCodeListFromAPtableWithID(
                    self.db.HAL_DefFunctions_getList(),
                    self.db.AP_implTable_getList('FunctionList',uuidAP),
                    'ImplHALFunction',
                    1,
                    2,
                    2,
                    1,
                    2
            )
        # 3. AP
        impl_AP = self.buildCodeListFromAPtable(
                    self.db.AP_implTable_getList('APList',uuidAP),
                    'ImplAP',
                    2,
                    1
            )
        # 4. driver
        impl_MsgDrv = self.buildCodeListFromAPtable(
                    self.db.AP_implTable_getList('DriverList',uuidAP),
                    'ImplMsgDriver',
                    2,
                    1
            )
        
        return (impl_Vars, impl_Func, impl_AP, impl_MsgDrv)

    

    def _genVarDefinition (self, varID):
        vi = self.db.HAL_VariableDefinition_getByVariableID(varID)
        if None == vi[0]:
            return (False,'error at variable id ({varid}) a HAL definition with the id dosn\'t exists'.format(varID))
        varUUID, varID, vname, vdesc = vi[0]

        # gen variable descr. struct
        fn = self.getVarFunctName(varID)
        
        varFunc = ''
        for e, d in fn.items():
            if varFunc != '':
                varFunc += ',\n'
            varFunc += '.pFkt_{subvalue} = {value}'.format(subvalue=e,value=d[1])
        
        return """// HAL variable info for {vname} ({varID})
{{
    .id = {varID},
    {varFunc}
}}""".format(
           vname = vname,
           varID = varID,
           varFunc=self._genCCodeOrientation(varFunc,1)
        )
        

    def _genBasicTypeList (self):
        basicTypeList = self.db.HAL_basicIOTypes_getList()
        cText = self.genBreakComment('basic type list')
        cText += '// declare the basic io type array\n'
        cText += 'THAL_basicIO const gHALbasicIOtype []= {\n'
        counter = 0
        for bt in basicTypeList:
            counter += 1
            cText += '\t{'+ str(bt[1]) +',' + str(bt[6])+',' + str(self.getEndianMatter(bt[5])) + '}'
            if counter < len(basicTypeList):
                cText += ','
            else:
                cText += '\t'
                
            cText += '\t//'+bt[2]+'\n'
        cText += '};\n\n'
        cText += 'THAL_basicIOList const gHALbasicIOtypeList = {\n'
        cText += '\tgHALbasicIOtype,\n'
        cText += '\t'+str(len(basicTypeList))+'\n'
        cText += '};'
        return cText
    
    def _genRawParamDataConverter (self):
        basicTypeList = self.db.HAL_basicIOTypes_getList()
        # basic io helper
        cText = """// converts data
int APconvertRawParamData (int dataEndianes, void * pData, THALFunctionParam const * pPD, TuAPInterpreterFunctionParameter * pP, TAPInterpreterVariable *pIVL) {
    int index;
    
    if (eHALfunctionParamClass_basicIOtype == pPD->paramClass) goto basictypeConv;
    APendianConversation32Bit((uint32_t *)pData, dataEndianes);
    index = (int) *((int32_t *)pData);
    switch (pPD->paramClass) {
        case eHALfunctionParamClass_refVar:
            pP->fp_pV = &pIVL[index];
            break;
        case eHALfunctionParamClass_refDataVar:
            pP->fp_pD = pIVL[index].pVI->pFkt_decodeData(pIVL[index].pData);
            break;
        case eHALfunctionParamClass_VarID:
            pP->fp_VarID = index ;
            break;
        case eHALfunctionParamClass_VarIndex:
            pP->fp_VarIndex = index ;
            break;
    }
    return 0;
basictypeConv:
    switch (pPD->paramTypeID) {
"""
        for bt in basicTypeList:
            cText += '\t\tcase '+str(bt[1])+':\n'
            if bt[5] == True:
                cText += '\t\t\tAPendianConversation32Bit((uint32_t *)pData, dataEndianes);\n'
            cText += '\t\t\tpP->fp_'+str(bt[2])+' = *((' + bt[4] +'* )pData);\n'
            cText += '\t\t\tbreak;\n'
        cText += '\t\tdefault:\n\t\t\treturn -1;\n\t};\n'
        cText += '\treturn 0;\n};\n'
        return cText
    

    def _genHALVariablesDef (self, varImplList):
        extraIncludes = []
        
        basicTypeList = self.db.HAL_basicIOTypes_getList()

        ct = ''
        ctHALVarsInfo =''
        if varImplList != None:
            for implVarUUID, varID, codeID, implDescr, groupID in varImplList:
                # get HAL var defs
                HALvar, HALvarParamL = self.db.HAL_VariableDefinition_getByVariableID(varID)
                HALvarUUID, varID, HALvarName, HALvarDescr = HALvar  
                # get implementation code
                implVarcode = self.db.Code_getCode(codeID)
                # get the extra includes
                extraIncludes += self.db.Code_getIncludesWithoutUUID(codeID)
                # generate code
                if ct != '':
                    ct += '\n'
                ct += """// HAL variable implementation for {HALvarName}
// HAL descr: {HALvarDescr}
// implementation descr: {implDescr}
// here goes the implementation
{implCode}""".format(
               HALvarName=HALvarName,
               HALvarDescr=HALvarDescr,
               implDescr=implDescr,
               implCode=implVarcode
               )
                if ctHALVarsInfo != '':
                    ctHALVarsInfo += ',\n'
                ctHALVarsInfo += self._genVarDefinition(varID)
                
            amountOfHALvars = len(varImplList)
        else:
            vL = self.db.HAL_VariableDefinition_getList()
            for v in vL:
                varID = v[1]
                incl, genC = self._genHALVarMsgScripts(varID)
                extraIncludes += incl
                ct += genC
                if ctHALVarsInfo != '':
                    ctHALVarsInfo += ',\n'
                ctHALVarsInfo += self._genVarDefinition(varID)
            
            amountOfHALvars = len(vL)
                
        # now generate some infos
        ct += """
// global HAL variable info variables
THAL_Variable const gHALvariableInfo [] = {{
    {ctHALVarsInfo}
}};

THAL_VariableList const gHALVariableList = {{gHALvariableInfo,{num}}};
""".format(
           ctHALVarsInfo=self._genCCodeOrientation(ctHALVarsInfo,1),
           num=amountOfHALvars 
           )
        return extraIncludes, ct

    def _genHALFunctionInfo (self, fid):
        fUUID, fid, fname, fdescr = self.db.HAL_DefFunctions_getFromFunctionID(fid)
        fPL = self.db.HAL_DefFunctions_getParamList(fid)
        cparams = ''
        for fpUUID, fid, pname, pdescr, pclass, ptype in fPL:
            if cparams != '':
                cparams += ',\n'
            cparams += '// name: {pname} descr: {pdescr}\n'.format(pname=pname,pdescr=pdescr)
            cparams += '{{.paramClass = {paramClass}, .paramTypeID = {paramTypeID}}}'.format(paramClass=pclass,paramTypeID=ptype)
        
        tfi = """// function info for {fname} ({fid})
THALFunctionParam const gpHALFunctionParam_{fid}_{fname} [] = {{ {cparams}
}};""".format(
              fname=fname,
              fid=fid,
              cparams=self._genCCodeOrientation(cparams,1)
              )

        tFParamList = """{{gpHALFunctionParam_{fid}_{fname},{num}}}""".format(
            fname=fname,
            fid=fid,
            num=len(fPL)
            )
        return tFParamList, tfi
        

    def _genHALFunctionImplCode (self, funcImplList):
        extraIncludes = []
        ct = ''
        cHALfuncList = ''
        if funcImplList is None:
            funcImplList = []
        
        for implFuncUUID, fID, codeID, implFuncDescr, groupID  in funcImplList:
            # get HAL func defs
            HALfuncUUID, fID, HALfuncName, HALfuncDescr = self.db.HAL_DefFunctions_getFromFunctionID(fID)  
            # get implementation code
            implFuncCode = self.db.Code_getCode(codeID)
            # get the extra includes
            extraIncludes += self.db.Code_getIncludesWithoutUUID(codeID)
            # generate code
            if ct != '':
                ct += '\n'
            ct += """// HAL function implementation for {HALfuncName}
// HAL descr: {HALfuncDescr}
// implementation descr: {implFuncDescr}
// here goes the implementation
{implCode}""".format(
               HALfuncName=HALfuncName,
               HALfuncDescr=HALfuncDescr,
               implFuncDescr=implFuncDescr,
               implCode=implFuncCode
               )
            
            fPN, fPC = self._genHALFunctionInfo(fID)
            ct += '\n' + fPC
            if cHALfuncList != '':
                cHALfuncList += ',\n'
            cHALfuncList += """// HAL function info for {HALfuncName}
{{
    .fid = {fID},
    .paramList = {fParamList},
    .pfktHAL = {fHALFuncName}
}}""".format(
             HALfuncName=HALfuncName,
             fID=fID,
             fParamList=self._genCCodeOrientation(fPN, 1),
             fHALFuncName=self.getFunctionNameFromFIDandName(fID, HALfuncName)
             )
        
        ct += """// the function info vector 
THALFunction const gpFunctionInfoVector [] = {{
    {cHALfuncList}
}};
// the global HAL function info variable
THALFunctionList const gHALFunctionList = {{gpFunctionInfoVector,{num}}};
""".format(
        cHALfuncList=self._genCCodeOrientation(cHALfuncList, 1),
        num=len(funcImplList)
        )
        return extraIncludes, ct
    
    def _genHALmsgSystem_enum (self):
        cText = ''
        msgTDict = self.genMsgTypeEnum()
        i = 0
        cText += 'enum eAPMsgTypes {\n'
        for msgTN,(enumMsgType,msgTypID) in msgTDict.items():
            if (i != 0) :
                cText +=','
            cText += '\n\t'+enumMsgType+' = '+str(msgTypID)
            i += 1
        cText += '\n};\n'
        return cText, msgTDict['ACK'][0]
    
    def _genHALmsgDrvImpl (self, implDrvL):
        ct = ''
        ht = ''
        extraIncludes = [] 
        msgDrvDataL, msgDrvFunctL = self.getMsgDrvFunctionsAndCommentsHeader()

        
        for idImplMsgDriver, codeID, descr, idImplGroup in implDrvL:
            # get code
            implDrvcode = self.db.Code_getCode(codeID)
            # get the extra includes
            extraIncludes += self.db.Code_getIncludesWithoutUUID(codeID)
            # gen the set code for the mapping of the drv struct to the driver
            drvFuncSet = ''
            for dfDescr, dfres, dfname, dfparams in msgDrvFunctL:
                if drvFuncSet != '':
                    drvFuncSet += '\n'
                drvFuncSet += 'pDrv->pfkt_{drvfname} = drv_{idImplMsgDriver}_{drvfname};'.format(drvfname=dfname,idImplMsgDriver=idImplMsgDriver)
            if ct != '':
                ct += '\n'
            ct += """// message system driver with uuid={idImplMsgDriver}
// description: {descr}

// the driver functions
{implDrvcode}

// the init function for driver {idImplMsgDriver}
void APdriver_{idImplMsgDriver}_init (TAPMsgDrv  * pDrv) {{
    memset(pDrv,0,sizeof(TAPMsgDrv));
    {drvFuncSet}
}}""".format(
             idImplMsgDriver=idImplMsgDriver,
             descr = descr,
             implDrvcode=implDrvcode,
             drvFuncSet=self._genCCodeOrientation(drvFuncSet, 1)
             )
            if ht != '':
                ht += '\n';
            ht += """// the init function for driver {idImplMsgDriver}
void APdriver_{idImplMsgDriver}_init (TAPMsgDrv  * pDrv);""".format(idImplMsgDriver=idImplMsgDriver)
                
        return extraIncludes, ht, ct
    
    def _genMSGSystem (self):
        cText = ''
        mspL = self.db.HAL_msg_Process_getList()
        
        rxList = 'THALMsgProcessMessageAssociation const gHALMsgProcessRXHandlerArray [] = {'
        rxCode = ''
        rxCount = 0
        
        for msp in mspL :
            # no debugging
            cplr = APmsgProcessCompilier.MsgProcessGrammar(0)
            msgProcID = msp[1]
            name = msp[2]
            descr = msp[3]
            isRX = msp[4]
            dstr = '// msg process :' + name + ' descr: ' + descr + '\n'
            compileRes = cplr.translate(msp[5])
            if None == compileRes:
                if isRX == True:
                    TMStr = 'RX'
                else:
                    TMStr = 'TX'
                return (False,'compiling msg process "' + msp[2]+ '",'+TMStr+' failed')
            if False == isRX:
                cText += dstr
                cText += compileRes
            else:
                if 0 != rxCount :
                    rxList += ','
                rxList += '\n\t{{.msgID = {msgid}, .pfktHandle = {handle}}}'.format(msgid=msgProcID,handle=cplr.functionName)
                rxCode += compileRes + '\n'
                rxCount += 1
            
        rxList += '\n};\n'

        cText += '// message RX process\n\n'
        cText += '// message RX process handle functions\n'
        cText += rxCode
        cText += '// rx handler array var\n'
        cText += rxList
        cText += '// message RX global var\n'
        cText += 'HALMsgProcessHandlerList const gHALMsgProcessRXHandlers = {\n'
        cText += '\tgHALMsgProcessRXHandlerArray,\n\t'
        cText += str(rxCount)
        cText += '\n};\n'
        
        return True, cText
    
    def _genAPListCode (self, APL):
        extraIncludes = []
        ct = ''

        for idImplAP, codeID, descr, idGroup in APL:
            implAPcode = self.db.Code_getCode(codeID)
            # get the extra includes
            extraIncludes += self.db.Code_getIncludesWithoutUUID(codeID)
            if ct != '':
                ct += '\n'
            ct += """// audio processor blueprint with uuid={idImplAP}
// description: {descr}

{implAPcode}""".format(
                       idImplAP=idImplAP,
                       descr=descr,
                       implAPcode=implAPcode
                       )
        return extraIncludes, ct
    
    def _genGroupCode (self, GL):
        cText = ''
        extraIncludes = []
        for g in GL:
            code = self.db.Code_getCode(g[2])
            inclL = self.db.Code_getIncludesWithoutUUID(g[2])
            if code != None:
                cText += self.genBreakComment('// extra code for group "'+g[1]+'"')
                cText += code
                cText += '\n'

            if inclL != None:
                for i in inclL:
                    extraIncludes.append(i)

        return extraIncludes, cText
    
    def genCode(self, uuidAP, extraDrvImplUUID, genDebugCode):
        
        extraIncludes = []
        
        # build header substitution strings 
        headerSubstitutions = {
            '@headerComment'            : self.genCCodeHeaderComment(),
            '@msgDrvDeclaration'        : self.genMsgDrvStruct(),
            '@functionParamClasses'     : self.genFunctionParamClasses(),
            '@IPmaxParams'              : self.genIPmaxParams(),
            '@funcParamType'            : self.genFuncParamType(),
            '@VarFunctions'             : self.genHALVarHeaderFunctions(),
            '@messagedriverHelper'      : None 
            }
        
        implementationSubstitutions = {
            '@headerInfo'               : self.genCCodeHeaderComment(),
            '@extraIncludes'            : None,
            '@basictypesImplementation' : None,
            '@RawParamDataConverter'    : None,
            '@varImplmentation'         : None,
            '@functionImplementaion'    : None,
            '@MsgTypeEnum'              : None,
            '@messageProcesses'         : None,
            '@APimplemention'           : None,
            '@ExtraGroupCode'           : None,
            '@ackEnum'                  : None,
            '@debugInterface'           : None
            }
        
        if uuidAP != None:
            # get the implementation index
            FL = self.db.AP_implTable_getList('FunctionList',uuidAP)
            VL = self.db.AP_implTable_getList('VariableList',uuidAP)
            DL = self.db.AP_implTable_getList('DriverList',uuidAP)
            AL = self.db.AP_implTable_getList('APList',uuidAP)
            # gather implementations
            implFunc = []
            for f in FL:
                implFunc.append(self.db.Impl_HALFunction_get(f[2]))
            implVar = []
            for v in VL:
                implVar.append(self.db.Impl_HALVariable_get(v[2]))
            implDrv = []
            for d in DL:
                implDrv.append(self.db.Impl_ImplMsgDriver_get(d[2]))
            implAP = []
            for ap in AL:
                implAP.append(self.db.Impl_ImplAP_get(ap[2]))
        else:
            implFunc = None
            implVar = None
            implDrv = [self.db.Impl_ImplMsgDriver_get(extraDrvImplUUID)]
            implAP = []
        
        # basic types
        
        implementationSubstitutions['@basictypesImplementation'] = self._genBasicTypeList()


        implementationSubstitutions['@RawParamDataConverter'] = self._genRawParamDataConverter()

        # -------------------------------
        # hal variables
        # -------------------------------
        extraIncl, cText = self._genHALVariablesDef(implVar)
        extraIncludes += extraIncl
        implementationSubstitutions['@varImplmentation'] = cText

        # -------------------------------        
        # functions
        # -------------------------------
        
        extraIncl, cText = self._genHALFunctionImplCode(implFunc)
        extraIncludes += extraIncl
        implementationSubstitutions['@functionImplementaion'] = cText
        
        # -------------------------------
        # msg types
        # -------------------------------
        
        cText, ackCode = self._genHALmsgSystem_enum()

        implementationSubstitutions['@MsgTypeEnum'] = cText
        implementationSubstitutions['@ackEnum'] = ackCode
        
        extraIncl, hText, cText = self._genHALmsgDrvImpl(implDrv)
        
        extraIncludes += extraIncl
        implementationSubstitutions['@messageDriver'] = cText
        headerSubstitutions['@messagedriverHelper'] = hText

        # generate message system

        r, cText = self._genMSGSystem()
        if (r == False):
            return r, cText 
        implementationSubstitutions['@messageProcesses'] = cText

        # generate AP functions
        if uuidAP is None:
            f = open(self.remoteInterfaceAPinterfaceTemplate, "rb")
            cText = f.read()
            f.close()
            extraIncl = [('pthread.h','pthread',True)]
        else:
            cText = ''
            extraIncl, cText = self._genAPListCode(implAP)
        extraIncludes += extraIncl
        implementationSubstitutions['@APimplemention'] = cText
        
        
        # generate extra code from the groups
        # 1. get the group list and match it againgst the implementation lists
        gl = self.db.AP_getGroups(uuidAP)
        # 2. iterate through groups and add code
        extraIncl, cText = self._genGroupCode(gl)
        extraIncludes += extraIncl
        implementationSubstitutions['@ExtraGroupCode'] = cText
        
        # insert the extra includes
        
        usedIncludes = self.removeDoubleIncludeEntries(extraIncludes)
        implementationSubstitutions['@extraIncludes'] = self.genCCodeFromDBIncludeList(usedIncludes)
        
        if genDebugCode == True:
            extraIncl,hText, cText = self._genDebugCode(implFunc)
            implementationSubstitutions['@debugInterface'] = cText 
            headerSubstitutions['@debugInterface'] = hText
        else:
            implementationSubstitutions['@debugInterface'] = '// not selected'
            headerSubstitutions['@debugInterface'] = ''

        # build files
        
        # the header file
        hText = self.staticData.files['header']
        for k, v in headerSubstitutions.items():
            hText = hText.replace(k, v)
        
        # the c/c++ file
        cText = self.staticData.files['code']
        for k, v in implementationSubstitutions.items():
            cText = cText.replace(k, v)
                    
        # build lib list from the include list
        libL = []
        for includefile, lib, syslib in usedIncludes:
            if (lib != None) and (lib != '') : libL.append(lib)
        
        # some extensions for the remote interface
        if uuidAP is None:
            readTextFromFile()
             
        
        return (True, hText, cText, libL)


    def generateAP(self, uuidAP, c89, genDebugCode):
        log = APlogger.getCodeGenLogger()
        
        log.info( 'check AP ...')
        log.info( 'start generate audio processor ...')
        
        log.info('setup environment for code generation...')
        self.setup()
        log.info('set file extensions')
        
        if c89 == False:
            self.hExt = '.h'
            self.cExt = '.cpp'
        else:
            self.hExt = '.h'
            self.cExt = '.c'
        
        log.info('generate AP')
        
        r = self.genCode(uuidAP, None, genDebugCode)
        if False == r[0]:
            log.error(r[1])
            return False
        # cast tuple values to the vars
        r, header, cfile, libList = r
                
        f = open(self.getCompleteFileName(self.HALskeletonHeaderFilename + self.hExt), "w")
        f.write(header)
        f.close()

        f = open(self.getAPSourceFile(), "w")
        f.write(cfile)
        f.close()
        
        log.info('generate main file')
        ap = self.db.AP_get(uuidAP)
        sc = self.db.Code_getCode(ap[4])
        if sc != None:
            f = open(self.getAPmainSourceFile(), "w")
            f.write(sc)
            f.close()
        log.info('generate lib list')
        inclL = self.db.Code_getIncludesWithoutUUID(ap[4])
        for includefile, lib, syslib in inclL:
            if (includefile != None) and (lib != ''):
                libList.append (lib)
        
        log.info('finished')
        return (True, libList)
        
        
    def UIgenAPemptyFunctions (self, uuidMMUImpl):
        incl = []
        incl.append((self.HALskeletonHeaderFilename + self.hExt,'',False))
        tc = self.genBreakComment('AP uuid = '+str(uuidMMUImpl))
        
        #replace Mutex sections
        mb = DBwindows.MessageBox(
                message='Generate a audio processor blueprint witch fits into a multithreading enviroment?',
                buttons=('Yes','No')
                )
        mb.run()

        if 'Yes' == mb.ret:
            tc += self.staticData.files['bp_mt'];
        else:
            tc += self.staticData.files['bp_st'];
        return (incl, tc)

    def UIgenMsgDrvEmptyFunctions (self, uuidDrvImpl):
        incl = []
        incl.append((self.HALskeletonHeaderFilename + self.hExt,'',False))
        
        drvPL,drvFL = self.getMsgDrvFunctionsAndCommentsHeader()
        
        tc = '// ===============================\n'
        tc += '// driver uuid ='+str(uuidDrvImpl)+'\n'
        tc += '// ===============================\n\n'
        
        for f in drvFL:
            tc += '//'+f[0]+'\n'
            tc += f[1] + ' drv_'+str(uuidDrvImpl)+'_' +f[2]+' ('+f[3]+') {\n\treturn 0;\n}\n'
        return (incl, tc)
    
    def _genCCodeOrientation (self, ctext, tabAmount):
        tabInsert = ''
        for i in range(0,tabAmount):
            tabInsert += '\t'
        ctext = ctext.replace('\n','\n'+tabInsert)
        return ctext

    def _genHALVar_getParamTypeDef (self, pArrayFlag, pname, cType, pDescr):
            if pArrayFlag == False:
                return ['{type} {name};//{comment}'.format(type=cType, name=pname, comment=pDescr)]
            else :
                return [
                  '{type} * {arrayPrefix}{name};// {comment} (array)'.format(type=cType,name=pname, arrayPrefix=self.dtypeArrayPrefix,comment=pDescr),
                  'int32_t {numPrefix}{name};// amount of {name} elements'.format(name=pname, numPrefix=self.dtypeArrayNumPrefix)
                ]
                
    def _genHALVar_getParamCreateCmdTmpl (self, pArrayFlag, pname, cType):
        if pArrayFlag == False:
            return ''
        return """// create array for {name} parameter
{{pE}}->{arrayPrefix}{name} = malloc(sizeof({type})*{{elementAmmount}});
if(!{pE}->{arrayPrefix}{name}) {{{{
    {mallocError}
}}}}
memset({{pE}}->{arrayPrefix}{name},0,sizeof({type})*{{elementAmmount}});
{pE}->{numPrefix}{name}={{elementAmmount}};""".format(name=pname, arrayPrefix=self.dtypeArrayPrefix, numPrefix=self.dtypeArrayNumPrefix, type=cType)

    def _genHALVar_getParamDelCmdTmpl (self, pArrayFlag, pname, cType):
        if pArrayFlag == False:
            return ''
        return """// delete parameter {name}
if ({{pE}}->{arrayPrefix}{name}) {{{{
    free({{pE}}->{arrayPrefix}{name});
    {{pE}}->{arrayPrefix}{name}=NULL;
    {{pE}}->{numPrefix}{name}=0;
}}}}""".format(name=pname, arrayPrefix=self.dtypeArrayPrefix,numPrefix=self.dtypeArrayNumPrefix)

    def _genHALVar_createTypeDef (self, vname, paramL, TypeStructStr):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr
        paramsTxt = ''
        for (pname, pArrayFlag, endianFlag, cType, pDescr) in paramL:
            pD = self._genHALVar_getParamTypeDef(pArrayFlag, pname, cType, pDescr)
            for e in pD:
                paramsTxt += '\n' + e
      
        return """// element structure for {vname}
typedef struct {eleStructName} {{{params}
}} {varEleType};

// vector structure for {vname}
typedef struct {vectStructName} {{
    {varEleType} * {FE}; // first element at the vector
    int32_t {numName}; // amount of elements at the vector
}} {vectTypeName};


""".format(
        vname=vname,
        eleStructName=strVarEleStruct,
        params=self._genCCodeOrientation(paramsTxt,1),
        vectStructName=strVarVectStruct,
        vectTypeName=strVarVectTyp,
        varEleType=strVarEleTyp,
        FE=self.dtypeVectFirstElementName,
        numName = self.dtypeVectNumName 
    )

    def _genHALVar_createTypeElementCreationCode (self, vname, TypeStructStr, vectName, amountPattern, errorPattern):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr
        return """// create the elements for {vname}
{vectName}->{FE} = malloc(sizeof({eleType})*{amountPattern});
if (!{vectName}->{FE}) {{
    free({vectName});
    {errorPattern}
}}
{vectName}->{numName} = {amountPattern};""".format(
           vname=vname,
           vectName=vectName,
           vectType=strVarVectTyp,
           eleType=strVarEleTyp,
           amountPattern=amountPattern,
           errorPattern=errorPattern,
           FE=self.dtypeVectFirstElementName,
           numName = self.dtypeVectNumName
        )


    def _genHALVar_createTypeCreationCode (self, vname, TypeStructStr, vectName, amountPattern, errorPattern):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr
        return """// create a new {vname} vector
{vectType} * {vectName};
 
{vectName} = malloc(sizeof({vectType}));
if (!{vectName}) {{
    {errorPattern}
}}
""".format(
           vname=vname,
           vectName=vectName,
           vectType=strVarVectTyp,
           eleType=strVarEleTyp,
           amountPattern=amountPattern,
           errorPattern=errorPattern,
           FE=self.dtypeVectFirstElementName,
           numName = self.dtypeVectNumName
        ) +  self._genHALVar_createTypeElementCreationCode(vname, TypeStructStr, vectName, amountPattern, errorPattern) + '\nreturn {vectName};'.format(vectName=vectName)
        
    def _genHALVar_createTypeDeleteCode (self, ParamL, vname, TypeStructStr, vectName, subVectName, counterVar,freeVectStruct=True):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr
        txtSubParams = ''
        txtVarDef = ''
        for (pname, pArrayFlag, endianFlag, cType, pDescr) in ParamL:
            txtSubParams += '\n' + self._genHALVar_getParamDelCmdTmpl(pArrayFlag, pname, cType)
        
        if txtSubParams != '':
            txtVarDef = '{varEleType} * {pE};\nint32_t {i};'.format(varEleType=strVarEleTyp,pE=subVectName,i = counterVar)
            txtSubParams = """// go over every element and delete the array paramters
{pE} = {vectName}->{FE};
for ({i}=0; {i}<{vectName}->{numName};{i}++) {{ {freeParam}
    {pE}++;
}}""".format(
             pE=subVectName,
             vectName=vectName,
             FE=self.dtypeVectFirstElementName,
             numName = self.dtypeVectNumName,
             i = counterVar,
             freeParam=self._genCCodeOrientation(txtSubParams.format(pE=subVectName),1)
            )
            
        txtFreeElements = """// frees a {vname} vector
{vectType} * {vectName} = ({vectType} *) pVarData;

if ({vectName}) {{
    if ({vectName}->{FE}) {{
        {subParamFree}
        free({vectName}->{FE});""".format(
           vname=vname,
           vectType=strVarVectTyp,
           vectName=vectName,
           FE=self.dtypeVectFirstElementName,
           numName = self.dtypeVectNumName,
           subParamFree=self._genCCodeOrientation(txtSubParams,2)
        )
        
        if freeVectStruct == True:
            txtFreeElements += """
        }}
    free({vectName});
}}""".format(vectName=vectName)
        else:
            txtFreeElements += """
        {vectName}->{FE} = NULL;
        {vectName}->{numName} = 0;
    }}
}}""".format(vectName=vectName, FE=self.dtypeVectFirstElementName, numName = self.dtypeVectNumName)
        return (txtVarDef, txtFreeElements)

    def _genHALVar_createTypeRXCode (self, ParamL, vname, TypeStructStr, vectName, subVectName):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr
        
        # get free code
        (subExtraParamVars,freeCodeVec) = self._genHALVar_createTypeDeleteCode(ParamL, vname, TypeStructStr, vectName, subVectName, 'i',False)
        # kick extra vars
        subExtraParamVars=''
        
        # get realloc code
        allocCodeVec = self._genHALVar_createTypeElementCreationCode(vname, TypeStructStr, 'pV', 'imax', 'return -1;')


        ParamsRecv = ''
        for (pname, pArrayFlag, endianFlag, cType, pDescr) in ParamL:
            if ParamsRecv != '':
                ParamsRecv += '\n'
            if endianFlag is True :
                endianConv = 'APendianConversation32Bit(pD,eAP_littleEndian);'
            else:
                endianConv = '// no endian conversation'
                
            if pArrayFlag is True:
                if subExtraParamVars == '':
                    subExtraParamVars = 'int32_t n, nmax;'
                ParamsRecv += """// rx {pname}
APendianConversation32Bit(pD,eAP_littleEndian);
nmax = *((int32_t *) pD);
// resize parameter
if (nmax != {pVele}->{numPreFix}{pname}) {{
    if ({pVele}->{arrayPreFix}{pname}) free({pVele}->{arrayPreFix}{pname});
    {pVele}->{arrayPreFix}{pname} = malloc(sizeof({varType})*nmax);
    if (!{pVele}->{arrayPreFix}{pname}) return -2;
    {pVele}->{numPreFix}{pname} = nmax;
}}

pD++;
for (n = 0; n < {pVele}->{numPreFix}{pname}; n++) {{
    {endianConv}
    {pVele}->{arrayPreFix}{pname}[n]=*(({varType} *)pD);
    pD++;
}}""".format(
             pname=pname,
             pVele=subVectName,
             arrayPreFix=self.dtypeArrayPrefix,
             numPreFix=self.dtypeArrayNumPrefix,
             endianConv=endianConv,
             varType=cType
        )
            else:
                ParamsRecv += """// rx {pname}
{endianConv}
{pVele}->{pname}=*(({varType} *)pD);\npD++;""".format(
                        endianConv=endianConv,
                        pVele=subVectName,
                        arrayPreFix=self.dtypeArrayPrefix,
                        pname=pname,
                        varType=cType
                    )

        
        return """// rx function for {vname}
uint32_t * pD = (uint32_t *) pMsgData;
{vecType} * {pVvec} =({vecType} *) pVarData;
{eleType} * {pVele};
int i, imax;
{subExtraParamVars}

// at the first possion at the message is the global var index
pD++; // skip it (it's the varindex)
// and now we are at amount of values
APendianConversation32Bit(pD,eAP_littleEndian);
imax = (int) *((int32_t *)pD);
pD++;
// 1. resize vector if needed
if ({pVvec}->{numName} != imax) {{
    {freeCodeVec}
    {allocCodeVec}
}}

// 2. fill parameters
{pVele} = {pVvec}->{FE};

for (i = 0; i < imax; i++) {{
    {ParamsRecv}
    // goto next element
    {pVele}++;
}}
return 0;""".format(
                   vname=vname,
                   vecType=strVarVectTyp,
                   pVvec=vectName,
                   eleType=strVarEleTyp,
                   pVele=subVectName,
                   subExtraParamVars=subExtraParamVars,
                   freeCodeVec=self._genCCodeOrientation(freeCodeVec,1),
                   allocCodeVec=self._genCCodeOrientation(allocCodeVec,1),
                   ParamsRecv=self._genCCodeOrientation(ParamsRecv,1),
                   FE=self.dtypeVectFirstElementName,
                   numName = self.dtypeVectNumName
                )
        
    def _genHALVar_createTypeTXCode (self, ParamL, vname, TypeStructStr, vectName, subVectName):
        (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct) = TypeStructStr

        staticSize = 0
        codeSize = ''
        txTransferCode = ''
        fm = self.getMsgDrvVarParameterToFunctionAsso()

        for (pname, pArrayFlag, endianFlag, cType, pDescr) in ParamL:
            if txTransferCode != '':
                txTransferCode += '\n'
            funcName = fm.get(cType,'sendRaw')
            if pArrayFlag == False:
                staticSize += 1
                txTransferCode += 'pMD->pfkt_{sendFunc}(pMD,1,&{pVele}->{pname});'.format(
                                                                                          pVele=subVectName,
                                                                                          sendFunc=funcName,
                                                                                          pname=pname
                                                                                        )
            else:
                # num = 1
                staticSize += 1 
                # calc
                if codeSize != '':
                    codeSize += '+'
                codeSize += '{pVele}->{numPreFix}{pname}'.format(
                                                                pVele=subVectName,
                                                                pname=pname,
                                                                numPreFix=self.dtypeArrayNumPrefix
                                                                )
                # no we have to send a vector
                # first length
                txTransferCode += 'pMD->pfkt_{sendFunc}(pMD,1,&{pVele}->{numPreFix}{pname});'.format(
                                                                                                     sendFunc=fm.get('int32_t'),
                                                                                                     pVele=subVectName,
                                                                                                     pname=pname,
                                                                                                     numPreFix=self.dtypeArrayNumPrefix
                                                                                                    )
                txTransferCode += '\npMD->pfkt_{sendFunc}(pMD,{pVele}->{numPreFix}{pname},{pVele}->{arrayPreFix}{pname});'.format(
                                                                                                                                sendFunc=funcName,
                                                                                                                                pVele=subVectName,
                                                                                                                                pname=pname,
                                                                                                                                arrayPreFix=self.dtypeArrayPrefix,
                                                                                                                                numPreFix=self.dtypeArrayNumPrefix
                                                                                                                            )
        # create code size code
        if codeSize != '':
            codeSize = """// calc amount of elements from the params
{pVele} = {pVvec}->{FE};
for (n = 0; n < {pVvec}->{numName}; n++) {{
    dataAmount += {codeSize};
}}""".format(
             pVvec=vectName,
             pVele=subVectName,
             FE=self.dtypeVectFirstElementName,
             numName = self.dtypeVectNumName,
             codeSize=codeSize
             )

        return """ // tx function for {vname}
{vecType} * {pVvec} =({vecType} *) pVarData;
{eleType} * {pVele};
TAPMsgDrv * pMD = (TAPMsgDrv *) pDrv;

int32_t dataAmount;
int32_t n;

// calc ammount of transmission bytes 
dataAmount = (int32_t) 1 + {pVvec}->{numName} * {staticSize};
{codeSize}
    
// 1 send header
pMD->pfkt_updateVariable(pMD->pDrvData, receiver, mNum, i, dataAmount);
        
// 2 send vector elementwise

// 2.1 send amount of elements at the vector
pMD->pfkt_sendInteger32(pMD,1,&{pVvec}->{numName});

// 2.2 send element
{pVele} = {pVvec}->{FE};
for (n = 0; n < {pVvec}->{numName}; n++) {{
    {txTransferCode}
    // inc
    {pVele}++;
}}
return 0;""".format (
                     vname=vname,
                     vecType=strVarVectTyp,
                     pVvec=vectName,
                     eleType=strVarEleTyp,
                     pVele=subVectName,
                     FE=self.dtypeVectFirstElementName,
                     numName = self.dtypeVectNumName,
                     staticSize=staticSize,
                     codeSize=codeSize,
                     txTransferCode=self._genCCodeOrientation(txTransferCode,1)
                    )
    
    
    def _genHALVarMsgScripts (self, varID):
        vi = self.db.HAL_VariableDefinition_getByVariableID(varID)
        if None == vi[0]:
            return (None,'// error at variable id ({varid}) a HAL definition with the id dosn\'t exists'.format(varID))

        
        varUUID, varID, vname, vdesc = vi[0]

        strVarEleTyp = 'T{0}{1}{2}'.format(self.dtypePreFix, self.dtypeElementStr, vname)
        strVarVectTyp = 'T{0}{1}{2}'.format(self.dtypePreFix, self.dtypeVectorStr, vname)
        strVarEleStruct = 'S{0}{1}{2}'.format(self.dtypePreFix, self.dtypeElementStr, vname)
        strVarVectStruct = 'S{0}{1}{2}'.format(self.dtypePreFix, self.dtypeVectorStr, vname)
        TypeStructStr = (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct)
        
        vpL = self.db.HAL_VariableDefinition_getParamList(varID)
                
        ParamL = []
                
        for paramUUID, bTID, vid, pname, pDescr, pArrayFlag in vpL:
            pArrayFlag = bool(pArrayFlag)
            bt = self.db.HAL_basicIOTypes_getByTypeID(bTID)
            btUUID, bTID, bTypeName, bTypeDescr, cType, endianFlag, btSize = bt
            endianFlag = bool(endianFlag)
            ParamL.append((pname, pArrayFlag, endianFlag, cType, pDescr))

        ctxtTypeDef = self._genHALVar_createTypeDef(vname, ParamL, TypeStructStr)
        ctxtCreate = self._genHALVar_createTypeCreationCode(vname, TypeStructStr, 'pV', 'numberOfElements', 'return NULL;')
        ctxtDelete = self._genHALVar_createTypeDeleteCode(ParamL, vname, TypeStructStr, 'pV', 'pE', 'i',True)[0] + self._genHALVar_createTypeDeleteCode(ParamL, vname, TypeStructStr, 'pV', 'pE', 'i',True)[1]
        ctxtRX = self._genHALVar_createTypeRXCode(ParamL, vname, TypeStructStr, 'pV', 'pE')
        ctxtTX = self._genHALVar_createTypeTXCode(ParamL, vname, TypeStructStr, 'pV', 'pE')
        
        incl = []
        incl.append((self.HALskeletonHeaderFilename + self.hExt,'',False))
        
        
        tc = '// ===============================\n'
        tc += '// variable implementation for {vname} (varID={varid})\n'.format(vname=vname,varid=varID)
        tc += '// ===============================\n\n'
        
        tc += ctxtTypeDef
        
        fd = self.getVarFunctName(varID)
        for e, func in fd.items():
            if e == 'sendUpdate':
                innerCode = ctxtTX
            elif e == 'recvUpdate':
                innerCode = ctxtRX
            elif e == 'create':
                innerCode = ctxtCreate
            elif e == 'delete':
                innerCode = ctxtDelete
            else:
                innerCode = func[4]
            tc += '// {0}\n{1} {2} ( {3} ) {{\n {4} \n}}\n'.format(func[0], func[2], func[1], func[3], self._genCCodeOrientation(innerCode,1))

        return (incl, tc)

    def _genDebugCode (self, implFunc):
        th = self.genBreakComment('debug interface')
        th += """ // function info
typedef struct SAPFuncDebugInfo {
    int const               fid;    //!< function id
    const char *            szName; //!< function name
    const TpfktHALfunction  fkt;    //!<  function pointer
} TAPFuncDebugInfo;

// function info list
typedef struct SAPFuncDebugInfoList {
    const TAPFuncDebugInfo *     pFI;    //!< pointer to const list
    int const                    num;    //!< amount of elements at the list
} TAPFuncDebugInfoList;

extern TAPFuncDebugInfoList const gDebugInfo_HALFunctionList;

TAPFuncDebugInfo * APDebugInfoFindHALFunction (TpfktHALfunction sf);
"""
        tc = self.genBreakComment('debug interface')
        tc += """TAPFuncDebugInfo const gDebugInfo_HALFunction [] = {
"""
        FL = self.db.HAL_DefFunctions_getList()
        i = 0
        for f in FL:
            fid=f[1]
            fname=f[2]
            
            fktHALName = 'NULL'
            for implF in implFunc:
                if implF[1] == fid:
                    fktHALName = self.getFunctionNameFromFIDandName(fid, fname)
                    break
            if i > 0:
                tc += ',\n\t'
            else:
                tc += '\t'
            tc += '{{.fid={fid}, .szName="{fname}", .fkt={fktHALName}}}'.format(fid=fid,fname=fname, fktHALName=fktHALName)
            i += 1
 
        tc += """
}};

TAPFuncDebugInfoList const gDebugInfo_HALFunctionList = {{gDebugInfo_HALFunction,{fnum}}};""".format(fnum=i)

        tc += """

TAPFuncDebugInfo * APDebugInfoFindHALFunction (TpfktHALfunction sf) {
    int i;
    for (i = 0; i < gDebugInfo_HALFunctionList.num; i++) {
        if (gDebugInfo_HALFunction[i].fkt == sf) return &gDebugInfo_HALFunction[i];  
    }
    return NULL;
}"""

        
        VL = self.db.HAL_VariableDefinition_getList()
        
        return ([],th, tc)


    def UIgenVar (self,varID):
        return self._genHALVarMsgScripts(varID)
    
    def UIgenFunc (self,fID):
        
        incl = []
        incl.append((self.HALskeletonHeaderFilename + self.hExt,'',False))

        fI = self.db.HAL_DefFunctions_getFromFunctionID(fID)
        fpL = self.db.HAL_DefFunctions_getParamList(fID)
        ifp = self.getInterpreterFunctionsParams()
        
        (fHeaderDef, pIPcpu, pParam) = self.getHALFunctionParameterDef()
        
        tc = '// ===============================\n'
        tc += '// function implementation for ' + fI[2] + '(var id = '+str(fI[1])+')\n'
        tc += '// description: ' + fI[3] + '\n'
        tc += '// ===============================\n'
        tc += 'void ' + self.getFunctionName(fI) + '('+fHeaderDef+ ') {\n'
        c = 0
        for fp in fpL:
            tc += '// parameter '+fp[2]+' descr: '+fp[3]+'\n'
            #check param class
            if fp[4] == self.db.dFuncClass_basicIOtype:
                indx = fp[5]
            elif fp[4] == self.db.dFuncClass_refDataVar:
                indx = -self.db.dFuncClass_refDataVar
            elif fp[4] == self.db.dFuncClass_refVar:
                indx = -self.db.dFuncClass_refVar
            elif fp[4] == self.db.dFuncClass_VarID:
                indx = -self.db.dFuncClass_VarID
            elif fp[4] == self.db.dFuncClass_VarIndex:
                indx = -self.db.dFuncClass_VarIndex
            else :
                indx = None
            typedesc = ifp[indx]
            tc += '\t'+typedesc[0] + ' '+fp[2]+' = '+ pParam + '['+ str(c)+ '].'+ typedesc[1] +';\n'
            c += 1

        tc += '};\n'
        return (incl, tc)

    def UIgenStartUpCode (self):
        incl = []
        incl.append((self.HALskeletonHeaderFilename + self.hExt,'',False))
        tc = self.genBreakComment('startup code for the audio processor')
        tc += '\n\n'
        tc += self.staticData.files['startUpCode'];
        return (incl, tc)
    
    def _genGenericVariablesCmdLineIOInterface (self, varID):
        vi = self.db.HAL_VariableDefinition_getByVariableID(varID)
        if None == vi[0]:
            return (None,'// error at variable id ({varid}) a HAL definition with the id dosn\'t exists'.format(varID))

        varUUID, varID, vname, vdesc = vi[0]

        strVarEleTyp = 'T{0}{1}{2}'.format(self.dtypePreFix, self.dtypeElementStr, vname)
        strVarVectTyp = 'T{0}{1}{2}'.format(self.dtypePreFix, self.dtypeVectorStr, vname)
        strVarEleStruct = 'S{0}{1}{2}'.format(self.dtypePreFix, self.dtypeElementStr, vname)
        strVarVectStruct = 'S{0}{1}{2}'.format(self.dtypePreFix, self.dtypeVectorStr, vname)
        TypeStructStr = (strVarEleTyp,strVarVectTyp,strVarEleStruct,strVarVectStruct)
        
        vpL = self.db.HAL_VariableDefinition_getParamList(varID)
        ParamL = []
        for paramUUID, bTID, vid, pname, pDescr, pArrayFlag in vpL:
            pArrayFlag = bool(pArrayFlag)
            bt = self.db.HAL_basicIOTypes_getByTypeID(bTID)
            btUUID, bTID, bTypeName, bTypeDescr, cType, endianFlag, btSize = bt
            endianFlag = bool(endianFlag)
            ParamL.append((pname, pArrayFlag, endianFlag, cType, pDescr))
        tmplSingleValueOutput = 'printf("%{pfFlag}",({pfCType}){{{{pEV}}}}->{{pname}});'
        tmplSingleValueInput = 'printf("{{pname}}: ");scanf("%{pfFlag}",&{{{{pEV}}}}->{{pname}});'
        tmplArrayValueOutput = 'printf("{{pname}}:\\n");for({{i}}=0;{{i}}<{{{{pEV}}}}->{numPreFix}{{pname}};{{i}}++) {{{{{{{{if({{i}}) printf(", ");printf("%{pfFlag}",({pfCType}){{{{pEV}}}}->{arrayPreFix}{{pname}}[{{i}}]);}}}}}}}}'
        tmplArrayValueInput = 'printf("{{pname}}:\\n");for({{i}}=0;{{i}}<{{{{pEV}}}}->{numPreFix}{{pname}};{{i}}++) {{{{{{{{printf("value %i:",{{i}});scanf("%{pfFlag}",&{{{{pEV}}}}->{arrayPreFix}{{pname}}[{{i}}]);}}}}}}}}'
        tmplArrayExtryVars = 'int32_t {i};'
        
        tmplStringEntryOutput = 'printf("%{pfFlag}",({pfCType}){{{{pEV}}}}->{arrayPreFix}{{pname}});'
        tmplStringEntryVarDecl = 'char {strDummyVar}[{maxSize}+1];'
        tmplStringEntryInput = """scanf("%{{maxSize}}s",{{strDummyVar}});
if(strlen({{{{pEV}}}}->{arrayPreFix}{{pname}}) < strlen({{strDummyVar}})) {{{{{{{{
    free({{{{pEV}}}}->{arrayPreFix}{{pname}});
    {{{{pEV}}}}->{arrayPreFix}{{pname}} = malloc(sizeof(char)*(strlen({{strDummyVar}})+1));
    if (!{{{{pEV}}}}->{arrayPreFix}{{pname}}) {{{{{{{{ {{mallocErrorHandling}} }}}}}}}}
}}}}}}}}
strcpy({{{{pEV}}}}->{arrayPreFix}{{pname}},{{strDummyVar}});
{{{{pEV}}}}->{numPreFix}{{pname}} = strlen({{strDummyVar}})+1;""".format(arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix)
        
        

        functionMapping = {
                ('uint32_t',False)  : (
                                       tmplSingleValueOutput.format(pfFlag='u',pfCType='unsigned int'),
                                       '',
                                       tmplSingleValueInput.format(pfFlag='u',pfCType='unsigned int'),
                                       ''
                                    ),
                ('uint32_t',True)  : (
                                      tmplArrayValueOutput.format(pfFlag='u',pfCType='unsigned int',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                      tmplArrayExtryVars,
                                      tmplArrayValueInput.format(pfFlag='u',pfCType='unsigned int',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                      tmplArrayExtryVars
                                    ),
                ('int32_t',False)  : (
                                      tmplSingleValueOutput.format(pfFlag='i',pfCType='int'),
                                      '',
                                      tmplSingleValueInput.format(pfFlag='i',pfCType='int'),
                                      ''
                                    ),
                ('int32_t',True)  : (
                                     tmplArrayValueOutput.format(pfFlag='i',pfCType='int',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                     tmplArrayExtryVars,
                                     tmplArrayValueInput.format(pfFlag='i',pfCType='int',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                     tmplArrayExtryVars
                                    ),
                ('float',False)  : (
                                    tmplSingleValueOutput.format(pfFlag='f',pfCType='float'),
                                    '',
                                    tmplSingleValueInput.format(pfFlag='f',pfCType='float'),
                                    ''
                                    ),
                ('float',True)  : (
                                   tmplArrayValueOutput.format(pfFlag='f',pfCType='float',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                   tmplArrayExtryVars,
                                   tmplArrayValueInput.format(pfFlag='f',pfCType='float',arrayPreFix=self.dtypeArrayPrefix,numPreFix=self.dtypeArrayNumPrefix),
                                   tmplArrayExtryVars
                                ),
                ('char',False)  : (
                                   tmplSingleValueOutput.format(pfFlag='c',pfCType='char'),
                                   '',
                                   tmplSingleValueInput.format(pfFlag='c',pfCType='char'),
                                   ''
                                ),
                ('char',True)  : (
                                  tmplStringEntryOutput.format(pfFlag='s',pfCType='char *',arrayPreFix=self.dtypeArrayPrefix),
                                  '',
                                  tmplStringEntryInput,
                                  tmplStringEntryVarDecl
                                ),
                }
        
        # lets got through the param list and generarte some code snipets
        ctxtOutput = ''
        ctxtInput = ''
        notFoundT = ('// no output template','','// no input template','')
        outVDict = {}
        inVDict = {}
        strMaxSize = 200
        strDummyVarName = 'szDummy'
        for pname, pArrayFlag, endianFlag, cType, pDescr in ParamL:
            st = (cType,pArrayFlag)
            templOut, outExtraVar, templIn, inExtraVar = functionMapping.get(st,notFoundT)
            ctxtOutput += '\n'
            ctxtInput += '\n'
            ctxtOutput += templOut.format(pname=pname,strDummyVar=strDummyVarName,maxSize=strMaxSize,i='i')
            ctxtInput += templIn.format(pname=pname,strDummyVar=strDummyVarName,maxSize=strMaxSize,mallocErrorHandling='return -1;',i='i')
            outVDict[outExtraVar] = None 
            inVDict[inExtraVar] = None 

        ctxtInExtraVars = ''
        for k, val in inVDict.items():
            if k != '':
                ctxtInExtraVars += '\n'+k.format(strDummyVar=strDummyVarName,maxSize=strMaxSize,i='i')

        ctxtOutExtraVars = ''
        for k, val in outVDict.items():
            if k != '':
                ctxtOutExtraVars += '\n'+k.format(strDummyVar=strDummyVarName,maxSize=strMaxSize,i='i')


        # lets generate the inpout function
        cTxtInF = """// read the params from the stdin for the {vname} type
int HALvar_{varID}_input (void *pMyVar, char * szVarname) {{
    {varType} * {pVE} = ({varType} *)pMyVar;
    // some extra var declaration{ctxtInExtraVars}
    // the input code goes here
    printf("enter values for %s({vname}): ",szVarname);{cTxtInF}
    printf("enter process finished!\\n");
    return 0;
}}""".format(varID=varID,
             varType=strVarEleTyp,
             pVE='pEV',
             vname=vname,
             ctxtInExtraVars=self._genCCodeOrientation(ctxtInExtraVars.format(pEV='pEV'), 1),
             cTxtInF= self._genCCodeOrientation(ctxtInput.format(pEV='pEV'),1)
             )

        # lets generate the output function
        cTxtOutF = """// writes the params to the stdout for the {vname} type
void HALvar_{varID}_output (void *pMyVar, char * szVarname) {{
    {varType} * {pVE} = ({varType} *)pMyVar;
    // some extra var declaration{ctxtOutExtraVars}
    // the input code goes here
    printf("%s({vname}): ",szVarname);{cTxtOutF}
    printf("finished!\\n");
}}""".format(varID=varID,
             varType=strVarEleTyp,
             pVE='pEV',
             vname=vname,
             ctxtOutExtraVars=self._genCCodeOrientation(ctxtOutExtraVars.format(pEV='pEV'), 1),
             cTxtOutF= self._genCCodeOrientation(ctxtOutput.format(pEV='pEV'),1)
             )

        return '// genric I/O functions\n'+ cTxtInF + cTxtOutF
    
    def _genGenericVariablesMessageInterface (self):
        vL = self.db.HAL_VariableDefinition_getList()
        interfaceCode = ''
        inclL = [(None,'stdlib.h','',True),(None,'string.h','',True)]
        t = ''
        for v in vL:
            incl, code = self._genHALVarMsgScripts(v[1])
            t += code
            t += self._genGenericVariablesCmdLineIOInterface(v[1])
            if interfaceCode != '':
                interfaceCode += ','
            interfaceCode += '\n{{ {varID}, HALvar_{varID}_input, HALvar_{varID}_output}}'.format(varID=v[1])
        # let's generate some interface for the genric I/O functions
        t += """
// generic interface for the I/O functions
typedef struct SgenIOVariableInterface {
    int32_t varID;
    int (* pfktInput) (void * pMyVar, char * szVarname);
    void (* pfktOutput) (void * pMyVar, char * szVarname);
} TgenIOVariableInterface;
    
typedef struct SgenIOVariableInterfaceVector {
    const TgenIOVariableInterface * pFE;
    int const num;
} TgenIOVariableInterfaceVector;

// setup the vector
TgenIOVariableInterface const gVarInterfaceVector [] = {"""
        t += self._genCCodeOrientation(interfaceCode, 1)
        t += """
};

TgenIOVariableInterfaceVector const gVarInterface = {gVarInterfaceVector,sizeof(gVarInterfaceVector)/sizeof(TgenIOVariableInterface)}; 
"""
        return inclL, t


    def genRemoteInterface (self, drvUUID, trgtDir):
        r = self.genCode(None, drvUUID)
        if False == r[0]:
            print (r[1])
            return False
        # cast tuple values to the vars
        r, header, cfile, libList = r
        f = open(os.path.join(os.getcwd(),trgtDir,self.HALskeletonHeaderFilename + '.h'), "w+b")
        f.write(header)
        f.close()

        f = open(os.path.join(os.getcwd(),trgtDir,self.HALskeletonCFileFilename + '.c'), "w+b")
        f.write(cfile)
        f.close()
        return True
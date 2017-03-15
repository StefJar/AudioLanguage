'''
Created on 18.01.2011

@author: stj
'''
import sqlite3
import APDBxml
import codeGen
import APlogger

class APDB(object):
    # some id defines
    dFuncClass_basicIOtype = 1
    dFuncClass_refVar      = 2
    dFuncClass_refDataVar  = 3
    dFuncClass_VarID       = 4
    dFuncClass_VarIndex    = 5
        
    dFuncParamsClasses = {
        dFuncClass_basicIOtype :   'basic io type',
        dFuncClass_refVar      :   'reference to variable',
        dFuncClass_refDataVar  :   'reference to the data of a variable',
        dFuncClass_VarID       :   'variable ID',
        dFuncClass_VarIndex    :   'variable index'
    }
    
    def getConstMsgProcActionID (self,index):
        return self.constMsgProcActionsList[index][0]
    
    
    def __init__(self,dbCreateFile,dbInitXMLFile):
        log = APlogger.getDBLogger()
        log.info ("try to open AP.db ...")
        self.con = sqlite3.connect('AP.db')
        log.info ("check database ...")
        try:
            self.con.executescript('SELECT NULL FROM HAL_basicIOTypes')
        except sqlite3.Error as e:
            log.info ("database is not ready ")
            log.info ("try to create database tables")
            log.info ("open db creation file...")
            file = open(dbCreateFile, 'r')
            text = file.read()
            file.close()
            log.info ( "execute creation script...")
            self.con.executescript(text)
            log.info ("populate the database...")
            #self.fillStdData()
            #self.HAL_Skeleton_create()
            xml = APDBxml.APDBxml(self)
            xml.XMLFileToDB(dbInitXMLFile)
            log.info ("finished!")
        log.info ('database is ready!')
        log.info ('backup database to dbDump.xml ...')
        xml = APDBxml.APDBxml(self)
        xml.dumpToXMLFile('dbDump.xml')
        log.info ('backup finished!')
        
                
    def generic_getList (self, table, sortTableName = None):
        cur = self.con.cursor()
        if None == sortTableName:
            cur.execute('SELECT * FROM '+table)
        else:
            cur.execute('SELECT * FROM '+table + ' ORDER BY '+sortTableName+' ASC')
        return cur.fetchall()
        
    def generic_get (self, table, uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT * FROM '+table+' WHERE id'+table+' = ?',t)
        return cur.fetchone()

    def generic_getBy2criteria (self, table, crit1Name, crit1Value, crit2Name, crit2Value,):
        cur = self.con.cursor()
        t = (crit1Value, crit2Value)
        cur.execute('SELECT * FROM '+table+' WHERE '+crit1Name+' = ? AND '+crit2Name+'= ?',t)
        return cur.fetchone()


    def generic_delete (self, table, uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('DELETE FROM '+table+' WHERE id'+table+' = ?',t)
        self.con.commit()
        
    def generic_getByValue (self, table, fieldName, value):
        cur = self.con.cursor()
        t = (value,)
        cur.execute('SELECT * FROM '+table+' WHERE '+fieldName+' = ?',t)
        return cur.fetchall()

    def generic_getSingleByValue (self, table, fieldName, value):
        cur = self.con.cursor()
        t = (value,)
        cur.execute('SELECT * FROM '+table+' WHERE '+fieldName+' = ?',t)
        return cur.fetchone()
        

    # HAL_basicIOTypes table
    def HAL_basicIOTypes_getList (self):
        return self.generic_getList('HAL_basicIOTypes','TypeID')

    # HAL_basicIOTypes table
    def HAL_basicIOTypes_getByTypeID (self, tid):
        return self.generic_getSingleByValue('HAL_basicIOTypes','TypeID', tid)


        
    def HAL_basicIOType_del (self, uuid):
        t = (uuid,)
        cur = self.con.cursor()
        cur.execute('DELETE FROM HAL_basicIOTypes WHERE idHAL_IOTypesDefinition=?',t)
        cur.close()
        self.con.commit()
    
    def HAL_basicIOType_add (self,TypeID, TypeName, description, cType, endianType, sizeInBytes):
        cur = self.con.cursor()
        t = (TypeID,)
        cur.execute('SELECT idHAL_IOTypesDefinition FROM HAL_basicIOTypes WHERE TypeID=?',t)
        row = cur.fetchone()
        if None != row:
            return (False, 'type with id already exists',row[0])
        t = (TypeID, TypeName, description, cType, endianType, sizeInBytes)
        cur.execute('INSERT INTO HAL_basicIOTypes (TypeID, TypeName, description, cType, endianType, sizeInBytes) VALUES(?,?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_IOTypesDefinition) FROM HAL_basicIOTypes')
        return (True, None ,cur.fetchone())
    
    def HAL_basicIOType_update(self,uuid,TypeID, TypeName, description, cType, endianType, sizeInBytes):
        cur = self.con.cursor()
        t = (TypeID, TypeName, description, cType, endianType, sizeInBytes,uuid)
        cur.execute('UPDATE HAL_basicIOTypes SET TypeID=?, TypeName=?, description=?, cType=?, endianType=?, sizeInBytes=? WHERE idHAL_IOTypesDefinition=?',t)
        cur.close()
        self.con.commit()

    def HAL_basicIOType_getTypeNameByID (self,uuid):
        t = (uuid,)
        cur = self.con.cursor()
        cur.execute('SELECT TypeName FROM HAL_basicIOTypes WHERE idHAL_IOTypesDefinition=?',t)
        res = cur.fetchone()
        if res != None:
            return res[0]
        else :
            return ""

    def HAL_basicIOType_getNameByTypeID (self,TypeID):
        t = (TypeID,)
        cur = self.con.cursor()
        cur.execute('SELECT TypeName FROM HAL_basicIOTypes WHERE TypeID=?',t)
        res = cur.fetchone()
        if res != None:
            return res[0]
        else :
            return ""

    def HAL_basicIOType_getCTypeNameByTypeID (self,TypeID):
        t = (TypeID,)
        cur = self.con.cursor()
        cur.execute('SELECT cType FROM HAL_basicIOTypes WHERE TypeID=?',t)
        res = cur.fetchone()
        if res != None:
            return res[0]
        else :
            return ""
    
    # HAL_VariableDefinition table
    def HAL_VariableDefinition_getList (self):
        return self.generic_getList('HAL_VariableDefinition','VariableID')
    
    def HAL_VariableDefinition_get (self, uuid):
        return self.generic_get('HAL_VariableDefinition',uuid)
    
    def HAL_VariableDefinition_getByVariableID (self, VariableID):
        t = (VariableID,)
        cur = self.con.cursor()
        cur.execute('SELECT * FROM HAL_VariableDefinition WHERE VariableID=?',t)
        return (cur.fetchone(), self.HAL_VariableDefinition_getParamList(VariableID))
        
    def HAL_VariableDefinition_getByName (self, name):
        return self.generic_getSingleByValue ('HAL_VariableDefinition', 'varName', name)
        
    def HAL_VariableDefinition_del (self, uuid):
        t = (uuid,)
        v = self.HAL_VariableDefinition_get(uuid)
        varID =v[1]
        cur = self.con.cursor()
        # delete all parameters
        cur.execute('DELETE FROM HAL_VariableIOParameter WHERE VariableID=?',(varID,))
        # delete variable definition
        cur.execute('DELETE FROM HAL_VariableDefinition WHERE idHAL_VariableDefinition=?',t)
        cur.close()
        self.con.commit()
    
    def HAL_VariableDefinition_add (self,VariableID, varName, description):
        cur = self.con.cursor()
        t = (VariableID,)
        cur.execute('SELECT idHAL_VariableDefinition FROM HAL_VariableDefinition WHERE VariableID=?',t)
        row = cur.fetchone()
        if None != row:
            return (False, 'type with id already exists',row[0])
        t = (VariableID, varName, description)
        cur.execute('INSERT INTO HAL_VariableDefinition (VariableID, varName, description) VALUES(?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_VariableDefinition) FROM HAL_VariableDefinition')
        return (True, '',cur.fetchone())
    
    def HAL_VariableDefinition_update(self,uuid,VariableID, varName, description):
        cur = self.con.cursor()
        t = (VariableID, varName, description,uuid)
        cur.execute('UPDATE HAL_VariableDefinition SET VariableID=?, varName=?, description=? WHERE idHAL_VariableDefinition=?',t)
        cur.close()
        self.con.commit()

    def HAL_VariableDefinition_delParam (self, paramUUID):
        t = (paramUUID,)
        cur = self.con.cursor()
        cur.execute('DELETE FROM HAL_VariableIOParameter WHERE idHAL_VariableIOParameter=?',t)
        cur.close()
        self.con.commit()
                                                                                                                          
    def HAL_VariableDefinition_addParam (self, basicTypeID, VariableID, name, description, isArray):
        cur = self.con.cursor()
        t = (basicTypeID,name)
        cur.execute('SELECT idHAL_VariableIOParameter FROM HAL_VariableIOParameter WHERE basicTypeID=? AND name=?',t)
        row = cur.fetchone()
        if None != row:
            return (False, 'parameter with that name already exists',row[0])
        t = (basicTypeID, VariableID, name, description, isArray)
        cur.execute('INSERT INTO HAL_VariableIOParameter (basicTypeID, VariableID, name, description, isArray) VALUES(?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_VariableIOParameter) FROM HAL_VariableIOParameter')
        return (True, '',cur.fetchone())
    
    def HAL_VariableDefinition_updateParam(self,paramUUID, basicTypeID, VariableID, name, description, isArray):
        cur = self.con.cursor()
        t = (basicTypeID, VariableID, name, description, isArray, paramUUID)
        cur.execute('UPDATE HAL_VariableIOParameter SET basicTypeID=?, VariableID=?, name=?, description=?, isArray=? WHERE idHAL_VariableIOParameter=?',t)
        cur.close()
        self.con.commit()

    def HAL_VariableDefinition_getParamList (self,VariableID):
        cur = self.con.cursor()
        t = (VariableID,)
        cur.execute('SELECT * FROM HAL_VariableIOParameter WHERE VariableID=?',t)
        return cur.fetchall()
    
    def Code_createCode (self,text):
        cur = self.con.cursor()
        t = (text,)
        cur.execute('INSERT INTO Code (idCode, code) VALUES(NULL,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idCode) FROM Code')
        res = cur.fetchone()
        cur.close()
        if res != None:
            return res[0]
        else :
            return None
           
    def Code_updateCode (self,uuid,text):
        cur = self.con.cursor()
        t = (unicode(text),uuid)
        cur.execute('UPDATE Code SET code=? WHERE idCode=?',t)
        self.con.commit()
        cur.close()
        
    def Code_deleteCode (self,uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT idIncludes FROM IncludeList WHERE idCode=?',t)
        resL = cur.fetchall()
        cur.executemany('DELETE FROM Includes  WHERE idIncludes=?',resL)
        cur.execute('DELETE FROM IncludeList WHERE idCode=?',t)
        self.con.commit()
        cur.close()
    
    def Code_getCode (self,uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT code FROM Code WHERE idCode=?',t)
        r = cur.fetchone()
        if r != None:
            return r[0]
        else:
            return None
    
    def Code_createInclude (self,uuid,includeFile, includeLib, syslib):
        cur = self.con.cursor()
        t = (uuid,includeFile,includeLib)
        cur.execute('SELECT i.idIncludes FROM IncludeList l JOIN Includes i ON l.idIncludes = i.idIncludes WHERE l.idCode=? AND (i.includefile=? AND i.lib=?)',t)
        res = cur.fetchone()
        if res != None:
            return (False,'include file or library still exists',res[0])
        t = (includeFile,includeLib,syslib)
        cur.execute('INSERT INTO Includes (includefile, lib, syslib) VALUES(?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idIncludes) FROM Includes')
        idInclude = cur.fetchone()[0]
        t=(uuid,idInclude)
        cur.execute('INSERT INTO IncludeList (idCode, idIncludes) VALUES(?,?)',t)
        self.con.commit()
        cur.close()
        return (True,None,idInclude)
    
    def Code_updateInclude (self,uuid,idIncludes,includeFile, includeLib, syslib):
        cur = self.con.cursor()
        t = (uuid,idIncludes,includeFile,includeLib)
        cur.execute('SELECT i.idIncludes FROM IncludeList l JOIN Includes i ON l.idIncludes = i.idIncludes WHERE l.idCode=? AND l.idIncludes!=? AND (i.includefile=? OR i.lib=?)',t)
        res = cur.fetchone()
        if res != None:
            return (False,res[0])
        t = (includeFile,includeLib,syslib,idIncludes)
        cur.execute('UPDATE Includes SET includefile=?, lib=?, syslib=? WHERE idIncludes=?',t)
        self.con.commit()
        cur.close()
        return (True,None)
    
    def Code_deleteInclude (self,uuid,idIncludes):
        cur = self.con.cursor()
        t = (uuid,idIncludes)
        cur.execute('DELETE FROM IncludeList WHERE idCode=? AND idIncludes=?',t)
        t = (idIncludes,)
        cur.execute('DELETE FROM Includes  WHERE idIncludes=?',t)
        self.con.commit()
        cur.close()
        
    def Code_getIncludes (self,uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT i.* FROM IncludeList l JOIN Includes i ON l.idIncludes = i.idIncludes WHERE l.idCode=?',t)        
        return cur.fetchall()

    def Code_getIncludesWithoutUUID (self,uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT i.includefile, i.lib, i.syslib FROM IncludeList l JOIN Includes i ON l.idIncludes = i.idIncludes WHERE l.idCode=?',t)        
        return cur.fetchall()

        
    def HAL_DefFunctions_getList (self):
        return self.generic_getList('HAL_Function','fid')

    def HAL_DefFunctions_get (self,uuid):
        return self.generic_get('HAL_Function', uuid)

    def HAL_DefFunctions_getByName (self,name):
        return self.generic_getSingleByValue ('HAL_Function', 'name', name)

    
    def HAL_DefFunctions_getFromFunctionID (self,fid):
        cur = self.con.cursor()
        t = (fid,)
        cur.execute('SELECT * FROM HAL_Function WHERE fid=?',t)
        return cur.fetchone()
    
    def HAL_DefFunction_getMaxParameterSize (self):
        cur = self.con.cursor()
        cur.execute('SELECT fid FROM HAL_Function')
        fl = cur.fetchall()
        res = 0
        for f in fl:
            cur.execute('SELECT COUNT(*) FROM HAL_FunctionsParameter WHERE functionID=?',f)
            amount = cur.fetchone()[0]
            if amount > res :
                res = amount
        return res
    
    def HAL_DefFunctions_add (self,fid,name,descr):
        cur = self.con.cursor()
        t = (fid,)
        cur.execute('SELECT idHAL_Function FROM HAL_Function WHERE fid=?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'function with the id still exists',f[0])
        t = (fid,name,descr)
        cur.execute('INSERT INTO HAL_Function (fid, name, descr) VALUES(?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_Function) FROM HAL_Function')
        return (True,None,cur.fetchone())
    
    def HAL_DefFunctions_update (self,uuid,fid,name,descr):
        cur = self.con.cursor()
        t = (fid,uuid)
        cur.execute('SELECT idHAL_Function FROM HAL_Function WHERE fid=? AND idHAL_Function!=?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'function with the id still exists')
        t = (fid,name,descr,uuid)
        cur.execute('UPDATE HAL_Function SET fid=?, name=?, descr=? WHERE idHAL_Function==?',t)
        self.con.commit()
        return (True,None, uuid)

    def HAL_DefFunctions_delete (self,uuid):
        cur = self.con.cursor()
        # get fid
        f = self.HAL_DefFunctions_get(uuid)
        if f != None:
            t=(f[1],)
            cur.execute('DELETE FROM HAL_FunctionsParameter WHERE fid=?',t)
            
        t = (uuid,)
        cur.execute('DELETE FROM HAL_Function WHERE idHAL_Function=?',t)
        self.con.commit()

    def HAL_DefFunctions_addParam (self, fid, name, descr, idParameterClass, idParameterType):
        cur = self.con.cursor()
        t = (fid,name)
        cur.execute('SELECT idHAL_FunctionsParameter FROM HAL_FunctionsParameter WHERE fid=? and name=?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'parameter with the name still exists',f[0])
        t = (fid, name, descr, idParameterClass, idParameterType)
        if None == idParameterType: idParameterType = 0;
        cur.execute('INSERT INTO HAL_FunctionsParameter (fid, name, descr, idParameterClass, idParameterType) VALUES(?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_FunctionsParameter) FROM HAL_FunctionsParameter')
        return (True,None,cur.fetchone())
   
    def HAL_DefFunctions_updateParam (self,uuid, fid, name, descr, idParameterClass, idParameterType):
        cur = self.con.cursor()
        t = (fid,name,uuid)
        cur.execute('SELECT idHAL_FunctionsParameter FROM HAL_FunctionsParameter WHERE fid=? and name=? and idHAL_FunctionsParameter!=?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'parameter with the name still exists')
        if None == idParameterType: idParameterType = 0;
        t = (fid, name, descr, idParameterClass, idParameterType ,uuid)
        cur.execute('UPDATE HAL_FunctionsParameter SET fid=?, name=?, descr=?, idParameterClass=?, idParameterType=?  WHERE idHAL_FunctionsParameter=?',t)
        self.con.commit()
        return (True,None)

    def HAL_DefFunctions_deleteParam (self,uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('DELETE FROM HAL_FunctionsParameter WHERE idHAL_FunctionsParameter=?',t)
        self.con.commit()

    def HAL_DefFunctions_getParamList (self,fid):
        cur = self.con.cursor()
        t = (fid,)
        cur.execute('SELECT * FROM HAL_FunctionsParameter WHERE fid=?',t)
        return cur.fetchall()

    def HAL_DefFunctions_maxParamCount (self):
        halFL = self.HAL_DefFunctions_getList()
        maxParams = 0
        for halF in halFL:
            pL = self.HAL_DefFunctions_getParamList(halF[1])
            PC = len(pL)
            if PC > maxParams:
                maxParams = PC
        return maxParams

    def HAL_Msg_Type_getList (self):
        return self.generic_getList('HAL_MessageType','msgID')

    def HAL_Msg_Type_getFromMsgID (self, msgID):
        cur = self.con.cursor()
        t = (msgID,)
        cur.execute('SELECT * FROM HAL_MessageType WHERE msgID=?',t)
        return cur.fetchone()
    
    def HAL_Msg_Type_add (self, msgID, name, descr ):
        cur = self.con.cursor()
        t = (msgID,)
        cur.execute('SELECT idHAL_MessageType FROM HAL_MessageType WHERE msgID=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'message with the id still exists',m[0])
        t = (msgID, name, descr)
        cur.execute('INSERT INTO HAL_MessageType (msgID, name, descr) VALUES(?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_MessageType) FROM HAL_MessageType')
        return (True,None,cur.fetchone())

    def HAL_Msg_Type_change (self, uuid, msgID, name, descr ):
        cur = self.con.cursor()
        t = (msgID,uuid)
        cur.execute('SELECT idHAL_MessageType FROM HAL_MessageType WHERE msgID=? AND idHAL_MessageType!=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'message with the id still exists',m[0])
        t = (msgID, name, descr, uuid)
        cur.execute('UPDATE HAL_MessageType SET msgID=?, name=?, descr=? WHERE idHAL_MessageType=?',t)
        self.con.commit()
        return (True,None,uuid)

    def HAL_Msg_Type_delete (self, uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('SELECT msgID FROM HAL_MessageType WHERE idHAL_MessageType!=?',t)
        m = cur.fetchone()
        cur.execute('DELETE FROM HAL_MessageType WHERE idHAL_MessageType!=?',t)
        t = (m[1],) #msg id
        cur.execute('DELETE FROM HAL_MessageParameter WHERE msgID=?',t)
        self.con.commit()

    def HAL_msg_TypeParam_getList (self,msgID):
        cur = self.con.cursor()
        t =(msgID,)
        cur.execute('SELECT * FROM HAL_MessageParameter WHERE msgID=? ORDER BY positionIndex ASC',t)
        return cur.fetchall()

    def HAL_msg_TypeParam_addParam (self, msgID, positionIndex, name, descr, basicTypeID, isArray):
        cur = self.con.cursor()
        t = (msgID,positionIndex)
        cur.execute('SELECT idHAL_MessageParameter FROM HAL_MessageParameter WHERE msgID=? AND positionIndex=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'message parameter on the same position index still exists',m[0])
        t = (msgID, positionIndex, name, descr, basicTypeID, isArray)
        cur.execute('INSERT INTO HAL_MessageParameter (msgID, positionIndex, name, descr, basicTypeID, isArray) VALUES(?,?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_MessageParameter) FROM HAL_MessageParameter')
        return (True,None,cur.fetchone())

    def HAL_msg_TypeParam_changeParam (self, uuid, msgID, positionIndex, name, descr, basicTypeID, isArray):
        cur = self.con.cursor()
        t = (msgID,positionIndex,uuid)
        cur.execute('SELECT idHAL_MessageParameter FROM HAL_MessageParameter WHERE msgID=? AND positionIndex=? AND idHAL_MessageParameter!=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'message parameter on the same position index still exists',m[0])
        t = (msgID, positionIndex, name, descr, basicTypeID, isArray, uuid)
        cur.execute('UPDATE HAL_MessageParameter SET msgID=?, positionIndex=?, name=?, descr=?, basicTypeID=?, isArray=? WHERE idHAL_MessageParameter=?',t)
        self.con.commit()
        return (True,None,uuid)

    def HAL_msg_TypeParam_deleteParam (self, uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('DELETE FROM HAL_MessageParameter WHERE idHAL_MessageParameter=?',t)
        self.con.commit()

    def HAL_msg_Process_getList (self):
        return self.generic_getList('HAL_MessageProcess','msgProcID')
        
    def HAL_msg_Process_add (self, msgProcID, name, descr, isRX, msgCode):
        cur = self.con.cursor()
        if isRX == True :
            t = (msgProcID,)
            cur.execute('SELECT idHAL_MessageProcess FROM HAL_MessageProcess WHERE msgProcID=?',t)
            m = cur.fetchone()
            if None != m:
                return (False,'message process with the same id still exists',m[0])
        else:
            msgProcID = 0
            
        t = (msgProcID, name, descr, isRX, msgCode)
        cur.execute('INSERT INTO HAL_MessageProcess (msgProcID, name, descr, isRX, msgCode) VALUES(?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idHAL_MessageProcess) FROM HAL_MessageProcess')
        return (True,None,cur.fetchone())

    def HAL_msg_Process_change (self,uuid, msgProcID, name, descr, isRX, msgCode):
        cur = self.con.cursor()
        if isRX == True :
            t = (msgProcID,uuid)
            cur.execute('SELECT idHAL_MessageProcess FROM HAL_MessageProcess WHERE msgProcID=? AND idHAL_MessageProcess!=?',t)
            m = cur.fetchone()
            if None != m:
                return (False,'message process with the same id still exists',m[0])
        else:
            msgProcID = 0

        t = (msgProcID, name, descr, isRX, msgCode, uuid)
        cur.execute('UPDATE HAL_MessageProcess SET msgProcID=?, name=?, descr=?, isRX=?, msgCode=? WHERE idHAL_MessageProcess=?',t)
        self.con.commit()
        return (True,None,uuid)

    def HAL_msg_Process_delete (self, uuid):
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute('DELETE FROM HAL_MessageProcess WHERE idHAL_MessageProcess=?',t)
        self.con.commit()

    def Comp_Compiler_getList(self):
        return self.generic_getList('Compiler')

    def Comp_Compiler_get (self, uuid):
        return self.generic_get('Compiler', uuid)


    def Comp_Compiler_add(self, name, description, OperatingSystem, CC, CXX, ASM, AR, LINK, CCFLAGS, OBJSUFFIX, CCCOM, CXXCOM, CXXFLAGS, LINKCOM, LINKFLAGS):
        cur = self.con.cursor()
        t = (name, description, OperatingSystem, CC, CXX, ASM, AR, LINK, CCFLAGS, OBJSUFFIX, CCCOM, CXXCOM, CXXFLAGS, LINKCOM, LINKFLAGS)
        cur.execute('INSERT INTO Compiler (name, description, OperatingSystem, CC, CXX, ASM, AR, LINK, CCFLAGS, OBJSUFFIX, CCCOM, CXXCOM, CXXFLAGS, LINKCOM, LINKFLAGS) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idCompiler) FROM Compiler')
        return (True,None,cur.fetchone())

    def Comp_Compiler_update(self,uuid, name, description, OperatingSystem, CC, CXX, ASM, AR, LINK, CCFLAGS, OBJSUFFIX, CCCOM, CXXCOM, CXXFLAGS, LINKCOM, LINKFLAGS):
        cur = self.con.cursor()
        t = (name, description, OperatingSystem, CC, CXX, ASM, AR, LINK, CCFLAGS, OBJSUFFIX, CCCOM, CXXCOM, CXXFLAGS, LINKCOM, LINKFLAGS, uuid)
        cur.execute('UPDATE Compiler SET name=?, description=?, OperatingSystem=?, CC=?, CXX=?, ASM=?, AR=?, LINK=?, CCFLAGS=?, OBJSUFFIX=?, CCCOM=?, CXXCOM=?, CXXFLAGS=?, LINKCOM=?, LINKFLAGS=? WHERE idCompiler=?',t)
        self.con.commit()
        return (True,None,uuid)

    def Comp_Compiler_delete (self, uuid):
        cur = self.con.cursor()
        t = (0,uuid)
        cur.execute('UPDATE AP SET idCompiler=? WHERE idCompiler=?',t)
        t = (uuid,)
        cur.execute('DELETE FROM CompilerLib WHERE idCompiler=?',t)
        cur.execute('DELETE FROM CompillerLibPath WHERE idCompiler=?',t)
        cur.execute('DELETE FROM CompilerIncludePath WHERE idCompiler=?',t)
        cur.execute('DELETE FROM Compiler WHERE idCompiler=?',t)
        self.con.commit()

    def Comp_CompilerXXX_getList(self, table, idCompiler):
        cur = self.con.cursor()
        t = (idCompiler,)
        cur.execute('SELECT * FROM '+table+' WHERE idCompiler=?',t)
        return cur.fetchall()

    def Comp_CompilerXXX_add(self, table, uuidName, tableField, idCompiler, value):
        cur = self.con.cursor()
        t = (idCompiler, value)
        cur.execute('SELECT '+uuidName+' FROM '+table+' WHERE idCompiler=? AND '+tableField+'=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'entry still exists',m[0])
        t = (idCompiler, value)
        cur.execute('INSERT INTO '+table+' (idCompiler,'+tableField+') VALUES(?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX('+uuidName+') FROM '+table)
        return (True,None,cur.fetchone())

    def Comp_CompilerXXX_update(self, table, uuidName, tableField, uuid, idCompiler, value):
        cur = self.con.cursor()
        t = (idCompiler,value, uuid)
        cur.execute('SELECT '+uuidName+' FROM '+table+' WHERE idCompiler=? AND '+tableField+'=? AND '+uuidName+'!=?',t)
        m = cur.fetchone()
        if None != m:
            return (False,'entry still exists',m[0])
        t = ( value, uuid)
        cur.execute('UPDATE '+table+' SET '+tableField+'=? WHERE '+uuidName+'=?',t)
        self.con.commit()
        return (True,None,uuid)

    def Comp_CompilerXXX_delete(self, table, uuidName, uuid):
        cur = self.con.cursor()
        t=(uuid,)
        cur.execute('DELETE FROM '+table+' WHERE '+uuidName+'=?',t)
        self.con.commit()

    def Comp_CompilerLib_getList (self, idCompiler):
        return self.Comp_CompilerXXX_getList('CompilerLib',idCompiler)

    def Comp_CompilerLib_add (self, idCompiler, lib):
        return self.Comp_CompilerXXX_add('CompilerLib','idCompilerLib','lib', idCompiler, lib)
    
    def Comp_CompilerLib_update (self, uuid, idCompiler, lib):
        return self.Comp_CompilerXXX_update('CompilerLib','idCompilerLib','lib', uuid, idCompiler, lib)

    def Comp_CompilerLib_delete (self, uuid):
        return self.Comp_CompilerXXX_delete('CompilerLib','idCompilerLib', uuid)

    def Comp_CompilerLibPath_getList (self, idCompiler):
        return self.Comp_CompilerXXX_getList('CompilerLibPath',idCompiler)

    def Comp_CompilerLibPath_add (self, idCompiler, path):
        return self.Comp_CompilerXXX_add('CompilerLibPath','idCompilerLibPath','path', idCompiler, path)
    
    def Comp_CompilerLibPath_update (self, uuid, idCompiler, path):
        return self.Comp_CompilerXXX_update('CompilerLibPath','idCompilerLibPath','path', uuid, idCompiler, path)

    def Comp_CompilerLibPath_delete (self, uuid):
        return self.Comp_CompilerXXX_delete('CompilerLibPath','idCompilerLibPath', uuid)

    def Comp_CompilerIncludePath_getList (self, idCompiler):
        return self.Comp_CompilerXXX_getList('CompilerIncludePath',idCompiler)

    def Comp_CompilerIncludePath_add (self, idCompiler, path):
        return self.Comp_CompilerXXX_add('CompilerIncludePath','idCompilerIncludePath','path', idCompiler, path)
    
    def Comp_CompilerIncludePath_update (self, uuid, idCompiler, path):
        return self.Comp_CompilerXXX_update('CompilerIncludePath','idCompilerIncludePath','path', uuid, idCompiler, path)

    def Comp_CompilerIncludePath_delete (self, uuid):
        return self.Comp_CompilerXXX_delete('CompilerIncludePath','idCompilerIncludePath', uuid)

    def Impl_add (self, table, code, descr, idFieldName, id, idImplGroup):
        idCode = self.Code_createCode(code)
        cur = self.con.cursor()
        if None == idFieldName:
            t = (idCode, descr, idImplGroup)
            cur.execute ('INSERT INTO '+table+' (idCode, descr, idImplGroup) VALUES(?,?,?)',t)
        else:
            t = (idCode, descr, id, idImplGroup)
            cur.execute ('INSERT INTO '+table+' (idCode, descr, '+idFieldName+',idImplGroup) VALUES(?,?,?,?)',t)
            
        self.con.commit()
        cur.execute('SELECT MAX(id'+table+') FROM '+table)
        return (True,None,cur.fetchone())
    
    def Impl_update (self, table, uuid, code, descr, idFieldName, id, touchCode, idImplGroup):
        if True == touchCode:
            oldF = self.generic_get(table, uuid)
            self.Code_updateCode(oldF[2], code)
            
        cur = self.con.cursor()
        
        if None == idFieldName:
            t = (descr, idImplGroup, uuid)
            cur.execute('UPDATE '+table+' SET descr=?, idImplGroup=? WHERE id'+table+'=?',t)
        else:
            t = (descr, idImplGroup, id, uuid)
            cur.execute('UPDATE '+table+' SET descr=?, idImplGroup=?, '+idFieldName+'=? WHERE id'+table+'=?',t)
        self.con.commit()

    def Impl_delete (self, table, uuid, APtable):
        oldF = self.generic_get(table, uuid)
        self.Code_deleteCode(oldF[2])
        t = (uuid,)
        cur = self.con.cursor()
        # delete old entries at the AP tables
        cur.execute('DELETE FROM '+APtable+' WHERE id'+table+'=?',t)
        self.con.commit()
        self.generic_delete(table, uuid)

    def Impl_Group_getList (self):
        res = self.generic_getList('ImplGroup','name')
        res.append((0,'no group',None))
        return res
    
    def Impl_Group_get (self, uuid):
        if (uuid == 0):
            return (0,'no group',None)
        return self.generic_get('ImplGroup', uuid)

    def Impl_Group_add (self, name, code):
        cur = self.con.cursor()
        t = (name,)
        cur.execute('SELECT * FROM ImplGroup WHERE name = ?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'group with the name still exists',f[0])

        idCode = self.Code_createCode(code)
        if (idCode == None):
            return (False,'creating code failed',None)
        t = (name,idCode)
        cur.execute('INSERT INTO ImplGroup (name, idCode) VALUES(?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idImplGroup) FROM ImplGroup')
        return (True,None,cur.fetchone())

    def Impl_Group_update (self, uuid, name, code):
        cur = self.con.cursor()
        t = (name, uuid)
        cur.execute('SELECT * FROM ImplGroup WHERE name=? AND idImplGroup!=?',t)
        f = cur.fetchone()
        if None != f:
            return (False,'group with the name still exists',f[0])
        if code != None:
            g = self.Impl_Group_get(uuid)
            self.Code_updateCode(g[2], code)
        cur.execute('UPDATE ImplGroup SET name=? WHERE idImplGroup=?',t)
        self.con.commit()
        return (True,None,(uuid,name))

    def Impl_Group_delete (self, uuid):
        cur = self.con.cursor()
        g = self.Impl_Group_get(uuid)
        self.Code_deleteCode(g[0])
        t = (0, uuid)
        cur.execute('UPDATE ImplHALFunction SET idImplGroup=? WHERE idImplGroup=?',t)
        cur.execute('UPDATE ImplHALVariable SET idImplGroup=? WHERE idImplGroup=?',t)
        cur.execute('UPDATE ImplMsgDriver SET idImplGroup=? WHERE idImplGroup=?',t)
        cur.execute('UPDATE ImplAP SET idImplGroup=? WHERE idImplGroup=?',t)
        self.generic_delete('ImplGroup',uuid)


    def Impl_HALFunction_getListSortByGroupAndFunctionID (self):
        cur = self.con.cursor()
        cur.execute('SELECT * FROM ImplHALFunction ORDER BY idImplGroup,fid ASC')
        return cur.fetchall()

    def Impl_HALFunction_get (self, uuid):
        return self.generic_get('ImplHALFunction', uuid)

    def Impl_HALFunction_add (self, fid, code, descr, idImplGroup):
        return self.Impl_add ('ImplHALFunction',code, descr, 'fid', fid, idImplGroup)
    
    def Impl_HALFunction_update (self, uuid, fid, code, descr, idImplGroup):
        return self.Impl_update(uuid, 'ImplHALFunction',code, descr, 'fid', fid, idImplGroup)

    def Impl_HALFunction_delete (self,uuid):
        return self.Impl_delete('ImplHALFunction', uuid)

    def Impl_HALVariables_getListSortByGroupAndVarID (self):
        cur = self.con.cursor()
        cur.execute('SELECT * FROM ImplHALVariable ORDER BY idImplGroup,VariableID ASC')
        return cur.fetchall()

    def Impl_HALVariable_get (self, uuid):
        return self.generic_get('ImplHALVariable', uuid)

    def Impl_HALVariable_add (self, VariableID, code, descr, idImplGroup):
        return self.Impl_add ('ImplHALVariable',code, descr, 'VariableID', VariableID, idImplGroup)
    
    def Impl_HALVariable_update (self, uuid, VariableID, code, descr, idImplGroup):
        return self.Impl_update(uuid, 'ImplHALVariable',code, descr, 'VariableID', VariableID, idImplGroup)

    def Impl_HALVariable_delete (self,uuid):
        return self.Impl_delete('ImplHALVariable', uuid)

    def Impl_ImplMsgDriver_getListSortedByGroup (self):
        return self.generic_getList('ImplMsgDriver', 'idImplGroup')

    def Impl_ImplMsgDriver_get (self, uuid):
        return self.generic_get('ImplMsgDriver', uuid)

    def Impl_ImplMsgDriver_add (self, code, descr, idImplGroup):
        return self.Impl_add ('ImplMsgDriver',code, descr, None, None, idImplGroup)
    
    def Impl_ImplMsgDriver_update (self, uuid, code, descr, idImplGroup):
        return self.Impl_update(uuid,'ImplMsgDriver', code, descr, None, None, idImplGroup)

    def Impl_ImplMsgDriver_delete (self,uuid):
        return self.Impl_delete('ImplMsgDriver', uuid)

    def Impl_ImplAP_getListSortedByGroup (self):
        return self.generic_getList('ImplAP', 'idImplGroup')

    def Impl_ImplAP_get (self, uuid):
        return self.generic_get('ImplAP', uuid)

    def Impl_ImplAP_add (self, code, descr, idImplGroup):
        return self.Impl_add('ImplAP', code, descr, None, None, idImplGroup)
    
    def Impl_ImplAP_update (self, uuid, code, descr, idImplGroup):
        return self.Impl_update('ImplAP', uuid, code, descr, None, None, idImplGroup)

    def Impl_ImplAP_delete (self,uuid):
        return self.Impl_delete('ImplAP', uuid)



    def AP_implTable_getList (self, APTable, idAP):
        return self.generic_getByValue(APTable, 'idAP', idAP)
        
    def AP_implTable_get (self, APTable, idAP, uuid):
        return self.generic_getBy2criteria(APTable, 'idAP', idAP, 'id'+APTable, uuid)
        
    def AP_implTable_checkFunctionExistance (self, APTable, implTable , idAP, idImpl):
        el = []
        ll = self.AP_implTable_getList(APTable ,idAP)
        for l in ll:
            d = self.generic_get(implTable,l[2])
            if d[1] == idImpl :
                el.append(d)
        return el
        
    def AP_implTable_add (self, APTable, implTable , idAP, uuidImp):
        impl = self.generic_get(implTable, uuidImp)
        if (None == impl):
            return (False,'implementation don\'t exists',None)
        el = self.AP_implTable_checkFunctionExistance( APTable, implTable, idAP , impl[1])
        if (len(el) > 0) :
            return (False,'implementation still exists',None)

        t = (idAP, uuidImp)
        cur = self.con.cursor()
        cur.execute ('INSERT INTO '+APTable+' (idAP, id'+implTable+') VALUES(?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(id'+APTable+') FROM '+APTable)
        return (True,None,cur.fetchone())

    def AP_implTable_deleteImplRef (self, APTable, implTable, idAP, refUUID):
        cur = self.con.cursor()
        t = (idAP, refUUID)
        cur.execute ('DELETE FROM '+APTable+' WHERE idAP =? AND id'+implTable+'=?',t)
        self.con.commit()

    def AP_implTable_deleteAP (self, APTable, idAP):
        cur = self.con.cursor()
        t = (idAP,)
        cur.execute ('DELETE FROM '+APTable+' WHERE idAP=?',t)
        self.con.commit()

    def AP_getList (self):
        return self.generic_getList('AP', 'name')
    
    def AP_get (self, uuid):
        return self.generic_get('AP', uuid)
        
    def AP_add (self, name, descr, idCompiler):
        if (None == idCompiler) :
            idCompiler = -1
        # set startup code to default 
        idStartupCode = -1
        
        t = (name, descr, idCompiler, idStartupCode)
        
        cur = self.con.cursor()
        cur.execute ('INSERT INTO AP (name, descr, idCompiler, idCodeStartup) VALUES(?,?,?,?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idAP) FROM AP')
        return (True,None,cur.fetchone())

    def AP_change (self, uuid, name, descr, idCompiler):
        if (None == idCompiler) :
            idCompiler = -1
        
        t = (name, idCompiler, descr, uuid)
        cur = self.con.cursor()
        cur.execute ('UPDATE AP SET name=?, idCompiler=?, descr=? WHERE idAP=?',t)
        self.con.commit()
        return (True,'', uuid)
    
    def AP_setStartupCode (self,uuid, idStartupCode):
        t = (idStartupCode, uuid)
        cur = self.con.cursor()
        cur.execute ('UPDATE AP SET idCodeStartup=? WHERE idAP=?',t)
        self.con.commit()
        

    def AP_delete (self, uuid):
        self.AP_implTable_deleteAP ('FunctionList',uuid)
        self.AP_implTable_deleteAP ('VariableList',uuid)
        self.AP_implTable_deleteAP ('DriverList',uuid)
        self.AP_implTable_deleteAP ('APList',uuid)
        cur = self.con.cursor()
        t = (uuid,)
        cur.execute ('DELETE FROM AP WHERE idAP=?',t)
        self.con.commit()

    def AP_getGroups (self, uuid):
        dGL = self.Impl_Group_getList()
        GL = {}
        GL[0] = [False,(0,'no group', 0)]
        for g in dGL:
            GL[g[0]] = [False, g]
        # match
        
        # functions 
        L = self.AP_implTable_getList ('FunctionList', uuid)
        for e in L:
            impl = self.Impl_HALFunction_get(e[2])
            if impl != None: 
                GL[impl[4]][0] = True
        # variables
        L = self.AP_implTable_getList ('VariableList', uuid)
        for e in L:
            impl = self.Impl_HALVariable_get(e[2])
            if impl != None: 
                GL[impl[4]][0] = True

        # msg driver
        L = self.AP_implTable_getList ('DriverList', uuid)
        for e in L:
            impl = self.Impl_ImplMsgDriver_get(e[2])
            if impl != None: 
                GL[impl[3]][0] = True
        # ap blue print
        L = self.AP_implTable_getList ('APList', uuid)
        for e in L:
            impl = self.Impl_ImplAP_get(e[2])
            if impl != None: 
                GL[impl[3]][0] = True
        # build list
        dGL = []
        for k,v in GL.items():
            if v[0] == True : dGL.append(v[1])
        return dGL
        
    # ==================================
    # db functions for test pattern  
    # ==================================
    
    def ALASMprg_getList (self):
        return self.generic_getList('ALASMprogramm')
    
    def ALASMprg_get (self, uuid):
        return self.generic_get('ALASMprogramm', uuid)
    
    def ALASMprg_create (self, text):
        cur = self.con.cursor()
        t = (text,)
        cur.execute ('INSERT INTO ALASMprogramm (code) VALUES(?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idALASMprogramm) FROM ALASMprogramm')
        return (True,None,cur.fetchone())
    
    def ALASMprg_update (self,uuid ,text):
        cur = self.con.cursor()
        t = (text, uuid)
        cur.execute ('UPDATE ALASMprogramm SET code=? WHERE idALASMprogramm=?',t)
        self.con.commit()    
    
    def ALASMprg_delete (self,uuid):
        return self.generic_delete('ALASMprogramm',uuid)


    def MatlabPrg_getList (self):
        return self.generic_getList('MatlabProgramm')
    
    def MatlabPrg_get (self, uuid):
        return self.generic_get('MatlabProgramm', uuid)
    
    def MatlabPrg_create (self, text):
        cur = self.con.cursor()
        t = (text,)
        cur.execute ('INSERT INTO MatlabProgramm (code) VALUES(?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idMatlabProgramm) FROM MatlabProgramm')
        return (True,None,cur.fetchone())
    
    def MatlabPrg_update (self,uuid ,text):
        cur = self.con.cursor()
        t = (text,uuid)
        cur.execute ('UPDATE MatlabProgramm SET code=? WHERE idMatlabProgramm=?',t)
        self.con.commit()    
    
    def MatlabPrg_delete (self,uuid):
        return self.generic_delete('MatlabProgramm',uuid)

    def PythonScript_getList (self):
        return self.generic_getList('pythonScript')
    
    def PythonScript_get (self, uuid):
        return self.generic_get('pythonScript', uuid)
    
    def PythonScript_create (self, text):
        cur = self.con.cursor()
        t = (text,)
        cur.execute ('INSERT INTO pythonScript (code) VALUES(?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idpythonScript) FROM pythonScript')
        return (True,None,cur.fetchone())
    
    def PythonScript_update (self,uuid ,text):
        cur = self.con.cursor()
        t = (text,uuid)
        cur.execute ('UPDATE pythonScript SET code=? WHERE idpythonScript=?',t)
        self.con.commit()
        
    def PythonScript_delete (self,uuid):
        return self.generic_delete('pythonScript',uuid)

    def TestPattern_getList (self):
        return self.generic_getList('testPattern')
    
    def TestPattern_get (self, uuid):
        return self.generic_get('testPattern', uuid)
    
    def TestPattern_create (self, name, descr, idAP ):
        cur = self.con.cursor()
        
        res = self.ALASMprg_create('')
        if res[0] == False:
            return res
        idALASMprogramm = res[2][0]

        res = self.PythonScript_create('# the python implementation')
        if res[0] == False:
            return res
        idpythonProgramm = res[2][0]

        res = self.MatlabPrg_create('% the matlab program')
        if res[0] == False:
            return res
        idMatlabProgramm = res[2][0]

        res = self.PythonScript_create('# the python initiation script')
        if res[0] == False:
            return res
        idPythonInitScript = res[2][0]

        res = self.PythonScript_create('# the python close script')
        if res[0] == False:
            return res
        idPythonExitScript = res[2][0]

        t = (name, descr, idAP, idALASMprogramm, idpythonProgramm, idMatlabProgramm, idPythonInitScript, idPythonExitScript)
        cur.execute ('INSERT INTO testPattern (name, descr, idAP, idALASMprogramm, idpythonProgramm, idMatlabProgramm, idPythonInitScript, idPythonExitScript) VALUES(?, ?, ?, ?, ?, ?, ?, ?)',t)
        self.con.commit()
        cur.execute('SELECT MAX(idtestPattern) FROM testPattern')
        return (True,None,cur.fetchone())
    
    def TestPattern_update (self, uuid, name, descr, idAP):
        cur = self.con.cursor()
        t = (name, descr, idAP, uuid)
        cur.execute ('UPDATE testPattern SET name=?, descr=?, idAP=? WHERE idtestPattern=?',t)
        self.con.commit()
        
    def TestPattern_delete (self,uuid):
        tp = self.TestPattern_get(uuid)
        # del python prg
        self.PythonScript_delete(tp[5])
        # del python init script
        self.PythonScript_delete(tp[7])
        # del python close script
        self.PythonScript_delete(tp[8])
        # del ap ASM prg
        self.ALASMprg_delete(tp[4])
        # del matlab prg
        self.MatlabPrg_delete(tp[6])
        # del
        return self.generic_delete('testPattern',uuid)

    

    # ==================================
    # functions for the code generator 
    # ==================================

    def HAL_gen_VariableList (self):
        cur = self.con.cursor()
        cur.execute('SELECT * FROM HAL_VariableDefinition')
        cl = cur.fetchall()
        start = True
        for c in cl:
            t = (c[0],)
            cur.execute('SELECT * FROM HAL_VariableIOParameter WHERE variableID=?',t)
            if start == True:
                res = [(c,cur.fetchall())]
                start = False
            else:
                res.append ((c,cur.fetchall()))
        if len(cl) <= 0:
            return []
        else :
            return res
        
    def HAL_gen_MsgTypeList (self):
        mtl = self.HAL_Msg_Type_getList()
        start = True
        for mt in mtl:
            t = (mt,self.HAL_msg_TypeParam_getList(mt[1]))
            if start == True:
                res = [t]
                start = False
            else:
                res.append (t)
        return res
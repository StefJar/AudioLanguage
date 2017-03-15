'''
Created on 16.05.2011

@author: StJ
'''
import xml.sax
import xml.sax.handler
import xml.dom.minidom
from warnings import catch_warnings
import sqlite3
import APDB

def boolStrToBool (text):
    if text == 'TRUE' :
        return True
    
    if text == 'true' :
        return True
    
    if text == 'True' :
        return True
    return False

def boolToStr (boolVar):
    if True == boolVar:
        return "True"
    return "False"

class APDBxmlTable():
    def __init__(self, db, multiLineField, tableName, tableField):
        self.db = db
        self.tableName = tableName
        self.tableField = tableField
        
        self.dataTypes = {
            'text'      : [self.SQLValueToXMLValue, self.XMLValueStrToSQLValue],
            'int'       : [self.SQLValueToXMLValue, self.XMLValueIntToSQLValue],
            'bool'      : [self.SQLValueBoolToXMLValue, self.XMLValueBoolToSQLValue],
            'blob'      : [self.SQLValueToXMLValue, self.XMLValueStrToSQLValue]
            }
        
        self.cIndexSQLtoXML = 0
        self.cIndexXMLtoSQL = 1
        
        self.XML_ListPostfix = '_List' 
        self.multiLineField = multiLineField
    
    def setMultilineFieldToData(self, text, data):
        if None == self.multiLineField:
            return data
        data[self.multiLineField] = text
        return data
        
    def SQLValueToXMLValue(self, val):
        return str(val).decode("utf-8")
    
    def SQLValueBoolToXMLValue (self, val):
        if True == val :
            return 'True'
        else:
            return 'False'
    
    def XMLValueIntToSQLValue (self, val):
        return int(val)
    
    def XMLValueStrToSQLValue (self, val):
        return str(val).decode("utf-8")
    
    def XMLValueBoolToSQLValue (self, val):
        if val == 'True' :
            return True
        if val == 'true' :
            return True
        if val == 'TRUE' :
            return True
        return False
    
    def getXMLTableName(self):
        return self.tableName + self.XML_ListPostfix
    
    def getGetSQLSelectAllStr (self):
        sqlStr = 'SELECT '
        c = int(0)
        for fName, fType in self.tableField.iteritems():
            if c != 0 :
                sqlStr += ', '
            sqlStr += fName
            c+= 1
        sqlStr += ' FROM ' + self.tableName
        return sqlStr
    
    def XMLtoSQL_Insert (self, data, commitDB, dbCursor):
        sqlStr = 'INSERT INTO ' + self.tableName
        i = int(0)
        fields = ''
        values = []
        valStr = ''
        # try to fill data to the db
        # we look if we can find a table field associated with the data name
        for key, value in data.iteritems():
            # try to get an entry at the table
            try:
                fType = self.tableField[key]
                if fields != '':
                    fields += ', '
                    valStr += ', '
                fields += key
                funcs = self.dataTypes[fType]
                values.append(funcs[self.cIndexXMLtoSQL](data[key]))
                valStr += '?'
                i+=1
            except:
                print 'skip ' + str(key) + ' with value ' + str(value)
        #build sql string
        sqlStr += '(' + fields +') VALUES (' + valStr + ')'
        # sql string & attributes are now ready
        try:
            dbCursor.execute(sqlStr,values)
        except sqlite3.Error as e:
            print "An error occurred:", e.args[0]
            print 'inserting "'+sqlStr+'" with the values "'+str(values)+'" failed!'
        except:
            print 'inserting "'+sqlStr+'" with the values "'+str(values)+'" failed!' 
        
        if commitDB == True:
            self.db.con.commit()

    def SQLtoXML (self, doc, mainRoot):
        mr = doc.createElement(self.getXMLTableName())
        try:
            cur = self.db.con.cursor()
            cur.execute(self.getGetSQLSelectAllStr())
            l = cur.fetchall()
            
            mainRoot.appendChild(mr)
            for el in l:
                e = doc.createElement(self.tableName)
                c = 0
                for fName, fType in self.tableField.iteritems():
                    convFunc = self.dataTypes[fType]
                    txt = convFunc[self.cIndexSQLtoXML](el[c])
                    if fName != self.multiLineField:
                        e.setAttribute(fName,txt)
                    else :
                        textN = doc.createTextNode(txt)
                        e.appendChild(textN)
                    c += 1
                mr.appendChild(e)
        except:
            print 'error dumping "'+self.tableName+'"'


class APDBxml(xml.sax.handler.ContentHandler):
    def __init__(self, db):
        self.db = db
        self.attributes = None
        self.text = None
        self.tableList = [
            # HAL defines
            APDBxmlTable (db, None,'HAL_basicIOTypes',{
                            'idHAL_IOTypesDefinition'       : 'int',
                            'TypeID'                        : 'int',
                            'TypeName'                      : 'text',
                            'description'                   : 'text',
                            'cType'                         : 'text',
                            'endianType'                    : 'bool',
                            'sizeInBytes'                   : 'int'
                            }),
            APDBxmlTable (db, None,'HAL_VariableIOParameter',{
                            'idHAL_VariableIOParameter' : 'int',
                            'basicTypeID'               : 'int',
                            'VariableID'                : 'int',
                            'name'                      : 'text',
                            'description'               : 'text',
                            'isArray'                   : 'bool'
                            }),
            APDBxmlTable (db, None,'HAL_FunctionsParameter',{
                            'idHAL_FunctionsParameter'  : 'int',
                            'fid'                       : 'int',
                            'name'                      : 'text',
                            'descr'                     : 'text',
                            'idParameterClass'          : 'int',
                            'idParameterType'           : 'int'
                            }),
            APDBxmlTable (db, None,'HAL_MessageParameter',{
                            'idHAL_MessageParameter'    : 'int',
                            'msgID'                     : 'int',
                            'positionIndex'             : 'int',
                            'name'                      : 'text',
                            'descr'                     : 'text',
                            'basicTypeID'               : 'int',
                            'isArray'                   : 'bool'
                            }),
            APDBxmlTable (db, None,'HAL_VariableDefinition',{
                            'idHAL_VariableDefinition'  : 'int',
                            'VariableID'                : 'int',
                            'varName'                   : 'text',
                            'description'               : 'text'
                            }),
            APDBxmlTable (db, None,'HAL_Function',{
                            'idHAL_Function'    : 'int',
                            'fid'               : 'int',
                            'name'              : 'text',
                            'descr'             : 'text'
                            }),
            APDBxmlTable (db, None,'HAL_MessageType',{
                            'idHAL_MessageType'     : 'int',
                            'msgID'                 : 'int',
                            'name'                  : 'text',
                            'descr'                 : 'text'
                            }),
            APDBxmlTable (db,'msgCode','HAL_MessageProcess',{
                            'idHAL_MessageProcess'      : 'int',
                            'msgProcID'                 : 'int',
                            'name'                      : 'text',
                            'descr'                     : 'text',
                            'isRX'                      : 'bool',
                            'msgCode'                   : 'text'
                            }),
            # c code
            APDBxmlTable (db, None,'Includes',{
                            'idIncludes'    : 'int',
                            'includefile'   : 'text',
                            'lib'           : 'text',
                            'syslib'        : 'text'
                            }),
            APDBxmlTable (db, None,'IncludeList',{
                            'idCode'        : 'int',
                            'idIncludes'    : 'int'
                            }),
            APDBxmlTable (db,'code','Code',{
                            'idCode'        : 'int',
                            'code'          : 'text'
                            }),
            # compiler
            APDBxmlTable (db, None,'Compiler',{
                            'idCompiler'        : 'int',
                            'name'              : 'text',
                            'description'       : 'text',
                            'OperatingSystem'   : 'text',
                            'CC'                : 'text',
                            'CXX'               : 'text',
                            'ASM'               : 'text',
                            'AR'                : 'text',
                            'LINK'              : 'text',
                            'CCFLAGS'           : 'text',
                            'OBJSUFFIX'         : 'text',
                            'CCCOM'             : 'text',
                            'CXXCOM'            : 'text',
                            'CXXFLAGS'          : 'text',
                            'LINKCOM'           : 'text',
                            'LINKFLAGS'         : 'text'
                            }),
            APDBxmlTable (db, None,'CompilerLib',{
                            'idCompilerLib'     : 'int',
                            'idCompiler'        : 'int',
                            'lib'               : 'text'
                            }),
            APDBxmlTable (db, None,'CompilerLibPath',{
                            'idCompilerLibPath'    : 'int',
                            'idCompiler'            : 'int',
                            'path'                  : 'text'
                            }),
            APDBxmlTable (db, None,'CompilerIncludePath',{
                            'idCompilerIncludePath' : 'int',
                            'idCompiler'            : 'int',
                            'path'                  : 'text'
                            }),
            # implementation
            APDBxmlTable (db, None,'ImplHALFunction',{
                            'idImplHALFunction'     : 'int',
                            'fid'                   : 'int',
                            'idCode'                : 'int',
                            'descr'                 : 'text',
                            'idImplGroup'           : 'int'
                            }),
            APDBxmlTable (db, None,'ImplHALVariable',{
                            'idImplHALVariable'     : 'int',
                            'VariableID'            : 'int',
                            'idCode'                : 'int',
                            'descr'                 : 'text',
                            'idImplGroup'           : 'int'
                            }),
            APDBxmlTable (db, None,'ImplMsgDriver',{
                            'idImplMsgDriver'       : 'int',
                            'idCode'                : 'int',
                            'descr'                 : 'text',
                            'idImplGroup'           : 'int'
                            }),
            APDBxmlTable (db, None,'ImplAP',{
                            'idImplAP'              : 'int',
                            'idCode'                : 'int',
                            'descr'                 : 'text',
                            'idImplGroup'           : 'int'
                            }),
                          
            APDBxmlTable (db, None,'ImplGroup',{
                            'idImplGroup'       : 'int',
                            'name'              : 'text',
                            'idCode'            : 'int'
                            }),

            # ap
            APDBxmlTable (db, None,'AP',{
                            'idAP'                  : 'int',
                            'name'                  : 'text',
                            'idCompiler'            : 'int',
                            'descr'                 : 'text',
                            'idCodeStartup'         : 'int'
                            }),
                          
            APDBxmlTable (db, None,'FunctionList',{
                            'idFunctionList'        : 'int',
                            'idAP'                  : 'int',
                            'idImplHALFunction'     : 'int'
                            }),
            APDBxmlTable (db, None,'VariableList',{
                            'idVariableList'        : 'int',
                            'idAP'                  : 'int',
                            'idImplHALVariable'     : 'int'
                            }),
            APDBxmlTable (db, None,'DriverList',{
                            'idDriverList'          : 'int',
                            'idAP'                  : 'int',
                            'idImplMsgDriver'       : 'int'
                            }),
            APDBxmlTable (db, None,'APList',{
                            'idAPList'              : 'int',
                            'idAP'                  : 'int',
                            'idImplAP'              : 'int'
                            }),
#test pattern
            APDBxmlTable (db, None,'ALASMprogramm',{
                            'idALASMprogramm'       : 'int',
                            'code'                  : 'text'
                            }),
            APDBxmlTable (db, None,'pythonScript',{
                            'idpythonScript'        : 'int',
                            'code'                  : 'text'
                            }),
            APDBxmlTable (db, None,'MatlabProgramm',{
                            'idMatlabProgramm'      : 'int',
                            'code'                  : 'text'
                            }),
                                      
            APDBxmlTable (db, None,'testPattern',{
                            'idtestPattern'         : 'int',
                            'name'                  : 'text',
                            'descr'                 : 'text',
                            'idAP'                  : 'int',
                            'idALASMprogramm'       : 'int',
                            'idpythonProgramm'      : 'int',
                            'idMatlabProgramm'      : 'int',
                            'idPythonInitScript'    : 'int',
                            'idPythonExitScript'    : 'int'
                            })            
            ]
        
    def dumpToXMLFile(self, filename):
        doc = xml.dom.minidom.Document()
        mainRoot = doc.createElement("APDB")
        doc.appendChild(mainRoot)
        for t in self.tableList:
            t.SQLtoXML (doc, mainRoot)

        f = open(filename, "w")
        #f.write(doc.toprettyxml())
        f.write(doc.toxml())
        f.close()
    
    def XMLFileToDB (self,filename):
        self.cur = self.db.con.cursor()
        parser = xml.sax.make_parser()
        parser.setContentHandler(self)
        parser.parse(filename)
        # save db
        self.cur.close()
        self.db.con.commit()
        
        
    def startElement(self, name, attributes):
        self.attributes = attributes
        self.text = ''
    
    def endElement(self, name):
        t = self.findTable(name)
        if None == t:
            return
        # build dict from the attributes
        mydict = {}
        for attrib, val in self.attributes.items():
            mydict[attrib] = val
        mydict = t.setMultilineFieldToData(self.text,mydict)
        t.XMLtoSQL_Insert(mydict,False,self.cur)

    def characters(self, data):
        self.text += data
    
    def findTable (self,name):
        for t in self.tableList:
            if t.tableName == name : return t
        return None
    
    def cleanAllTables (self):
        cur = self.db.con.cursor()
        for t in self.tableList:
            cur.execute ('DELETE FROM ' + t.tableName)
        cur.close()
        self.db.con.commit()
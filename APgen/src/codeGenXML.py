'''
Created on 06.06.2011

@author: StJ
'''

import xml.sax
import xml.sax.handler
import APDB
import xml.dom.minidom

import APDBxml


class CodeGeneratorXMLReader(xml.sax.handler.ContentHandler):
    def __init__(self):
        # dict <XML Tag> : [use info strack , end element function handling, handler>]
        self.XMLelements = {
            'APGen'                     : self.Handler_noAction,
            'files'                     : self.Handler_noAction,
            'headerTemplate'            : self.Handler_headerTemplate,
            'implementationTemplate'    : self.Handler_implTemplate,
            'APbluePrints'              : self.Handler_noAction,
            'APBPsingleThread'          : self.Handler_ST,
            'APBPmultiThread'           : self.Handler_MT,
            'APstartUpTemplate'         : self.Handler_startUpCode
            }
        
        self.attributeStack = []
        self.text = ''
        # vars
        self.includes = []
        self.files = {}

    def loadFile (self, filename):
        openfile = open(filename, 'r')
        res = openfile.read()
        openfile.close()
        return res;

        
    def startElement(self, name, attributes):
        self.text = ''
        self.attributeStack.append(attributes)

    def endElement(self, name):
        info = self.XMLelements.get(name,self.unknownElement)
        info(self.attributeStack[-1])
        self.attributeStack.pop()
        self.text = ''

    def characters(self, data):
        self.text += data

    def unknownElement (self, attributes):
        print ("unknown element!")
        print attributes.items()
        print self.text
        
    def Handler_noAction (self, attributes):
        pass
    
    def Handler_headerTemplate (self, attributes):
        self.files['header'] = self.loadFile (self.text)
    
    def Handler_implTemplate (self, attributes):
        self.files['code'] = self.loadFile (self.text)
    
    def Handler_ST (self, attributes):
        self.files['bp_st'] = self.loadFile (self.text)
        
    def Handler_MT (self, attributes):
        self.files['bp_mt'] = self.loadFile (self.text)
    
    def Handler_startUpCode (self, attributes):
        self.files['startUpCode'] = self.loadFile (self.text)

    def Handler_include (self, attributes):
        self.includes.append((
            -1, # fake id for handling the include like a db entry 
            attributes["includefile"],
            attributes["lib"], 
            APDBxml.boolStrToBool(attributes["syslib"])
            )
        )
    
    

def CodeGenXMLparseFile(filename):
    parser = xml.sax.make_parser()
    handler = CodeGeneratorXMLReader()
    parser.setContentHandler(handler)
    parser.parse(filename)
    return handler

        
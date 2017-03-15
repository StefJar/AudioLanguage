'''
Created on 05.10.2011

@author: StJ
'''

import logging

def createLogger (logfilename):
    logging.basicConfig(filename=logfilename,filemode='w',format='%(name)s [%(levelname)s] : %(message)s',level=logging.DEBUG)
    logging.info ('start logger')

def closeLogger ():
    logging.info ('close logger')

def getScriptProcessorLogger ():
    return logging.getLogger('SP')

def getAPBuilderLogger ():
    return logging.getLogger('AB')

def getUILogger ():
    return logging.getLogger('UI')

def getDBLogger ():
    return logging.getLogger('DB')

def getCodeGenLogger ():
    return logging.getLogger('CG')

'''
Created on 04.10.2011

@author: StJ
'''


import platform
import re
import os

import subprocess

import APDB
import APlogger


def executePythonScript (scriptText):
    log = APlogger.getScriptProcessorLogger()
    
    log.info('create python process ...')
    # spawn process for python
    process = subprocess.Popen('python', shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    log.info('execute script ...')
    # feed the process with the script
    process.stdin.write (scriptText)
    # terminate python
    log.info('terminate python process ...')
    process.stdin.write ("\nexit()\n")
    process.stdin.close()
    # save stdout to log file
    log.info('python out: '+ process.stdout.read())
    process.stdout.close()
    #wait till python has ended
    rc = process.wait()
    if  rc != 0:
        log.error ('python failed with error code '+str(rc))
        return False
    return True

def executeMatlabProg (matlabPrg):
    log = APlogger.getScriptProcessorLogger()
    
    log.info('create matlab process and execute script...')
    # spawn process for matlab
    sd = os.getcwd()
    ms = 'cd ' + sd + ';\n' 
    ms += matlabPrg
    ms += '\nexit();\n'
    process = subprocess.Popen('matlab -automation -wait -nosplash -r "'+ms+'"' ,shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    #wait till python has ended
    rc = process.wait()
    if  rc != 0:
        log.error ('matlab failed with error code '+str(rc))
        return False
    return True

def executeApp ():
    log = APlogger.getScriptProcessorLogger()
    
    log.info('create audio processor and execute script ...')

    process = subprocess.Popen('code/StjAPcrossoverTest.exe' ,shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE)    
    #wait till python has ended
    rc = process.wait()
    if  rc != 0:
        log.error ('audio processor failed with error code '+str(rc))
        return False
    
    
    return True
    

def executeTestPattern (db, testPatternID):
    log = APlogger.getScriptProcessorLogger()
    log.info ('start performing test pattern')
    # get data set

    log.info ('get test pattern ...')
    tp = db.TestPattern_get(testPatternID)
    if tp == None:
        log.error ('getting test pattern with id='+str(testPatternID)+' failed')
        return False

    # init
    
    log.info ('execute init script ...')
    s = db.PythonScript_get(tp[7])
    if s == None:
        log.error ('init script with id='+str(tp[7])+'does not exist (maybe database corrupt)')
        return False
    if executePythonScript(s[1]) == False:
        log.error ('execution of the init script failed!')
        return False
    
    # execute 
    log.info ('execute python program ...')
    s = db.PythonScript_get(tp[5])
    if s == None:
        log.error ('python program with id='+str(tp[5])+'does not exist (maybe database corrupt)')
        return False
    if executePythonScript(s[1]) == False:
        log.error ('execution of the python program failed!')
        return False


    log.info ('execute matlab program ...')
    s = db.MatlabPrg_get(tp[6])
    if s == None:
        log.error ('matlab program with id='+str(tp[6])+'does not exist (maybe database corrupt)')
        return False
    if executeMatlabProg(s[1]) == False:
        log.error ('execution of the matlab program failed!')
        return False

    log.info ('execute audio processor program ...')
    s = db.ALASMprg_get(tp[4])
    if s == None:
        log.error ('audio processor program with id='+str(tp[6])+'does not exist (maybe database corrupt)')
        return False
    if executeApp() == False:
        log.error ('execution of the audio processor program failed!')
        return False


    # close
    log.info ('execute close script ...')
    s = db.PythonScript_get(tp[8])
    if s == None:
        log.error ('close script with id='+str(tp[7])+'does not exist (maybe database corrupt)')
        return False
    if executePythonScript(s[1]) == False:
        log.error ('execution of the close script failed!')
        return False
    
    log.info ('end of performing of the test pattern')
    return True
    
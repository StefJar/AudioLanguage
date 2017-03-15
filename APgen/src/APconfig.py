#!/usr/bin/env python

# First run tutorial.glade through gtk-builder-convert with this command:
# gtk-builder-convert tutorial.glade tutorial.xml
# Then save this file as tutorial.py and make it executable using this command:
# chmod a+x tutorial.py
# And execute it:
# ./tutorial.py

import APDB
import DBwindows
import APlogger

import codeGen


if __name__ == "__main__":

    APlogger.createLogger('APcfg.log')
    
    db = APDB.APDB('APdbCreate.sql','dbInit.xml')

#    cg = codeGen.codeGenerator(db,'')
#    cg.genGenericVariablesMessageInterface()
    
       
    mainUI = DBwindows.uiAPmain('AP.glade',db)
    mainUI.show();

    DBwindows.UIstart();

    
    APlogger.closeLogger()
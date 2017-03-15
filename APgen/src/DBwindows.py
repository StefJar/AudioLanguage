'''
Created on 19.01.2011

@author: stj
'''

import sys
import getopt
import subprocess
import os
import shutil

import pygtk
pygtk.require("2.0")
import gtk
import gtk.glade
import gtk.gdk
import time

import APDB
import codeGen
import APDBxml

import apBuilder
import benchmark
import APmsgProcessCompilier

import signGen
import floatwavefile

import APdocgen


def UIstart():
    print('start UI')
    print ('gtk version ...')
    print (pygtk._get_available_versions())
    gtk.main()
    print('finished UI')
         
class MessageBox(gtk.Dialog):
    def __init__(self, message="", buttons=(), pixmap=None,
            modal= gtk.TRUE):
        gtk.Dialog.__init__(self)
        self.connect("destroy", self.quit)
        self.connect("delete_event", self.quit)
        if modal:
            self.set_modal(gtk.TRUE)
        hbox = gtk.HBox(spacing=5)
        hbox.set_border_width(5)
        self.vbox.pack_start(hbox)
        hbox.show()
        if pixmap:
            self.realize()
            pixmap = Pixmap(self, pixmap)
            hbox.pack_start(pixmap, expand=gtk.FALSE)
            pixmap.show()
        label = gtk.Label(message)
        hbox.pack_start(label)
        label.show()
        for text in buttons:
            b = gtk.Button(text)
            b.set_flags(gtk.CAN_DEFAULT)
            b.set_data("user_data", text)
            b.connect("clicked", self.click)
            self.action_area.pack_start(b)
            b.show()
        self.ret = None
    def quit(self, *args):
        self.hide()
        self.destroy()
    def click(self, button):
        self.ret = button.get_data("user_data")
        self.quit()

# adding cols
def addColumnToTable (treeView,title,listStoreID,editable):
    renderer = gtk.CellRendererText();
    renderer.set_property('editable', editable)
    col = gtk.TreeViewColumn(title,renderer,text=listStoreID)
    col.set_resizable(True)
    col.set_sort_column_id(listStoreID)
    treeView.append_column(col)
    return renderer

def getTextViewCompleteText(tv):
    b = tv.get_buffer()
    (start, end) = b.get_bounds() 
    return b.get_text(start, end).decode("utf-8")

def getTextBufferCompleteText(tb):
    (start, end) = tb.get_bounds() 
    return tb.get_text(start, end).decode("utf-8")



def comboBoxSelectValue (cb,compareVal,listpos):
    model = cb.get_model()
    if model != None:
        it = model.get_iter_first()
        while it:
            value = model.get_value(it,listpos)
            if value == compareVal:
                cb.set_active_iter(it)
                return
            it = model.iter_next(it)
        cb.set_active(-1)

def comboBoxGetValue (cb, listPos):
        it = cb.get_active_iter()
        if it != None:
            return cb.get_model().get_value(it,listPos)
        else :
            return None

def executeExternalProgramm (programm, parameter, stdinTxt):
    cmdLine = programm + ' ' + parameter
    process = subprocess.Popen(cmdLine,shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)    
    # if some std in txt ist set write it to the pipe
    if stdinTxt != None:
        process.stdin.write (stdinTxt)
        process.stdin.close()
    # get the results
    outTxt = process.stdout.read()
    process.stdout.close()
    
    errTxt = process.stderr.read()
    process.stderr.close()
    
    # wait for the process
    rc = process.wait()
    if  rc != 0:
        return False, outTxt, errTxt
    return True, outTxt, errTxt

def setWaitCursor (dlg):
    watch = gtk.gdk.Cursor(gtk.gdk.WATCH)
    dlg.get_window().set_cursor(watch)
    time.sleep(0)
    gtk.main_iteration_do(False)

    
def setStdCursor (dlg):
    dlg.get_window().set_cursor(None)
    time.sleep(0)
    gtk.main_iteration_do(False)

class uiEnterTxtDlg (object):
    def __init__(self, gladeFile,textLabel,text):
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "dlgEnterText") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bOK_dlgEnterText_clicked" : self.ok,
             "on_bClose_dlgEnterText_clicked" : self.close,
            }
            )
        self.ret = None
        self.dlg = self.gladeTmpl.get_widget("dlgEnterText")
        self.lTextLabel = self.gladeTmpl.get_widget("lText_dlgEnterText")
        self.lTextLabel.set_text(textLabel)
        self.eText = self.gladeTmpl.get_widget("tvText_dlgEnterText")
        self.textBuffer = gtk.TextBuffer()
        self.textBuffer.set_text(text)
        self.eText.set_buffer(self.textBuffer)
        
        
    def close(self,b):
        self.dlg.response(-1)
        self.dlg.hide()
        self.dlg.destroy()

    def ok(self,b):
        start, end = self.textBuffer.get_bounds()
        self.ret = self.textBuffer.get_text(start,end);
        self.dlg.response(0)
        self.dlg.hide()
        self.dlg.destroy()
        
    def run (self):
        return self.dlg.run()

class uiHALbasicIOTypes (object):
    def __init__(self, gladeFile,db):
        self.db = db
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "wIOTypes") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_clicked" : self.actionClose,
             "on_tvTypes_wIOTypes_cursor_changed": self.cursorChanged,
             "on_bNew_wIOTypes_clicked": self.newType,
             "on_bConfirm_wIOTypes_clicked": self.changeType,
             "on_bDelete_wIOTypes_clicked": self.delType
            }
            )
        self.wdg = self.gladeTmpl.get_widget("wIOTypes")
        # get the edit fields
        self.edTypeID = self.gladeTmpl.get_widget("eTypeID_wIOTypes")
        self.edTypeName = self.gladeTmpl.get_widget("eTypeName_wIOTypes")
        self.edTypeDescr = self.gladeTmpl.get_widget("eTypeDescription_wIOTypes")
        self.edCType = self.gladeTmpl.get_widget("eCType_wIOTypes")
        self.edSize = self.gladeTmpl.get_widget("eSizeInBytes_wIOTypes")
        self.cbEndian = self.gladeTmpl.get_widget("cbEndianCare_wIOTypes")
        self.uuid = 0;
        
        #build table
        
        #create view header
        tv = self.gladeTmpl.get_widget ("tvTypes_wIOTypes")
        cr1 = addColumnToTable(tv, 'id', 1,False)
        cr2 = addColumnToTable(tv, 'name', 2,False)
        cr3 = addColumnToTable(tv, 'description',3,False)
        cr4 = addColumnToTable(tv, 'c type',4,False)
        cr5 = addColumnToTable(tv, 'endian type',5,False)
        cr6 = addColumnToTable(tv, 'size in bytes',6,False)
        
        
        # create the list
        self.list = gtk.ListStore(int, int, str , str, str, bool, int)
        tv.set_model(self.list)
       
        #cr1.connect('edited', self.edited_cb1, self.list)
        #cr2.connect('edited', self.edited_cb2, self.list)
        #cr3.connect('edited', self.edited_cb3, self.list)

        self.updateModel()

    def updateModel (self):
        # insert data from the database
        # 1. delete all data at the list
        self.list.clear()
        # 2. get list from db
        dbrows = self.db.HAL_basicIOTypes_getList()
        #3. transfer db list to gtk list
        for row in dbrows:
            self.list.append(row)
       
    def show(self):
        self.wdg.show();
    
    def actionClose(self, widget):
        self.wdg.destroy()

    def edited_cb1(self, cell, path, new_text, user_data):
        self.list[path][1] = int (new_text)

    def cursorChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuid = model.get_value(iter,0)
            self.edTypeID.set_text (str(model.get_value(iter,1)))
            self.edTypeName.set_text (model.get_value(iter,2))
            self.edTypeDescr.set_text (model.get_value(iter,3))
            self.edCType.set_text (model.get_value(iter,4))
            self.cbEndian.set_active (model.get_value(iter,5))
            self.edSize.set_text (str(model.get_value(iter,6)))
            
    def newType (self,b):
        (res, errormsg, uuid) = self.db.HAL_basicIOType_add(
            int(self.edTypeID.get_text()),
            self.edTypeName.get_text(),
            self.edTypeDescr.get_text(),
            self.edCType.get_text (),
            self.cbEndian.get_active(),
            int(self.edSize.get_text ())
            )
        if res == False:
            mb = MessageBox(
                message=errormsg,
                buttons=('Ok',)
                )
            mb.run()
        else:
            self.updateModel()
            
    def changeType (self,b):
        self.db.HAL_basicIOType_update(
            self.uuid,
            int(self.edTypeID.get_text()),
            self.edTypeName.get_text(),
            self.edTypeDescr.get_text(),
            self.edCType.get_text (),
            self.cbEndian.get_active(),
            int(self.edSize.get_text ())
        )
        self.updateModel()
    
    def delType (self,b):
        self.db.HAL_basicIOType_del(self.uuid)
        self.updateModel()


class uiHALVariable (object):
    def __init__(self, gladeFile,db):
        self.db = db
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "wHALVariable") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_wHALVariable_clicked" : self.actionClose,
             "on_tvVariable_wHALVariable_cursor_changed": self.cursorVarChanged,
             "on_bCNew_wHALVariable_clicked" : self.addComp,
             "on_bChange_wHALVariable_clicked": self.changeComp,
             "on_bDel_wHALVariable_clicked": self.delComp,
             "on_tvParameter_wHALVariable_cursor_changed": self.cursorCompParamChanged,
             "on_bPAdd_wHALVariable_clicked": self.addParam,
             "on_bPChange_wHALVariable_clicked" : self.updateParam,
             "on_bPDel_wHALVariable_clicked" : self.delParam
            }
            )
        self.wdg = self.gladeTmpl.get_widget("wHALVariable")
        # get the edit fields
        self.uuid = 0;
        self.edVID = self.gladeTmpl.get_widget("eVID_wHALVariable")
        self.edVName = self.gladeTmpl.get_widget("eVName_wHALVariable")
        self.edVDescr = self.gladeTmpl.get_widget("eDescr_wHALVariable")
        self.cbPType = self.gladeTmpl.get_widget("cbPType_wHALVariable")
        # parameter
        self.puuid = 0
        self.epname = self.gladeTmpl.get_widget("ePName_wHALVariable")
        self.cbParamType = self.gladeTmpl.get_widget("cbPType_wHALVariable")
        self.epdescr = self.gladeTmpl.get_widget("ePDescr_wHALVariable")
        self.cbpArray = self.gladeTmpl.get_widget("cbArray_wHALVariable")

        #build table
        
        #create component view header
        tv = self.gladeTmpl.get_widget ("tvVariable_wHALVariable")
        cr1 = addColumnToTable(tv, 'id', 1,False)
        cr2 = addColumnToTable(tv, 'name', 2,False)
        cr3 = addColumnToTable(tv, 'description',3,False)
        
        # create the list
        self.clist = gtk.ListStore(int, int, str , str)
        tv.set_model(self.clist)
        
        #create list for the combobox
        self.pTypeList = gtk.ListStore( int, str)
        self.cbPType.set_model(self.pTypeList)
        cell = gtk.CellRendererText()
        self.cbPType.pack_start(cell, True)
        self.cbPType.add_attribute(cell, 'text', 1)
        
        #create component parameter view header
        tpv = self.gladeTmpl.get_widget ("tvParameter_wHALVariable")
        cp1 = addColumnToTable(tpv, 'name', 3 ,False)
        cp2 = addColumnToTable(tpv, 'type', 2 ,False)
        cp3 = addColumnToTable(tpv, 'description', 4 ,False)
        cp4 = addColumnToTable(tpv, 'is array parameter', 5 ,False)
        
        # create the list
        self.cplist = gtk.ListStore(int, int, str , str, str, bool)
        tpv.set_model(self.cplist)
        
        #populate combobox and treeview

        self.pTypeList.clear()
        # 2. get list from db
        dbrows = self.db.HAL_basicIOTypes_getList()
        #3. transfer db list to gtk list
        for row in dbrows:
            self.pTypeList.append((row[1], row[2]))

        # the main treeview
        self.updateCompModel()


    def updateCompModel (self):
        # insert data from the database
        # 1. delete all data at the list
        self.clist.clear()
        # 2. get list from db
        dbrows = self.db.HAL_VariableDefinition_getList()
        #3. transfer db list to gtk list
        for row in dbrows:
            self.clist.append(row)
        
        self.uuid = 0
        self.edVID.set_text ('0')
        self.edVName.set_text ('unknown')
        self.edVDescr.set_text ('')

        self.updateCompParamModel()

    def updateCompParamModel(self):
        # insert data from the database
        # 1. delete all data at the list
        self.cplist.clear()
        # 2. get list from db
        dbrows = self.db.HAL_VariableDefinition_getParamList(int(self.edVID.get_text()))
        #3. transfer db list to gtk list
        for row in dbrows:
            myrow = (
                row[0],
                row[1],
                self.db.HAL_basicIOType_getNameByTypeID(row[1]),
                row[3],
                row[4],
                row[5]
                )
            self.cplist.append(myrow)
        #4. select nothing
        self.puuid = None
        self.epname.set_text('unknown')
        self.epdescr.set_text('')
        self.cbParamType.set_active(-1)
        self.cbPType.set_active(-1)
        self.cbpArray.set_active(False)


    def show(self):
        self.wdg.show();
        
    def actionClose(self, widget):
        self.wdg.destroy()
        
    def cursorVarChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuid = model.get_value(iter,0)
            self.edVID.set_text (str(model.get_value(iter,1)))
            self.edVName.set_text (model.get_value(iter,2))
            self.edVDescr.set_text (model.get_value(iter,3))
        else:
            self.uuid = 0
            self.edVID.set_text ('0')
            self.edVName.set_text ('unknown')
            self.edVDescr.set_text ('')
        self.updateCompParamModel()
            
    def addComp(self,b):
        (res, errormsg, uuid) = self.db.HAL_VariableDefinition_add(
            int(self.edVID.get_text()),
            self.edVName.get_text(),
            self.edVDescr.get_text()
            )
        if res == False:
            mb = MessageBox(
                message=errormsg,
                buttons=('Ok',)
                )
            mb.run()
        else:
            self.updateCompModel()
            
            
    def changeComp (self,b):
        self.db.HAL_VariableDefinition_update(
            self.uuid,
            int(self.edVID.get_text()),
            self.edVName.get_text(),
            self.edVDescr.get_text()
        )
        self.updateCompModel()
    
    def delComp (self,b):
        self.db.HAL_VariableDefinition_del(self.uuid)
        self.updateCompModel()

    def cursorCompParamChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.puuid = model.get_value(iter,0)
            self.epname.set_text(model.get_value(iter,3))
            comboBoxSelectValue(self.cbParamType,model.get_value(iter,1),0)
            self.epdescr.set_text(model.get_value(iter,4))
            self.cbpArray.set_active(model.get_value(iter,5))
        self.epname = self.gladeTmpl.get_widget("ePName_wHALVariable")
        self.eptype = 0;

    def addParam (self,b):
        if self.uuid <= 0: return
        (res, errormsg, uuid) = self.db.HAL_VariableDefinition_addParam(
            comboBoxGetValue(self.cbPType,0),
            int (self.edVID.get_text()),
            self.epname.get_text(),
            self.epdescr.get_text(),
            self.cbpArray.get_active()
            )
        if res == False:
            mb = MessageBox(
                message=errormsg,
                buttons=('Ok',)
                )
            mb.run()
        else:
            self.updateCompParamModel()

    def updateParam (self,b):
        if self.uuid <= 0: return
        self.db.HAL_VariableDefinition_updateParam(
            self.puuid,
            comboBoxGetValue(self.cbPType,0),
            int (self.edVID.get_text()),
            self.epname.get_text(),
            self.epdescr.get_text(),
            self.cbpArray.get_active()
            )
        self.updateCompParamModel()
            
    def delParam (self,b):
        if self.uuid <= 0: return
        self.db.HAL_VariableDefinition_delParam(self.puuid)
        self.updateCompParamModel()
    
    def typeCBchanged(self,cb):
        iter = cb.get_active_iter()
        if iter != None:
            self.ParamTypeID = self.pTypeList.get_value(iter,0)

class uiCodeEntry (object):
    def __init__(self, gladeFile, db, idCode):
        self.gladefile = gladeFile
        self.db = db
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "dCodeEntry") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_dCodeEntry_clicked" : self.actionClose,
             "on_bIncludeAdd_dCodeEntry_clicked": self.inclAdd,
             "on_bIncludeChange_dCodeEntry_clicked": self.inclChange,
             "on_bIncludeDel_dCodeEntry_clicked": self.inclDel,
             "on_tvIncludes_dCodeEntry_cursor_changed": self.inclCurChanged,
             "on_bDiscard_dCodeEntry_clicked": self.actionDiscard
            }
            )
        self.wdg = self.gladeTmpl.get_widget("dCodeEntry")
        
        #include list
        self.tvIncludes = self.gladeTmpl.get_widget ("tvIncludes_dCodeEntry")
        cp1 = addColumnToTable(self.tvIncludes, 'include file', 1 ,False)
        cp2 = addColumnToTable(self.tvIncludes, 'include lib', 2 ,False)
        cp3 = addColumnToTable(self.tvIncludes, 'system lib', 3 ,False)
        
        # create the include list
        self.includeList = gtk.ListStore(int, str , str, bool)
        self.tvIncludes.set_model(self.includeList)

        self.eIncludeFile = self.gladeTmpl.get_widget ("eIncludeFilename_dCodeEntry")
        self.eIncludeLib = self.gladeTmpl.get_widget ("eIncludeLib_dCodeEntry")
        self.cbSyslib = self.gladeTmpl.get_widget("cbSyslib_dCodeEntry")
        
        self.tCCode = self.gladeTmpl.get_widget ("tvCode_dCodeEntry")
        self.codeBuffer = gtk.TextBuffer()
        self.tCCode.set_buffer(self.codeBuffer)
        #create code or load from db
        if idCode <= 0:
            self.uuid = self.db.Code_createCode('// enter new code here')
        else:
            self.uuid = idCode
        
        # fill lists
        text = self.db.Code_getCode(self.uuid)
        self.codeBuffer.set_text(text)

        # fill includes
        self.updateIncludeList()
        
        
    def updateIncludeList(self):
        self.includeList.clear()
        list = self.db.Code_getIncludes(self.uuid)
        for element in list:
            self.includeList.append(element)
        
        
    def run(self):
        self.wdg.run();
    
    def actionClose(self, widget):
        #update db
        self.db.Code_updateCode(self.uuid,getTextViewCompleteText(self.tCCode))
        
        self.wdg.response(gtk.RESPONSE_OK)
        self.wdg.destroy()
    
    def actionDiscard (self, b):
        self.wdg.response(gtk.RESPONSE_CANCEL)
        self.wdg.destroy()
    
    def inclAdd(self,b):
        (res,errorTxt,id) = self.db.Code_createInclude(self.uuid,self.eIncludeFile.get_text(),self.eIncludeLib.get_text(),self.cbSyslib.get_active())
        if res == False:
            mb = MessageBox(
                message=errorTxt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateIncludeList()


    def inclChange(self,b):
        sel = self.tvIncludes.get_selection()
        if sel == None:
            return
        (model, iter) = sel.get_selected()
        (res, id) = self.db.Code_updateInclude(self.uuid,model.get_value(iter,0),self.eIncludeFile.get_text(),self.eIncludeLib.get_text(),self.cbSyslib.get_active())
        if res == False:
            mb = MessageBox(
                message='include with the file or the library still exists',
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateIncludeList()
            
        
    def inclDel(self,b):
        sel = self.tvIncludes.get_selection()
        if sel == None: return
        (model, iter) = sel.get_selected()

        self.db.Code_deleteInclude(self.uuid,model.get_value(iter,0))
        self.updateIncludeList()

    def inclCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.eIncludeFile.set_text(model.get_value(iter,1))
            self.eIncludeLib.set_text(model.get_value(iter,2))
            self.cbSyslib.set_active (model.get_value(iter,3))


class uiHALSkeleton (object):
    def __init__(self, gladeFile,db):
        self.db = db
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "wHALSkeleton") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_wHALSkeleton_clicked" : self.actionClose,
             "on_bIOTypes_wHALSkeleton_clicked" : self.actionIOTypes,
             "on_bVariable_wHALSkeleton_clicked": self.actionVariable,
             "on_bFunctions_wHALSkeleton_clicked": self.actionHALFunctions,
             "on_bMsgSystem_wHALSkeleton_clicked": self.actionMsgSystem
             
            }
            )
        self.wdg = self.gladeTmpl.get_widget("wHALSkeleton")

    def show(self):
        self.wdg.show();
    
    def actionClose(self, widget):
        self.wdg.destroy()
        
    def actionIOTypes(self, b):
        uiHALbasicIOTypes(self.gladefile,self.db).show()

    def actionVariable(self,b):
        uiHALVariable(self.gladefile,self.db).show()

    def actionHALFunctions(self,b):
        hf = uiHALDefineFunctions(self.gladefile,self.db)
        res = hf.run()

    def actionMsgSystem(self,b):
        dlg = uiHALMsgSystem(self.gladefile,self.db)
        dlg.run()

class uiAPmain(object):
    def __init__(self, gladeFile,db):
        self.db = db
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgMain') 
        self.gladeTmpl.signal_autoconnect (
            {
             "destroy" : gtk.main_quit,
             "on_bClose_dlgMain_clicked"                : self.actionClose,
             "on_bAPskeleton_dlgMain_clicked"           : self.actionHALSkeleton,
             "on_bAP_dlgMain_clicked"                   : self.actionAP,
             'on_bDumpDB_dlgMain_clicked'               : self.dumpDB,
             'on_bRestoreDB_dlgMain_clicked'            : self.restoreDB,
             'on_bImpl_dlgMain_clicked'                 : self.actionImplHAL,
             'on_bCompiler_dlgMain_clicked'             : self.actionCompiler,
             'on_bTestAudioProcessor_dlgMain_clicked'   : self.actionTestAP,
             'on_bGroups_dlgMain_clicked'               : self.actionImplemntGroups,
             'on_bWavFileGenerators_dlgMain_clicked'    : self.actionWavFileGen,
             'on_bDocGen_dlgMain_clicked'               : self.actionGenDoc,
             'on_bGenRemoteInterface_dlgMain_clicked'   : self.actionGenRemoteInterface,
             'on_bCmplPrg_dlgMain_clicked'              : self.actionCompileAL
            }
            )
        self.wdg = self.gladeTmpl.get_widget('dlgMain')
        
    def show(self):
        self.wdg.show()
    
    def actionClose(self, b):
        gtk.mainquit()
        
    def actionHALSkeleton(self, b):
        wndHALSkel = uiHALSkeleton(self.gladefile,self.db)
        wndHALSkel.show()
    
    def actionAP(self,b):
        dlgAP = uiAPsetup(self.gladefile,self.db)
        dlgAP.run()
        
    def dumpDB(self,b):
        fsDlg = gtk.FileChooserDialog(title=None,action=gtk.FILE_CHOOSER_ACTION_SAVE,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        
        fltr = gtk.FileFilter()
        fltr.set_name("All files")
        fltr.add_pattern("*")
        fsDlg.add_filter(fltr)
        fltr = gtk.FileFilter()
        fltr.set_name("XML file")
        fltr.add_pattern("*.xml")
        fsDlg.add_filter(fltr)
        
        res = fsDlg.run()
        file =  fsDlg.get_filename()
        fsDlg.destroy()
        if res == gtk.RESPONSE_OK:
            xml = APDBxml.APDBxml(self.db)
            print 'save tables to file ' + file + '...'
            xml.dumpToXMLFile(file)
            print 'finished!'
    
    def restoreDB (self,b):
        fsDlg = gtk.FileChooserDialog(title=None,action=gtk.FILE_CHOOSER_ACTION_OPEN,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))

        fltr = gtk.FileFilter()
        fltr.set_name("All files")
        fltr.add_pattern("*")
        fsDlg.add_filter(fltr)
        fltr = gtk.FileFilter()
        fltr.set_name("XML file")
        fltr.add_pattern("*.xml")
        fsDlg.add_filter(fltr)

        res = fsDlg.run()
        file =  fsDlg.get_filename()
        fsDlg.destroy()
        if res == gtk.RESPONSE_OK:
            xml = APDBxml.APDBxml(self.db)
            print 'clean tables ...'
            xml.cleanAllTables()
            print 'fill database with file ' + file + '...'
            xml.XMLFileToDB(file)
            print 'finished!'

    def actionImplHAL (self,b):
        dlg = uiImplMain(self.gladefile, self.db)
        dlg.run()
    
    def actionCompiler (self,b):
        dlg = uiCompiler(self.gladefile, self.db)
        dlg.run()
        
    def actionTestAP (self, b):
        dlg = uiTestAP(self.gladefile, self.db)
        dlg.run()
    
    def actionImplemntGroups(self, b):
        dlgG = uiImplGroups(self.gladefile, self.db)
        dlgG.run()
    
    def actionWavFileGen(self, b):
        uiWF = uiWavGen(self.gladefile)
        uiWF.run()

    def actionGenDoc(self,b):
        dlg = uiDocGenOption(self.gladefile)
        res = dlg.run()
        genOptions = dlg.genOptions
        if res != gtk.RESPONSE_OK:
            return
        
        
        
        fsDlg = gtk.FileChooserDialog(title='enter pdf filename to save the documentation',action=gtk.FILE_CHOOSER_ACTION_SAVE,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))

        fltr = gtk.FileFilter()
        fltr.set_name("pdf files")
        fltr.add_pattern("*.pdf")
        fsDlg.add_filter(fltr)

        fltr = gtk.FileFilter()
        fltr.set_name("All files")
        fltr.add_pattern("*")
        fsDlg.add_filter(fltr)

        res = fsDlg.run()
        fileDest =  fsDlg.get_filename()
        fsDlg.destroy()
        
        if res != gtk.RESPONSE_OK:
            return
        
        APdocgen.APdocgen_generateDoc(self.db, fileDest, genOptions)
    
    def actionGenRemoteInterface(self, b):
        dlg = uiGenAPexternalInterface(self.gladefile, self.db)
        res = dlg.run()
        
    def actionCompileAL(self, b):
        dlg = uiALcompile(self.gladefile)
        dlg.run()


class uiHALDefineFunctions (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgHALFunction') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgHALFunction_clicked'             : self.actionClose,
    
             'on_tvFunction_dlgHALFunction_cursor_changed'  : self.actionHALFunctionCurChanged,
             'on_bFAdd_dlgHALFunction_clicked'              : self.actionFuncAdd,
             'on_bFChange_dlgHALFunction_clicked'           : self.actionFuncUpdate,
             'on_bFDel_dlgHALFunction_clicked'              : self.actionFuncDel,
             
             'on_tvFParams_dlgHALFunction_cursor_changed'   : self.actionHALFunctionParamCurChanged,
             'on_bPAdd_dlgHALFunction_clicked'              : self.actionFuncParamAdd,
             'on_bPChange_dlgHALFunction_clicked'           : self.actionFuncParamUpdate,
             'on_bPDel_dlgHALFunction_clicked'              : self.actionFuncParamDel,
             
             'on_cbClass_dlgHALFunction_changed'            : self.actionParamClassChanged
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgHALFunction')

        # creating lists
        self.FunctionList = gtk.ListStore(int, int, str , str)
        self.ParameterList = gtk.ListStore(int, str, str, str, str)
        self.BasicTypes = gtk.ListStore (int, str)
        self.VariableTypes = gtk.ListStore (int, str)
        self.VariableRefTypes = gtk.ListStore (int, str)
        self.ParamClassSelction = gtk.ListStore (int, str)
                
        # getting controls
        self.eFid = self.gladeTmpl.get_widget("eFID_dlgHALFunction")
        self.eFname = self.gladeTmpl.get_widget("eFName_dlgHALFunction")
        self.eFdescr = self.gladeTmpl.get_widget("eFDescr_dlgHALFunction")
        
        self.eParamName = self.gladeTmpl.get_widget("ePName_dlgHALFunction")
        self.eParamDescr = self.gladeTmpl.get_widget("ePDescr_dlgHALFunction")
        self.cbParamClass = self.gladeTmpl.get_widget('cbClass_dlgHALFunction')
        self.cbTypeID = self.gladeTmpl.get_widget("cbType_dlgHALFunction")
        self.lTypeLabel = self.gladeTmpl.get_widget("lType_dlgHALFunction")

        self.tvFunctions = self.gladeTmpl.get_widget("tvFunction_dlgHALFunction")
        self.tvParameter = self.gladeTmpl.get_widget("tvFParams_dlgHALFunction")
        
        #create table headers
        addColumnToTable(self.tvFunctions, 'function id', 1 ,False)
        addColumnToTable(self.tvFunctions, 'name', 2 ,False)
        addColumnToTable(self.tvFunctions, 'description', 3 ,False)
        
        addColumnToTable(self.tvParameter, 'name', 1 ,False)
        addColumnToTable(self.tvParameter, 'description', 2 ,False)
        addColumnToTable(self.tvParameter, 'type class', 3 ,False)
        addColumnToTable(self.tvParameter, 'type', 4 ,False)

        # set the combobox
        cell = gtk.CellRendererText()
        self.cbParamClass.pack_start(cell, True)
        self.cbParamClass.add_attribute(cell, 'text', 1)

        self.cbTypeID.pack_start(cell, True)
        self.cbTypeID.add_attribute(cell, 'text', 1)

        #populate lists
        
        # 1. populate basic type list
        btl = self.db.HAL_basicIOTypes_getList()
        for b in btl:
            n = (b[1],b[2])
            self.BasicTypes.append (n)

        # 2. populate variable type list
        ctl = self.db.HAL_VariableDefinition_getList()
        for c in ctl:
            n = (c[1],c[2])
            self.VariableTypes.append(n)
        # 3. populate type class list
        for k,t in self.db.dFuncParamsClasses.items():
            self.ParamClassSelction.append((k, t))
        # 4. populate var ref types
        self.VariableRefTypes = self.VariableTypes
        self.VariableTypes.append((0,'not specified'))
        
        # start the dlg with the basic io types
        self.cbParamClass.set_model (self.ParamClassSelction)
        comboBoxSelectValue(self.cbParamClass, 1, 0) 

        # set the treeview models 
        self.tvFunctions.set_model (self.FunctionList)
        self.tvParameter.set_model (self.ParameterList)
        
        # set some loacl vars
        self.Fuuid = -1
        self.Puuid = -1
        
        self.updateFunctionList()
        
    def updateFunctionList(self):
        fl = self.db.HAL_DefFunctions_getList()
        self.FunctionList.clear()
        for f in fl:
            self.FunctionList.append(f)
        self.Fuuid = -1
        self.Puuid = -1

    def updateFunctionParamList(self):
        pl = self.db.HAL_DefFunctions_getParamList(self.eFid.get_text())
        self.ParameterList.clear()
        for p in pl:
            #class
            classStr = self.db.dFuncParamsClasses[p[4]]
            # type
            if p[4] == self.db.dFuncClass_basicIOtype:
                # basic io
                type = self.db.HAL_basicIOType_getNameByTypeID(p[5])
            elif p[4] == self.db.dFuncClass_refDataVar:
                vdef = self.db.HAL_VariableDefinition_getByVariableID(p[5])
                if vdef[0] == None:
                    type = 'not specified'
                else:
                    type = vdef[0][2]
            elif p[4] == self.db.dFuncClass_refVar:
                v = self.db.HAL_VariableDefinition_getByVariableID(p[5])
                if v[0] == None:
                    type = 'not specified'
                else:
                    type = v[0][2]
            else:
                type = ""
            n = (p[0], p[2], p[3], classStr,type)
            self.ParameterList.append(n)
        self.Puuid = -1

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()

    def actionHALFunctionCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.Fuuid = model.get_value(iter,0)
            self.eFid.set_text(str(model.get_value(iter,1)))
            self.eFname.set_text(model.get_value(iter,2))
            self.eFdescr.set_text(model.get_value(iter,3))
            
            self.updateFunctionParamList()
        else:
            self.Fuuid = -1
            self.Puuid = -1
        


    def actionFuncAdd(self,b):
        (res, errormsg, uuid) = self.db.HAL_DefFunctions_add(
            self.eFid.get_text(),
            self.eFname.get_text(),
            self.eFdescr.get_text()
        )
        
        if res == False:
            mb = MessageBox(
                message=errormsg,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateFunctionList()
        
    def actionFuncUpdate(self,b):
        (res, errormsg, uuid) = self.db.HAL_DefFunctions_update(
            self.Fuuid,
            self.eFid.get_text(),
            self.eFname.get_text(),
            self.eFdescr.get_text()
        )
        
        if res == False:
            mb = MessageBox(
                message=errormsg,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateFunctionList()
        
    def actionFuncDel(self,b):
        self.db.HAL_DefFunctions_delete(self.Fuuid)
        self.updateFunctionList()
        
    def actionHALFunctionParamCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()

        if iter != None:
            self.Puuid = model.get_value(iter,0)
            self.eParamName.set_text(model.get_value(iter,1))
            self.eParamDescr.set_text(model.get_value(iter,2))
            comboBoxSelectValue(self.cbParamClass,model.get_value(iter,3),1)
            comboBoxSelectValue(self.cbTypeID,model.get_value(iter,4),1)
        else:
            self.Puuid = -1

    def actionParamClassChanged(self,cb):
        iter = cb.get_active_iter()
        if iter != None:
            m = cb.get_model()
            id = m.get_value(iter,0)
            if id == self.db.dFuncClass_basicIOtype:
                self.cbTypeID.set_model (self.BasicTypes)
                self.cbTypeID.set_visible(True)
                self.lTypeLabel.set_visible(True)
                self.cbTypeID.set_active(-1)
            elif id == self.db.dFuncClass_refVar:
                self.cbTypeID.set_model (self.VariableTypes)
                self.cbTypeID.set_visible(True)
                self.lTypeLabel.set_visible(True)
                self.cbTypeID.set_active(-1)
            elif id == self.db.dFuncClass_refDataVar:
                self.cbTypeID.set_model (self.VariableRefTypes)
                self.cbTypeID.set_visible(True)
                self.lTypeLabel.set_visible(True)
                self.cbTypeID.set_active(-1)                
            elif id == self.db.dFuncClass_VarID:
                self.cbTypeID.set_model (None)
                self.cbTypeID.set_visible(False)
                self.lTypeLabel.set_visible(False)
            elif id == self.db.dFuncClass_VarIndex:
                self.cbTypeID.set_model (None)
                self.cbTypeID.set_visible(False)
                self.lTypeLabel.set_visible(False)
            

    def actionFuncParamAdd(self,b):
        (res, txt, id) = self.db.HAL_DefFunctions_addParam(
            self.eFid.get_text(),
            self.eParamName.get_text(),
            self.eParamDescr.get_text(),
            comboBoxGetValue(self.cbParamClass,0),
            comboBoxGetValue(self.cbTypeID,0)
        )
        
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateFunctionParamList()
        
    def actionFuncParamUpdate(self,b):
        (res, txt) = self.db.HAL_DefFunctions_updateParam(
            self.Puuid,
            self.eFid.get_text(),
            self.eParamName.get_text(),
            self.eParamDescr.get_text(),
            comboBoxGetValue(self.cbParamClass,0),
            comboBoxGetValue(self.cbTypeID,0)
        )
        
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateFunctionParamList()
        
    def actionFuncParamDel(self,b):
        self.db.HAL_DefFunctions_deleteParam(self.Puuid)
        self.updateFunctionParamList()

class uiHALMsgSystem (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "dlgMessageSystem") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_dlgMessageSystem_clicked" : self.actionClose,
             "on_bMsgType_dlgMessageSystem_clicked": self.actionMsgTyes,
             "on_bMsgProcess_dlgMessageSystem_clicked": self.actionMsgProc
             }
            )
        self.dlg = self.gladeTmpl.get_widget("dlgMessageSystem")
        
    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()

    def actionMsgTyes(self,b):
        dlg = uiHALMsgTypes(self.gladefile,self.db)
        dlg.run()
    
    def actionMsgProc(self,b):
        dlg = uiHALMsgProc(self.gladefile,self.db)
        dlg.run()
        
class uiHALMsgTypes (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, "dlgMessageTypes") 
        self.gladeTmpl.signal_autoconnect (
            {
             "on_bClose_dlgMessageTypes_clicked" : self.actionClose,
             "on_tvMsg_dlgMessageTypes_cursor_changed": self.actionTvMsgCurChanged,
             "on_bMsgAdd_dlgMessageTypes_clicked": self.actionMsgAdd,
             "on_bMsgChange_dlgMessageTypes_clicked": self.actionMsgUpdate,
             "on_bMsgDelete_dlgMessageTypes_clicked": self.actionMsgDelete,
             
             "on_tvParams_dlgMessageTypes_cursor_changed": self.actionMsgParamSelChanged,
             "on_bParamAdd_dlgMessageTypes_clicked" : self.actionMsgParamAdd,
             "on_bParamChange_dlgMessageTypes_clicked" : self.actionMsgParamChanged,
             "on_bParamDel_dlgMessageTypes_clicked" : self.actionMsgParamDelete,
             "on_cbParamType_dlgMessageTypes_changed" : self.actionTypeCBchanged
             }
            )
        self.dlg = self.gladeTmpl.get_widget("dlgMessageTypes")

        # creating lists
        self.MsgList = gtk.ListStore(int, int, str, str)
        self.ParamList = gtk.ListStore(int, int, int, str, str, int, str, bool)
        self.cbTypeList = gtk.ListStore(int, str)
        
        #
        self.tvMT = self.gladeTmpl.get_widget("tvMsg_dlgMessageTypes")
        addColumnToTable(self.tvMT, 'msg id', 1 ,False)
        addColumnToTable(self.tvMT, 'name', 2 ,False)
        addColumnToTable(self.tvMT, 'description', 3 ,False)
        self.tvMT.set_model(self.MsgList)
        
        self.eMsgID = self.gladeTmpl.get_widget("eMsgID_dlgMessageTypes")
        self.eName = self.gladeTmpl.get_widget("eMsgName_dlgMessageTypes")
        self.eDescr = self.gladeTmpl.get_widget("eMsgDescr_dlgMessageTypes")


        self.tvMP = self.gladeTmpl.get_widget("tvParams_dlgMessageTypes")
        addColumnToTable(self.tvMP, 'position index', 2 ,False)
        addColumnToTable(self.tvMP, 'name', 3 ,False)
        addColumnToTable(self.tvMP, 'description', 4 ,False)
        addColumnToTable(self.tvMP, 'type', 6 ,False)
        addColumnToTable(self.tvMP, 'is an array', 7 ,False)
        self.tvMP.set_model(self.ParamList)

        self.eParamPosIndx = self.gladeTmpl.get_widget("ePosIndex_dlgMessageTypes")
        self.eParamName = self.gladeTmpl.get_widget("eParamName_dlgMessageTypes")
        self.eParamDescr = self.gladeTmpl.get_widget("eParamDescr_dlgMessageTypes")
        self.cbParamType = self.gladeTmpl.get_widget("cbParamType_dlgMessageTypes")
        self.cbArray = self.gladeTmpl.get_widget("cbParamIsArray_dlgMessageTypes")

        cell = gtk.CellRendererText()
        self.cbParamType.pack_start(cell, True)
        self.cbParamType.add_attribute(cell, 'text', 1)
        self.cbParamType.set_model(self.cbTypeList)
        self.cbTypeList.clear()

        btl = self.db.HAL_basicIOTypes_getList()
        for b in btl:
            self.cbTypeList.append((b[1], b[2]))
        
        

        
        self.updateMsgTypes()
        self.updateMsgParam()
        self.typeID = -1
        
    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()

    def updateMsgTypes (self):
        ml = self.db.HAL_Msg_Type_getList()
        self.MsgList.clear()
        for l in ml:
            self.MsgList.append(l)
        self.Muuid = -1
        self.eMsgID.set_text('-1')
        self.eName.set_text('unknown')
        self.eDescr.set_text('')

    
    def updateMsgParam (self):
        self.ParamList.clear()
        msgID = int(self.eMsgID.get_text())
        mpl = self.db.HAL_msg_TypeParam_getList(msgID)
        for mp in mpl:
            n = (mp[0], mp[1], mp[2], mp[3], mp[4], mp[5], self.db.HAL_basicIOType_getTypeNameByID(mp[5]), mp[6])
            self.ParamList.append(n)
        self.Puuid = -1
        self.eParamPosIndx.set_text('-1')
        self.eParamName.set_text('unknown')
        self.eParamDescr.set_text('')
        comboBoxSelectValue(self.cbParamType,None,0)
        self.cbArray.set_active(False)

    
    def actionTvMsgCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.Muuid = model.get_value(iter,0)
            self.eMsgID.set_text(str(model.get_value(iter,1)))
            self.eName.set_text(model.get_value(iter,2))
            self.eDescr.set_text(model.get_value(iter,3))
        else:
            self.Muuid = -1
        
        self.updateMsgParam()
    
    def actionMsgParamSelChanged(self, tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.Puuid = model.get_value(iter,0)
            self.eParamPosIndx.set_text(str(model.get_value(iter,2)))
            self.eParamName.set_text(model.get_value(iter,3))
            self.eParamDescr.set_text(model.get_value(iter,4))
            comboBoxSelectValue(self.cbParamType,model.get_value(iter,5),0)
            self.cbArray.set_active(model.get_value(iter,7))
        else:
            self.Puuid = -1
        
    
    def actionMsgAdd(self,b):
        (res, txt, id) = self.db.HAL_Msg_Type_add(
            self.eMsgID.get_text(),
            self.eName.get_text(),
            self.eDescr.get_text()
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateMsgTypes()

    def actionMsgUpdate(self,b):
        (res, txt, id) = self.db.HAL_Msg_Type_change(
            self.Muuid,                                     
            self.eMsgID.get_text(),
            self.eName.get_text(),
            self.eDescr.get_text()
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateMsgTypes()

    def actionMsgDelete(self,b):
        self.db.HAL_Msg_Type_delete(self.Muuid)
        self.updateMsgTypes()
 
    def actionTypeCBchanged(self,cb):
        iter = cb.get_active_iter()
        if iter != None:
            m = cb.get_model()
            self.typeID = m.get_value(iter,0)

 
    def actionMsgParamAdd(self, b):
        (res, txt, id) = self.db.HAL_msg_TypeParam_addParam(
            self.eMsgID.get_text(),
            self.eParamPosIndx.get_text(),
            self.eParamName.get_text(),
            self.eParamDescr.get_text(),
            self.typeID,
            self.cbArray.get_active()
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateMsgParam()
        
    def actionMsgParamChanged (self, b):
        (res, txt, id) = self.db.HAL_msg_TypeParam_changeParam(
            self.Puuid,
            self.eMsgID.get_text(),
            self.eParamPosIndx.get_text(),
            self.eParamName.get_text(),
            self.eParamDescr.get_text(),
            self.typeID,
            self.cbArray.get_active()
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.updateMsgParam()
        
    def actionMsgParamDelete (self, b):
        self.db.HAL_msg_TypeParam_deleteParam(self.Puuid)
        self.updateMsgParam()


class uiHALMsgProc (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgMessageProcess') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgMessageProcess_clicked'              : self.actionClose,
             'on_tvMsgProc_dlgMessageProcess_cursor_changed'    : self.actionTvMsgProcCurChanged,
             'on_bAddMsgProc_dlgMessageProcess_clicked'         : self.actionMsgProcAdd,
             'on_bChangeMsgProc_dlgMessageProcess_clicked'      : self.actionMsgProcUpdate,
             'on_bDelMsgProc_dlgMessageProcess_clicked'         : self.actionMsgProcDelete,
             'on_bSyntaxCheck_dlgMessageProcess_clicked'        : self.actionMsgProcCheck,
             'on_cbIsRX_dlgMessageProcess_toggled'              : self.actionRXtoggled
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgMessageProcess')

        # creating lists
        self.ProcList = gtk.ListStore(int, str, str, str, bool, str)
        # left side
        self.tvMP = self.gladeTmpl.get_widget('tvMsgProc_dlgMessageProcess')
        addColumnToTable(self.tvMP, 'message process id', 1 ,False)
        addColumnToTable(self.tvMP, 'process name', 2 ,False)
        addColumnToTable(self.tvMP, 'description', 3 ,False)
        self.tvMP.set_model(self.ProcList)
        
        self.cbRXProc = self.gladeTmpl.get_widget('cbRXmessage_dlgMessageProcess')
        self.lRXProc = self.gladeTmpl.get_widget('lMsgProcID_dlgMessageProcess')
        
        #create list for the combobox
        self.lsMsg = gtk.ListStore( int, str)
        self.cbRXProc.set_model(self.lsMsg)
        cell = gtk.CellRendererText()
        self.cbRXProc.pack_start(cell, True)
        self.cbRXProc.add_attribute(cell, 'text', 1)
        
        self.eProcName = self.gladeTmpl.get_widget('eMsgProcName_dlgMessageProcess')
        self.eProcDescr = self.gladeTmpl.get_widget('eMsgProcDescr_dlgMessageProcess')
        self.cbIsRX = self.gladeTmpl.get_widget('cbIsRX_dlgMessageProcess')

        #right side
        self.codeBuffer = gtk.TextBuffer()
        self.tvMPAction = self.gladeTmpl.get_widget('tvMsgProcCode_dlgMessageProcess')
        self.tvMPAction.set_buffer(self.codeBuffer)

        # populate msg type list
        msgTL = self.db.HAL_Msg_Type_getList()
        for m in msgTL:
            self.lsMsg.append((m[1], m[2]))
        
        self.buildMsgProcTable()

        # uncheck toggle button
        self.cbIsRX.set_active(False)
        self.cbRXProc.hide()
        self.lRXProc.hide()

        # set uuid's
        self.MPuuid = -1

    def buildMsgProcTable(self):
        self.ProcList.clear()
        mpl = self.db.HAL_msg_Process_getList()
        for mp in mpl:
            if False == mp[4]:
                e = (mp[0], 'none', mp[2], mp[3], mp[4], mp[5])
            else:
                e = (mp[0], str(mp[1]), mp[2], mp[3], mp[4], mp[5])
            self.ProcList.append(e)
        self.MPuuid = -1

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    def actionTvMsgProcCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            rxFlag = model.get_value(iter,4)
            self.MPuuid = model.get_value(iter,0)
            self.eProcName.set_text(model.get_value(iter,2))
            self.eProcDescr.set_text(model.get_value(iter,3))
            self.cbIsRX.set_active(rxFlag)
            self.codeBuffer.set_text(model.get_value(iter,5))
            # check rx
            if rxFlag == True:
                self.cbRXProc.show()
                self.lRXProc.show()
                msgId = int(model.get_value(iter,1))
                comboBoxSelectValue(self.cbRXProc, msgId, 0)
            else:
                self.cbRXProc.hide()
                self.lRXProc.hide()
        else:
            self.MPuuid = -1
            
    def actionMsgProcAdd(self,b):
        (res, txt, id) = self.db.HAL_msg_Process_add(
            comboBoxGetValue(self.cbRXProc, 0),
            self.eProcName.get_text(),
            self.eProcDescr.get_text(),
            self.cbIsRX.get_active(),
            getTextBufferCompleteText(self.codeBuffer)
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildMsgProcTable()

    def actionMsgProcUpdate(self,b):
        (res, txt, id) = self.db.HAL_msg_Process_change(
            self.MPuuid,
            comboBoxGetValue(self.cbRXProc, 0),
            self.eProcName.get_text(),
            self.eProcDescr.get_text(),
            self.cbIsRX.get_active(),
            getTextBufferCompleteText(self.codeBuffer)
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildMsgProcTable()

    def actionMsgProcDelete(self,b):
        self.db.HAL_msg_Process_delete(self.MPuuid)
        self.buildMsgProcTable()
             
    def actionMsgProcCheck(self,b):
        msgCode = getTextBufferCompleteText(self.codeBuffer)
        print msgCode
        gm = APmsgProcessCompilier.MsgProcessGrammar(False)
        res = gm.translate(msgCode)
        print res
    
    def actionRXtoggled(self, checkBox):
        if True == checkBox.get_active():
            self.cbRXProc.show()
            self.lRXProc.show()
        else:
            self.cbRXProc.hide()
            self.lRXProc.hide()
            


class uiAPsetup (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.cg = codeGen.codeGenerator(db,'')

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgAP') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgAP_clicked'              : self.actionClose,
             'on_tvAP_dlgAP_cursor_changed'         : self.actionAPtvCurChanged,
             'on_bNew_dlgAP_clicked'                : self.actionNew,
             'on_bChange_dlgAP_clicked'             : self.actionChange,
             'on_bDelete_dlgAP_clicked'             : self.actionDelete,
             'on_bVariableTypes_dlgAP_clicked'      : self.actionImplVars,
             'on_bHALFunctions_dlgAP_clicked'       : self.actionImplFunc,
             'on_bAP_dlgAP_clicked'                 : self.actionImplAP,
             'on_bMsgDriver_dlgAP_clicked'          : self.actionImplDrv,
             'on_cbCompiler_dlgAP_changed'          : self.actionCompChanged,
             'on_bGenAP_dlgAP_clicked'              : self.actionGenAP,
             'on_bAP_setupStartCode_clicked'        : self.actionStartCode
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgAP')

        # creating lists
        self.APList = gtk.ListStore(int, str, int, str, int)
        # left side
        self.tvMP = self.gladeTmpl.get_widget('tvAP_dlgAP')
        addColumnToTable(self.tvMP, 'AP name', 1 ,False)
        addColumnToTable(self.tvMP, 'description', 3 ,False)

        self.tvMP.set_model(self.APList)
        
        self.eAPName = self.gladeTmpl.get_widget('eAPName_dlgAP')
        
        self.eAPDescr = self.gladeTmpl.get_widget('eDescr_dlgAP')

        #create list for the combobox
        self.CompilerList = gtk.ListStore( int, str)
        
        self.cbCompiler = self.gladeTmpl.get_widget('cbCompiler_dlgAP')
        
        self.cbCompiler.set_model(self.CompilerList)
        cell = gtk.CellRendererText()
        self.cbCompiler.pack_start(cell, True)
        self.cbCompiler.add_attribute(cell, 'text', 1)

        self.uuidAP = None
        self.uuidCompiler = None

        self.buildAPTable()
        self.buildCompilerList()


    def buildAPTable(self):
        self.APList.clear()
        apl = self.db.AP_getList()
        for ap in apl:
            if ap[4] == None :
                scid = -1
            else:
                scid = ap[4]
            t = (ap[0], ap[1], ap[2], ap[3], scid)
            self.APList.append(t)
            
        self.uuidAP = None
        self.uuidCompiler = None

    def buildCompilerList(self):
        self.CompilerList.clear()
        cl = self.db.Comp_Compiler_getList()
        for c in cl:
            self.CompilerList.append((c[0],c[1]))


    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    def actionAPtvCurChanged(self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuidAP = model.get_value(iter,0)
            self.eAPName.set_text(model.get_value(iter,1))
            self.eAPDescr.set_text(model.get_value(iter,3))
        
            self.uuidCompiler = model.get_value(iter,2)
            comboBoxSelectValue(self.cbCompiler,self.uuidCompiler,0)
        else:
            self.uuidAP = None
            self.uuidCompiler = None
    
    def actionNew(self,b):
        (res, txt, id) = self.db.AP_add(
                    self.eAPName.get_text(),
                    self.eAPDescr.get_text(),
                    self.uuidCompiler
                )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildAPTable()

    def actionChange(self,b):
        if self.uuidAP == None:
            return
        
        (res, txt, id) = self.db.AP_change(
                self.uuidAP,
                self.eAPName.get_text(),
                self.eAPDescr.get_text(),
                self.uuidCompiler
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildAPTable()

    def actionDelete(self,b):
        if self.uuidAP == None:
            return

        self.db.AP_delete(self.uuidAP)
        self.buildAPTable()
    
    def actionImplVars(self,b):
        if None == self.uuidAP:
            return
        dlg = uiAPsetupGroup (self.gladefile, self.db,
                              self.uuidAP,
                              'variable ID', 'HAL_VariableDefinition',2, 'VariableID' ,
                              'ImplHALVariable', 'VariableList'
                              )
        dlg.run()
    
    def actionImplFunc(self,b):
        if None == self.uuidAP:
            return
        dlg = uiAPsetupGroup (self.gladefile, self.db,
                              self.uuidAP,
                              'function ID', 'HAL_Function',2, 'fid' ,
                              'ImplHALFunction', 'FunctionList'
                              )
        dlg.run()
    

    def actionImplAP(self,b):
        if None == self.uuidAP:
            return
        dlg = uiAPsetupGroup (self.gladefile, self.db,
                              self.uuidAP,
                              None, None,None, None,
                              'ImplAP', 'APList'
                              )
        dlg.run()
        
    def actionImplDrv(self,b):
        if None == self.uuidAP:
            return
        dlg = uiAPsetupGroup (self.gladefile, self.db,
                              self.uuidAP,
                              None, None,None, None,
                              'ImplMsgDriver', 'DriverList'
                              )
        dlg.run()

    def actionCompChanged(self, cb):
        iter = cb.get_active_iter()
        if iter != None:
            self.uuidCompiler = self.CompilerList.get_value(iter,0)

    def actionGenAP(self,b):
        if None == self.uuidAP:
            return
        
        dlg = uiCodeGenOptions(self.gladefile);
        res = dlg.run()
        options = dlg.options
        if res != gtk.RESPONSE_OK:
            return
        
        
        setWaitCursor(self.dlg)
        
        # create code generator 
        cg = codeGen.codeGenerator(self.db,'code')
        
        # generate code
        res = cg.generateAP(self.uuidAP,options['C89'], options['debug'])
        if (res == False):
            setStdCursor(self.dlg)
            print ('generating AP failed')
            return
        # copy AL binary file or c-file to the dir
        ALfilepath,ALfilepathExt = os.path.splitext(options['eALFile'])

        if ALfilepathExt == '.c':
            extraCopyFiles = [options['eALFile'], ALfilepath + '.h']
            p, f = os.path.split(options['eALFile'])
            extraFiles = [os.path.join(cg.workingPath,f)]
        elif ALfilepathExt == '.alasm':
            extraCopyFiles = [options['eALFile']]
            extraFiles = []
        else:
            extraCopyFiles = []
            extraFiles = []
        
        for f in extraCopyFiles:
            srcP, file = os.path.split(f)
            dest = os.path.join(cg.workingPath, file)
            shutil.copyfile(f, dest)
        
        print extraFiles
        
        print ('generating code finished')
        
        toolchainDict = {
            'scons' :   apBuilder.APbuilderScons,
            'c':        apBuilder.APbuilderUserShell,
            'cmd' :     apBuilder.APbuilderCmdLineScript            
        }

        builderTemplate = toolchainDict.get(options['toolChain'], None) 
        
        if builderTemplate == None:
            setStdCursor(self.dlg)
            return
        
        # save lib list
        libL = res[1]
        # create builder
        b = apBuilder.APbuilder(self.db,'templ/SConstruct.py')
        # execute
        b.buildAP(self.uuidAP, libL, cg.workingPath, [cg.getAPSourceFile(),cg.getAPmainSourceFile()]+extraFiles, builderTemplate)
        setStdCursor(self.dlg)
        print ('builder finished')
        
    def actionStartCode (self, cb):
        if None == self.uuidAP:
            return
        values = self.db.AP_get(self.uuidAP)
        
        if ((values[4] == None) or (values[4] == -1)):
            cg = codeGen.codeGenerator(self.db,'code')
            (inclL, cCode ) = cg.UIgenStartUpCode()
            codeID = self.db.Code_createCode (cCode)
            for incl in inclL:
                self.db.Code_createInclude (codeID, incl[0],incl[1],incl[2])
            self.db.AP_setStartupCode(self.uuidAP, codeID)
        else :
            codeID = values[4]
        dlg = uiCodeEntry(self.gladefile, self.db, codeID)
        dlg.run()

class uiAPsetupGroup (object):
    # pool list format
    def __init__(self, gladeFile,db, uuidAP, halIDFieldName, halTableName, halTableNameIndex, halTableIDFieldName ,implTableName, selectTableName):
        self.db = db

        self.uuidAP = uuidAP
        self.halIDFieldName = halIDFieldName
        self.halTableName = halTableName
        self.implTableName = implTableName
        self.halTableNameIndex = halTableNameIndex
        self.halTableIDFieldName = halTableIDFieldName
        self.selectTableName = selectTableName
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgAPsetupModuleGroup') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgAPsetupModuleGroup_clicked'          : self.actionClose,
             'on_tvPool_dlgAPsetupModuleGroup_cursor_changed'   : self.actionPoolSel,
             'on_tvSelc_dlgAPsetupModuleGroup_cursor_changed'   : self.actionSelcSel,
             'on_bAddElement_dlgAPsetupModuleGroup_clicked'     : self.actionAddEle,
             'on_bAddGroup_dlgAPsetupModuleGroup_clicked'       : self.actionAddGroup,
             'on_bRemGroup_dlgAPsetupModuleGroup_clicked'       : self.actionRemGroup,
             'on_bRemElement_dlgAPsetupModuleGroup_clicked'     : self.actionRemEle
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgAPsetupModuleGroup')
        self.tvPool = self.gladeTmpl.get_widget('tvPool_dlgAPsetupModuleGroup')
        self.tvSelc = self.gladeTmpl.get_widget('tvSelc_dlgAPsetupModuleGroup')

        # creating lists
        # layout
        # uuid |  hal id | group id | name | descr | group name
        self.PoolList = gtk.ListStore(int, int, int, str, str, str)
        self.SelcList = gtk.ListStore(int, int, int, str, str, str)
        # set models
        self.tvPool.set_model(self.PoolList)
        self.tvSelc.set_model(self.SelcList)
            
        if self.halIDFieldName != None:
            addColumnToTable(self.tvPool, self.halIDFieldName, 1 ,False)
            addColumnToTable(self.tvSelc, self.halIDFieldName, 1 ,False)
            addColumnToTable(self.tvPool, 'name', 3 ,False)
            addColumnToTable(self.tvSelc, 'name', 3 ,False)
        
        addColumnToTable(self.tvPool, 'description', 4 ,False)
        addColumnToTable(self.tvSelc, 'description', 4 ,False)
        
        addColumnToTable(self.tvPool, 'group', 5 ,False)
        addColumnToTable(self.tvSelc, 'group', 5 ,False)

        # build pool table
        self.PoolList.clear()
        
        # get impl table
        pL = self.db.generic_getList(self.implTableName,self.halTableIDFieldName)
        
        for e in pL:
            if self.halIDFieldName != None:
                id = e[1]
                typL = self.db.generic_getByValue(self.halTableName, self.halTableIDFieldName,id)
                name = typL[0][self.halTableNameIndex]
                descr = e[3]
                gn = self.getGroupNameFromPoolListElement(e,4)
                gnr = e[4]
            else:
                id = 0
                name = ''
                descr = e[2]
                gn = self.getGroupNameFromPoolListElement(e,3)
                gnr = e[3]
            
            
            x = (e[0], id, gnr, name, descr, gn)
            
            self.PoolList.append(x)

        self.buildSelecList()

        self.poolUUID = None
        self.selcUUID = None
        self.poolGroupID = None
        self.selcGroupID = None
    
    def findImplUUIDinPoollist (self, uuid):
        for e in self.PoolList:
            if e[0] == uuid:
                return e
        return None

    def getGroupNameFromPoolListElement (self,e, gidIndex):
        gn = self.db.Impl_Group_get(e[gidIndex])
        if gn != None:
            gn = gn[1]
        else:
            gn = 'not assigned'
        return gn
    
    def buildSelecList(self):
        self.SelcList.clear()
        el = self.db.AP_implTable_getList (self.selectTableName, self.uuidAP)
        for e in el:
            # find element in pool list
            pe = self.findImplUUIDinPoollist(e[2])
            self.SelcList.append(pe)
        self.selcUUID = None
        self.selcGroupID = None

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()

    def actionPoolSel (self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.poolUUID = model.get_value(iter,0)
            self.poolGroupID = model.get_value(iter,2)
        else:
            self.poolUUID = None
            self.poolGroupID = None

    def actionSelcSel (self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.selcUUID = model.get_value(iter,0) 
            self.selcGroupID = model.get_value(iter,2)
        else:
            self.selcUUID = None
            self.selcGroupID = None

    def actionAddEle(self,b):
        if self.poolUUID == None:
            return
        (res, txt, id) = self.db.AP_implTable_add(self.selectTableName,self.implTableName,self.uuidAP, self.poolUUID)
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildSelecList()

    def actionRemEle(self,b):
        print (str(self.selectTableName))
        if self.selcUUID == None:
            return
        self.db.AP_implTable_deleteImplRef(self.selectTableName, self.implTableName,self.uuidAP, self.selcUUID)
        self.buildSelecList()

    def actionAddGroup(self,b):
        if self.poolGroupID == None:
            return
        # get group id
        iL = self.db.generic_getByValue (self.implTableName,'idImplGroup',self.poolGroupID)
        # iterate through list and add
        for i in iL:
             (res, txt, id) = self.db.AP_implTable_add(self.selectTableName,self.implTableName,self.uuidAP, i[0])
        self.buildSelecList()
    
    def actionRemGroup(self,b):
        if self.selcGroupID == None:
            return
        # get group id
        iL = self.db.generic_getByValue (self.implTableName,'idImplGroup',self.selcGroupID)
        for i in iL:
            # get the uuid of the entries with the implUUID
            self.db.AP_implTable_deleteImplRef(self.selectTableName,self.implTableName,self.uuidAP,i[0])
        self.buildSelecList()
    
class uiImplMain (object):
    def __init__(self, gladeFile,db):
        self.db = db
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlg_Impl') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlg_Impl_clicked'       : self.actionClose,
             'on_bFunc_dlg_Impl_clicked'        : self.actionFunc,
             'on_bVar_dlg_Impl_clicked'         : self.actionVar,
             'on_bMsgDriver_dlg_Impl_clicked'   : self.actionMsgDrv,
             'on_bAP_dlg_Impl_clicked'          : self.actionAP
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlg_Impl')

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    
    def actionFunc(self,b):
        cg = codeGen.codeGenerator(self.db,'')
        igDlg = uiImplGeneric(
                 self.gladefile,
                 self.db,
                 self.db.HAL_DefFunctions_getList(),
                 1,
                 'function ID',
                 2,
                 'ImplHALFunction',
                 'fID',
                 cg.UIgenFunc,
                 'FunctionList'
                )
        igDlg.run()

    def actionVar(self,b):
        cg = codeGen.codeGenerator(self.db,'')
        igDlg = uiImplGeneric(
                 self.gladefile,
                 self.db,
                 self.db.HAL_VariableDefinition_getList(),
                 1,
                 'variable ID',
                 2,
                 'ImplHALVariable',
                 'VariableID',
                 cg.UIgenVar,
                 'VariableList'
                )
        igDlg.run()

    def actionMsgDrv(self,b):
        cg = codeGen.codeGenerator(self.db,'')
        igDlg = uiImplGeneric(
                 self.gladefile,
                 self.db,
                 None,
                 None,
                 None,
                 None,
                 'ImplMsgDriver',
                 None,
                 cg.UIgenMsgDrvEmptyFunctions,
                 'DriverList'
                )
        igDlg.run()

    def actionAP(self,b):
        cg = codeGen.codeGenerator(self.db,'')
        igDlg = uiImplGeneric(
                 self.gladefile,
                 self.db,
                 None,
                 None,
                 None,
                 None,
                 'ImplAP',
                 None,
                 cg.UIgenAPemptyFunctions,
                 'APList'
                )
        igDlg.run()
    
class uiImplGroups (object):
    def __init__(self, gladeFile,db):
        self.db = db
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgGroups') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgGroups_clicked'      : self.actionClose,
             'on_tvG_dlgGroups_cursor_changed'  : self.actionTVchanged,
             'on_bAdd_dlgGroups_clicked'        : self.actionAdd,
             'on_bchange_dlgGroups_clicked'     : self.actionUpdate,
             'on_bdel_dlgGroups_clicked'        : self.actionDel,
             'on_bCode_dlgGroups_clicked'       : self.actionCode
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgGroups')
        self.tvGroup = self.gladeTmpl.get_widget('tvG_dlgGroups')
        self.GroupList = gtk.ListStore( int, str, int)
        self.eGN = self.gladeTmpl.get_widget('eGN_dlgGroups')
        
        addColumnToTable(self.tvGroup, 'name', 1 ,False)
        self.tvGroup.set_model(self.GroupList)
        
        self.buildGroupTable()

        self.uuid = None
        self.codeID = None

        
    def buildGroupTable (self):
        gl = self.db.Impl_Group_getList()
        self.GroupList.clear()
        for g in gl:
            # skip all unimplement groups
            if (g[2] != None): 
                self.GroupList.append(g)
        self.uuid = None
    
    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    def actionTVchanged (self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuid = model.get_value(iter,0)
            self.eGN.set_text(str(model.get_value(iter,1)))
            self.codeID = model.get_value(iter,2)
        else:
            self.uuid = None
            self.codeID = None

    def actionAdd (self,b):
        (res, txt, id) = self.db.Impl_Group_add(self.eGN.get_text(),'')
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildGroupTable()

    def actionUpdate (self,b):
        if self.uuid == None:
            return
        (res, txt, id) = self.db.Impl_Group_update(self.uuid,self.eGN.get_text(),None)
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        self.buildGroupTable()

    def actionDel (self,b):
        if self.uuid == None:
            return
        self.db.Impl_Group_delete(self.uuid)
        self.buildGroupTable()
    
    def actionCode (self,b):
        if self.codeID != None:
            dlg = uiCodeEntry(self.gladefile, self.db, self.codeID)
            dlg.run ()
        
class uiImplGeneric (object):
    def __init__(self,
                 gladeFile,
                 db,
                 HALDBList,
                 HALidFieldIndex,
                 HalIDname,
                 HALnameFieldIndex,
                 ImplTableName,
                 ImplTableIDfield,
                 codeTmplFunction,
                 APRefTable
            ):
        self.db = db
        
        self.HALDBList = HALDBList
        self.HALidFieldIndex = HALidFieldIndex
        self.ImplTableName = ImplTableName
        self.ImplTableIDfield = ImplTableIDfield
        self.HALnameFieldIndex = HALnameFieldIndex
        
        self.codeGenFunction = codeTmplFunction
        
        self.APRefTable = APRefTable
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgImplGroup') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgImplGroup_clicked'           : self.actionClose,
             'on_bAdd_dlgImplGroup_clicked'             : self.actionAdd,
             'on_bChange_dlgImplGroup_clicked'          : self.actionUpdate,
             'on_bDel_dlgImplGroup_clicked'             : self.actionDel,
             'on_tvImpl_dlgImplGroup_cursor_changed'    : self.actionTVchanged,
             'on_bCode_dlgImplGroup_clicked'            : self.actionEditCode,
             'on_bDefGroup_dlgImplGroup_clicked'        : self.actionGroup
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgImplGroup')
        # get controls
        self.tvImpl = self.gladeTmpl.get_widget('tvImpl_dlgImplGroup')
        self.cbGroup = self.gladeTmpl.get_widget('cbGroup_dlgImplGroup')
        self.lHalID = self.gladeTmpl.get_widget('lHALdef_dlgImplGroup')
        self.cbHalID = self.gladeTmpl.get_widget('cbHALdef_dlgImplGroup')
        self.eDescr = self.gladeTmpl.get_widget('eDescr_dlgImplGroup')
        
        if (HalIDname != None):
            self.lHalID.set_label(HalIDname)
        else:
            self.lHalID.set_label('')
        
        # build treeview models an cb list
        if self.HALDBList == None:
            self.ImplList = gtk.ListStore( int, str , str, int)
            addColumnToTable(self.tvImpl, 'description', 1 ,False)
            addColumnToTable(self.tvImpl, 'group', 2 ,False)
            self.lHalID.set_visible(False)
            self.cbHalID.set_visible(False)
        else:
            self.ImplList = gtk.ListStore( int, int, str, str, str, int)
            addColumnToTable(self.tvImpl, HalIDname, 1 ,False)
            addColumnToTable(self.tvImpl, 'name', 2 ,False)
            addColumnToTable(self.tvImpl, 'description', 3 ,False)
            addColumnToTable(self.tvImpl, 'group', 4 ,False)
            
        self.tvImpl.set_model(self.ImplList)

        self.HALlist = gtk.ListStore( int, str)
        cell = gtk.CellRendererText()
        self.cbHalID.pack_start(cell, True)
        self.cbHalID.add_attribute(cell, 'text', 1)
        self.cbHalID.set_model(self.HALlist)

        # set up group combo box
        self.GroupList = gtk.ListStore( int, str)
        cell = gtk.CellRendererText()
        self.cbGroup.pack_start(cell, True)
        self.cbGroup.add_attribute(cell, 'text', 1)
        self.cbGroup.set_model(self.GroupList)
        
        self.buildImplTable()
        self.buildHalCB()
        self.buildGroupCB()

        self.uuid = None
        self.codeID = None
    
    def getHALelement (self, eID):
        for h in self.HALDBList:
            if h[self.HALidFieldIndex] == eID:
                return h
        return None

    def buildImplTable(self):
        self.ImplList.clear()
        implL = self.db.generic_getList(self.ImplTableName,self.ImplTableIDfield)
        for i in implL:
            if self.HALDBList == None:
                if (i[3] == None):
                    g = 'not assigned'
                else:
                    g = self.db.Impl_Group_get(i[3])[1]
                self.ImplList.append ((i[0], i[2], g, i[1]))
            else:
                h = self.getHALelement(i[1])
                if (i[4] == None):
                    g = 'not assigned'
                else:
                    g = self.db.Impl_Group_get(i[4])[1]
                if h == None:
                    fname = 'unknown HAL function id (%d)' % (i[1],)
                else:
                    fname = h[self.HALnameFieldIndex]
                self.ImplList.append ((i[0], i[1], fname, i[3] ,g , i[2]))
        
        self.uuid = None
        self.codeID = None
        

    def buildHalCB(self):
        if self.HALDBList == None:
            return
        self.HALlist.clear()
        for h in self.HALDBList:
            self.HALlist.append((h[self.HALidFieldIndex],'[' + str(h[self.HALidFieldIndex]) + '] ' +h[self.HALnameFieldIndex]))
        self.cbHalID.set_active(-1)
        
    def buildGroupCB (self):
        gl = self.db.Impl_Group_getList()
        self.GroupList.clear()
        #self.GroupList.append((0,'no group'))
        for g in gl:
            self.GroupList.append((g[0], g[1]))
        self.cbGroup.set_active(-1)

    
    
    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    def actionTVchanged (self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuid = model.get_value(iter,0)
            if self.HALDBList == None:
                self.eDescr.set_text(str(model.get_value(iter,1)))
                self.codeID = model.get_value(iter,3)
                comboBoxSelectValue(self.cbGroup, model.get_value(iter,2), 1)
            else:
                self.eDescr.set_text(str(model.get_value(iter,3)))
                self.codeID = model.get_value(iter,5)
                comboBoxSelectValue(self.cbHalID, model.get_value(iter,1), 0)
                comboBoxSelectValue(self.cbGroup, model.get_value(iter,4), 1)
        else:
            self.eDescr.set_text('')
            self.cbGroup.set_active(-1)
            self.uuid = None
            self.codeID = None

    def actionAdd (self,b):
        if self.HALDBList == None:
            # we will generate the code with the uuid parameter
            halID = None
            codeTmpl = (None,'')
        else:
            halID = comboBoxGetValue(self.cbHalID, 0)
            codeTmpl = self.codeGenFunction(halID)

        (res, txt, id) = self.db.Impl_add (
                self.ImplTableName,
                codeTmpl[1],
                self.eDescr.get_text(),
                self.ImplTableIDfield,
                halID,
                comboBoxGetValue(self.cbGroup, 0)
            )
 
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        #if this is an non HAL implementation we will create the code with the uuid
        if self.HALDBList == None:
            codeTmpl = self.codeGenFunction(id[0])
            e = self.db.generic_get(self.ImplTableName,id[0])
            codeID = e[1]
            self.db.Code_updateCode(codeID,codeTmpl[1])
        
        # set the includes
        e = self.db.generic_get(self.ImplTableName,id[0])
        if self.HALDBList == None:
            codeID = e[1]
        else :
            codeID = e[2]
        for i in  codeTmpl[0]:
            self.db.Code_createInclude (codeID,i[0],i[1],i[2])
            
        # rebuild table
        self.buildImplTable()

    def actionUpdate (self,b):
        if self.uuid == None:
            return
        if self.HALDBList == None:
            halID = None
        else:
            halID = comboBoxGetValue(self.cbHalID, 0)
        
        self.db.Impl_update (
                self.ImplTableName,
                self.uuid,
                None,
                self.eDescr.get_text(),
                self.ImplTableIDfield,
                halID,
                False,
                comboBoxGetValue(self.cbGroup, 0)
            )
        self.buildImplTable()

    def actionDel (self,b):
        if self.uuid == None:
            return
        self.db.Impl_delete(self.ImplTableName, self.uuid, self.APRefTable)
        self.buildImplTable()
    
    def actionEditCode (self,b):
        if self.codeID != None:
            cdlg = uiCodeEntry(self.gladefile,self.db,self.codeID)
            cdlg.run()
        
            
    def actionGroup (self,b):
        dlgG = uiImplGroups(self.gladefile, self.db)
        dlgG.run()
        # save old selection
        gID = comboBoxGetValue(self.cbGroup, 0)
        # rebuild list
        self.buildGroupCB()
        # rebuild table
        self.buildImplTable()
        # set old selection
        comboBoxSelectValue(self.cbGroup, gID, 0)

class uiCompiler (object):
    def __init__(self, gladeFile,db):
        self.db = db
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgCompilerList') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgCompilerList_clicked'                : self.actionClose,
             'on_tvCompiler_dlgCompilerList_cursor_changed'     : self.actionCompCursorChanged,
             'on_bAdd_dlgCompilerList_clicked'                  : self.actionAddComp,
             'on_bChange_dlgCompilerList_clicked'               : self.actionChangeComp,
             'on_bDelete_dlgCompilerList_clicked'               : self.actionDelComp,
             'on_tvLibs_dlgCompilerList_cursor_changed'         : self.actionLibCursorChanged,
             'on_bLibAdd_dlgCompilerList_clicked'               : self.actionLibAdd,
             'on_bLibChange_dlgCompilerList_clicked'            : self.actionLibChange,
             'on_bLibDelete_dlgCompilerList_clicked'            : self.actionLibDelete,
             'on_tvLibPath_dlgCompilerList_cursor_changed'      : self.actionLibpathCursorChanged,
             'on_bLibAddPath_dlgCompilerList_clicked'           : self.actionLibpathAdd,
             'on_bLibChangePath_dlgCompilerList_clicked'        : self.actionLibpathChange,
             'on_bLibDeletePath_dlgCompilerList_clicked'        : self.actionLibpathDelete,
             'on_tvInclPath_dlgCompilerList_cursor_changed'     : self.actionIncludepathCursorChanged,
             'on_bLibAddIncludePath_dlgCompilerList_clicked'    : self.actionIncludepathAdd,
             'on_bLibChangeIncludePath_dlgCompilerList_clicked' : self.actionIncludepathChange,
             'on_bLibDeleteIncludePath_dlgCompilerList_clicked' : self.actionIncludepathDelete,
             
             }
            )
        # dlg control
        self.dlg = self.gladeTmpl.get_widget('dlgCompilerList')

        # tree views
        self.tvCList = self.gladeTmpl.get_widget('tvCompiler_dlgCompilerList')
        self.tvLibList = self.gladeTmpl.get_widget('tvLibs_dlgCompilerList')
        self.tvLibpathList = self.gladeTmpl.get_widget('tvLibPath_dlgCompilerList')
        self.tvIncludeList = self.gladeTmpl.get_widget('tvInclPath_dlgCompilerList')

        # edit fields
        self.eName = self.gladeTmpl.get_widget('eName_dlgCompilerList')
        self.eDescription = self.gladeTmpl.get_widget('eDescr_dlgCompilerList')
        self.eOperatingSystem = self.gladeTmpl.get_widget('eOS_dlgCompilerList')
        self.eCC = self.gladeTmpl.get_widget('eCC_dlgCompilerList')
        self.eCXX = self.gladeTmpl.get_widget('eCXX_dlgCompilerList')
        self.eASM = self.gladeTmpl.get_widget('eASM_dlgCompilerList')
        self.eAR = self.gladeTmpl.get_widget('eAR_dlgCompilerList')
        self.eLINK = self.gladeTmpl.get_widget('eLink_dlgCompilerList')
        self.eCCFLAGS = self.gladeTmpl.get_widget('eCCFLAGS_dlgCompilerList')
        self.eOBJSUFFIX = self.gladeTmpl.get_widget('eOBJSUFFIX_dlgCompilerList')
        self.eCCCOM = self.gladeTmpl.get_widget('eCCCOM_dlgCompilerList')
        self.eCXXCOM = self.gladeTmpl.get_widget('eCXXCOM_dlgCompilerList')
        self.eCXXFLAGS = self.gladeTmpl.get_widget('eCXXFLAGS_dlgCompilerList')
        self.eLINKCOM = self.gladeTmpl.get_widget('eLINKCOM_dlgCompilerList')
        self.eLINKFLAGS = self.gladeTmpl.get_widget('eLINKFLAGS_dlgCompilerList')

        self.eLib = self.gladeTmpl.get_widget('eLib_dlgCompilerList')
        self.eLibpath = self.gladeTmpl.get_widget('eLibPath_dlgCompilerList')
        self.eIncludepath = self.gladeTmpl.get_widget('eIncludePaths_dlgCompilerList')

        # storage for the data
        self.CList = gtk.ListStore(int,str,str,str,str,str,str,str,str,str,str,str,str,str,str,str)
        self.libList = gtk.ListStore(int,int,str)
        self.libpathList = gtk.ListStore(int,int,str)
        self.includePathList = gtk.ListStore(int,int,str)
        
        # table headers
        
        # compiler table
        addColumnToTable(self.tvCList,'name' , 1 ,False)
        addColumnToTable(self.tvCList,'description' , 2 ,False)
        addColumnToTable(self.tvCList,'operating system' , 3 ,False)
        self.tvCList.set_model(self.CList)

        addColumnToTable(self.tvLibList,'libary' , 2 ,False)
        self.tvLibList.set_model(self.libList)
        
        addColumnToTable(self.tvLibpathList,'libary path' , 2 ,False)
        self.tvLibpathList.set_model(self.libpathList)
        
        addColumnToTable(self.tvIncludeList,'include path' , 2 ,False)
        self.tvIncludeList.set_model(self.includePathList)
        
        self.uuid = None
        self.uuidLib = None
        self.uuidLibpath = None
        self.uuidIncludepath = None
        
        self.updateList()
        
    def updateList (self):
        self.uuid = None
        self.uuidLib = None
        self.uuidLibpath = None
        self.uuidIncludepath = None
        
        self.CList.clear()
        self.libList.clear()
        self.libpathList.clear()
        self.includePathList.clear()
        
        L = self.db.Comp_Compiler_getList()
        for e in L:
            self.CList.append(e)
            
    def updateLibList (self):
        if self.uuid == None : return
        
        self.libList.clear()
        L = self.db.Comp_CompilerLib_getList(self.uuid)
        for e in L:
            self.libList.append(e)
        self.uuidLib = None

    def updateLibpathList (self):
        if self.uuid == None : return
        self.libpathList.clear()
        L = self.db.Comp_CompilerLibPath_getList(self.uuid)
        for e in L:
            self.libpathList.append(e)
        self.uuidLibpath = None
    
    def updateIncludePathList (self):
        if self.uuid == None : return
        self.includePathList.clear()
        L = self.db.Comp_CompilerIncludePath_getList(self.uuid)
        for e in L:
            self.includePathList.append(e)
        self.uuidIncludepath = None
        
            
    def updateCompilerSubLists (self):
        self.updateLibList()
        self.updateLibpathList()
        self.updateIncludePathList()
        
    
    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
    
    def actionCompCursorChanged (self, tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuid = model.get_value(iter,0)
            self.eName.set_text(model.get_value(iter,1))
            self.eDescription.set_text(model.get_value(iter,2))
            self.eOperatingSystem.set_text(model.get_value(iter,3))
            self.eCC.set_text(model.get_value(iter,4))
            self.eCXX.set_text(model.get_value(iter,5))
            self.eASM.set_text(model.get_value(iter,6))
            self.eAR.set_text(model.get_value(iter,7))
            self.eLINK.set_text(model.get_value(iter,8))
            self.eCCFLAGS.set_text(model.get_value(iter,9))
            self.eOBJSUFFIX.set_text(model.get_value(iter,10))
            self.eCCCOM.set_text(model.get_value(iter,11))
            self.eCXXCOM.set_text(model.get_value(iter,12))
            self.eCXXFLAGS.set_text(model.get_value(iter,13))
            self.eLINKCOM.set_text(model.get_value(iter,14))
            self.eLINKFLAGS.set_text(model.get_value(iter,15))
        else:
            self.uuid = None
        self.updateCompilerSubLists()
        
    
    def actionAddComp (self, b):
        self.db.Comp_Compiler_add (
            self.eName.get_text(),
            self.eDescription.get_text(),
            self.eOperatingSystem.get_text(),
            self.eCC.get_text(),
            self.eCXX.get_text(),
            self.eASM.get_text(),
            self.eAR.get_text(),
            self.eLINK.get_text(),
            self.eCCFLAGS.get_text(),
            self.eOBJSUFFIX.get_text(),
            self.eCCCOM.get_text(),
            self.eCXXCOM.get_text(),
            self.eCXXFLAGS.get_text(),
            self.eLINKCOM.get_text(),
            self.eLINKFLAGS.get_text()
            )
        self.updateList()
    
    def actionChangeComp (self, b):
        if self.uuid == None: return
        self.db.Comp_Compiler_update(
            self.uuid,
            self.eName.get_text(),
            self.eDescription.get_text(),
            self.eOperatingSystem.get_text(),
            self.eCC.get_text(),
            self.eCXX.get_text(),
            self.eASM.get_text(),
            self.eAR.get_text(),
            self.eLINK.get_text(),
            self.eCCFLAGS.get_text(),
            self.eOBJSUFFIX.get_text(),
            self.eCCCOM.get_text(),
            self.eCXXCOM.get_text(),
            self.eCXXFLAGS.get_text(),
            self.eLINKCOM.get_text(),
            self.eLINKFLAGS.get_text()
            )
        self.updateList()
    
    def actionDelComp (self, b):
        if self.uuid == None: return
        self.db.Comp_Compiler_delete(self.uuid)
        self.updateList()
        
    def actionLibCursorChanged(self, tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuidLib = model.get_value(iter,0)
            self.eLib.set_text(model.get_value(iter,2))
        else:
            self.uuidLib = None

    def actionLibAdd (self, b):
        if self.uuid == None : return
        self.db.Comp_CompilerLib_add (
            self.uuid,
            self.eLib.get_text()
        )
        self.updateLibList()
    
    def actionLibChange (self, b):
        if (self.uuid == None) or (self.uuidLib == None) : return
        self.db.Comp_CompilerLib_update(
            self.uuidLib,
            self.uuid,
            self.eLib.get_text()
        )
        self.updateLibList()
    
    def actionLibDelete (self, b):
        if (self.uuid == None) or (self.uuidLib == None) : return
        self.db.Comp_CompilerLib_delete(self.uuidLib)
        self.updateLibList()

    def actionLibpathCursorChanged(self, tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuidLibpath = model.get_value(iter,0)
            self.eLibpath.set_text(model.get_value(iter,2))
        else:
            self.uuidLibpath = None

    def actionLibpathAdd (self, b):
        if self.uuid == None : return
        self.db.Comp_CompilerLibPath_add (
            self.uuid,
            self.eLibpath.get_text()
        )
        self.updateLibpathList()
    
    def actionLibpathChange (self, b):
        if (self.uuid == None) or (self.uuidLibpath == None) : return
        self.db.Comp_CompilerLibPath_update(
            self.uuidLibpath,
            self.uuid,
            self.eLibpath.get_text()
        )
        self.updateLibpathList()
    
    def actionLibpathDelete (self, b):
        if (self.uuid == None) or (self.uuidLibpath == None) : return
        self.db.Comp_CompilerLibPath_delete(self.uuidLibpath)
        self.updateLibpathList()


    def actionIncludepathCursorChanged(self, tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuidIncludepath = model.get_value(iter,0)
            self.eIncludepath.set_text(model.get_value(iter,2))
        else:
            self.uuidIncludepath = None

    def actionIncludepathAdd (self, b):
        if self.uuid == None : return
        self.db.Comp_CompilerIncludePath_add(
            self.uuid,
            self.eIncludepath.get_text()
        )
        self.updateIncludePathList()
    
    def actionIncludepathChange (self, b):
        if (self.uuid == None) or (self.uuidIncludepath == None) : return
        self.db.Comp_CompilerIncludePath_update(
            self.uuidIncludepath,
            self.uuid,
            self.eIncludepath.get_text()
        )
        self.updateIncludePathList()
    
    def actionIncludepathDelete (self, b):
        if (self.uuid == None) or (self.uuidIncludepath == None) : return
        self.db.Comp_CompilerIncludePath_delete(self.uuidIncludepath)
        self.updateIncludePathList()

class uiTestAP (object):
    def __init__(self, gladeFile,db):
        self.db = db

        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgTestAP') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgTestAP_clicked'                  : self.actionClose,
             'on_bRunTest_dlgTestAP_clicked'                : self.runTest,
             'on_bInitPython_dlgTestAP_clicked'             : self.initPythonScript,
             'on_bClosePython_dlgTestAP_clicked'            : self.closePythonScript,
             'on_bTestPrg_dlgTestAP_clicked'                : self.APASMProgram,
             'on_bPythonPrg_dlgTestAP_clicked'              : self.PythonProgram,
             'on_bMatlab_dlgTestAP_clicked'                 : self.MatlabProgram,
             'on_bAdd_dlgTestAP_clicked'                    : self.addTest,
             'on_cChange_dlgTestAP_clicked'                 : self.changeTest,
             'on_bDelete_dlgTestAP_clicked'                 : self.deleteTest,
             'on_tvTestPattern_dlgTestAP_cursor_changed'    : self.actionTVchanged
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgTestAP')

        # creating list
        self.TPList = gtk.ListStore(int, str, str, int, int, int, int, int, int)
        self.APList = gtk.ListStore(int, str )

        # test pattern list view
        self.tvTP = self.gladeTmpl.get_widget('tvTestPattern_dlgTestAP')
        addColumnToTable(self.tvTP, 'test pattern name', 1 ,False)
        addColumnToTable(self.tvTP, 'test pattern description', 2 ,False)

        self.tvTP.set_model(self.TPList)
        
        self.eTPName = self.gladeTmpl.get_widget('eName_dlgTestAP')
        self.eTPDescr = self.gladeTmpl.get_widget('eDescr_dlgTestAP')
        self.cbAP = self.gladeTmpl.get_widget('cbAudioProcessor_dlgTestAP')
        
        self.cbAP.set_model(self.APList)
        cell = gtk.CellRendererText()
        self.cbAP.pack_start(cell, True)
        self.cbAP.add_attribute(cell, 'text', 1)

        self.uuidTP = None

        self.buildTPTable()
        self.buildAPcb()

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
    
    def buildTPTable (self):
        self.TPList.clear()
        self.uuidTP = None
        
        L = self.db.TestPattern_getList()
        for tp in L:
            self.TPList.append(tp)
    
    def buildAPcb(self):
        self.APList.clear()
        
        self.APList.append((0,'none'))
        APL = self.db.AP_getList()
        for ap in APL:
            self.APList.append((ap[0],ap[1]))
                
    def initPythonScript (self, b):
        if self.uuidTP == None:
            return
        p = self.db.TestPattern_get(self.uuidTP)
        ps = self.db.PythonScript_get(p[7])
        txtDlg = uiEnterTxtDlg(self.gladefile,'initiational python script',ps[1])
        if txtDlg.run() == 0:
            self.db.PythonScript_update(p[7],txtDlg.ret)

    def closePythonScript (self, b):
        if self.uuidTP == None:
            return
        p = self.db.TestPattern_get(self.uuidTP)
        ps = self.db.PythonScript_get(p[8])
        txtDlg = uiEnterTxtDlg(self.gladefile,'close python script',ps[1])
        if txtDlg.run() == 0:
            self.db.PythonScript_update(p[8],txtDlg.ret)
    
    def APASMProgram (self, b):
        if self.uuidTP == None:
            return
        p = self.db.TestPattern_get(self.uuidTP)
        ap = self.db.ALASMprg_get(p[4])
        txtDlg = uiEnterTxtDlg(self.gladefile,'AL asm program',ap[1])
        if txtDlg.run() == 0:
            self.db.ALASMprg_update(p[4],txtDlg.ret)
    
    def PythonProgram (self, b):
        if self.uuidTP == None:
            return
        p = self.db.TestPattern_get(self.uuidTP)
        ps = self.db.PythonScript_get(p[5])
        txtDlg = uiEnterTxtDlg(self.gladefile,'python program script',ps[1])
        if txtDlg.run() == 0:
            self.db.PythonScript_update(p[5],txtDlg.ret)
    
    def MatlabProgram (self, b):
        if self.uuidTP == None:
            return
        p = self.db.TestPattern_get(self.uuidTP)
        mp = self.db.MatlabPrg_get(p[6])
        txtDlg = uiEnterTxtDlg(self.gladefile,'matlab program',mp[1])
        if txtDlg.run() == 0:
            self.db.MatlabPrg_update(p[6],txtDlg.ret)
    
    def addTest (self, b):
        APid = comboBoxGetValue(self.cbAP, 0)
        if APid == None:
            APid = 0 
        (res, txt, id) = self.db.TestPattern_create (
                self.eTPName.get_text(),
                self.eTPDescr.get_text(),
                APid
            )
        if res == False:
            mb = MessageBox(
                message=txt,
                buttons=('Ok',)
                )
            mb.run()
            return
        # rebuild table
        self.buildTPTable()
    
    def changeTest (self, b):
        if self.uuidTP == None:
            return
        APid = comboBoxGetValue(self.cbAP, 0)
        if APid == None:
            APid = 0 
        self.db.TestPattern_update (
                self.uuidTP,
                self.eTPName.get_text(),
                self.eTPDescr.get_text(),
                APid
            )
        # rebuild table
        self.buildTPTable()
     
    def deleteTest (self, b):
        if self.uuidTP == None: return
        self.db.TestPattern_delete(self.uuidTP)
        # rebuild table
        self.buildTPTable()

    def actionTVchanged (self,tv):
        treeSel = tv.get_selection()
        (model, iter) = treeSel.get_selected()
        if iter != None:
            self.uuidTP = model.get_value(iter,0)
            self.eTPName.set_text(str(model.get_value(iter,1)))
            self.eTPDescr.set_text(str(model.get_value(iter,2)))
            comboBoxSelectValue(self.cbAP,model.get_value(iter,3),0)
        else:
            self.uuidTP = None

    def runTest (self, b):
        if self.uuidTP == None:
            return
        benchmark.executeTestPattern(self.db, self.uuidTP) 

class uiWavGen (object):
    def __init__(self, gladeFile):
        
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgWavGen') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bClose_dlgWavGen_clicked'          : self.actionClose,
             'on_bPhaseNoise_dlgWavGen_clicked'     : self.actionPhaseNoise,
             'on_bLogSweep_dlgWavGen_clicked'       : self.actionLogSweep
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgWavGen')

    def run(self):
        self.dlg.run()
    
    def actionClose(self, b):
        self.dlg.response(0)
        self.dlg.destroy()
        
    
    def actionPhaseNoise(self,b):
        pass

    def actionLogSweep(self,b):
        uiLogSweep = uiGenLogSweep (self.gladefile)
        uiLogSweep.run()


class uiGenLogSweep (object):
    def __init__(self, gladeFile):
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgGenLogSweep') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bGenerate_dlgGenLogSweep_clicked'  : self.actionGen,
             'on_bChancel_dlgGenLogSweep_clicked'   : self.actionChancel
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgGenLogSweep')
        self.eFs = self.gladeTmpl.get_widget('eFs_dlgGenLogSweep')
        self.eFstart = self.gladeTmpl.get_widget('eFstart_dlgGenLogSweep')
        self.eNPoint = self.gladeTmpl.get_widget('eNumPoints_dlgGenLogSweep')
        
        self.eFs.set_text(str(48000.))
        self.eFstart.set_text(str(30.))
        self.eNPoint.set_text(str(1024))

    def run(self):
        self.dlg.run()
    
    def actionGen(self, b):
        fs = float(self.eFs.get_text())
        fstart = float(self.eFstart.get_text())
        N = int(self.eNPoint.get_text())
        values = signGen.genSineSweep(fs, N, fstart)
        
        file = 'logSweep fs'+str(fs/1000.)+'kHz fstart'+str(fstart/1000.)+'kHz N'+str(N)+'samples.wav'
        
        fsDlg = gtk.FileChooserDialog(title='enter WAV filename',action=gtk.FILE_CHOOSER_ACTION_SAVE,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        
        fltr = gtk.FileFilter()
        fltr.set_name("WAV file")
        fltr.add_pattern("*.wav")
        fsDlg.add_filter(fltr)
        
        fsDlg.set_current_name(file)
        
        res = fsDlg.run()
        file =  fsDlg.get_filename()
        fsDlg.destroy()
        if res == gtk.RESPONSE_OK:
            floatwavefile.writeFloatWAV(file, fs, values)

        self.dlg.response(0)
        self.dlg.destroy()
        
    def actionChancel(self, b):
        self.dlg.response(-1)
        self.dlg.destroy()
    

class uiDocGenOption (object):
    def __init__(self, gladeFile):
        # result var
        self.genOptions = {}
        # gui vars
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgDocGenOptions') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bGen_dlgDocGenOptions_clicked'  : self.actionGen,
             'on_bChancel_dlgDocGenOptions_clicked'   : self.actionChancel
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgDocGenOptions')
        self.cbGenDef = self.gladeTmpl.get_widget('cbDefGen_dlgDocGenOptions')

        self.cbGenImpl = self.gladeTmpl.get_widget('cbImplGen_dlgDocGenOptions')
        self.cbGenImplIncl = self.gladeTmpl.get_widget('cbImplGenIncl_dlgDocGenOptions')
        self.cbGenImplCode = self.gladeTmpl.get_widget('cbImplGenCode_dlgDocGenOptions')


        self.cbGenDef.set_active(True)

        self.cbGenImpl.set_active(True)
        self.cbGenImplIncl.set_active(True)
        self.cbGenImplCode.set_active(True)
        

    def run(self):
        return self.dlg.run()
    
    def actionGen(self, b):
        if self.cbGenDef.get_active() is True:
            self.genOptions['definition'] = (True,True)
        if self.cbGenImpl.get_active() is True:
            self.genOptions['implementation'] = (self.cbGenImplIncl.get_active(),self.cbGenImplCode.get_active())
        
        self.dlg.response(gtk.RESPONSE_OK)
        self.dlg.destroy()
        
    def actionChancel(self, b):
        self.dlg.response(gtk.RESPONSE_CANCEL)
        self.dlg.destroy()

class uiGenAPexternalInterface (object):
    def __init__(self, gladeFile, db):
        self.db = db
        # gui vars
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgGenAPexternalInterface') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bGen_dlgGenAPexternalInterface_clicked'  : self.actionGen,
             'on_bClose_dlgGenAPexternalInterface_clicked'   : self.actionClose
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgGenAPexternalInterface')
        self.cbDrv = self.gladeTmpl.get_widget('cbCommDriver_dlgGenAPexternalInterface')
     
        # set the combobox
              
        # fill cb
        dL = self.db.Impl_ImplMsgDriver_getListSortedByGroup()
        self.lsDrv = gtk.ListStore( int, str)
        for d in dL:
            self.lsDrv.append((d[0], d[2]))
        self.cbDrv.set_model(self.lsDrv)

        cell = gtk.CellRendererText()
        self.cbDrv.pack_start(cell, True)
        self.cbDrv.add_attribute(cell, 'text', 1)
        
        if len(dL) == 0:
            comboBoxSelectValue(self.cbDrv, None, None)
        else:        
            comboBoxSelectValue(self.cbDrv, d[0], 0)
        
    def run(self):
        return self.dlg.run()
    
    def actionGen(self, b):
        drvUUID = comboBoxGetValue(self.cbDrv, 0)
        fsDlg = gtk.FileChooserDialog(title='select folder into the remote interface is generated',action=gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        fsDlg.set_current_folder(os.getcwd())
        res = fsDlg.run()
        destFolder = fsDlg.get_current_folder()
        fsDlg.destroy()
        if res != gtk.RESPONSE_OK:
            return
        cg = codeGen.codeGenerator(self.db, '')
        cg.genRemoteInterface(drvUUID, destFolder)
        print ('finished!')
        
        
        
    def actionClose(self, b):
        self.dlg.response(gtk.RESPONSE_CANCEL)
        self.dlg.destroy()
    
class uiCodeGenOptions (object):
    def __init__(self, gladeFile):
        # gui vars
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgCodeGenOptions') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bGen_dlgCodeGenOptions_clicked'  : self.actionGen,
             'on_bChancel_dlgCodeGenOptions_clicked'   : self.actionClose,
             'on_bSelFile_dlgCodeGenOptions_clicked' : self.actionSelALCFile
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgCodeGenOptions')
        self.cbDebugI = self.gladeTmpl.get_widget('cbDebugInfos_dlgCodeGenOptions')
        self.lsDebugI = gtk.ListStore( int, str)
        self.lsDebugI.append([True, 'generate debug interface'])
        self.lsDebugI.append([False, 'no debug interface'])
        self.cbDebugI.set_model(self.lsDebugI)
        cell = gtk.CellRendererText()
        self.cbDebugI.pack_start(cell, True)
        self.cbDebugI.add_attribute(cell, 'text', 1)
        comboBoxSelectValue(self.cbDebugI,False,0)
        
        self.cbCodeOpt = self.gladeTmpl.get_widget('cbCodeOutput_dlgCodeGenOptions')
        self.lsCodeOpt = gtk.ListStore( int, str)
        self.lsCodeOpt.append([True, 'C89 code'])
        self.lsCodeOpt.append([False, 'C++ code'])
        self.cbCodeOpt.set_model(self.lsCodeOpt)
        self.cbCodeOpt.pack_start(cell, True)
        self.cbCodeOpt.add_attribute(cell, 'text', 1)
        comboBoxSelectValue(self.cbCodeOpt,True,0)
        
        self.cbToolChain = self.gladeTmpl.get_widget('cbToolchain_dlgCodeGenOptions')
        self.lsToolChain = gtk.ListStore( str, str)
        self.lsToolChain.append(['' , 'no code compilation'])
        self.lsToolChain.append(['scons', 'scons build tool'])
        self.lsToolChain.append(['c', 'generic c-compilier'])
        self.lsToolChain.append(['cmd', 'command line file'])
    
        self.cbToolChain.set_model(self.lsToolChain)
        self.cbToolChain.pack_start(cell, True)
        self.cbToolChain.add_attribute(cell, 'text', 1)
        comboBoxSelectValue(self.cbToolChain,'',0)
        
        self.eALcFile = self.gladeTmpl.get_widget('eSelFile_dlgCodeGenOptions')
        self.eALcFile.set_text("")
        
        self.options = None
        
        
    def run(self):
        return self.dlg.run()
    
    def actionGen(self, b):
        self.options = {
            'debug' : comboBoxGetValue(self.cbDebugI, 0),
            'C89' : comboBoxGetValue(self.cbCodeOpt, 0),
            'toolChain' : comboBoxGetValue(self.cbToolChain, 0),
            'eALFile' : self.eALcFile.get_text()
            }
        self.dlg.response(gtk.RESPONSE_OK)
        self.dlg.destroy()
        
    def actionClose(self, b):
        self.options = None
        self.dlg.response(gtk.RESPONSE_CANCEL)
        self.dlg.destroy()
    
    def actionSelALCFile (self, b):
        fsDlg = gtk.FileChooserDialog(title='select audio language file',action=gtk.FILE_CHOOSER_ACTION_OPEN,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        fsDlg.set_current_folder(os.getcwd())
        
        fltr = gtk.FileFilter()
        fltr.set_name("All files")
        fltr.add_pattern("*")
        fsDlg.add_filter(fltr)
        fltr = gtk.FileFilter()
        fltr.set_name("audio language binary code file")
        fltr.add_pattern("*.alc")
        fsDlg.add_filter(fltr)
        fltr = gtk.FileFilter()
        fltr.set_name("audio language C-code file")
        fltr.add_pattern("*.c")
        fsDlg.add_filter(fltr)

        res = fsDlg.run()
        fn = fsDlg.get_filename()
        fsDlg.destroy()
        if res != gtk.RESPONSE_OK:
            return
        self.eALcFile.set_text(fn)
        

class uiALcompile (object):
    def __init__(self, gladeFile):
        # gui vars
        self.gladefile = gladeFile
        self.gladeTmpl = gtk.glade.XML(self.gladefile, 'dlgCompile') 
        self.gladeTmpl.signal_autoconnect (
            {
             'on_bSelFile_dlgCompile_clicked'  : self.actionSelSrcFile,
             'on_bSelDestDir_dlgCompile_clicked'   : self.actionSelDir,
             'on_bBuild_dlgCompile_clicked' : self.actionCompile,
             'on_bClose_dlgCompile_clicked' : self.actionClose,
             'on_cbBuildCfg_dlgCompile_changed': self.actionBuildSelected,
             }
            )
        self.dlg = self.gladeTmpl.get_widget('dlgCompile')
        self.eSrcFile = self.gladeTmpl.get_widget('eScrFile_dlgCompile')
        self.eDestDir = self.gladeTmpl.get_widget('eDestDir_dlgCompile')
        
        self.cbBuildCfg = self.gladeTmpl.get_widget('cbBuildCfg_dlgCompile')

        self.lAmInstrBeforMsgSys = self.gladeTmpl.get_widget('label5_dlgCompile')
        self.eAmInstrBeforMsgSys = self.gladeTmpl.get_widget('eInstrAmount_dlgCompile')
    
        self.eDestDir.set_text(os.path.curdir)
        
        
    def run(self):
        return self.dlg.run()
    
    def actionSelSrcFile(self, b):
        fsDlg = gtk.FileChooserDialog(title='select audio language file',action=gtk.FILE_CHOOSER_ACTION_OPEN,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        fsDlg.set_current_folder(os.getcwd())

        fltr = gtk.FileFilter()
        fltr.set_name("audio language code file")
        fltr.add_pattern("*.al")
        fsDlg.add_filter(fltr)

        
        fltr = gtk.FileFilter()
        fltr.set_name("All files")
        fltr.add_pattern("*")
        fsDlg.add_filter(fltr)

        res = fsDlg.run()
        fn = fsDlg.get_filename()
        fsDlg.destroy()
        if res != gtk.RESPONSE_OK:
            return
        self.eSrcFile.set_text(fn)
        
        
    def actionSelDir(self, b):
        fsDlg = gtk.FileChooserDialog(title='select folder where the result is dumped',action=gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER,buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        fsDlg.set_current_folder(self.eDestDir.get_text())
        res = fsDlg.run()
        destFolder = fsDlg.get_current_folder()
        fsDlg.destroy()

        if res != gtk.RESPONSE_OK:
            return
        self.eDestDir.set_text(destFolder)

    def actionCompile(self, b):
        file = self.eSrcFile.get_text()
        path = os.path.dirname(file)
        print ('compile '+file+' into '+path)
        progPathExe = os.path.join(os.curdir,'ALc2.py')
        pythonCmd = 'python {progPathExe} -i="{file}" -o="{path}"'.format(file=file, path=path, progPathExe=progPathExe)
        proc = subprocess.Popen(pythonCmd, shell=True)
        proc.wait()
        

    def actionClose(self, b):
        self.options = None
        self.dlg.response(gtk.RESPONSE_CANCEL)
        self.dlg.destroy()


    def actionBuildSelected (self, entry):
        itemID = comboBoxGetValue(self.cbBuildCfg, 0)
        if itemID == 3:
            self.lAmInstrBeforMsgSys.show()
            self.eAmInstrBeforMsgSys.show()
        else:
            self.lAmInstrBeforMsgSys.hide()
            self.eAmInstrBeforMsgSys.hide()

'''
Created on 12.08.2011

@author: StJ
'''

import platform
import re
import os
import subprocess

import APlogger


def reformatFilePathForRegEx (pathFile):
    return pathFile.replace("\\",'/')


class APbuilderBaseClass():
    def __init__(self, tmplFile):
        pass
    
    def loadFile (self, filename):
        openfile = open(filename, 'r')
        res = openfile.read()
        openfile.close()
        return res
    
    def saveFile (self, filename, text):
        savefile = open(filename, 'w')
        savefile.write(text)
        savefile.close()

    def executeScript2 (self, scriptText):
        log = APlogger.getAPBuilderLogger()
        
        log.info('create  process ...')
        # spawn process for python
        process = subprocess.Popen('cmd', shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        log.info('execute script ...')
        # feed the process with the script
        process.stdin.write (scriptText)
        # terminate python
        log.info('terminate process ...')
        process.stdin.write ("\nexit\n")
        process.stdin.close()
        # save stdout to log file
        resTxt = process.stdout.read()
        log.info('process out: '+ resTxt)
        process.stdout.close()
        #wait till python has ended
        errTxt = process.stderr.read()
        process.stderr.close()
        
        rc = process.wait()
        if  rc != 0:
            resTxt = 'process failed with error code '+str(errTxt)
            log.error (resTxt)
            return False, resTxt
        return True, resTxt

    def executeScript (self, scriptText):
        log = APlogger.getAPBuilderLogger()
        
        log.info('create  process ...')
        # spawn process for python
        process = subprocess.Popen('cmd', shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        log.info('execute script ...')
        
        scriptText += '\nexit\n'
        resTxt, errTxt = process.communicate(scriptText)
        if errTxt != '':
            resTxt = 'process failed with error code '+str(errTxt)
            log.error (resTxt)
            return False, resTxt
        return True, resTxt


    def build (self, sources, destDir, dbLibPaths, dbAPLibList, dbCompilerLibList, dbIncludePaths, dbCompiler, builtArtifactName):
        return False,'no implementation'

class APbuilderScons (APbuilderBaseClass):
    def __init__(self, templateFile):
        self.keys = [
            'CC',
            'CXX',
            'ASM',
            'AR',
            'LINK',
            'CCFLAGS',
            'OBJSUFFIX',
            'CCCOM',
            'CXXCOM',
            'CXXFLAGS',
            'LINKCOM',
            'LINKFLAGS'
        ]
        self.sconstructTemplate = self.loadFile(templateFile)
        self.sconstructReplacePattern = {
            '@envSubst' : '',
            '@ProgName' : '',
            '@SrcFiles' : '',
            '@Libs' : '',
            '@LibPath' : '',
            '@CppPath' : ''
            } 
    
    def build (self, sources, destDir, dbLibPaths, dbAPLibList, dbCompilerLibList, dbIncludePaths, dbCompiler, builtArtifactName):
        log = APlogger.getAPBuilderLogger()
        log.info('scons builder started ...')
        # build include path list
        c = 0
        libPaths = '['
        for p in dbLibPaths:
            if c != 0: libPaths += ","
            libPaths += "'"+p[2]+"'"
            c += 1
        libPaths += ']'
        # build lib lists
        libs = '['
        c = 0
        # add compiler libs
        for l in dbCompilerLibList:
            if c != 0: libs += ","
            libs += "'"+l[2]+"'"
            c += 1
        # add AP libs
        for l in dbAPLibList:
            if c != 0: libs += ","
            libs += "'"+l+"'"
            c += 1
        libs += ']'
        # build path list
        inclPaths = '['
        c = 0
        for p in dbIncludePaths:
            if c != 0: inclPaths += ","
            inclPaths += "'"+p[2]+"'"
            c += 1
        inclPaths += ']'
        
        #build environment vars
        log.info( 'setup the environment')

        c = 4;
        i = 0;
        envKeys = self.keys
        envText = ''
        for i in range(0,12):
            envText += "\nmyEnv['" + envKeys[i] + "'] = '" + dbCompiler[c] + "'"
            c += 1
        # get sourcefile strings
        sourcefileText = '['
        c = 0
        for sf in sources:
            if c != 0: sourcefileText += ","
            sourcefileText += "'"+sf+"'"
            c += 1
        sourcefileText += ']'    
        
        log.info( 'substitute expressions at the template')
        
        ospath = '\''+os.environ['PATH']+'\''
        #subsitude expressions
        patterns = self.sconstructReplacePattern
        patterns['@envSubst']=reformatFilePathForRegEx(envText)
        patterns['@ProgName']="'"+reformatFilePathForRegEx(builtArtifactName)+"'"
        patterns['@SrcFiles']=reformatFilePathForRegEx(sourcefileText)
        patterns['@Libs']=reformatFilePathForRegEx(libs)
        patterns['@LibPath']=reformatFilePathForRegEx(libPaths)
        patterns['@CppPath']=reformatFilePathForRegEx(inclPaths)
        patterns['@SysPath']=reformatFilePathForRegEx(ospath)
        
        # replace pattern with the values
        pyText = self.sconstructTemplate
        for k, v in patterns.items():
            p = re.compile (k, re.UNICODE)
            pyText = p.sub(v,pyText)
        log.info( 'dump construct file')
        sconsFilename = os.path.join(destDir,'SConstruct')
        self.saveFile (sconsFilename,pyText)
        
        # start scons
        log.info( 'init build process')
        syscallText = 'cd '+destDir+'\nscons\n'
        r, txt = self.executeScript(syscallText)
        log.info('finished')
        return r, txt

class APbuilderUserShell (APbuilderBaseClass):
    def __init__(self, templateFile):
        pass
    
    def build (self, sources, destDir, dbLibPaths, dbAPLibList, dbCompilerLibList, dbIncludePaths, dbCompiler, builtArtifactName):
        log = APlogger.getAPBuilderLogger()
        log.info('user builder started ...')
        # build include path list
        libPaths = ''
        for p in dbLibPaths:
            libPaths += '-L"'+p[2]+'" '
        # build lib lists
        libs = ''
        # add compiler libs
        for l in dbCompilerLibList:
            libs += '-l"'+l[2]+'" '
        # add AP libs
        for l in dbAPLibList:
            libs += '-l"'+l+'" '
        # build path list
        inclPaths = ''
        for p in dbIncludePaths:
            inclPaths += '-I"'+p[2]+'" '

        #build build script
        log.info( 'build compile and link script')

        #clean pattern
        cleanpattern = (
            '\$CFLAGS',
            '\$_CCCOMCOM',
            '\$CCFLAGS',
            '\$LINKFLAGS'
            )
        
        #substitute pattern
        substpattern = {
            '\$CC'              : dbCompiler[4],
            '\$CXX'             : dbCompiler[5],
            '\$ASM'             : dbCompiler[6],
            '\$LINK'            : dbCompiler[4],
            '\$TARGET'          : '',
            '\$SOURCES'         : '',
            '\$_LIBDIRFLAGS'    : '',
            '\$_LIBFLAGS'       : ''
        }
        
        clearPattern = '\$[a-zA-Z_]*'
        # load pattern
        compileCmd = dbCompiler[11]
        linkCmd = dbCompiler[14]

        # build reg exp
        pstr = ''
        c = 0
        for p in cleanpattern:
            if c != 0:
                pstr += '|'
            pstr += p
            c += 1
        # clean cmd's
        p = re.compile (pstr, re.UNICODE)
        compileCmd = p.sub('',compileCmd)
        linkCmd = p.sub('',linkCmd)

        # start scripting
        
        script = 'cd ' + destDir +'\n'
        
        # build compile commands
        destL = []
        for s in sources:
            pt = substpattern
            destName = os.path.relpath(os.path.splitext(s)[0] + '.o',destDir)
            pt['\$TARGET'] = destName
            pt['\$SOURCES'] = os.path.relpath(s,destDir)
            cmd = compileCmd
            for k, v in pt.items():
                p = re.compile (k, re.UNICODE)
                cmd = p.sub(v,cmd)
            p = re.compile (clearPattern, re.UNICODE)
            cmd = p.sub('',cmd)
                
            script += cmd +' ' + inclPaths+' '+'\n'
            destL.append(destName)
        
        # build link command
        src = ''
        for d in destL:
            src += d + ' '
        pt = substpattern
        pt['\$TARGET'] = builtArtifactName + '.exe'
        pt['\$SOURCES'] = src
        pt['\$_LIBDIRFLAGS'] = libPaths
        pt['\$_LIBFLAGS'] = libs
        cmd = linkCmd
        for k, v in pt.items():
            p = re.compile (k, re.UNICODE)
            cmd = p.sub(v,cmd)
        p = re.compile (clearPattern, re.UNICODE)
        cmd = p.sub('',cmd)
        script += cmd +'\n'
        # build list for compile
        # build linker
        log.info( 'execute script')
        r, txt = self.executeScript(script)
        log.info('finished')
        return r, txt

class APbuilderCmdLineScript (APbuilderBaseClass):
    def __init__(self, templateFile):
        pass
    
    def build (self, sources, destDir, dbLibPaths, dbAPLibList, dbCompilerLibList, dbIncludePaths, dbCompiler, builtArtifactName):
        log = APlogger.getAPBuilderLogger()
        log.info('comandline script builder started ...')
        # build include path list
        libPaths = ''
        for p in dbLibPaths:
            libPaths += '-L"'+p[2]+'" '
        # build lib lists
        libs = ''
        # add compiler libs
        for l in dbCompilerLibList:
            libs += '-l"'+l[2]+'" '
        # add AP libs
        for l in dbAPLibList:
            libs += '-l"'+l+'" '
        # build path list
        inclPaths = ''
        for p in dbIncludePaths:
            inclPaths += '-I"'+p[2]+'" '

        #build build script
        log.info( 'build compile and link script')

        #clean pattern
        cleanpattern = (
            '\$CFLAGS',
            '\$_CCCOMCOM',
            '\$CCFLAGS',
            '\$LINKFLAGS'
            )
        
        #substitute pattern
        substpattern = {
            '\$CC'              : dbCompiler[4],
            '\$CXX'             : dbCompiler[5],
            '\$ASM'             : dbCompiler[6],
            '\$LINK'            : dbCompiler[4],
            '\$TARGET'          : '',
            '\$SOURCES'         : '',
            '\$_LIBDIRFLAGS'    : '',
            '\$_LIBFLAGS'       : ''
        }
        
        clearPattern = '\$[a-zA-Z_]*'
        # load pattern
        compileCmd = dbCompiler[11]
        linkCmd = dbCompiler[14]

        # build reg exp
        pstr = ''
        c = 0
        for p in cleanpattern:
            if c != 0:
                pstr += '|'
            pstr += p
            c += 1
        # clean cmd's
        p = re.compile (pstr, re.UNICODE)
        compileCmd = p.sub('',compileCmd)
        linkCmd = p.sub('',linkCmd)

        # start scripting
        
        script = 'cd ' + destDir +'\n'
        
        # build compile commands
        destL = []
        for s in sources:
            pt = substpattern
            destName = os.path.relpath(os.path.splitext(s)[0] + '.o',destDir)
            pt['\$TARGET'] = destName
            pt['\$SOURCES'] = os.path.relpath(s,destDir)
            cmd = compileCmd
            for k, v in pt.items():
                p = re.compile (k, re.UNICODE)
                cmd = p.sub(v,cmd)
            p = re.compile (clearPattern, re.UNICODE)
            cmd = p.sub('',cmd)
                
            script += cmd +' ' + inclPaths+' '+'\n'
            destL.append(destName)
        
        # build link command
        src = ''
        for d in destL:
            src += d + ' '
        pt = substpattern
        pt['\$TARGET'] = builtArtifactName + '.exe'
        pt['\$SOURCES'] = src
        pt['\$_LIBDIRFLAGS'] = libPaths
        pt['\$_LIBFLAGS'] = libs
        cmd = linkCmd
        for k, v in pt.items():
            p = re.compile (k, re.UNICODE)
            cmd = p.sub(v,cmd)
        p = re.compile (clearPattern, re.UNICODE)
        cmd = p.sub('',cmd)
        script += cmd +'\n'
        # build list for compile
        # build linker
        log.info( 'build command script file')
        dumpFile = os.path.join(destDir,'make.cmd')
        f = open(dumpFile,'w+')
        log.info( 'dump commands into file')
        f.write(script)
        f.close
        log.info('finished')
        return True, 'succeeded'



class APbuilder():
    def __init__(self, db, templateFile):
        self.db = db
        self.templateFile = templateFile

    def buildAP (self, APuuid, dbAPLibList, destDir, sourceFiles, builder=APbuilderScons):
        log = APlogger.getAPBuilderLogger()
        log.info( 'get the AP from the database ...')
        ap = self.db.AP_get (APuuid)
        if (None == ap):
            log.error('AP with uuid = '+str(APuuid) +' do not exists at the database.')
            return False
        log.info( 'get the compiler from the database ...')
        dbCompiler = self.db.Comp_Compiler_get(ap[2])
        if (None == dbCompiler):
            log.error('compiler with uuid = '+str(APuuid) +' do not exists at the database.')
            return False
        builtArtifactName = ap[1]
        dbLibPaths = self.db.Comp_CompilerLibPath_getList (dbCompiler[0])
        dbCompilerLibList = self.db.Comp_CompilerLib_getList(dbCompiler[0])
        dbIncludePaths = self.db.Comp_CompilerIncludePath_getList(dbCompiler[0])
        
        blr = builder(self.templateFile)
        r, txt = blr.build ( sourceFiles, destDir, dbLibPaths, dbAPLibList, dbCompilerLibList, dbIncludePaths, dbCompiler, builtArtifactName)
        print (txt)
        return r
# -*- coding: utf-8 -*-
'''
Created on 07.01.2013

@author: StJ
'''


import subprocess
import os
import random
import tempfile
import shutil
import sys

import APDB

texTmplStart =r"""
\documentclass[12pt,a4paper,oneside,german]{{report}}
\usepackage{{listings}}
\usepackage{{hyperref}}
\usepackage{{ae}}
\usepackage[english]{{babel}}
\usepackage[ansinew]{{inputenc}}
\usepackage{{eurosym}}
\usepackage{{longtable}}
\usepackage[final]{{pdfpages}}

\lstset{{
    basicstyle= \ttfamily \small,
    numbers=left, % none, left, right
    stepnumber=1,
    numberstyle= \sffamily \tiny \color[rgb]{{0.5, 0.5, 0.5}},
    numbersep=8pt,
    lineskip=-3pt,
    frame=lines, % none, leftline, topline, bottomline, lines (top and bottom), single, shadowbox 
    breaklines=true, % activates automatic line breaking of too long lines
    showspaces=false,
    commentstyle=\bfseries\color[rgb]{{0.2,0.5,0.2}}, 
    keywordstyle=\bfseries\color{{blue}}, 
    backgroundcolor=\bfseries\color[gray]{{0.95}},
    showtabs=false,
    showstringspaces=false
}}

\makeatother

\author{{Stefan Jaritz}}
\title{{{title}}}
\makeindex

\begin{{document}}

\shorthandoff{{"}}

\pagenumbering{{Roman}}
\maketitle

\tableofcontents
\newpage

\pagenumbering{{arabic}}
"""

texTmplEnd =r"""
\end{document}
"""
texChapter = '\\chapter{{{0}}}\n'
texSection = '\\section{{{0}}}\n'
texSubSection = '\\subsection{{{0}}}\n'
texSubSubSection = '\\subsubsection{{{0}}}\n'
texTableStart = '\\begin{{tabular}}[hp]{{{0}}}\n'
texTableEnd = '\\end{tabular}\n'
texTableHLine = '\\hline\n'
texNewLine = '\\newline\n'
texNewParagraph = '\\par '
texCodeListing = '\\begin{{lstlisting}}\n{0}\n\\end{{lstlisting}}\n'
texCodeListingC = '\\begin{{lstlisting}}[language=C]\n{0}\n\\end{{lstlisting}}\n'
texCodeListingExternalFile = '\\lstinputlisting{{{0}}}\n'


def buildLatexStr(nativeStr):
    lstr = nativeStr.replace('&','\\&')
    lstr = lstr.replace('\\','\\textbackslash ')
    lstr = lstr.replace('_','\\_')
    lstr = lstr.replace('<','\\textless ')
    lstr = lstr.replace('>','\\textgreater ')
    lstr = lstr.replace('§','\\S')
    lstr = lstr.replace('$','\\$')
    lstr = lstr.replace('&','\\&')
    lstr = lstr.replace('#','\\#')
    lstr = lstr.replace('{','\\{')
    lstr = lstr.replace('}','\\}')
    lstr = lstr.replace('%','\\%')
    lstr = lstr.replace('~','\\textasciitilde ')
    lstr = lstr.replace('"','"\\\'')
    lstr = lstr.replace('€','\\texteuro ')
    return lstr

def genCode(codeID, db, CodeListingFlag, IncludeListingFlag):
    t = ''
    if IncludeListingFlag is True:
        IL = db.Code_getIncludes(codeID)
        if len(IL) > 0:
            t += 'includes:'
            t += texNewLine
            t += texTableStart.format('|p{5cm}|p{5cm}|p{2cm}|')
            t += texTableHLine
            t += 'c-Include & c-Library & system lib\\\\\n'
            t += texTableHLine
            for i in IL:
                if i[3]==True:
                    dummy = 'yes'
                else:
                    dummy = 'no'
                t += '\\parbox{{5cm}}{{{0}}} & \\parbox{{5cm}}{{{1}}} & \\parbox{{5cm}}{{{2}}} \\\\'.format(buildLatexStr(i[1]),buildLatexStr(i[2]),dummy) 
                t += texTableHLine +'\n'
            t += texTableEnd
            t += texNewLine
            t += texNewLine
            
    if CodeListingFlag is True:
        code = db.Code_getCode(codeID)
        if code is not None:
            t += 'code:'
            t += texNewLine
            t += texCodeListingC.format(code.encode('ascii','ignore'))
    return t

def genDefinition(db, codeListingFlag, IncludeListingFlag):
    t = ''

    # 1. HAL    
    t += texChapter.format('HAL')
    
    # 1.1. Variables
    t += texSection.format('Variables')
    L = db.HAL_VariableDefinition_getList()
    for e in L:
        PL = db.HAL_VariableDefinition_getParamList(e[1])
        
        t += texSubSection.format(e[2]+' (HAL vid='+str(e[1])+')')
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'HAL variable id:& {0}\\\\'.format(e[1])
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(e[3])
        t += texTableHLine + '\n'
        syntaxDummy = e[2] + ' test [3];'
        t += 'AL ASM syntax:& {0}\\\\'.format(syntaxDummy)
        t += texTableHLine + '\n'
        t += texTableEnd
        if len(PL) > 0:
            t += texNewLine
            t += texNewLine
            t += 'sub variables:'
            t += texNewLine
            t += texTableStart.format('|p{0.5cm}|p{2.5cm}|p{5cm}|p{5cm}|')
            t += texTableHLine
            t += 'Nr. & Name & Description & Type\\\\\n'
            t += texTableHLine
            i = 1
            for p in PL:
                (idHAL_VariableIOParameter, basicTypeID, VariableID, name, description, isArray)= p
                (idHAL_IOTypesDefinition, TypeID, TypeName, IOdescription, cType, endianType, sizeInBytes) = db.HAL_basicIOTypes_getByTypeID(basicTypeID)
                if TypeName is None:
                    paramType = r'unknown basic type(error)'
                else:
                    paramType = TypeName
                if isArray == True:
                    paramType += ' (array)'
                t += '{0} & \\parbox{{2.5cm}}{{{1}}} & \\parbox{{5cm}}{{{2}}} & \\parbox{{5cm}}{{{3}}} \\\\ '.format(i ,name, description, paramType)
                t += texTableHLine +'\n'
                i += 1
            t += texTableEnd
        
    # 1.2 Functions
    t += texSection.format('Functions')
    L = db.HAL_DefFunctions_getList()
    for e in L:
        PL = db.HAL_DefFunctions_getParamList(e[1])
        
        t += texSubSection.format(e[2] + ' (HAL fid ='+str(e[1])+')')
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'HAL function id:& {0}\\\\'.format(e[1])
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(e[3])
        t += texTableHLine + '\n'
        syntaxDummy = e[2] + ' '
        i = 0
        for p in PL:
            if i > 0:
                syntaxDummy += ','
            syntaxDummy += p[2]
            i += 1
        syntaxDummy += ';'
        
        t += 'AL ASM syntax:& {0}\\\\'.format(syntaxDummy)
        t += texTableHLine + '\n'

        t += texTableEnd
        
        if len(PL) > 0:
            t += texNewLine
            t += texNewLine
            t += 'Parameters:'
            t += texNewLine
            t += texTableStart.format('|p{0.5cm}|p{2cm}|p{5cm}|p{3.5cm}|p{2cm}|')
            t += texTableHLine
            t += 'Nr. & Name & Description & Class & Type\\\\\n'
            t += texTableHLine
            i = 1
            for p in PL:
                paramClass = db.dFuncParamsClasses.get(p[4],r'unknown(error)')
                if p[4] == db.dFuncClass_basicIOtype:
                    bt = db.HAL_basicIOTypes_getByTypeID(p[5])
                    if bt is None:
                        paramType = r'unknown basic type(error)'
                    else:
                        paramType = r'basic type\\\\' + bt[2]
                else:
                    vt = db.HAL_VariableDefinition_getByVariableID(p[5])
                    if vt[0] is None:
                        paramType = 'unknown(error)'
                    else:
                        paramType = 'HAL variable type\\\\'+vt[0][2]
                t += '{0} & \\parbox{{2cm}}{{{1}}} & \\parbox{{5cm}}{{{2}}} & \\parbox{{3.5cm}}{{{3}}} & \\parbox{{2cm}}{{{4}}} \\\\ '.format(i ,p[2], p[3], paramClass, paramType)
                t += texTableHLine +'\n'
                i += 1
            t += texTableEnd
    
    # 2. Communication
    t += texChapter.format('Communication Interface')
    
    # 2.1 message frames
    t += texSection.format('Message Frames')
    L = db.HAL_Msg_Type_getList()
    for e in L:
        PL = db.HAL_msg_TypeParam_getList(e[1])
        
        t += texSubSection.format(e[2] + ' ( msgId ='+str(e[1])+')')
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'message type id:& {0}\\\\'.format(e[1])
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(e[3])
        t += texTableHLine + '\n'
        t += texTableEnd
        
        if len(PL) > 0:
            t += texNewLine
            t += texNewLine
            t += 'Elements:'
            t += texNewLine
            t += texTableStart.format('|p{0.5cm}|p{5cm}|p{5cm}|p{3cm}|')
            t += texTableHLine
            t += 'Pos. & Name & Description & Type\\\\\n'
            t += texTableHLine
            i = 1
            for p in PL:
                bt = db.HAL_basicIOTypes_getByTypeID(p[5])
                if bt is None:
                    paramType = 'unknown basic type(error)'
                else:
                    paramType = bt[2]
                if p[6] == True:
                    paramType += ' (array)' 
                t += '{0} & \\parbox{{5cm}}{{{1}}} & \\parbox{{5cm}}{{{2}}} & \\parbox{{3cm}}{{{3}}} \\\\ '.format(p[2] ,p[3], p[4], paramType)
                t += texTableHLine +'\n'
                i += 1
            t += texTableEnd
    # 2.2. message processes
    t += texSection.format('Message Processes')
    L = db.HAL_msg_Process_getList()
    for e in L:
        t += texSubSection.format(e[2] + ' ( msgProcId ='+str(e[1])+')')
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'message process id:& {0}\\\\'.format(e[1])
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(e[3])
        t += texTableHLine + '\n'
        if e[4] == True:
            dummy = 'RX'
        else:
            dummy = 'TX'
        t += 'handler:& {0}\\\\'.format(dummy)
        t += texTableHLine + '\n'
        t += texTableEnd

        t += texNewLine
        t += texNewLine
        t += 'code:'
        t += texNewLine

        t += texCodeListing.format(e[5])
    return t

def genImplementations(db, codeListingFlag = True, IncludeListingFlag = True):
    t = ''
    # Implementations
    t += texChapter.format('Implementations')
    
    # groups
    t += texSection.format('Implementation groups')
    L = db.Impl_Group_getList()
    for e in L:
        t += texSubSection.format(buildLatexStr(e[1]))
        t += genCode(e[2], db, codeListingFlag, IncludeListingFlag)
    
    # HAL variables
    t += texSection.format('Implementation of the HAL Variables')
    L = db.Impl_HALVariables_getListSortByGroupAndVarID()
    for e in L:
        # get variable
        v = db.HAL_VariableDefinition_getByVariableID(e[1])
        dummy = v[0][2] + ' ('
        # get group
        if e[4] >= 0:
            g = db.Impl_Group_get(e[4])
            dummy += g[1]
        else:
            dummy += 'no group'
        dummy += ')'
        t += texSubSection.format(buildLatexStr(dummy))
        # build table
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'variable type id:& {0}\\\\'.format(v[0][1])
        t += texTableHLine + '\n'
        t += 'variable type name:& {0}\\\\'.format(buildLatexStr(v[0][2]))
        t += texTableHLine + '\n'
        t += 'group:& {0}\\\\'.format(buildLatexStr(g[1]))
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(buildLatexStr(e[3]))
        t += texTableHLine + '\n'
        t += texTableEnd
        t += genCode(e[2], db, codeListingFlag, IncludeListingFlag)

    # HAL functions
    t += texSection.format('Implementation of the HAL functions')
    L = db.Impl_HALFunction_getListSortByGroupAndFunctionID()
    for e in L:
        # get HAL function
        f = db.HAL_DefFunctions_getFromFunctionID(e[1])
        dummy = f[2] + ' ('
        # get group
        if e[4] >= 0:
            g = db.Impl_Group_get(e[4])
            dummy += g[1]
        else:
            dummy += 'no group'
        dummy += ')'
        t += texSubSection.format(buildLatexStr(dummy))
        # build table
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'function HAL id:& {0}\\\\'.format(f[1])
        t += texTableHLine + '\n'
        t += 'variable type name:& {0}\\\\'.format(buildLatexStr(f[2]))
        t += texTableHLine + '\n'
        t += 'group:& {0}\\\\'.format(buildLatexStr(g[1]))
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(buildLatexStr(e[3]))
        t += texTableHLine + '\n'
        t += texTableEnd
        t += genCode(e[2], db, codeListingFlag, IncludeListingFlag)

    # msg drivers
    t += texSection.format('message system drivers')
    L = db.Impl_ImplMsgDriver_getListSortedByGroup()
    i = 1
    for e in L:
        dummy = 'driver ' +str(i) + ' ('
        # get group
        if e[3] >= 0:
            g = db.Impl_Group_get(e[3])
            dummy += g[1]
        else:
            dummy += 'no group'
        dummy += ')'
        t += texSubSection.format(buildLatexStr(dummy))
        # build table
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(buildLatexStr(e[2]))
        t += texTableHLine + '\n'
        t += texTableEnd
        t += genCode(e[1], db, codeListingFlag, IncludeListingFlag)
        i += 1

    # AP blueprints
    t += texSection.format('audio processor blueprints')
    L = db.Impl_ImplAP_getListSortedByGroup()
    i = 1
    for e in L:
        dummy = 'audio processor blueprint '+str(i) + ' ('
        # get group
        if e[3] >= 0:
            g = db.Impl_Group_get(e[3])
            dummy += g[1]
        else:
            dummy += 'no group'
        dummy += ')'
        t += texSubSection.format(buildLatexStr(dummy))
        # build table
        t += 'Informations:'
        t += texNewLine
        t += texTableStart.format('|p{4cm}|p{10cm}|')
        t += texTableHLine + '\n'
        t += 'description:& {0}\\\\'.format(buildLatexStr(e[2]))
        t += texTableHLine + '\n'
        t += texTableEnd
        t += genCode(e[1], db, codeListingFlag, IncludeListingFlag)
        i += 1
    
    return t


# doc gen options
# optDict = {
# <entry> = (codelisting, includeListing)
# }
# values:
#    definition - generate definition
#    implementation - generate implementation
def genTex (db, options):
    t = ''
    p = options.get('definition', None)
    if p is not None:
        t += genDefinition(db, p[0], p[1])
    p = options.get('implementation', None)
    if p is not None:
        t += genImplementations(db, p[0], p[1])
    return t

def genPDFfileFromLatexStr (lstr, filename):
    directory = tempfile.mkdtemp()
    rand = random.randrange(100000, 999999)
    ltxfile = r'{0}.tex'.format(rand)
    ltxpath = os.path.join(directory, ltxfile)
    
    pdffile = r'{0}.pdf'.format(rand)
    pdfpath = os.path.join(directory, pdffile)

    print (r'dump into {0}'.format(ltxpath))
    f = open(ltxpath, 'wb')
    f.write(lstr)
    f.close()

    cmd = ["pdflatex", "-halt-on-error", "-interaction=batchmode", ltxfile]
        
    #p = subprocess.Popen(cmd, stdout=subprocess.PIPE, cwd=directory)
    p = subprocess.Popen(cmd, stderr=sys.stderr, cwd=directory)
        
    p.wait()
    # Double compilation because of table of content and indexes
    #p = subprocess.Popen(cmd, stdout=subprocess.PIPE, cwd=directory)
    p = subprocess.Popen(cmd, stderr=sys.stderr, cwd=directory)
    p.wait()
    if not os.path.isfile(pdfpath):
        #shutil.rmtree(directory)
        return False
    # copy pdf file
    filepath = os.path.join(os.curdir, filename)
    print (r'try copy {0} to {1}'.format(pdfpath, filepath))
    shutil.copy(pdfpath, filepath)
    shutil.rmtree(directory)
    print (r'finished')
    return True

def APdocgen_generateDoc (db, filename , genOptions = {
            'definition' : (True, True),
            'implementation': (True, True)
        }):
    lstr = texTmplStart.format(title='Audio Processor definition and implementation documentation')
    lstr += genTex(db, genOptions)
    lstr += texTmplEnd
    return genPDFfileFromLatexStr(lstr, filename)

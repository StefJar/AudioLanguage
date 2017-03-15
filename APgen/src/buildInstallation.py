'''
Created on 07.08.2013

@author: StJ
'''

import os
import shutil
import subprocess
import errno

pyScriptsL = [
              'ALasm.py',
              'ALc.py',
              'ALc2.py',
              'ALCFileToCcode.py',
              'AP.db',
              'AP.glade',
              'apBuilder.py',
              'APconfig.py',
              'APDB.py',
              'APdbCreate.sql',
              'APDBxml.py',
              'APdocgen.py',
              'APgenTemplates.xml',
              'APlogger.py',
              'APmsgProcessCompilier.py',
              'benchmark.py',
              'buildInstallation.py',
              'codeGen.py',
              'codeGenXML.py',
              'dbDump.xml',
              'dbInit.xml',
              'DBwindows.py',
              'fileDataExtractor.py',
              'floatwavefile.py',
              'signFilter.py',
              'signGen.py',
              'stjMatPython.py',
              'stjSocket.py',
              # libs
              'libs\\libfftw3f-3.dll',
              'libs\\libsndfile-1.dll',
              'libs\\main.ldf',
              # templates
              'templ/ALcTempl.tex',
              'templ/APbluePrintMultiThread.c',
              'templ/APbluePrintSingleThread.c',
              'templ/headerTempl.h',
              'templ/implTempl.c',
              'templ/mainTempl.c',
              'templ/remoteInterfaceAPTempl.c',
              'templ/remoteInterfaceFrameWork.c',
              'templ/SConstruct.py'

         ]

pyInstallRequiresL=[
          ('ply', 'http://www.dabeaz.com/ply/'),
          #('pygtk', 'http://ftp.gnome.org/pub/GNOME/sources/pygtk/2.24/'),
          ('scons','http://sourceforge.net/projects/scons/files/scons/2.3.0/scons-2.3.0.tar.gz/download')
          #('numpy', ''),
          #('scipy','')
          ]

def copyanything(src, dst):
    try:
        shutil.copytree(src, dst)
    except OSError as exc: # python >2.5
        if exc.errno == errno.ENOTDIR:
            shutil.copy(src, dst)
        else: raise

if __name__ == '__main__':
    datafiles = ''
    pyModules = ''
    pyScipts = ''
    installRequires = ''
    depLinks = ''
    
    print 'building installation'
    print 'copy files into installation dir:'
    destDir = os.path.join(os.getcwd(),'installation')
    if os.path.exists(destDir) == True:
        shutil.rmtree(destDir)
    #os.mkdir(destDir)
    
    # create scripts and copy them

    copyanything('src','installation');
    i = 0
    for p in pyScriptsL:
        if i != 0:
            pyScipts += ', '
        pyScipts += "'"+p+"'"
        i += 1
        
    # installRequires
    i = 0
    for p in pyInstallRequiresL:
        if i != 0:
            installRequires += ', '
            depLinks += ', '
        installRequires += "'" + p[0] + "'"
        depLinks += "'" + p[1] + "'"
        
        i += 1

    print 'build setup.py...'
    
    
    setupText = """
from setuptools import setup, find_packages

setup(name='ALandAP',
      version='1.0',
      description='the complete framework for generating an maintaining Audio Processors plus the Audio Language compilers',
      author='Stefan Jaritz',
      author_email='stefan.jaritz@gmail.com',
      url='',
      packages = find_packages(),
      install_requires=[{installRequires}],
      dependency_links =[{depLinks}],
      data_files=[{datafiles}],
      py_modules = [{pyModules}],
      scripts=[{pyScipts}],
      include_package_data=True,
      zip_safe=False
     )""".format(datafiles=datafiles,installRequires=installRequires,pyModules=pyModules,pyScipts=pyScipts,depLinks=depLinks)
     
    f = open(os.path.join(destDir,'setup.py'), 'w')
    f.write (setupText)
    f.close()
    
    print 'create distribution...'
    print '\tcreate egg and exe file'
    sp = subprocess.Popen(r'python setup.py bdist_egg bdist_wininst', cwd=destDir)
    sp.wait()
    
    print 'copy installation files to the current working directory'
    shutil.copyfile(os.path.join(destDir,'dist','ALandAP-1.0-py2.7.egg'),os.path.join(os.getcwd(),'ALandAP-1.0-py2.7.egg'))
    shutil.copyfile(os.path.join(destDir,'dist','ALandAP-1.0.win32.exe'),os.path.join(os.getcwd(),'ALandAP-1.0.win32.exe'))
    
    print 'delete install dir'
    if os.path.exists(destDir) == True:
        shutil.rmtree(destDir)
    os.mkdir(destDir)

    
    print 'finished'
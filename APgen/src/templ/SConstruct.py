import os
import sys
import platform

from SCons.Script import *

ctools=['default']
if platform.system()=="Windows":
	ctools=['mingw']

myEnv = Environment(tools=ctools,ENV = {'PATH' : @SysPath})
#myEnv = Environment(tools=ctools,ENV = {'PATH' : os.environ['PATH']})
#myEnv = Environment(tools=ctools)
@envSubst


#dict = myEnv.Dictionary()
#keys = dict.keys()
#keys.sort()
#
#for k in keys:
#	print (str(k)+':'+str(dict[k]))

myEnv.Program(
			  target = @ProgName,
			  source = @SrcFiles,
			  LIBS =  @Libs,
			  LIBPATH  = @LibPath,
			  CPPPATH = @CppPath
			  )

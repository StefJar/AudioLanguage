CREATE TABLE ImplGroup (
  idImplGroup INTEGER  NOT NULL  ,
  name TEXT    ,
  idCode INTEGER      ,
PRIMARY KEY(idImplGroup));



CREATE TABLE ImplHALFunction (
  idImplHALFunction INTEGER  NOT NULL  ,
  fid INTEGER    ,
  idCode INTEGER    ,
  descr TEXT    ,
  idImplGroup INTEGER      ,
PRIMARY KEY(idImplHALFunction));



CREATE TABLE ImplHALVariable (
  idImplHALVariable INTEGER  NOT NULL  ,
  VariableID INTEGER    ,
  idCode INTEGER    ,
  descr TEXT    ,
  idImplGroup INTEGER      ,
PRIMARY KEY(idImplHALVariable));



CREATE TABLE ImplAP (
  idImplAP INTEGER  NOT NULL  ,
  idCode INTEGER    ,
  descr TEXT    ,
  idImplGroup INTEGER      ,
PRIMARY KEY(idImplAP));



CREATE TABLE HAL_MessageType (
  idHAL_MessageType INTEGER  NOT NULL  ,
  msgID INTEGER    ,
  name TEXT    ,
  descr TEXT      ,
PRIMARY KEY(idHAL_MessageType));



CREATE TABLE HAL_VariableDefinition (
  idHAL_VariableDefinition INTEGER  NOT NULL  ,
  VariableID INTEGER    ,
  varName TEXT    ,
  description TEXT      ,
PRIMARY KEY(idHAL_VariableDefinition));



CREATE TABLE HAL_VariableIOParameter (
  idHAL_VariableIOParameter INTEGER  NOT NULL  ,
  basicTypeID INTEGER    ,
  VariableID INTEGER    ,
  name TEXT    ,
  description TEXT    ,
  isArray BOOL      ,
PRIMARY KEY(idHAL_VariableIOParameter));



CREATE TABLE pythonScript (
  idpythonScript INTEGER  NOT NULL  ,
  code TEXT      ,
PRIMARY KEY(idpythonScript));



CREATE TABLE testPattern (
  idtestPattern INTEGER  NOT NULL  ,
  name TEXT    ,
  descr TEXT    ,
  idAP INTEGER    ,
  idALASMprogramm INTEGER    ,
  idpythonProgramm INTEGER    ,
  idMatlabProgramm INTEGER    ,
  idPythonInitScript INTEGER    ,
  idPythonExitScript INTEGER      ,
PRIMARY KEY(idtestPattern));



CREATE TABLE VariableList (
  idVariableList INTEGER  NOT NULL  ,
  idAP INTEGER    ,
  idImplHALVariable INTEGER      ,
PRIMARY KEY(idVariableList));



CREATE TABLE MatlabProgramm (
  idMatlabProgramm INTEGER  NOT NULL  ,
  code TEXT      ,
PRIMARY KEY(idMatlabProgramm));



CREATE TABLE ImplMsgDriver (
  idImplMsgDriver INTEGER  NOT NULL  ,
  idCode INTEGER    ,
  descr TEXT    ,
  idImplGroup INTEGER      ,
PRIMARY KEY(idImplMsgDriver));



CREATE TABLE IncludeList (
  idCode INTEGER  NOT NULL  ,
  idIncludes INTEGER  NOT NULL  );



CREATE TABLE Includes (
  idIncludes INTEGER  NOT NULL  ,
  includefile TEXT    ,
  lib TEXT    ,
  syslib BOOL      ,
PRIMARY KEY(idIncludes));



CREATE TABLE HAL_MessageProcess (
  idHAL_MessageProcess INTEGER  NOT NULL  ,
  msgProcID INTEGER    ,
  name TEXT    ,
  descr TEXT    ,
  isRX BOOL    ,
  msgCode TEXT      ,
PRIMARY KEY(idHAL_MessageProcess));



CREATE TABLE Compiler (
  idCompiler INTEGER  NOT NULL  ,
  name TEXT    ,
  description TEXT    ,
  OperatingSystem TEXT    ,
  CC TEXT    ,
  CXX TEXT    ,
  ASM TEXT    ,
  AR TEXT    ,
  LINK TEXT    ,
  CCFLAGS TEXT    ,
  OBJSUFFIX TEXT    ,
  CCCOM TEXT    ,
  CXXCOM TEXT    ,
  CXXFLAGS TEXT    ,
  LINKCOM TEXT    ,
  LINKFLAGS TEXT      ,
PRIMARY KEY(idCompiler));



CREATE TABLE CompilerIncludePath (
  idCompilerIncludePath INTEGER  NOT NULL  ,
  idCompiler INTEGER    ,
  path TEXT      ,
PRIMARY KEY(idCompilerIncludePath));



CREATE TABLE CompilerLib (
  idCompilerLib INTEGER  NOT NULL  ,
  idCompiler INTEGER    ,
  lib TEXT      ,
PRIMARY KEY(idCompilerLib));



CREATE TABLE Code (
  idCode INTEGER  NOT NULL  ,
  code TEXT      ,
PRIMARY KEY(idCode));



CREATE TABLE ALASMprogramm (
  idALASMprogramm INTEGER  NOT NULL  ,
  code TEXT      ,
PRIMARY KEY(idALASMprogramm));



CREATE TABLE AP (
  idAP INTEGER  NOT NULL  ,
  name TEXT    ,
  idCompiler INTEGER    ,
  descr TEXT    ,
  idCodeStartup INTEGER      ,
PRIMARY KEY(idAP));



CREATE TABLE APList (
  idAPList INTEGER  NOT NULL  ,
  idAP INTEGER    ,
  idImplAP INTEGER      ,
PRIMARY KEY(idAPList));



CREATE TABLE HAL_Function (
  idHAL_Function INTEGER  NOT NULL  ,
  fid INTEGER    ,
  name TEXT    ,
  descr TEXT      ,
PRIMARY KEY(idHAL_Function));



CREATE TABLE HAL_FunctionsParameter (
  idHAL_FunctionsParameter INTEGER  NOT NULL  ,
  fid INTEGER    ,
  name TEXT    ,
  descr TEXT    ,
  idParameterClass INTEGER    ,
  idParameterType INTEGER      ,
PRIMARY KEY(idHAL_FunctionsParameter));



CREATE TABLE HAL_MessageParameter (
  idHAL_MessageParameter INTEGER  NOT NULL  ,
  msgID INTEGER    ,
  positionIndex INTEGER    ,
  name TEXT    ,
  descr TEXT    ,
  basicTypeID INTEGER    ,
  isArray BOOL      ,
PRIMARY KEY(idHAL_MessageParameter));



CREATE TABLE HAL_basicIOTypes (
  idHAL_IOTypesDefinition INTEGER  NOT NULL  ,
  TypeID INTEGER    ,
  TypeName TEXT    ,
  description TEXT    ,
  cType TEXT    ,
  endianType BOOL    ,
  sizeInBytes INTEGER      ,
PRIMARY KEY(idHAL_IOTypesDefinition));



CREATE TABLE CompilerLibPath (
  idCompilerLibPath INTEGER  NOT NULL  ,
  idCompiler INTEGER    ,
  path TEXT      ,
PRIMARY KEY(idCompilerLibPath));



CREATE TABLE DriverList (
  idDriverList INTEGER  NOT NULL  ,
  idAP INTEGER    ,
  idImplMsgDriver INTEGER      ,
PRIMARY KEY(idDriverList));



CREATE TABLE FunctionList (
  idFunctionList INTEGER  NOT NULL  ,
  idAP INTEGER    ,
  idImplHALFunction INTEGER      ,
PRIMARY KEY(idFunctionList));

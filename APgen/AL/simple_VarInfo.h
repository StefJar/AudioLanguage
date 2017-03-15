// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="y", .typeID=1}, 
	{.szName="x", .typeID=1}, 
	{.szName="#const1", .typeID=1}, 
};

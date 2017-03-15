// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="s2", .typeID=3}, 
	{.szName="s1", .typeID=3}, 
	{.szName="#const1", .typeID=3}, 
};

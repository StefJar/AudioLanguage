// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="bqf1", .typeID=10}, 
	{.szName="bqf2", .typeID=10}, 
	{.szName="out1", .typeID=1}, 
	{.szName="out2", .typeID=1}, 
	{.szName="fs", .typeID=1}, 
	{.szName="f", .typeID=1}, 
	{.szName="in1", .typeID=1}, 
	{.szName="in2", .typeID=1}, 
	{.szName="#const9", .typeID=1}, 
	{.szName="#const10", .typeID=1}, 
};

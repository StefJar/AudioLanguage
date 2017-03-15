// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="bqf1", .typeID=10}, 
	{.szName="bqf2", .typeID=10}, 
	{.szName="f2", .typeID=1}, 
	{.szName="fs", .typeID=1}, 
	{.szName="d", .typeID=103}, 
	{.szName="g", .typeID=1}, 
	{.szName="f", .typeID=1}, 
	{.szName="q", .typeID=1}, 
	{.szName="p", .typeID=100}, 
	{.szName="bRight", .typeID=101}, 
	{.szName="bLeft", .typeID=101}, 
	{.szName="bMiddle", .typeID=101}, 
	{.szName="tstr", .typeID=3}, 
	{.szName="#const1", .typeID=3}, 
	{.szName="#const2", .typeID=1}, 
	{.szName="#const3", .typeID=1}, 
	{.szName="#const4", .typeID=1}, 
	{.szName="#const5", .typeID=1}, 
	{.szName="#const6", .typeID=1}, 
	{.szName="#const7", .typeID=1}, 
	{.szName="#const8", .typeID=1}, 
};

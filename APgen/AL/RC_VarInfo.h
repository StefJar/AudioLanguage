// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="uiState", .typeID=2}, 
	{.szName="ub1", .typeID=101}, 
	{.szName="ub2", .typeID=101}, 
	{.szName="ub3", .typeID=101}, 
	{.szName="gain", .typeID=1}, 
	{.szName="db1", .typeID=101}, 
	{.szName="db3", .typeID=101}, 
	{.szName="db2", .typeID=101}, 
	{.szName="db5", .typeID=101}, 
	{.szName="db4", .typeID=101}, 
	{.szName="pan", .typeID=100}, 
	{.szName="dis", .typeID=103}, 
	{.szName="#const11", .typeID=2}, 
	{.szName="#fv_checkUI_gainStr", .typeID=3}, 
	{.szName="#fv_checkUI_gaintext", .typeID=3}, 
	{.szName="#const1", .typeID=3}, 
	{.szName="#const2", .typeID=1}, 
	{.szName="#const3", .typeID=2}, 
	{.szName="#const4", .typeID=1}, 
	{.szName="#const5", .typeID=1}, 
	{.szName="#const6", .typeID=1}, 
	{.szName="#const8", .typeID=3}, 
	{.szName="#const9", .typeID=2}, 
	{.szName="#const10", .typeID=3}, 
};

// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="bqf1", .typeID=10}, 
	{.szName="bqf2", .typeID=10}, 
	{.szName="gaintext", .typeID=3}, 
	{.szName="gainStr", .typeID=3}, 
	{.szName="bHP", .typeID=101}, 
	{.szName="p", .typeID=100}, 
	{.szName="fLP", .typeID=1}, 
	{.szName="bDown", .typeID=101}, 
	{.szName="bReset", .typeID=101}, 
	{.szName="fHP", .typeID=1}, 
	{.szName="fs", .typeID=1}, 
	{.szName="byPassFlag", .typeID=2}, 
	{.szName="in1", .typeID=1}, 
	{.szName="in2", .typeID=1}, 
	{.szName="gain", .typeID=1}, 
	{.szName="out1", .typeID=1}, 
	{.szName="out2", .typeID=1}, 
	{.szName="d", .typeID=103}, 
	{.szName="g", .typeID=1}, 
	{.szName="bUp", .typeID=101}, 
	{.szName="bLP", .typeID=101}, 
	{.szName="q", .typeID=1}, 
	{.szName="bBypass", .typeID=101}, 
	{.szName="bBP", .typeID=101}, 
	{.szName="#const1", .typeID=1}, 
	{.szName="#const2", .typeID=1}, 
	{.szName="#const3", .typeID=1}, 
	{.szName="#const4", .typeID=1}, 
	{.szName="#const5", .typeID=1}, 
	{.szName="#const6", .typeID=2}, 
	{.szName="#const7", .typeID=3}, 
	{.szName="#const8", .typeID=3}, 
	{.szName="#const9", .typeID=1}, 
	{.szName="#const10", .typeID=1}, 
	{.szName="#const11", .typeID=3}, 
	{.szName="#const12", .typeID=1}, 
	{.szName="#const13", .typeID=3}, 
	{.szName="#const14", .typeID=3}, 
	{.szName="#const15", .typeID=2}, 
	{.szName="#const16", .typeID=3}, 
	{.szName="#const17", .typeID=3}, 
	{.szName="#const18", .typeID=3}, 
};

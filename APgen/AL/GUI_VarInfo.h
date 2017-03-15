// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="impactNoiseBypass", .typeID=2}, 
	{.szName="compressor", .typeID=13}, 
	{.szName="noiseG", .typeID=11}, 
	{.szName="gain", .typeID=1}, 
	{.szName="impactNoiseF", .typeID=10}, 
	{.szName="sens", .typeID=1}, 
	{.szName="EQ", .typeID=10}, 
	{.szName="panLeft", .typeID=1}, 
	{.szName="#fv_UI_txtOpening", .typeID=3}, 
	{.szName="#fv_UI_lGreen", .typeID=102}, 
	{.szName="#fv_UI_d", .typeID=103}, 
	{.szName="#fv_UI_txtFloorNoiseFon", .typeID=3}, 
	{.szName="#fv_UI_txtFloorNoiseFoff", .typeID=3}, 
	{.szName="#fv_UI_state", .typeID=2}, 
	{.szName="#fv_UI_p", .typeID=100}, 
	{.szName="#fv_UI_bRight", .typeID=101}, 
	{.szName="#fv_UI_txtFloorNoiseSelect", .typeID=3}, 
	{.szName="#fv_UI_bLeft", .typeID=101}, 
	{.szName="#fv_UI_lRed", .typeID=102}, 
	{.szName="#fv_UI_bMiddle", .typeID=101}, 
	{.szName="#fv_UI_dispalyStr", .typeID=3}, 
	{.szName="#fv_UI_tstr", .typeID=3}, 
	{.szName="#const8", .typeID=3}, 
	{.szName="#const9", .typeID=3}, 
	{.szName="#const10", .typeID=3}, 
	{.szName="#const11", .typeID=3}, 
	{.szName="#const12", .typeID=3}, 
	{.szName="#const13", .typeID=2}, 
	{.szName="#const14", .typeID=3}, 
	{.szName="#const15", .typeID=2}, 
};

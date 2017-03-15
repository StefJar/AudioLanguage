// variables names 
typedef struct SVarDebugInfo {
    const char *    szName; //!< name of the variable
    int             typeID; //!< var type id
} TVarDebugInfo;

// global variable holding the debug info of the variables
const TVarDebugInfo gVarDebugInfo [] = {
	{.szName="uiUpdate", .typeID=2}, 
	{.szName="uiFilterTypeSel", .typeID=2}, 
	{.szName="uiFilterIndex", .typeID=2}, 
	{.szName="LoutFilter", .typeID=10}, 
	{.szName="RoutInpSel", .typeID=2}, 
	{.szName="RinFilter", .typeID=10}, 
	{.szName="bDown", .typeID=101}, 
	{.szName="uiFilterBankSel", .typeID=2}, 
	{.szName="fquality", .typeID=1}, 
	{.szName="fs", .typeID=1}, 
	{.szName="uiSel", .typeID=2}, 
	{.szName="volume", .typeID=1}, 
	{.szName="RoutFilter", .typeID=10}, 
	{.szName="ffreq", .typeID=1}, 
	{.szName="LoutInpSel", .typeID=2}, 
	{.szName="d", .typeID=103}, 
	{.szName="bUp", .typeID=101}, 
	{.szName="bSelect", .typeID=101}, 
	{.szName="LinFilter", .typeID=10}, 
	{.szName="uiMenuSel", .typeID=2}, 
	{.szName="p", .typeID=100}, 
	{.szName="fgain", .typeID=1}, 
	{.szName="uiSelChannel", .typeID=2}, 
	{.szName="uiState", .typeID=2}, 
	{.szName="inL", .typeID=1}, 
	{.szName="outR", .typeID=1}, 
	{.szName="outL", .typeID=1}, 
	{.szName="inR", .typeID=1}, 
	{.szName="#const37", .typeID=2}, 
	{.szName="#const38", .typeID=2}, 
	{.szName="#const39", .typeID=2}, 
	{.szName="#const40", .typeID=1}, 
	{.szName="#fv_dspInit_i", .typeID=2}, 
	{.szName="#const98", .typeID=2}, 
	{.szName="#const99", .typeID=1}, 
	{.szName="#const102", .typeID=1}, 
};

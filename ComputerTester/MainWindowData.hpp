#pragma once
struct MainWindowData {
	NONCLIENTMETRICS ncm;
	HFONT hFont;
	HWND local_box, network_box, performance_box;
	TesterWindowData* avpresent_data;
	TesterWindowData* avworking_data;
	TesterWindowData* unknownexe_data;
	TesterWindowData* swapexe_data;
	TesterWindowData* returnexe_data;
	TesterWindowData* connection_data;
	TesterWindowData* fwpresent_data;
	TesterWindowData* fwworking_data;
	TesterWindowData* dleicar_data;
	TesterWindowData* disksfull_data;
public:
	~MainWindowData();
};
#pragma once
struct MainWindowData {
	NONCLIENTMETRICS ncm;
	HFONT hFont;
	HWND local_box;
	TesterWindowData* avpresent_data;
	TesterWindowData* avworking_data;
	TesterWindowData* unknownexe_data;
	TesterWindowData* swapexe_data;
	TesterWindowData* returnexe_data;
public:
	~MainWindowData();
};
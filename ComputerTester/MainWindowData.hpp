#pragma once
struct MainWindowData {
	NONCLIENTMETRICS ncm;
	HFONT hFont;
	std::vector<HWND> boxes;
	std::vector<std::vector<TesterWindowData*>*> datas;
	std::map<HMENU, TesterWindowData*> menus;
	int y;
	unsigned int dpi;
public:
	~MainWindowData();
	static const int external_margin, internal_margin, tester_height;
};
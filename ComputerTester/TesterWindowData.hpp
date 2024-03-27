class TesterWindowData {
	HWND static_wnd, edit_wnd, button_wnd;
	HWND window;
	LPCWSTR static_text;
	HMENU menu;
	Tester* tester;

	TesterWindowData();

public:
	~TesterWindowData();

	TesterWindowData(HWND parent, HMENU menu, LPCWSTR text, Tester* tester);

	HWND getWindow();
	Tester* getTester();
	void SetText(LPCWSTR text);

	friend LRESULT CALLBACK TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
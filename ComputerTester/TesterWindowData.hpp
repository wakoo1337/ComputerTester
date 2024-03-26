class TesterWindowData {
	HWND static_wnd, edit_wnd, button_wnd;
	HWND window;
	LPCWSTR static_text;
	Tester* tester;

	TesterWindowData();

public:
	~TesterWindowData();

	TesterWindowData(HWND parent, LPCWSTR text, Tester* tester);

	HWND getWindow();

	friend LRESULT CALLBACK TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
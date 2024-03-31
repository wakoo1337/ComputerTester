class TesterWindowData final {
	HWND static_wnd, edit_wnd, button_wnd;
	HWND window;
	LPCWSTR static_text;
	HMENU menu;
	Tester* tester;
	HANDLE thread;

	TesterWindowData();

public:
	~TesterWindowData();

	TesterWindowData(HWND parent, HMENU menu, LPCWSTR text, Tester* tester);

	HWND getWindow();
	void PerformTest();
	void FinishTest();
	LPCWSTR GetTesterResult();
	LPCWSTR GetStaticText();

	friend LRESULT CALLBACK TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	friend DWORD WINAPI TesterThreadWrapper(LPVOID lpParameter);
};
class TesterWindowData final {
	HWND static_wnd, edit_wnd, button_wnd;
	HWND window;
	LPCWSTR static_text;
	HMENU menu;
	Tester* tester;
	HANDLE thread;
	int height;

	TesterWindowData();

public:
	~TesterWindowData();

	TesterWindowData(HWND parent, HMENU menu, LPCWSTR text, int height, Tester* tester);

	HWND getWindow();
	void PerformTest();
	void FinishTest();
	int GetHeight();
	LPCWSTR GetTesterResult();
	LPCWSTR GetStaticText();

	friend LRESULT CALLBACK TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	friend DWORD WINAPI TesterThreadWrapper(LPVOID lpParameter);

	static const int static_width, button_width, interval;
};
// ComputerTester.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "ComputerTester.h"
#include "Tester.hpp"
#include "testers.hpp"
#include "TesterInitData.hpp"
#include "TesterWindowData.hpp"
#include "MainWindowData.hpp"

#define MAX_LOADSTRING 100

// Глобальные переменные:

HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szTesterClass[MAX_LOADSTRING];			// имя класса окна тестера

// Отправить объявления функций, включенных в этот модуль кода:
VOID                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_COMPUTERTESTER, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TESTERNAME, szTesterClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMPUTERTESTER));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CoUninitialize();

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
VOID MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(MainWindowData*);
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMPUTERTESTER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COMPUTERTESTER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	WNDCLASSEXW wcex2;

	wcex2.cbSize = sizeof(WNDCLASSEX);
	wcex2.style = CS_HREDRAW | CS_VREDRAW;
	wcex2.lpfnWndProc = TesterWndProc;
	wcex2.cbClsExtra = 0;
	wcex2.cbWndExtra = sizeof(TesterWindowData*);
	wcex2.hInstance = hInstance;
	wcex2.hIcon = NULL;
	wcex2.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex2.lpszMenuName = NULL;
	wcex2.lpszClassName = szTesterClass;
	wcex2.hIconSm = NULL;

	RegisterClassEx(&wcex);
	RegisterClassEx(&wcex2);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) return FALSE;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 720, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK TesterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	TesterWindowData* data_struct;
	data_struct = (TesterWindowData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#define STATIC_WIDTH 120
#define BUTTON_WIDTH 40
#define INTERVAL 10
	switch (message) {
	case WM_CREATE:
		CREATESTRUCT* cs;
		cs = (CREATESTRUCT*)lParam;
		data_struct = (TesterWindowData*)cs->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)data_struct);
		data_struct->static_wnd = CreateWindowEx(0, L"static", data_struct->static_text, WS_CHILD | WS_VISIBLE, 0, 0, STATIC_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
		data_struct->edit_wnd = CreateWindowEx(0, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY | ES_MULTILINE, STATIC_WIDTH + INTERVAL, 0, cs->cx - 2 * INTERVAL - STATIC_WIDTH - BUTTON_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
		data_struct->button_wnd = CreateWindowEx(0, L"button", L"Тест", WS_CHILD | WS_VISIBLE, cs->cx - BUTTON_WIDTH, 0, BUTTON_WIDTH, cs->cy, hWnd, data_struct->menu, hInst, nullptr);
		break;
	case WM_SETFONT:
		SendMessage(data_struct->static_wnd, WM_SETFONT, wParam, lParam);
		SendMessage(data_struct->edit_wnd, WM_SETFONT, wParam, lParam);
		SendMessage(data_struct->button_wnd, WM_SETFONT, wParam, lParam);
		break;
	case WM_SIZE:
	{
		const int width = LOWORD(lParam);
		const int height = HIWORD(lParam);
		SetWindowPos(data_struct->static_wnd, HWND_TOP, 0, 0, STATIC_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		SetWindowPos(data_struct->edit_wnd, HWND_TOP, STATIC_WIDTH + INTERVAL, 0, width - 2 * INTERVAL - STATIC_WIDTH - BUTTON_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		SetWindowPos(data_struct->button_wnd, HWND_TOP, width - BUTTON_WIDTH, 0, BUTTON_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
	};
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == (WORD)data_struct->menu) data_struct->PerformTest();
		else return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

#define EXTERNAL_MARGIN 20
#define INTERNAL_MARGIN 20
#define TESTER_HEIGHT 30

void PositionElements(std::vector<TesterWindowData*>& datas, int width, int& y) {
	std::for_each(datas.cbegin(), datas.cend(), [&y, width](TesterWindowData* twd) {
		SetWindowPos(twd->getWindow(), HWND_TOP,
		EXTERNAL_MARGIN + INTERNAL_MARGIN,
		y,
		width - 2 * (EXTERNAL_MARGIN + INTERNAL_MARGIN),
		twd->GetHeight(),
		SWP_NOACTIVATE | SWP_SHOWWINDOW);
	y += INTERNAL_MARGIN + twd->GetHeight();
		}
	); y += INTERNAL_MARGIN;
};

#define WM_THREADWAIT WM_USER+0 // В lParam - указатель на TesterWindowData

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static const std::vector<LPCWSTR> box_names = { L"Локальная безопасность", L"Сетевая безопасность", L"Производительность" };
	MainWindowData* data_struct;
	data_struct = (MainWindowData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	switch (message)
	{
	case WM_CREATE:
	{
		try {
			data_struct = new MainWindowData;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)data_struct);
			data_struct->ncm.cbSize = sizeof(NONCLIENTMETRICS);
			if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &data_struct->ncm, 0)) {
				data_struct->hFont = CreateFontIndirect(&data_struct->ncm.lfMenuFont);
				if (data_struct->hFont) {
					CREATESTRUCT* cs;
					cs = (CREATESTRUCT*)lParam;
					static const std::vector<std::vector<TesterInitData>*> inits = {
						new std::vector<TesterInitData> {
							{L"Проверить наличие антивируса", (HMENU)IDM_AVPRESENT, TESTER_HEIGHT, new CheckInstallAntivirus},
							{L"Проверить работоспособность антивируса", (HMENU)IDM_AVWORKS, TESTER_HEIGHT, new Tester},
							{L"Неизвестный EXE", (HMENU)IDM_UNKNOWNEXE, TESTER_HEIGHT, new Tester},
							{L"Подмена EXE", (HMENU)IDM_SWAPEXE, TESTER_HEIGHT, new Tester},
							{L"Вернуть EXE", (HMENU)IDM_RETURNEXE, TESTER_HEIGHT, new Tester},
						},
						new std::vector<TesterInitData> {
							{L"Проверить подключение к Интернету", (HMENU)IDM_INETCONNECTED, TESTER_HEIGHT, new InetConnectedTester},
							{L"Проверить наличие МСЭ", (HMENU)IDM_FWPRESENT, TESTER_HEIGHT, new FireWallTester},
							{L"Проверить работоспособность МСЭ", (HMENU)IDM_FWWORKS, TESTER_HEIGHT, new FireWallWorkTester},
							{L"Скачать EICAR", (HMENU)IDM_DLEICAR, TESTER_HEIGHT, new Tester},
						},
						new std::vector<TesterInitData> {
							{L"Проверить заполнение дисков", (HMENU)IDM_DISKSFULL, 3 * TESTER_HEIGHT, new DiskSpaceTester},
						}
					};
					assert(box_names.size() == inits.size());
					data_struct->y = EXTERNAL_MARGIN + INTERNAL_MARGIN;
					int old_y = data_struct->y;
					for (unsigned int j = 0; j < inits.size(); j++) {
						std::vector<TesterInitData> inits_part = *inits.at(j);
						std::vector<TesterWindowData*>* testers = new std::vector<TesterWindowData*>;
						for (unsigned int i = 0; i < inits_part.size(); i++) {
							TesterInitData tid;
							tid = inits_part.at(i);
							TesterWindowData* twd;
							twd = new TesterWindowData(hWnd, tid.menu, tid.static_name, tid.height, tid.tester);
							SendMessage(twd->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
							testers->push_back(twd);
							data_struct->menus[tid.menu] = twd;
						};
						data_struct->datas.push_back(testers);
						PositionElements(*data_struct->datas.at(j), cs->cx, data_struct->y);
						HWND new_box = CreateWindowEx(0, L"button", box_names.at(j), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, cs->cx - 2 * EXTERNAL_MARGIN, data_struct->y - old_y, hWnd, NULL, hInst, NULL);
						SendMessage(new_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
						data_struct->boxes.push_back(new_box);
						data_struct->y += EXTERNAL_MARGIN;
						old_y = data_struct->y;
					}
					data_struct->y -= data_struct->datas.size() * INTERNAL_MARGIN;
					SCROLLINFO si;
					si.cbSize = sizeof(SCROLLINFO);
					si.fMask = SIF_ALL;
					si.nMin = 0;
					si.nMax = data_struct->y;
					si.nPage = cs->cy;
					si.nPos = si.nTrackPos = 0;
					SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
				}
			}
			else return -1;
		}
		catch (std::bad_alloc ba) {
			return -1;
		}
	}
	break;
	case WM_DESTROY:
	{
		delete data_struct;
		PostQuitMessage(0);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_SAVETXT:
		{
			static const COMDLG_FILTERSPEC txt_filter{ L"Текстовые файлы (*.txt)", L"*.txt" };
			IFileSaveDialog* save_dialog;
			IShellItem* shell_item;
			LPWSTR path;
			HRESULT hResult;
			hResult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (LPVOID*)&save_dialog);
			if (SUCCEEDED(hResult)) {
				if (SUCCEEDED(hResult = save_dialog->SetFileTypes(1, &txt_filter)) &&
					SUCCEEDED(hResult = save_dialog->SetTitle(L"Выберите путь для сохранения файла")) &&
					SUCCEEDED(hResult = save_dialog->SetOptions(FOS_NOCHANGEDIR)) &&
					SUCCEEDED(hResult = save_dialog->Show(hWnd)) &&
					SUCCEEDED(hResult = save_dialog->GetResult(&shell_item))) {
					if (SUCCEEDED(hResult = shell_item->GetDisplayName(SIGDN_FILESYSPATH, &path))) {
						{
							try {
								std::wofstream out_stream(path, std::ios::out | std::ios::trunc);
								out_stream.imbue(std::locale("en_US.UTF-8"));
								std::chrono::system_clock::time_point sysclk = std::chrono::system_clock::now();
								out_stream << L"Отчёт за " << sysclk << std::endl;
								int c = 0;
								for (int j = 0; j < data_struct->datas.size(); j++) {
									out_stream << box_names.at(j) << std::endl;
									for (int i = 0; i < data_struct->datas.at(i)->size(); i++) {
										c++;
										TesterWindowData* twd = data_struct->datas.at(j)->at(i);
										out_stream << c << L". " << twd->GetStaticText() << L" : " << twd->GetTesterResult() << std::endl;
									}
								};
								out_stream.close();
							}
							catch (std::wofstream::failure fail) {
								const char* what = fail.what();
								MessageBoxExA(hWnd, what, "Cannot save file", MB_OK | MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
							}
						}
						CoTaskMemFree(path);
					}
					shell_item->Release();
				};
				save_dialog->Release();
			};
		}
		break;
		default:
		{
			std::map<HMENU, TesterWindowData*>::iterator found = data_struct->menus.find((HMENU)wmId);
			if (found != data_struct->menus.end()) found->second->PerformTest();
			else return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}
	}
	break;
	case WM_SIZE:
	{
		const int width = LOWORD(lParam);
		const int height = HIWORD(lParam);
		int y = EXTERNAL_MARGIN + INTERNAL_MARGIN;
		int old_y = y;
		for (unsigned int j = 0; j < data_struct->datas.size(); j++) {
			PositionElements(*(data_struct->datas.at(j)), width, y);
			SetWindowPos(data_struct->boxes.at(j), HWND_TOP, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, width - 2 * EXTERNAL_MARGIN, y - old_y, SWP_NOACTIVATE | SWP_SHOWWINDOW);
			old_y = y;
		};
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
		GetScrollInfo(hWnd, SB_VERT, &si);
		si.nMax = data_struct->y;
		si.nPage = height;
		si.nPos = max(0, min(si.nMax, si.nPos));
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
	}
	break;
	case WM_VSCROLL:
	{
		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS | SIF_RANGE;
		GetScrollInfo(hWnd, SB_VERT, &si);
		int old_pos = si.nPos;
		switch (LOWORD(wParam)) {
		case SB_TOP:
			si.nPos = si.nMin;
			break;
		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			si.nPos = HIWORD(wParam);
			break;
		};
		si.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hWnd, SB_VERT, &si);
		ScrollWindowEx(hWnd, 0, old_pos - si.nPos, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN | SW_ERASE | SW_INVALIDATE);
		UpdateWindow(hWnd);
	}
	break;
	case WM_THREADWAIT:
	{
		TesterWindowData* twd;
		twd = (TesterWindowData*)lParam;
		twd->FinishTest();
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

TesterWindowData::TesterWindowData(HWND parent, HMENU menu, LPCWSTR text, int height, Tester* tester) : tester{ tester }, thread{ 0 }, button_wnd{ nullptr }, static_wnd{ nullptr }, edit_wnd{ nullptr }, static_text{ text }, menu{ menu }, height{ height } {
	this->window = CreateWindowExW(0, szTesterClass, text, WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, parent, menu, hInst, this);
};

HWND TesterWindowData::getWindow() {
	return window;
};

DWORD WINAPI TesterThreadWrapper(LPVOID lpParameter) {
	TesterWindowData* twd;
	twd = (TesterWindowData*)lpParameter;
	twd->tester->DoTest();
	SetWindowText(twd->edit_wnd, twd->GetTesterResult());
	PostMessage(GetParent(twd->window), WM_THREADWAIT, 0, (LPARAM)twd);
	return 0;
};

void TesterWindowData::PerformTest() {
	if (thread == 0) {
		thread = CreateThread(NULL, 0, &TesterThreadWrapper, this, 0, NULL);
		EnableWindow(this->button_wnd, FALSE);
	}
	else MessageBoxExW(GetParent(window), L"Тест уже идёт", L"Невозможно запустить тест", MB_OK | MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
};

void TesterWindowData::FinishTest() {
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	thread = 0;
	EnableWindow(this->button_wnd, TRUE);
};

int TesterWindowData::GetHeight() {
	return height;
};

LPCWSTR TesterWindowData::GetTesterResult() {
	return tester->GetResult();
};

LPCWSTR TesterWindowData::GetStaticText() {
	return static_text;
};

TesterWindowData::~TesterWindowData() {
	DestroyWindow(static_wnd);
	DestroyWindow(edit_wnd);
	DestroyWindow(button_wnd);
	DestroyWindow(window);
	delete tester;
};

MainWindowData::~MainWindowData() {
	for (HWND box : boxes) DestroyWindow(box);
	for (std::vector<TesterWindowData*>* vec : datas) {
		vec->clear();
		delete vec;
	};
	DeleteObject(hFont);
};

Tester::Tester() : result{ L"Неизвестно" }, allocated{ false } {};

void Tester::DoTest() {};

LPCWSTR Tester::GetResult() {
	return result;
}

void Tester::SetResult(LPCWSTR result, bool allocated) {
	if (this->allocated) delete[] this->result;
	this->result = result;
	this->allocated = allocated;
};

InetConnectedTester::InetConnectedTester() : Tester() {};

void InetConnectedTester::DoTest() {
	DWORD flags;
	SetResult(InternetGetConnectedState(&flags, 0) ? L"Интернет доступен" : L"Интернет недоступен", false);
}

FireWallTester::FireWallTester() : Tester() {};

void FireWallTester::DoTest() {
	std::filesystem::path filePath("C:\\Program Files\\COMODO\\COMODO Internet Security\\cis.exe");
	if (std::filesystem::exists(filePath)) {
		SetResult(L"МЭ установлен", false);
	}
	else {
		SetResult(L"МЭ не установлен", false);
	}
}

FireWallWorkTester::FireWallWorkTester() : Tester() {};
void FireWallWorkTester::DoTest() {
	HINTERNET hInternet = InternetOpen(L"FireWallWorkTester", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet) {
		SetResult(L"Ошибка при открытии сессии интернета", false);
		return;
	}

	HINTERNET hUrl = InternetOpenUrl(hInternet, L"https://ya.ru", NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hUrl) {
		InternetCloseHandle(hInternet);
		SetResult(L"МЭ функционирует правильно", false);
		return;
	}

	InternetCloseHandle(hUrl);
	InternetCloseHandle(hInternet);

	SetResult(L"МЭ функционирует не правильно", false);
}
CheckInstallAntivirus::CheckInstallAntivirus() :Tester() {};
void CheckInstallAntivirus::DoTest() {
	SetResult(L"Антивирус не установлен!", false);

	std::vector<std::wstring> antiv = {
		L"Dr.Web Security Space",
		L"Kaspersky Internet Security",
		L"Kaspersky Total Security",
		L"Avast Internet Security",
		L"Avast! Pro Antivirus"
	};

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {
		DWORD count_subkey;
		if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &count_subkey, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			std::vector<std::wstring> software_list;
			for (DWORD i = 0; i < count_subkey; ++i) {
				std::wstring softwareName;
				try {
					WCHAR asubkey_name[255];
					DWORD size = sizeof(asubkey_name);
					if (RegEnumKeyEx(hKey, i, asubkey_name, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
						HKEY hSubKey;
						if (RegOpenKeyEx(hKey, asubkey_name, 0, KEY_READ | KEY_WOW64_64KEY, &hSubKey) == ERROR_SUCCESS) {
							WCHAR displayName[1024];
							DWORD dataSize = sizeof(displayName);
							if (RegQueryValueEx(hSubKey, L"DisplayName", NULL, NULL, (LPBYTE)displayName, &dataSize) == ERROR_SUCCESS) {
								softwareName = displayName;
								software_list.push_back(softwareName);
								if (std::find(antiv.begin(), antiv.end(), softwareName) != antiv.end()) {
									SetResult(L"Антивирус установлен!", false);
									break;
								}
							}
							RegCloseKey(hSubKey);
						}
					}
				}
				catch (...) {
					continue;
				}
			}
		}
		RegCloseKey(hKey);
	}
}
DiskSpaceTester::DiskSpaceTester() :Tester() {};
void DiskSpaceTester::DoTest() {
	const double GB_DIVISOR = 1024.0 * 1024.0 * 1024.0;
	DWORD drives = GetLogicalDrives();
	std::wstringstream ss;

	for (int i = 0; i < 26; i++) {
		if (drives & (1 << i)) {
			char driveLetter = 'A' + i;
			char drivePath[4] = { driveLetter, ':', '\\', '\0' };

			ULARGE_INTEGER freeBytesAvailableToCaller;
			ULARGE_INTEGER totalNumberOfBytes;
			ULARGE_INTEGER totalNumberOfFreeBytes;

			if (GetDiskFreeSpaceExA(drivePath, &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
				// Преобразование размеров из байтов в гигабайты
				double freeGB = static_cast<double>(totalNumberOfFreeBytes.QuadPart) / GB_DIVISOR;
				double totalGB = static_cast<double>(totalNumberOfBytes.QuadPart) / GB_DIVISOR;

				ss << L"Drive " << driveLetter << L": has " << std::setprecision(2) << std::fixed << freeGB << L" GB free out of " << totalGB << L" GB total.\r\n";
			}
			else {
				ss << L"Failed to get disk space for drive " << driveLetter << L"\r\n";
			}
		}
	}

	std::wstring resultStr = ss.str();

	WCHAR* res = new WCHAR[resultStr.size() + 1];
	res[resultStr.size()] = L'\0';
	std::copy(resultStr.cbegin(), resultStr.cend(), res);

	SetResult(res, true);
}



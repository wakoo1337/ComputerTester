// ComputerTester.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "ComputerTester.h"
#include "Tester.hpp"
#include "testers.hpp"
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
		data_struct->edit_wnd = CreateWindowEx(0, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, STATIC_WIDTH + INTERVAL, 0, cs->cx - 2 * INTERVAL - STATIC_WIDTH - BUTTON_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
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
					SendMessage(data_struct->local_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->avpresent_data = new TesterWindowData(hWnd, (HMENU)IDM_AVPRESENT, L"Проверить наличие антивируса", TESTER_HEIGHT, new CheckInstallAntivirus);
					SendMessage(data_struct->avpresent_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->avworking_data = new TesterWindowData(hWnd, (HMENU)IDM_AVWORKS, L"Проверить работоспособность антивируса", TESTER_HEIGHT, new Tester);
					SendMessage(data_struct->avworking_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->unknownexe_data = new TesterWindowData(hWnd, (HMENU)IDM_UNKNOWNEXE, L"Неизвестный EXE", TESTER_HEIGHT, new Tester);
					SendMessage(data_struct->unknownexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->swapexe_data = new TesterWindowData(hWnd, (HMENU)IDM_SWAPEXE, L"Подмена EXE", TESTER_HEIGHT, new Tester);
					SendMessage(data_struct->swapexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->returnexe_data = new TesterWindowData(hWnd, (HMENU)IDM_RETURNEXE, L"Вернуть EXE", TESTER_HEIGHT, new Tester);
					SendMessage(data_struct->returnexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->local_datas = { data_struct->avpresent_data , data_struct->avworking_data, data_struct->unknownexe_data, data_struct->swapexe_data, data_struct->returnexe_data };
					data_struct->y = EXTERNAL_MARGIN + INTERNAL_MARGIN;
					int old_y = data_struct->y;
					PositionElements(data_struct->local_datas, cs->cx, data_struct->y);
					data_struct->local_box = CreateWindowEx(0, L"button", L"Локальная безопасность", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, cs->cx - 2 * EXTERNAL_MARGIN, data_struct->y - old_y, hWnd, NULL, hInst, NULL);
					SendMessage(data_struct->local_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->y += EXTERNAL_MARGIN;
					old_y = data_struct->y;
					data_struct->connection_data = new TesterWindowData(hWnd, (HMENU)IDM_INETCONNECTED, L"Проверить подключение к Интернету", TESTER_HEIGHT, new InetConnectedTester);
					SendMessage(data_struct->connection_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->fwpresent_data = new TesterWindowData(hWnd, (HMENU)IDM_FWPRESENT, L"Проверить наличие МСЭ", TESTER_HEIGHT, new FireWallTester);
					SendMessage(data_struct->fwpresent_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->fwworking_data = new TesterWindowData(hWnd, (HMENU)IDM_FWWORKS, L"Проверить работоспособность МСЭ", TESTER_HEIGHT, new FireWallWorkTester);
					SendMessage(data_struct->fwworking_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->dleicar_data = new TesterWindowData(hWnd, (HMENU)IDM_DLEICAR, L"Скачать EICAR", TESTER_HEIGHT, new Tester);
					SendMessage(data_struct->dleicar_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->network_datas = { data_struct->connection_data, data_struct->fwpresent_data,data_struct->fwworking_data, data_struct->dleicar_data };
					PositionElements(data_struct->network_datas, cs->cx, data_struct->y);
					data_struct->network_box = CreateWindowEx(0, L"button", L"Сетевая безопасность", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, cs->cx - 2 * EXTERNAL_MARGIN, data_struct->y - old_y, hWnd, NULL, hInst, NULL);
					SendMessage(data_struct->network_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->y += EXTERNAL_MARGIN;
					old_y = data_struct->y;
					data_struct->disksfull_data = new TesterWindowData(hWnd, (HMENU)IDM_DISKSFULL, L"Проверить заполнение дисков", 3 * TESTER_HEIGHT, new DiskSpaceTester);
					SendMessage(data_struct->disksfull_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->performance_datas = { data_struct->disksfull_data };
					PositionElements(data_struct->performance_datas, cs->cx, data_struct->y);
					data_struct->performance_box = CreateWindowEx(0, L"button", L"Производительность", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, cs->cx - 2 * EXTERNAL_MARGIN, data_struct->y - old_y, hWnd, NULL, hInst, NULL);
					SendMessage(data_struct->performance_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->y += EXTERNAL_MARGIN;
					old_y = data_struct->y;
					data_struct->y -= 3 * INTERNAL_MARGIN;
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
		case IDM_AVPRESENT:
			data_struct->avpresent_data->PerformTest();
			break;
		case IDM_AVWORKS:
			data_struct->avworking_data->PerformTest();
			break;
		case IDM_UNKNOWNEXE:
			data_struct->unknownexe_data->PerformTest();
			break;
		case IDM_SWAPEXE:
			data_struct->swapexe_data->PerformTest();
			break;
		case IDM_RETURNEXE:
			data_struct->returnexe_data->PerformTest();
			break;
		case IDM_INETCONNECTED:
			data_struct->connection_data->PerformTest();
			break;
		case IDM_FWPRESENT:
			data_struct->fwpresent_data->PerformTest();
			break;
		case IDM_FWWORKS:
			data_struct->fwworking_data->PerformTest();
			break;
		case IDM_DLEICAR:
			data_struct->dleicar_data->PerformTest();
			break;
		case IDM_DISKSFULL:
			data_struct->disksfull_data->PerformTest();
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
								if (out_stream.good()) {
									std::vector<LPCWSTR> names = { L"Локальная безопасность", L"Сетевая безопасность", L"Производительность" };
									std::vector<std::vector<TesterWindowData*>> datas = { data_struct->local_datas, data_struct->network_datas, data_struct->performance_datas };
									int c = 0;
									for (int j = 0; j < 3; j++) {
										out_stream << names.at(j) << std::endl;
										for (int i = 0; i < datas.at(j).size(); i++) {
											c++;
											TesterWindowData* twd = datas.at(j).at(i);
											out_stream << c << L". " << twd->GetStaticText() << L" : " << twd->GetTesterResult() << std::endl;
										}
									};
								};
								out_stream.close();
							}
							catch (std::wofstream::failure fail) {
								const char* what = fail.what();
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
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{
		const int width = LOWORD(lParam);
		const int height = HIWORD(lParam);
		int y = EXTERNAL_MARGIN + INTERNAL_MARGIN;
		int old_y = y;
		PositionElements(data_struct->local_datas, width, y);
		SetWindowPos(data_struct->local_box, HWND_TOP, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, width - 2 * EXTERNAL_MARGIN, y - old_y, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		old_y = y;
		PositionElements(data_struct->network_datas, width, y);
		SetWindowPos(data_struct->network_box, HWND_TOP, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, width - 2 * EXTERNAL_MARGIN, y - old_y, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		old_y = y;
		PositionElements(data_struct->performance_datas, width, y);
		SetWindowPos(data_struct->performance_box, HWND_TOP, EXTERNAL_MARGIN, old_y - INTERNAL_MARGIN, width - 2 * EXTERNAL_MARGIN, y - old_y, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		old_y = y;
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
	if (thread == 0) thread = CreateThread(NULL, 0, &TesterThreadWrapper, this, 0, NULL);
	else MessageBoxExW(GetParent(window), L"Тест уже идёт", L"Невозможно запустить тест", MB_OK | MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
};

void TesterWindowData::FinishTest() {
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	thread = 0;
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
	DestroyWindow(local_box);
	DestroyWindow(network_box);
	DestroyWindow(performance_box);
	delete avpresent_data;
	delete avworking_data;
	delete unknownexe_data;
	delete swapexe_data;
	delete returnexe_data;
	delete connection_data;
	delete fwpresent_data;
	delete fwworking_data;
	delete dleicar_data;
	delete disksfull_data;
	DeleteObject(hFont);
};

Tester::Tester() : result{ L"неизвестно" } {};

void Tester::DoTest() {};

LPCWSTR Tester::GetResult() {
	return result;
}

InetConnectedTester::InetConnectedTester() : Tester() {};

void InetConnectedTester::DoTest() {
	DWORD flags;
	result = InternetGetConnectedState(&flags, 0) ? L"Интернет доступен" : L"Интернет недоступен";
}

FireWallTester::FireWallTester() : Tester() {};

void FireWallTester::DoTest() {
	std::filesystem::path filePath("C:\\Program Files\\COMODO\\COMODO Internet Security\\cis.exe");
	if (std::filesystem::exists(filePath)) {
		result = L"МЭ установлен";
	}
	else {
		result = L"МЭ не установлен";
	}
}

FireWallWorkTester::FireWallWorkTester() : Tester() {};
void FireWallWorkTester::DoTest() {
	HINTERNET hInternet = InternetOpen(L"FireWallWorkTester", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet) {
		result = L"Ошибка при открытии сессии интернета";
		return;
	}

	HINTERNET hUrl = InternetOpenUrl(hInternet, L"https://ya.ru", NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hUrl) {
		InternetCloseHandle(hInternet);
		result = L"МЭ функционирует правильно";
		return;
	}

	InternetCloseHandle(hUrl);
	InternetCloseHandle(hInternet);

	result = L"МЭ функционирует не правильно";
}
CheckInstallAntivirus::CheckInstallAntivirus() :Tester() {};
void CheckInstallAntivirus::DoTest() {
	result = L"Антивирус не установлен!";

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
									result = L"Антивирус установлен!";
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

				ss << L"Drive " << driveLetter << L": has " << std::setprecision(2) << std::fixed << freeGB << L" GB free out of " << totalGB << L" GB total.\n";
			}
			else {
				ss << L"Failed to get disk space for drive " << driveLetter << L":\n";
			}
		}
	}

	std::wstring resultStr = ss.str();
	result = resultStr.c_str();
}



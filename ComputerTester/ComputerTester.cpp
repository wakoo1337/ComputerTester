// ComputerTester.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "ComputerTester.h"
#include "Tester.hpp"
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
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
	wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
#define STATIC_WIDTH 100
#define BUTTON_WIDTH 50
#define INTERVAL 10
	switch (message) {
	case WM_CREATE:
		CREATESTRUCT* cs;
		cs = (CREATESTRUCT*)lParam;
		data_struct = (TesterWindowData*)cs->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)data_struct);
		data_struct->static_wnd = CreateWindowEx(0, L"static", data_struct->static_text, WS_CHILD | WS_VISIBLE, INTERVAL, 0, STATIC_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
		data_struct->edit_wnd = CreateWindowEx(0, L"edit", L"", WS_CHILD | WS_VISIBLE, STATIC_WIDTH + 2 * INTERVAL, 0, cs->cx - 4 * INTERVAL - STATIC_WIDTH - BUTTON_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
		data_struct->button_wnd = CreateWindowEx(0, L"button", L"", WS_CHILD | WS_VISIBLE, cs->cx - INTERVAL - BUTTON_WIDTH, 0, BUTTON_WIDTH, cs->cy, hWnd, nullptr, hInst, nullptr);
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
		SetWindowPos(data_struct->static_wnd, HWND_TOP, INTERVAL, 0, STATIC_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		SetWindowPos(data_struct->edit_wnd, HWND_TOP, STATIC_WIDTH + 2 * INTERVAL, 0, width - 4 * INTERVAL - STATIC_WIDTH - BUTTON_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		SetWindowPos(data_struct->button_wnd, HWND_TOP, width - INTERVAL - BUTTON_WIDTH, 0, BUTTON_WIDTH, height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
	};
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
#define EXTERNAL_MARGIN 20
#define INTERNAL_MARGIN 10
#define TESTER_HEIGHT 30
					
					SendMessage(data_struct->local_box, WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->avpresent_data = new TesterWindowData(hWnd, L"Проверка наличия антивируса", new Tester);
					SendMessage(data_struct->avpresent_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					//SetWindowPos(data_struct->avpresent_data->getWindow(), HWND_TOP, EXTERNAL_MARGIN + INTERNAL_MARGIN, EXTERNAL_MARGIN + INTERNAL_MARGIN, , , );
					data_struct->avworking_data = new TesterWindowData(hWnd, L"Проверка работоспособности антивируса", new Tester);
					SendMessage(data_struct->avworking_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->unknownexe_data = new TesterWindowData(hWnd, L"Неизвестный EXE", new Tester);
					SendMessage(data_struct->unknownexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->swapexe_data = new TesterWindowData(hWnd, L"Подмена EXE", new Tester);
					SendMessage(data_struct->swapexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					data_struct->returnexe_data = new TesterWindowData(hWnd, L"Вернуть EXE", new Tester);
					SendMessage(data_struct->returnexe_data->getWindow(), WM_SETFONT, (WPARAM)data_struct->hFont, TRUE);
					std::vector<TesterWindowData*> datas = { data_struct->avpresent_data , data_struct->avworking_data, data_struct->unknownexe_data, data_struct->swapexe_data, data_struct->returnexe_data };
					int i = 0;
					std::for_each(datas.cbegin(), datas.cend(), [&i,cs](TesterWindowData* twd) {
						SetWindowPos(twd->getWindow(), HWND_TOP, EXTERNAL_MARGIN + INTERNAL_MARGIN, EXTERNAL_MARGIN+INTERNAL_MARGIN*(i+1)+TESTER_HEIGHT*i, cs->cx - 2 * (EXTERNAL_MARGIN + INTERNAL_MARGIN), TESTER_HEIGHT, SWP_NOACTIVATE | SWP_SHOWWINDOW);
						i++;
						}
					);
					data_struct->local_box = CreateWindowEx(0, L"button", L"Локальная безопасность", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, EXTERNAL_MARGIN, EXTERNAL_MARGIN, cs->cx - 2 * EXTERNAL_MARGIN, datas.size() * TESTER_HEIGHT + (datas.size() + 1) * INTERNAL_MARGIN, hWnd, NULL, hInst, NULL);
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
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

TesterWindowData::TesterWindowData(HWND parent, LPCWSTR text, Tester* tester) {
	this->button_wnd = nullptr;
	this->static_wnd = nullptr;
	this->edit_wnd = nullptr;
	this->tester = tester;
	this->static_text = text;
	this->window = CreateWindowExW(0, szTesterClass, text, WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, parent, NULL, hInst, this);
};

HWND TesterWindowData::getWindow() {
	return window;
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
	delete avpresent_data;
	DeleteObject(hFont);
};
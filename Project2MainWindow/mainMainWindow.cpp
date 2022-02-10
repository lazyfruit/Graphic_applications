#include<Windows.h>
#include<cstdio>

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";
CONST CHAR g_szTitle[] = "My first MainWindow";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//1. РЕГИСТРАЦИЯ КЛАССА ОКНА:
	WNDCLASSEX wc;//wc - Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;//
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szCLASS_NAME;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc))//Проверяем регистрацию класса окна
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
	}
	
	//2. СОЗДАНИЕ ОКНА:
	//1) Узнаем размер экрана
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	//Высчитываем размер окна на четверть меньше
	int window_width = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	//Высчитываем 
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,//exStyle
		g_szCLASS_NAME,//Имя класса окна
		g_szCLASS_NAME,//Имя заголовка окна
		WS_OVERLAPPEDWINDOW,//Стиль окна OVERLAPPED всегда задается для главного окна программы
		window_start_x /*CW_USEDEFAULT*/, window_start_y /* CW_USEDEFAULT*/,//Позиция окна на экране
		window_width /*640*/ /*CW_USEDEFAULT*/, window_height/*480*/ /*CW_USEDEFAULT*/,//Размер окна
		NULL,//Родительское окно
		NULL,//Меню отсутствует
		hInstance,//*.exe-файл окна
		NULL//???
	);
	if (hwnd == NULL)//Проверка создания главного окна
	{
		MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;//Если окно не создалось нет смысла продолжать
	}
	ShowWindow(hwnd, nCmdShow);//Задаем режим отображения окна
	UpdateWindow(hwnd);//Прорисовка окна (отправляем сообщение WM_PAINT)
	
	//3. ЗАПУСКАЕМ ЦИКЛ СООБЩЕНИЙ:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE://Создаются элементы окна
		break;
	case WM_COMMAND://Обработка команд нажатия кнопок и других элементов
		break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		SendMessage(hwnd, WM_GETTEXT, SIZE, (LPARAM)buffer);
		sprintf
		(
			buffer, "%s Position: %dx%d, Size: %dx%d",//%s - строка, %d - decimal (десятичное число)
			g_szTitle,
			rect.left, rect.top,//Позиция окна
			rect.right - rect.left, rect.bottom - rect.top//Размер окна
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_CLOSE:
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Шо, внатуре?", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			MessageBox(hwnd, "Лучше бы двери закрыли...", "Ну ок, че...", MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd); break;
		case IDNO: MessageBox(hwnd, "Тогда продолжим!", "Красавчик!", MB_OK | MB_ICONINFORMATION); break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
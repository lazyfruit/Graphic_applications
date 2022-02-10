#include<Windows.h>
#include"resource.h"

//#define MESSAGE_BOX
BOOL CALLBACK DlgProc(HWND hwnd,//hwnd - handler to window (окно)
	UINT uMsg,//Сообщение
	WPARAM wParam, LPARAM lParam);//Параметры сообщения

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef MESSAGE_BOX //Протейшее окно
	MessageBox(//Старая функция имеющая много документации
			   //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
		NULL,//Ссыдка на главное окно
		"Вы создали ваше первое окно!",//Выводимое сообщение
		"Info",//Заголовок
		/*MB_OKCANCEL*/ /*MB_YESNO*/ MB_YESNOCANCEL |//Задаем доступные клавиши
		MB_HELP | //Клавиша помощи-справки (не закрывает окно)
		MB_ICONINFORMATION /*MB_ICONWARNING*/ /*MB_ICONERROR*/ |//Задаем тип окна информации
		MB_SYSTEMMODAL |//Устанавливаем окно жестко модальным для всей системы
		MB_DEFBUTTON4 |//Задаем клавишу по умолчанию
		MB_RIGHT);//Выравнимает текст в окне по правому краю
		//MB сокр. от MessageBox  
#endif // MESSAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

//Сайт иконок: https://icon-icons.com/ru/

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(NULL, L"Была нажата кнопка OK", L"Info", MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
	} break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
//SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
//{
//case IDC_BTN_COPY:
//{
//CONST INT SIZE = 256;
//CHAR buffer[SIZE]{};
//HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);//Получаем Handler текстового поля по номеру его ресурса
//SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
//SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_GETTEXT, 0, (LPARAM)buffer);
//}
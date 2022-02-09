#include<Windows.h>
#include"resource.h"

//#define MESSAGE_BOX
BOOL CALLBACK DlgProc(HWND hwnd,//hwnd - handler to window (����)
	UINT uMsg,//���������
	WPARAM wParam, LPARAM lParam);//��������� ���������

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef MESSAGE_BOX //��������� ����
	MessageBox(//������ ������� ������� ����� ������������
			   //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
		NULL,//������ �� ������� ����
		"�� ������� ���� ������ ����!",//��������� ���������
		"Info",//���������
		/*MB_OKCANCEL*/ /*MB_YESNO*/ MB_YESNOCANCEL |//������ ��������� �������
		MB_HELP | //������� ������-������� (�� ��������� ����)
		MB_ICONINFORMATION /*MB_ICONWARNING*/ /*MB_ICONERROR*/ |//������ ��� ���� ����������
		MB_SYSTEMMODAL |//������������� ���� ������ ��������� ��� ���� �������
		MB_DEFBUTTON4 |//������ ������� �� ���������
		MB_RIGHT);//����������� ����� � ���� �� ������� ����
		//MB ����. �� MessageBox  
#endif // MESSAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

//���� ������: https://icon-icons.com/ru/

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(NULL, "���� ������ ������ OK", "Info", MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
	} break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
//HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
//SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
//{
//case IDC_BTN_COPY:
//{
//CONST INT SIZE = 256;
//CHAR buffer[SIZE]{};
//HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);//�������� Handler ���������� ���� �� ������ ��� �������
//SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);
//SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_GETTEXT, 0, (LPARAM)buffer);
//}
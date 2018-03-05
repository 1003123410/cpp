#include <windows.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

//�Ӵ��ڻص�����
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd,LPARAM lParam)
{
	char title[100] = { 0 };
	GetWindowTextA(hwnd, title, 100);
	if (strlen(title)>0)
		cout <<hex<<"�����"<<hwnd<<"  ���⣺"<<title << endl;
	return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title[100] = { 0 };
	GetWindowTextA(hwnd, title, 100);
	if (strlen(title) > 0)
		cout << hex << "�����" << hwnd << "  ���⣺" << title << endl;
	EnumChildWindows(hwnd, EnumChildWindowsProc, NULL);
	return true;
}

BOOL myEnumWindow(HWND hwnd)
{
	char title[100] = { 0 };
	HWND after = NULL;
	while (after = ::FindWindowEx(hwnd, after, NULL, NULL))
	{
		GetWindowTextA(after, title, 100);
		if(strlen(title)>0)
			cout <<"�����"<<hex<< after<<"  ���⣺" << title <<endl;
		myEnumWindow(after);
	}
	return true;
}

int main()
{
	HWND handle = NULL;
	FindWindow(NULL, "���������");//�����ض����ڵĴ��ھ��
	RECT rect;
	int width, height;
	if (handle)
	{
		GetWindowRect(handle, &rect);//��ȡ������Ϣ
		width = rect.right - rect.left, height = rect.bottom - rect.top;
		cout << "��: " << width << endl << "��: " << height << endl;
		cout << MoveWindow(handle, 100, 100, width, height, true) << endl;
	}
	//��ȡ���ж���ɼ����ڼ����ǵ��Ӵ���
	EnumWindows(EnumWindowsProc, NULL);

	cout << endl << endl << "�ڶ��ַ�����" << endl;
	myEnumWindow(NULL);//ʹ��FindWindowExö�ٴ���

	getchar();
	getchar();
	return 0;
}
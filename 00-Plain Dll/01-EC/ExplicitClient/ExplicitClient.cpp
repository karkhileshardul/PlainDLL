#include<stdio.h>
#include<Windows.h>
#include"ExplicitServer.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/*
int findgcd(int num1, int num2)
{
	int gcd;

	num1 = ( num1 > 0) ? num1 : -num1;
    num2 = ( num2 > 0) ? num2 : -num2;
	for (int i = 1; i <= num1 && i <= num2; i++)
	{
		if (num1%i == 0 && num2%i == 0) {
			gcd = i;
		}
	}


	/*
  		while(num1!=num2)
    	{
	        if(num1 > num2)
            	num1 -= num2;
        	else
	            num2 -= num1;
    	}
	
	return (gcd);
}
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclassex;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = L"0-Explicit Client";

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.lpszClassName = szClassName;
	wndclassex.lpszMenuName = NULL;
	wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hInstance = hInstance;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclassex);

	hwnd = CreateWindow(szClassName, L"My Explicit Client",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, HWND_DESKTOP,
		NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow() Failed!!!!",L"ERROR",MB_OK);
		exit(EXIT_FAILURE);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HMODULE hModule = NULL;
	static int number = 0;
	TCHAR tchar_str[100];
	typedef double(*RefractiveIndex)(double,double,double,double);
	typedef int(*findGCD)(int, int);
	findGCD pfnfindGCD = NULL;
	RefractiveIndex pfn = NULL;
	double danswer;
	int imyans;
	switch (iMsg)
	{
		case WM_CREATE:
			hModule = LoadLibrary(TEXT("ExplicitServer.dll"));
			if (hModule == NULL)
			{
				MessageBox(hwnd, L"Error in LoadLibrary()", L"ERROR", MB_OK);
				exit(EXIT_FAILURE);
			}
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_SPACE:
//					pfn = (RefractiveIndex)GetProcAddress(hModule, "MakeSquare");
					//number = pfn(5);

					
					//wsprintf(tchar_str,L"The Square is 5 is %d", number);
					//MessageBox(hwnd, tchar_str, L"OUTPUT", MB_OK);
					MessageBox(hwnd, L"Nothing", L"OUTPUT", MB_OK);
					break;
				case VK_UP:
					
					pfn = (RefractiveIndex)GetProcAddress(hModule, "RefractiveIndex");
					danswer = pfn(0.0, 1.333, 35.0, 25.0);
					swprintf(tchar_str, 100, L"The danswer is %f",danswer);
					MessageBox(hwnd, tchar_str, L"OUTPUT", MB_OK);
					break;
				case VK_DOWN:
					pfnfindGCD = (findGCD)GetProcAddress(hModule, "findgcd");
					imyans = pfnfindGCD(76,52);
					wsprintf(tchar_str,L"The GCD  %d", imyans);
					MessageBox(hwnd, tchar_str, L"OUTPUT", MB_OK);
					break;
			}
			break;
		case WM_DESTROY:
			FreeLibrary(hModule);
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
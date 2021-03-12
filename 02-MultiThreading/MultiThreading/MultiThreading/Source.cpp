#include<Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclassex;
	MSG msg;
	HWND hwnd;
	TCHAR szClassName[] = TEXT("05-MultiThreading");

	wndclassex.cbSize = sizeof(wndclassex);
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclassex.hInstance = hInstance;
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpszMenuName = NULL;
	wndclassex.lpszClassName = szClassName;
	wndclassex.lpfnWndProc = WndProc;

	if (!(RegisterClassEx(&wndclassex))) {
		MessageBox(NULL, L"RegisterClassfailed", L"ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}
	hwnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, L"hwnd Failed!!!\n", L"ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HANDLE hThread1, hThread2;
	DWORD dwID1, dwID2;
	switch (iMsg) {
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) MyThreadProcOne,(LPVOID) hwnd, 0, &dwID1);
		hThread2 = CreateThread(NULL, 0, MyThreadProcTwo, hwnd, 0, &dwID2);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param) 
{
	HDC hdc;
	int i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	for (i = 0; i <= 32767; i++) {
		wsprintf(str, TEXT("Thread1->Increasing order output=%d"), i);
		TextOut(hdc, 5, 5, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return(0);
}

DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	HDC hdc;
	int i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	for(i = 32676; i >= 0; i--) {
		wsprintf(str, TEXT("Thread2->Decreasing order output=%d"), i);
		TextOut(hdc, 5, 25, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return (0);
}

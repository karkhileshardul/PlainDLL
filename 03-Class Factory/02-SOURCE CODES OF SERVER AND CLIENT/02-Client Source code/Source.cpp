#include<Windows.h>
#include"Header.h"

//Declaring callback function
LRESULT CALLBACK MyCallBack(HWND, UINT, WPARAM, LPARAM);

//pointer types of isum and isubtract to catch aaddresses of object

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndcls;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	TCHAR AppName[] = TEXT("ComClient");

	// to start com engine for you i.e by this ole32.dll and oleaut32.dll of com will be available for you
	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Com Library Cannot Be Loaded!!.."), TEXT("ERROR"), MB_OKCANCEL);
		exit(0);
	}

	//WNDCLASSEX Initialization
	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.lpszClassName = AppName;
	wndcls.lpszMenuName = NULL;
	wndcls.lpfnWndProc = MyCallBack;
	wndcls.hbrBackground = CreateSolidBrush(RGB(128, 129, 128));
	wndcls.hInstance = hInstance;
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndcls);

	hwnd = CreateWindow(AppName,
		TEXT("Client Of Com Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//To Shut Com's Engine which was started for you.
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK MyCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	void SafeInterfaceRelease(void);

	HRESULT hr;
	int iNum1, iNum2, outNum;
	TCHAR str[255];

	switch (iMsg) {

	case WM_CREATE:

		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Cannot Create Instance of ISum!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		//initialize argumeents hardcoded
		iNum1 = 55;
		iNum2 = 45;
		pISum->SumOfTwoInt(iNum1, iNum2, &outNum);

		wsprintf(str, TEXT("Addition of %d + %d = %d"), iNum1, iNum2, outNum);

		MessageBox(hwnd, str, TEXT("Output"), MB_OK);
		//call to CSumSubtract's QI to get Object of subtract type only
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Cannot Create Instance of ISubtrct!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 155;
		iNum2 = 100;

		pISubtract->SubtractionOfTwoInt(iNum1, iNum2, &outNum);
		wsprintf(str, TEXT("Subtraction of %d - %d = %d"), iNum1, iNum2, outNum);

		MessageBox(hwnd, str, TEXT("Output"), MB_OK);

		//now both instances aare no longer needed but as the convention we must release that which we got recent using so

		pISubtract->Release();
		pISubtract = NULL;	//make released interface null
		pISum->Release();
		pISum = NULL;	//make released interface null

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void) {

	if (pISum) {
		pISubtract->Release();
		pISubtract = NULL;
	}
	if (pISubtract) {
		pISum->Release();
		pISum = NULL;
	}
}



#include<Windows.h>
#include<math.h>
#include"ExplicitServer.h"
#include"CFDServer.h"

#define PI			3.142
#define AIR			1.000
#define CARBONDIOXIDE	1.001
#define WATER			1.330
#define DIAMOND			2.417

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;


int WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}
	return (TRUE);
}
/*
extern "C" int MakeSquare(int num)
{
	int result=0;
	result = num*num;
	return(result);
}

extern "C" double RefractiveIndex(double n1,double n2,double angle1,double angle2)
{
	double result = 0.0;
	double t_angle1 = 0.0, t_angle2 = 0.0;

	if (n1 == 0.0)
	{
		angle1 = angle1 *(PI / 180.0);
		angle2 = angle2 *(PI / 180.0);
		t_angle1 = sin(angle1);
		t_angle2 = sin(angle2);
		result = (n2* t_angle2) / t_angle1;
	}
	else if (n2 == 0.0)
	{
		angle1 = angle1 *(PI / 180.0);
		angle2 = angle2 *(PI/ 180.0);
		t_angle1 = sin(angle1);
		t_angle2 = sin(angle2);
		result = (n1*t_angle1) / t_angle2;
	}
	else
	{
		MessageBox(NULL, L"Unexpected Error", L"ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}
	return (result);
}
*/
/*extern "C" int findgcd(int num1, int num2)
{
	int gcd;

	for (int i = 1; i <= num1 && i <= num2; i++)
	{
		if (num1%i == 0 && num2%i == 0) 
		{
			gcd = i;
		}
	}

	return (gcd);
}
*/

extern "C" int getGCD(int num1, int num2)
{
	void SafeInterfaceRelease(void);
	HRESULT hr;
	int result;
	TCHAR str[255];
	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Com Library Cannot Be Loaded!!.."), TEXT("ERROR"), MB_OKCANCEL);
		exit(0);
	}

	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Cannot Create Instance of ISum!"), TEXT("ERROR"), MB_OK);
		DestroyWindow(NULL);
	}

	//initialize argumeents hardcoded
	pISum->SumOfTwoInt(num1, num2, &result);

	return result;
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




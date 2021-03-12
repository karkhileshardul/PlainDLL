#include<Windows.h>
#include"Header.h"

//co-class declaration {Avdhut Of the Example}

class CSumSubtract : public ISum, ISubtract {
private:
	long m_cRef;

public:
	//Constructor and destructor of class
	CSumSubtract(void);
	~CSumSubtract(void);

	//Methods of IUnknown

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//Methods of ISum
	HRESULT __stdcall SumOfTwoInt(int, int, int*);

	//Methods of ISubtract
	HRESULT __stdcall SubtractionOfTwoInt(int, int, int*);

};

class CSumSubtractClassFactory : public IClassFactory {
private:
	long m_cRef;
public:
	//Constructor and destructor of class
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	//Methods of IUnknown
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//Methods of IClassFactory
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declaration
long glNumberOfActiveComponents = 0;	//counnt of active componenets
long glNumberOfServerLocks = 0;		//number of dll locks;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {

	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return (TRUE);
}

// Implementation to CSumSubtract's Methods 

// Constructor abd destructor 

CSumSubtract::CSumSubtract(void) {

	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);

}

CSumSubtract::~CSumSubtract(void) {

	InterlockedDecrement(&glNumberOfActiveComponents);

}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv) {

	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void) {

	InterlockedIncrement(&m_cRef); //sort of m_cRef++
	return(m_cRef);
}

ULONG CSumSubtract::Release(void) {

	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//implementation to iSum's method SumOfTwoIntegers
HRESULT CSumSubtract::SumOfTwoInt(int num1, int num2, int *pSum) {
	*pSum = num1 + num2;
	return(S_OK);
}

//implementation to ISubtract's method SumOfTwoIntegers
HRESULT CSumSubtract::SubtractionOfTwoInt(int num1, int num2, int *pSub) {
	*pSub = num1 - num2;
	return(S_OK);
}


//Implementation to all 5 methods of CSumSubtractClassFactory

CSumSubtractClassFactory::CSumSubtractClassFactory() {
	m_cRef = 1;

}

CSumSubtractClassFactory::~CSumSubtractClassFactory() {

}


HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv) {

	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CSumSubtractClassFactory::AddRef(void) {

	InterlockedIncrement(&m_cRef); //sortbof m_cRef++
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void) {

	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *rUnkouter, REFIID riid, void **ppv) {
	//variable to store address of obj.
	CSumSubtract *pSumSubtract = NULL;
	HRESULT hr;

	if (rUnkouter != NULL)
		return(CLASS_E_NOAGGREGATION);
	//create instance of class CSumSubtract
	pSumSubtract = new CSumSubtract;

	if (pSumSubtract == NULL) {
		return(E_OUTOFMEMORY);
	}
	hr = pSumSubtract->QueryInterface(riid, ppv);
	pSumSubtract->Release();
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL flock) {

	if (flock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

//Naked FunctionOf Dll which is gonna be be Exported

extern "C" HRESULT __stdcall  DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {

	HRESULT hr;
	CSumSubtractClassFactory *pSumSubtractClassFactory = NULL;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create instance of class factory
	pSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pSumSubtractClassFactory == NULL) {
		return(E_OUTOFMEMORY);
	}

	hr = pSumSubtractClassFactory->QueryInterface(riid, ppv);
	pSumSubtractClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}



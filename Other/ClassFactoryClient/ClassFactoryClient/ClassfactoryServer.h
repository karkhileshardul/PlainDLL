#pragma once

class ISum : public IUnknown {

public:
	// ISum specific methods declarations
	virtual HRESULT __stdcall SumOfTwoInt(int, int, int *) = 0;	//Pure virtuual function
};

class ISubtract : public IUnknown {

public:
	// ISubtract specific methods declarations
	virtual HRESULT __stdcall SubtractionOfTwoInt(int, int, int *) = 0;		//pure virtual function
};

// {1947A228-CCEF-441F-BA08-3DB490EC4189}	
const IID IID_ISum = { 0x1947a228, 0xccef, 0x441f, 0xba, 0x8, 0x3d, 0xb4, 0x90, 0xec, 0x41, 0x89 };

// {56240535-E029-4FEE-9399-F4D25D66EA59}
const IID IID_ISubtract = { 0x56240535, 0xe029, 0x4fee, 0x93, 0x99, 0xf4, 0xd2, 0x5d, 0x66, 0xea, 0x59 };

// {5F09C8A2-5ABF-4AED-8905-31CCA526E0CC}
const CLSID CLSID_SumSubtract = { 0x5f09c8a2, 0x5abf, 0x4aed, 0x89, 0x5, 0x31, 0xcc, 0xa5, 0x26, 0xe0, 0xcc };







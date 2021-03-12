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

//Stringised Representation of GUID for ISum "{527DD9B4-F7EC-4440-9DD3-5467E1C26B86}"

const IID IID_ISum = { 0x527dd9b4, 0xf7ec, 0x4440, 0x9d, 0xd3, 0x54, 0x67, 0xe1, 0xc2, 0x6b, 0x86 };

//Stringised representaation of GUID for ISubtract "{AF2C0413-4EC5-425C-A7CE-7B785F8FAC2D}"

const IID IID_ISubtract = {	0xaf2c0413, 0x4ec5, 0x425c, 0xa7, 0xce, 0x7b, 0x78, 0x5f, 0x8f, 0xac, 0x2d };


// Stringised Representation of GIUD for cSumSubtract "{10BB2565-104A-4725-80D1-DFA31C521F89}"

const CLSID CLSID_SumSubtract = { 0x10bb2565, 0x104a, 0x4725, 0x80, 0xd1, 0xdf, 0xa3, 0x1c, 0x52, 0x1f, 0x89 };





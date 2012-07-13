#pragma once

#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif

//#include <windows.h>
#include <QString>
// #include <atlbase.h>
#include <tchar.h>
#include <stdio.h>
#include <oaidl.h>
#include <ocidl.h>
#include <objbase.h>

// WDispatchInfo: private helper class to store type info of a method or a property
class WDispatchInfo
{
	friend class WDispatchDriver;
	WDispatchInfo();
	~WDispatchInfo();
	// dispatch id
	DISPID m_dispID;
	// method or property name
	BSTR m_bstrName;
	// invoke flag
	WORD m_wFlag;
	// offset of virtual function
	short m_oVft;
	// calling convention
	CALLCONV m_callconv;
	// output type
	VARTYPE m_vtOutputType;
	// output data
	VARIANT* m_pOutput;
	// number of parameters
	int m_nParamCount;
	// parameter type array
	WORD* m_pParamTypes;
	// assignment operator
	WDispatchInfo& operator=(const WDispatchInfo& src);
};

// WDispatchDriver: the main class
class WDispatchDriver
{
	// pointer to the IDispatch interface
	IDispatch* m_pDisp;
	// pointer to the IConnectionPoint interface
	IConnectionPoint* m_pCP;
	// used by IConnectionPoint::Advise/Unadvise
	DWORD m_dwCookie;
	// number of methods and properties
	int m_nDispInfoCount;
	// array of type info
	WDispatchInfo* m_pDispInfo;
	// error return code
	HRESULT m_hRet;
	// exception info
	EXCEPINFO m_exceptInfo;
	// private helper functions/members
	int m_nVarCount;
	int m_nMethodCount;
	int FindDispInfo(const QString& strName, const WORD wFlag = DISPATCH_METHOD);
	HRESULT InvokeMethodV(const int nIndex, va_list argList);
	static HRESULT InvokeVariantMethodV(IDispatch* pDisp,
										const DISPID dispidMethod,
										WORD wInvokeFlag,
										VARIANT* pVarRet,
										EXCEPINFO* pExcepInfo,
										const int nParamCount,
										va_list argList);
	bool LoadTypeInfo();
public:
	WDispatchDriver();
	~WDispatchDriver();
	// clean up
	void Clear();
	// copy contructor
	WDispatchDriver(const WDispatchDriver& src);
	// assignment operator
	WDispatchDriver& operator=(const WDispatchDriver& src);
	// create a com object with given prog id
	bool CreateObject(const QString& strProgID, DWORD dwClsContext = CLSCTX_ALL, const QString& strServerName = QString());
	// create a com object with given class id
	bool CreateObject(CLSID clsid,  DWORD dwClsContext = CLSCTX_ALL, const QString& strServerName = QString());
	// attach a IDispatch pointer to the obejct
	bool Attach(IDispatch* pDisp);
	// return the IDispatch pointer
	IDispatch* GetDispatch() { return m_pDisp; }
	// return the pointer to ith WDispatchInfo 
	WDispatchInfo* GetDispInfo(const int i) { return (i>=0&&i<m_nDispInfoCount)?(m_pDispInfo+i):NULL; }
	// return the index of a property in the internal storage
	int FindProperty(LPCTSTR strPropertyName);
	// return the index of a method in the internal storage
	int FindMethod(LPCTSTR strMethodName);
	// get the type of a property by name
	WORD GetPropertyType(LPCTSTR strPropertyName);
	// get the type of a property by index
	WORD GetPropertyType(int nPropertyIndex);
	// get a property value by name
	VARIANT* GetProperty(LPCTSTR strPropertyName);
	// get a property value by index
	VARIANT* GetProperty(int nPropertyIndex);
	// set a property value by name
	bool SetProperty(LPCTSTR strPropertyName, ...);
	// set a property value by index
	bool SetProperty(int nPropertyIndex, ...);
	// set a property value (ref) by name
	bool SetPropertyRef(LPCTSTR strPropertyName, ...);
	// set a property value (ref) by index
	bool SetPropertyRef(int nPropertyIndex, ...);
	// get return type of a method by name
	WORD GetReturnType(LPCTSTR strMethodName);
	// get return type of a method by index
	WORD GetReturnType(int nMethodIndex);
	// get number of parameters in a method by name
	int GetParamCount(LPCTSTR strMethodName);
	// get number of parameters in a method by index
	int GetParamCount(int nMethodIndex);
	// get the type of a parameter in a method by name
	WORD GetParamType(LPCTSTR strMethodName, const int nParamIndex);
	// get the type of a parameter in a method by index
	WORD GetParamType(int nMethodIndex, const int nParamIndex);
	// invoke a method by name
	VARIANT* InvokeMethod(LPCTSTR strMethodName, ...);
	// invoke a method by index
	VARIANT* InvokeMethod(int nMethodIndex, ...);
	// invoke a method without type info
	static HRESULT InvokeVariantMethod(IDispatch* pDisp, LPCTSTR strMethodName, WORD wInvokeFlag, VARIANT* pVarRet, EXCEPINFO* pExcepInfo, const int nParamCount, ...);
	static HRESULT InvokeVariantMethod(IDispatch* pDisp, const DISPID dispidMethod, WORD wInvokeFlag, VARIANT* pVarRet, EXCEPINFO* pExcepInfo, const int nParamCount, ...);
	// add event handler
	bool Advise(IUnknown *pUnkSink, REFIID riid);
    // remove event handler
    void Unadvise();
	// get the last error code as HRESULT
	HRESULT GetLastError() { return m_hRet; }
	// get exception info
	const EXCEPINFO* GetExceptionInfo() const { return &m_exceptInfo; }
};

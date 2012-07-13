#include "WDispatchDriver.h"
#include <qaxtypes.h>

WDispatchInfo::WDispatchInfo()
{
	m_dispID = 0;
	m_bstrName = NULL;
	m_wFlag = 0;
	m_oVft = -1;
	m_callconv = CC_STDCALL;
	m_vtOutputType = VT_EMPTY;
	m_pOutput = NULL;
	m_nParamCount = 0;
	m_pParamTypes = NULL;
}

WDispatchInfo::~WDispatchInfo()
{
	if(m_bstrName!=NULL)
	{
		::SysFreeString(m_bstrName);
	}
	if(m_pOutput!=NULL)
	{
		::VariantClear(m_pOutput);
	}
	delete m_pOutput;
	delete []m_pParamTypes;
}

WDispatchInfo& WDispatchInfo::operator=(const WDispatchInfo& src)
{
	m_dispID = src.m_dispID;
	if(m_bstrName) ::SysFreeString(m_bstrName);
	if(src.m_bstrName) m_bstrName = ::SysAllocString(src.m_bstrName);
	else m_bstrName = NULL;
	m_wFlag = src.m_wFlag;
	m_oVft = src.m_oVft;
	m_callconv = src.m_callconv;
	m_vtOutputType = src.m_vtOutputType;
	if(m_pOutput) delete m_pOutput;
	m_pOutput = new VARIANT;
	::VariantInit(m_pOutput);
	m_nParamCount = src.m_nParamCount;
	if(m_pParamTypes) delete []m_pParamTypes;
	if(m_nParamCount>0)
	{
		m_pParamTypes = new WORD[m_nParamCount+1];
		memcpy(m_pParamTypes,src.m_pParamTypes,(m_nParamCount+1)*sizeof(WORD));
	}
	else m_pParamTypes = NULL;
	return *this;
}

WDispatchDriver::WDispatchDriver()
{
	m_pCP = NULL;
	m_dwCookie = 0;
	m_pDisp = NULL;
	m_nVarCount = 0;
	m_nMethodCount = 0;
	m_nDispInfoCount = 0;
	m_pDispInfo = NULL;
	m_hRet = S_OK;
	::memset(&m_exceptInfo, 0, sizeof (EXCEPINFO));
}

WDispatchDriver::~WDispatchDriver()
{
	Clear();
}

WDispatchDriver::WDispatchDriver(const WDispatchDriver& src)
{
	m_pCP = NULL;
	m_dwCookie = 0;
	m_pDisp = NULL;
	m_nVarCount = 0;
	m_nMethodCount = 0;
	m_nDispInfoCount = 0;
	m_pDispInfo = NULL;
	m_hRet = S_OK;
	*this = src;
}

WDispatchDriver& WDispatchDriver::operator=(const WDispatchDriver& src)
{
	Clear();
	m_pDisp = src.m_pDisp;
	if(m_pDisp)
	{
		m_pDisp->AddRef();
		if(src.m_nDispInfoCount>0)
		{
			m_nDispInfoCount = src.m_nDispInfoCount;
			m_pDispInfo = new WDispatchInfo[m_nDispInfoCount];
			for(int i=0;i<m_nDispInfoCount;i++) m_pDispInfo[i] = src.m_pDispInfo[i];
		}
	}
	return *this;
}

void WDispatchDriver::Clear()
{
	m_hRet = S_OK;
	Unadvise();
	{
		::SysFreeString(m_exceptInfo.bstrSource);
		::SysFreeString(m_exceptInfo.bstrDescription);
		::SysFreeString(m_exceptInfo.bstrHelpFile);
		::memset(&m_exceptInfo, 0, sizeof(EXCEPINFO));
	}
	if(m_pDisp!=NULL)
	{
		m_pDisp->Release();
		m_pDisp = NULL;
	}
	if(m_pDispInfo)
	{
		delete []m_pDispInfo;
		m_pDispInfo = NULL;
	}
	m_nVarCount = 0;
	m_nMethodCount = 0;
	m_nDispInfoCount = 0;
}

bool WDispatchDriver::CreateObject(const QString& strProgID, DWORD dwClsContext, const QString& strServerName)
{
	Clear();
	CLSID clsid;
	m_hRet = ::CLSIDFromProgID((LPCOLESTR)strProgID.utf16(), &clsid);
	if(m_hRet==S_OK) return CreateObject(clsid, dwClsContext, strServerName);
	else
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("CLSIDFromProgID failed: %x\n",m_hRet);
		#endif
		return false;
	}
}

bool WDispatchDriver::CreateObject(CLSID clsid, DWORD dwClsContext, const QString& strServerName)
{
	Clear();
	// COSERVERINFO svrinfo = {0, T2W((TCHAR*)strServerName), NULL, 0};
	LPWSTR s = strServerName.isNull() ? 0 : (LPWSTR)strServerName.utf16();
	COSERVERINFO svrinfo = {0, s, NULL, 0};
	MULTI_QI multiqi = {&IID_IDispatch, m_pDisp, S_OK};
	m_hRet = ::CoCreateInstanceEx(clsid,NULL,dwClsContext,strServerName==NULL?NULL:(&svrinfo),1,&multiqi);
	if(m_hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("CoCreateInstance failed: %x\n",m_hRet);
		#endif
		return false;
	}
	m_pDisp = (IDispatch*)(multiqi.pItf);
	return LoadTypeInfo();
}

bool WDispatchDriver::LoadTypeInfo()
{
	/*UINT nTypeInfoCount;
	m_hRet = m_pDisp->GetTypeInfoCount(&nTypeInfoCount);
	if(m_hRet!=S_OK||nTypeInfoCount==0)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("GetTypeInfoCount failed or no type info: %x\n",m_hRet);
		#endif
	}*/

	ITypeInfo* pTypeInfo;
	m_hRet = m_pDisp->GetTypeInfo(0,LOCALE_SYSTEM_DEFAULT,&pTypeInfo);
	if(m_hRet!=S_OK||pTypeInfo==NULL)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("GetTypeInfo failed: %x\n",m_hRet);
		#endif
		return false;
	}

	TYPEATTR* pTypeAttr;
	m_hRet = pTypeInfo->GetTypeAttr(&pTypeAttr);
	if(m_hRet!=S_OK)
	{
		pTypeInfo->Release();
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("GetTypeAttr failed: %x\n",m_hRet);
		#endif
		return false;
	}

	if(pTypeAttr->typekind!=TKIND_DISPATCH&&pTypeAttr->typekind!=TKIND_COCLASS)
	{
		pTypeInfo->ReleaseTypeAttr(pTypeAttr);
		pTypeInfo->Release();
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Cannot get type info\n");
		#endif
		m_hRet = S_FALSE;
		return false;
	}

	if(pTypeAttr->typekind==TKIND_COCLASS)
	{
		int nFlags;
		HREFTYPE hRefType;
		ITypeInfo* pTempInfo;
		TYPEATTR* pTempAttr = NULL;
		for (int i=0;i<pTypeAttr->cImplTypes;i++)
		{
			if(pTypeInfo->GetImplTypeFlags(i,&nFlags)==S_OK&&(nFlags&IMPLTYPEFLAG_FDEFAULT))
			{
				m_hRet = pTypeInfo->GetRefTypeOfImplType(i,&hRefType);
				if(m_hRet==S_OK) m_hRet = pTypeInfo->GetRefTypeInfo(hRefType,&pTempInfo);
				if(m_hRet==S_OK)
				{
					m_hRet = pTempInfo->GetTypeAttr(&pTempAttr);
					if(m_hRet!=S_OK)
					{
						pTempInfo->Release();
						pTempInfo = NULL;
						break;
					}
				}
				else break;
			}
		}
		pTypeInfo->ReleaseTypeAttr(pTypeAttr);
		pTypeInfo->Release();
		if(pTempAttr==NULL)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("Failed to get reference type info: %x\n",m_hRet);
			#endif
			if(m_hRet==S_OK) m_hRet = S_FALSE;
			return false;
		}
		else
		{
			pTypeInfo = pTempInfo;
			pTypeAttr = pTempAttr;
		}
	}

	m_nMethodCount = pTypeAttr->cFuncs;
	m_nVarCount = pTypeAttr->cVars;
	m_nDispInfoCount = m_nMethodCount+2*m_nVarCount;
	#ifdef XYDISPDRIVER_DEBUG
	qWarning("Method and variable count = %d\n", m_nMethodCount+m_nVarCount);
	#endif
	m_pDispInfo = new WDispatchInfo[m_nDispInfoCount];

	for(int i=0;i<m_nMethodCount;i++)
	{
		FUNCDESC* pFuncDesc;
		m_hRet = pTypeInfo->GetFuncDesc(i, &pFuncDesc);
		if(m_hRet!=S_OK)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("GetFuncDesc failed: %x\n",m_hRet);
			#endif
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
			pTypeInfo->Release();
			m_nMethodCount = m_nVarCount = m_nDispInfoCount = 0;
			return false;
		}
		m_pDispInfo[i].m_dispID = pFuncDesc->memid;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("%d: DispID = %d\n",i, m_pDispInfo[i].m_dispID);
		#endif

		unsigned int nCount;
		m_hRet = pTypeInfo->GetNames(m_pDispInfo[i].m_dispID ,&m_pDispInfo[i].m_bstrName,1,&nCount);
		if(m_hRet!=S_OK)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("GetNames failed: %x\n",m_hRet);
			#endif
			pTypeInfo->ReleaseFuncDesc(pFuncDesc);
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
			pTypeInfo->Release();
			m_nMethodCount = m_nVarCount = m_nDispInfoCount = 0;
			return false;
		}
		#ifdef XYDISPDRIVER_DEBUG
		qWarning(L"MethodName = %s\n", m_pDispInfo[i].m_bstrName);
		#endif

		switch(pFuncDesc->invkind)
		{
		case INVOKE_PROPERTYGET:
			m_pDispInfo[i].m_wFlag = DISPATCH_PROPERTYGET;
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("PropertyGet\n");
			#endif
			break;
		case INVOKE_PROPERTYPUT:
			m_pDispInfo[i].m_wFlag = DISPATCH_PROPERTYPUT;
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("PropertyPut\n");
			#endif
			break;
		case INVOKE_PROPERTYPUTREF:
			m_pDispInfo[i].m_wFlag = DISPATCH_PROPERTYPUTREF;
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("PropertyPutRef\n");
			#endif
			break;
		case INVOKE_FUNC:
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("DispatchMethod\n");
			#endif
			m_pDispInfo[i].m_wFlag = DISPATCH_METHOD;
			break;
		default:
			break;
		}

		m_pDispInfo[i].m_oVft = pFuncDesc->oVft;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("VTable offset: %d\n",m_pDispInfo[i].m_oVft);
		#endif

		m_pDispInfo[i].m_callconv = pFuncDesc->callconv;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Calling convention: %d\n",m_pDispInfo[i].m_callconv);
		#endif

		m_pDispInfo[i].m_pOutput = new VARIANT;
		::VariantInit(m_pDispInfo[i].m_pOutput);
		m_pDispInfo[i].m_vtOutputType = pFuncDesc->elemdescFunc.tdesc.vt;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Return type = %d\n", m_pDispInfo[i].m_vtOutputType);
		#endif
		if(m_pDispInfo[i].m_vtOutputType==VT_VOID||m_pDispInfo[i].m_vtOutputType==VT_NULL)
		{
			m_pDispInfo[i].m_vtOutputType = VT_EMPTY;
		}

		m_pDispInfo[i].m_nParamCount = pFuncDesc->cParams;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("ParamCount = %d\n", m_pDispInfo[i].m_nParamCount);
		#endif

		m_pDispInfo[i].m_pParamTypes = new WORD[m_pDispInfo[i].m_nParamCount+1];
		for(int j=0;j<m_pDispInfo[i].m_nParamCount;j++)
		{
			if(pFuncDesc->lprgelemdescParam[j].tdesc.vt==VT_SAFEARRAY)
			{
				m_pDispInfo[i].m_pParamTypes[j] = (pFuncDesc->lprgelemdescParam[j].tdesc.lptdesc->vt)|VT_ARRAY;
			}
			else if(pFuncDesc->lprgelemdescParam[j].tdesc.vt==VT_PTR)
			{
				m_pDispInfo[i].m_pParamTypes[j] = (pFuncDesc->lprgelemdescParam[j].tdesc.lptdesc->vt)|VT_BYREF;
			}
			else
			{
				m_pDispInfo[i].m_pParamTypes[j] = pFuncDesc->lprgelemdescParam[j].tdesc.vt;
			}

			#ifdef XYDISPDRIVER_DEBUG
			qWarning("Param(%d) type = %d\n",j,m_pDispInfo[i].m_pParamTypes[j]);
			#endif
		}
		m_pDispInfo[i].m_pParamTypes[m_pDispInfo[i].m_nParamCount] = 0;
		pTypeInfo->ReleaseFuncDesc(pFuncDesc);
	}

	for(int i=m_nMethodCount;i<m_nMethodCount+m_nVarCount;i++)
	{
		VARDESC* pVarDesc;
		m_hRet = pTypeInfo->GetVarDesc(i-m_nMethodCount, &pVarDesc);
		if(m_hRet!=S_OK)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("GetVarDesc failed: %x\n",m_hRet);
			#endif
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
			pTypeInfo->Release();
			m_nMethodCount = m_nVarCount = m_nDispInfoCount = 0;
			return false;
		}
		m_pDispInfo[i].m_dispID = pVarDesc->memid;
		m_pDispInfo[i+m_nVarCount].m_dispID = m_pDispInfo[i].m_dispID;
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("%d: DispID = %d\n",i, m_pDispInfo[i].m_dispID);
		#endif

		unsigned int nCount;
		m_hRet = pTypeInfo->GetNames(m_pDispInfo[i].m_dispID ,&m_pDispInfo[i].m_bstrName,1,&nCount);
		if(m_hRet!=S_OK)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("GetNames failed: %x\n",m_hRet);
			#endif
			pTypeInfo->ReleaseVarDesc(pVarDesc);
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
			pTypeInfo->Release();
			m_nMethodCount = m_nVarCount = m_nDispInfoCount = 0;
			return false;
		}
		m_pDispInfo[i+m_nVarCount].m_bstrName = ::SysAllocString(m_pDispInfo[i].m_bstrName);
		#ifdef XYDISPDRIVER_DEBUG
		qWarning(L"VarName = %s\n", m_pDispInfo[i].m_bstrName);
		#endif

		switch(pVarDesc->varkind)
		{
		case VAR_DISPATCH:
			m_pDispInfo[i].m_wFlag = DISPATCH_PROPERTYGET;
			m_pDispInfo[i+m_nVarCount].m_wFlag = DISPATCH_PROPERTYPUT;
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("VarKind = VAR_DISPATCH\n");
			#endif
			m_pDispInfo[i].m_vtOutputType = pVarDesc->elemdescVar.tdesc.vt;
			m_pDispInfo[i+m_nVarCount].m_vtOutputType = VT_EMPTY;
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("VarType = %d\n", m_pDispInfo[i].m_vtOutputType);
			#endif
			m_pDispInfo[i+m_nVarCount].m_nParamCount = 1;
			m_pDispInfo[i+m_nVarCount].m_pParamTypes = new WORD[2];
			m_pDispInfo[i+m_nVarCount].m_pParamTypes[0] = m_pDispInfo[i].m_vtOutputType;
			m_pDispInfo[i+m_nVarCount].m_pParamTypes[1] = 0;
			break;
		default:
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("VarKind = %d\n",pVarDesc->varkind);
			#endif
			m_pDispInfo[i].m_wFlag = 0;
			m_pDispInfo[i+m_nVarCount].m_wFlag = 0;
			break;
		}
		m_pDispInfo[i].m_pOutput = new VARIANT;
		::VariantInit(m_pDispInfo[i].m_pOutput);
		m_pDispInfo[i+m_nVarCount].m_pOutput = new VARIANT;
		::VariantInit(m_pDispInfo[i+m_nVarCount].m_pOutput);
		pTypeInfo->ReleaseVarDesc(pVarDesc);
	}

	pTypeInfo->ReleaseTypeAttr(pTypeAttr);
	pTypeInfo->Release();
	return true;
}

bool WDispatchDriver::Attach(IDispatch* pDisp)
{
	Clear();
	if(pDisp==NULL)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Invalid dipatch pointer",m_hRet);
		#endif
		return false;
	}
	m_pDisp = pDisp;
	m_pDisp->AddRef();
	return LoadTypeInfo();
}

int WDispatchDriver::FindProperty(LPCTSTR strPropertyName)
{
	return FindDispInfo(strPropertyName,DISPATCH_PROPERTYGET);
}

int WDispatchDriver::FindMethod(LPCTSTR strMethodName)
{
	return FindDispInfo(strMethodName);
}

WORD WDispatchDriver::GetPropertyType(LPCTSTR strPropertyName)
{
	int nPropertyIndex = FindProperty(strPropertyName);
	return GetPropertyType(nPropertyIndex);
}

WORD WDispatchDriver::GetPropertyType(int nPropertyIndex)
{
	if(nPropertyIndex>=0) return m_pDispInfo[nPropertyIndex].m_vtOutputType;
	else return VT_EMPTY;
}

VARIANT* WDispatchDriver::GetProperty(LPCTSTR strPropertyName)
{
	int nPropertyIndex = FindProperty(strPropertyName);
	if(nPropertyIndex>=0)
	{
		return GetProperty(nPropertyIndex);
	}
	return NULL;
}

VARIANT* WDispatchDriver::GetProperty(int nPropertyIndex)
{
	if(m_pDispInfo[nPropertyIndex].m_wFlag==DISPATCH_PROPERTYGET)
	{
		va_list argList;
		va_start(argList,nPropertyIndex);
		m_hRet = InvokeMethodV(nPropertyIndex, argList);
		va_end(argList);
		return m_hRet==S_OK?m_pDispInfo[nPropertyIndex].m_pOutput:NULL;
	}
	return NULL;
}

bool WDispatchDriver::SetProperty(LPCTSTR strPropertyName, ...)
{
	int nPropertyIndex = FindDispInfo(strPropertyName,DISPATCH_PROPERTYPUT);
	if(nPropertyIndex>=0)
	{
		va_list argList;
		va_start(argList,strPropertyName);
		m_hRet = InvokeMethodV(nPropertyIndex, argList);
		va_end(argList);
		return m_hRet==S_OK;
	}
	return false;
}

bool WDispatchDriver::SetProperty(int nPropertyIndex, ...)
{
	if(m_pDispInfo[nPropertyIndex].m_wFlag==DISPATCH_PROPERTYPUT)
	{
		va_list argList;
		va_start(argList,nPropertyIndex);
		m_hRet = InvokeMethodV(nPropertyIndex, argList);
		va_end(argList);
		return m_hRet==S_OK;
	}
	return false;
}

bool WDispatchDriver::SetPropertyRef(LPCTSTR strPropertyName, ...)
{
	int nPropertyIndex = FindDispInfo(strPropertyName,DISPATCH_PROPERTYPUTREF);
	if(nPropertyIndex>=0)
	{
		va_list argList;
		va_start(argList,strPropertyName);
		m_hRet = InvokeMethodV(nPropertyIndex, argList);
		va_end(argList);
		return m_hRet==S_OK;
	}
	return false;
}

bool WDispatchDriver::SetPropertyRef(int nPropertyIndex, ...)
{
	if(m_pDispInfo[nPropertyIndex].m_wFlag==DISPATCH_PROPERTYPUTREF)
	{
		va_list argList;
		va_start(argList,nPropertyIndex);
		m_hRet = InvokeMethodV(nPropertyIndex, argList);
		va_end(argList);
		return m_hRet==S_OK;
	}
	return false;
}

WORD WDispatchDriver::GetReturnType(LPCTSTR strMethodName)
{
	int nMethodIndex = FindMethod(strMethodName);
	return GetReturnType(nMethodIndex);
}

WORD WDispatchDriver::GetReturnType(int nMethodIndex)
{
	if(nMethodIndex>=0) return m_pDispInfo[nMethodIndex].m_vtOutputType;
	else return VT_EMPTY;
}

int WDispatchDriver::GetParamCount(LPCTSTR strMethodName)
{
	int nMethodIndex = FindMethod(strMethodName);
	return GetParamCount(nMethodIndex);
}

int WDispatchDriver::GetParamCount(int nMethodIndex)
{
	if(nMethodIndex>=0) return m_pDispInfo[nMethodIndex].m_nParamCount;
	else return -1;
}

WORD WDispatchDriver::GetParamType(LPCTSTR strMethodName, const int nParamIndex)
{
	int nMethodIndex = FindMethod(strMethodName);
	return GetParamType(nMethodIndex, nParamIndex);
}

WORD WDispatchDriver::GetParamType(int nMethodIndex, const int nParamIndex)
{
	if(nMethodIndex>=0&&nParamIndex>=0&&nParamIndex<m_pDispInfo[nMethodIndex].m_nParamCount)
	{
		return m_pDispInfo[nMethodIndex].m_pParamTypes[nParamIndex];
	}
	else return VT_EMPTY;
}

VARIANT* WDispatchDriver::InvokeMethod(LPCTSTR strMethodName, ...)
{
	int nMethodIndex = FindMethod(strMethodName);
	if(nMethodIndex>=0)
	{
		va_list argList;
		va_start(argList,strMethodName);
		m_hRet = InvokeMethodV(nMethodIndex, argList);
		va_end(argList);
		return m_hRet==S_OK?m_pDispInfo[nMethodIndex].m_pOutput:NULL;
	}
	return NULL;
}

VARIANT* WDispatchDriver::InvokeMethod(int nMethodIndex, ...)
{
	if(m_pDispInfo[nMethodIndex].m_wFlag==DISPATCH_METHOD)
	{
		va_list argList;
		va_start(argList,nMethodIndex);
		m_hRet = InvokeMethodV(nMethodIndex, argList);
		va_end(argList);
		return m_hRet==S_OK?m_pDispInfo[nMethodIndex].m_pOutput:NULL;
	}
	return NULL;
}

int WDispatchDriver::FindDispInfo(const QString& strName, const WORD wFlag)
{
	int nRet = -1;
	for(int i=0;i<m_nDispInfoCount;i++)
	{
		if(wcscmp((const wchar_t*)strName.utf16(),m_pDispInfo[i].m_bstrName)==0&&m_pDispInfo[i].m_wFlag==wFlag)
		{
			nRet = i;
			break;
		}
	}
	return nRet;
}

HRESULT WDispatchDriver::InvokeMethodV(int nIndex, va_list argList)
{
	m_hRet = S_OK;

	if(m_pDispInfo[nIndex].m_wFlag==0)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Invalid invokation flag\n");
		#endif
		m_hRet = S_FALSE;
		return m_hRet;
	}

	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = m_pDispInfo[nIndex].m_nParamCount;

	DISPID dispidNamed = DISPID_PROPERTYPUT;
	if(m_pDispInfo[nIndex].m_wFlag&(DISPATCH_PROPERTYPUT|DISPATCH_PROPERTYPUTREF))
	{
		dispparams.cNamedArgs = 1;
		dispparams.rgdispidNamedArgs = &dispidNamed;
	}

	if(dispparams.cArgs!=0)
	{
		// allocate memory for all VARIANT parameters
		VARIANT* pArg = new VARIANT[dispparams.cArgs];
		dispparams.rgvarg = pArg;
		memset(pArg, 0, sizeof(VARIANT) * dispparams.cArgs);

		// get ready to walk vararg list
		const WORD* pb = m_pDispInfo[nIndex].m_pParamTypes;
		pArg += dispparams.cArgs - 1;   // params go in opposite order

		while(*pb!=0)
		{
			pArg->vt = *pb; // set the variant type
			switch (pArg->vt)
			{
			case VT_UI1:
				pArg->bVal = va_arg(argList, BYTE);
				break;
			case VT_I2:
				pArg->iVal = va_arg(argList, short);
				break;
			case VT_I4:
				pArg->lVal = va_arg(argList, long);
				break;
			case VT_R4:
				pArg->vt = VT_R4;
				pArg->fltVal = va_arg(argList, float);
				break;
			case VT_R8:
				pArg->dblVal = va_arg(argList, double);
				break;
			case VT_BOOL:
				pArg->boolVal = (VARIANT_BOOL)(va_arg(argList, BOOL) ? -1 : 0);
				break;
			case VT_ERROR:
				pArg->scode = va_arg(argList, SCODE);
				break;
			case VT_DATE:
				pArg->date = va_arg(argList, DATE);
				break;
			case VT_CY:
				pArg->cyVal = va_arg(argList, CY);
				break;
			case VT_BSTR:
				{
				#ifdef _UNICODE
					LPCOLESTR lpsz = va_arg(argList, LPOLESTR);
					pArg->bstrVal = ::SysAllocString(lpsz);
				#else
					LPCSTR lpsz = va_arg(argList, LPSTR);
					QString s = QString::fromLatin1(lpsz);
					pArg->bstrVal = QStringToBSTR(s);
				#endif
				}
				break;
			case VT_UNKNOWN:
				pArg->punkVal = va_arg(argList, LPUNKNOWN);
				break;
			case VT_DISPATCH:
				pArg->pdispVal = va_arg(argList, LPDISPATCH);
				break;
			case VT_VARIANT:
				*pArg = va_arg(argList, VARIANT);
				break;
			case VT_UI1|VT_BYREF:
				pArg->pbVal = va_arg(argList,unsigned char*);
				break;
			case VT_I2|VT_BYREF:
				pArg->piVal = va_arg(argList, short*);
				break;
			case VT_I4|VT_BYREF:
				pArg->plVal = va_arg(argList, long*);
				break;
			case VT_R4|VT_BYREF:
				pArg->pfltVal = va_arg(argList, float*);
				break;
			case VT_R8|VT_BYREF:
				pArg->pdblVal = va_arg(argList, double*);
				break;
			case VT_BOOL|VT_BYREF:
				{
					// coerce BOOL into VARIANT_BOOL
					BOOL* pboolVal = va_arg(argList, BOOL*);
					*pboolVal = (*pboolVal)?MAKELONG(0,-1):0;
					pArg->pboolVal = (VARIANT_BOOL*)pboolVal;
				}
				break;
			case VT_ERROR|VT_BYREF:
				pArg->pscode = va_arg(argList, SCODE*);
				break;
			case VT_DATE|VT_BYREF:
				pArg->pdate = va_arg(argList, DATE*);
				break;
			case VT_CY|VT_BYREF:
				pArg->pcyVal = va_arg(argList, CY*);
				break;
			case VT_BSTR|VT_BYREF:
				pArg->pbstrVal = va_arg(argList, BSTR*);
				break;
			case VT_UNKNOWN|VT_BYREF:
				pArg->ppunkVal = va_arg(argList, LPUNKNOWN*);
				break;
			case VT_DISPATCH|VT_BYREF:
				pArg->ppdispVal = va_arg(argList, LPDISPATCH*);
				break;
			case VT_VARIANT|VT_BYREF:
				pArg->pvarVal = va_arg(argList, VARIANT*);
				break;
			case VT_ARRAY:
			case VT_ARRAY|VT_I2:
			case VT_ARRAY|VT_I4:
			case VT_ARRAY|VT_R4:
			case VT_ARRAY|VT_R8:
			case VT_ARRAY|VT_DATE:
			case VT_ARRAY|VT_CY:
			case VT_ARRAY|VT_BSTR:
			case VT_ARRAY|VT_DISPATCH:
			case VT_ARRAY|VT_ERROR:
			case VT_ARRAY|VT_BOOL:
			case VT_ARRAY|VT_VARIANT:
			case VT_ARRAY|VT_UNKNOWN:
			case VT_ARRAY|VT_UI1:
				pArg->parray = va_arg(argList, SAFEARRAY*);
				break;
			case VT_ARRAY|VT_BYREF:
			case VT_ARRAY|VT_I2|VT_BYREF:
			case VT_ARRAY|VT_I4|VT_BYREF:
			case VT_ARRAY|VT_R4|VT_BYREF:
			case VT_ARRAY|VT_R8|VT_BYREF:
			case VT_ARRAY|VT_DATE|VT_BYREF:
			case VT_ARRAY|VT_CY|VT_BYREF:
			case VT_ARRAY|VT_BSTR|VT_BYREF:
			case VT_ARRAY|VT_DISPATCH|VT_BYREF:
			case VT_ARRAY|VT_ERROR|VT_BYREF:
			case VT_ARRAY|VT_BOOL|VT_BYREF:
			case VT_ARRAY|VT_VARIANT|VT_BYREF:
			case VT_ARRAY|VT_UNKNOWN|VT_BYREF:
			case VT_ARRAY|VT_UI1|VT_BYREF:
				pArg->pparray = va_arg(argList, SAFEARRAY **);
				break;
			default:
				break;
			}
			--pArg; // get ready to fill next argument
			++pb;
		}
	}

	// initialize return value
	VARIANT* pvarResult = m_pDispInfo[nIndex].m_pOutput;
	::VariantClear(pvarResult);

	// initialize EXCEPINFO struct
	{
		::SysFreeString(m_exceptInfo.bstrSource);
		::SysFreeString(m_exceptInfo.bstrDescription);
		::SysFreeString(m_exceptInfo.bstrHelpFile);
		::memset(&m_exceptInfo, 0, sizeof(EXCEPINFO));
	}

	UINT nArgErr = (UINT)-1;  // initialize to invalid arg

	// make the call
	m_hRet = m_pDisp->Invoke(m_pDispInfo[nIndex].m_dispID,IID_NULL,LOCALE_SYSTEM_DEFAULT,m_pDispInfo[nIndex].m_wFlag,&dispparams,pvarResult,&m_exceptInfo,&nArgErr);

	// cleanup any arguments that need cleanup
	if (dispparams.cArgs != 0)
	{
		VARIANT* pArg = dispparams.rgvarg + dispparams.cArgs - 1;
		const WORD* pb = m_pDispInfo[nIndex].m_pParamTypes;
		while (*pb != 0)
		{
			switch (*pb)
			{
			case VT_BSTR:
				::SysFreeString(pArg->bstrVal);
				break;
			}
			--pArg;
			++pb;
		}
	}
	delete[] dispparams.rgvarg;

	// throw exception on failure
	if(m_hRet<0)
	{
		::VariantClear(m_pDispInfo[nIndex].m_pOutput);
		if(m_hRet!=DISP_E_EXCEPTION)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("Invoke failed, no exception: %x\n",m_hRet);
			#endif
			return m_hRet;
		}

		// make sure excepInfo is filled in
		if(m_exceptInfo.pfnDeferredFillIn != NULL)
			m_exceptInfo.pfnDeferredFillIn(&m_exceptInfo);

		#ifdef XYDISPDRIVER_DEBUG
		qWarning(L"Exception source: %s\n",m_exceptInfo.bstrSource);
		qWarning(L"Exception description: %s\n",m_exceptInfo.bstrDescription);
		qWarning(L"Exception help file: %s\n",m_exceptInfo.bstrHelpFile);
		#endif
		return m_hRet;
	}

	// if(m_pDispInfo[nIndex].m_vtOutputType!=VT_EMPTY)
	// {
		// m_pDispInfo[nIndex].m_pOutput->vt = m_pDispInfo[nIndex].m_vtOutputType;
	// }
	return m_hRet;
}

bool WDispatchDriver::Advise(IUnknown __RPC_FAR *pUnkSink, REFIID riid)
{
	if(m_pDisp==NULL)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Null dipatch pointer\n");
		#endif
		m_hRet = S_FALSE;
		return false;
	}
	Unadvise();
	IConnectionPointContainer* pCPContainer = NULL;
	m_hRet = m_pDisp->QueryInterface(IID_IConnectionPointContainer,(void**)&pCPContainer);
	if(m_hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Failed to call QueryInterface to get the IConnectionPointContainer interface: %x\n",m_hRet);
		#endif
		return false;
	}
	m_hRet = pCPContainer->FindConnectionPoint(riid,&m_pCP);
	pCPContainer->Release();
	if(m_hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Failed to call FindConnectionPoint to get the IConnectionPointerface: %x\n",m_hRet);
		#endif
		return false;
	}
	m_hRet = m_pCP->Advise(pUnkSink,&m_dwCookie);
	if(m_hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Failed to call Advise: %x\n",m_hRet);
		#endif
		m_pCP->Release();
		m_pCP = NULL;
		return false;
	}
	return true;
}

void WDispatchDriver::Unadvise()
{
	if(m_pCP!=NULL)
	{
		m_hRet = m_pCP->Unadvise(m_dwCookie);
		if(m_hRet!=S_OK)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("Failed to call Unadvise: %x\n",m_hRet);
			#endif
		}
		m_pCP->Release();
		m_pCP = NULL;
		m_dwCookie = 0;
	}
}

HRESULT WDispatchDriver::InvokeVariantMethod(IDispatch* pDisp,
										  LPCTSTR strMethodName,
										  WORD wInvokeFlag,
										  VARIANT* pVarRet,
										  EXCEPINFO* pExcepInfo,
										  const int nParamCount, ...)
{
	if(pDisp==NULL||strMethodName==NULL||nParamCount<0)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Invalid parameters to InvokeVariantMethod");
		#endif
		return S_FALSE;
	}
	DISPID dispid;
#ifdef _UNICODE
	WCHAR* pName = (WCHAR*)strMethodName;
#else
	QString sMethodName = QString::fromLatin1(strMethodName);
	WCHAR* pName = (WCHAR*)sMethodName.utf16();
#endif
	HRESULT hRet = pDisp->GetIDsOfNames(IID_NULL,&pName,1,LOCALE_SYSTEM_DEFAULT,&dispid);
	#ifndef _UNICODE
	delete []pName;
	#endif
	if(hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("GetIDsOfNames failed: %x\n",hRet);
		#endif
		return hRet;
	}
	else
	{
		va_list argList;
		va_start(argList,nParamCount);
		hRet = InvokeVariantMethodV(pDisp, dispid, wInvokeFlag, pVarRet, pExcepInfo, nParamCount, argList);
		va_end(argList);
	}
	return hRet;
}



HRESULT WDispatchDriver::InvokeVariantMethod(IDispatch* pDisp,
										  const DISPID dispidMethod,
										  WORD wInvokeFlag,
										  VARIANT* pVarRet,
										  EXCEPINFO* pExcepInfo,
										  const int nParamCount,
										  ...)
{
	if(pDisp==NULL||nParamCount<0)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Invalid parameters to InvokeVariantMethod");
		#endif
		return S_FALSE;
	}
	va_list argList;
	va_start(argList,nParamCount);
	HRESULT hRet = InvokeVariantMethodV(pDisp, dispidMethod, wInvokeFlag, pVarRet, pExcepInfo, nParamCount, argList);
	va_end(argList);
	return hRet;
}

HRESULT WDispatchDriver::InvokeVariantMethodV(IDispatch* pDisp, const DISPID dispidMethod, WORD wInvokeFlag, VARIANT* pVarRet, EXCEPINFO* pExcepInfo, const int nParamCount, va_list argList)
{
	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = nParamCount;
	if(nParamCount>0)
	{
		dispparams.rgvarg = new VARIANT[nParamCount];
		memset(dispparams.rgvarg, 0, sizeof(VARIANT)*nParamCount);
		VARIANT* pArg;
		for(int i=nParamCount-1;i>=0;i--)
		{
			pArg = dispparams.rgvarg+i;
			*pArg = va_arg(argList, VARIANT);
		}
	}
	else dispparams.rgvarg = NULL;
	if(pVarRet) ::VariantInit(pVarRet);
	UINT nArgErr = (UINT)-1;
	HRESULT hRet = pDisp->Invoke(dispidMethod,IID_NULL,LOCALE_SYSTEM_DEFAULT,wInvokeFlag,&dispparams,pVarRet,pExcepInfo,&nArgErr);
	if(nParamCount>0) delete[] dispparams.rgvarg;
	if(hRet!=S_OK)
	{
		#ifdef XYDISPDRIVER_DEBUG
		qWarning("Invoke failed: %x\n",hRet);
		#endif
		if(pVarRet) ::VariantClear(pVarRet);
		if(hRet==DISP_E_EXCEPTION)
		{
			#ifdef XYDISPDRIVER_DEBUG
			qWarning("Exception occurred\n");
			#endif
			if(pExcepInfo)
			{
				if(pExcepInfo->pfnDeferredFillIn != NULL)
					pExcepInfo->pfnDeferredFillIn(pExcepInfo);

				#ifdef XYDISPDRIVER_DEBUG
				qWarning(L"Exception source: %s\n",QString::fromWCharArray(pExcepInfo->bstrSource));
				qWarning(L"Exception description: %s\n",QString::fromWCharArray(pExcepInfo->bstrDescription));
				qWarning(L"Exception help file: %s\n",QString::fromWCharArray(pExcepInfo->bstrHelpFile));
				#endif
			}
		}
	}
	return hRet;
}

#ifndef _WINAPI_H_
#define _WINAPI_H_

#include <qt_windows.h>
#include <shlwapi.h>

namespace WinApi
{
	HRESULT SetCurrentProcessExplicitAppUserModelID(PCWSTR AppID);
	HRESULT PropVariantClear(PROPVARIANT *variant);

	inline void PropVariantInit(PROPVARIANT *variant)
	{
		memset(variant, 0, sizeof(PROPVARIANT));
	}

	inline HRESULT InitPropVariantFromString(PCWSTR string, PROPVARIANT *propvar)
	{
		propvar->vt = VT_LPWSTR;
		HRESULT hr = SHStrDupW(string, &propvar->pwszVal);
		if (FAILED(hr)) {
			WinApi::PropVariantInit(propvar);
		}
		return hr;
	}

	inline HRESULT InitPropVariantFromBoolean(BOOL value, PROPVARIANT *variant)
	{
		 variant->vt = VT_BOOL;
		 variant->boolVal = value ? VARIANT_TRUE : VARIANT_FALSE;
		 return S_OK;
	}

}

#endif

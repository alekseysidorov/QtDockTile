#include "_winapi.h"

namespace WinApi
{
	typedef HRESULT (__stdcall * SetCurrentProcessExplicitAppUserModelID_t)(PCWSTR AppID);
	typedef HRESULT (__stdcall * PropVariantClear_t)(PROPVARIANT *);

	HRESULT SetCurrentProcessExplicitAppUserModelID(PCWSTR AppID)
	{
		static SetCurrentProcessExplicitAppUserModelID_t impl = 0;
		static bool tried = false;
		if (!impl && !tried) {
            HMODULE lib = LoadLibrary(L"shell32.dll");
			if (lib) {
				impl  = reinterpret_cast<SetCurrentProcessExplicitAppUserModelID_t>(GetProcAddress(lib, "SetCurrentProcessExplicitAppUserModelID"));
			}
			tried = true;
		}
		if (impl)
			return impl(AppID);
		else
			return E_NOTIMPL;
	}

	HRESULT PropVariantClear(PROPVARIANT *variant)
	{
		static PropVariantClear_t impl = 0;
		static bool tried = false;
		if (!impl && !tried) {
            HMODULE lib = LoadLibrary(L"ole32.dll");
			impl  = reinterpret_cast<PropVariantClear_t>(GetProcAddress(lib, "PropVariantClear"));
			tried = true;
		}
		if (impl)
			return impl(variant);
		else
			return E_NOTIMPL;
	}
}

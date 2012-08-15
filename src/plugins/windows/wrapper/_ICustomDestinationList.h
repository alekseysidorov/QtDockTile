#ifndef _ICUSTOMDESTINATIONLIST_H_
#define _ICUSTOMDESTINATIONLIST_H_

#include <qt_windows.h>
#include <commctrl.h>

#ifndef COMMETHOD
#	define COMMETHOD virtual __stdcall
#endif

namespace WinApi
{
	const CLSID CLSID_DestinationList            = {0x77f10cf0, 0x3db5, 0x4966, {0xb5, 0x20, 0xb7, 0xc5, 0x4f, 0xd3, 0x5e, 0xd6}};
	const CLSID CLSID_EnumerableObjectCollection = {0x2d3468c1, 0x36a7, 0x43b6, {0xac, 0x24, 0xd3, 0xf0, 0x2f, 0xd9, 0x60, 0x7a}};
	const CLSID CLSID_ShellLink                  = {0x00021401, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
	const IID   IID_ICustomDestinationList       = {0x6332debf, 0x87b5, 0x4670, {0x90, 0xc0, 0x5e, 0x57, 0xb4, 0x08, 0xa4, 0x9e}};
	const IID   IID_IObjectArray                 = {0x92CA9DCD, 0x5622, 0x4bba, {0xA8, 0x05, 0x5E, 0x9F, 0x54, 0x1B, 0xD8, 0xC9}};
	const IID   IID_IObjectCollection            = {0x5632b1a4, 0xe38a, 0x400a, {0x92, 0x8a, 0xd4, 0xcd, 0x63, 0x23, 0x02, 0x95}};
	const IID   IID_IShellLinkW                  = {0x000214F9, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
	const IID   IID_IPropertyStore               = {0x886d8eeb, 0x8cf2, 0x4446, {0x8d, 0x02, 0xcd, 0xba, 0x1d, 0xbd, 0xcf, 0x99}};

	struct IObjectArray;

	enum KNOWNDESTCATEGORY {
		KDC_FREQUENT = 1,
		KDC_RECENT = 2
	};

	struct ICustomDestinationList : public IUnknown
	{
		HRESULT COMMETHOD SetAppID(LPCWSTR AppID) = 0;
		HRESULT COMMETHOD BeginList(UINT *minSlots, REFIID riid, void **ppv) = 0;
		HRESULT COMMETHOD AppendCategory(LPCWSTR category, IObjectArray *poa) = 0;
		HRESULT COMMETHOD AppendKnownCategory(KNOWNDESTCATEGORY category) = 0;
		HRESULT COMMETHOD AddUserTasks(IObjectArray *poa) = 0;
		HRESULT COMMETHOD CommitList() = 0;
		HRESULT COMMETHOD GetRemovedDestinations(REFIID riid, void **ppv) = 0;
		HRESULT COMMETHOD DeleteList(LPCWSTR AppID) = 0;
		HRESULT COMMETHOD AbortList() = 0;
	};

	struct IObjectArray : public IUnknown
	{
		HRESULT COMMETHOD GetCount(UINT *objects) = 0;
		HRESULT COMMETHOD GetAt(UINT index, REFIID riid, void **ppv) = 0;
	};

	struct IObjectCollection : IObjectArray
	{
		HRESULT COMMETHOD AddObject(IUnknown *punk) = 0;
		HRESULT COMMETHOD AddFromArray(IObjectArray *source) = 0;
		HRESULT COMMETHOD RemoveObjectAt(UINT index) = 0;
		HRESULT COMMETHOD Clear() = 0;
	};

	struct IShellLinkW : public IUnknown
	{
		typedef void PIDLIST_ABSOLUTE;
		typedef void *PCIDLIST_ABSOLUTE;

		HRESULT COMMETHOD GetPath(LPWSTR file, int cch, WIN32_FIND_DATAW *pfd, DWORD flags) = 0;
		HRESULT COMMETHOD GetIDList(PIDLIST_ABSOLUTE *ppidl) = 0;
		HRESULT COMMETHOD SetIDList(PCIDLIST_ABSOLUTE pidl) = 0;
		HRESULT COMMETHOD GetDescription(LPWSTR name, int cch) = 0;
		HRESULT COMMETHOD SetDescription(LPCWSTR name) = 0;
		HRESULT COMMETHOD GetWorkingDirectory(LPWSTR dir, int cch) = 0;
		HRESULT COMMETHOD SetWorkingDirectory(LPCWSTR dir) = 0;
		HRESULT COMMETHOD GetArguments(LPWSTR args, int cch) = 0;
		HRESULT COMMETHOD SetArguments(LPCWSTR args) = 0;
		HRESULT COMMETHOD GetHotkey(WORD *hotkey) = 0;
		HRESULT COMMETHOD SetHotkey(WORD hotkey) = 0;
		HRESULT COMMETHOD GetShowCmd(int *showCmd) = 0;
		HRESULT COMMETHOD SetShowCmd(int showCmd) = 0;
		HRESULT COMMETHOD GetIconLocation(LPWSTR iconPath, int cch, int *icon) = 0;
		HRESULT COMMETHOD SetIconLocation(LPCWSTR iconPath, int icon) = 0;
		HRESULT COMMETHOD SetRelativePath(LPCWSTR pathRel, DWORD reserved) = 0;
		HRESULT COMMETHOD Resolve(HWND hwnd, DWORD flags) = 0;
		HRESULT COMMETHOD SetPath(LPCWSTR file) = 0;
	};

	struct PROPERTYKEY {
	  GUID  fmtid;
	  DWORD pid;
	};

	const PROPERTYKEY PKEY_Title = {{0xF29F85E0, 0x4FF9, 0x1068, {0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9}}, 0x02};
	const PROPERTYKEY PKEY_AppUserModel_IsDestListSeparator = {{0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}}, 6};

	struct IPropertyStore : IUnknown
	{
		 HRESULT COMMETHOD GetCount(DWORD *props) = 0;
		 HRESULT COMMETHOD GetAt(DWORD prop, PROPERTYKEY *key) = 0;
		 HRESULT COMMETHOD GetValue(const PROPERTYKEY &key, PROPVARIANT *pv) = 0;
		 HRESULT COMMETHOD SetValue(const PROPERTYKEY &key, PROPVARIANT &propvar) = 0;
		 HRESULT COMMETHOD Commit() = 0;
	};

}

#endif // _ICUSTOMDESTINATIONLIST_H_

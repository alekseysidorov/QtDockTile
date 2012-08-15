#ifndef _ITASKBARLIST4_H_
#define _ITASKBARLIST4_H_

#include <windows.h>
#include <basetyps.h>
#include <commctrl.h>

#ifndef COMMETHOD
#	define COMMETHOD virtual __stdcall
#endif

namespace WinApi
{
	const GUID CLSID_TaskbarList = {0x56FDF344, 0xFD6D, 0x11d0, {0x95, 0x8A, 0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90}};
	const GUID IID_ITaskbarList4 = {0xc43dc798, 0x95d1, 0x4bea, {0x90, 0x30, 0xbb, 0x99, 0xe2, 0x98, 0x3a, 0x1a}};

	struct THUMBBUTTON {
		enum THUMBBUTTONMASK {
		  THB_BITMAP    = 0x00000001,
		  THB_ICON      = 0x00000002,
		  THB_TOOLTIP   = 0x00000004,
		  THB_FLAGS     = 0x00000008
		};

		enum THUMBBUTTONFLAGS {
		  THBF_ENABLED          = 0x00000000,
		  THBF_DISABLED         = 0x00000001,
		  THBF_DISMISSONCLICK   = 0x00000002,
		  THBF_NOBACKGROUND     = 0x00000004,
		  THBF_HIDDEN           = 0x00000008,
		  THBF_NONINTERACTIVE   = 0x00000010
		};

		THUMBBUTTONMASK  dwMask;
		UINT             iId;
		UINT             iBitmap;
		HICON            hIcon;
		WCHAR            szTip[260];
		THUMBBUTTONFLAGS dwFlags;
	};

	enum TBPFLAG {
		TBPF_NOPROGRESS = 0x00000000,
		TBPF_INDETERMINATE = 0x00000001,
		TBPF_NORMAL = 0x00000002,
		TBPF_ERROR = 0x00000004,
		TBPF_PAUSED = 0x00000008
	};

	enum STPFLAG {
		STPF_NONE                        = 0x00000000,
		STPF_USEAPPTHUMBNAILALWAYS       = 0x00000001,
		STPF_USEAPPTHUMBNAILWHENACTIVE   = 0x00000002,
		STPF_USEAPPPEEKALWAYS            = 0x00000004,
		STPF_USEAPPPEEKWHENACTIVE        = 0x00000008
	};

	class IUnknown
	{
	public:
		 HRESULT COMMETHOD QueryInterface(IID &iid, void **object) = 0;
		 HRESULT COMMETHOD AddRef( void) = 0;
		 HRESULT COMMETHOD Release( void) = 0;
	};

	struct ITaskbarList4 : public IUnknown
	{
		// ------
		// ITL - http://msdn.microsoft.com/en-us/library/windows/desktop/bb774652.aspx
		HRESULT COMMETHOD HrInit() = 0;
		HRESULT COMMETHOD AddTab(HWND hwnd) = 0;
		HRESULT COMMETHOD DeleteTab(HWND hwnd) = 0;
		HRESULT COMMETHOD ActivateTab(HWND hwnd) = 0;
		HRESULT COMMETHOD SetActiveAlt(HWND hwnd) = 0;

		// -------
		// ITL2 - http://msdn.microsoft.com/en-us/library/windows/desktop/bb774638.aspx

		HRESULT COMMETHOD MarkFullscreenWindow(HWND hwnd, BOOL fFullscreen) = 0;

		// -------
		// ITL3 - http://msdn.microsoft.com/en-us/library/windows/desktop/dd391692.aspx

		HRESULT COMMETHOD SetProgressValue(HWND hwnd, ULONGLONG completed, ULONGLONG total) = 0;
		HRESULT COMMETHOD SetProgressState(HWND hwnd, TBPFLAG tbpFlags) = 0;
		HRESULT COMMETHOD RegisterTab(HWND tab, HWND window) = 0;
		HRESULT COMMETHOD UnregisterTab(HWND tab) = 0;
		HRESULT COMMETHOD SetTabOrder(HWND tab, HWND insertBefore) = 0;
		HRESULT COMMETHOD SetTabActive(HWND tab, HWND window, DWORD reserved = 0) = 0;
		HRESULT COMMETHOD ThumbBarAddButtons(HWND hwnd, UINT count, THUMBBUTTON buttons) = 0;
		HRESULT COMMETHOD ThumbBarUpdateButtons(HWND hwnd, UINT count, THUMBBUTTON *buttons) = 0;
		HRESULT COMMETHOD ThumbBarSetImageList(HWND hwnd, HIMAGELIST imglist) = 0;
		HRESULT COMMETHOD SetOverlayIcon(HWND hwnd, HICON icon, LPCWSTR description) = 0;
		HRESULT COMMETHOD SetThumbnailTooltip(HWND hwnd, LPCWSTR tooltip) = 0;
		HRESULT COMMETHOD SetThumbnailClip(HWND hwnd, RECT *clip) = 0;

		// -------
		// ITL4 - http://msdn.microsoft.com/en-us/library/windows/desktop/dd562040.aspx

		HRESULT COMMETHOD SetTabProperties(HWND tab, STPFLAG flags) = 0;
	};

}

#undef COMMETHOD

#endif // _ITASKBARLIST4_H_

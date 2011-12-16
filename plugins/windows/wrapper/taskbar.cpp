#include "taskbar.h"
#include <ShObjIdl.h>
#include <QtAlgorithms>

void setActionInvoker(ActionInvoker *pointer)
{

}

void setJumpLists(ActionInfo *list, size_t size)
{

}

void setApplicationId(const wchar_t *appId)
{

}

void setOverlayIcon(HWND winId, HICON icon, wchar_t *description)
{

}

void clearOverlayIcon(HWND winId)
{

}

void setProgress(HWND winId, int percents)
{
	int progress = qBound(0, percents, 100);
	ITaskbarList3 *taskbar;
	if(S_OK != CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&taskbar))
		return;
	taskbar->HrInit();
	taskbar->SetProgressValue(winId, progress, 100);
	taskbar->SetProgressState(winId, progress ? TBPF_NORMAL : TBPF_NOPROGRESS);
	taskbar->Release();
}

void setProgressState(HWND winId, ProgressState state)
{
	TBPFLAG flags;
	ITaskbarList3 *taskbar;
	if(S_OK != CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&taskbar))
		return;
	taskbar->HrInit();
	switch (state)	{
		default:
		case ProgressStateNone			: flags = TBPF_NOPROGRESS;    break;
		case ProgressStateNormal        : flags = TBPF_NORMAL;        break;
		case ProgressStatePaused        : flags = TBPF_PAUSED;        break;
		case ProgressStateError         : flags = TBPF_ERROR;         break;
		case ProgressStateIndeterminate : flags = TBPF_INDETERMINATE; break;
	}
	taskbar->SetProgressState(winId, flags);
	taskbar->Release();
}

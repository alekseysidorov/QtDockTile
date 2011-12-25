#include "taskbar.h"
#include <ShObjIdl.h>
#include "jumplistsmanager.h"
#include <iostream>

static ITaskbarList3 *windowsTaskBar()
{
	ITaskbarList3 *taskbar;
	if(S_OK != CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&taskbar))
		return 0;
	return taskbar;
}

void setActionInvoker(ActionInvoker pointer)
{
	jumpListsManager()->setActionInvoker(pointer);
}

void setJumpLists(ActionInfo *list, size_t size)
{
	jumpListsManager()->beginList();
	for (size_t i = 0; i != size; i++) {
		if (list[i].type == ActionTypeSeparator)
			jumpListsManager()->addSeparator();
		else
			jumpListsManager()->addTask(&list[i]);
	}
	jumpListsManager()->commitList();
}

void setApplicationId(const wchar_t *appId)
{
	jumpListsManager()->setAppId(appId);
}

void setOverlayIcon(HWND winId, HICON icon, wchar_t *description)
{
	ITaskbarList3 *taskbar = windowsTaskBar();
	if (!taskbar)
		return;

	if(description)
		taskbar->SetOverlayIcon(winId, icon, description);
	else
		taskbar->SetOverlayIcon(winId, icon, L"No description");
	taskbar->Release();
}

void clearOverlayIcon(HWND winId)
{
	ITaskbarList3 *taskbar = windowsTaskBar();
	if (!taskbar)
		return;

	setOverlayIcon(winId, 0, 0);
	taskbar->Release();
}

void setProgressValue(HWND winId, int progress)
{
	ITaskbarList3 *taskbar = windowsTaskBar();
	if (!taskbar)
		return;
	taskbar->HrInit();
	taskbar->SetProgressValue(winId, progress, 100);
	taskbar->SetProgressState(winId, progress ? TBPF_NORMAL : TBPF_NOPROGRESS);
	taskbar->Release();
}

void setProgressState(HWND winId, ProgressState state)
{
	TBPFLAG flags;
	ITaskbarList3 *taskbar = windowsTaskBar();
	if (!taskbar)
		return;
	taskbar->HrInit();
	switch (state)	{
		default:
		case ProgressStateNone          : flags = TBPF_NOPROGRESS;    break;
		case ProgressStateNormal        : flags = TBPF_NORMAL;        break;
		case ProgressStatePaused        : flags = TBPF_PAUSED;        break;
		case ProgressStateError         : flags = TBPF_ERROR;         break;
		case ProgressStateIndeterminate : flags = TBPF_INDETERMINATE; break;
	}
	taskbar->SetProgressState(winId, flags);
	taskbar->Release();
}

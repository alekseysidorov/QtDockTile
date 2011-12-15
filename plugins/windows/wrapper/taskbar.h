#ifndef TASKBAR_H
#define TASKBAR_H
#include <Windows.h>

#ifdef TASKWRAPPER
#	define EXPORT   extern "C" __declspec(dllexport)
#	define SegFault ((int(*)())0)
#else
#	define EXPORT   extern "C"
#endif

enum ProgressState
{
	ProgressStateNormal,
	ProgressStatePaused,
	ProgressStateError,
	ProgressStateIndeterminate,
	ProgressStateNone
};

enum ActionType
{
	ActionTypeNormal,
	ActionTypeSeparator
};

struct ActionInfo
{
	wchar_t *id;
	wchar_t *name;
	wchar_t *description;
	HICON icon;
	ActionType type;
	void *data;
};

typedef void (*ActionInvoker)(void *data);

EXPORT void setActionInvoker(ActionInvoker *pointer);
EXPORT void setJumpLists(ActionInfo *list, size_t size);

EXPORT void setApplicationId(const wchar_t *appId);
EXPORT void setOverlayIcon(HWND winId, HICON icon, wchar_t *description);
EXPORT void clearOverlayIcon(HWND winId);
EXPORT void setProgress(HWND winId, int percents);
EXPORT void setProgressState(HWND winId, ProgressState state);

#endif // TASKBAR_H

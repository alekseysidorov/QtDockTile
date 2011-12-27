#ifndef TASKBAR_H
#define TASKBAR_H
#include <windows.h>

#ifdef TASKWRAPPER
#	define EXPORT   extern "C" __declspec(dllexport)
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
	const char *id;
	wchar_t *name;
	wchar_t *description;
	wchar_t *iconPath;
	ActionType type;
	void *data;
};

typedef void (*ActionInvoker)(void*);

EXPORT void setActionInvoker(ActionInvoker pointer);
EXPORT void setJumpLists(ActionInfo *list, size_t size);
EXPORT void deleteJumpLists();

EXPORT void setApplicationId(const wchar_t *appId);
EXPORT void setOverlayIcon(HWND winId, HICON icon, wchar_t *description = 0);
EXPORT void clearOverlayIcon(HWND winId);
EXPORT void setProgressValue(HWND winId, int percents);
EXPORT void setProgressState(HWND winId, ProgressState state);

#endif // TASKBAR_H

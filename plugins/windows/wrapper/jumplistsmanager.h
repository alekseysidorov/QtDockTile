#ifndef JUMPLISTSMANAGER_H
#define JUMPLISTSMANAGER_H
#include "windows.h"
#include <string>
#include <map>

typedef void (*ActionInvoker)(void *data);
struct ActionInfo;
struct ICustomDestinationList;
struct IObjectCollection;

class JumpListsManager
{
public:
	static JumpListsManager *instance();
	void setAppId(const wchar_t *appId);
	//TODO
	void beginList();
	void addTask(ActionInfo *info);
	void deleteList(const wchar_t *appId = 0);
	void addSeparator();
	void beginCategory(const wchar_t *name);
	void commitList();
	void setActionInvoker(ActionInvoker pointer);
	ActionInvoker actionInvoker() const;
protected:
	JumpListsManager();
	~JumpListsManager();
private:
	const wchar_t *m_appId;
	ActionInvoker m_invoker;
	ICustomDestinationList *m_destList;
	IObjectCollection *m_destListContent;
	std::wstring m_wrapperPath;

	typedef std::map<std::string, ActionInfo*> ActionInfoMap;
	ActionInfoMap m_actionInfoMap;

	std::wstring makeArgs(ActionInfo *info);
	static void handlerCallback(const char *);
	static ActionInfo *actionInfo(const char *id);
};

inline JumpListsManager *jumpListsManager()
{
	return JumpListsManager::instance();
}

#endif // JUMPLISTSMANAGER_H

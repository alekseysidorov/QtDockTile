#include "jumplistsmanager.h"
#include <ShObjIdl.h>

JumpListsManager *JumpListsManager::instance()
{
	static JumpListsManager pointer;
	return &pointer;
}

void JumpListsManager::setAppId(const wchar_t *appId)
{
	SetCurrentProcessExplicitAppUserModelID(appId);
	m_appId = appId;
}

void JumpListsManager::beginList()
{
}

void JumpListsManager::addTask(ActionInfo *info)
{
}

void JumpListsManager::addSeparator()
{
}

void JumpListsManager::beginCategory(const wchar_t *name)
{
}

void JumpListsManager::commitList()
{
}

void JumpListsManager::setActionInvoker(ActionInvoker pointer)
{
	m_invoker = pointer;
}

ActionInvoker JumpListsManager::actionInvoker() const
{
	return m_invoker;
}

JumpListsManager::JumpListsManager() :
	m_appId(0),
	m_invoker(0)
{
}

JumpListsManager::~JumpListsManager()
{
}

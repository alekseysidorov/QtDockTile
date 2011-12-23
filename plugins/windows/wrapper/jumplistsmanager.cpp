#include "jumplistsmanager.h"
#include "taskbar.h"
#include <ShObjIdl.h>
#include <Propvarutil.h>
#include <Propkey.h>

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
	if (m_destList)
		return;

	ICustomDestinationList *list;
	HRESULT res = CoCreateInstance(CLSID_DestinationList, 0, CLSCTX_INPROC_SERVER, IID_ICustomDestinationList, (void**)&list);
	if (FAILED(res)) {
		return;
	}
	UINT maxSlots;
	m_destList = list;
	m_destList->SetAppID(m_appId);

	m_destList->BeginList(&maxSlots, IID_IObjectArray, (void**)&m_destListContent);
	m_destListContent->Release();

	IObjectArray *objArray;
	CoCreateInstance(CLSID_EnumerableObjectCollection, 0, CLSCTX_INPROC_SERVER, IID_IObjectArray, (void**)&objArray);
	objArray->QueryInterface(IID_IObjectCollection, (void**)&m_destListContent);
	objArray->Release();
}

void JumpListsManager::addTask(ActionInfo *info)
{
	if (!m_destList)
		return;
	IShellLinkW *task;
	HRESULT res = CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&task);
	if (FAILED(res))
		return;
	task->SetDescription(info->description);
	task->SetPath(L"prog");
	task->SetArguments(L"args");

	IPropertyStore *title;
	PROPVARIANT titlepv;
	res = task->QueryInterface(IID_IPropertyStore, (void**)&title);
	if (FAILED(res)) {
		task->Release();
		return;
	}
	InitPropVariantFromString(info->name, &titlepv);
	title->SetValue(PKEY_Title, titlepv);
	title->Commit();
	PropVariantClear(&titlepv);

	res = m_destListContent->AddObject(task);
	title->Release();
	task->Release();
}

void JumpListsManager::deleteList(const wchar_t *appId)
{
	beginList();
	m_destList->DeleteList(appId);
	commitList();
}

void JumpListsManager::addSeparator()
{
	IShellLinkW *separator;
	IPropertyStore *propStore;
	PROPVARIANT pv;
	HRESULT res = CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&separator);
	if (FAILED(res))
		return;
	res = separator->QueryInterface(IID_IPropertyStore, (void**)&propStore);
	if (FAILED(res)) {
		separator->Release();
		return;
	}
	InitPropVariantFromBoolean(TRUE, &pv);
	propStore->SetValue(PKEY_AppUserModel_IsDestListSeparator, pv);
	PropVariantClear(&pv);
	propStore->Commit();
	propStore->Release();
	res = m_destListContent->AddObject(separator);
	separator->Release();
}

void JumpListsManager::beginCategory(const wchar_t *name)
{
}

void JumpListsManager::commitList()
{
	if (!m_destList)
		return;

	m_destList->AddUserTasks(m_destListContent);
	m_destList->CommitList();
	m_destList->Release();
	m_destListContent->Release();
	m_destList = 0;
	m_destListContent = 0;
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
	m_invoker(0),
	m_destList(0),
	m_destListContent(0)
{
}

JumpListsManager::~JumpListsManager()
{
}

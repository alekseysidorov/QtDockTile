#include "jumplistsmanager.h"
#include "taskbar.h"
#include "handling.h"
#include <ShObjIdl.h>
#include <Propvarutil.h>
#include <Propkey.h>
#include <string>

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
	task->SetPath(L"rundll32.exe");
	task->SetArguments(makeArgs(info).c_str());
	if (info->iconPath)
		task->SetIconLocation(info->iconPath, 0);

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
	if (!appId)
		appId = m_appId;
	ICustomDestinationList *list;
	CoInitialize(0);
	HRESULT res = CoCreateInstance(CLSID_DestinationList, 0, CLSCTX_INPROC_SERVER, IID_ICustomDestinationList, (void**)&list);
	if (FAILED(res))
		return;
	res = list->DeleteList(appId);
	list->Release();
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
	Handler::instance()->setCallback(&JumpListsManager::handlerCallback);
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
	const int buffsize = 4096;
	wchar_t *buff = new wchar_t[buffsize];
	const int pathLen = GetModuleFileNameW(0, buff, buffsize);
	if (pathLen > 0) {
		buff[pathLen] = 0;
		m_wrapperPath = buff;
#ifdef _DEBUG
		m_wrapperPath.replace(m_wrapperPath.find_last_of(L"\\")+1, std::wstring::npos, L"wrapperd.dll");
#else
		m_wrapperPath.replace(m_wrapperPath.find_last_of(L"\\")+1, std::wstring::npos, L"wrapper.dll");
#endif
	}
	delete[] buff;
}

JumpListsManager::~JumpListsManager()
{
}

std::wstring JumpListsManager::makeArgs(ActionInfo *info)
{
	std::wstring args = m_wrapperPath;
#ifdef _WIN64
	args += L",_RundllCallback@28 "; // WARNING: TEST ME! // ptr×3 + int
#else
	args += L",_RundllCallback@16 ";
#endif
	wchar_t buffer[16] = {0};
	const int res = swprintf(buffer, 15, L"%x", reinterpret_cast<uintptr_t>(info->data));
	if (res) {
		buffer[res] = 0;
		args += buffer;
	}
	return args;
}

void JumpListsManager::handlerCallback(const char *b)
{
#pragma warning(push)
#pragma warning(disable:4244)
	uintptr_t ptr = _strtoui64(b, 0, 16);
#pragma warning(pop)
	if (JumpListsManager::instance()->actionInvoker())
		JumpListsManager::instance()->actionInvoker()(reinterpret_cast<void*>(ptr));
}

#include "temporaryfile.h"
#include <objbase.h>
#include <vector>
#include "stdio.h"

static std::wstring getTempPath()
{
	DWORD result = ::GetTempPath(0, "");
	if(result == 0)
		throw std::runtime_error("Could not get system temp path");

	// Allocate temporary buffer. The retured length includes the terminating _T('\0').
	// std::vector is guaranteed to be sequential, thus can serve as a buffer that can be written to.
	std::vector<TCHAR> tempPath(result);

	// If the buffer is large enough, the return value does _not_ include the terminating _T('\0')
	result = ::GetTempPath(static_cast<DWORD>(tempPath.size()), &tempPath[0]);
	if((result == 0) || (result > tempPath.size()))
		throw std::runtime_error("Could not get system temp path");

	return std::wstring(tempPath.begin(), tempPath.begin() + static_cast<std::size_t>(result));
}

static std::wstring generateGuid()
{
	RPC_CSTR cstr = NULL;
	GUID guid;
	CoCreateGuid(&guid);
	UuidToString(&guid, &cstr);

	//black magic
	char *str = reinterpret_cast<char*>(cstr);
	int len = strlen(str);
	std::wstring guidString(len, 0);
	for (int i = 0; i < len; ++i)
		guidString[i] = static_cast<wchar_t>(str[i]);
	return guidString;
}

TemporaryFile::TemporaryFile(const std::wstring &extension)
{
	std::wstring tmpPath = getTempPath();
	m_fileName = tmpPath + generateGuid() + L"." + extension;
}

TemporaryFile::~TemporaryFile()
{
	_wremove(m_fileName.data());
}

std::wstring TemporaryFile::fileName() const
{
	return m_fileName;
}

void TemporaryFile::write(const char *data, size_t size)
{
	FILE *file = NULL;
	errno_t status = _wfopen_s(&file, m_fileName.data(), L"w");
	if (status)
		return;
	fwrite(data, sizeof(data), size, file);
	fclose(file);
}

size_t TemporaryFile::read(char *data, size_t maxSize)
{
	FILE *file = NULL;
	errno_t status = _wfopen_s(&file, m_fileName.data(), L"w");
	if (status)
		return -1;
	size_t size = fread(data, sizeof(data), maxSize, file);
	fclose(file);
	return size;
}

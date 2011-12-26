#ifndef TEMPORARYFILE_H
#define TEMPORARYFILE_H
#include <string>
#include <fstream>

class TemporaryFile
{
public:
	TemporaryFile(const std::wstring &extension = L"ico");
	~TemporaryFile();
	std::wstring fileName() const;
	void write(const char *data, size_t size);
	size_t read(char *data, size_t maxSize);

private:
	std::wstring m_fileName;
};

#endif // TEMPORARYFILE_H

#include "system/File.h"
#include "core/Exception.h"
#include <stdio.h>

using namespace nb::System;

File::File(const String &path)
: m_pFileHandle(NULL)
, m_FilePath(path)
{

}
//never use this
File::File(const File &other)
: m_pFileHandle(NULL)
{

}
//never use this
void File::operator = (const File &other)
{

}

File::~File()
{
	Close();
}

void File::Open(OpenMode op, AccessMode ass)
{
	std::string s = m_FilePath.ToUtf8().GetData();
	m_pFileHandle = fopen(s.data(), "rt");
}

void File::Close()
{
	if(m_pFileHandle)
		fclose(m_pFileHandle);
}

bool File::IsOpened() const
{
	return m_pFileHandle != NULL;
}

File::OpenMode File::GetOpenMode() const
{
	return m_OpenMode;
}

File::AccessMode File::GetAccessMode() const
{
	return m_AccessMode;
}

UInt64 File::GetLenght() const
{
	return GetSize();
}

UInt64 File::GetSize() const
{
	if(!m_pFileHandle) return 0;
	UInt64 currentPos = ftell(m_pFileHandle);
	fseek(m_pFileHandle, SEEK_SET, SEEK_END);
	int ret = ftell(m_pFileHandle);
	fseek(m_pFileHandle, currentPos, SEEK_SET);
	return ret;
}

UInt64 File::GetLines() const
{
	return 0;
}

Stream File::ReadBytes(UInt64 nBeg, UInt64 nCount) const
{
	return Stream();
}

Stream File::ReadLine(UInt64 nLineIndex) const
{
	return Stream();
}

Stream File::ReadAll() const
{
	if(m_pFileHandle == NULL)
		return Stream();
	//此处有bug，bytearry大小最大为4G多，而文件
	int fileSize = (int)GetSize();
	Stream ba(fileSize);
	fread((void *)ba.GetData(), 1, fileSize, m_pFileHandle);
	return ba;
}

void File::WriteBytes(UInt64 nIndex, char *pData, UInt64 nSize)
{

}

void File::WriteBytes(UInt64 nIndex, Stream ba)
{

}

void File::PrependBytes(UInt64 nIndex, char *pData, UInt64 nSize)
{

}

void File::PrependBytes(UInt64 nIndex, Stream ba)
{

}

void File::AppendBytes(UInt64 nIndex, char *pData, UInt64 nSize)
{

}

void File::AppendBytes(UInt64 nIndex, Stream ba)
{

}

void File::WriteLine(int nLineIndex, char *pData, UInt64 nSize)
{

}

void File::WriteLine(int nLineIndex, Stream ba)
{

}

bool File::IsExists(const String &path)
{
	return false;
}

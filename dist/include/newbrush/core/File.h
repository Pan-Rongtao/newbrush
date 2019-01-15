/*******************************************************
**
**	File
**	
**		文件类
**			提供单个文件的操作
**				可以以不同的打开模式和权限模式打开文件
**				并对文件进行读写操作。									该类未完成，请勿使用！！
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "String.h"
#include "Stream.h"

namespace nb{ namespace core {

class NB_API File
{
public:
	//定义文件打开的模式
	enum OpenMode
	{
		OpenExistsOnly =			0x00000001,						//打开现有的文件；如果不存在，将抛出file not found异常（此模式的前提是需要操作系统中文件的读权限）
		CreateNewOnly =				0x00000002,						//创建新的文件；如果文件已经存在，将产生异常。（此模式的前提是需要操作系统中文件的写权限）
		OpenOrCreate =				0x00000004,						//如果不存在建立新的文件（此模式的前提是需要操作系统中文件的读写权限）
		CreateForceCover =			0x00000008,						//无论文件是否存在，都创建一个新的，需要操作系统的写权限，否则抛出系统权限不足的异常
		Append =					0x00000010,						//追加模式，即打开后指向文件尾部
	};
	//权限模式
	enum AccessMode
	{
		Read =						0x00000001,						//只读模式（此模式的前提是需要操作系统中文件的读权限）
		Write =						0x00000002,						//只写模式（此模式的前提是需要操作系统中文件的写权限）
		ReadWrite =					0x00000003,						//读写模式（此模式的前提是需要操作系统中文件的读写权限）
	};

public:
	//打开一个路径为path的文件，打开模式为op，访问模式为ass
	//异常1：无效的path，未找到文件
	//异常2：无效的op或者ass，越界
	//异常3：指定的ass权限不能够被满足，一般由于操作系统
	//异常4：系统级不能满足调用者所需的权限
	void Open(OpenMode op, AccessMode ass);

	//关闭
	void Close();

	//是否已经打开
	bool IsOpened() const;

	//获取打开模式，如果文件未打开，将抛出异常
	OpenMode GetOpenMode() const;

	//获取权限模式，如果文件未打开，将抛出异常
	AccessMode GetAccessMode() const;

	//获取文件总字节数，如果文件未打开，将抛出异常
	uint64_t GetLenght() const;
	uint64_t GetSize() const;

	//获取行数，如果文件未打开，将抛出异常
	uint64_t GetLines() const;

	//读取以nBeg开始的nCount个字节，实际读到的字节数以返回的Stream的长度为准，如果文件未打开，将抛出异常
	Stream ReadBytes(uint64_t nBeg, uint64_t nCount) const;

	//读取第nLineIndex行的数据，如果文件未打开，将抛出异常
	Stream ReadLine(uint64_t nLineIndex) const;
	//ReadLines();

	//读取所有的数据，如果文件未打开，将抛出异常
	Stream ReadAll() const;

	//在nIndex处写入数据，如果文件未打开，将抛出异常
	void WriteBytes(uint64_t nIndex, char *pData, uint64_t nSize);
	void WriteBytes(uint64_t nIndex, Stream ba);

	//在文件头部插入数据，如果文件未打开，将抛出异常
	void PrependBytes(uint64_t nIndex, char *pData, uint64_t nSize);
	void PrependBytes(uint64_t nIndex, Stream ba);

	//在文件尾部插入数据，如果文件未打开，将抛出异常
	void AppendBytes(uint64_t nIndex, char *pData, uint64_t nSize);
	void AppendBytes(uint64_t nIndex, Stream ba);

	//写入一行，会在需要写入的数据加上一个换行标志，如果文件未打开，将抛出异常
	void WriteLine(int nLineIndex, char *pData, uint64_t nSize);
	void WriteLine(int nLineIndex, Stream ba);

//Constructors & operators override.
public:
	//构建一个路径为path的File对象
	//File(const char *path);
	File(const String &path);
	~File();

public:
	static bool IsExists(const String &path);


private:
	File(const File &other);
	void operator = (const File &other);


	FILE				*m_pFileHandle;
	OpenMode			m_OpenMode;
	AccessMode			m_AccessMode;
	nb::core::String	m_FilePath;
};
	
}}

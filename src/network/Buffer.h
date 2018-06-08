/*******************************************************
**	Buffer
**
**	内存块
**	
**	该类是
**	它将用于定制数据流的传输
**
**		
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Packet.h"

namespace nb{ namespace Network{

class NB_EXPORT Buffer
{
public:
	//获取数据头部
	char *GetData();
	const char *GetData() const;

	//获取数据字节数
	int GetSize() const;

public:
	//构建一个Buffer， 该Buffer为空，长度为0
	Buffer();

	//构建一个Buffer，长度为nLenBytes
	Buffer(unsigned int nLenBytes);

	//构建一个Buffer，长度为nLenBytes，并从pData开始拷贝数据以填充内存
	Buffer(const char *pData, unsigned int nLenBytes);

	//从其它Buffer构建一个Buffer
	Buffer(const Buffer &other);

	~Buffer();

public:
	void operator = (const Buffer &other);

private:
	char			*m_pData;
	int				m_nLen;
};

class BufferDecoder
{
public:
	//构建一个Buffer解码器，它将对buffer进行解码
	BufferDecoder(Buffer buffer);

	//解码并获取包头
	Header GetHeader() const;

	//解码并获取包体数据
	const char *GetBodyData() const;


private:
	Buffer	m_buffer;
};

}}
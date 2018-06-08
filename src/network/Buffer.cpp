#include "Buffer.h"
#include "Packet.h"

using nb::Network::Buffer;
using nb::Network::BufferDecoder;
using nb::Network::Header;

Buffer::Buffer()
: m_pData(NULL)
, m_nLen(0)
{
}

Buffer::Buffer(unsigned int nLenBytes)
: m_nLen(nLenBytes)
{
	m_pData = new char[nLenBytes];
}

Buffer::Buffer(const char *pData, unsigned int nLenBytes)
: m_pData(NULL)
, m_nLen(nLenBytes)
{
	if(pData != NULL)
	{
		m_pData = new char[nLenBytes];
		memcpy(m_pData, pData, nLenBytes);
	}
}

Buffer::Buffer(const Buffer &other)
: m_pData(NULL)
{
	m_nLen = other.GetSize();
	if(other.m_pData != NULL)
	{
		delete [] m_pData;
		m_pData = new char[m_nLen];
		memcpy(m_pData, other.GetData(), GetSize());
	}
}

void Buffer::operator = (const Buffer &other)
{
	delete [] m_pData;
	m_pData = NULL;
	m_nLen = other.GetSize();
	if(other.m_pData != NULL)
	{
		m_pData = new char[m_nLen];
		memcpy(m_pData, other.GetData(), GetSize());
	}
}

Buffer::~Buffer()
{
	delete [] m_pData;
	m_pData = NULL;
}

char *Buffer::GetData()
{
	return m_pData;
}

const char *Buffer::GetData() const
{
	return m_pData;
}

int Buffer::GetSize() const
{
	return m_nLen;
}
///////////////

BufferDecoder::BufferDecoder(Buffer buffer)
: m_buffer(buffer)
{
}

Header BufferDecoder::GetHeader() const
{
	Header header;
	memcpy(header.GetData(), m_buffer.GetData(), Header::Size());
	return header;
}

const char *BufferDecoder::GetBodyData() const
{
	return m_buffer.GetData() + Header::Size();
}
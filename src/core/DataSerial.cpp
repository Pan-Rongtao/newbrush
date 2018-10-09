#include "core/DataSerial.h"
#include "core/Object.h"
#include "core/Exception.h"
#include <stdio.h>
#include <string.h>

DataSerial::DataSerial(void)
	: m_pBuffer(NULL)
	, m_nMaxBufferSize(1024*10)
	, m_nUseBufferSize(0)
	, m_pCurr(NULL)
	, m_pCurrRead(NULL)
	, m_bUseExternData(false)
{
}

DataSerial::DataSerial(int beginBufferSize)
	: m_pBuffer(NULL)
	, m_nMaxBufferSize(beginBufferSize)
	, m_nUseBufferSize(0)
	, m_pCurr(NULL)
	, m_pCurrRead(NULL)
	, m_bUseExternData(false)
{
}

DataSerial::~DataSerial(void)
{
	if(!m_bUseExternData) delete [] m_pBuffer;
}

void DataSerial::AssureBuffer()
{
	if(m_pBuffer != NULL) return;
	m_pBuffer = new unsigned char[m_nMaxBufferSize];

	m_pCurr = m_pBuffer;
	m_pCurrRead = m_pBuffer;
}

void DataSerial::ClearData()
{
	if(m_pBuffer == NULL) return;
	m_pCurr = m_pBuffer;
	m_pCurrRead = m_pCurr;
}

DataSerial & DataSerial::Put(const unsigned char *pData, long nLen)
{
	if(pData == NULL) nLen = 0;

	TestBuffer(nLen + sizeof(nLen));
	AssureBuffer();

	if(pData == NULL || nLen == 0)
	{
		*this << 0l;
		return *this;
	}

	*this << nLen;
	memcpy(m_pCurr, pData, nLen);
	m_pCurr += nLen;

	return *this;
}

DataSerial & DataSerial::Write(const unsigned char *pData, long nLen)
{
	TestBuffer(nLen);
	AssureBuffer();

	memcpy(m_pCurr, pData, nLen);
	m_pCurr += nLen;

	return *this;
}

DataSerial & DataSerial::operator << (const wchar_t *pstr)
{
	if(pstr == NULL)
	{
		*this << 0l;
		return *this;
	}

	long nLen = wcslen(pstr);
	if(nLen == 0)
	{
		*this << nLen;
		return *this;
	}

	int nDataLen = sizeof(wchar_t)*nLen;

	TestBuffer(nDataLen + sizeof(nLen));
	AssureBuffer();

	*this << nLen;
	memcpy(m_pCurr, pstr, nDataLen);
	m_pCurr += nDataLen;

	return *this;
}

DataSerial & DataSerial::operator << (const char *pstr)
{
	if(pstr == NULL)
	{
		*this << 0l;
		return *this;
	}

	long nLen = strlen(pstr);
	if(nLen == 0)
	{
		*this << nLen;
		return *this;
	}

	int nDataLen = sizeof(char)*nLen;

	TestBuffer(nDataLen + sizeof(nLen));
	AssureBuffer();

	*this << nLen;
	memcpy(m_pCurr, pstr, nDataLen);
	m_pCurr += nDataLen;

	return *this;
}

DataSerial & DataSerial::Get(unsigned char *pData, long &nLen)
{
	if(m_pCurrRead + sizeof(long) > m_pCurr)
	{
		m_pCurrRead = m_pCurr;
		return *this;
	}

	long nl = 0;

	*this >> nl;

	if(nl > 0)
	{
		if(m_pCurrRead + nl > m_pCurr)
		{
			m_pCurrRead = m_pCurr;
			return *this;
		}

		memcpy(pData, m_pCurrRead, nl);
		m_pCurrRead += nl;
	}
	else
	{
		// 数据长度为零
	}

	nLen = nl;
	return *this;
}

DataSerial & DataSerial::Read(unsigned char *pData, long nLen)
{
//	if(m_pCurrRead + nLen > m_pCurr)
//	{
//		m_pCurrRead = m_pCurr;
//		return *this;
//	}

	LoadTest(nLen);

	memcpy(pData, m_pCurrRead, nLen);
	m_pCurrRead += nLen;

	return *this;
}

DataSerial & DataSerial::operator >> (std::wstring &str)
{
	if(m_pCurrRead + sizeof(long) > m_pCurr)
	{
		m_pCurrRead = m_pCurr;
		return *this;
	}

	long nLen;
	*this >> nLen;
	if(nLen == 0)
	{
		str = L"";
		return *this;
	}

	int nDataLen = sizeof(wchar_t)*nLen;
	if(m_pCurrRead + nDataLen > m_pCurr)
	{
		m_pCurrRead = m_pCurr;
		return *this;
	}

	wchar_t *pdata = new wchar_t[nLen+1];

	memcpy(pdata, m_pCurrRead, nDataLen);
	pdata[nLen] = L'\0';
	m_pCurrRead += nDataLen;

	str = pdata;
	delete [] pdata;

	return *this;
}

DataSerial & DataSerial::operator >> (std::string &str)
{
	if(m_pCurrRead + sizeof(long) > m_pCurr)
	{
		m_pCurrRead = m_pCurr;
		return *this;
	}

	long nLen;
	*this >> nLen;
	if(nLen == 0)
	{
		str = "";
		return *this;
	}

	int nDataLen = sizeof(char)*nLen;
	if(m_pCurrRead + nDataLen > m_pCurr)
	{
		m_pCurrRead = m_pCurr;
		return *this;
	}

	char *pdata = new char[nLen+1];

	memcpy(pdata, m_pCurrRead, nDataLen);
	pdata[nLen] = '\0';
	m_pCurrRead += nDataLen;

	str = pdata;
	delete [] pdata;

	return *this;
}

long DataSerial::GetDataSize() const
{
	if(m_pBuffer == NULL) return 0;

	return m_pCurr - m_pBuffer;
}

bool DataSerial::IsPosEnd() const
{
	return m_pCurrRead >= m_pCurr;
}

const unsigned char *DataSerial::GetBuffer() const
{
	return m_pBuffer;
}

void DataSerial::UseExternData(unsigned char *pData, long nLen)
{
	if(!m_bUseExternData)
	{
		delete [] m_pBuffer;
	}

	m_pBuffer = pData;

	m_pCurr = m_pBuffer;
	m_pCurrRead = m_pBuffer;

	m_pCurr += nLen;

	m_bUseExternData = true;

	m_nMaxBufferSize = GetDataSize();	// 此处m_nMaxBufferSize将不一定为1024*10的倍数了
}

void DataSerial::TestBuffer(long nAddSize)
{
	long nDataSize = GetDataSize();

	long nNewSize = nDataSize + nAddSize;
	if(nNewSize > m_nMaxBufferSize)
	{
	//	m_nMaxBufferSize = ((nNewSize + 1024*10-1) / (1024*10)) * (1024*10);
		do {
			m_nMaxBufferSize *= 1.5;
		} while (nNewSize > m_nMaxBufferSize);

		if(m_pBuffer == NULL) return;

		long nReadOffset = m_pCurrRead - m_pBuffer;

		unsigned char *pOld = m_pBuffer;
		m_pBuffer = new unsigned char[m_nMaxBufferSize];
		memcpy(m_pBuffer, pOld, nDataSize);
		delete [] pOld;

		m_pCurr = m_pBuffer + nDataSize;
		m_pCurrRead = m_pBuffer + nReadOffset;
	}
}

void DataSerial::LoadTest(int len) const
{
	if(m_pCurrRead + len > m_pCurr)
	{
		NB_THROW_EXCEPTION("读取越界");
	}
}

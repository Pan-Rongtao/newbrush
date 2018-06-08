#pragma once

#include "../../../Include/Gui/ClientServer.h"

class FarCallTest
{
public:
	FarCallTest(void);
	virtual ~FarCallTest(void);
};

class xxClientObject;
class xxServerObject;

class xxClientObject : public nb::System::FarCallClient
{
public:
	xxClientObject() : m_pReturnResultData(NULL) {}
	~xxClientObject()
	{
		if(m_pReturnResultData != NULL) delete [] m_pReturnResultData;
	}
	virtual void SendDataOverride(nb::System::FarCallSerial &dataSerial, nb::System::FarCallSerial &resultSerial);
	void OnAcceptServerReturnResult(const unsigned char *pData, int len);

	xxServerObject *m_server;

	unsigned char *m_pReturnResultData;
	int m_nReturnResultDataLen;
};


class xxServerObject : public nb::System::FarCallServer
{
public:
//	virtual void SendReturnResultOverride(FarCallSerial &dataSerial);

	xxClientObject *m_client;

	void OnAcceptData(const unsigned char *pData, int len);
};


class DataCell
{
};

class DataNode
{
public:
	void InitFar();
	virtual DataNode * GetParent() const {return NULL;}
};

template<class T>
class ValueDataNode : public DataNode
{
public:
	operator T () const
	{
	}

	void operator = (const T &v)
	{
	}
};

class MediaID3Data : public DataNode
{
	std::string m_sArtist;
	std::string m_sName;

	class TestNode : public ValueDataNode<int>
	{
	}
	m_nTest;
};

class MediaData : public DataNode
{
	MediaID3Data m_ID3;

public:
	class TestNode : public ValueDataNode<int>
	{
	public:
		virtual DataNode * GetParent() const
		{
			const MediaData *pNull = NULL;
			unsigned long long offset = (unsigned long long)&pNull->m_nTest;
			unsigned long long parentValue = ((unsigned long long)this) - offset;
			return (MediaData *)parentValue;
		}
	}
	m_nTest;
};

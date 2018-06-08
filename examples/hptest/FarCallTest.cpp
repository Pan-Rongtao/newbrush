#include "FarCallTest.h"

using namespace nb::System;

FarCallTest::FarCallTest(void)
{
}

FarCallTest::~FarCallTest(void)
{
}

void xxClientObject::SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial)
{
	const unsigned char *pData = dataSerial.GetBuffer();
	int dataLen = dataSerial.GetDataSize();

	m_server->OnAcceptData(pData, dataLen);

	resultSerial.UseExternData(m_pReturnResultData, m_nReturnResultDataLen);
}

void xxClientObject::OnAcceptServerReturnResult(const unsigned char *pData, int len)
{
	if(m_pReturnResultData != NULL) delete [] m_pReturnResultData;

	m_nReturnResultDataLen = len;
	m_pReturnResultData = new unsigned char[len];
	memcpy(m_pReturnResultData, pData, len);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//void xxServerObject::SendReturnResultOverride(FarCallSerial &dataSerial)
//{
//	const unsigned char *pData = dataSerial.GetBuffer();
//	int dataLen = dataSerial.GetDataSize();
//
//	m_client->OnAcceptServerReturnResult(pData, dataLen);
//}

void xxServerObject::OnAcceptData(const unsigned char *pData, int len)
{
	FarCallSerial dataSerial(FarCallSerial::Mode_Storing);
	AcceptData(pData, len, dataSerial);


	const unsigned char *pResultData = dataSerial.GetBuffer();
	int resultDataLen = dataSerial.GetDataSize();
	m_client->OnAcceptServerReturnResult(pResultData, resultDataLen);
}

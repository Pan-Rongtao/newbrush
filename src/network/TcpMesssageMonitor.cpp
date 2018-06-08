#include "TcpMesssageMonitor.h"
#include "Buffer.h"
#include "core/Exception.h"

using nb::Network::TcpMessageMonitor;
using nb::Network::Socket;
using nb::Network::TcpMessageMonitorEvent;

TcpMessageMonitor::TcpMessageMonitor()
: m_bStopFlag(true)
, m_pEventInterface(NULL)
{
	
}

TcpMessageMonitor::~TcpMessageMonitor()
{

}

void TcpMessageMonitor::SetSocket(Socket *socket)
{
	m_pSocket = socket;
}

void TcpMessageMonitor::Start()
{
	m_bStopFlag = false;
	Thread::Start();
}

void TcpMessageMonitor::Stop()
{
	m_bStopFlag = true;
}

void TcpMessageMonitor::SetEventInterface(TcpMessageMonitorEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpMessageMonitor::Run()
{
	try{
		while(true)
		{
			Buffer bufferHead(Header::Size());
			int nHead = m_pSocket->RecvData(bufferHead.GetData(), bufferHead.GetSize());
			if(nHead <= 0)
			{
//				printf("recv head error: size < 0\r\n");
				m_pEventInterface->TcpMessageMonitor_OnErrorPacket();
			}
			else
			{
				BufferDecoder decoder(bufferHead);
				unsigned int id = decoder.GetHeader().GetID();
				Header::ActionProperty ap = decoder.GetHeader().GetActionProperty();
				Header::MessageType msgType = decoder.GetHeader().GetMessageType();
				Header::Priority priority = decoder.GetHeader().GetPriority();
				unsigned int nBodySize = decoder.GetHeader().GetBodySize();
				if(nBodySize >= Packet::MaxSize())
					printf("warning! packet is too large size[%d] bytes.\r\n", nBodySize);

				Header head(id, ap, msgType, priority, nBodySize);
				Packet pkg(head, NULL);
				//接收余下报文
				if(nBodySize > 0)
				{
					int nRemain = nBodySize;
					Buffer bufferBody(nBodySize);
					while(nRemain > 0)
					{
						char *pCurrent = bufferBody.GetData() + (nBodySize - nRemain);
						int nGet = m_pSocket->RecvData(pCurrent, nRemain);
						nRemain -= nGet;
					}
					//填充packet的body数据
					pkg.FillBodyData(bufferBody.GetData());
				}
				//根据包类型和消息类型动作
				if((ap > Header::Property_Unknow && ap < Header::Property_Max) && (msgType > Header::Message_Unknow && msgType < Header::Message_Signal_Max))
				{
					m_pEventInterface->TcpMessageMonitor_OnPacketArrived(pkg);
				}
				else
				{
					printf("[%d]unhandle data, maybe remote hang up. id[%d], ap[%d], msgType[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), id, ap, msgType);
					m_pEventInterface->TcpMessageMonitor_OnErrorPacket();
				}
			}

			if(m_bStopFlag)
				break;
		}
	}
	catch(nb::Core::ExceptionPtr ex)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("exception: %s\r\n", ex->GetErrorMessageData());
		printf("file: %s\r\n", ex->GetFileNameData());
		printf("line: %d\r\n\r\n", ex->GetFileLine());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
}

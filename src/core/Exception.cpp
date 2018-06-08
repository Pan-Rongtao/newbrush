#include "core/Exception.h"
#include "core/Type.h"

#include "core/DependencyProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

namespace nb { namespace Core {

class ExceptionInternal
{
public:
	std::string m_sMessage;
	int m_fileLine;
	std::string m_fileName;

};

}}


Exception::Exception(void)
{
	m_internal = new ExceptionInternal();
	m_internal->m_fileLine = -1;
}

Exception::Exception(const char *pMessage)
{
	m_internal = new ExceptionInternal();
	m_internal->m_fileLine = -1;
	if(pMessage != NULL) m_internal->m_sMessage = pMessage;
}

Exception::Exception(const std::string &sMessage)
{
	m_internal = new ExceptionInternal();
	m_internal->m_fileLine = -1;
	m_internal->m_sMessage = sMessage;
}

Exception::Exception(const char *pMessage, const char *fileName, int fileRow)
{
	m_internal = new ExceptionInternal();
	m_internal->m_fileLine = fileRow;
	if(pMessage != NULL) m_internal->m_sMessage = pMessage;
	if(fileName != NULL) m_internal->m_fileName = fileName;
}

Exception::~Exception(void)
{
	delete m_internal;
}

const char * Exception::GetErrorMessageData() const
{
	return m_internal->m_sMessage.data();
}

int Exception::GetFileLine() const
{
	return m_internal->m_fileLine;
}

const char * Exception::GetFileNameData() const
{
	return m_internal->m_fileName.data();
}

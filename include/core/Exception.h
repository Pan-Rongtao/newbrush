#pragma once

#include "Object.h"
#include "DependencyProperty.h"


namespace nb { namespace Core {

class ExceptionInternal;
class NB_CORE_DECLSPEC_X_INTERFACE Exception : public nb::Core::RefObject
{
public:

	Exception(void);
	Exception(const char *pMessage);
	Exception(const char *pMessage, const char *fileName, int fileLine);
	Exception(const std::string &sMessage);

	virtual ~Exception(void);

	static DependencyPropertyPtr m_TestProperty;
	
	const char * GetErrorMessageData() const;
	int GetFileLine() const;
	const char * GetFileNameData() const;

private:
	ExceptionInternal *m_internal;
//	static void *s_pPrepareType;
};

class ExceptionPtr : public nbObjectPtrDerive<Exception, RefObjectPtr>
{
public:
	ExceptionPtr(){}
	ExceptionPtr(Exception *p) : nbObjectPtrDerive(p) {}

	static ExceptionPtr GetPtrInstance(const char *pMessage) {return ExceptionPtr(new Exception(pMessage));}
	static ExceptionPtr GetPtrInstance(const char *pMessage, const char *fileName, int fileLine) {return ExceptionPtr(new Exception(pMessage, fileName, fileLine));}
	static ExceptionPtr GetPtrInstance(const std::string &sMessage) {return ExceptionPtr(new Exception(sMessage));}
};

}}

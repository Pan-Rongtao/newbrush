#include "InternalCore.h"
#include "TypePrivate.h"
#include "PropertyInternal.h"

using namespace nb::core;
bool nbInternalCore::m_bConstructerEnsure = false;

nbInternalCore::nbInternalCore(void)
	: m_pTypeInternal(NULL)
	, m_pDependencyPropertyInternal(NULL)
{
	m_csRefPtr = new ObjectLiveMonitor::CriticalSection();
}

nbInternalCore::~nbInternalCore(void)
{
	delete m_pTypeInternal;
	delete m_pDependencyPropertyInternal;
	delete m_csRefPtr; //这个需要在delete m_pTypeInternal之后
}

TypeInternal * nbInternalCore::GetTypeInternal()
{
	if(GetInstance()->m_pTypeInternal == NULL)
	{
		GetInstance()->m_pTypeInternal = new TypeInternal();
	}
	return GetInstance()->m_pTypeInternal;
}

DependencyPropertyInternal * nbInternalCore::GetDependencyPropertyInteranl()
{
	if(GetInstance()->m_pDependencyPropertyInternal == NULL)
	{
		GetInstance()->m_pDependencyPropertyInternal = new DependencyPropertyInternal();
	}
	return GetInstance()->m_pDependencyPropertyInternal;
}

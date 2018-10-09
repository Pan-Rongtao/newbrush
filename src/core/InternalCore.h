#pragma once
#include "ObjectLiveMonitor.h"

namespace nb { namespace core {

class TypeInternal;
class DependencyPropertyInternal;

class nbInternalCore
{
public:
	nbInternalCore(void);
	virtual ~nbInternalCore(void);

	static nbInternalCore * GetInstance()
	{
		static nbInternalCore xx;
		return &xx;
	}

	static ObjectLiveMonitor * GetObjectLiveMonitor(){return &GetInstance()->m_ObjectLiveMonitor;}
//	static nbCoreApplication * GetApplication();
	static TypeInternal * GetTypeInternal();
	static DependencyPropertyInternal * GetDependencyPropertyInteranl();

	static ObjectLiveMonitor::CriticalSection * GetRefPtrCriticalSection() {return GetInstance()->m_csRefPtr;}

	static inline void ConstructerEnsure()
	{
		if(m_bConstructerEnsure) return;
		m_bConstructerEnsure = true;
		GetInstance();
	}

private:
	ObjectLiveMonitor m_ObjectLiveMonitor;
//	nbCoreApplication *m_pApplication;
	TypeInternal *m_pTypeInternal;
	DependencyPropertyInternal *m_pDependencyPropertyInternal;

	ObjectLiveMonitor::CriticalSection *m_csRefPtr;

	static bool m_bConstructerEnsure;
};

}}
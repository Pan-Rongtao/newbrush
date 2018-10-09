#include <stdlib.h>
#include "ObjectLiveMonitor.h"
#include "malloc.h" 

using namespace nb::core;

ObjectLiveMonitor::CriticalSection::CriticalSection()
{
#ifdef WIN32
	InitializeCriticalSection(&m_section);
#else
	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_mutex, &mattr);
	pthread_mutexattr_destroy(&mattr);
#endif
}

ObjectLiveMonitor::CriticalSection::~CriticalSection()
{
#ifdef WIN32
	DeleteCriticalSection(&m_section);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

void ObjectLiveMonitor::CriticalSection::Lock()
{
#ifdef WIN32
	EnterCriticalSection(&m_section);
#else
	pthread_mutex_lock(&m_mutex);
#endif
}

void ObjectLiveMonitor::CriticalSection::Unlock()
{
#ifdef WIN32
	LeaveCriticalSection(&m_section);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}

ObjectLiveMonitor::ObjectLiveMonitor(void)
	: m_nWaitConstructCount(0)
{
	WatiConstructInfo *p = m_WaitConstructInfo;
	WatiConstructInfo *pEnd = m_WaitConstructInfo + WAIT_CONSTRUCT_MAX;
	for(; p < pEnd; p++) p->m_p = NULL;
}

ObjectLiveMonitor::~ObjectLiveMonitor(void)
{
	if(!m_mapMoneyBlock.empty())
	{
		std::map<long long, BlockInfo *> map;

		std::map<void *, BlockInfo>::iterator itor = m_mapMoneyBlock.begin();
		for(; itor != m_mapMoneyBlock.end(); itor++)
		{
			map[itor->second.m_serial] = &itor->second;
		}
	}
}

void * ObjectLiveMonitor::Malloc(size_t t, bool bSaveHeapConstructPermit, const char * lpszFileName, int nLine)
{
	static long long serial = 0;
	serial++;

	m_cs.Lock();
	void *p = malloc(t);

	m_mapMoneyBlock[p] = BlockInfo(lpszFileName, nLine, serial);

	if(bSaveHeapConstructPermit)
	{
		WatiConstructInfo * pWait = m_WaitConstructInfo;
		WatiConstructInfo * pWaitEnd = pWait + WAIT_CONSTRUCT_MAX;
		for(; pWait < pWaitEnd; pWait++)
		{
			if(pWait->m_p == NULL)
			{
				pWait->m_p = p;
				pWait->m_len = t;
				m_nWaitConstructCount++;
				break;
			}
		}
		if(pWait == pWaitEnd)
		{
			//溢出了
			printf("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
			printf("[New Brush] Error!!\r\n");
			printf("[New Brush] The temporary pool overflowed while malloc memory.\r\n");
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
			exit(1);
		}
	}

	m_cs.Unlock();

	return p;
}

void ObjectLiveMonitor::Free(void *p)
{
	m_cs.Lock();
	m_mapMoneyBlock.erase(p);
	free(p);
	m_cs.Unlock();
}


bool ObjectLiveMonitor::ObjectHeapConstructPermit(void *pObject)
{
	if(m_nWaitConstructCount <= 0) return false;

	m_cs.Lock();

	WatiConstructInfo *pWait = m_WaitConstructInfo;
	WatiConstructInfo *pWaitEnd = m_WaitConstructInfo + WAIT_CONSTRUCT_MAX;
	for(; pWait < pWaitEnd; pWait++)
	{
		if(pObject == pWait->m_p || (pObject > pWait->m_p  && pObject < ((unsigned char *)pWait->m_p) + pWait->m_len))
		{
			pWait->m_p = NULL;
			m_nWaitConstructCount--;
			m_cs.Unlock();
			return true;
		}
	}

	m_cs.Unlock();
	return false;
}

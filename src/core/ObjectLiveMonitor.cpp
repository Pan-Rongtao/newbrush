#include <stdlib.h>
#include "ObjectLiveMonitor.h"
#include "malloc.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using nb::Core::ObjectLiveMonitor;

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
//	void **p = m_WaitConstruct;
//	void **pEnd = m_WaitConstruct + WAIT_CONSTRUCT_MAX;
//	for(; p < pEnd; p++) *p = NULL;


	{
		WatiConstructInfo *p = m_WaitConstructInfo;
		WatiConstructInfo *pEnd = m_WaitConstructInfo + WAIT_CONSTRUCT_MAX;
		for(; p < pEnd; p++) p->m_p = NULL;
	}

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

	//	NB_OUTA("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	//	NB_OUTA("The following NewBrush objects needs to be delete");

	/*	int i = 0;
		for(; itor != m_mapMoneyBlock.end() && i < 10; itor++, i++)
		{
			char c[1024];
			::NB_SNPRINTF(c, 1023, "0x%08x, Serial: %I64d, Line: %04d, File: %s", itor->first, itor->second.m_serial, itor->second.m_line, itor->second.m_fileName);
			NB_OUTA(c);
		}

		if(i == 10 && itor != m_mapMoneyBlock.end())
		{
			char c[100];
			::NB_SNPRINTF(c, 99, "Omit more(Total: %d)", m_mapMoneyBlock.size());
			NB_OUTA(c);
		}*/
		/*
		std::map<long long, BlockInfo *>::iterator itorx = map.begin();

		int i = 0;
		for(; itorx != map.end() && i < 20; itorx++, i++)
		{
			char c[1024];
			::NB_SNPRINTF(c, 1023, "[%I64d]  Line: %04d, File: %s", itorx->second->m_serial, itorx->second->m_line, itorx->second->m_fileName);
			NB_OUTA(c);
		}

		if(i == 20 && itorx != map.end())
		{
			char c[100];
			::NB_SNPRINTF(c, 99, "Omit more(Total: %d)", map.size());
			NB_OUTA(c);
		}

		NB_OUTA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		*/
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
			NB_OUTA("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			NB_OUTA("[New Brush] Error!!");
			NB_OUTA("[New Brush] The temporary pool overflowed while malloc memory.");
			NB_OUTA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
			exit(1);
		}
	}

	m_cs.Unlock();

//	m_setMoneyBlock.insert(NULL);
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

/*	void **pWait = m_WaitConstruct;
	void **pWaitEnd = m_WaitConstruct + WAIT_CONSTRUCT_MAX;
	for(; pWait < pWaitEnd; pWait++)
	{
		if(*pWait == pObject)
		{
			testOut1++;

			*pWait = NULL;
			m_nWaitConstructCount--;
			m_cs.Unlock();
			return true;
		}
	}*/

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

//#include <fstream>
void ObjectLiveMonitor::Test()
{
/*	static int k = GetTickCount();

	if(GetTickCount() - k > 300)
	{
		std::fstream f;
		f.open("d:\\a\\aa.txt", std::ios_base::app);
		char c[1024];
		sprintf(c, "%d,   %d, %d, %d\r\n", m_nWaitConstructCount, testIn, testOut, testOut1);
		f.seekg(0, std::ios::end);
		f << c;
		k = GetTickCount();
	}*/
}
#pragma once
#include <set>
#include <map>
#include <list>

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace nb { namespace core {

class ObjectLiveMonitor
{
public:
	class CriticalSection
	{
	public:
		CriticalSection();
		virtual ~CriticalSection();

		void Lock();
		void Unlock();

	private:

#ifdef WIN32
		CRITICAL_SECTION m_section;
#else
		pthread_mutex_t m_mutex;
#endif
	};

public:
	ObjectLiveMonitor(void);
	virtual ~ObjectLiveMonitor(void);

	void * Malloc(size_t t, bool bSaveHeapConstructPermit, const char * lpszFileName, int nLine);
	void Free(void *p);

	bool ObjectHeapConstructPermit(void *pObject);

	void Test();

private:
	struct BlockInfo
	{
		BlockInfo() : m_fileName(NULL), m_line(0), m_serial(0) {}
		BlockInfo(const char * lpszFileName, int nLine, long long serial) : m_fileName(lpszFileName), m_line(nLine), m_serial(serial) { }
		const char *m_fileName;
		int m_line;
		long long m_serial;
	};

private:
	std::map<void *, BlockInfo> m_mapMoneyBlock;

	CriticalSection m_cs;

	struct WatiConstructInfo
	{
		void * m_p;
		size_t m_len;
	};

	enum {WAIT_CONSTRUCT_MAX = 1024};
//	void * m_WaitConstruct[WAIT_CONSTRUCT_MAX];
	WatiConstructInfo m_WaitConstructInfo[WAIT_CONSTRUCT_MAX];
	int m_nWaitConstructCount;
};

}}

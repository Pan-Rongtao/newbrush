#pragma once

#include <map>
#include "system/Timer.h"

namespace nb { namespace System 
{
class TimerPrivate
{
public:
	class AllowNullIterator
	{
	public:
		AllowNullIterator(const std::multimap<unsigned long long, Timer *>::iterator &itor)
			: m_itor(itor)
			, m_bNull(false)
		{}

		AllowNullIterator() : m_bNull(true){}

		const std::multimap<unsigned long long, Timer *>::iterator &GetIterator() const
		{
			return m_itor;
		}

		bool IsNull() const
		{
			return m_bNull;
		}

		void SetNull() {m_bNull = true;}
		void SetIterator(const std::multimap<unsigned long long, Timer *>::iterator &itor) { m_itor = itor; m_bNull = false;}

		void operator ++() {m_itor++;}
		void operator ++(int) {m_itor++;}
	private:
		std::multimap<unsigned long long, Timer *>::iterator m_itor;
		bool m_bNull;
	};

public:
	TimerPrivate(void);
	virtual ~TimerPrivate(void);

	bool IsActive() const { return m_isActive;}

//	void SetActive(const std::map<unsigned long long, Timer *>::iterator &itor)
//	{
//		m_isActive = true;
//		m_driverItor = itor;
//	}

	void SetActive(bool active)
	{
		m_isActive = active;
	}

//	const std::map<unsigned long long, Timer *>::iterator &GetDriverItor() const
//	{
//		return m_driverItor;
//	}

	AllowNullIterator m_driverItor;
	bool m_isActive;

	void SetDriverItor(std::multimap<unsigned long long, Timer *>::iterator *pitor)
	{
		if(pitor == NULL)
		{
			m_driverItor.SetNull();
		}
		else
		{
			m_driverItor.SetIterator(*pitor);
		}
	}

	bool IsUseDriverItor() const
	{
		return !m_driverItor.IsNull();
	}

	const std::multimap<unsigned long long, Timer *>::iterator & GetDriverItor()
	{
		return m_driverItor.GetIterator();
	}

private:
//	std::map<unsigned long long, Timer *>::iterator m_driverItor;
};

}}

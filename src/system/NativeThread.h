#pragma once
#include "system/Thread.h"

namespace nb{ namespace System{

class NativeThread
{
public:
	virtual void SetPriority(nb::System::Thread::Priority priority) {m_Priority = priority;}

	nb::System::Thread::Priority GetPriority() const {return m_Priority;}

	virtual void Start() = 0;

	virtual void Quit() = 0;

	virtual bool IsRunning() const = 0;

	virtual bool Wait(unsigned long millisecons) = 0;

protected:
	NativeThread(Thread *pV) : m_pV(pV) {}

	nb::System::Thread::Priority	m_Priority;
	Thread							*m_pV;
};

}}

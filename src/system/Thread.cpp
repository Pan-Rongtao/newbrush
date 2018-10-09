#include "system/Thread.h"
#include "Thread_Internal.h"

using namespace nb::System;

Thread::Thread()
{
	m_internal = new Thread_Internal(this);
}

Thread::~Thread()
{
	delete m_internal;
}

void Thread::setPriority(Priority priority)
{
	m_internal->setPriority(priority);
}

Thread::Priority Thread::priority() const
{
	return m_internal->priority();
}

void Thread::start()
{
	m_internal->start();
}

void Thread::quit()
{
	m_internal->quit();
}

bool Thread::isRunning()
{
	return m_internal->isRunning();
}

bool Thread::wait(unsigned long nMs)
{
	return m_internal->wait(nMs);
}

void Thread::run()
{
}

void Thread::sleep(unsigned long seconds)
{
	nb::sleep(seconds);
}

void Thread::msleep(unsigned long milliseconds)
{
	nb::msleep(milliseconds);
}

void Thread::usleep(unsigned long useconds)
{
	nb::usleep(useconds);
}

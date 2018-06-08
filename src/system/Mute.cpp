#include "system/Mute.h"
#include "Mute_Internal.h"

using nb::System::Mute;

Mute::Mute(const char *name)
{
	m_internal = new Mute_Internal(name);
}

Mute::~Mute()
{
	delete m_internal;
}

void Mute::Lock()
{
	m_internal->Lock();
}

void Mute::Unlock()
{
	m_internal->Unlock();
}

bool Mute::IsExists(const char *name)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	return ::OpenMutexA(MUTEX_ALL_ACCESS, false, name) != 0;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	return sem_open(name, O_RDONLY) != SEM_FAILED;
#endif
}

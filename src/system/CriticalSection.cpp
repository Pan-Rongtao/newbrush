#include "system/CriticalSection.h"
#include "CriticalSection_Internal.h"

using namespace nb::System;

CriticalSection::CriticalSection()
{
	m_pInternal = new CriticalSection_Internal();
}

CriticalSection::~CriticalSection()
{
	delete m_pInternal;
}

void CriticalSection::Lock()
{
	m_pInternal->Lock();
}

void CriticalSection::Unlock()
{
	m_pInternal->Unlock();
}

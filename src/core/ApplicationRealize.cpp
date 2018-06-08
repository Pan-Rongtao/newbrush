#include "core/ApplicationRealize.h"
#include "InternalCore.h"
#include "TypePrivate.h"
#include "PropertyInternal.h"

using namespace nb::Core;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

nbCoreApplication::nbCoreApplication(void)
{
}

nbCoreApplication::~nbCoreApplication(void)
{
}

void nbCoreApplication::Run()
{
//	Test();
}

nbCoreApplication * nbCoreApplication::GetInstance()
{
	return NULL;// nbInternalCore::GetApplication();
}

void nbCoreApplication::InitGlobal()
{
	nbInternalCore::GetTypeInternal()->AppPrepareTypes();
	nbInternalCore::GetDependencyPropertyInteranl()->AppPreparePropertys();
}

#include "core/Application.h"
#include "core/ApplicationRealize.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


nbCoreApplicationPtr::nbCoreApplicationPtr(void)
{
}

nbCoreApplicationPtr::~nbCoreApplicationPtr(void)
{
}

void nbCoreApplicationPtr::Run()
{
	GetRealize()->Run();
}

nbCoreApplication * nbCoreApplicationPtr::GetRealize()
{
	return dynamic_cast<nbCoreApplication *>(nbObjectPtr::GetRealize());
}

//void nbApplicationPtr::CreateInstance()
//{
//	EqualAndRealseRef(new nbApplication());
//}

#include "InternalCore.h"
#include "core/Application.h"

#include "TypePrivate.h"
#include "PropertyInternal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

//class nbCoreEnd
//{
//};

//static nbCoreEnd m_CoreEnd;

bool nbInternalCore::m_bConstructerEnsure = false;

nbInternalCore::nbInternalCore(void)
	//: m_pApplication(NULL)
	: m_pTypeInternal(NULL)
	, m_pDependencyPropertyInternal(NULL)
{
	m_csRefPtr = new ObjectLiveMonitor::CriticalSection();

	char c[1024];
	::NB_SNPRINTF(c, 1023, "   NewBrush ver 0.0.0.1\r\n   Desay SV copyright\r\n   Build on %s %s", __DATE__, __TIME__);

/*		NB_OUTA("\r\n======================================================================");
	NB_OUTA("");
	NB_OUTA("   ##   ##                 ######                          ###        ");
	NB_OUTA("   ##   ##                  ##  ##                          ##        ");
	NB_OUTA("   ###  ##                  ##  ##                          ##        ");
	NB_OUTA("   #### ##  ####   ##   ##  ##  ## ### ##  ##  ##   ####    ## ##     ");
	NB_OUTA("   ####### ##  ##  ##   ##  #####   ## ### ##  ##  ##  ##   ### ##    ");
	NB_OUTA("   ## #### ######  ## # ##  ##  ##  ### ## ##  ##   ##      ##  ##    ");
	NB_OUTA("   ##  ### ##      ## # ##  ##  ##  ##     ##  ##     ##    ##  ##    ");
	NB_OUTA("   ##   ## ##  ##   ## ##   ##  ##  ##     ##  ##  ##  ##   ##  ##    ");
	NB_OUTA("   ##   ##  ####    ## ##  ######  ####     ### ##  ####   ###  ##    ");
	NB_OUTA("");
	NB_OUTA("  ..................................................................");
	NB_OUTA("");
	NB_OUTA(c);
	NB_OUTA("");
	NB_OUTA("======================================================================\r\n");
*/
/*
	NB_OUTA("\r\n============================================================================");
	NB_OUTA("");
	NB_OUTA("   ##    ##                   #######                             ###        ");
	NB_OUTA("   ##    ##                    ##   ##                             ##        ");
	NB_OUTA("   ###   ##                    ##   ##                             ##        ");
	NB_OUTA("   ####  ##   ####   ##   ##   ##   ##  ###      ##  ##    ####    ## ##     ");
	NB_OUTA("   ## ## ##  ##  ##  ##   ##   ######    ## ###  ##  ##   ##  ##   ### ##    ");
	NB_OUTA("   ##  ####  ######  ## # ##   ##   ##   ####    ##  ##    ##      ##  ##    ");
	NB_OUTA("   ##   ###  ##      ## # ##   ##   ##   ##      ##  ##      ##    ##  ##    ");
	NB_OUTA("   ##    ##  ##  ##   ## ##    ##   ##   ##      ##  ##   ##  ##   ##  ##    ");
	NB_OUTA("   ##    ##   ####    ## ##   #######   ####      ### ##   ####   ###  ##    ");
	NB_OUTA("");
	NB_OUTA("  ........................................................................");
	NB_OUTA("");
	NB_OUTA(c);
	NB_OUTA("");
	NB_OUTA("============================================================================\r\n");
	*/
}

nbInternalCore::~nbInternalCore(void)
{
//	if(m_pApplication != NULL)
//	{
//		m_pApplication->ReleaseRef();
//		m_pApplication = NULL;
//	}
	
	delete m_pTypeInternal;
	delete m_pDependencyPropertyInternal;

	delete m_csRefPtr; //这个需要在delete m_pTypeInternal之后
}

//nbCoreApplication *nbInternalCore::GetApplication()
//{
//	if(GetInstance()->m_pApplication == NULL)
//	{
//		GetInstance()->m_pApplication = new nbCoreApplication();
//	}
//	return GetInstance()->m_pApplication;

//	return NULL;
//}

TypeInternal * nbInternalCore::GetTypeInternal()
{
	if(GetInstance()->m_pTypeInternal == NULL)
	{
		GetInstance()->m_pTypeInternal = new TypeInternal();
	}
	return GetInstance()->m_pTypeInternal;
}

DependencyPropertyInternal * nbInternalCore::GetDependencyPropertyInteranl()
{
	if(GetInstance()->m_pDependencyPropertyInternal == NULL)
	{
		GetInstance()->m_pDependencyPropertyInternal = new DependencyPropertyInternal();
	}
	return GetInstance()->m_pDependencyPropertyInternal;
}

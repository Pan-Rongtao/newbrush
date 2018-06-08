#include "core/ObjectPtr.h"
#include "core/Object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*

nbObjectPtr::nbObjectPtr(void)
	: m_pRealize(NULL)
{
}

nbObjectPtr::nbObjectPtr(nbObjectPtr &right)
	: m_pRealize(NULL)
{
	operator = (right);
}

nbObjectPtr::nbObjectPtr(nbObject *pObject)
	: m_pRealize(NULL)
{
	operator = (pObject);
}


nbObjectPtr::~nbObjectPtr(void)
{
	if(m_pRealize != NULL) m_pRealize->ReleaseRef();
}

void nbObjectPtr::operator = (nbObjectPtr &right)
{
	Equal(right.m_pRealize);
}

void nbObjectPtr::operator = (nbObject *pRealize)
{
	Equal(pRealize);
}

nbObject * nbObjectPtr::GetRealize()
{
	return m_pRealize;
}

void nbObjectPtr::Equal(nbObject *pRealize)
{
	if(m_pRealize == pRealize) return;

	if(pRealize != NULL && !pRealize->IsCanRef())
	{
		NB_OUTA("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		NB_OUTA("[New Brush] Error!!");
		NB_OUTA("[New Brush] Non ref object, prohibited assignment to Ptr.");
		NB_OUTA("[New Brush] exit(1)");
		NB_OUTA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		exit(1);
		return;
	}

	if(m_pRealize != NULL)
	{
		m_pRealize->ReleaseRef();
	}
	
	m_pRealize = pRealize;
	if(m_pRealize != NULL)
	{
		m_pRealize->AddRef();
	}
}

//void nbObjectPtr::EqualAndRealseRef(nbObject *pRealize)
//{
//	Equal(pRealize);
//	pRealize->ReleaseRef();
//}
*/

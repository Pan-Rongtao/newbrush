#include <stdlib.h>
#include "core/RefObject.h"
#include "InternalCore.h"
#include "ObjectLiveMonitor.h"

using namespace nb::core;

NB_OBJECT_TYPE_IMPLEMENT(RefObject, OriginObject, NULL, NULL);

#define NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(T) \
	void *RefRockValueObjectsPropareType::s_p##T##PrepareType = nb::core::OriginObject::PrepargeType<T, RefObject>(NULL, NULL);

class RefRockValueObjectsPropareType
{
public:
	static void *s_paIntPrepareType;
	static void *s_paLongPrepareType;
	static void *s_paFloatPrepareType;
	static void *s_paDoublePrepareType;
	static void *s_paBoolPrepareType;
};

NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(aInt);
NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(aLong);
NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(aFloat);
NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(aDouble);
NB_REF_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(aBool);


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RefObjectWeatPtr::RefObjectWeatPtr()
	: m_pObject(NULL)
{
}

RefObjectWeatPtr::RefObjectWeatPtr(RefObject *pObject)
	: m_pObject(NULL)
{
	operator = (pObject);
}

RefObjectWeatPtr::RefObjectWeatPtr(const RefObjectWeatPtr &right)
	: m_pObject(NULL)
{
	operator = (right);
}

RefObjectWeatPtr::~RefObjectWeatPtr()
{
	operator = (NULL);
}

void RefObjectWeatPtr::operator = (RefObject *pObject)
{
	if(m_pObject == pObject) return;

	std::set<RefObjectWeatPtr *> *pData;

	if(m_pObject != NULL)
	{
		pData = (std::set<RefObjectWeatPtr *> *)TakeObjectWeatPtrData(m_pObject);
		pData->erase(this);
	}

	m_pObject = pObject;

	if(m_pObject != NULL)
	{
		pData = (std::set<RefObjectWeatPtr *> *)TakeObjectWeatPtrData(m_pObject);
		pData->insert(this);
	}
}

void RefObjectWeatPtr::operator = (const RefObjectWeatPtr &right)
{
	operator = (right.m_pObject);
}

void * RefObjectWeatPtr::TakeObjectWeatPtrData(RefObject *pObject)
{
	if(pObject->m_pWeatPtrData == NULL)
	{
		pObject->m_pWeatPtrData = new std::set<RefObjectWeatPtr *>();
	}

	return pObject->m_pWeatPtrData;
}

void * RefObjectWeatPtr::GetObjectWeatPtrData(RefObject *pObject)
{
	return pObject->m_pWeatPtrData;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SharedPtrBase::SharedPtrBase()
{
}

SharedPtrBase::~SharedPtrBase(void)
{
}

void SharedPtrBase::Verify(RefObject *obj) const
{
	if(obj != NULL && !obj->IsCanRef())
	{
		printf("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		printf("[New Brush] Error!!\r\n");
		printf("[New Brush] 不是可计数对象，禁止保存到 Shared Ptr 。\r\n");
		printf("[New Brush] exit(1)\r\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		exit(1);
		return;
	}
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RefObjectPtr::RefObjectPtr(void)
	: m_pRealize(NULL)
{
}

RefObjectPtr::RefObjectPtr(const RefObjectPtr &right)
	: m_pRealize(NULL)
{
	operator = (right);
}

RefObjectPtr::RefObjectPtr(RefObject *pObject)
	: m_pRealize(NULL)
{
	operator = (pObject);
}


RefObjectPtr::~RefObjectPtr(void)
{
	if(m_pRealize != NULL) m_pRealize->ReleaseRef();
}

void RefObjectPtr::operator = (const RefObjectPtr &right)
{
	Equal(right.m_pRealize);
}

void RefObjectPtr::operator = (RefObject *pRealize)
{
	Equal(pRealize);
}

RefObject * RefObjectPtr::GetRealize() const
{
	return m_pRealize;
}

void RefObjectPtr::Equal(RefObject *pRealize)
{
	if(m_pRealize == pRealize) return;

	if(pRealize != NULL && !pRealize->IsCanRef())
	{
		printf("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		printf("[New Brush] Error!!\r\n");
		printf("[New Brush] 不是可计数对象，禁止保存到 Ptr 。\r\n");
		printf("[New Brush] exit(1)\r\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
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


RefObject::RefObject(void)
	: m_nRef(0)
	, m_pWeatPtrData(NULL)
{
	m_bIsCanRef = nbInternalCore::GetObjectLiveMonitor()->ObjectHeapConstructPermit(this);
}

RefObject::RefObject(const RefObject &r)
	: m_nRef(0)
	, m_pWeatPtrData(NULL)
{
	m_bIsCanRef = nbInternalCore::GetObjectLiveMonitor()->ObjectHeapConstructPermit(this);
}

RefObject::~RefObject(void)
{
	if(m_pWeatPtrData != NULL)
	{
		std::set<RefObjectWeatPtr *> * pWeatPtrs = (std::set<RefObjectWeatPtr *> *)m_pWeatPtrData;
		std::set<RefObjectWeatPtr *>::iterator itor = pWeatPtrs->begin();
		for(; itor != pWeatPtrs->end(); itor++)
		{
			RefObjectWeatPtr *pWeatPtr = *itor;
			pWeatPtr->m_pObject = NULL;
		}

		delete pWeatPtrs;
	}
}

void RefObject::operator = (const RefObject &r)
{
}

void RefObject::AddRef()
{
	m_nRef++;
}

void RefObject::ReleaseRef()
{
	m_nRef--;
	if(m_nRef == 0) delete this;
}

void * RefObject::operator new(size_t t)
{
	void *p = nbInternalCore::GetObjectLiveMonitor()->Malloc(t, true, NULL, 0);
//	s_pMallocingObject = p;
	return p;
}

void * RefObject::operator new(size_t t, const char * lpszFileName, int nLine)
{
	void *p = nbInternalCore::GetObjectLiveMonitor()->Malloc(t, true, lpszFileName, nLine);
	return p;
}

void RefObject::operator delete(void *p)
{
	if(p == NULL) return;

	nbInternalCore::GetObjectLiveMonitor()->Free(p);
}

void RefObject::operator delete(void *p, const char * /*lpszFileName*/, int /*nLine*/)
{
	operator delete(p);
}

bool RefObject::IsCanRef() const
{
	return m_bIsCanRef;
}

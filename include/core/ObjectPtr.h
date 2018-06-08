#pragma once

#include "NewBrushDef.h"

/*
class nbObject;
class NB_EXPORT nbObjectPtr
{
public:
	nbObjectPtr(void);
	nbObjectPtr(nbObjectPtr &right);
	nbObjectPtr(nbObject *pObject);

	virtual ~nbObjectPtr(void);

	nbObject * GetRealize();
	nbObject * operator ->() {return GetRealize();}

	void operator = (nbObjectPtr &right);
	void operator = (nbObject *pRealize);
	void Equal(nbObject *pRealize);


protected:
//	void EqualAndRealseRef(nbObject *pRealize);
private:
	nbObject *m_pRealize;
};


template<class ObjectT, class ParentPtrT>
class nbObjectPtrDerive : public ParentPtrT
{
public:
	nbObjectPtrDerive(){}
	nbObjectPtrDerive(ObjectT *pObject) : ParentPtrT(pObject) {}

	ObjectT * operator ->() {return GetRealize();}
	ObjectT * GetRealize() {return dynamic_cast<ObjectT *>(ParentPtrT::GetRealize());}
	operator ObjectT *() {return GetRealize();}
	void CreateInstance() {Equal(new ObjectT());}

	void operator = (ObjectT *pObject) {ParentPtrT::Equal(pObject);}
};
*/

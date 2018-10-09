#pragma once
#include "OriginObject.h"

namespace nb { namespace core {

class RefObjectPtr;
class RefObjectWeatPtr;
class NB_API RefObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();

	friend class RefObjectPtr;
	friend class RefObjectWeatPtr;
	friend class SharedPtrBase;

public:
	RefObject(void);
	RefObject(const RefObject &r);
	virtual ~RefObject(void);

	void * operator new(size_t t);
	void operator delete(void *p);

	void * operator new(size_t t, const char * lpszFileName, int nLine);
	void operator delete(void *p, const char * lpszFileName, int nLine);

	void * operator new[](size_t t);

	bool IsCanRef() const;

	void operator = (const RefObject &r);

private:
	void AddRef();
	void ReleaseRef();
	int m_nRef;
	bool m_bIsCanRef;

	void * m_pWeatPtrData;
};

class NB_API RefObjectWeatPtr
{
	friend class RefObject;
public:
	RefObjectWeatPtr();
	RefObjectWeatPtr(RefObject *pObject);
	RefObjectWeatPtr(const RefObjectWeatPtr &right);
	virtual ~RefObjectWeatPtr();

	void operator = (RefObject *pRealize);
	void operator = (const RefObjectWeatPtr &right);

	operator RefObject *() const {return m_pObject;}
	RefObject * operator ->() const {return m_pObject;}

private:
	static void * GetObjectWeatPtrData(RefObject *pObject);
	static void * TakeObjectWeatPtrData(RefObject *pObject);

	RefObject *m_pObject;
};


template<class T>
class RefObjectWeatPtrT : public RefObjectWeatPtr
{
public:
	RefObjectWeatPtrT(){}
	RefObjectWeatPtrT(T *pObject) : RefObjectWeatPtr(pObject) {}
	RefObjectWeatPtrT(const RefObjectWeatPtrT &right) : RefObjectWeatPtr(right) {}

	operator T *() const {return (T *)RefObjectWeatPtr::operator ->();}
	T * operator ->() const {return (T *)RefObjectWeatPtr::operator ->();}
};

class NB_API SharedPtrBase
{
public:
	SharedPtrBase(void);
	virtual ~SharedPtrBase(void);

	void Verify(RefObject *obj) const;

protected:
	inline void ObjectAddRef(RefObject *obj) const
	{
		obj->AddRef();
	}

	inline void ObjectReleaseRef(RefObject *obj) const
	{
		obj->ReleaseRef();
	}
};

template<class T>
class SharedPtr : public SharedPtrBase
{
public:
	SharedPtr() : m_ptr(NULL) {}

	SharedPtr(T *ptr) : m_ptr(NULL) { Set(ptr); }

	SharedPtr(const SharedPtr &right) : m_ptr(NULL) { Set(right.Get()); }

	template<class Tr>
	SharedPtr(const SharedPtr<Tr> &right) : m_ptr(NULL) { Set(right.Get()); }

	virtual ~SharedPtr() { if(m_ptr != NULL) ObjectReleaseRef(m_ptr); }

	void Set(T *ptr)
	{
		Verify(ptr);

		if(m_ptr != NULL)
		{
			ObjectReleaseRef(m_ptr);
		}
	
		m_ptr = ptr;
		if(m_ptr != NULL)
		{
			ObjectAddRef(m_ptr);
		}
	}

	T * Get() const {return m_ptr;}

	bool operator == (T *right) const { return m_ptr == right; }


	void operator = (T *ptr) { Set(ptr); }

	void operator = (const SharedPtr &right) { Set(right.Get()); }

	template<class Tr>
	void operator = (const SharedPtr<Tr> &right) { Set(right.Get()); }

private:
	T * m_ptr;
};

template<class T1, class T2>
bool operator == (const SharedPtr<T1> &s1, const SharedPtr<T2> &s2) { return s1.Get() == s2.Get(); }

template<class Ts, class Tp>
bool operator == (const SharedPtr<Ts> &s, Tp * const p) { return s.Get() == p; }

template< class Tp, class Ts>
bool operator == (Tp * const p, const SharedPtr<Ts> &s) { return s.Get() == p; }


class NB_API RefObjectPtr
{
public:
	RefObjectPtr(void);
	RefObjectPtr(const RefObjectPtr &right);
	RefObjectPtr(RefObject *pObject);

	virtual ~RefObjectPtr(void);

	RefObject * GetRealize() const;
	RefObject * operator ->() const {return GetRealize();}

	void operator = (const RefObjectPtr &right);
	void operator = (RefObject *pRealize);
	void Equal(RefObject *pRealize);

	operator RefObject *() const {return GetRealize();}

	bool operator < (const RefObjectPtr &other) const {return m_pRealize < other.m_pRealize;}
	bool operator <= (const RefObjectPtr &other) const {return m_pRealize <= other.m_pRealize;}
	bool operator > (const RefObjectPtr &other) const {return m_pRealize > other.m_pRealize;}
	bool operator >= (const RefObjectPtr &other) const {return m_pRealize >= other.m_pRealize;}
	bool operator == (const RefObjectPtr &other) const {return m_pRealize == other.m_pRealize;}
	bool operator != (const RefObjectPtr &other) const {return m_pRealize != other.m_pRealize;}

	bool operator < (RefObject *other) const {return m_pRealize < other;}
	bool operator <= (RefObject *other) const {return m_pRealize <= other;}
	bool operator > (RefObject *other) const {return m_pRealize > other;}
	bool operator >= (RefObject *other) const {return m_pRealize >= other;}
	bool operator == (RefObject *other) const {return m_pRealize == other;}
	bool operator != (RefObject *other) const {return m_pRealize != other;}


	template<class T>
	T DynamicCast()
	{
		return dynamic_cast<T>(m_pRealize);
	}

	template<class T>
	const T DynamicCast() const
	{
		return dynamic_cast<T>(m_pRealize);
	}

protected:
	//	void EqualAndRealseRef(nbObject *pRealize);
private:
	RefObject *m_pRealize;
};


template<class T>
class RefObjectPtrT : public RefObjectPtr
{
public:
	RefObjectPtrT(){}
	RefObjectPtrT(T *pObject) : RefObjectPtr(pObject) {}
	RefObjectPtrT(const RefObjectPtrT &right) : RefObjectPtr(right) {}

	operator T *() const {return (T *)RefObjectPtr::operator ->();}
	T * operator ->() const {return (T *)RefObjectPtr::operator ->();}
};


template<class T>
class RefRockValueObject : public RefObject
{
//	NB_OBJECT_TYPE_DECLARE();
public:
	RefRockValueObject() {}
	RefRockValueObject(const T &v) : m_value(v) {}
//	void operator = (const RockValueObject &right) {m_value = right.m_value;}

	bool operator == (const RefRockValueObject<T> &other) const {return m_value == other.m_value;}
	operator T & () {return m_value;}

	typedef T t;
public:
	T m_value;
};

//typedef RefRockValueObject<int> aInt;
typedef RefRockValueObject<long> aLong;
//typedef RefRockValueObject<float> aFloat;
typedef RefRockValueObject<double> aDouble;
typedef RefRockValueObject<bool> aBool;

//typedef float _aFloat;

class aInt : public RefRockValueObject<int>
{
public:
	aInt() {}
	aInt(int v) : RefRockValueObject(v) {}
	void ToString() const {}
};

class aFloat : public  RefRockValueObject<float>
{
public:
	aFloat() {}
	aFloat(float v) : RefRockValueObject(v) {}
	void ToString() const {}
};

class RefEnumObjectBase : public RefObject
{
};

template<class T>
class RefEnumObject : public RefEnumObjectBase
{
public:
	RefEnumObject(T e) : m_e(e){}
	operator T () const {return m_e;}
private:
	T m_e;
};

}}

template<class T, class ParentPtrT>
class NB_API nbObjectPtrDerive : public ParentPtrT
{
public:
	nbObjectPtrDerive(){}
	nbObjectPtrDerive(T *pObject) : ParentPtrT(pObject) {}

	T * operator ->() const {return GetRealize();}
	T * GetRealize() const {return dynamic_cast<T *>(ParentPtrT::GetRealize());}
	operator T *() const {return GetRealize();}
	void CreateInstance() {Equal(new T());}

	void operator = (T *pObject) {ParentPtrT::Equal(pObject);}

	T & operator * () const {return *GetRealize();}

};

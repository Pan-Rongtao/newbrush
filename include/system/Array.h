#pragma once

#include "core/RefObject.h"
#include "core/Object.h"
#include "SystemDef.h"

namespace nb { namespace System {

class NB_SYSTEM_DECLSPEC_INTERFACE IArray : public nb::Core::InterfaceBase
{
public:
	virtual void Add(nb::Core::RefObject *value) = 0;
	virtual void Insert(int index, nb::Core::RefObject *value) = 0;
	virtual void Clear() = 0;
	virtual void RemoveAt(int index) = 0;
	virtual nb::Core::RefObject * GetAt(int index) const = 0;
	virtual nb::Core::RefObject * operator [](int index) const = 0;

	virtual int GetCount() const = 0;
};

class NB_SYSTEM_DECLSPEC_INTERFACE IHasChildrenArray : public nb::Core::InterfaceBase
{
public:
	virtual IArray * GetChildrenArray() = 0;
};


class ObjectArrayBasePrivate;
class NB_SYSTEM_DECLSPEC_INTERFACE ObjectArrayBase : public nbObject, public IArray
{
	NB_OBJECT_TYPE_DECLARE();

public:
	int GetCount() const;
	void Clear();
	void RemoveAt(int index);

	virtual ~ObjectArrayBase();

	static ObjectArrayBase * FindObjectBelongToArray(nbObject *object);

protected:
	ObjectArrayBase();
	void AddBase(RefObject *object);
	void InsertBase(int index, RefObject *object);
	nb::Core::RefObject * GetAt(int index) const;

	virtual void OnChanged() {NotifyContentChanged();}

	inline ObjectArrayBasePrivate * GetPrivate() const {return m_private;}

	virtual nb::Core::InterfaceBase * GetInterfaceOverride(const std::type_info &type);

private:
	ObjectArrayBasePrivate * m_private;
};

template<class T>
class NB_EXPORT_NO ObjectArray : public ObjectArrayBase
{
public:
	void Add(const Core::RefObjectPtr &ptr)
	{
		Add((RefObject *)ptr);
	}

	void Add(T *value)
	{
		AddBase(value);
	}

	void Insert(int index, const Core::RefObjectPtr &ptr)
	{
		Insert(index, (RefObject *)ptr);
	}

	void Insert(int index, T *value)
	{
		InsertBase(index, value);
	}


	T * GetAt(int index) const
	{
		return (T *)ObjectArrayBase::GetAt(index);
	}

	T * operator [](int index) const
	{
		return (T *)ObjectArrayBase::GetAt(index);
	}


	void Add(nb::Core::RefObject *value)
	{
		T * x = dynamic_cast<T *>(value);

		if(x == NULL)
		{
			ThrowException("在ObjectArray中添加错误类型的项目。");
		}
		else
		{
			AddBase(value);
		}
	}

	void Insert(int index, nb::Core::RefObject *value)
	{
		T * x = dynamic_cast<T *>(value);

		if(x == NULL)
		{
			ThrowException("在ObjectArray中插入错误类型的项目。");
		}
		else
		{
			InsertBase(index, value);
		}
	}

};

/*
class IArrayItem
{
	virtual IArray * GetArray() const = 0;
};

class ObjectArrayItemBase : public nbObject, public IArrayItem
{
	NB_OBJECT_TYPE_DECLARE();

	friend ObjectArrayBase;
public:
	ObjectArrayItemBase() : m_belongToArray(NULL) {}
	IArray * GetArray() const {return m_belongToArray;}
private:
	IArray * m_belongToArray;
};*/

}}

#pragma once
#include "../core/Object.h"
#include "../core/Exception.h"
#include "../core/DataSerial.h"

class NB_API GenericVariant : public nbObject
{
public:
	GenericVariant(void);
	virtual ~GenericVariant(void);

	template<class T>
	GenericVariant(const T& value)
		: m_content(new Holder<T>(value))
	{
	}

	GenericVariant(const GenericVariant &r)
		: m_content(r.m_content == NULL ? NULL : r.m_content->Clone())
	{
	}

public:

	template<class T>
	void operator = (const T &value)
	{
		if(m_content != NULL) delete m_content;
		m_content = new Holder<T>(value);
	}

	void operator = (const GenericVariant &r)
	{
		if(m_content == r.m_content) return;

		if(m_content != NULL) delete m_content;
		m_content = (r.m_content == NULL ? NULL : r.m_content->Clone());
	}

	template<class T>
	operator T &() const
	{
		if(m_content == NULL) NB_THROW_EXCEPTION("GenericVariant没有存储数据。");

		Holder<T> *h = dynamic_cast<Holder<T> *>(m_content);
		if(h == NULL) NB_THROW_EXCEPTION("GenericVariant存储的类型不是所获取的类型。");

		return h->value();
	}

	template<class T>
	operator const T &() const
	{
		if(m_content == NULL) NB_THROW_EXCEPTION("GenericVariant没有存储数据。");

		Holder<T> *h = dynamic_cast<Holder<T> *>(m_content);
		if(h == NULL) NB_THROW_EXCEPTION("GenericVariant存储的类型不是所获取的类型。");

		return h->value();
	}

	template<class T>
	T & Get() const
	{
		return operator T &();
	}

	template<class T>
	const T & Get() const
	{
		return operator const T &();
	}

	template<class T>
	bool IsType() const
	{
		if(m_content == NULL) return false;
		Holder<T> *h = dynamic_cast<Holder<T> *>(m_content);
		return (h != NULL);
	}

	void StoreData(DataSerial &serial)
	{
		if(m_content == NULL) NB_THROW_EXCEPTION("GenericVariant没有存储数据。");

		m_content->StoreData(serial);
	}

	bool IsNull() const { return m_content == NULL; }

private:
	class PlaceHolder
	{
	public:
		virtual ~PlaceHolder() {}
		virtual PlaceHolder * Clone() const = 0;
	//	virtual DataSerial & Serial(DataSerial &serial) = 0; 
		virtual void StoreData(DataSerial &serial) = 0;
	};

	template<typename ValueType>
	class Holder : public PlaceHolder {
	public:
		Holder(const ValueType& value) : m_held(value) {}
		ValueType &value() {return m_held;}
		const ValueType &value() const {return m_held;}

		virtual PlaceHolder * Clone() const
		{
			return new Holder(m_held);
		}

		virtual DataSerial & Serial(DataSerial &serial)
		{
			if(serial.IsStoring()) serial << m_held;
			else serial >> m_held;

			return serial;
		}

		virtual void StoreData(DataSerial &serial)
		{
			serial << m_held;
		}

	private:
		ValueType m_held;
	};

	PlaceHolder* m_content;

};

typedef nbObjectPtrDerive<GenericVariant, nb::core::RefObjectPtr> GenericVariantPtr;

//DataSerial & operator << (DataSerial &serial, GenericVariant &variant)
//{
//	variant.Ser
//	return serial;
//}

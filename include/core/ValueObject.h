#pragma once
#include "OriginObject.h"

namespace nb { namespace core {

class NB_API ValueObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ValueObject(void);
	virtual ~ValueObject(void);

	virtual void operator = (const ValueObject &right) {}

	void * operator new(size_t t);
	void operator delete(void *p);

private:
	void * operator new[](size_t t);
};

template<class T>
class RockValueObject : public ValueObject
{
//	NB_OBJECT_TYPE_DECLARE();
public:
	RockValueObject() {}
	RockValueObject(const T &v) : m_value(v) {}
//	void operator = (const RockValueObject &right) {m_value = right.m_value;}

	bool operator == (const RockValueObject<T> &other) const {return m_value == other.m_value;}
	operator T & () {return m_value;}
public:
	T m_value;
};

typedef RockValueObject<int> Int;
typedef RockValueObject<long> Long;
typedef RockValueObject<float> Float;
typedef RockValueObject<double> Double;
typedef RockValueObject<bool> Boolx;

}}

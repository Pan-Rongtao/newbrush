#pragma once
#include <fstream>

class TestBase
{
public:
	virtual void test() = 0;

};

template <class T>
class TestHandle
{
public:
	TestHandle<T>() { m_pInter = new T(); }
	~TestHandle() { delete m_pInter; }

	T * operator ->() { return (T *)m_pInter; }

private:
	TestBase *m_pInter;
};

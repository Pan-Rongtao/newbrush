#include "core/Assembly.h"
#include "core/Exception.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

Assembly::Assembly(NewObjectAssemblerFun pFun, NewCopyObjectAssemblerFun pFunCopy)
	: m_pFun(pFun)
	, m_pFunCopy(pFunCopy)
{
}

Assembly::~Assembly(void)
{
}

OriginObject * Assembly::CreateObjectInstance()
{
	if(m_pFun == NULL) NB_THROW_EXCEPTION("构建对象函数指针为空。");

	return m_pFun();
}

OriginObject * Assembly::CreateObjectInstance(const nb::Core::OriginObject &other)
{
	if(m_pFunCopy == NULL) NB_THROW_EXCEPTION("复制构建对象函数指针为空。");

	return m_pFunCopy(other);
}

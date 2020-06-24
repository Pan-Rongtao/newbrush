#include "RpcService.h"
#include "RpcServiceImpl.h"

using namespace nb;

RpcService::RpcService(const std::string &address)
	: m_impl(std::make_shared<RpcServiceImpl>(address))
{
}

const std::string & nb::RpcService::address() const
{
	return m_impl->address();
}

void nb::RpcService::startup()
{
	m_impl->startup();
}

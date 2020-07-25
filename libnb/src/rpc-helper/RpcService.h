#pragma once
#include <string>
#include <memory>
#include "newbrush/core/Def.h"

namespace nb {
	
class RpcServiceImpl;
class NB_API RpcService
{
public:
	RpcService(const std::string &address);

	const std::string &address() const;

	void startup();

private:
	std::shared_ptr<RpcServiceImpl> m_impl;
};

}


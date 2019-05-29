/*******************************************************
**	Storage
**
**	存储类
**		Storage是描述存储uniform以及值的数据结构
**
**
**		潘荣涛
**
********************************************************/
#pragma once
#include <map>
#include <string>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb{ namespace gl{

class NB_API Storage
{
public:
	Storage();
	~Storage();

	void insert(const std::string &name, const nb::core::Any &v);

	std::map<const std::string, nb::core::Any>::iterator beg();

	std::map<const std::string, nb::core::Any>::iterator end();

	nb::core::Any find(const std::string &name);
	
	void clear();

private:

	std::map<std::string, nb::core::Any>	m_uniforms;
};

} }
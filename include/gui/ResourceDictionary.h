#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb {
namespace gui{

class NB_API ResourceDictionary
{
public:
	//添加一个资源
	//异常：std::logic_error，已经有相同key的资源
	template<class resT>
	void add(const std::string &key, const resT &v);

	//移除一个资源
	void remove(const std::string &key);

	//清空资源
	void clear();

	//查找资源
	Any &find(const std::string &key);
	const Any &find(const std::string &key) const;

private:
	std::unordered_map<std::string, Any>	m_resmap;
};

template<class resT>
inline void ResourceDictionary::add(const std::string & key, const resT & v)
{
	if (m_resmap.find(key))
		nbThrowException(std::logic_error, "[%s] already exists.", key.data());
	else
		m_resmap[key] = v;
}

}
}
#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "Poco/Dynamic/Var.h"

namespace nb {
namespace gui{

using Poco::Dynamic::Var;
class NB_API ResourceDictionary
{
public:
	ResourceDictionary() = default;
	static ResourceDictionary fromFile(const std::string &path);

	//添加一个资源
	//异常：std::logic_error，已经有相同key的资源
	void add(const std::string &key, const Var &v);

	//移除一个资源
	void remove(const std::string &key);

	//清空资源
	void clear();

	//查找资源
	Var &find(const std::string &key);
	const Var &find(const std::string &key) const;

	//个数
	int count() const;
	

private:
	std::unordered_map<std::string, Var>	m_resmap;
};

}
}
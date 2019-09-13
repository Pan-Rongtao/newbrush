#pragma once
#include <unordered_map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb {
namespace gui{

class NB_API ResourceDictionary
{
public:
	ResourceDictionary() = default;
	static ResourceDictionary fromFile(const std::string &path);

	//添加一个资源
	//异常：std::logic_error，已经有相同key的资源
	void add(const std::string &key, const Any &v);

	//移除一个资源
	void remove(const std::string &key);

	//清空资源
	void clear();

	//查找资源
	Any &find(const std::string &key);
	const Any &find(const std::string &key) const;

	//个数
	int count() const;
	

private:
	std::unordered_map<std::string, Any>	m_resmap;
};

}
}
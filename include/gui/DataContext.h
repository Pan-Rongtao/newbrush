#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

class NB_API DataVar : public Poco::Dynamic::Var
{
public:
	DataObject *parent;
};

class NB_API DataObject
{
public:
	DataObject(const std::string &name);
	virtual ~DataObject() = default;

	//设置名字
	//异常：与兄弟节点重名
	void setName(const std::string &name) &;
	std::string name() const;

	//获取值
	DataVar get(const std::string &key) const;

	//获取所有子节点的键值
	void getKeys(std::vector<std::string> &keys) const;
	std::vector<std::string> getKeys() const;

	//是否有名为key的子节点
	bool has(const std::string &key) const;

	//子节点个数
	std::size_t childCount() const;

	//设置子节点的值，如果该子节点不存在，自动创建
	void set(const std::string &key, const DataVar &value) &;

	//移除子节点
	void remove(const std::string &key) &;

	struct ValueChangedArgs { std::shared_ptr<DataContext> root; std::string path; };
	Event<ValueChangedArgs>		ValueChanged;		//值改变事件

private:
	std::string			m_name;
	DataObject			*m_parent;
	Poco::JSON::Object	m_obj;
};

}}

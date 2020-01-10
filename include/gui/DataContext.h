#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

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
	Var get(const std::string &key) const;

	//获取所有子节点的键值
	void getKeys(std::vector<std::string> &keys) const;
	std::vector<std::string> getKeys() const;

	//是否有名为key的子节点
	bool has(const std::string &key) const;

	//子节点个数
	std::size_t childCount() const;

	//设置子节点的值，如果该子节点不存在，自动创建
	void set(const std::string &key, const Var &value) &;

	//移除子节点
	void remove(const std::string &key) &;

private:
	std::string			m_name;
	DataObject			*m_parent;
	Poco::JSON::Object	m_obj;
};

class NB_API ObjectData : public DataContext, public std::enable_shared_from_this<ObjectData>
{
public:
	ObjectData(const std::string &name);
	virtual ~ObjectData() = default;

	//添加一个子节点
	void insertChild(DataContextPtr child);

	//删除一个子节点
	void removeChild(const std::string & childName);

	//是否有子节点
	bool hasChild(const std::string & childName) &;

	//获取子节点，不存在返回空
	DataContextPtr getChild(const std::string &childName);

	//按路径查询节点
	//path：形如"a.b.c"，表示查找基于当前节点下的a/b/c节点
	//找不到返回空
	DataContextPtr lookup(const std::string &path);

	DataContextPtr operator [](const std::string &name);

private:
	ChildernContainer	m_children;
};

class NB_API ValueDataBase : public DataContext, public std::enable_shared_from_this<ValueDataBase>
{
public:
	virtual const std::type_info &type() const { return typeid(void); }
	virtual Var getAny() const { return Var(); }

	struct ValueChangedArgs { std::shared_ptr<DataContext> root; std::string path; };
	Event<ValueChangedArgs>		ValueChanged;		//值改变事件
	
protected:
	ValueDataBase(const std::string &name) : DataContext(name) {}
};
using ValueDataBasePtr = std::shared_ptr<ValueDataBase>;

template<class T>
class ValueData : public ValueDataBase
{
public:
	ValueData(const std::string &name, const T &v = T())
		: ValueDataBase(name)
		, m_v(v)
	{
	}

	void set(const T &v)
	{
		if (v != m_v.extract<T>())
		{
			m_v = v;
			std::string path = name();
			std::weak_ptr<DataContext> p = shared_from_this();
			while (p.lock()->m_parent.lock())
			{
				p = p.lock()->m_parent;
				if(p.lock()->m_parent.lock())
					path = p.lock()->name() + "." + path;
			}
			ValueChanged.invoke({ p.lock() , path });
		}
	}
	T get() { return m_v.extract<T>(); }
	const T get() const { return m_v.extract<T>(); }

	virtual Var getAny() const override { return m_v; }

	virtual const std::type_info &type() const override { return typeid(T); }

	void operator = (const T &v)	{ set(v); }
	bool operator != (const T &v) const { return m_v != v; }
	bool operator == (const T &v) const { return !(operator!=(v)); }

private:
	Var	m_v;
};


}}

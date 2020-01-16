#pragma once
#include <map>
#include "../core/Def.h"
#include "../core/Event.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"

namespace nb{ 
namespace gui{

class NB_API DataContext
{
public:
	virtual ~DataContext() = default;

	virtual void set(const Var &value) &;
	virtual Var get() const;
	virtual std::shared_ptr<DataContext> lookup(const std::string &path) const;
	virtual const std::type_info &type() const;

	struct ValueChangedArgs	{ DataContext *root; std::string path; };
	Event<ValueChangedArgs>	ValueChanged;		//值改变事件
	
protected:
	DataContext(const std::string &_name);

private:
	DataContext *getRoot() const;
	std::string getAbsPath() const;
	std::string getPath() const;

	std::string	name;
	DataContext *parent;
	friend class DataObject;
	template<class T> friend class DataVar;
};

class NB_API DataObject : public DataContext
{
public:
	DataObject(const std::string &name);

	//添加一个子节点
	void add(std::shared_ptr<DataContext> child) &;

	//删除一个子节点
	void remove(const std::string & childName) &;

	//是否有子节点
	bool has(const std::string & childName) const;

	//获取子节点，不存在返回空
	std::shared_ptr<DataContext> get(const std::string &childName) const;
	std::shared_ptr<DataObject> getObject(const std::string &childName) const;

	//按路径查询节点
	//path：形如"a.b.c"，表示查找基于当前节点下的a/b/c节点
	//找不到返回空
	virtual std::shared_ptr<DataContext> lookup(const std::string &path) const override;

	virtual const std::type_info &type() const;

	static std::shared_ptr<DataObject> gen(const std::string &name);

private:
	std::map<std::string, std::shared_ptr<DataContext>>	m_children;
};

template<class T>
class DataVar : public DataContext
{
public:
	DataVar(const std::string &name, const T &v = T())
		: DataContext(name)
		, m_v(v)
	{
	}

	void set(const T &v)
	{
		set(Var(T));
	}

	virtual void set(const Var &v) &
	{
		auto root = getRoot();
		auto path = getPath();
		if (m_v.type() == v.type())
		{
			m_v = v;
			root->ValueChanged.invoke({ root, path });
		}
		else
		{
			bool bEqual = false;
			try {
				bEqual = m_v == v;
			}
			catch (...) {
				nbThrowException(std::logic_error, "should set for [%s] with [%s] but not [%s].", getAbsPath().data(), m_v.type().name(), v.type().name());
			}

			if (!bEqual)
			{
				m_v = v;
				root->ValueChanged.invoke({ root, path });
			}
		}
	}
	virtual Var get() const override { return m_v; }

	virtual const std::type_info &type() const override { return typeid(T); }

	static std::shared_ptr<DataVar<T>> gen(const std::string &name, const T &v = T())
	{
		return std::make_shared<DataVar<T>>(name, v);
	}

private:
	Var	m_v;
};

class NB_API DataArray : public DataContext
{
public:
	DataArray(const std::string &name);

	void setTemplate(std::shared_ptr<DataObject> temp);

	const std::shared_ptr<DataObject> &getTemplate() const;

	void addItem(std::shared_ptr<DataObject> item);

	void removeItem(std::size_t index);

	std::shared_ptr<DataObject> item(std::size_t index);

	size_t itemCount() const;

	static std::shared_ptr<DataArray> gen(const std::string &name);

private:
	std::vector<std::shared_ptr<DataObject>>	m_items;
	std::shared_ptr<DataObject>					m_template;
};

}}

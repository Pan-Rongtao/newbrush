#pragma once
#include <map>
#include "newbrush/core/Def.h"
#include "newbrush/core/Event.h"

namespace nb{

class DataContext;
class DataObject;
using DataContextPtr = std::shared_ptr<DataContext>;
using DataObjectPtr = std::shared_ptr<DataObject>;

class NB_API DataContext
{
public:
	virtual ~DataContext() = default;

	virtual void set(const var &value) &;
	virtual var get() const;
	virtual DataContextPtr lookup(const std::string &path) const;
	virtual const std::type_info &type() const;

	struct ValueChangedArgs { DataContext *root; std::string path; var value; };
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
	void add(DataContextPtr child) &;

	//删除一个子节点
	void remove(const std::string & childName) &;

	//是否有子节点
	bool has(const std::string & childName) const;

	//获取子节点，不存在返回空
	DataContextPtr get(const std::string &childName) const;
	DataObjectPtr getObject(const std::string &childName) const;

	//按路径查询节点
	//path：形如"a.b.c"，表示查找基于当前节点下的a/b/c节点
	//找不到返回空
	virtual DataContextPtr lookup(const std::string &path) const override;

	virtual const std::type_info &type() const;

	static DataObjectPtr gen(const std::string &name);

private:
	std::map<std::string, DataContextPtr>	m_children;
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
		set(var(T));
	}

	virtual void set(const var &v) &
	{
		auto root = getRoot();
		auto path = getPath();
		if (m_v.get_type() == v.get_type())
		{
			m_v = v;
			root->ValueChanged.invoke({ root, path, v });
		}
		else
		{
			bool bEqual = false;
			try {
				bEqual = m_v == v;
			}
			catch (...) {
				nbThrowException(std::logic_error, "should set for [%s] with [%s] but not [%s].", getAbsPath().data(), m_v.get_type().get_name().data(), v.get_type().get_name().data());
			}

			if (!bEqual)
			{
				m_v = v;
				root->ValueChanged.invoke({ root, path, v });
			}
		}
	}
	virtual var get() const override { return m_v; }

	virtual const std::type_info &type() const override { return typeid(T); }

	static std::shared_ptr<DataVar<T>> gen(const std::string &name, const T &v = T())
	{
		return std::make_shared<DataVar<T>>(name, v);
	}

private:
	var	m_v;
};

class NB_API DataArray : public DataContext
{
public:
	DataArray(const std::string &name);

	void setTemplate(DataObjectPtr temp);

	const DataObjectPtr &getTemplate() const;

	void addItem(DataObjectPtr item);

	void removeItem(std::size_t index);

	DataObjectPtr item(std::size_t index);

	size_t itemCount() const;

	static std::shared_ptr<DataArray> gen(const std::string &name);

private:
	std::vector<DataObjectPtr>	m_items;
	DataObjectPtr				m_template;
};

}

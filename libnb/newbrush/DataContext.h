#pragma once
#include <map>
#include "newbrush/Object.h"
#include "newbrush/Event.h"
#include "newbrush/Types.h"

namespace nb{

class DataContext;
class DataObject;

class NB_API DataContext
{
public:
	virtual ~DataContext() = default;

	virtual void set(const var &value) &							{}
	virtual var get() const											{ return var(); }
	virtual ref<DataContext> lookup(const std::string &path) const	{ return nullptr; }
	virtual rttr::type type() const									{ return type::get<DataContext>(); }

	struct ValueChangedArgs { DataContext *root; std::string path; var value; };
	Event<ValueChangedArgs>	ValueChanged;
	
protected:
	DataContext(const std::string &_name) 
		: name(_name), parent(nullptr)
	{}

private:
	DataContext *getRoot() const
	{
		auto p = (DataContext *)this;
		while (p->parent && (p = p->parent)) {}
		return p;
	}

	std::string getPath(bool relative) const
	{
		std::string path;
		auto p = this;
		do
		{
			path = p->name + "." + path;
		} while (relative ? (p->parent && p->parent->parent && (p = p->parent)) : (p->parent && (p = p->parent)));
		path.pop_back();
		return path;
	}

	std::string	name;
	DataContext *parent;
	friend class DataObject;
	template<class T> friend class DataVar;
};

class NB_API DataObject : public DataContext
{
public:
	DataObject(const std::string &name) 
		: DataContext(name) 
	{}

	//添加一个子节点
	void add(ref<DataContext> child) &
	{
		nbThrowExceptionIf(!child, std::invalid_argument, "child is nullptr.");

		auto ret = m_children.insert({ child->name, child });
		nbThrowExceptionIf(!ret.second, std::runtime_error, "[%s] is already exists in [%s]", child->name.data(), this->name.data());
		child->parent = this;
	}

	//删除一个子节点
	void remove(const std::string & childName) &
	{
		auto iter = m_children.find(childName);
		if (iter != m_children.end())
		{
			m_children.erase(iter);
		}
	}

	//获取子节点，不存在返回空
	ref<DataContext> get(const std::string &childName) const
	{
		auto iter = m_children.find(childName);
		return iter == m_children.end() ? nullptr : iter->second;
	}

	ref<DataObject> getObject(const std::string &childName) const
	{
		return std::dynamic_pointer_cast<DataObject>(get(childName));
	}

	//按路径查询节点
	//path：形如"a.b.c"，表示查找基于当前节点下的a/b/c节点
	//找不到返回空
	virtual ref<DataContext> lookup(const std::string &path) const override
	{
		auto pathSegments = nb::stringSplit(path, ".", false);
		auto obj = this;
		for (int32_t i = 0; i != pathSegments.size(); ++i)
		{
			const std::string &sKey = pathSegments[i];
			if (i == pathSegments.size() - 1)
			{
				return obj->get(sKey);
			}
			else
			{
				obj = obj->getObject(sKey).get();
				if (!obj)
					return nullptr;
			}
		}
		return nullptr;
	}

	virtual rttr::type type() const override { return type::get<DataObject>(); }

private:
	std::map<std::string, ref<DataContext>>	m_children;
};

template<class T>
class DataVar : public DataContext
{
public:
	DataVar(const std::string &name, const T &v = T()) 
		: DataContext(name) , m_v(v) 
	{}

	virtual void set(const var &value) & override
	{
		auto root = getRoot();
		auto path = getPath(true);
		auto thisType = m_v.get_type();
		auto valueType = value.get_type();
		if (thisType == valueType)
		{
			m_v = value;
			root->ValueChanged.invoke({ root, path, m_v });
		}
		else
		{
			var fixSetValue = value;
			bool ok = fixSetValue.convert(rttr::type(thisType));
			nbThrowExceptionIf(!ok, std::logic_error, "setValueNodes for [%s] must be type [%s] instead of [%s], or check if has a converter from [%s] to [%s]", 
				getPath(false).data(), thisType.get_name().data(), valueType.get_name().data(), thisType.get_name().data(), valueType.get_name().data());

			bool bEqual = m_v == fixSetValue;
			if (!bEqual)
			{
				m_v = fixSetValue;
				root->ValueChanged.invoke({ root, path, m_v });
			}
		}
	}
	virtual var get() const override { return m_v; }

	virtual rttr::type type() const override { return type::get<T>(); }
	
private:
	var	m_v;
};

class NB_API DataArray : public DataContext
{
public:
	DataArray(const std::string &name) : DataContext(name) {}

	void setTemplate(ref<DataObject> temp) 
	{
		nbThrowExceptionIf(!temp, std::invalid_argument, "temp is nullptr.");
		m_template = temp;
	}

	const ref<DataObject> &getTemplate() const { return m_template; }

	void addItem(ref<DataObject> item) { m_items.push_back(item); }

	void removeItem(std::size_t index) 
	{
		nbThrowExceptionIf(index >= itemCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)itemCount());
		m_items.erase(m_items.begin() + index);
	}

	ref<DataObject> item(std::size_t index)
	{
		nbThrowExceptionIf(index >= itemCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)itemCount());
		return m_items[index];
	}

	size_t itemCount() const { return m_items.size(); }

private:
	std::vector<ref<DataObject>>	m_items;
	ref<DataObject>				m_template;
};

using DataBool = DataVar<bool>;
using DataInt = DataVar<int32_t>;
using DataFloat = DataVar<float>;
using DataDouble = DataVar<double>;
using DataString = DataVar<std::string>;

template<class T>
static ref<DataVar<T>> makeDataVar(const std::string &name, const T &value = T())
{
	return createRef<DataVar<T>>(name, value);
}
static ref<DataBool> makeDataBool(const std::string &name, bool v = false)
{
	return makeDataVar<bool>(name, v);
}
static ref<DataInt> makeDataInt(const std::string &name, int32_t v = 0)
{
	return makeDataVar<int>(name, v);
}
static ref<DataFloat> makeDataFloat(const std::string &name, float v = 0.0f)
{
	return makeDataVar<float>(name, v);
}
static ref<DataDouble> makeDataDouble(const std::string &name, double v = 0.0)
{
	return makeDataVar<double>(name, v);
}
static ref<DataString> makeDataString(const std::string &name, const std::string &v = std::string())
{
	return makeDataVar<std::string>(name, v);
}

static ref<DataObject> makeDataObject(const std::string &name)
{
	return createRef<DataObject>(name);
}

static ref<DataArray> makeDataArray(const std::string &name) 
{
	return createRef<DataArray>(name);
}

static ref<DataVar<Color>> makeDataColor(const std::string &name, const Color &v = Colors::white)
{
	return makeDataVar<Color>(name, v);
}

static ref<DataVar<glm::vec2>> makeDataVec2(const std::string &name, const glm::vec2 &v = glm::vec2())
{
	return makeDataVar<glm::vec2>(name, v);
}
static ref<DataVar<glm::vec3>> makeDataVec3(const std::string &name, const glm::vec3 &v = glm::vec3())
{
	return makeDataVar<glm::vec3>(name, v);
}
static ref<DataVar<glm::vec4>> makeDataVec4(const std::string &name, const glm::vec4 &v = glm::vec4())
{
	return makeDataVar<glm::vec4>(name, v);
}
}

#pragma once
#include "newbrush/Event.h"
#include "newbrush/DataContext.h"
#include "newbrush/Object.h"

namespace nb{

//数据流方向
enum class BindingModeE
{
	OneTime,		//仅一次
	OneWayToTarget,	//单向到目标
	OneWayToSource,	//单向到源
	TwoWay,			//双向
};

class NB_API Binding : public std::enable_shared_from_this<Binding>, public Object
{
public:
	Binding();
	Binding(const std::string &path);
	Binding(ref<DataContext> _source, const std::string &_path, BindingModeE _mode = BindingModeE::OneWayToTarget);
	~Binding();

	std::string path;
	BindingModeE mode;

	//源
	void setSource(ref<DataContext> source);
	ref<DataContext> source() const { return m_source; }

	struct BindDataChangedEventArgs { ref<Binding> sender; var value; };
	Event<BindDataChangedEventArgs> BindDataChanged;

private:
	int m_handle;
	ref<DataContext> m_source;
};

class NB_API BindingMaster
{
public:
	//添加一个绑定
	//target：目标依赖对象，可以是UI元素或非UI元素
	static void addBinding(ref<Object> target, const property &prop, ref<Binding> bd);

	//清除所有绑定
	static void clear();

private:
	static void setToTarget(ref<Object> target, const property &prop, const var &value);
};

}
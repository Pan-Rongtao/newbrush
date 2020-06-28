#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/Event.h"

namespace nb{

//数据流方向
enum class BindingModeE
{
	OneTime,		//仅一次
	OneWayToTarget,	//单向到目标
	OneWayToSource,	//单向到源
	TwoWay,			//双向
};

class DataContext;
using DataContextPtr = std::shared_ptr<DataContext>;
class NB_API Binding
{
public:
	Binding();
	Binding(const std::string &path);
	Binding(DataContextPtr source, const std::string &path, BindingModeE mode = BindingModeE::OneWayToTarget);
	~Binding() = default;

	//数据流方向模式
	void setMode(BindingModeE mode) &;
	BindingModeE mode() const;

	//源
	void setSource(DataContextPtr source) &;
	DataContextPtr source() const;

	//属性路径
	void setPath(const std::string &path) &;
	std::string path() const;

	struct BindDataChangedEventArgs { var value; };
	Event<BindDataChangedEventArgs> BindDataChanged;

private:
	BindingModeE	m_mode;
	DataContextPtr	m_source;
	std::string		m_path;
};

}
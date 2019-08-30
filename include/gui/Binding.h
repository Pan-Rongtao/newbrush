#pragma once
#include "../gui/Property.h"
#include "../gui/DataContext.h"

namespace nb{
namespace gui{
	
class NB_API Binding
{
public:
	//据流方向
	enum class ModeE
	{
		OneTime,		//仅一次
		OneWayToTarget,	//单向到目标
		OneWayToSource,	//单向到源
		TwoWay,			//双向
	};

	Binding();
	Binding(const std::string &path);
	Binding(DataContextPtr source, const std::string &path, ModeE mode = ModeE::OneWayToTarget);
	~Binding() = default;

	//数据流方向模式
	void setMode(ModeE mode);
	ModeE mode() const;

	//源
	void setSource(DataContextPtr source);
	DataContextPtr source() const;

	//属性路径
	void setPath(const std::string &path);
	std::string path() const;

private:
	ModeE			m_mode;
	DataContextPtr	m_source;
	std::string		m_path;
};

using BindingPtr = std::shared_ptr<Binding>;

}}
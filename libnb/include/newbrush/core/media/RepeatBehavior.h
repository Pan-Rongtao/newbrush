#pragma once
#include "newbrush/core/TimeSpan.h"

namespace nb{

class NB_API RepeatBehavior
{
public:
	//构建一个次数循环器
	//异常：std::out_of_range
	RepeatBehavior(float count);

	//构建一个时间循环器
	//异常：ts为负值
	RepeatBehavior(const TimeSpan &duration);

	//构建次数循环器
	static RepeatBehavior fromCount(float count);

	//构建时间段循环器
	static RepeatBehavior fromDuration(const TimeSpan &duration);

	//构建永久循环器
	static RepeatBehavior forever();

	//是否是永久循环
	bool isForever() const;

	//获取循环次数
	//异常：std::logic_error，不是一个次数循环器
	bool hasCount() const;
	float getCount() const;

	//获取时间长度
	//如果不是时间循环器，返回false
	bool hasDuration() const;
	TimeSpan getDuration() const;

	bool operator ==(const RepeatBehavior &other) const;
	bool operator !=(const RepeatBehavior &other) const;

private:
	enum class Type : char
	{
		Counter,
		Duration,
		Forever,
	};

	Type		m_type;
	float		m_count;
	TimeSpan	m_duration;
};

}
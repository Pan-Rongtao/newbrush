#pragma once
#include "../core/Event.h"
#include "../core/Any.h"
#include "../core/DependencyProperty.h"
#include "../core/EffectiveValueEntry.h"

namespace nb {

class NB_API DependencyObject
{
public:
	//设置属性值
	//如果未存储有该属性的值，则当value与defaultValue不相等时，插入新存储
	//反之已经存储该属性的值，当value与defaultValue相等，移除该存储，否则更新该值
	template<class T>
	void set(const DependencyProperty &dp, const T &value)
	{
		auto metadata = dp.defaultMetadata();
		if (metadata.type() != typeid(value))
		{
			nbThrowException(std::logic_error, "value must be type of [%s]", dp.defaultValue().type().name());
		}

		auto iter = m_valueEntrys.find(dp.globalIndex());
		bool bValueEqualDefault = any_cast<T>(metadata->defaultValue());
		if (iter == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys[dp.globalIndex()] = newEntry;
				onPropertyChanged({dp, metadata->defaultValue(), value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iter);
			}
			else
			{
				iter->second.setBaseValue(value);
				onPropertyChanged({ dp, metadata->defaultValue(), value });
			}
		}
	}

	//获取属性值
	//如果未存储有该属性的值，则返回defaultValue
	//反之，返回该存储值
	template<class T>
	T getValue(const DependencyProperty &dp) const
	{
		auto iter = m_valueEntrys.find(dp.globalIndex());
		if (iter == m_valueEntrys.end())
		{
			return dp.defaultValue();
		}
		else
		{
			return any_cast<T>(iter->second.baseValue());
		}
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}
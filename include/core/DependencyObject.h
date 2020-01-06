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
	void set(const DependencyProperty &dp, const T &value) &
	{
		if (dp.propertyType() != typeid(value))
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
		}

		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		auto bValueEqualDefault = any_cast<T>(defaultValue) == value;
		if (iterFind == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys.insert({ dp.globalIndex(), newEntry });
				onPropertyChanged({dp, defaultValue, value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iterFind);
			}
			else
			{
				iterFind->second.setBaseValue(value);
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
	}

	template<>
	void set<const char *>(const DependencyProperty &dp, const char* const&value) &
	{
		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto bValueEqualDefault = false;
		if (dp.propertyType() == typeid(std::string))
		{
			bValueEqualDefault = any_cast<std::string>(defaultValue) == value;
		}
		else if (dp.propertyType() == typeid(const char *))
		{
			bValueEqualDefault = strcmp(any_cast<const char *>(defaultValue), value) == 1 ? true : false;
		}
		else
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
		}

		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		if (iterFind == m_valueEntrys.end())
		{
			if (!bValueEqualDefault)
			{
				EffectiveValueEntry newEntry(dp);
				newEntry.setBaseValue(value);
				m_valueEntrys.insert({ dp.globalIndex(), newEntry });
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
		else
		{
			if (bValueEqualDefault)
			{
				m_valueEntrys.erase(iterFind);
			}
			else
			{
				iterFind->second.setBaseValue(value);
				onPropertyChanged({ dp, defaultValue, value });
			}
		}
	}

	//待优化：未比较值是否相等
	template<>
	void set<Any>(const DependencyProperty &dp, const Any &value) &
	{
		if (dp.propertyType() != typeid(value))
		{
			nbThrowException(std::logic_error, "value must be a [%s] type", dp.propertyType().name());
		}

		auto defaultValue = dp.defaultMetadata()->defaultValue();
		auto iterFind = m_valueEntrys.find(dp.globalIndex());
		if (iterFind == m_valueEntrys.end())
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(value);
			m_valueEntrys.insert({ dp.globalIndex(), newEntry });
			onPropertyChanged({ dp, defaultValue, value });
		}
		else
		{
			iterFind->second.setBaseValue(value);
			onPropertyChanged({ dp, defaultValue, value });
		}
	}


	//获取属性值
	//如果未存储有该属性的值，则返回defaultValue
	//反之，返回该存储值
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		auto iter = m_valueEntrys.find(dp.globalIndex());
		if (iter == m_valueEntrys.end())
		{
			return any_cast<T>(dp.defaultMetadata()->defaultValue());
		}
		else
		{
			auto x = iter->second.baseValue();
			return any_cast<T>(x);
		}
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}
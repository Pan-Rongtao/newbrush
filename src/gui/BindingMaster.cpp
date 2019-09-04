#include "gui/BindingMaster.h"
#include "gui/DependencyObject.h"

using namespace nb::gui;

std::map<BindingPtr, std::pair<DependencyObjectPtr, DependencyProperty>>	BindingMaster::g_bindingmap;

#ifdef NB_OS_FAMILY_WINDOWS
#pragma warning(push)
#pragma warning(disable : 4800) // forcing value to bool 'true' or 'false' (performance warning)
#endif
template<class T>
void syncTargetValueData(DependencyObjectPtr target, const DependencyProperty & dp, ValueDataBasePtr bindingData)
{
	if (bindingData->type() == typeid(int8_t))			target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<int8_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(int16_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<int16_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(int32_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<int32_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(int64_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<int64_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(uint8_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<uint8_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(uint16_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<uint16_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(uint32_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<uint32_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(uint64_t))	target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<uint64_t>>(bindingData)->get());
	else if (bindingData->type() == typeid(bool))		target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<bool>>(bindingData)->get());
	else if (bindingData->type() == typeid(float))		target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<float>>(bindingData)->get());
	else if (bindingData->type() == typeid(double))		target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<double>>(bindingData)->get());
	else if (bindingData->type() == typeid(long))		target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<long>>(bindingData)->get());
	else if (bindingData->type() == typeid(unsigned long))		target->set<T>(dp, (T)std::dynamic_pointer_cast<ValueData<unsigned long>>(bindingData)->get());
	else nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", bindingData->type().name(), dp.defaultValue().type().name());
}

#ifdef NB_OS_FAMILY_WINDOWS
#pragma warning(pop)
#endif

void BindingMaster::addBinding(DependencyObjectPtr target, const DependencyProperty & dp, BindingPtr bd)
{
	auto source = std::dynamic_pointer_cast<ObjectData>(bd->source());
	auto path = bd->path();
	auto valueNode = std::dynamic_pointer_cast<ValueDataBase>(source->lookup(path));
	if (!valueNode)
		nbThrowException(std::runtime_error, "binding data must be a value type, check soure.path[%s]", path.data());
	valueNode->ValueChanged += std::bind(&BindingMaster::onBingingDataChanged, std::placeholders::_1);
	g_bindingmap.insert(std::make_pair(bd, std::make_pair(target, dp)));
}

void BindingMaster::onBingingDataChanged(const ValueDataBase::ValueChangedArgs & args)
{
	auto iter = std::find_if(g_bindingmap.begin(), g_bindingmap.end(), [&args](const std::pair<BindingPtr, std::pair<DependencyObjectPtr, DependencyProperty>> &p)
	{
		return p.first->source() == args.root && p.first->path() == args.path;
	});

	if(iter != g_bindingmap.end())
	{
		auto binding = iter->first;
		auto bindingData = std::dynamic_pointer_cast<ValueDataBase>(std::dynamic_pointer_cast<ObjectData>(binding->source())->lookup(binding->path()));
		auto target = iter->second.first;
		auto dp = iter->second.second;
		auto propertyDefaultValue = dp.defaultValue();

		if (propertyDefaultValue.type() == bindingData->type())		target->set(dp, bindingData->getAny());
		else if (propertyDefaultValue.type() == typeid(int8_t))		syncTargetValueData<int8_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(int16_t))	syncTargetValueData<int16_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(int32_t))	syncTargetValueData<int32_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(int64_t))	syncTargetValueData<int64_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(uint8_t))	syncTargetValueData<uint8_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(uint16_t))	syncTargetValueData<uint16_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(uint32_t))	syncTargetValueData<uint32_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(uint64_t))	syncTargetValueData<uint64_t>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(bool))		syncTargetValueData<bool>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(float))		syncTargetValueData<float>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(double))		syncTargetValueData<double>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(long))		syncTargetValueData<long>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(unsigned long))	syncTargetValueData<unsigned long>(target, dp, bindingData);
		else if (propertyDefaultValue.type() == typeid(std::string))
		{
			std::string s;
			if (bindingData->type() == typeid(int8_t))			s = std::to_string(std::dynamic_pointer_cast<ValueData<int8_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(int16_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<int16_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(int32_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<int32_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(int64_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<int64_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(uint8_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<uint8_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(uint16_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<uint16_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(uint32_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<uint32_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(uint64_t))	s = std::to_string(std::dynamic_pointer_cast<ValueData<uint64_t>>(bindingData)->get());
			else if (bindingData->type() == typeid(bool))		s = std::to_string(std::dynamic_pointer_cast<ValueData<bool>>(bindingData)->get());
			else if (bindingData->type() == typeid(float))		s = std::to_string(std::dynamic_pointer_cast<ValueData<float>>(bindingData)->get());
			else if (bindingData->type() == typeid(double))		s = std::to_string(std::dynamic_pointer_cast<ValueData<double>>(bindingData)->get());
			else if (bindingData->type() == typeid(long))		s = std::to_string(std::dynamic_pointer_cast<ValueData<long>>(bindingData)->get());
			else if (bindingData->type() == typeid(unsigned long))s = std::to_string(std::dynamic_pointer_cast<ValueData<unsigned long>>(bindingData)->get());
			else nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", bindingData->type().name(), propertyDefaultValue.type().name());
			target->set(dp, s);
		}
		else
		{
			nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", bindingData->type().name(), propertyDefaultValue.type().name());
		}
	}
}

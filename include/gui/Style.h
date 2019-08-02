#pragma once
#include <vector>
#include "../core/Def.h"
#include "../core/Any.h"
#include "../core/Property.h"

namespace nb {
namespace gui {

class NB_API Setter
{
public:
	std::string		propertyName;
	core::Any		propertyValue;
};

class NB_API Trigger
{
public:
	std::string			propertyName;
	std::vector<Setter>	setters;
};

class NB_API Style
{
public:
	Style(const std::size_t &tagetTypeHash);


	core::Property_rw<std::shared_ptr<Style>>					BaseOn;
	core::Property_rw<std::vector<std::shared_ptr<Setter>>>		Setters;
	core::Property_rw<std::vector<std::shared_ptr<Trigger>>>	Triggers;
//	core::Property_rw<

private:
	std::size_t		m_tagetTypeHash;
};

}
}
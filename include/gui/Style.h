#pragma once
#include <vector>
#include "../core/Def.h"
#include "../core/Any.h"
#include "../gui/Property.h"

namespace nb {
namespace gui {

class NB_API Setter
{
public:
	std::string		propertyName;
	Any				propertyValue;
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
	Style();


	Property_rw<std::shared_ptr<Style>>					BaseOn;
	Property_rw<std::vector<std::shared_ptr<Setter>>>	Setters;
	Property_rw<std::vector<std::shared_ptr<Trigger>>>	Triggers;
//	Property_rw<

private:
	std::size_t		m_tagetTypeHash;
};

}
}
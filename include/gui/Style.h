#pragma once
#include <vector>
#include <typeindex>
#include "../gui/Setter.h"
#include "../gui/Trigger.h"

namespace nb{
namespace gui{

class NB_API Style
{
public:
	Style();
	
	Property_rw<std::type_index>						TragetType;
	Property_rw<std::shared_ptr<Style>>					BaseOn;
	Property_rw<std::vector<std::shared_ptr<Setter>>>	Setters;
	Property_rw<std::vector<std::shared_ptr<Trigger>>>	Triggers;
//	Property_rw<

private:
	std::size_t		m_tagetTypeHash;
};

}
}
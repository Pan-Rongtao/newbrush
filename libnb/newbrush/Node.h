#pragma once
#include "newbrush/Object.h"

namespace nb 
{

class NB_API Node : public Object
{
	RTTR_ENABLE(Object)
public:
	Node();
	Node(const std::string &name);

	void setName(const std::string &name);
	const std::string &getName() const;
	
	virtual void onRender() {}

private:
	std::string m_name;
};

}
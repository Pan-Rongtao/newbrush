#pragma once
#include "newbrush/Object.h"

namespace nb 
{

class NB_API Node : public Object
{
	RTTR_ENABLE(Object)
public:
	Node()											{}
	Node(const std::string &name) : m_name(name)	{}

	void setName(const std::string &name)			{ m_name = name; }
	const std::string &getName() const				{ return m_name; }
	
	virtual void onRender()							{}

private:
	std::string m_name;
};

}
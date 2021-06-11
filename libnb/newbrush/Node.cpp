#include "newbrush/Node.h"

using namespace nb;

Node::Node()
	: Node("")
{}

Node::Node(const std::string &name)
	: m_name(name)
{
}

void Node::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Node::getName() const
{
	return m_name;
}

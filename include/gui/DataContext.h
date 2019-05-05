#pragma once
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"

namespace nb{ namespace core{

template<class T>
class DataContext
{
public:
	DataContext();

private:
	Poco::JSON::Object	m_root;
};

}}
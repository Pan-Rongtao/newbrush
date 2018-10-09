#pragma once
#include <vector>
#include "core/String.h"

namespace nb{ namespace media{

class ImageSources_Internal
{
public:
	void pushBack(const nb::core::String &source);
	void insert(int index, const nb::core::String &source);
	void remove(int index);
	void clear();
	int count() const;

	const nb::core::String &operator [] (int index) const;

	void set(const std::vector<nb::core::String> &sources);
	void get(std::vector<nb::core::String> &ret) const;


private:
	std::vector<nb::core::String>	m_Sources;
};

}}

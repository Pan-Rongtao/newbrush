#pragma once
#include <vector>
#include "system/String.h"

namespace nb{ namespace Media{

class ImageSources_Internal
{
public:
	void PushBack(const nb::System::String &source);
	void Insert(int index, const nb::System::String &source);
	void Remove(int index);
	void Clear();
	int GetCount() const;

	const nb::System::String &operator [] (int index) const;

	void Set(const std::vector<nb::System::String> &sources);
	void Get(std::vector<nb::System::String> &ret) const;


private:
	std::vector<nb::System::String>	m_Sources;
};

}}

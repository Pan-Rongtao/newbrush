#include "gui/WindowCollection.h"

using namespace nb;

void nb::WindowCollection::push(gui::Window * w)
{
	m_windows.push_back(w);
}

void nb::WindowCollection::erase(gui::Window * w)
{
	auto iter = std::find(m_windows.begin(), m_windows.end(), w);
	if (iter != m_windows.end())
	{
		m_windows.erase(iter);
	}
}

std::vector<gui::Window*>& nb::WindowCollection::windows()
{
	return m_windows;
}

gui::Window * nb::WindowCollection::operator[](size_t index)
{
	if(index >= m_windows.size())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, m_windows.size());
	return m_windows[index];
}

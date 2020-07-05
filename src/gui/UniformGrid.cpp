#include "newbrush/gui/UniformGrid.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

UniformGrid::UniformGrid()
{
}

DependencyPropertyPtr UniformGrid::RowsProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("Rows", -1, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UniformGrid::ColumnsProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("Columns", -1, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UniformGrid::FirstColumnProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("FirstColumn", -1, nullptr, nullptr, nullptr);
	return dp;
}

Size UniformGrid::measureOverride(const Size & availableSize)
{
	auto rowsColums = calcRowsColums();
	auto cellWidth = availableSize.width() / rowsColums.second;
	auto cellHeight = availableSize.height() / rowsColums.first;
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		child->measure(Size(cellWidth, cellHeight));
	}
	return availableSize;
}

Size UniformGrid::arrangeOverride(const Size & finalSize)
{
	auto rowsColums = calcRowsColums();
	auto cellWidth = finalSize.width() / rowsColums.second;
	auto cellHeight = finalSize.height() / rowsColums.first;
	auto cols = getValue<int>(ColumnsProperty());
	auto firstColumn = getValue<int>(FirstColumnProperty());
	auto firstCol = (cols < 0 || firstColumn < 0 || firstColumn >= cols) ? 0 : firstColumn;
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto row = (i + firstCol) % rowsColums.second;
		auto col = (i + firstCol) / rowsColums.second;
		auto x = row * cellWidth;
		auto y = col * cellHeight;
		child->arrage(Rect(x, y, cellWidth, cellHeight));
	}
	return finalSize;
}

std::pair<int, int> UniformGrid::calcRowsColums() const
{
	std::pair<int, int> ret;
	auto rows = getValue<int>(RowsProperty());
	auto cols = getValue<int>(ColumnsProperty());
	if (rows <= 0)
	{
		if (cols <= 0)
		{
			ret.first = (int)std::ceil(sqrt(m_children.count()));
			ret.second = ret.first;
		}
		else
		{
			ret.second = cols;
			ret.first = (int)std::ceil(m_children.count() / (double)cols);
		}
	}
	else
	{
		ret.first = rows;
		if (cols <= 0)
		{
			ret.second = (int)std::ceil(m_children.count() / (double)rows);
		}
		else
		{
			ret.second = cols;
		}
	}
	return ret;
}

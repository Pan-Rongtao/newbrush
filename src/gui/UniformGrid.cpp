#include "gui/UniformGrid.h"

using namespace nb;
using namespace nb::gui;

UniformGrid::UniformGrid()
	: Rows([&](int v) {set(RowsProperty(), v); }, [&]()->int& {return get<int>(RowsProperty()); })
	, Columns([&](int v) {set(ColumnsProperty(), v); }, [&]()->int& {return get<int>(ColumnsProperty()); })
	, FirstColumn([&](int v) {set(FirstColumnProperty(), v); }, [&]()->int& {return get<int>(FirstColumnProperty()); })
{
}

DependencyProperty UniformGrid::RowsProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("Rows", -1);
	return dp;
}

DependencyProperty UniformGrid::ColumnsProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("Columns", -1);
	return dp;
}

DependencyProperty UniformGrid::FirstColumnProperty()
{
	static auto dp = DependencyProperty::registerDependency<UniformGrid, int>("FirstColumn", -1);
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
	auto firstCol = (Columns() < 0 || FirstColumn() < 0 || FirstColumn() >= Columns()) ? 0 : FirstColumn();
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
	int32_t rows, cols;
	if (Rows() <= 0)
	{
		if (Columns() <= 0)
		{
			rows = (int)std::ceil(sqrt(m_children.count()));
			cols = rows;
		}
		else
		{
			cols = Columns();
			rows = (int)std::ceil(m_children.count() / (double)cols);
		}
	}
	else
	{
		rows = Rows();
		if (Columns() <= 0)
		{
			cols = (int)std::ceil(m_children.count() / (double)rows);
		}
		else
		{
			cols = Columns();
		}
	}
	return{ rows, cols };
}

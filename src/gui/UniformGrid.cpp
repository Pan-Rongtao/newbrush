#include "gui/UniformGrid.h"

using namespace nb::core;
using namespace nb::gui;

UniformGrid::UniformGrid()
	: Rows(-1)
	, Columns(-1)
	, FirstColumn(-1)
{
}

Size UniformGrid::measureOverride(const nb::core::Size & availableSize)
{
	auto rowsColums = calcRowsColums();
	auto cellWidth = availableSize.width() / rowsColums.second;
	auto cellHeight = availableSize.height() / rowsColums.first;
	for (auto child : Children())
	{
		child->measure(Size(cellWidth, cellHeight));
	}
	return availableSize;
}

Size UniformGrid::arrangeOverride(const nb::core::Size & finalSize)
{
	auto rowsColums = calcRowsColums();
	auto cellWidth = finalSize.width() / rowsColums.second;
	auto cellHeight = finalSize.height() / rowsColums.first;
	auto firstCol = (Columns < 0 || FirstColumn < 0 || FirstColumn >= Columns) ? 0 : FirstColumn();
	for (auto i = 0u; i != Children().size(); ++i)
	{
		auto child = Children()[i];
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
	if (Rows <= 0)
	{
		if (Columns <= 0)
		{
			rows = std::ceil(sqrt(Children().size()));
			cols = rows;
		}
		else
		{
			cols = Columns;
			rows = std::ceil(Children().size() / (double)cols);
		}
	}
	else
	{
		rows = Rows;
		if (Columns <= 0)
		{
			cols = std::ceil(Children().size() / (double)rows);
		}
		else
		{
			cols = Columns;
		}
	}
	return{ rows, cols };
}

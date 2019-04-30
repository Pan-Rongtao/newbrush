#include "gui/Grid.h"

using namespace nb::core;
using namespace nb::gui;

Grid::Grid(void)
{
}

Grid::~Grid(void)
{
}

void Grid::setRow(int row, std::shared_ptr<UIElement> element)
{
}

int Grid::getRow(std::shared_ptr<UIElement> element)
{
	return 0;
}

void Grid::setColumn(int col, std::shared_ptr<UIElement> element)
{
}

int Grid::getColumn(std::shared_ptr<UIElement> element)
{
	return 0;
}

void Grid::setRowSpan(std::shared_ptr<UIElement> element, int value)
{
}

int Grid::getRowSpan(std::shared_ptr<UIElement> element)
{
	return 0;
}

void Grid::setColumnSpan(std::shared_ptr<UIElement> element, int value)
{
}

int Grid::getColumnSpan(std::shared_ptr<UIElement> element)
{
	return 0;
}

Size Grid::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Grid::arrangeOverride(const Size & finalSize)
{
	return Size();
}

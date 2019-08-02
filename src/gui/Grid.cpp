#include "gui/Grid.h"
#include "gui/DependencyProperty.h"
#include <numeric>

using namespace nb::core;
using namespace nb::gui;

GridLength::GridLength()
	: m_type(GridUnitType::Pixcel)
	, m_value(0.0)
{
}

GridLength::GridLength(float value)
	: m_type(GridUnitType::Pixcel)
	, m_value(value)
{
}

GridLength::GridLength(float value, GridUnitType type)
	: m_type(type)
	, m_value(value)
{
}

bool GridLength::operator==(const GridLength & other) const
{
	return !(operator !=(other));
}

bool GridLength::operator!=(const GridLength & other) const
{
	return m_type != other.m_type || m_value != other.m_value;
}

bool GridLength::isAuto() const
{
	return m_type == GridUnitType::Auto;
}

bool GridLength::isStar() const
{
	return m_type == GridUnitType::Star;
}

float GridLength::value() const
{
	return m_value;
}

GridLength::GridUnitType GridLength::gridUnitType() const
{
	return m_type;
}

GridLength GridLength::automate()
{
	return GridLength(0.0, GridUnitType::Auto);
}

RowDefinition::RowDefinition()
	: Height(GridLength(1.0f, GridLength::GridUnitType::Star))
{
}

RowDefinition::~RowDefinition()
{
}

ColumnDefinition::ColumnDefinition()
	: Width(GridLength(1.0f, GridLength::GridUnitType::Star))
{
}

ColumnDefinition::~ColumnDefinition()
{
}

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::setRow(std::shared_ptr<UIElement> element, uint32_t row)
{
	if ((row > 0 && row < RowDefinitions().size()) && std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		DependencyProperty::registerAttached(element, AttachedPropertyRow, row);
	}
}

uint32_t Grid::getRow(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRow);
	return v.empty() ? 0 : any_cast<uint32_t>(v);
}

void Grid::setColumn(std::shared_ptr<UIElement> element, uint32_t col)
{
	if ((col > 0 && col < ColumnDefinitions().size()) && std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		DependencyProperty::registerAttached(element, AttachedPropertyColumn, col);
	}
}

uint32_t Grid::getColumn(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyColumn);
	return v.empty() ? 0 : any_cast<uint32_t>(v);
}

void Grid::setRowSpan(std::shared_ptr<UIElement> element, uint32_t rowSpan)
{
	if ((rowSpan >= 1 && rowSpan <= RowDefinitions().size()) && std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		DependencyProperty::registerAttached(element, AttachedPropertyRowSpan, rowSpan);
	}
}

uint32_t Grid::getRowSpan(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRowSpan);
	return v.empty() ? 1 : any_cast<uint32_t>(v);
}

void Grid::setColumnSpan(std::shared_ptr<UIElement> element, uint32_t colSpan)
{
	if ((colSpan <= ColumnDefinitions().size()) && std::find(Children().begin(), Children().end(), element) != Children().end() && colSpan >= 1)
	{
		DependencyProperty::registerAttached(element, AttachedPropertyColumnSpan, colSpan);
	}
}

uint32_t Grid::getColumnSpan(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyColumnSpan);
	return v.empty() ? 1 : any_cast<uint32_t>(v);
}

//规则：每次根据RowDefinitions和ColumnDefinitions把每个网格单元的像素尺寸计算出来：
//根据每个望各单元的长度类型GridUnitType，如果是Pixcel，则直接保存；如果是Auto，则取该行/列中的最大元素；如果是Star，则换算成Pixcel
//所有单元格尺寸都保存在m_pixcelWidthsForEachCols和m_pixcelHeightsForEachRows中，在arrangeOverride中会用到
Size Grid::measureOverride(const Size & availableSize)
{
	auto calcPixcelLenghts = [&](bool isRowdefinition)->std::vector<float>
	{
		auto rows = RowDefinitions().size();
		auto cols = ColumnDefinitions().size();
		std::vector<float> rowOrColUnitsPixcelLenghts(isRowdefinition ? rows : cols, NAN);
		auto verifiedCount = 0u;
		//第一次循环把非Start的像素长度确定下来
		for (auto i = 0u; i != rowOrColUnitsPixcelLenghts.size(); ++i)
		{
			auto lenght = isRowdefinition ? RowDefinitions()[i]->Height() : ColumnDefinitions()[i]->Width();
			switch (lenght.gridUnitType())
			{
			case GridLength::GridUnitType::Pixcel:
			{
				rowOrColUnitsPixcelLenghts[i] = lenght.value();	
				++verifiedCount;
				break; 
			}
			case GridLength::GridUnitType::Auto:
			{
				auto maxLenghtOfRowOrCol = 0.0f;
				for (auto child : Children())
				{
					auto childRowOrCol = isRowdefinition ? getRow(child) : getColumn(child);
					auto x = isRowdefinition ? (std::isnan(child->Height()) ? 0.0f : child->Height()) : (std::isnan(child->Height()) ? 0.0f : child->Height());
					if(childRowOrCol == i && x > maxLenghtOfRowOrCol)
						maxLenghtOfRowOrCol = x;
				}
				rowOrColUnitsPixcelLenghts[i] = maxLenghtOfRowOrCol;
				++verifiedCount;
			}
			break;
			default:	continue;	break;
			}
		}
		//如果第一次循环中遗留有Star类型的GridLenght，计算出它们的pixcel值
		if (verifiedCount < rowOrColUnitsPixcelLenghts.size())
		{
			float verifiedLeghtPixcels = 0.0f;									//已经计算的像素长度和
			float remainStars = 0.0f;											//剩余Start和
			float remainPixcels = 0.0f;											//剩余像素和
			for (auto i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (!std::isnan(rowOrColUnitsPixcelLenghts[i]))
					verifiedLeghtPixcels += rowOrColUnitsPixcelLenghts[i];
				else
				{
					auto lenght = isRowdefinition ? RowDefinitions()[i]->Height() : ColumnDefinitions()[i]->Width();
					remainStars += lenght.value();
				}
			}
			remainPixcels = isRowdefinition ? (availableSize.height() - verifiedLeghtPixcels) : (availableSize.width() - verifiedLeghtPixcels);
			//计算每个Star类型Lenght对应的像素值
			for (auto i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (std::isnan(rowOrColUnitsPixcelLenghts[i]))
				{
					rowOrColUnitsPixcelLenghts[i] = isRowdefinition ? (RowDefinitions()[i]->Height().value() / remainStars * remainPixcels) : 
						(ColumnDefinitions()[i]->Width().value() / remainStars * remainPixcels);
				}
			}
		}
		return rowOrColUnitsPixcelLenghts;
	};

	//计算出所有网格单元的像素宽高，并测量children
	m_pixcelWidthsForEachCols = calcPixcelLenghts(false);
	m_pixcelHeightsForEachRows = calcPixcelLenghts(true);
	for (auto child : Children())
	{
		auto rowOfChild = getRow(child);
		auto colOfChild = getColumn(child);
		auto rowSpan = getRowSpan(child);
		auto colSpan = getColumnSpan(child);
		auto w = std::accumulate(m_pixcelWidthsForEachCols.begin() + colOfChild, m_pixcelWidthsForEachCols.begin() + colOfChild + rowSpan, 0.0f);
		auto h = std::accumulate(m_pixcelHeightsForEachRows.begin() + rowOfChild, m_pixcelHeightsForEachRows.begin() + rowOfChild + colSpan, 0.0f);

		child->measure(Size(w, h));
	}

	auto w = std::accumulate(m_pixcelWidthsForEachCols.begin(), m_pixcelWidthsForEachCols.end(), 0.0f);
	auto h = std::accumulate(m_pixcelHeightsForEachRows.begin(), m_pixcelHeightsForEachRows.end(), 0.0f);
	return Size(w, h);
}

//以m_pixcelWidthsForEachCols和m_pixcelHeightsForEachRows对Children进行arrage
Size Grid::arrangeOverride(const Size & finalSize)
{
	for (auto child : Children())
	{
		auto rowOfChild = getRow(child);
		auto colOfChild = getColumn(child);
		rowOfChild = nb::clamp<int>(0, RowDefinitions().size(), rowOfChild);
		colOfChild = nb::clamp<int>(0u, ColumnDefinitions().size(), colOfChild);
		auto rowSpan = getRowSpan(child);
		auto colSpan = getColumnSpan(child);
		auto x = std::accumulate(m_pixcelWidthsForEachCols.begin(), m_pixcelWidthsForEachCols.begin() + colOfChild, 0.0f);
		auto y = std::accumulate(m_pixcelHeightsForEachRows.begin(), m_pixcelHeightsForEachRows.begin() + rowOfChild, 0.0f);
		auto w = std::accumulate(m_pixcelWidthsForEachCols.begin() + colOfChild, m_pixcelWidthsForEachCols.begin() + colOfChild + rowSpan, 0.0f);
		auto h = std::accumulate(m_pixcelHeightsForEachRows.begin() + rowOfChild, m_pixcelHeightsForEachRows.begin() + rowOfChild + colSpan, 0.0f);

		child->arrage(Rect(x, y, w, h));
	}
	return finalSize;
}

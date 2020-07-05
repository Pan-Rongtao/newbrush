#include "newbrush/gui/Grid.h"
#include "newbrush/core/DependencyProperty.h"
#include <numeric>

using namespace nb;

GridLength::GridLength()
	: GridLength(GridUnitType::Pixcel, 0.0)
{
}

GridLength::GridLength(float value)
	: GridLength(GridUnitType::Pixcel, value)
{
}

GridLength::GridLength(GridUnitType type, float value)
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

GridUnitType GridLength::gridUnitType() const
{
	return m_type;
}

GridLength GridLength::automate()
{
	return GridLength(GridUnitType::Auto, 0.0);
}

RowDefinition::RowDefinition()
{
}

DependencyPropertyPtr RowDefinition::HeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("Height", GridLength(GridUnitType::Star, 1.0));
	return dp;
}

DependencyPropertyPtr RowDefinition::MinHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("MinHeight", 0.0);
	return dp;
}

DependencyPropertyPtr RowDefinition::MaxHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("MaxHeight", GridLength(std::numeric_limits<float>::max()));
	return dp;
}

DependencyPropertyPtr RowDefinition::ActualHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, float>("MaxHeight", 0.0);
	return dp;
}

ColumnDefinition::ColumnDefinition()
{
}

DependencyPropertyPtr ColumnDefinition::WidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("Width", GridLength(GridUnitType::Star, 1.0));
	return dp;
}

DependencyPropertyPtr ColumnDefinition::MinWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("MinWidth", GridLength(0.0));
	return dp;
}

DependencyPropertyPtr ColumnDefinition::MaxWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("MaxWidth", GridLength(std::numeric_limits<float>::max()));
	return dp;
}

DependencyPropertyPtr ColumnDefinition::ActualWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, float>("ActualWidth", 0.0);
	return dp;
}

Grid::Grid()
{
}

DependencyPropertyPtr Grid::RowDefinitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Grid, std::vector<RowDefinitionPtr>>("RowDefinitions", {});
	return dp;
}

DependencyPropertyPtr Grid::ColumnDefinitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency <Grid, std::vector<ColumnDefinitionPtr>>("ColumnDefinitions", {});
	return dp;
}

DependencyPropertyPtr Grid::RowProperty()
{
	static auto dp = DependencyProperty::registerAttached<Grid, uint32_t>("Row", 0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Grid::ColumnProperty()
{
	static auto dp = DependencyProperty::registerAttached<Grid, uint32_t>("Column", 0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Grid::RowSpanProperty()
{
	static auto dp = DependencyProperty::registerAttached<Grid, uint32_t>("RowSpan", 1, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Grid::ColumnSpanProperty()
{
	static auto dp = DependencyProperty::registerAttached<Grid, uint32_t>("ColumnSpan", 1, nullptr, nullptr, nullptr);
	return dp;
}

void Grid::setRow(UIElementPtr element, uint32_t row)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(RowProperty(), row);
}

uint32_t Grid::getRow(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue(RowProperty()).get_value<uint32_t>();
}

void Grid::setColumn(UIElementPtr element, uint32_t col)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(ColumnProperty(), col);
}

uint32_t Grid::getColumn(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue(ColumnProperty()).get_value<uint32_t>();
}

void Grid::setRowSpan(UIElementPtr element, uint32_t rowSpan)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(RowSpanProperty(), rowSpan);
}

uint32_t Grid::getRowSpan(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue(RowSpanProperty()).get_value<uint32_t>();
}

void Grid::setColumnSpan(UIElementPtr element, uint32_t colSpan)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(ColumnSpanProperty(), colSpan);
}

uint32_t Grid::getColumnSpan(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue(ColumnSpanProperty()).get_value<uint32_t>();
}

//规则：每次根据RowDefinitions和ColumnDefinitions把每个网格单元的像素尺寸计算出来：
//根据每个望各单元的长度类型GridUnitType，如果是Pixcel，则直接保存；如果是Auto，则取该行/列中的最大元素；如果是Star，则换算成Pixcel
//所有单元格尺寸都保存在m_pixcelWidthsForEachCols和m_pixcelHeightsForEachRows中，在arrangeOverride中会用到
Size Grid::measureOverride(const Size & availableSize)
{
	auto calcPixcelLenghts = [&](bool isRowdefinition)->std::vector<float>
	{
		auto rowDefinitions = getValue<std::vector<RowDefinitionPtr>>(RowDefinitionsProperty());
		auto colDefinitions = getValue<std::vector<ColumnDefinitionPtr>>(ColumnDefinitionsProperty());
		std::vector<float> rowOrColUnitsPixcelLenghts(isRowdefinition ? rowDefinitions.size() : colDefinitions.size(), NAN);
		auto verifiedCount = 0u;
		//第一次循环把非Start的像素长度确定下来
		for (auto i = 0u; i != rowOrColUnitsPixcelLenghts.size(); ++i)
		{
			auto lenght = isRowdefinition ? rowDefinitions[i]->getValue<GridLength>(RowDefinition::HeightProperty()) : colDefinitions[i]->getValue<GridLength>(ColumnDefinition::WidthProperty());
			switch (lenght.gridUnitType())
			{
			case GridUnitType::Pixcel:
			{
				rowOrColUnitsPixcelLenghts[i] = lenght.value();	
				++verifiedCount;
				break; 
			}
			case GridUnitType::Auto:
			{
				auto maxLenghtOfRowOrCol = 0.0f;
				for (auto j = 0u; j < m_children.count(); ++j)
				{
					auto child = m_children.childAt(j);
					auto childRowOrCol = isRowdefinition ? getRow(child) : getColumn(child);
					auto childHeight = child->getValue<float>(HeightProperty());
					auto x = isRowdefinition ? (std::isnan(childHeight) ? 0.0f : childHeight) : (std::isnan(childHeight) ? 0.0f : childHeight);
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
			for (size_t i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (!std::isnan(rowOrColUnitsPixcelLenghts[i]))
				{
					verifiedLeghtPixcels += rowOrColUnitsPixcelLenghts[i];
				}
				else
				{
					auto rowDefinitions = getValue<std::vector<RowDefinitionPtr>>(RowDefinitionsProperty());
					auto colDefinitions = getValue<std::vector<ColumnDefinitionPtr>>(ColumnDefinitionsProperty());
					auto lenght = isRowdefinition ? (i < rowDefinitions.size() ? rowDefinitions[i]->getValue<GridLength>(RowDefinition::HeightProperty()) : 0.0) 
						: (i < colDefinitions.size() ? colDefinitions[i]->getValue<GridLength>(ColumnDefinition::WidthProperty()) : 0.0);
					remainStars += lenght.value();
				}
			}
			remainPixcels = isRowdefinition ? (availableSize.height() - verifiedLeghtPixcels) : (availableSize.width() - verifiedLeghtPixcels);
			//计算每个Star类型Lenght对应的像素值
			for (size_t i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (std::isnan(rowOrColUnitsPixcelLenghts[i]))
				{
					auto rowDefinitions = getValue<std::vector<RowDefinitionPtr>>(RowDefinitionsProperty());
					auto colDefinitions = getValue<std::vector<ColumnDefinitionPtr>>(ColumnDefinitionsProperty());
					auto rowHeight = i < rowDefinitions.size() ? rowDefinitions[i]->getValue<GridLength>(RowDefinition::HeightProperty()) : 0.0;
					auto colWidth = i < colDefinitions.size() ? colDefinitions[i]->getValue<GridLength>(ColumnDefinition::WidthProperty()) : 0.0;
					rowOrColUnitsPixcelLenghts[i] = isRowdefinition ? (rowHeight.value() / remainStars * remainPixcels) :
						(colWidth.value() / remainStars * remainPixcels);
				}
			}
		}
		//如果为空，表示未定义行集合或列集合
		if (rowOrColUnitsPixcelLenghts.empty())
		{
			rowOrColUnitsPixcelLenghts.push_back(isRowdefinition ? availableSize.height() : availableSize.width());
		}
		return rowOrColUnitsPixcelLenghts;
	};

	//计算出所有网格单元的像素宽高，并测量children
	m_pixcelWidthsForEachCols = calcPixcelLenghts(false);
	m_pixcelHeightsForEachRows = calcPixcelLenghts(true);
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto rowOfChild = getRow(child);
		auto colOfChild = getColumn(child);
		auto rowSpan = getRowSpan(child);
		auto colSpan = getColumnSpan(child);
		auto actualRowSpan = rowOfChild + rowSpan <= m_pixcelHeightsForEachRows.size() ? rowSpan : m_pixcelHeightsForEachRows.size() - rowOfChild;
		auto actualColSpan = colOfChild + colSpan <= m_pixcelWidthsForEachCols.size() ? colSpan : m_pixcelHeightsForEachRows.size() - colOfChild;
		auto w = std::accumulate(m_pixcelWidthsForEachCols.begin() + colOfChild, m_pixcelWidthsForEachCols.begin() + colOfChild + actualColSpan, 0.0f);
		auto h = std::accumulate(m_pixcelHeightsForEachRows.begin() + rowOfChild, m_pixcelHeightsForEachRows.begin() + rowOfChild + actualRowSpan, 0.0f);

		child->measure(Size(w, h));
	}

	auto w = std::accumulate(m_pixcelWidthsForEachCols.begin(), m_pixcelWidthsForEachCols.end(), 0.0f);
	auto h = std::accumulate(m_pixcelHeightsForEachRows.begin(), m_pixcelHeightsForEachRows.end(), 0.0f);
	return Size(w, h);
}

//以m_pixcelWidthsForEachCols和m_pixcelHeightsForEachRows对Children进行arrage
Size Grid::arrangeOverride(const Size & finalSize)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto rowOfChild = getRow(child);
		auto colOfChild = getColumn(child);
		auto rowDefinitions = getValue<std::vector<RowDefinitionPtr>>(RowDefinitionsProperty());
		auto colDefinitions = getValue<std::vector<ColumnDefinitionPtr>>(ColumnDefinitionsProperty());
		rowOfChild = clamp<int>(0, rowDefinitions.size(), rowOfChild);
		colOfChild = clamp<int>(0u, colDefinitions.size(), colOfChild);
		auto rowSpan = getRowSpan(child);
		auto colSpan = getColumnSpan(child);
		auto actualRowSpan = rowOfChild + rowSpan <= m_pixcelHeightsForEachRows.size() ? rowSpan : m_pixcelHeightsForEachRows.size() - rowOfChild;
		auto actualColSpan = colOfChild + colSpan <= m_pixcelWidthsForEachCols.size() ? colSpan : m_pixcelHeightsForEachRows.size() - colOfChild;
		auto x = std::accumulate(m_pixcelWidthsForEachCols.begin(), m_pixcelWidthsForEachCols.begin() + colOfChild, 0.0f);
		auto y = std::accumulate(m_pixcelHeightsForEachRows.begin(), m_pixcelHeightsForEachRows.begin() + rowOfChild, 0.0f);
		auto w = std::accumulate(m_pixcelWidthsForEachCols.begin() + colOfChild, m_pixcelWidthsForEachCols.begin() + colOfChild + actualColSpan, 0.0f);
		auto h = std::accumulate(m_pixcelHeightsForEachRows.begin() + rowOfChild, m_pixcelHeightsForEachRows.begin() + rowOfChild + actualRowSpan, 0.0f);

		child->arrage(Rect(x, y, w, h));
	}
	return finalSize;
}

UIElementPtr Grid::clone() const
{
	return std::make_shared<Grid>(*this);
}

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

DependencyProperty RowDefinition::HeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("Height", GridLength(GridUnitType::Star, 1.0));
	return dp;
}

DependencyProperty RowDefinition::MinHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("MinHeight", 0.0);
	return dp;
}

DependencyProperty RowDefinition::MaxHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, GridLength>("MaxHeight", GridLength(std::numeric_limits<float>::max()));
	return dp;
}

DependencyProperty RowDefinition::ActualHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<RowDefinition, float>("MaxHeight", 0.0);
	return dp;
}

ColumnDefinition::ColumnDefinition()
{
}

DependencyProperty ColumnDefinition::WidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("Width", GridLength(GridUnitType::Star, 1.0));
	return dp;
}

DependencyProperty ColumnDefinition::MinWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("MinWidth", GridLength(0.0));
	return dp;
}

DependencyProperty ColumnDefinition::MaxWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, GridLength>("MaxWidth", GridLength(std::numeric_limits<float>::max()));
	return dp;
}

DependencyProperty ColumnDefinition::ActualWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<ColumnDefinition, float>("ActualWidth", 0.0);
	return dp;
}

Grid::Grid()
{
}

DependencyProperty Grid::RowDefinitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Grid, std::vector<std::shared_ptr<RowDefinition>>>("RowDefinitions", {});
	return dp;
}

DependencyProperty Grid::ColumnDefinitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency <Grid, std::vector<std::shared_ptr<ColumnDefinition>>>("ColumnDefinitions", {});
	return dp;
}

void Grid::setRow(std::shared_ptr<UIElement> element, uint32_t row)
{
	auto rows = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty()).size();
	if ((row > 0 && row < rows) && m_children.contains(element))
	{
		DependencyProperty::registerAttached(element, AttachedPropertyRow, row);
	}
}

uint32_t Grid::getRow(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRow);
	return v.isEmpty() ? 0 : v.extract<uint32_t>();
}

void Grid::setColumn(std::shared_ptr<UIElement> element, uint32_t col)
{
	auto cols = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty()).size();
	if ((col > 0 && col < cols) && m_children.contains(element))
	{
		DependencyProperty::registerAttached(element, AttachedPropertyColumn, col);
	}
}

uint32_t Grid::getColumn(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyColumn);
	return v.isEmpty() ? 0 : v.extract<uint32_t>();
}

void Grid::setRowSpan(std::shared_ptr<UIElement> element, uint32_t rowSpan)
{
	auto rows = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty()).size();
	if ((rowSpan >= 1 && rowSpan <= rows) && m_children.contains(element))
	{
		DependencyProperty::registerAttached(element, AttachedPropertyRowSpan, rowSpan);
	}
}

uint32_t Grid::getRowSpan(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRowSpan);
	return v.isEmpty() ? 1 : v.extract<uint32_t>();
}

void Grid::setColumnSpan(std::shared_ptr<UIElement> element, uint32_t colSpan)
{
	auto cols = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty()).size();
	if ((colSpan <= cols) && colSpan >= 1 && m_children.contains(element))
	{
		DependencyProperty::registerAttached(element, AttachedPropertyColumnSpan, colSpan);
	}
}

uint32_t Grid::getColumnSpan(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyColumnSpan);
	return v.isEmpty() ? 1 : v.extract<uint32_t>();
}

//规则：每次根据RowDefinitions和ColumnDefinitions把每个网格单元的像素尺寸计算出来：
//根据每个望各单元的长度类型GridUnitType，如果是Pixcel，则直接保存；如果是Auto，则取该行/列中的最大元素；如果是Star，则换算成Pixcel
//所有单元格尺寸都保存在m_pixcelWidthsForEachCols和m_pixcelHeightsForEachRows中，在arrangeOverride中会用到
Size Grid::measureOverride(const Size & availableSize)
{
	auto calcPixcelLenghts = [&](bool isRowdefinition)->std::vector<float>
	{
		auto rowDefinitions = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty());
		auto colDefinitions = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty());
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
			for (auto i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (!std::isnan(rowOrColUnitsPixcelLenghts[i]))
				{
					verifiedLeghtPixcels += rowOrColUnitsPixcelLenghts[i];
				}
				else
				{
					auto rowDefinitions = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty());
					auto colDefinitions = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty());
					auto lenght = isRowdefinition ? (i < rowDefinitions.size() ? rowDefinitions[i]->getValue<GridLength>(RowDefinition::HeightProperty()) : 0.0) 
						: (i < colDefinitions.size() ? colDefinitions[i]->getValue<GridLength>(ColumnDefinition::WidthProperty()) : 0.0);
					remainStars += lenght.value();
				}
			}
			remainPixcels = isRowdefinition ? (availableSize.height() - verifiedLeghtPixcels) : (availableSize.width() - verifiedLeghtPixcels);
			//计算每个Star类型Lenght对应的像素值
			for (auto i = 0; i != rowOrColUnitsPixcelLenghts.size(); ++i)
			{
				if (std::isnan(rowOrColUnitsPixcelLenghts[i]))
				{
					auto rowDefinitions = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty());
					auto colDefinitions = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty());
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
		auto rowDefinitions = getValue<std::vector<std::shared_ptr<RowDefinition>>>(RowDefinitionsProperty());
		auto colDefinitions = getValue<std::vector<std::shared_ptr<ColumnDefinition>>>(ColumnDefinitionsProperty());
		rowOfChild = nb::clamp<int>(0, rowDefinitions.size(), rowOfChild);
		colOfChild = nb::clamp<int>(0u, colDefinitions.size(), colOfChild);
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

EditorInfo Grid::getEditorInfo()
{
	EditorInfo info;
	info.id = typeid(Grid).hash_code();
	std::string s = typeid(Grid).name();
	auto n = s.rfind(':');
	if (n == std::string::npos)
	{
		n = s.rfind(' ');
	}
	info.name = s.substr(n + 1);
	info.description = "网格，一种对子元素进行网格化管理的布局容器";
	return info;
}

std::shared_ptr<UIElement> Grid::clone() const
{
	return std::make_shared<Grid>(*this);
}

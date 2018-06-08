#include "GridPrivate.h"
#include "core/TypesPropertyValuesStore.h"
#include "core/Type.h"
#include "gui/Grid.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::System;

GridPrivate::GridPrivate(Grid *owner)
	: m_owner(owner)
{
}

GridPrivate::~GridPrivate(void)
{
}

void GridPrivate::SetRow(UIElement *element, int row)
{
	Type *pType = Type::GetType<Grid>();
//	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("Row"), Int(row));
	element->GetTypesPropertyValuesStore()->SaveRefValue(pType, Grid::RowProperty(), new aInt(row));
}

void GridPrivate::SetCol(UIElement *element, int col)
{
	Type *pType = Type::GetType<Grid>();
//	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("Col"), Int(col));
	element->GetTypesPropertyValuesStore()->SaveRefValue(pType, Grid::ColProperty(), new aInt(col));
}

int GridPrivate::GetRow(UIElement *element)
{
	Type *pType = Type::GetType<Grid>();
//	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("Row"));
//	const Int & x =  dynamic_cast<const Int &>(v);
//	return x.m_value;

	aInt *x = dynamic_cast<aInt *>(element->GetTypesPropertyValuesStore()->GetRefValue(pType, Grid::RowProperty()));
	if(x == NULL) return -1;
	return *x;
}

int GridPrivate::GetCol(UIElement *element)
{
	Type *pType = Type::GetType<Grid>();
//	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("Col"));
//	const Int & x =  dynamic_cast<const Int &>(v);
//	return x.m_value;

	aInt *x = dynamic_cast<aInt *>(element->GetTypesPropertyValuesStore()->GetRefValue(pType, Grid::ColProperty()));
	if(x == NULL) return -1;
	return *x;
}

bool GridPrivate::IsSetRow(UIElement *element)
{
	Type *pType = Type::GetType<Grid>();
//	return element->GetTypesPropertyValuesStore()->IsSavedValue(pType, pType->GetExternalProperty("Row"));
	return element->GetTypesPropertyValuesStore()->IsSavedValue(pType, Grid::RowProperty());
}

bool GridPrivate::IsSetCol(UIElement *element)
{
	Type *pType = Type::GetType<Grid>();
//	return element->GetTypesPropertyValuesStore()->IsSavedValue(pType, pType->GetExternalProperty("Col"));
	return element->GetTypesPropertyValuesStore()->IsSavedValue(pType, Grid::ColProperty());
}

int GridPrivate::GetElementActualRow(UIElement *element, int rows) const
{
	int row = IsSetRow(element) ? GetRow(element) : 0;
	if(row >= rows) row = rows - 1;
	return row;
}

int GridPrivate::GetElementActualCol(UIElement *element, int cols) const
{
	int col = IsSetCol(element) ? GetCol(element) : 0;
	if(col >= cols) col = cols - 1;
	return col;
}

RowDefinition * GridPrivate::GetElementActualRowDefinition(UIElement *element, RowDefinitionCollection * rds) const
{
	int row = GetElementActualRow(element, rds->GetCount());
	if(row < 0) return GetDefaultRowDefinition();
	else return rds->GetAt(row);
}

ColDefinition * GridPrivate::GetElementActualColDefinition(UIElement *element, ColDefinitionCollection * cds) const
{
	int col = GetElementActualCol(element, cds->GetCount());
	if(col < 0) return GetDefaultColDefinition();
	else return cds->GetAt(col);
}

RowDefinition * GridPrivate::GetDefaultRowDefinition() const
{
	if(m_defaultRowDefinition == NULL)
	{
		GridPrivate *pThis = const_cast<GridPrivate *>(this);
		pThis->m_defaultRowDefinition = new RowDefinition();
		pThis->m_defaultRowDefinition->Height() = GridLength(1, GridLength::UnitType_Star);
	}

	return m_defaultRowDefinition;
}

ColDefinition * GridPrivate::GetDefaultColDefinition() const
{
	if(m_defaultColDefinition == NULL)
	{
		GridPrivate *pThis = const_cast<GridPrivate *>(this);
		pThis->m_defaultColDefinition = new ColDefinition();
		pThis->m_defaultColDefinition->Width() = GridLength(1, GridLength::UnitType_Star);
	}

	return m_defaultColDefinition;
}

nb::System::Size GridPrivate::MeasureWork(const nb::System::Size &availableSize)
{
	//int tick = GetTickCount();
//for(int kkk=0; kkk<100; kkk++)
//{
	float allHeight = availableSize.GetHeight();
	float allWidth = availableSize.GetWidth();

	bool isInfiniteWidth = availableSize.GetWidth() >= 1.0e12;
	bool isInfiniteHeight = availableSize.GetHeight() >= 1.0e12;


	RowDefinitionCollection *rds = m_owner->RowDefCollection;
	ColDefinitionCollection *cds = m_owner->ColDefCollection;

	// 清除所有的RowDefinition的ActualHeight，并统计所有Star标记RowDefinition的合计值，以及设置固定值行的ActualHeight = gl.Value
	GetDefaultRowDefinition()->SetActualHeight(availableSize.Height());
	int rows = rds->GetCount();
	float allRowStar = 0.0;
	for(int i=0; i<rows; i++)
	{
		RowDefinition *rd = rds->GetAt(i);
		rd->SetActualHeight(0);
		const GridLength &gl = rd->Height();
		if(gl.IsStar()) allRowStar += gl.GetValue();
		else if(!gl.IsAuto()) allHeight -= IncreaseRowDefinitionActualHeightTo(rd, gl.GetValue());
	}

	// 清除所有的ColDefinition的ActualWidth，并统计所有Star标记ColDefinition的合计值，以及设置固定值列的ActualWidth = gl.Value
	GetDefaultColDefinition()->SetActualWidth(availableSize.Width());
	int cols = cds->GetCount();
	float allColStar = 0.0;
	for(int i=0; i<cols; i++)
	{
		ColDefinition *cd = cds->GetAt(i);
		cd->SetActualWidth(0);
		const GridLength &gl = cd->Width();
		if(gl.IsStar()) allColStar += gl.GetValue();
		else if(!gl.IsAuto()) allWidth -= IncreaseColDefinitionActualWidthTo(cd, gl.GetValue());
	}

	UIElementArray &children = *(m_owner->Children());
	int count = children.GetCount();

	// 为所有的Auto行设置最小的高度，所有的Auto列设置最小的宽度
	for(int i=0; i<count; i++)
	{
		UIElement *element = children[i];
		if(!element->Height().IsNull() && rows > 0) // 假如行数为零，使用默认行，默认行的GridLength为Star
		{
			int row = GetElementActualRow(element, rows);
			RowDefinition *rd = rds->GetAt(row);
			const GridLength &rgl = rd->Height();

			if(rgl.IsAuto())
			{
				float v = (Float)element->Height();
				allHeight -= IncreaseRowDefinitionActualHeightTo(rd, v);
			}
		}

		if(!element->Width().IsNull() && cols > 0) // 假如行数为零，使用默认列，默认列的GridLength为Star
		{
			int col = GetElementActualCol(element, cols);
			ColDefinition *cd = cds->GetAt(col);
			const GridLength &cgl = cd->Width();

			if(cgl.IsAuto())
			{
				float v = (Float)element->Width();
				allWidth -= IncreaseColDefinitionActualWidthTo(cd, v);
			}
		}
	}


	// 第一次循环，处理掉所有的非Star的行列，并对allHeight减去所处理行的高度，allWidth减去所处理的宽度
	// 只有当行数和列数都大于零时，才进入，否则，必然是行或列为 Star类型
	if(rows > 0 && cols > 0)
	{
		for(int i=0; i<count; i++)
		{
			UIElement *element = children[i];
			int row = IsSetRow(element) ? GetRow(element) : 0;
			int col = IsSetCol(element) ? GetCol(element) : 0;

			RowDefinition *rd = (row < 0 ? NULL : rds->GetAt(row));
			ColDefinition *cd = (col < 0 ? NULL : cds->GetAt(col));

			const GridLength &rgl = rd->Height();
			const GridLength &cgl = cd->Width();

			if(rgl.IsStar() || cgl.IsStar())
			{
				continue;
			}

			float height = (rgl.IsAuto() ? 1.0e30 : height = rgl.GetValue());
			float width = (cgl.IsAuto() ? 1.0e30 : cgl.GetValue());

			element->Measure(width, height);
			const nb::System::Size &sz = element->GetDesiredSize();

			allHeight -= IncreaseRowDefinitionActualHeightTo(rd, sz.GetHeight());
			allWidth -= IncreaseColDefinitionActualWidthTo(cd, sz.GetWidth());
		}
	}

	// 计算标记为Star的列的宽度
	for(int i=0; i<cols; i++)
	{
		ColDefinition *cd = cds->GetAt(i);
		const GridLength &cgl = cd->Width();
		if(cgl.IsStar())
		{
			if(allWidth <= 0)
			{
				cd->SetActualWidth(0);
			}
			else
			{
				float f = (allColStar == 0 ? 0 : cgl.GetValue() / allColStar * allWidth);
				cd->SetActualWidth(f);
			}
		}
	}

	//第二次循环，处理列标志位是Star但行标志不是Star的对应的元素
	double colStarRate = 0.0;
	for(int i=0; i<count; i++)
	{
		UIElement *element = children[i];

		RowDefinition *rd = GetElementActualRowDefinition(element, rds);
		ColDefinition *cd = GetElementActualColDefinition(element, cds);

		const GridLength &rgl = rd->Height();
		const GridLength &rgc = cd->Width();

		if(rgl.IsStar()) continue;
		if(!rgc.IsStar()) continue;

		float height = (rgl.IsAuto() ? 1.0e30 : height = rgl.GetValue());
		float width = cd->GetActualWidth();

		element->Measure(width, height);
		const nb::System::Size &sz = element->GetDesiredSize();

		double f = sz.Width() / width;
		if(colStarRate < f) colStarRate = f;

		allHeight -= IncreaseRowDefinitionActualHeightTo(rd, sz.GetHeight());
	}

	// 计算标记为Star的行的高度
	for(int i=0; i<rows; i++)
	{
		RowDefinition *rd = rds->GetAt(i);
		const GridLength &rgl = rd->Height();
		if(rgl.IsStar())
		{
			if(allHeight <= 0)
			{
				rd->SetActualHeight(0);
			}
			else
			{
				float f = (allRowStar == 0 ? 0 : rgl.GetValue() / allRowStar * allHeight);
				rd->SetActualHeight(f);
			}
		}
	}

//Star一个单元多个元素的情况尚未处理

	// 第三次循环，处理行标志位Star的行对应的元素
	double rowStarRate = 0.0;
	for(int i=0; i<count; i++)
	{
		UIElement *element = children[i];
		int row = IsSetRow(element) ? GetRow(element) : 0;
		int col = IsSetCol(element) ? GetCol(element) : 0;

		RowDefinition *rd = GetElementActualRowDefinition(element, rds);
		ColDefinition *cd = GetElementActualColDefinition(element, cds);

		const GridLength &rgl = rd->Height();
		if(!rgl.IsStar()) continue;

		float height = rd->GetActualHeight();
		float width = cd->GetActualWidth();

		element->Measure(width, height);
		const nb::System::Size &sz = element->GetDesiredSize();

		double f = sz.Height() / height;
		if(rowStarRate < f) rowStarRate = f;


		const GridLength &cgl = cd->Width();
		if(cgl.IsStar())
		{
			f = sz.Width() / width;
			if(colStarRate < f) colStarRate = f;
		}

		IncreaseColDefinitionActualWidthTo(cd, sz.Width());


/*		UIElement *element = GetChild(i);
		int row = IsSetRow(element) ? GetRow(element) : 0;

		RowDefinition *rd = rds->GetAt(row);

		const GridLength &gl = rd->Height();

		if(gl.IsStar())
		{
			float height = (allRowStar <= 0.0 ? 0.0 : gl.GetValue() / allRowStar * allHeight);

			element->Measure(availableSize.WidthR(), height);
		//	const nb::System::Size &sz = element->GetDesiredSize();
			rd->SetActualHeight(height);//sz.GetHeight());
		}*/
	}

	//按colStarRate比例调整star的列宽
	if(colStarRate < 1)
	{
		for(int i=0; i<cols; i++)
		{
			ColDefinition *cd = cds->GetAt(i);
			const GridLength &cgl = cd->Width();
			if(cgl.IsStar())
			{
				cd->SetActualWidth(colStarRate * cd->GetActualWidth());
			}
		}
	}

	//按rowStarRate比例调整star的行高
	if(rowStarRate < 1)
	{
		for(int i=0; i<rows; i++)
		{
			RowDefinition *rd = rds->GetAt(i);
			const GridLength &rgl = rd->Height();
			if(rgl.IsStar())
			{
				rd->SetActualHeight(rowStarRate * rd->GetActualHeight());
			}
		}
	}

//*/}tick = GetTickCount() - tick;

//	return Size(availableSize.Width() + (allWidth < 0 ? -allWidth : 0), 
//		availableSize.Height() + (allHeight < 0 ? -allHeight : 0));

	bool isSettedWidth = false, isSettedHeight = false;
	float gridWidth = 0, gridHeight = 0;
	if(m_owner->RowDefCollection->GetCount() == 0 || m_owner->ColDefCollection->GetCount() == 0)
	{
		float width = 0;
		float height = 0;
		for(int i=0; i<count; i++)
		{
			UIElement *element = children[i];
			const Size &sz = element->GetDesiredSize();
			if(width < sz.Width()) width = sz.Width();
			if(height < sz.Height()) height = sz.Height();
		}

		if(m_owner->RowDefCollection->GetCount() == 0)
		{
			if(isInfiniteHeight) GetDefaultRowDefinition()->SetActualHeight(height);
			gridHeight = height;
			isSettedHeight = true;
		}

		if(m_owner->ColDefCollection->GetCount() == 0)
		{
			if(isInfiniteWidth) GetDefaultColDefinition()->SetActualWidth(width);
			gridWidth = width;
			isSettedWidth = true;
		}
	}

	if(!isSettedWidth)
	{
		for(int i=0; i<cols; i++)
			gridWidth += m_owner->ColDefCollection->GetAt(i)->GetActualWidth();
	}

	if(!isSettedHeight)
	{
		for(int i=0; i<rows; i++)
			gridHeight += m_owner->RowDefCollection->GetAt(i)->GetActualHeight();
	}

	return Size(gridWidth, gridHeight);
}

nb::System::Size GridPrivate::ArrangeWork(const nb::System::Size &finalSize)
{
	RowDefinitionCollection *rds = m_owner->RowDefCollection;
	ColDefinitionCollection *cds = m_owner->ColDefCollection;

	int rows = rds->GetCount();

	//调整实际应用的高度值
	std::vector<float> rowsHeight;
	if(rows == 0)
	{
		rowsHeight.push_back(finalSize.Height());
	}
	else
	{
		int allHeight = finalSize.Height();
		double starTotal = 0;
		int starRowCount = 0;

		rowsHeight.resize(rows);
		for(int i=0; i<rows; i++)
		{
			const GridLength &rgl = rds->GetAt(i)->Height();
			if(!rgl.IsStar())
			{
				rowsHeight[i] = rds->GetAt(i)->GetActualHeight();
				allHeight -= rowsHeight[i];
			}
			else
			{
				starTotal += rgl.GetValue();
				starRowCount++;
			}
		}

		for(int i=0; i<rows; i++)
		{
			const GridLength &rgl = rds->GetAt(i)->Height();
			if(rgl.IsStar())
			{
				if(starTotal == 0) rowsHeight[i] = allHeight / starRowCount;
				else rowsHeight[i] = rgl.GetValue() / starTotal * allHeight;
			}
		}
	}


	std::vector<float> rowsPos;

//	if(finalSize.Width() != m_owner->GetDesignWidth() || finalSize.Height() != m_owner->GetDesignHeight())
//	{
//		int a = 0;
//		a++;
//	}

	if(rows == 0)
	{
		rowsPos.push_back(0);
	}
	else
	{
		rowsPos.resize(rows);
		float rPos = 0;
		for(int i=0; i<rows; i++)
		{
			rowsPos[i] = rPos;
			rPos += rowsHeight[i];
		}
	}

	int cols = cds->GetCount();



	//调整实际应用的宽度值
	std::vector<float> colsWidth;
	if(cols == 0)
	{
		colsWidth.push_back(finalSize.Width());
	}
	else
	{
		int allWidth = finalSize.Width();
		double starTotal = 0;
		int starColCount = 0;

		colsWidth.resize(cols);
		for(int i=0; i<cols; i++)
		{
			const GridLength &cgl = cds->GetAt(i)->Width();
			if(!cgl.IsStar())
			{
				colsWidth[i] = cds->GetAt(i)->GetActualWidth();
				allWidth -= colsWidth[i];
			}
			else
			{
				starTotal += cgl.GetValue();
				starColCount++;
			}
		}

		for(int i=0; i<cols; i++)
		{
			const GridLength &cgl = cds->GetAt(i)->Width();
			if(cgl.IsStar())
			{
				if(starTotal == 0) colsWidth[i] = allWidth / starColCount;
				else colsWidth[i] = cgl.GetValue() / starTotal * allWidth;
			}
		}
	}

	std::vector<float> colsPos;

	if(cols == 0)
	{
		colsPos.push_back(0);
	}
	else
	{
		colsPos.resize(cols);
		float cPos = 0;
		for(int i=0; i<cols; i++)
		{
			colsPos[i] = cPos;
			cPos += colsWidth[i];
		}
	}

//	float width = m_owner->GetDesignWidth();
//	float height = m_owner->GetDesignHeight();

	UIElementArray &children = *(m_owner->Children());

	int count = children.GetCount();
	for(int i=0; i<count; i++)
	{
		UIElement *element = children[i];
		int row = IsSetRow(element) ? GetRow(element) : 0;
		int col = IsSetCol(element) ? GetCol(element) : 0;
	//	RowDefinition *rd = GetElementActualRowDefinition(element, rds);
	//	ColDefinition *cd = GetElementActualColDefinition(element, cds);

	//	float h = rd->GetActualHeight();
	//	float w = cd->GetActualWidth();

		float h = rowsHeight[row];
		float w = colsWidth[col];

		element->Arrange(nb::System::Rect(colsPos[col], rowsPos[row], w, h));
	}

	return finalSize;//Panel::ArrangeOverride(finalSize);
}

float GridPrivate::IncreaseRowDefinitionActualHeightTo(RowDefinition *rd, float newHeight) const
{
	float old = rd->GetActualHeight();
	if(newHeight <= old) return 0;

	rd->SetActualHeight(newHeight);
	return newHeight - old;
}

float GridPrivate::IncreaseColDefinitionActualWidthTo(ColDefinition *cd, float newWidth) const
{
	float old = cd->GetActualWidth();
	if(newWidth <= old) return 0;

	cd->SetActualWidth(newWidth);
	return newWidth - old;
}

#pragma once

#include "gui/RowDefinitionCollection.h"
#include "gui/ColDefinitionCollection.h"
#include "system/Size.h"

namespace nb { namespace Gui {

class Grid;
class UIElement;
class GridPrivate
{
public:
	GridPrivate(Grid *owner);
	virtual ~GridPrivate(void);

	static void SetRow(UIElement *element, int row);
	static int GetRow(UIElement *element);

	static bool IsSetRow(UIElement *element);
	static bool IsSetCol(UIElement *element);

	static void SetCol(UIElement *element, int col);
	static int GetCol(UIElement *element);

	int GetElementActualRow(UIElement *element, int rows) const;
	int GetElementActualCol(UIElement *element, int cols) const;

	RowDefinition * GetDefaultRowDefinition() const;
	ColDefinition * GetDefaultColDefinition() const;

	nb::System::Size ArrangeWork(const nb::System::Size &finalSize);
	nb::System::Size MeasureWork(const nb::System::Size &availableSize);

	float IncreaseRowDefinitionActualHeightTo(RowDefinition *rd, float newHeight) const;
	float IncreaseColDefinitionActualWidthTo(ColDefinition *cd, float newWidth) const;

private:
	RowDefinition * GetElementActualRowDefinition(UIElement *element, RowDefinitionCollection * rds) const;
	ColDefinition * GetElementActualColDefinition(UIElement *element, ColDefinitionCollection * cds) const;

private:
	RowDefinitionPtr m_defaultRowDefinition;
	ColDefinitionPtr m_defaultColDefinition;

	Grid *m_owner;
};

}}

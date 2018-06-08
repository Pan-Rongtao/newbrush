/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 怀保胜

 * 编写日期: 2016-04

 * 简要描述:

 * 修改记录:

 *****************************************************************************/

#include "gui/StackPanel.h"
#include "system/System.h"
#include "core/TypesPropertyValuesStore.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(StackPanel, Panel, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(StackPanel, Orientation, nb::Core::EnumObject, NULL);

namespace nb
{ 
	namespace Gui
	{
		class StackPanelTypeProperties
		{
		public:
			StackPanelTypeProperties()
			{
				Core::DependencyProperty::PrepareExternalProperty("Orientation", typeid(StackPanel), typeid(Int), NULL);
			}
		} s_StackPanelTypeProperties;
	}
}

StackPanel::StackPanel()
{
}

StackPanel::~StackPanel()
{
}

nb::System::Size StackPanel::ArrangeOverride(const nb::System::Size &finalSize)
{
	nb::Gui::Orientation nOrientation = Orientation();
	int nChildCount = Children()->GetCount();//GetChildCount();
	nb::System::Size sDesiredSize(0.0 , 0.0);
	nb::System::Size nArrangeSize(0.0, 0.0);
	float fxPos = 0.0;
	float fyPos = 0.0;
	for(int i=0;i<nChildCount;i++)
	{
		UIElement *element  = Children()->GetAt(i);//GetChild(i);
		sDesiredSize = element->GetDesiredSize();
		if(nOrientation == nb::Gui::Orientation_Hor)
		{
			element->Arrange(nb::System::Rect(fxPos, fyPos, sDesiredSize));
			fxPos += sDesiredSize.Width();
			nArrangeSize.SetWidth(nArrangeSize.Width() + sDesiredSize.Width());
			nArrangeSize.SetHeight(nb::System::Max(nArrangeSize.Height(), sDesiredSize.Height()));
		}
		else if(nOrientation == nb::Gui::Orientation_Vert)
		{
			element->Arrange(nb::System::Rect(fxPos, fyPos, sDesiredSize));
			fyPos += sDesiredSize.Height();
			nArrangeSize.SetWidth(nb::System::Max(nArrangeSize.Width(), sDesiredSize.Width()));
			nArrangeSize.SetHeight(nArrangeSize.Height() + sDesiredSize.Height());
		}
		else
		{}
	}
	return nArrangeSize;
	//return Panel::ArrangeOverride(finalSize);
}


nb::System::Size StackPanel::MeasureOverride(const nb::System::Size &availableSize)
{
	nb::System::Size nDesiredSize(0.0, 0.0);
	nb::Gui::Orientation nOrientation = Orientation();
	int nChildCount = Children()->GetCount();//GetChildCount();
	for(int i=0;i<nChildCount;i++)
	{
		UIElement *element  = Children()->GetAt(i);//GetChild(i);
		if(nOrientation == nb::Gui::Orientation_Hor)
		{
			element->Measure(1.0e30, availableSize.Height());
			nb::System::Size sChildDesiredSize = element->GetDesiredSize();
			nDesiredSize.SetWidth(nDesiredSize.Width()+sChildDesiredSize.Width());
			nDesiredSize.SetHeight(nb::System::Max(nDesiredSize.Height(), sChildDesiredSize.Height()));
		}
		else if(nOrientation == nb::Gui::Orientation_Vert)
		{
			element->Measure(availableSize.Width(), 1.0e30);
			nb::System::Size sChildDesiredSize = element->GetDesiredSize();
			nDesiredSize.SetHeight(nDesiredSize.Height()+sChildDesiredSize.Height());
			nDesiredSize.SetWidth(nb::System::Max(nDesiredSize.Width(), sChildDesiredSize.Width()));
		}
		else
		{}
	}
	return nDesiredSize;
}

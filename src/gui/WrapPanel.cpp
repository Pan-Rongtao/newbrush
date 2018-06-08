/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 怀保胜

 * 编写日期: 2016-04

 * 简要描述:

 * 修改记录:

 *****************************************************************************/

#include "gui/WrapPanel.h"
#include "system/System.h"
#include "core/TypesPropertyValuesStore.h"
#include "WrapPanelPrivate.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;


NB_OBJECT_TYPE_IMPLEMENT(WrapPanel, Panel, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(WrapPanel, Orientation, nb::Core::EnumObject, NULL);


namespace nb
{ 
	namespace Gui
	{
		class WrapPanelTypeProperties
		{
		public:
			WrapPanelTypeProperties()
			{
				Core::DependencyProperty::PrepareExternalProperty("Orientation", typeid(WrapPanel), typeid(Int), NULL);
			}
		} s_WrapPanelTypeProperties;
	}
}
WrapPanel::WrapPanel()
{
	m_private = new WrapPanelPrivate(this);
}

WrapPanel::~WrapPanel()
{
	delete m_private;
}

WrapPanelPrivate * WrapPanel::GetPrivate()
{
	return m_private;
}

nb::System::Size WrapPanel::ArrangeOverride(const nb::System::Size &finalSize)
{
	return GetPrivate()->ArrangeWork(finalSize);
}

nb::System::Size WrapPanel::MeasureOverride(const nb::System::Size &availableSize)
{
	return GetPrivate()->MeasureWork(availableSize);
}

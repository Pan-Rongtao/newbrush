/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 怀保胜

 * 编写日期: 2016-04

 * 简要描述: 自动换行布局容器

			

 * 修改记录:

 *****************************************************************************/

#pragma once

#include "WrapPanel.h"
#include "system/Size.h"

namespace nb
{
	namespace Gui
	{
		class NB_EXPORT StackPanel : public Panel
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			StackPanel(void);
			virtual ~StackPanel(void);

			NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(Orientation, nb::Gui::Orientation);
			
		protected:
			virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);
			virtual System::Size MeasureOverride(const nb::System::Size &availableSize);
		};
		typedef nbObjectPtrDerive<StackPanel, PanelPtr> StackPanelPtr;
	}
}

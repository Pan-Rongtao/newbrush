/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 怀保胜

 * 编写日期: 2016-04

 * 简要描述: 自动换行布局容器

			

 * 修改记录:

 *****************************************************************************/

#pragma once

#include "Panel.h"
#include "system/Size.h"

namespace nb
{
	namespace Gui
	{
		enum Orientation
		{
			Orientation_Hor = 0x00,
			Orientation_Vert
		};

		class WrapPanelPrivate;
		class NB_EXPORT WrapPanel : public Panel
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			WrapPanel(void);
			virtual ~WrapPanel(void);

			WrapPanelPrivate *GetPrivate();

			NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(Orientation, nb::Gui::Orientation);

		protected:
			virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);
			virtual System::Size MeasureOverride(const nb::System::Size &availableSize);
		private:
			WrapPanelPrivate *m_private;
		};
		typedef nbObjectPtrDerive<WrapPanel, PanelPtr> WrapPanelPtr;
	}
}

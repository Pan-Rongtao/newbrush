/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-04

 * 简要描述: 通过SetTop()和SetLeft()来设置Canvas控件下面的元素放置的位置
		

 * 修改记录:

 *****************************************************************************/

#pragma once
#include "Panel.h"
#include "system/Size.h"


namespace nb
{
	namespace Gui
	{
		class NB_EXPORT Canvas : public Panel
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			Canvas(void);
			virtual ~Canvas(void);

			static void SetTop(UIElement *element, float fTopLength);
			static float GetTop(UIElement *element);

			static void SetBottom(UIElement *element, float fBottomLength);
			static float GetBottom(UIElement *element);

			static void SetLeft(UIElement *element, float fLeftLength);
			static float GetLeft(UIElement *element);

			static void SetRight(UIElement *element, float fRightLength);
			static float GetRight(UIElement *element);


		protected:
			virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);
			virtual System::Size MeasureOverride(const nb::System::Size &availableSize);
		};
		typedef nbObjectPtrDerive<Canvas, PanelPtr> CanvasPtr;
	}
}

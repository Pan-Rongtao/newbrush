/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-04

 * 简要描述:

 * 修改记录:

 *****************************************************************************/

#include "gui/Canvas.h"
#include "system/System.h"
#include "core/TypesPropertyValuesStore.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(Canvas, Panel, NULL, NULL);

namespace nb
{ 
	namespace Gui
	{
		class CanvasTypeProperties
		{
		public:
			CanvasTypeProperties()
			{
				DependencyProperty::PrepareExternalProperty("TopLength", typeid(Canvas), typeid(Float), NULL);
				DependencyProperty::PrepareExternalProperty("BottomLength", typeid(Canvas), typeid(Float), NULL);
				DependencyProperty::PrepareExternalProperty("LeftLength", typeid(Canvas), typeid(Float), NULL);
				DependencyProperty::PrepareExternalProperty("RightLength", typeid(Canvas), typeid(Float), NULL);
			}
		} s_CanvasTypeProperties;
	}
}
Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}


void Canvas::SetTop(UIElement *element, float fTopLength)
{
	Type *pType = Type::GetType<Canvas>();
	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("TopLength"), Float(fTopLength));
}

float Canvas::GetTop(UIElement *element)
{
	Type *pType = Type::GetType<Canvas>();
	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("TopLength"));
	const Float & x =  dynamic_cast<const Float &>(v);
	return x.m_value;
}

void Canvas::SetBottom(UIElement *element, float fBottomLength)
{
	Type *pType = Type::GetType<Canvas>();
	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("BottomLength"), Float(fBottomLength));
}


float Canvas::GetBottom(UIElement *element)
{
	Type *pType = Type::GetType<Canvas>();
	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("BottomLength"));
	const Float & x =  dynamic_cast<const Float &>(v);
	return x.m_value;
}

void Canvas::SetLeft(UIElement *element, float fLeftLength)
{
	Type *pType = Type::GetType<Canvas>();
	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("LeftLength"), Float(fLeftLength));
}


float Canvas::GetLeft(UIElement *element)
{
	Type *pType = Type::GetType<Canvas>();
	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("LeftLength"));
	const Float & x =  dynamic_cast<const Float &>(v);
	return x.m_value;
}

void Canvas::SetRight(UIElement *element, float fRightLength)
{
	Type *pType = Type::GetType<Canvas>();
	element->GetTypesPropertyValuesStore()->SaveValueValue(pType, pType->GetExternalProperty("RightLength"), Float(fRightLength));
}


float Canvas::GetRight(UIElement *element)
{
	Type *pType = Type::GetType<Canvas>();
	const ValueObject &v = element->GetTypesPropertyValuesStore()->GetValueValue(pType, pType->GetExternalProperty("RightLength"));
	const Float & x =  dynamic_cast<const Float &>(v);
	return x.m_value;
}

nb::System::Size Canvas::MeasureOverride(const nb::System::Size &availableSize)
{
	//int nChildCount = GetChildCount();
	int nChildCount = Children()->GetCount();
	nb::System::Size nDesiredSize(0.0, 0.0);
	for (int i=0;i<nChildCount;i++)
	{
		//UIElement* element = GetChild(i);
		UIElement* element = Children()->GetAt(i);
		element->Measure(1.0e30, 1.0e30);
		nDesiredSize = element->GetDesiredSize();
	}
	return nDesiredSize;
}

nb::System::Size Canvas::ArrangeOverride(const nb::System::Size &finalSize)
{
	//int nChildCount = GetChildCount();
	int nChildCount = Children()->GetCount();
	float fxPos = 0.0;
	float fyPos = 0.0;
	for (int i =0; i<nChildCount; i++)
	{
		//UIElement* element = GetChild(i);
		UIElement* element = Children()->GetAt(i);
		nb::System::Size s = element->GetDesiredSize();
		fxPos = GetLeft(element);
		fyPos = GetTop(element);
		element->Arrange(nb::System::Rect(fxPos,fyPos,s));
	}
	return Panel::ArrangeOverride(finalSize);
}


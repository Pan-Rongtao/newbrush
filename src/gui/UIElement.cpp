#include "gui/UIElement.h"
#include "UIElementPrivate.h"

#include "gui/VisualState.h"
#include "gui/VisualStateGroup.h"
#include "gui/NameRealm.h"
#include "gui/Transform.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::System;
using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(UIElement, nbObject, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Width, Float, &UIElement::OnWidthPropertyChanged);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Height, Float, &UIElement::OnHeightPropertyChanged);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, HorzAlignment, EnumObject, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, VertAlignment, EnumObject, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Margin, Thickness, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Visibility, EnumObject, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, VisualStateMgr, VisualStateManager, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Width1, Float, &UIElement::OnWidthPropertyChanged);

//NB_OBJECT_VALUE_PROPERTY_IMPLEMENT_EX_1(UIElement, WidthTest, Float, NULL);


NB_OBJECT_PROPERTY_IMPLEMENT_EX(UIElement, Visibility_New, RefObject, NULL);
//	nbDependencyPropertyPtr UIElement::property_Visibility_New = nbDependencyProperty::PrepareProperty<UIElement, EnumObject>("Visibility_New", 
//		NULL); 
//	nbDependencyProperty * className::Get##propertyName##Property() const {return property_##propertyName;} \

//nbDependencyProperty * UIElement::property_Widthex = nbDependencyProperty::PrepareProperty<UIElement, aFloat>((int)(&((UIElement *)(NULL))->Widthex), "Widthex", NULL);
//nbDependencyProperty * UIElement::WidthexProperty() {return property_Widthex;}

NB_X_OBJECT_PROPERTY_IMPLEMENT(UIElement, RenderTransform, Transform, &UIElement::OnRenderTransformChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(UIElement, Widthex, aFloat, &UIElement::OnTestWidthChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(UIElement, Opacity, aFloat, NULL);


UIElement::UIElement(void)
	: m_width(0)
	, m_height(0)
{
	m_pPrivate = new UIElementPrivate(this);

	Visibility() = Visibility_Visible;

	Opacity = 1;

//	Width() = 10.0f;
//	Float k = Width();
//	int f = k;

//	HorzAlignment() = ::HorizontalAlignment_Center;
//	::HorizontalAlignment h = HorzAlignment();
}

UIElement::~UIElement(void)
{
	delete m_pPrivate;
}

void UIElement::Measure(float width, float height)
{
	m_pPrivate->Measure(width, height);
}

void UIElement::Arrange(const nb::System::Rect &rect)
{
	m_pPrivate->Arrange(rect);
}

void UIElement::OnWidthPropertyChanged(PropertyValueChangedEventArgs &args)
{
}

void UIElement::OnHeightPropertyChanged(PropertyValueChangedEventArgs &args)
{
}

float UIElement::GetDesignWidth() const
{
	return m_pPrivate->GetDesignWidth();
}

float UIElement::GetDesignHeight() const
{
	return m_pPrivate->GetDesignHeight();
}

const nb::System::Size &UIElement::GetDesiredSize() const
{
	return m_pPrivate->GetDesiredSize();
}

float UIElement::GetActualWidth() const
{
	return m_pPrivate->GetActualWidth();
}

float UIElement::GetActualHeight() const
{
	return m_pPrivate->GetActualHeight();
}

float UIElement::GetX() const
{
	return m_pPrivate->GetX();
}

float UIElement::GetY() const
{
	return m_pPrivate->GetY();
}

void UIElement::GotoVisualState(const char *groupName, const char *stateName)
{
	NameRealm * nameRealm = NULL;
	String * name = NULL;
	if(!NameRealm::FindNameRealm(this, nameRealm, name)) return;

	VisualState *state = dynamic_cast<VisualState *>(nameRealm->FindObject(stateName));
	if(state == NULL) return;


	VisualStateArray *arr = dynamic_cast<VisualStateArray *>(ObjectArrayBase::FindObjectBelongToArray(state));
	if(arr == NULL) return;

	VisualStateGroup *group = VisualStateGroup::FindGroup(arr);
	if(group == NULL) return;

	VisualStateGroupCollection *groupArray = dynamic_cast<VisualStateGroupCollection *>(ObjectArrayBase::FindObjectBelongToArray(group));
	if(groupArray == NULL) return;


	VisualStateManager *stateMgr = VisualStateManager::FindVisualStateManager(groupArray);
	if(stateMgr == NULL) return;

//	VisualStateManager *stateMgr = VisualStateMgr();
//	if(stateMgr == NULL) return;

//	group = stateMgr->GetGroup(groupName);
//	if(group == NULL) return;

//	state = group->GetChild(stateName);
//	if(state == NULL) return;

	stateMgr->TestGotoState(group, state);
}

void UIElement::InvalidateArrange()
{
	GetPrivate()->InvalidateArrange();
}

void UIElement::InvalidateMeasure()
{
	GetPrivate()->InvalidateMeasure();
}

void UIElement::OnRenderTransformChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	GetPrivate()->InvalidateRenderMatrix();
}

void UIElement::OnTestWidthChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
}

void UIElement::SetTrack(BaseTrack *track)
{
	GetPrivate()->m_track = track;
}

BaseTrack * UIElement::GetTrack() const
{
	return GetPrivate()->m_track;
}

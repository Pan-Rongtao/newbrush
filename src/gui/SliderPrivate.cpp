#include "SliderPrivate.h"
#include "gui/Slider.h"
#include "gui/Grid.h"
#include "system/System.h"
#include "core/Exception.h"
using namespace nb::Gui;
using namespace nb::System;
using namespace nb::Core;

SliderPrivate::SliderPrivate(Slider *owner)
: m_owner(owner)
{
	Init();
	UpdateLayout();
	Update();
}

SliderPrivate::~SliderPrivate()
{
}

void SliderPrivate::Init()
{
	Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
	if(pBody)
	{
		RepeatButton *pLeftTop = new RepeatButton();
		pLeftTop->RepeatClickEvent.Add(this, &SliderPrivate::OnLTRepeatButtonClick);
		pBody->Children()->Add(pLeftTop);
		Thumb *pThumb = new Thumb();
		pBody->Children()->Add(pThumb);
		RepeatButton *pRightBottom = new RepeatButton();
		pRightBottom->RepeatClickEvent.Add(this, &SliderPrivate::OnRBRepeatButtonClick);
		pBody->Children()->Add(pRightBottom);
	}
	else
	{
		throw ExceptionPtr::GetPtrInstance("无法构造主体面板为空的滑块控件");
	}
}

void SliderPrivate::OnPointerPress(bool &handled)
{
}

void SliderPrivate::OnPointerRelease()
{
}

void SliderPrivate::OnValueChanged(float fOldValue, float fNewValue)
{
	Update();
}

void SliderPrivate::OnDelayChanged()
{
	Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
	if(pBody)
	{
		RepeatButton *pLeftTop = (RepeatButton *)pBody->Children()->GetAt(0);
		int nChildCount = pBody->Children()->GetCount();
		for(int i=0;i<nChildCount;i++)
		{
			RepeatButton *pRepeatButton = (RepeatButton *)pBody->Children()->GetAt(i);
			pRepeatButton->Delay = m_owner->Delay;
		}
	}	
}

void SliderPrivate::OnIntervalChanged()
{
	Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
	if(pBody)
	{
		RepeatButton *pLeftTop = (RepeatButton *)pBody->Children()->GetAt(0);
		int nChildCount = pBody->Children()->GetCount();
		for(int i=0;i<nChildCount;i++)
		{
			RepeatButton *pRepeatButton = (RepeatButton *)pBody->Children()->GetAt(i);
			pRepeatButton->Interval = m_owner->Interval;
		}
	}	
}

void SliderPrivate::OnOrientationChanged()
{
	Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
	if(pBody)
	{
		pBody->RowDefCollection->Clear();
		pBody->ColDefCollection->Clear();
		UpdateLayout();
	}
}

void SliderPrivate::OnDirectionReversedChanged()
{
	UpdateLayout();
}

void SliderPrivate::Update()
{//在这里更新各个部分的尺寸
	float fMaximum = (Float)m_owner->Maximum;
	float fMinimum = (Float)m_owner->Minimum;
	if(nb::System::Abs(fMaximum - fMinimum) < 0.01)
	{//最大值与最小值相等
	}
	else
	{
		float fTemp = fMaximum;
		fMaximum = nb::System::Max(fTemp, fMinimum);
		fMinimum = nb::System::Min(fTemp, fMinimum);
		float fRange = fMaximum - fMinimum;
		float fValue = (Float)m_owner->Value;
		float fk = fValue/fRange;
		float fWidth = (Float)m_owner->Width();
		float fHeight = (Float)m_owner->Height();
		nb::Gui::Orientation nOrientation = (nb::Gui::Orientation)m_owner->Orientation();
		bool bIsDirectionReversed = (Boolx)m_owner->IsDirectionReversed;
		Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
		int nStartIndex = (bIsDirectionReversed == false)?0:2;
		int nPosStepSize = (bIsDirectionReversed == false)?1:-1;
		if(nOrientation == nb::Gui::Orientation_Hor)
		{
			float fThumbPos = fk * fWidth;
			ColDefinitionCollection *ColCollection = pBody->ColDefCollection;
			ColDefinition *pLCol = ColCollection->GetAt(nStartIndex);
			pLCol->Width() = GridLength(fk, GridLength::UnitType_Star);
			ColDefinition *pMCol = ColCollection->GetAt(nStartIndex + nPosStepSize);
			ColDefinition *pRCol = ColCollection->GetAt(nStartIndex + nPosStepSize*2);
			pRCol->Width() = GridLength(1-fk, GridLength::UnitType_Star);
		}
		else if(nOrientation == nb::Gui::Orientation_Vert)
		{
			float fThumbPos = fk * fHeight;
			RowDefinitionCollection *RowCollection = pBody->RowDefCollection;
			RowDefinition *pTRow = RowCollection->GetAt(nStartIndex);
			pTRow->Height() = GridLength(fk, GridLength::UnitType_Star);
			RowDefinition *pMRow = RowCollection->GetAt(nStartIndex + nPosStepSize);
			RowDefinition *pBRow = RowCollection->GetAt(nStartIndex + nPosStepSize*2);
			pBRow->Height() = GridLength(1-fk, GridLength::UnitType_Star);
		}
	}
}

void SliderPrivate::UpdateLayout()
{
	Grid *pBody = dynamic_cast<Grid *>(m_owner->GetBody());
	bool bIsDirectionReversed = (Boolx)m_owner->IsDirectionReversed;
	int nChildStartIndex = (bIsDirectionReversed == false)?0:2;
	int nChildPosStepSize = (bIsDirectionReversed == false)?1:-1;
	RepeatButton *pLT = (RepeatButton *)pBody->Children()->GetAt(nChildStartIndex);
	Thumb *pThumb = (Thumb *)pBody->Children()->GetAt(nChildStartIndex + nChildPosStepSize);
	RepeatButton *pRB = (RepeatButton *)pBody->Children()->GetAt(nChildStartIndex + nChildPosStepSize*2);
	nb::Gui::Orientation nOrientation = m_owner->Orientation();
	if(nb::Gui::Orientation_Hor == nOrientation)
	{
//		pBody->ColDefCollection = new ColDefinitionCollection();
		ColDefinitionCollection *pColCollection = pBody->ColDefCollection;
		ColDefinition *pLCol = new ColDefinition();
		pColCollection->Add(pLCol);
		ColDefinition *pMCol = new ColDefinition();
		pColCollection->Add(pMCol);
		ColDefinition *pRCol = new ColDefinition();
		pColCollection->Add(pRCol);
		Grid::SetCol(pLT, nChildStartIndex);
		Grid::SetCol(pThumb, nChildStartIndex + nChildPosStepSize);
		Grid::SetCol(pRB, nChildStartIndex + nChildPosStepSize*2);
	}
	else
	{
	//	pBody->RowDefCollection = new RowDefinitionCollection();
		RowDefinitionCollection *pRowCollection = pBody->RowDefCollection;
		RowDefinition *pTRow = new RowDefinition();
		pRowCollection->Add(pTRow);
		RowDefinition *pMRow = new RowDefinition();
		pRowCollection->Add(pMRow);
		RowDefinition *pBRow = new RowDefinition();
		pRowCollection->Add(pBRow);
		Grid::SetRow(pLT, nChildStartIndex);
		Grid::SetRow(pThumb, nChildStartIndex + nChildPosStepSize);
		Grid::SetRow(pRB, nChildStartIndex + nChildPosStepSize*2);
	}
}

void SliderPrivate::OnLTRepeatButtonClick(nb::Gui::RepeatButton::RepeatClickEventParam &param)
{
	float fCurrValue = (Float)m_owner->Value;
	float fLargeChange = (Float)m_owner->LargeChange;
	if(fLargeChange <= 0.0f)
	{
		throw ExceptionPtr::GetPtrInstance("LargeChange属性不能是负数!");
	}
	m_owner->Value = fCurrValue - fLargeChange;
	Update();
}

void SliderPrivate::OnRBRepeatButtonClick(nb::Gui::RepeatButton::RepeatClickEventParam &param)
{
	float fCurrValue = (Float)m_owner->Value;
	float fLargeChange = (Float)m_owner->LargeChange;
	if(fLargeChange <= 0.0f)
	{
		throw ExceptionPtr::GetPtrInstance("LargeChange属性不能是负数!");
	}
	m_owner->Value = fCurrValue + fLargeChange;
	Update();
}


nb::System::Size SliderPrivate::ArrangeWork(const nb::System::Size &finalSize)
{
	return finalSize;
}

nb::System::Size SliderPrivate::MeasureWork(const nb::System::Size &availableSize)
{
	return availableSize;
}

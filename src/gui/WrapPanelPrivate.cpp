#include "WrapPanelPrivate.h"
#include "system/System.h"
#include "gui/WrapPanel.h"

using namespace nb::Gui;
using namespace nb::System;

WrapPanelPrivate::WrapPanelPrivate(WrapPanel *owner)
	: m_owner(owner)
{
	m_mapIndex = new std::map<int, int>();
	if(m_mapIndex)
	{
		m_mapIndex->clear();
	}
}

WrapPanelPrivate::~WrapPanelPrivate(void)
{
	if(m_mapIndex)
	{
		m_mapIndex->clear();
		delete m_mapIndex;
		m_mapIndex =NULL;
	}
}

void WrapPanelPrivate::SaveIndex(int nIndex, int nItemIndex)
{
	if(m_mapIndex)
	{
		std::map<int, int>::iterator iter = m_mapIndex->find(nIndex);
		if(iter == m_mapIndex->end())
		{
			m_mapIndex->insert(std::pair<int, int>(nIndex, nItemIndex));
		}
		else
		{
			//已经保存过，不需要更新;
		}
	}
	else
	{
	}
}

nb::System::Size WrapPanelPrivate::ArrangeWork(const nb::System::Size &finalSize)
{
	nb::System::Size nArrangeSize(0.0f, 0.0f);
	if(m_mapIndex)
	{
		nb::Gui::Orientation nOrientation = m_owner->Orientation();
		int nChildCount = m_owner->Children()->GetCount();//GetChildCount();
		float fxPos = 0.0;
		float fyPos = 0.0;
		float fMaxH = 0.0;
		float fMaxW = 0.0;

		int nLineCount = (int)m_mapIndex->size();
		for(int i=0;i<nLineCount;i++)
		{
			std::map<int, int>::iterator iterLineStart = m_mapIndex->find(i);
			std::map<int, int>::iterator iterNextLineStart = m_mapIndex->find(i+1);
			//fMaxH = 0.0;
			if(iterLineStart != m_mapIndex->end())
			{
				int nStartIndex = iterLineStart->second;
				int nEndIndex = iterNextLineStart != m_mapIndex->end()?iterNextLineStart->second:(nChildCount);
				if(nOrientation == Orientation_Hor)
				{
					fxPos = 0.0;
					fyPos += fMaxH;
					fMaxH = 0.0;
					for(int nItemIndex = nStartIndex;nItemIndex<nEndIndex;nItemIndex++)
					{
						UIElement *element = m_owner->Children()->GetAt(nItemIndex);//GetChild(nItemIndex);
						nb::System::Size s = element->GetDesiredSize();
						element->Arrange(nb::System::Rect(fxPos, fyPos, s));
						fxPos += s.GetWidth();
						fMaxH = nb::System::Max(fMaxH, s.GetHeight());
						nArrangeSize.SetWidth(nb::System::Max(nArrangeSize.Width(), fxPos));
					}
					nArrangeSize.SetHeight(nArrangeSize.Height() + fMaxH);
				}
				else if(nOrientation == Orientation_Vert)
				{
					fxPos += fMaxW;
					fyPos = 0.0;
					for(int nItemIndex = nStartIndex;nItemIndex<nEndIndex;nItemIndex++)
					{
						UIElement *element = m_owner->Children()->GetAt(nItemIndex);//GetChild(nItemIndex);
						nb::System::Size s = element->GetDesiredSize();
						element->Arrange(nb::System::Rect(fxPos, fyPos, s));
						fyPos += s.Height();
						fMaxW = nb::System::Max(fMaxW, s.Width());
						nArrangeSize.SetHeight(nb::System::Max(nArrangeSize.Height(), fyPos));
					}
					nArrangeSize.SetWidth(nArrangeSize.Width() + fMaxW);
				}
				else
				{}
			}
			else
			{}
		}

	}
	else
	{
	} 
	return nArrangeSize;
	//return finalSize;//Panel::ArrangeOverride(finalSize);
}

nb::System::Size WrapPanelPrivate::MeasureWork(const nb::System::Size &availableSize)
{
	nb::System::Size nDesiredSize(0.0, 0.0);
	if(m_mapIndex)
	{
		m_mapIndex->clear();
		nb::Gui::Orientation nOrientation = m_owner->Orientation();
		m_owner->Orientation();
		int nChildCount = m_owner->Children()->GetCount();//GetChildCount();
		float fxPos = 0.0;
		float fyPos = 0.0;
		float fMaxH = 0.0;
		float fMaxW = 0.0;
		float fWidth_Left = availableSize.Width();
		float fHeight_Left = availableSize.Height();
		int nRowIndex = 0;//Orientation_Hor模式使用
		int nColIndex = 0;//Orientation_Vert模式使用
		for(int i=0;i<nChildCount;i++)
		{
			UIElement *element = m_owner->Children()->GetAt(i);//GetChild(i);
			element->Measure(1.0e30, 1.0e30);
			nb::System::Size sFirst = element->GetDesiredSize();
			if(nOrientation == Orientation_Hor)
			{
				if(fWidth_Left <= 0.0)
				{//说明之前的子控件已经达到了区域的最后
					fWidth_Left = availableSize.Width();
					fMaxH = nb::System::Max(fMaxH, sFirst.Height());
					fxPos = 0.0;
					fyPos += fMaxH;
					fMaxH = 0.0;
					nRowIndex ++;
				}

				if(sFirst.Width() > fWidth_Left)
				{//放不下，先不换行，看是否放得下；需要换行，重新测量
					//element->InvalidMeasure();
					element->Measure(fWidth_Left, fMaxH);
					nb::System::Size sSecond = element->GetDesiredSize();
					if(sSecond.Width() > fWidth_Left)
					{//还是放不下,换行测量
						if(sFirst != sSecond)
						{
	//						element->InvalidMeasure();
							element->Measure(availableSize.Width(), 1.0e30);
							sSecond = element->GetDesiredSize();
						}
						fxPos = 0.0;
						fyPos += fMaxH;
						fMaxH = sSecond.Height();				
						nDesiredSize.SetWidth(nb::System::Max(nDesiredSize.Width(), sSecond.Width()));
						nDesiredSize.SetHeight(fyPos+sSecond.Height());
						fWidth_Left = availableSize.Width() - sSecond.Width();
						nRowIndex ++;
					}
					else
					{//可以放下了
						fWidth_Left -= sSecond.Width();
						fMaxH = nb::System::Max(fMaxH, sSecond.Height());
						fxPos += sSecond.Width();
						nDesiredSize.SetWidth(nb::System::Max(fxPos, nDesiredSize.Width()));
						nDesiredSize.SetHeight(fyPos + fMaxH);
					}
				}
				else
				{//可以放下
					fWidth_Left -= sFirst.Width();
					fMaxH = nb::System::Max(fMaxH, sFirst.Height());
					fxPos += sFirst.Width();
					nDesiredSize.SetWidth(nb::System::Max(fxPos, nDesiredSize.Width()));
					nDesiredSize.SetHeight(fyPos + fMaxH);
				}
				SaveIndex(nRowIndex, i);
			}
			else if(nOrientation == Orientation_Vert)
			{
				if(fHeight_Left <= 0.0)
				{//说明之前的子控件已经达到了区域的最后
					fHeight_Left = availableSize.Height();
					fMaxW = nb::System::Max(fMaxW, sFirst.Height());
					fyPos = 0.0;
					fxPos += fMaxW;
					fMaxW = 0.0;
					nColIndex ++;
				}
				if(sFirst.Height()>fHeight_Left)
				{//放不下，先不换列，看是否放得下；需要换列，重新测量
	//				element->InvalidMeasure();
					element->Measure(fMaxW, fHeight_Left);
					System::Size sSecond = element->GetDesiredSize();
					if(sSecond.Height() > fHeight_Left)
					{//还是放不下
						if(sFirst != sSecond)
						{
	//						element->InvalidMeasure();
							element->Measure(1.0e30, availableSize.Height());
							sSecond = element->GetDesiredSize();
						}
						fyPos = 0.0;
						fxPos += fMaxW;
						fMaxW = 0.0;
						nDesiredSize.SetHeight(nb::System::Max(nDesiredSize.Height(), sSecond.Height()));
						nDesiredSize.SetWidth(fxPos + sSecond.Width());
						fHeight_Left = availableSize.Height() - sSecond.Height();
						nColIndex ++;
					}
					else
					{//可以放下了
						fMaxW = nb::System::Max(fMaxW, sSecond.Width());
						fyPos += sSecond.Height();
						fHeight_Left -= sSecond.Height();
						nDesiredSize.SetHeight(nb::System::Max(fyPos, nDesiredSize.Height()));
						nDesiredSize.SetWidth(fxPos + fMaxW);
					}
				}
				else
				{//可以放下
					fMaxW = nb::System::Max(fMaxW, sFirst.Width());
					fyPos += sFirst.Height();
					fHeight_Left -= sFirst.Height();
					nDesiredSize.SetHeight(nb::System::Max(fyPos, nDesiredSize.Height()));
					nDesiredSize.SetWidth(fxPos + fMaxW);
				}
				SaveIndex(nColIndex, i);
			}
			else
			{}
		}
	}
	else
	{
	}
	return nDesiredSize;
}


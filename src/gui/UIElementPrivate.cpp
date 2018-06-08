#include "UIElementPrivate.h"
#include "gui/UIElement.h"
#include "system/System.h"
#include "gui/Transform.h"
#include "math/Matrix4x4.h"

#include "gui/Page.h" // 特殊使用，Page里面包含有window信息，用于获取window

using namespace nb::Gui;

using namespace nb::Core;

UIElementPrivate::UIElementPrivate(UIElement *owner)
	: m_x(0)
	, m_y(0)
	, m_designWidth(0)
	, m_designHeight(0)
	, m_invalidateMeasure(true)
	, m_invalidateArrange(true)
	, m_measureOriginWidth(0)
	, m_measureOriginHeight(0)
	, m_owner(owner)
	, m_actualWidth(-1)
	, m_actualHeight(-1)
	, m_parent(NULL)
	, m_invalidateRenderMatrix(true)
	, m_renderer(NULL)
{
}

UIElementPrivate::~UIElementPrivate(void)
{
	delete m_renderer;
}

void UIElementPrivate::OnRender(nb::gl::Gles::Painter *pPainter, float x, float y)
{
}

void UIElementPrivate::Measure(float width, float height)
{
//	m_owner->Visibility() == Visibility_Collapsed;
	if(!m_invalidateMeasure && m_measureOriginWidth == width && m_measureOriginHeight == height) return;

	m_measureOriginWidth = width;
	m_measureOriginHeight = height;

//	if(!m_owner->Visibility().IsNull() && m_owner->Visibility() == Visibility_Collapsed) return;


	float measureHeight = height;
	float measureWidth = width;


	// 高度调整
	float minHeight = 0.0;
	if(!m_owner->Height().IsNull())
	{
		measureHeight = (Float)m_owner->Height();
		minHeight = measureHeight;

		if(!m_owner->Margin().IsNull())
		{
			float heightMargin = m_owner->Margin()->Top() + m_owner->Margin()->Bottom();
			if(minHeight + heightMargin <= height)
			{
				minHeight += heightMargin;
			}
			else
			{
				minHeight = height;
			}
		}
	}
	else
	{
		if(!m_owner->Margin().IsNull())
		{
			measureHeight -= m_owner->Margin()->Top();
			measureHeight -= m_owner->Margin()->Bottom();
			if(measureHeight < 0) measureHeight = 0;
		}
	}


	// 宽度调整
	float minWidth = 0.0;
	if(!m_owner->Width().IsNull())
	{
		measureWidth = (Float)m_owner->Width();
		minWidth = measureWidth;

		if(!m_owner->Margin().IsNull())
		{
			float widthMargin = m_owner->Margin()->Left() + m_owner->Margin()->Right();
			if(minWidth + widthMargin <= width)
			{
				minWidth += widthMargin;
			}
			else
			{
				minWidth = width;
			}
		}
	}
	else
	{
		if(!m_owner->Margin().IsNull())
		{
			measureWidth -= m_owner->Margin()->Left();
			measureWidth -= m_owner->Margin()->Right();
			if(measureWidth < 0) measureWidth = 0;
		}
	}


	// 测量
	m_desiredSize = m_owner->MeasureOverride(System::Size(measureWidth, measureHeight));

	if(m_desiredSize.GetHeight() < minHeight) m_desiredSize.SetHeight(minHeight);
	if(m_desiredSize.GetWidth() < minWidth) m_desiredSize.SetWidth(minWidth);

	m_invalidateMeasure = false;
}

void UIElementPrivate::Arrange(const nb::System::Rect &rect)
{
//	if(m_invalidateMeasure)
//	{
//		m_owner->Measure(rect.GetWidth(), rect.GetHeight());
//	}

	if(m_invalidateArrange || rect.GetSize() != m_arrangeOriginSize)
	{
		m_owner->Measure(rect.GetWidth(), rect.GetHeight());

		m_arrangeOriginSize = rect.GetSize();

//		m_x = rect.GetLeft();
//		m_y = rect.GetTop();

		float height = 0;
		float width = 0;

		VerticalAlignment vertAlignment = VerticalAlignment_Stretch;
		if(!m_owner->VertAlignment().IsNull())
		{
			vertAlignment = m_owner->VertAlignment();
		}

		if(m_owner->Height().IsNull())
		{
			// 没有指定高度 
			if(vertAlignment == VerticalAlignment_Stretch)
			{
				height = rect.GetHeight();
				if(!m_owner->Margin().IsNull())
				{
					height -= m_owner->Margin()->Top();
					height -= m_owner->Margin()->Bottom();
					if(height < 0) height = 0;
				}
			}
			else
			{
				height = nb::System::Min(rect.GetHeight(), GetDesiredSize().Height());
				//height = 0;
			}
		}
		else
		{
			// 指定了高度
			height = m_owner->Height()->m_value;
		}

		HorizontalAlignment horzAlignment = HorizontalAlignment_Stretch;
		if(!m_owner->HorzAlignment().IsNull())
		{
			horzAlignment = m_owner->HorzAlignment();
		}

		if(m_owner->Width().IsNull())
		{
			// 没有指定宽度
			if(horzAlignment == HorizontalAlignment_Stretch)
			{
				width = rect.GetWidth();
				if(!m_owner->Margin().IsNull())
				{
					width -= m_owner->Margin()->Left();
					width -= m_owner->Margin()->Right();
					if(width < 0) width = 0;
				}
			}
			else
			{
				width = nb::System::Min(rect.GetWidth(), GetDesiredSize().Width());
			//	width = 0;
			}
		}
		else
		{
			// 指定了宽度
			width = m_owner->Width()->m_value;
		}

		nb::System::Size sz = m_owner->ArrangeOverride(nb::System::Size(width, height));
	//	SetActualHeight(sz.GetHeight());
	//	SetActualWidth(sz.GetWidth());
		SetActualSize(sz.GetWidth(), sz.GetHeight());


		switch(vertAlignment)
		{
		case VerticalAlignment_Top:
			m_y = rect.GetTop() + GetTopMargin();
			break;
		case VerticalAlignment_Center:
			m_y = rect.GetTop() + GetTopMargin() + (rect.GetHeight() - GetTopMargin() - GetBottomMargin() - sz.GetHeight()) / 2.0;
			break;
		case VerticalAlignment_Bottom:
			m_y = rect.GetBottom() - GetBottomMargin() - sz.GetHeight();
			break;
		default:
			{
				float h = rect.GetHeight() - GetTopMargin() - GetBottomMargin();
				if(sz.GetHeight() < h)
					m_y = rect.GetTop() + GetTopMargin() +  (h -  sz.GetHeight()) / 2.0;
				else
					m_y = rect.GetTop() + GetTopMargin();
			}
			break;
		}


		switch(horzAlignment)
		{
		case HorizontalAlignment_Left:
			m_x = rect.GetLeft();
			break;
		case HorizontalAlignment_Center:
			m_x = rect.GetLeft() + GetLeftMargin() + (rect.GetWidth() - GetLeftMargin() - GetRightMargin() - sz.GetWidth()) / 2.0;
			break;
		case HorizontalAlignment_Right:
			m_x = rect.GetRight() - GetRightMargin() - sz.GetWidth();
			break;
		default:
			{
				float w = rect.GetWidth() - GetLeftMargin() - GetRightMargin();
				if(sz.GetWidth() < w)
					m_x = rect.GetLeft() + GetLeftMargin() +  (w -  sz.GetWidth()) / 2.0;
				else
					m_x = rect.GetLeft() + GetLeftMargin();
			}
			break;
		}

		m_invalidateArrange = false;
	}
}

float UIElementPrivate::GetLeftMargin() const
{
	return m_owner->Margin().IsNull() ? 0 : m_owner->Margin()->Left();
}

float UIElementPrivate::GetRightMargin() const
{
	return m_owner->Margin().IsNull() ? 0 : m_owner->Margin()->Right();
}

float UIElementPrivate::GetTopMargin() const
{
	return m_owner->Margin().IsNull() ? 0 : m_owner->Margin()->Top();
}

float UIElementPrivate::GetBottomMargin() const
{
	return m_owner->Margin().IsNull() ? 0 : m_owner->Margin()->Bottom();
}

UIElement * UIElementPrivate::PointerPress()
{
	bool handled = false;
	m_owner->OnPointerPress(handled);
	if(handled) return m_owner;

	UIElement *parent = GetParent();
	if(parent == NULL) return NULL;

	return parent->GetPrivate()->PointerPress();
}

void UIElementPrivate::PointerRelease()
{
	m_owner->OnPointerRelease();
}

void UIElementPrivate::InvalidateArrange()
{
	if(m_invalidateArrange) return;
	m_invalidateArrange = true;

//	m_owner->InvalidateArrangeOverride();

	if(m_parent != NULL)
	{
		m_parent->InvalidateArrange();
	}
}

void UIElementPrivate::InvalidateMeasure()
{
	if(m_invalidateMeasure) return;
	m_invalidateMeasure = true;

//	m_owner->InvalidateMeasureOverride();

	if(m_parent != NULL)
	{
		m_parent->InvalidateMeasure();
	}
}

void UIElementPrivate::RenderWork(float x, float y)
{
	IElementRender *pElementRender = m_owner->GetElementRender();
	if(pElementRender == NULL) return;

//	bool invalidateRenderMatrix = (m_renderer == NULL ? false : m_renderer->m_invalidateRenderMatrix);
	if(/*updateRenderMatrix || */(m_renderer == NULL ? false : m_renderer->m_invalidateRenderMatrix))
	{
		//updateRenderMatrix = true;

		nb::Math::Matrix4x4 pm;
/*
		if(renderMatrix == NULL)
		{
			if(m_owner->RenderTransform == NULL)
			{
			}
			else
			{
//				pm = new nb::Media::Matrix4x4(m_owner->RenderTransform->Value());
			}
		}
		else
		{
			if(m_owner->RenderTransform == NULL)
			{
			//	pm = new nb::Media::Matrix4x4(*renderMatrix);
			}
			else
			{
//				nb::Media::Matrix4x4 m = m_owner->RenderTransform->Value();
//				pm = new nb::Media::Matrix4x4(m * (*renderMatrix));
			}
		}
*/
		if(/*pm == NULL*/1)
		{
			if(m_renderer != NULL)
			{
				if(m_renderer->m_model != NULL)
				{
					m_renderer->m_model->SetMatrix(/*nb::Media::Matrix4x4().GetPrivate()->GetGlesMatrix()*/nb::Math::Matrix4x4());
				}

				delete m_renderer;
				m_renderer = NULL;
			}
		}
		else
		{
			Renderer *renderer = TakeRenderer();
			m_renderer->m_invalidateRenderMatrix = false;
			renderer->m_usingRenderMatrix = pm;
			if(renderer->m_model != NULL)
			{
				const nb::Math::Matrix4x4 x = pm;
				renderer->m_model->SetMatrix(/*pm->GetPrivate()->GetGlesMatrix()*/nb::Math::Matrix4x4());
			}

		}
	}


	if(m_renderer != NULL)
	{
//		pElementRender->OnRender(pContex, x + m_owner->GetX() + m_owner->GetExtraRenderOffsetX(), y + m_owner->GetY() + m_owner->GetExtraRenderOffsetY(), updateRenderMatrix, m_renderer->m_usingRenderMatrix);
	}
	else
	{
		pElementRender->OnRender(x + m_owner->GetX() + m_owner->GetExtraRenderOffsetX(), y + m_owner->GetY() + m_owner->GetExtraRenderOffsetY());
	}
	return;


/*	if(updateRenderMatrix)
	{
		Renderer *renderer = TakeRenderer();
		
	}

	if(updateRenderMatrix || m_invalidateRenderMatrix)
	{
		m_invalidateRenderMatrix = false;
		updateRenderMatrix = true;

		nb::Media::Matrix4x4 m;
		const nb::Media::Matrix4x4 *pm;
		if(renderMatrix == NULL)
		{
			if(m_owner->RenderTransform == NULL)
			{
				pm = NULL;
			}
			else
			{
				m = m_owner->RenderTransform->Value();
				pm = &m;
			}
		}
		else
		{
			if(m_owner->RenderTransform == NULL)
			{
				pm = renderMatrix;
			}
			else
			{
				m = m_owner->RenderTransform->Value();
				m = m * (*renderMatrix);
				pm = &m;
			}
		}

		pElementRender->OnRender(pContex, x + m_owner->GetX(), y + m_owner->GetY(), updateRenderMatrix, pm);
	}
	else
	{
		pElementRender->OnRender(pContex, x + m_owner->GetX(), y + m_owner->GetY(), updateRenderMatrix, renderMatrix);
	}*/
}

Window * UIElementPrivate::GetWindow() const
{
	UIElement *parent = GetParent();
	if(parent == NULL) return NULL;

	Page *page = dynamic_cast<Page *>(m_owner);
	if(page != NULL) return page->GetWindow();

	return parent->GetPrivate()->GetWindow();
}

void UIElementPrivate::SetActualSize(float width, float height)
{
	if(m_actualWidth != width || m_actualHeight != height)
	{
		m_actualWidth = width;
		m_actualHeight = height;
		m_owner->OnActualSizeChanged();
	}
}

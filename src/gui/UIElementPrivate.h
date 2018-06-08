#pragma once
#include "core/Exception.h"
#include "system/Rect.h"
#include "system/Size.h"
#include "math/Matrix4x4.h"
#include "ElementRender.h"
#include "gui/UIElement.h"
#include "gles/Model.h"

#include "gui/BaseTrack.h"

namespace nb{ namespace gl{ namespace Gles {
	class Painter;
	class aaa;
}}}

namespace nb { namespace Gui {

class UIElement;
class Window;

class UIElementPrivate
{
	friend class UIElement;

public:
	UIElementPrivate(UIElement *owner);
	virtual ~UIElementPrivate(void);

	virtual void OnRender(nb::gl::Gles::Painter *pPainter, float x, float y);

	void Measure(float width, float height);
	void Arrange(const nb::System::Rect &rect);

	float GetX() const {return m_x;}
	float GetY() const {return m_y;}

	float GetDesignWidth() const {return m_desiredSize.Width();}
	float GetDesignHeight() const {return m_desiredSize.Height();}


	float GetActualWidth() const {return m_actualWidth;}
	float GetActualHeight() const {return m_actualHeight;}

	const System::Size &GetDesiredSize() const {return m_desiredSize;}

	float GetLeftMargin() const;
	float GetRightMargin() const;
	float GetTopMargin() const;
	float GetBottomMargin() const;

	UIElement * PointerPress();
	void PointerRelease();

	inline void SetParent(UIElement *parent)
	{
		if(parent == NULL)
		{
			m_parent = NULL;
		}
		else
		{
			if(m_parent != NULL)
			{
				NB_THROW_EXCEPTION("已存在父元素，在把父元素设置为空之前，不允许直切切换父元素。");
			}

			m_parent = parent;
		}
	}
	inline UIElement * GetParent() const {return m_parent;}

	void InvalidateArrange();
	void InvalidateMeasure();

	void RenderWork(float x, float y);

	inline void InvalidateRenderMatrix()
	{
		TakeRenderer()->m_invalidateRenderMatrix = true;
	}

	inline void SetModel(nb::gl::Gles::Model *model)
	{
		TakeRenderer()->m_model = model;
	}

	inline nb::gl::Gles::Model * GetModel() const
	{
		if(m_renderer == NULL) return NULL;
		return m_renderer->m_model;
	}

	Window * GetWindow() const;

private:
//	void SetActualWidth(float width) {m_actualWidth = width;}
//	void SetActualHeight(float height) {m_actualHeight = height;}

	void SetActualSize(float width, float height);

	float m_x;
	float m_y;
	bool m_invalidateMeasure;
	bool m_invalidateArrange;

	float m_measureOriginWidth;
	float m_measureOriginHeight;

	System::Size m_arrangeOriginSize;

	float m_designWidth;
	float m_designHeight;
	System::Size m_desiredSize;

	UIElement * m_owner;

	float m_actualWidth;
	float m_actualHeight;

	UIElement * m_parent;

	bool m_invalidateRenderMatrix;
	nb::Math::Matrix4x4 m_usingRenderMatrix;

	BaseTrackPtr m_track;

	class Renderer
	{
	public:
		Renderer() : m_invalidateRenderMatrix(false) {}
		bool m_invalidateRenderMatrix;
		nb::Math::Matrix4x4 m_usingRenderMatrix;
		nb::gl::Gles::Model *m_model;
	} * m_renderer;


	inline Renderer * TakeRenderer()
	{
		if(m_renderer == NULL) m_renderer = new Renderer;
		return m_renderer;
	}

	inline Renderer * GetRenderer() const {return m_renderer;}
};

}}

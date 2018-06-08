#pragma once

#include "core/Object.h"
#include "GuiDef.h"

#include "system/Size.h"
#include "system/Rect.h"
#include "gui/Thickness.h"
#include "VisualStateManager.h"

namespace nb
{
	namespace Core
	{

	}

	namespace Media
	{
		class Transform;
	};

	namespace Gui
	{
		enum HorizontalAlignment
		{
			HorizontalAlignment_Left = 0,
			HorizontalAlignment_Center = 1,
			HorizontalAlignment_Right = 2,
			HorizontalAlignment_Stretch = 3
		};

		enum VerticalAlignment
		{
			VerticalAlignment_Top = 0,
			VerticalAlignment_Center = 1,
			VerticalAlignment_Bottom = 2,
			VerticalAlignment_Stretch = 3
		};

		enum VisibilityEnum
		{
			//显示组件。
			Visibility_Visible = 0,		

			//不要显示的元素，但是，保留空间中的元素格式。
			Visibility_Hidden = 1,		

			//不要显示元素，并且不希望它的保留空间。格式。
			Visibility_Collapsed,
		};

		class UIElementPrivate;
		class PanelPrivate;
		class IElementRender;
		class BaseTrack;
		class NB_EXPORT UIElement : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
			
			friend class UIElementPrivate;
			friend class PanelPrivate;

		public:
			UIElement(void);
			virtual ~UIElement(void);

			void Measure(float width, float height);
			void Arrange(const nb::System::Rect &rect);

			float GetDesignWidth() const;
			float GetDesignHeight() const;

			float GetActualWidth() const;
			float GetActualHeight() const;

			float GetX() const;
			float GetY() const;

			const System::Size &GetDesiredSize() const;

			void GotoVisualState(const char *groupName, const char *stateName);

			void InvalidateArrange();
			void InvalidateMeasure();

			NB_OBJECT_VALUE_PROPERTY_DECLARE(Width, Core::Float);
			NB_OBJECT_VALUE_PROPERTY_DECLARE(Height, Core::Float);
			NB_OBJECT_VALUE_PROPERTY_DECLARE(Margin, Thickness);

		//	NB_OBJECT_VALUE_PROPERTY_DECLARE_1(WidthTest, Float);
			
			NB_OBJECT_PROPERTY_DECLARE(Width1, Core::Float);

			NB_OBJECT_ENUM_PROPERTY_DECLARE(HorzAlignment, HorizontalAlignment);
			NB_OBJECT_ENUM_PROPERTY_DECLARE(VertAlignment, VerticalAlignment);
			NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(Visibility, VisibilityEnum);

			NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(Visibility_New, VisibilityEnum);


			NB_OBJECT_PROPERTY_DECLARE(VisualStateMgr, VisualStateManager);

		//	static nbDependencyProperty * property_Widthex;
		//	static nbDependencyProperty * WidthexProperty();
		//	RockPV<aFloat> Widthex;

			NB_X_OBJECT_PROPERTY_DECLARE(RenderTransform, Media::Transform);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Widthex, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Opacity, Core::aFloat);

			UIElementPrivate * GetPrivate() const {return m_pPrivate;}

			virtual IElementRender * GetElementRender() const {return NULL;}

			BaseTrack * GetTrack() const;

		protected:
			virtual System::Size MeasureOverride(const System::Size &availableSize) {return System::Size(0, 0);}
			virtual System::Size ArrangeOverride(const System::Size &finalSize) {return finalSize;}

			virtual void OnPointerPress(bool &handled){}
			virtual void OnPointerRelease(){}

			void OnRenderTransformChanged(nb::Core::PropertyValueChangedEventArgs &args);

			virtual float GetExtraRenderOffsetX() const {return 0;}
			virtual float GetExtraRenderOffsetY() const {return 0;}

			virtual void OnActualSizeChanged(){}

		//	virtual void InvalidateMeasureOverride(){}
		//	virtual void InvalidateArrangeOverride(){}

		//	virtual void ChildInvalidateMeasureOverride(UIElement *child) {}
		//	virtual void ChildInvalidateArrangeOverride(UIElement *child) {}


		protected:
			void SetTrack(BaseTrack *track);

		private:
			void OnWidthPropertyChanged(Core::PropertyValueChangedEventArgs &args);
			void OnHeightPropertyChanged(Core::PropertyValueChangedEventArgs &args);
			
			void OnTestWidthChanged(nb::Core::PropertyValueChangedEventArgs &args);

		private:

			float m_width;
			float m_height;

			mutable UIElementPrivate *m_pPrivate;
		};

		typedef nbObjectPtrDerive<UIElement, nbObjectPtr> UIElementPtr;
	}
}

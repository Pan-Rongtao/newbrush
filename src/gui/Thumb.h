#pragma once

#include "gui/Control.h"
#include "core/Event.h"

namespace nb
{
	namespace Gui
	{
		class Thumb : public Control
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			Thumb(void);
			virtual ~Thumb(void);


		public:
			void CancelDrag();
		protected:
			virtual void OnPointerPress(bool &handled);
			virtual void OnPointerRelease();

			class DragStartedEventParam : public nbEventParamT<Thumb>
			{
			public:
				DragStartedEventParam(void):m_fHorizontalOffset(0.0f), m_fVerticalOffset(0.0f){};
				virtual ~DragStartedEventParam(void){};	
			public:
				float m_fHorizontalOffset;/**<鼠标点击点相对于Thumb控件左上角的水平偏移量>*/
				float m_fVerticalOffset;/**<鼠标点击点相对于Thumb控件左上角的竖直偏移量>*/
			};

			class DragDeltaEventParam : public nbEventParamT<Thumb>
			{
			public:
				DragDeltaEventParam(void):m_fHorizontalChange(0.0f), m_fVerticalChange(0.0f){};
				virtual ~DragDeltaEventParam(void){};
			public:
				float m_fHorizontalChange;/**<相对于上一次移动后的位置，本次移动的水平距离>*/
				float m_fVerticalChange;/**<相对于上一次移动后的位置，本次移动的竖直距离>*/
			};

			class DragCompletedEventParam : public nbEventParamT<Thumb>
			{
			public:
				/*
				 * m_bCanceled:Indicates that whether the drag action was canceled by Thumb::CancelDrag method.
				 */
				DragCompletedEventParam(void):m_fHorizontalChange(0.0f), m_fVerticalChange(0.0f), m_bCanceled(false){};
				virtual ~DragCompletedEventParam(void){};
			public:
				float m_fHorizontalChange;/**<按下鼠标时的点与松开鼠标时的点之间的水平距离>*/
				float m_fVerticalChange;/**<按下鼠标时的点与松开鼠标时的点之间的竖直距离>*/
				bool m_bCanceled;/**<本次拖动结束事件是否是因为调用了CancelDrag方法产生的>*/
			};
		public:
			nbEvent<DragStartedEventParam> DragStartedEvent;
			nbEvent<DragDeltaEventParam> DragDeltaEvent;
			nbEvent<DragCompletedEventParam> DragCompletedEvent;
		};
		typedef nbObjectPtrDerive<Thumb, ControlPtr> ThumbPtr;
	}
}

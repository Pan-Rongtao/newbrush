#pragma once

#include "ReboundScroll.h"
#include "GestureAnalyse.h"
#include "MovePositionAnalyse.h"

namespace nb
{
	namespace Gui
	{
		enum EnumWorkMode
		{
			WorkMode_Hor = 0x00,
			WorkMode_Vert
		};
		class ReboundScrollCtrler : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			ReboundScrollCtrler();
			virtual ~ReboundScrollCtrler();
			

			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ItemCount, Core::aInt)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(FirstItem, Core::aInt)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ItemSize, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(FirstItemOffset, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(PageSize, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Accel, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ReboundAccel, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(MaxSpeed, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(HoldBackSpeed, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(CycMode, Core::aBool)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(PressItem, Core::aInt)
			NB_OBJECT_ENUM_PROPERTY_DECLARE(WorkMode, nb::Gui::EnumWorkMode)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(MinScrollItem, Core::aInt)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(MaxScrollItem, Core::aInt)
			
			
			class ScrollEventParam : public nbEventParamT<ReboundScrollCtrler>
			{
			public:
				ScrollEventParam():m_nFirstItem(0), m_fFirstItemOffset(0.0f), m_nWorkMode(WorkMode_Vert){}
				virtual ~ScrollEventParam(void){};
			public:
				int m_nFirstItem;
				float m_fFirstItemOffset;
				nb::Gui::EnumWorkMode m_nWorkMode;
			};

			class ScrollEndEventParam : public nbEventParamT<ReboundScrollCtrler>
			{
			public:
				ScrollEndEventParam(){}
				virtual ~ScrollEndEventParam(void){};
			};
			
			class FirstItemChangedEventParam : public nbEventParamT<ReboundScrollCtrler>
			{
			public:
				FirstItemChangedEventParam(){}
				virtual ~FirstItemChangedEventParam(void){};
			public:
				int m_nOldFirstItem;
				int m_nNewFirstItem;
			};
			
			// 鼠标压下
			void PointerPressEvent(nb::System::Point pos);

			// 鼠标移动
			void PointerMoveEvent(nb::System::Point pos);

			// 鼠标释放
			void PointerReleaseEvent(nb::System::Point pos);

			// 将第一项的偏移量置为零
			void ZeroItemOffset();

			// 停止滚动
			void StopScroll();
			
			// 向增量方向滚动
			void ScrollIncrease(int nItems, float fAccel=1000.0);

			// 向减量方向滚动
			void ScrollDecrease(int nItems, float fAccel=1000.0);

			// 滚动指定的距离
			void ScrollDistance(float fDistance, float fAccel);

			// 获取鼠标压下点到压下项开始位置的偏离量
			float GetOffsetOfPressPosToPressItemBegin() const;

			// 是否激活了滚动
			bool IsActiveScroll() const;

			// 是否正在滚动
			bool IsScrolling() const;
			void SetGestureLock(int xGestureLock, int yGestureLock);
		private:
			
			void ScrollWork(float fSpeed, float fAccel, bool bUseHoldBackSpeed);
			inline void AdjustDragPos(nb::System::Point posOrigin, nb::System::Point &pos) /*const*/;
			inline int GetVisibleItems() /*const*/;
			inline void AdjustFirstItem();
			
			void OnKineticScroll(ReboundScroll::ScrollEventParam &param);
			void OnKineticScrollEnd(ReboundScroll::ScrollEndEventParam &param);

		public:
			nbEvent<ScrollEventParam> ScrollEvent;
			nbEvent<ScrollEndEventParam> ScrollEndEvent;
			nbEvent<FirstItemChangedEventParam> FirstItemChangedEvent;
		private:
			ReboundScrollPtr m_pReboundScroll;
			GestureAnalysePtr m_pGestureAnalyse;	//该对象分析鼠标手势，计算鼠标的滑动速度
			MovePositionAnalysePtr m_pMovePositionAnalyse;

			float m_fOffsetOfPressPosToPressItemBegin;
			bool m_bScrollByIncDec;
			int m_nPressFirstItem;			//鼠标压下时的第一项的序号
			float m_fPressFirstItemOffset;	//鼠标压下是的第一项的偏移量
		};
		typedef nbObjectPtrDerive<ReboundScrollCtrler, nbObjectPtr> ReboundScrollCtrlerPtr;
	}
}
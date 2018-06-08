#pragma once

#include "core/Object.h"
#include "core/Event.h"
#include "KineticMove.h"


namespace nb
{
	namespace Gui
	{
		class ReboundScroll : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			ReboundScroll();
			virtual ~ReboundScroll();
			
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(IsRuning, Core::aBool);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(UseRebound, Core::aBool);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(TopLeftReboundPos, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(BottomRightReboundPos, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ReboundStopLength, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ReboundAccel, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(ContentHeight, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(PageHeight, Core::aFloat)

			
			class ScrollEventParam : public nbEventParamT<ReboundScroll>
			{
			public:
				ScrollEventParam():m_nSpace(0){}
				virtual ~ScrollEventParam(void){};
			public:
				int m_nSpace;
			};
			
			class ScrollEndEventParam : public nbEventParamT<ReboundScroll>
			{
			public:
				ScrollEndEventParam(){}
				virtual ~ScrollEndEventParam(void){};
			};
			// 启动运动
			void Start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight);

			// 停止运动
			void Stop();

			// 偏移运动的开始位置
			void OffsetStartPos(float fStartPosOffset);

		private:
			inline void OnScrollEndEvent();
			void OnKineticMove(KineticMove::MoveDistanceEventParam &param);
			void OnKineticMoveEnd(KineticMove::MoveEndEventParam &param);
		public:
			nbEvent<ScrollEventParam> ScrollEvent;
			nbEvent<ScrollEndEventParam> ScrollEndEvent;

		private:
			KineticMovePtr m_pKineticMove;
			bool m_bElastic;
			bool m_bElasticDec;
			bool m_bScrollDown;
			float m_fElasticSpace;

		};
		typedef nbObjectPtrDerive<ReboundScroll, nbObjectPtr> ReboundScrollPtr;
	}
}

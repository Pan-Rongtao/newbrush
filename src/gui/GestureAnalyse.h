#pragma once

#include "core/Object.h"
#include "core/Event.h"
#include "system/Timer.h"
#include "system/Time.h"
#include "system/Point.h"
#include <iostream>
#include <queue>
using namespace std;
using namespace nb::System;

namespace nb
{
	namespace Gui
	{
		class GestureAnalyse : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			GestureAnalyse();
			virtual ~GestureAnalyse();

		struct Node
		{
			nb::System::Time m_time;
			nb::System::Point m_pos;
		};

		public:
			void GesturePress(nb::System::Point pos);
			void GestureMove(nb::System::Point pos);
			void GestureRelease(nb::System::Point pos);
			float GetHorizontalSpeed() const;
			float GetVerticalSpeed() const;
		private:
			void OnTimeout(nb::System::Timer::TimeoutParam &param);

			void AddPos(nb::System::Point pos);
			inline void ClearNodeQueue();
		private:
			std::queue<Node *> m_queueNode;
			bool m_bPress;
			bool m_bOffsetActive;
			nb::System::Point m_ptPress;
			nb::System::Point m_ptOffset;
			nb::System::Point m_ptPrev;
			nb::System::Time m_timePrev;
			nb::System::Point m_ptLast;
			nb::System::Time m_timeLast;
			float m_fSpeed;
			nb::System::TimerPtr m_timer;
		};
		typedef nbObjectPtrDerive<GestureAnalyse, nbObjectPtr> GestureAnalysePtr;
	}
}

#pragma once

#include "core/Object.h"
#include "core/Event.h"
#include "system/Time.h"
#include "system/Point.h"
#include "system/Timer.h"

using namespace nb::System;

namespace nb
{
	namespace Gui
	{
		class KineticMove : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			KineticMove();
			virtual ~KineticMove();

			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(InitSpeed, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Speed, Core::aFloat)
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Accel, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(StartPos, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(CurrentPos, Core::aFloat);
			NB_OBJECT_PROPERTY_DECLARE(TimeStart, nb::System::Time);

			class MoveDistanceEventParam : public nbEventParamT<KineticMove>
			{
			public:
				MoveDistanceEventParam():m_nSpace(0){}
				virtual ~MoveDistanceEventParam(void){};
			public:
				int m_nSpace;
			};

			class MoveEndEventParam : public nbEventParamT<KineticMove>
			{
			public:
				MoveEndEventParam():m_fSpace(0.0f){}
				virtual ~MoveEndEventParam(void){};
			public:
				float m_fSpace;
			};
			

			// 启动运动
			void Start(float fAccel, float fStartSpeed, float fStartPos);

			// 偏移运动的开始位置
			void OffsetStartPos(float fStartPosOffset);

			// 停止运动
			void Stop();

			// 设置运动的加速度
			void SetAccel(float fAccel);

			// 获取运动时的实时速度
			float GetSpeed() /*const*/;

			// 判断是否正在运动中
			bool IsRunning() const;

			// 计算加速度
			// fStartSpeed 开始速度； fSpace 打算运行的距离； fTime 运行时间
			static float ComputeAccel(float fStartSpeed, float fSpace, float fTime);

			// 已知运行距离(s)，初始速度(v)，求加速度(a)
			// （运行距离 s 后，速度为零）
			// （由于末速度为零，依据公式vt = v0 + at，其中vt=0，可知(a)必须要与
			// (v)符号相反，所以，(s)、(v) 不能同为正数，或同为负数）
			static float ComputeAccel(float s, float v);

			// 已知加速度(a)，运行距离(s)，求初始速度(v)
			// （运行距离 s 后，速度为零）
			static void ComputeVelocity(float a, float s, float &v);

			// 假设要在fTime的时间内运行fSpace的距离（在经过fTime时间后，速度为零），
			// 计算起始速度和加速度
			static void ComputeStartSpeedAndAccel(float fSpace, float fTime, float &fSpeed, float &fAccel);

			// 已知初速度(v)，加速度(a)，计算当速度为零时的距离(s)
			// 由于最终速度要为零， v、a 不能同为整数 或 同为负数
			static void ComputeSpace(float v, float a, float &s);

		private:
			void OnTimeout(nb::System::Timer::TimeoutParam &param);

		public:
			nbEvent<MoveDistanceEventParam> MoveDistanceEvent;
			nbEvent<MoveEndEventParam> MoveEndEvent;
		private:
			nb::System::TimerPtr m_timer;
		};
		typedef nbObjectPtrDerive<KineticMove, nbObjectPtr> KineticMovePtr;
	}
}

#pragma once
#include "core/Event.h"
#include "KineticMove.h"

namespace nb{ namespace gui {

class ReboundScroll
{
public:
	ReboundScroll();
	virtual ~ReboundScroll();

	// 启动运动
	void start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight);

	// 停止运动
	void stop();

	// 偏移运动的开始位置
	void offsetStartPos(float fStartPosOffset);

public:
	nb::core::Property_rw<bool>			IsRuning;
	nb::core::Property_rw<bool>			UseRebound;
	nb::core::Property_rw<float>		TopLeftReboundPos;
	nb::core::Property_rw<float>		BottomRightReboundPos;
	nb::core::Property_rw<float>		ReboundStopLength;
	nb::core::Property_rw<float>		ReboundAccel;
	nb::core::Property_rw<float>		ContentHeight;
	nb::core::Property_rw<float>		PageHeight;

	struct ScrollArgs { float m_nSpace; };
	nb::core::Event<ScrollArgs>			ScrollEvent;

	struct ScrollEndArgs { };
	nb::core::Event<ScrollEndArgs>		ScrollEndEvent;

private:
	inline void onScrollEndEvent();
	void onKineticMove(const KineticMove::MoveDistanceArgs &param);
	void onKineticMoveEnd(const KineticMove::MoveEndArgs &param);

private:
	bool m_bElastic;
	bool m_bElasticDec;
	bool m_bScrollDown;
	float m_fElasticSpace;
	std::shared_ptr<KineticMove> m_pKineticMove;
};

}}

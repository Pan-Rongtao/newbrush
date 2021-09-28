#pragma once
#include "Object.h"
#include "newbrush/UserControl.h"
#include "newbrush/GestureAnalyse.h"
#include "newbrush/KineticMove.h"
#include "newbrush/MovePositionAnalyse.h"
#include "newbrush/ReboundScroll.h"
#include "newbrush/Log.h"

namespace nb
{
class NB_API PhysicsMovePage : public Node2D
{
public:
	PhysicsMovePage();
	PhysicsMovePage(const Rect &rc);
	PhysicsMovePage(float x, float y, float w, float h);

	void addPage(ref<Node2D> pageItem);
protected:
	virtual void onRender() override;

	virtual void onTouch(const TouchEventArgs &e) override;
	void jumpToPosition(float position);

private:
	void init();
	void onMousePress(Point pos);
	void onMouseMove(Point pos);
	void onMouseRelease(Point pos);
	void OnKineticScroll(const MoveDistanceEventArgs & e);
	void OnKineticScrollEnd(const MoveEndEventArgs & e);
private:
	std::vector<ref<Node2D>> m_vecPageItems;
	int m_itemcount;
	OrientationE m_itemOrientation;


	ref<CKineticMove> m_pKineticMove;
	ref<CGestureAnalyse> m_pGestureAnalyse;	//该对象分析鼠标手势，计算鼠标的滑动速度
	ref<CMovePositionAnalyse> m_pMovePositionAnalyse;

	bool m_bIsRunning;
	bool m_bIsPress;

	Point m_MouseLastMovePos;

	float m_flastOffset;

	float m_fAccel;//默认加速度
};
}
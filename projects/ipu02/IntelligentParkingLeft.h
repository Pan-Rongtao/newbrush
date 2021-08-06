#pragma once
#include "newbrush/Node2D.h"
#include "newbrush/Components.h"
#include "newbrush/Font.h"
#include "newbrush/UserControl.h"

#include "AnimationMgr.h"

namespace nb {
class IntelligentParkingLeft;
typedef ref<IntelligentParkingLeft> IntelligentParkingLeftRef;

class NB_API IntelligentParkingLeft : public Node2D//, public AnimationTimeOutEvent
{
public:

public:
	IntelligentParkingLeft(float x, float y, float w, float h);
	virtual ~IntelligentParkingLeft();

	static IntelligentParkingLeftRef createIntelligentParkingLeftRef(float x, float y, float w, float h);

	void onEnterMenu(int id);
	void onExitMenu();

protected:
	//virtual void onRender() override;
	
private:
	void initVirtualParking();
	void initRealParking();

	void onSwitchBtnParkingClick(const EventArgs &e);
	void onTick(const EventArgs & e);

	void onAnimationUpdate(const AnimationArgs & e);

private:
	ref<Node2D> m_NodeParkingCenterRef;
	ref<Node2D> m_NodeParkingTopRef;
	ref<Node2D> m_NodeParkingTopLeftRef;
	ref<Node2D> m_NodeParkingLeftRef;
	ref<Node2D> m_NodeParkingRightRef;
	ref<Node2D> m_NodeParkingBottomRef;
	ref<Node2D> m_NodeParkingBottomLeftRef;

	ref<Button> m_BtnParkingLeftHor0;
	ref<Button> m_BtnParkingLeftHor1;
	ref<Button> m_BtnParkingLeftHor2;
	ref<Button> m_BtnParkingLeftHor3;

	ref<Button> m_BtnParkingLeftVer0;
	ref<Button> m_BtnParkingLeftVer1;
	ref<Button> m_BtnParkingLeftBottomVer;

	ref<Button> m_BtnParkingRightHor0;
	ref<Button> m_BtnParkingRightHor1;
	ref<Button> m_BtnParkingRightHor2;
	ref<Button> m_BtnParkingRightHor3;

	ref<Button> m_BtnParkingRightVer0;
	ref<Button> m_BtnParkingRightVer1;
	ref<Button> m_BtnParkingRightBottomVer;

	ref<Node2D> m_NodeCarRef;

	ref<Node2D> m_NodeSubLineLeftRef;
	ref<Node2D> m_NodeSubLineRightRef;


	Timer m_timerAutoParking;

	AnimationCtrlData<float> m_AniMove;
	AnimationCtrlData<float> m_AniRotate;
	AnimationMgr m_AnimationMgr;
};
}

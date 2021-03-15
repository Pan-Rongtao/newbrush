#pragma once
#include "newbrush/Controls.h"
#include "newbrush/Application.h"
#include "newbrush/StateManager.h"
#include "newbrush/Animation.h"
#include "../Common.h"

using namespace nb;

class MyView : public ViewBase
{
public:
	virtual void init() override;
	virtual ref<Node> getRoot() override;



private:
	void initStateMachines();
	void onTick(const EventArgs &e);
	void setSpeed(int speed);

	ref<Node2D> m_root;
	ref<Node2D> m_LED_EleSteerLock;
	ref<Node2D> m_LED_OilPressure;
	ref<Node2D> m_LED_BrakeFluidLevel;
	ref<Node2D> m_LED_StartStop;
	ref<Node2D> m_LED_DayTime;
	ref<Node2D> m_LED_FrontFog;
	ref<Node2D> m_LED_RearFog;
	ref<Node2D> m_LED_HMA;
	ref<Node2D> m_LED_HighBeam;
	ref<Node2D> m_LED_Position;
	ref<Node2D> m_LED_LeftTurn;
	ref<Node2D> m_LED_SpeedLimit;
	ref<Node2D> m_LED_ACC;
	ref<Node2D> m_LED_LDW;
	ref<Node2D> m_LED_BSD;
	ref<Node2D> m_LED_FCW;
	ref<Node2D> m_LED_SeatBelt1;
	ref<Node2D> m_LED_SeatBelt2;
	ref<Node2D> m_LED_SeatBelt3;
	ref<Node2D> m_LED_SeatBelt4;
	ref<Node2D> m_LED_SeatBelt5;
	ref<Node2D> m_LED_EPC;
	ref<Node2D> m_LED_MILEmission;
	ref<Node2D> m_LED_EPB;
	ref<Node2D> m_LED_DrivingMode;
	ref<Node2D> m_LED_Charging;
	ref<Node2D> m_LED_RightTurn;
	ref<Node2D> m_LED_AVH;
	ref<Node2D> m_LED_CoolantTemp;
	ref<Node2D> m_LED_GearBox;
	ref<Node2D> m_LED_ElecStability;
	ref<Node2D> m_LED_ABS;
	ref<Node2D> m_LED_HDC;
	ref<Node2D> m_LED_Warning;
	ref<Node2D> m_LED_GPF;
	ref<Node2D> m_LED_EPS;
	ref<Node2D> m_LED_MaintenanceTip;
	ref<Node2D> m_LED_AirBag;
	ref<Node2D> m_LED_TPMS;

	ref<Node2D> m_DialLeftRoot;
	ref<Node2D> m_SpeedValue;
	ref<Node2D> m_SpeedPointer;
	ref<Node2D> m_DialRightRoot;
	ref<Node2D> m_RpmValue;
	ref<Node2D> m_ECU_Pointer;
	ref<Node2D> m_RpmPointer;

	ref<Node2D> m_TopMenu;
	ref<Node2D> m_Menu;

	ref<StateManager> m_smEleSteerLock;
	ref<StateManager> m_smHMA;
	ref<StateManager> m_smLeftTurn;
	ref<StateManager> m_smRightTurn;
	ref<StateManager> m_smDrivingMode;
	ref<StateManager> m_smCoolantTemp;

	Timer m_timerLeftTurn;
	Timer m_timerRightTurn;
	Timer m_timerHMA;

	FloatAnimation m_carAnimation;
};
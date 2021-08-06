#pragma once
#include "../Common.h"
#include "newbrush/UserControl.h"
#include "IntelligentParkingLeft.h"
#include "IntelligentParkingRight.h"
#include "IntelligentRemoteCtrlParking.h"

class IntelligentParkingView : public Node2D
{
public:
	enum CourseID
	{
		ID_Unknow = 0,
		ID_AutoParking,
		ID_RemoteParking,
		ID_SeltParking,
	};

public:
	IntelligentParkingView();

	void selectParking(int index);
	void setAutoParking();

protected:
	virtual void onTouch(const TouchEventArgs &e);

private:
	void onBtnClick(const EventArgs &e);
	void onSwitchBtnClick(const EventArgs &e);
	void onAutoParkingPlayTick(const EventArgs & e);

private:
	CourseID m_CurState;
	int m_nCurrentPage;

	ref<Node2D> m_BtnBackImage;
	ref<Button> m_BtnBack;
	ref<Node2D> m_TopBtnsRef;

	IntelligentParkingLeftRef m_NodeLeftRef;
	IntelligentParkingRightRef m_NodeRightRef;
	IntelligentRemoteCtrlParkingRef m_NodeRemoteCtrlParkingRef;

	ref<Button> m_btnAutoParking;
	ref<Button> m_btnCtrlParking;
	ref<Button> m_btnSeletParking;
	ref<Button> m_btnMemoryParking;
	ref<TextBlock> m_txtAutoParking;
	ref<TextBlock> m_txtCtrlParking;
	ref<TextBlock> m_txtSeletParking;
	ref<TextBlock> m_txtMemoryParking;

	Timer m_timerAutoParkingPlayer;
};
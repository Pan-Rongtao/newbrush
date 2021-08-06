#pragma once
#include "../Common.h"
#include "newbrush/StateManager.h"
#include "MainView.h"
#include "IntelligentParkingView.h"

class ManualParkingView : public Node2D
{
	RTTR_ENABLE();
public:
	ManualParkingView();
	

private:
	enum class TopView
	{
		None,
		Park,
		Mirror,
		Radar,
		BackLine,
		Set,
		TB2Dto3D,
	};

	enum class RadarState
	{
		None,
		Warning,
		Red,
		YellowRed,
		Yellow,
		Green,
	};

	enum class ViewDir
	{
		None,
		left,
		right,
		up,
		down,
		up1,
		up2,
		up3,
		down1,
		down2,
		down3
	};
	void ParkingSetView();
	void onBtnClick(const EventArgs &e);
	void onTBtnClick(const EventArgs &e);
	void swithPage(TopView page, bool check);

	void ParkingNormalView();
	void ParkingRadarView();
	void Parking2DView();
	void Parking3DView();


	void CameraBtnControl(int Data);
	void CameraBtnClick(ref<Button> Data, int* State);

	void CarViewDir(ViewDir Data);
	void WarningText(int data);

public:
	int nMirrorState;
	
	ref<TextBlock> m_txt;
	ref<Node2D> Main_Node2D;
	//top button
	int nReturn;
	int nPark;
	int nMirror;
	int nRadar;
	int nBackline;
	int nSet;

	ref<Button> m_btnReturn;
	ref<Button> m_btnPark;
	ref<Button> m_btnMirror;
	ref<Button> m_btnRadar;
	ref<Button> m_btnBackline;
	ref<Button> m_btnSet;
	
	ref<Node2D> imgCar;
	ref<StateManager> m_smCarLock;

	ref<Node2D> imgOutCarFLWarning;
	ref<Node2D> imgOutCarFRWarning;
	ref<Node2D> imgOutCarRFWarning;
	ref<Node2D> imgOutCarRRWarning;

	ref<StateManager> m_smBGRight;

	ref<Node2D> imgCarLine;
	ref<Node2D> imgCarRightLine;

	ref<Node2D> leftView_Node2D;
	ref<ToggleButton> m_t2Dto3D;
	int n2Dto3D;

	int nNormalLoadState;
	int nRadarLoadState;
	int n2DLoadState;
	int n3DLoadState;
	int nSetLoadState;

	ref<Node2D> leftNormalView_Node2D;
	ref<Node2D> leftLightView_Node2D;
	ref<Node2D> leftRadarView_Node2D;
	ref<Node2D> leftFourCameraView_Node2D;
	ref<Node2D> leftSixCameraView_Node2D;
	ref<Transform2D> imgCameraNormal_Transform;

	ref<Node2D> imgUpCenterLeft;
	ref<Node2D> imgUpCenterRight;
	ref<Node2D> imgUpRightRight;
	ref<Node2D> imgUpLeftLeft;
	ref<Node2D> imgCenterUpLeft;
	ref<Node2D> imgCenterUpRight;

	ref<Node2D> imgDownCenterLeft;
	ref<Node2D> imgDownCenterRight;
	ref<Node2D> imgDownRightRight;
	ref<Node2D> imgDownLeftLeft;
	ref<Node2D> imgCenterDownLeft;
	ref<Node2D> imgCenterDownRight;
	/**/
	int nRadarUpLeftLeft;
	int nRadarUpRightRight;
	int nRadarUpCenterLeft;
	int nRadarUpCenterRight;

	int nRadarDownLeftLeft;
	int nRadarDownRightRight;
	int nRadarDownCenterLeft;
	int nRadarDownCenterRight;

	int nRadarCenterLeftUp;
	int nRadarCenterRightUp;
	int nRadarCenterLeftDown;
	int nRadarCenterRightDown;

	//radar up
	ref<StateManager> m_smUpCenterLeftLock;
	ref<StateManager> m_smUpCenterRightLock;
	ref<StateManager> m_smUpRightRightLock;
	ref<StateManager> m_smUpLeftLeftLock;
	//radar down
	ref<StateManager> m_smDownCenterLeftLock;
	ref<StateManager> m_smDownCenterRightLock;
	ref<StateManager> m_smDownRightRightLock;
	ref<StateManager> m_smDownLeftLeftLock;
	//radar center
	ref<StateManager> m_smCenterUpLeftLock;
	ref<StateManager> m_smCenterUpRightLock;
	ref<StateManager> m_smCenterDownLeftLock;
	ref<StateManager> m_smCenterDownRightLock;
	
	//right
	ref<Node2D> rightView_Node2D;
	ref<Node2D> rightNormalView_Node2D;
	ref<Node2D> imgLine;
	ref<Node2D> picwarning1;
	ref<Node2D> picwarning2;
	ref<Node2D> menuset_Node2D;
	ref<Node2D> menusetbg;
	ref<TextBlock> m_settitle;
	ref<TextBlock> m_settextoneline;
	ref<TextBlock> m_settexttwoline;
	ref<TextBlock> m_settextthreeline;
	ref<TextBlock> m_settextfourline;
	ref<TextBlock> m_settextfiveline;

	ref<ToggleButton> m_tbtnone;
	ref<ToggleButton> m_tbtntwo;
	ref<ToggleButton> m_tbtnthree;
	ref<ToggleButton> m_tbtnfour;
	ref<ToggleButton> m_tbtnfive;

	ref<Node2D> menusetbgline1;
	ref<Node2D> menusetbgline2;
	ref<Node2D> menusetbgline3;
	ref<Node2D> menusetbgline4;

	ref<Button> m_btnmenuReturn;

	ref<Node2D> iconviewcar;
	ref<Node2D> iconviewdir;
	ref<Node2D> iconalert; 
	ref<Node2D> throughalert;

	ref<Node2D> warningtext;

	//Camera
	/**/

	int nFourCameraUp;
	int nFourCameraLeft;
	int nFourCameraRight;
	int nFourCameraDown;

	int nSixCameraUpLeft;
	int nSixCameraUpCenter;
	int nSixCameraUpRight;
	int nSixCameraDownLeft;
	int nSixCameraDownCenter;
	int nSixCameraDownRight;

	ref<Button> m_btnFourCameraUp;
	ref<Button> m_btnFourCameraLeft;
	ref<Button> m_btnFourCameraRight;
	ref<Button> m_btnFourCameraDown;

	ref<Button> m_btnSixCameraUpLeft;
	ref<Button> m_btnSixCameraUpCenter;
	ref<Button> m_btnSixCameraUpRight;
	ref<Button> m_btnSixCameraDownLeft;
	ref<Button> m_btnSixCameraDownCenter;
	ref<Button> m_btnSixCameraDownRight;
};
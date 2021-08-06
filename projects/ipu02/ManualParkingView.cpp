#include "ManualParkingView.h"

ManualParkingView::ManualParkingView()
{
	BrushLibrary::addImageBrush("bgBrush", RES_DIR"ipu02/manual_day.png");

	ref<Node2D> m_bg = createRef<Node2D>(0, 100, 600, 885);
	m_bg->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/ManualParkingBG.png")));
	addChild(m_bg); 

	
	 ref<Node2D> m_bg1 = createRef<Node2D>(605, 100, 1308, 884);
	 m_smBGRight = createRef<StateManager>(4);
	 (*m_smBGRight)[0]->assignProperty(m_bg1, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	 (*m_smBGRight)[1]->assignProperty(m_bg1, nb::prop<Node2D>("Background"), createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/ManualParkingBGRight.png")));
	 (*m_smBGRight)[2]->assignProperty(m_bg1, nb::prop<Node2D>("Background"), createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/2DToCamera.png")));
	 (*m_smBGRight)[3]->assignProperty(m_bg1, nb::prop<Node2D>("Background"), createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/3DFrontRight.png")));
	 m_smBGRight->gotoState(1);
	 addChild(m_bg1);
	 
	 nMirrorState = 0;
	 n2Dto3D = 1;

	 nReturn = 0;;
	 nPark = 0;;
	 nMirror = 0;;
	 nRadar = 0;;
	 nBackline = 0;;
	 nSet = 0;;
	
	 nSetLoadState = 0;
	 nFourCameraUp = 0;
	 nFourCameraLeft = 0;
	 nFourCameraRight = 0;
	 nFourCameraDown = 0;

	 nSixCameraUpLeft = 0;
	 nSixCameraUpCenter = 0;
	 nSixCameraUpRight = 0;
	 nSixCameraDownLeft = 0;
	 nSixCameraDownCenter = 0;
	 nSixCameraDownRight = 0;

	 nRadarUpLeftLeft = 1;
	 nRadarUpRightRight = 2;
	 nRadarUpCenterLeft = 3;
	 nRadarUpCenterRight = 4;

	 nRadarDownLeftLeft = 2;
	 nRadarDownRightRight = 1;
	 nRadarDownCenterLeft = 3;
	 nRadarDownCenterRight = 4;

	 nRadarCenterLeftUp = 3;
	 nRadarCenterRightUp = 1;
	 nRadarCenterLeftDown = 2;
	 nRadarCenterRightDown = 1;

	 nNormalLoadState = 0;
	 nRadarLoadState = 0;
	 n2DLoadState = 0;
	 n3DLoadState = 0;
	 
	TextureLibrary::addTextureAtlas("manual_day", RES_DIR"ipu02/manual_day.png", RES_DIR"ipu02/manual_day.txt");
	TextureLibrary::addTextureAtlas("manual_night", RES_DIR"ipu02/manual_night.png", RES_DIR"ipu02/manual_night.txt");

	//m_txt = createRef<TextBlock>(u8" 泊车影像界面 ");
	Main_Node2D = Node2D::createWithTextureFrameName("manual_day", "topbar/bg_topbar.png", true, 0.0f, 0.0f);
	auto imgBottombar = Node2D::createWithTextureFrameName("manual_day", "topbar/bg_topbar.png", true, 0, 980);

	m_btnReturn = Button::createWithTextureFrameName("manual_day", "topbar/autopark_btn_back.png", true, 46.0f, 0.0f);
	m_btnReturn->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

	m_btnPark = Button::createWithTextureFrameName("manual_day", "topbar/autopark_btn_park_nor.png", true, 633.0f, 0.0f);
	m_btnPark->setBkgndCheck(createRef<ImageBrush>("manual_day", "topbar/autopark_btn_park_sel.png"));
	m_btnPark->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

	m_btnMirror = Button::createWithTextureFrameName("manual_day", "topbar/autopark_btn_mirror_nor.png", true, 765.0f, 0.0f);
	m_btnMirror->setBkgndCheck(createRef<ImageBrush>("manual_day", "topbar/autopark_btn_mirror_sel.png"));
	m_btnMirror->Click += nbBindEventFunction(ManualParkingView::onBtnClick);
	
	m_btnRadar = Button::createWithTextureFrameName("manual_day", "topbar/autopark_btn_radar_nor.png", true, 909.0f, 0.0f);
	m_btnRadar->setBkgndCheck(createRef<ImageBrush>("manual_day", "topbar/autopark_btn_radar_sel.png"));
	m_btnRadar->Click += nbBindEventFunction(ManualParkingView::onBtnClick);
	
	m_btnBackline = Button::createWithTextureFrameName("manual_day", "topbar/btn_backline_nor.png", true, 1521.0f, 0.0f);
	m_btnBackline->setBkgndCheck(createRef<ImageBrush>("manual_day", "topbar/btn_backline_sel.png"));
	m_btnBackline->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

	m_btnSet = Button::createWithTextureFrameName("manual_day", "topbar/autopark_btn_set_nor.png", true, 1665.0f, 0.0f);
	m_btnSet->setBkgndCheck(createRef<ImageBrush>("manual_day", "topbar/autopark_btn_set_sel.png"));
	m_btnSet->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

	m_t2Dto3D = createRef<ToggleButton>(1065.0f, 19.0f, 400.0f, 62.0f);
	auto tb2Dto3DNormal = createRef<ImageBrush>("manual_day", "topbar/autopark_btn_23d_62px_nor.png");
	auto tb2Dto3DCheck = createRef<ImageBrush>("manual_day", "topbar/autopark_btn_23d_62px_nor.png");
	auto ticon2Dto3DNormal = createRef<ImageBrush>("manual_day", "topbar/autopark_btn_23d_62px_sel.png");
	auto rightnow2Dto3D = Node2D::createWithTextureFrameName("manual_day", "topbar/autopark_text_2d-sel.png", true, 0, 0);
	auto latter2Dto3D = Node2D::createWithTextureFrameName("manual_day", "topbar/autopark_text_3d-sel.png", true, 200, 0);
	m_t2Dto3D->setBkgndNormal(tb2Dto3DNormal);
	m_t2Dto3D->setBkgndPress(tb2Dto3DNormal);
	m_t2Dto3D->setBkgndCheck(tb2Dto3DCheck);
	m_t2Dto3D->setIcon(ticon2Dto3DNormal);
	m_t2Dto3D->setIconOffset({ 0.0f, 0.0f });
	m_t2Dto3D->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);
	m_t2Dto3D->addChild(rightnow2Dto3D);
	m_t2Dto3D->addChild(latter2Dto3D);

	Main_Node2D->addChild(m_btnReturn);
	Main_Node2D->addChild(m_btnPark);
	Main_Node2D->addChild(m_btnMirror);
	Main_Node2D->addChild(m_btnRadar);
	Main_Node2D->addChild(m_btnBackline);
	Main_Node2D->addChild(m_btnSet);
	Main_Node2D->addChild(imgBottombar);
	Main_Node2D->addChild(m_t2Dto3D);
	addChild(Main_Node2D);
	
	leftView_Node2D = createRef<Node2D>(0.0f, 0.0f, 600.0f, 880.0f);
	leftNormalView_Node2D = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	leftRadarView_Node2D = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	leftFourCameraView_Node2D = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	leftSixCameraView_Node2D = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	leftLightView_Node2D = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);

	imgCar = Node2D::createWithTextureFrameName("manual_day", "car/autopark_pic_car.png", true, 150, 200);
	m_smCarLock = createRef<StateManager>(4);
	(*m_smCarLock)[0]->assignProperty(imgCar, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	(*m_smCarLock)[1]->assignProperty(imgCar, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "car/autopark_pic_car.png"));
	(*m_smCarLock)[2]->assignProperty(imgCar, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "car/autopark_pic_car2.png"));
	(*m_smCarLock)[3]->assignProperty(imgCar, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "car/autopark_pic_warningcar.png"));
	m_smCarLock->gotoState(1);
	leftView_Node2D->addChild(imgCar);
	addChild(leftView_Node2D);

	//right view
	rightView_Node2D = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	menuset_Node2D = createRef<Node2D>(134.0f, 40.0f, 1040.0f, 705.0f);
	rightNormalView_Node2D = createRef<Node2D>(0.0f, 0.0f, 1310.0f, 880.0f);

	iconviewcar = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_view_car.png", true, 12.0, 3.0);
	CarViewDir(ManualParkingView::ViewDir::down1);

	iconalert = Node2D::createWithTextureFrameName("manual_day", "icon_alert2.png", true, 32.0, 135.0);
	throughalert = Node2D::createWithTextureFrameName("manual_day", "icon_throughalert.png", true, 32.0, 235.0);

	WarningText(2);
	rightView_Node2D->addChild(rightNormalView_Node2D);
	rightView_Node2D->addChild(iconviewcar);
	rightView_Node2D->addChild(iconalert);
	rightView_Node2D->addChild(throughalert);
	rightView_Node2D->addChild(iconviewdir);
	
	addChild(rightView_Node2D);
	
}

void ManualParkingView::onTBtnClick(const EventArgs & e)
{
	Log::info("On Toggle Button Click!\n");
	if (e.sender == m_tbtnone.get())
	{
		Log::info("on toggle changed={}", m_tbtnone->isChecked());
		if (m_tbtnone->isChecked())
		{
			ParkingNormalView();
			leftNormalView_Node2D->setVisibility(VisibilityE::Visible);
		}
		else
		{
			leftNormalView_Node2D->setVisibility(VisibilityE::Hidden);
		}
	}
	else if (e.sender == m_tbtntwo.get())
	{

	}
	else if (e.sender == m_tbtnthree.get())
	{
		if (m_tbtnthree->isChecked())
		{
			m_smCarLock->gotoState(2);
		}
		else
		{
			m_smCarLock->gotoState(1);
		}
	}
	else if (e.sender == m_tbtnfour.get())
	{
		if (m_tbtnfour->isChecked())
		{
			ParkingRadarView();
			leftRadarView_Node2D->setVisibility(VisibilityE::Visible);
		}
		else
		{
			leftRadarView_Node2D->setVisibility(VisibilityE::Hidden);
		}
	}
	else if (e.sender == m_tbtnfive.get())
	{
		if (m_tbtnfive->isChecked())
		{
			ParkingNormalView();
			leftLightView_Node2D->setVisibility(VisibilityE::Visible);
		}
		else
		{
			leftLightView_Node2D->setVisibility(VisibilityE::Hidden);
		}
		
	}
	else if (e.sender == m_t2Dto3D.get())
	{
		if (m_t2Dto3D->isChecked())
		{
			n2Dto3D = 2;
			leftFourCameraView_Node2D->setVisibility(VisibilityE::Hidden);
			m_smBGRight->gotoState(3);
			if (nMirrorState == 1)
			{
				Parking3DView();
			}
		}
		else
		{
			leftSixCameraView_Node2D->setVisibility(VisibilityE::Hidden);
			m_smBGRight->gotoState(2);
			n2Dto3D = 1;
			if (nMirrorState == 1)
			{
				Parking2DView();
			}
		}
	}
	else
	{

	}
}

void ManualParkingView::swithPage(TopView page, bool check)
{
	switch (page)
	{
	case TopView::Park:
	{
		
		break;
	}
	case TopView::Mirror:
	{
		if (check)
		{
			nMirrorState = 1;
			if (n2Dto3D == 1)
			{
				m_smBGRight->gotoState(3);
				leftSixCameraView_Node2D->setVisibility(VisibilityE::Hidden);
				rightNormalView_Node2D->setVisibility(VisibilityE::Hidden);
				Parking2DView();
			}
			else if (n2Dto3D == 2)
			{
				m_smBGRight->gotoState(2);
				leftFourCameraView_Node2D->setVisibility(VisibilityE::Hidden);
				rightNormalView_Node2D->setVisibility(VisibilityE::Hidden);
				Parking3DView();
			}
			else{}
		}
		else
		{
			leftFourCameraView_Node2D->setVisibility(VisibilityE::Hidden);
			leftSixCameraView_Node2D->setVisibility(VisibilityE::Hidden);
			rightNormalView_Node2D->setVisibility(VisibilityE::Hidden);
		}

		break;
	}
	case TopView::Radar:
	{
		if (check)
		{
			ParkingRadarView();
		}
		else
		{
			leftRadarView_Node2D->setVisibility(VisibilityE::Hidden);
		}

		break;
	}
	case TopView::BackLine:
	{
		if (check)
		{
			ParkingNormalView();
			m_smBGRight->gotoState(1);
		}
		else
		{
			leftLightView_Node2D->setVisibility(VisibilityE::Hidden);
			leftNormalView_Node2D->setVisibility(VisibilityE::Hidden);
			rightNormalView_Node2D->setVisibility(VisibilityE::Hidden);
		}
		break;
	}
	case TopView::Set:
	{
		if (check)
		{
			ParkingSetView();
			rightNormalView_Node2D->setVisibility(VisibilityE::Visible);
		}
		else
		{
			rightNormalView_Node2D->setVisibility(VisibilityE::Hidden);
			menuset_Node2D->setVisibility(VisibilityE::Hidden);
		}

		break;
	}
	default:
	{
		break;
	}
	}
}

void ManualParkingView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnReturn.get())
	{
		MainView::get()->switchView<IntelligentParkingView>();
	}
	else if (e.sender == m_btnPark.get())
	{
		MainView::get()->switchView<IntelligentParkingView>();
	}
	else if (e.sender == m_btnMirror.get())
	{
		Log::info("On Click &= %d !\n", m_btnMirror->isChecked());
		CameraBtnClick(m_btnMirror, &nMirror);
		swithPage(TopView::Mirror, nMirror);
	}
	else if (e.sender == m_btnRadar.get())
	{
		CameraBtnClick(m_btnRadar, &nRadar);
		swithPage(TopView::Radar, nRadar);
	}
	else if (e.sender == m_btnBackline.get())
	{
		CameraBtnClick(m_btnBackline, &nBackline);
		swithPage(TopView::BackLine, nBackline);
	}
	else if (e.sender == m_btnSet.get())
	{
		CameraBtnClick(m_btnSet, &nSet);
		swithPage(TopView::Set, nSet);
	}
	else if (e.sender == m_btnFourCameraUp.get())
	{
		CameraBtnControl(1);
	}
	else if (e.sender == m_btnFourCameraLeft.get())
	{
		CameraBtnControl(2);
	}
	else if (e.sender == m_btnFourCameraRight.get())
	{
		CameraBtnControl(3);
	}
	else if (e.sender == m_btnFourCameraDown.get())
	{
		CameraBtnControl(4);
	}
	else if (e.sender == m_btnSixCameraUpLeft.get())
	{
		CameraBtnControl(5);
	}
	else if (e.sender == m_btnSixCameraUpCenter.get())
	{
		CameraBtnControl(6);
	}
	else if (e.sender == m_btnSixCameraUpRight.get())
	{
		CameraBtnControl(7);
	}
	else if (e.sender == m_btnSixCameraDownLeft.get())
	{
		CameraBtnControl(8);
	}
	else if (e.sender == m_btnSixCameraDownCenter.get())
	{
		CameraBtnControl(9);
	}
	else if (e.sender == m_btnSixCameraDownRight.get())
	{
		CameraBtnControl(10);
	}
	else if (e.sender == m_btnmenuReturn.get())
	{
		CameraBtnClick(m_btnSet, &nSet);
		swithPage(TopView::Set, nSet);
	}
	
}
void ManualParkingView::ParkingNormalView()
{
	if (nNormalLoadState == 0)
	{
		nNormalLoadState = 1;
		//PageNormal
		imgOutCarFLWarning = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left1.png", true, 40, 140);
		imgOutCarFRWarning = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left1.png", true, 448, 140);
		imgOutCarRFWarning = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left1.png", true, 40, 736);
		imgOutCarRRWarning = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left1.png", true, 448, 736);
		imgOutCarFRWarning->setTransform(createRef<RotateTransform2D>(180.0f, 50.0f, 50.0f));
		imgOutCarRRWarning->setTransform(createRef<RotateTransform2D>(180.0f, 50.0f, 50.0f));
		leftLightView_Node2D->addChild(imgOutCarFLWarning);
		leftLightView_Node2D->addChild(imgOutCarFRWarning);
		leftLightView_Node2D->addChild(imgOutCarRFWarning);
		leftLightView_Node2D->addChild(imgOutCarRRWarning);

		imgCarLine = Node2D::createWithTextureFrameName("manual_day", "autopark_pic_subline.png", true, 160, 500);

		imgCarRightLine = createRef<Node2D>(180, 0, 225, 858);
		imgCarRightLine->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/line.png")));

		leftNormalView_Node2D->addChild(imgCarRightLine);
		leftNormalView_Node2D->addChild(imgCarLine);
		leftView_Node2D->addChild(leftNormalView_Node2D);
		leftView_Node2D->addChild(leftLightView_Node2D);

		//right
		imgLine = Node2D::createWithTextureFrameName("manual_day", "autopark_btn_backupline.png", true, 894.0 - 610.0, 428.0 - 100.0);
		picwarning1 = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left2.png", true, 750.0 - 610.0, 659.0 - 100.0);
		picwarning2 = Node2D::createWithTextureFrameName("manual_day", "pic_warning_left2.png", true, 1554.0 - 610.0, 656.0 - 100.0);
		picwarning2->setTransform(createRef<RotateTransform2D>(180.0f, 115.0f, 55.0f));

		rightNormalView_Node2D->addChild(imgLine);
		rightNormalView_Node2D->addChild(picwarning1);
		rightNormalView_Node2D->addChild(picwarning2);

	}
	else
	{

		
	}
	leftLightView_Node2D->setVisibility(VisibilityE::Visible);
	rightNormalView_Node2D->setVisibility(VisibilityE::Visible);
	leftNormalView_Node2D->setVisibility(VisibilityE::Visible);
}
void ManualParkingView::ParkingRadarView()
{
	if (0 == nRadarLoadState)
	{
		nRadarLoadState = 1;
		//up
		imgUpCenterLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_41.png", false, 150, 103);
		m_smUpCenterLeftLock = createRef<StateManager>(6);
		(*m_smUpCenterLeftLock)[0]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smUpCenterLeftLock)[1]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_41.png"));
		(*m_smUpCenterLeftLock)[2]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_31.png"));
		(*m_smUpCenterLeftLock)[3]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_23.png"));
		(*m_smUpCenterLeftLock)[4]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_13.png"));
		(*m_smUpCenterLeftLock)[5]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_13.png"));
		m_smUpCenterLeftLock->gotoState(nRadarUpCenterLeft);
		leftRadarView_Node2D->addChild(imgUpCenterLeft);

		imgUpCenterRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_42.png", false, 150, 103);
		m_smUpCenterRightLock = createRef<StateManager>(6);
		(*m_smUpCenterRightLock)[0]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smUpCenterRightLock)[1]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_42.png"));
		(*m_smUpCenterRightLock)[2]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_32.png"));
		(*m_smUpCenterRightLock)[3]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_24.png"));
		(*m_smUpCenterRightLock)[4]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_14.png"));
		(*m_smUpCenterRightLock)[5]->assignProperty(imgUpCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_14.png"));
		m_smUpCenterRightLock->gotoState(nRadarUpCenterRight);
		leftRadarView_Node2D->addChild(imgUpCenterRight);

		imgUpLeftLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_15.png", false, 150, 103);
		m_smUpLeftLeftLock = createRef<StateManager>(4);
		(*m_smUpLeftLeftLock)[0]->assignProperty(imgUpLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smUpLeftLeftLock)[1]->assignProperty(imgUpLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_15.png"));
		(*m_smUpLeftLeftLock)[2]->assignProperty(imgUpLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_25.png"));
		(*m_smUpLeftLeftLock)[3]->assignProperty(imgUpLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_15.png"));
		m_smUpLeftLeftLock->gotoState(nRadarUpLeftLeft);
		leftRadarView_Node2D->addChild(imgUpLeftLeft);

		imgUpRightRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_12.png", false, 150, 103);
		m_smUpRightRightLock = createRef<StateManager>(4);
		(*m_smUpRightRightLock)[0]->assignProperty(imgUpRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smUpRightRightLock)[1]->assignProperty(imgUpRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_12.png"));
		(*m_smUpRightRightLock)[2]->assignProperty(imgUpRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_22.png"));
		(*m_smUpRightRightLock)[3]->assignProperty(imgUpRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_12.png"));
		m_smUpRightRightLock->gotoState(nRadarUpRightRight);
		leftRadarView_Node2D->addChild(imgUpRightRight);

		//down
		imgDownCenterLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_41.png", false, 150, 103);
		m_smDownCenterLeftLock = createRef<StateManager>(6);
		(*m_smDownCenterLeftLock)[0]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smDownCenterLeftLock)[1]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_41.png"));
		(*m_smDownCenterLeftLock)[2]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_31.png"));
		(*m_smDownCenterLeftLock)[3]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_23.png"));
		(*m_smDownCenterLeftLock)[4]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_13.png"));
		(*m_smDownCenterLeftLock)[5]->assignProperty(imgDownCenterLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_23.png"));
		m_smDownCenterLeftLock->gotoState(nRadarDownCenterLeft);
		leftRadarView_Node2D->addChild(imgDownCenterLeft);

		imgDownCenterRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_42.png", false, 150, 103);
		m_smDownCenterRightLock = createRef<StateManager>(6);
		(*m_smDownCenterRightLock)[0]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smDownCenterRightLock)[1]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_42.png"));
		(*m_smDownCenterRightLock)[2]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_32.png"));
		(*m_smDownCenterRightLock)[3]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_24.png"));
		(*m_smDownCenterRightLock)[4]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_14.png"));
		(*m_smDownCenterRightLock)[5]->assignProperty(imgDownCenterRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_24.png"));
		m_smDownCenterRightLock->gotoState(nRadarDownCenterRight);
		leftRadarView_Node2D->addChild(imgDownCenterRight);

		imgDownLeftLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_15.png", false, 150, 103);
		m_smDownLeftLeftLock = createRef<StateManager>(6);
		(*m_smDownLeftLeftLock)[0]->assignProperty(imgDownLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smDownLeftLeftLock)[1]->assignProperty(imgDownLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_15.png"));
		(*m_smDownLeftLeftLock)[2]->assignProperty(imgDownLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_25.png"));
		(*m_smDownLeftLeftLock)[3]->assignProperty(imgDownLeftLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_25.png"));
		m_smDownLeftLeftLock->gotoState(nRadarDownLeftLeft);
		leftRadarView_Node2D->addChild(imgDownLeftLeft);
		imgDownRightRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_12.png", false, 150, 103);
		m_smDownRightRightLock = createRef<StateManager>(6);
		(*m_smDownRightRightLock)[0]->assignProperty(imgDownRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smDownRightRightLock)[1]->assignProperty(imgDownRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_12.png"));
		(*m_smDownRightRightLock)[2]->assignProperty(imgDownRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_22.png"));
		(*m_smDownRightRightLock)[3]->assignProperty(imgDownRightRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_22.png"));
		m_smDownRightRightLock->gotoState(nRadarDownRightRight);
		leftRadarView_Node2D->addChild(imgDownRightRight);

		//center
		imgCenterUpLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_11.png", false, 150, 103);
		m_smCenterUpLeftLock = createRef<StateManager>(6);
		(*m_smCenterUpLeftLock)[0]->assignProperty(imgCenterUpLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smCenterUpLeftLock)[1]->assignProperty(imgCenterUpLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_11.png"));
		(*m_smCenterUpLeftLock)[2]->assignProperty(imgCenterUpLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_21.png"));
		(*m_smCenterUpLeftLock)[3]->assignProperty(imgCenterUpLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_11.png"));
		m_smCenterUpLeftLock->gotoState(nRadarCenterLeftUp);
		leftRadarView_Node2D->addChild(imgCenterUpLeft);

		imgCenterUpRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_redup_16.png", false, 150, 103);
		m_smCenterUpRightLock = createRef<StateManager>(6);
		(*m_smCenterUpRightLock)[0]->assignProperty(imgCenterUpRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smCenterUpRightLock)[1]->assignProperty(imgCenterUpRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_16.png"));
		(*m_smCenterUpRightLock)[2]->assignProperty(imgCenterUpRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_redup_26.png"));
		(*m_smCenterUpRightLock)[3]->assignProperty(imgCenterUpRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_redup_alert_16.png"));
		m_smCenterUpRightLock->gotoState(nRadarCenterRightUp);
		leftRadarView_Node2D->addChild(imgCenterUpRight);

		imgCenterDownLeft = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_11.png", false, 150, 103);
		m_smCenterDownLeftLock = createRef<StateManager>(6);
		(*m_smCenterDownLeftLock)[0]->assignProperty(imgCenterDownLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smCenterDownLeftLock)[1]->assignProperty(imgCenterDownLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_11.png"));
		(*m_smCenterDownLeftLock)[2]->assignProperty(imgCenterDownLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_21.png"));
		(*m_smCenterDownLeftLock)[3]->assignProperty(imgCenterDownLeft, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_21.png"));
		m_smCenterDownLeftLock->gotoState(nRadarCenterLeftDown);
		leftRadarView_Node2D->addChild(imgCenterDownLeft);

		imgCenterDownRight = Node2D::createWithTextureFrameName("manual_day", "radar_topversion/autopark_pic_reddown_16.png", false, 150, 103);
		m_smCenterDownRightLock = createRef<StateManager>(6);
		(*m_smCenterDownRightLock)[0]->assignProperty(imgCenterDownRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
		(*m_smCenterDownRightLock)[1]->assignProperty(imgCenterDownRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_16.png"));
		(*m_smCenterDownRightLock)[2]->assignProperty(imgCenterDownRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_topversion/autopark_pic_reddown_26.png"));
		(*m_smCenterDownRightLock)[3]->assignProperty(imgCenterDownRight, nb::prop<Node2D>("Background"), createRef<ImageBrush>("manual_day", "radar_warn/autopark_pic_reddown_alert_26.png"));
		m_smCenterDownRightLock->gotoState(nRadarCenterRightDown);
		leftRadarView_Node2D->addChild(imgCenterDownRight);
		leftView_Node2D->addChild(leftRadarView_Node2D);
	}
	leftRadarView_Node2D->setVisibility(VisibilityE::Visible);

}

void ManualParkingView::ParkingSetView()
{
	if (0 == nSetLoadState)
	{
		nSetLoadState = 1;
		menusetbg = createRef<Node2D>();
		menusetbg->setBackground(SolidColorBrush::floralWhite());
		m_settitle = createRef<TextBlock>(u8" 设置 ");
		m_settitle->setPosition(Point(1227.0 - 610.0 - 134.0, 186.4 - 100.0 - 40.0));
		m_btnmenuReturn = Button::createWithTextureFrameName("manual_day", "autopark_btn_close_nor.png", true, 1700.0 - 610.0 - 134.0, 193.0 - 140.0);
		m_btnmenuReturn->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_settextoneline = createRef<TextBlock>(u8" 轨迹线 ");
		m_settextoneline->setPosition(Point(804.0 - 610.0 - 134.0, 281.0 - 100.0 - 40.0));
		m_settexttwoline = createRef<TextBlock>(u8" P档退出 ");
		m_settexttwoline->setPosition(Point(804.0 - 610.0 - 134.0, 396.0 - 100.0 - 40.0));
		m_settextthreeline = createRef<TextBlock>(u8" 透明底盘 ");
		m_settextthreeline->setPosition(Point(804.0 - 610.0 - 134.0, 511.0 - 100.0 - 40.0));
		m_settextfourline = createRef<TextBlock>(u8" 雷达激活全景 ");
		m_settextfourline->setPosition(Point(804.0 - 610.0 - 134.0, 624.0 - 100.0 - 40.0));
		m_settextfiveline = createRef<TextBlock>(u8" 转向灯激活全景 ");
		m_settextfiveline->setPosition(Point(804.0 - 610.0 - 134.0, 739.0 - 100.0 - 40.0));

		m_tbtnone = createRef<ToggleButton>(1641.0 - 610.0 - 134.0, 280.0 - 100.0 - 40.0, 84.0f, 46.0f);
		auto bkgNormal = createRef<ImageBrush>("manual_day", "autopark_btn_button_nor.png");
		auto bkgCheck = createRef<ImageBrush>("manual_day", "autopark_btn_button_sel.png");
		auto iconNormal = createRef<ImageBrush>("manual_day", "autopark_btn_button_dot.png");
		m_tbtnone->setBkgndNormal(bkgNormal);
		m_tbtnone->setBkgndPress(bkgNormal);
		m_tbtnone->setBkgndCheck(bkgCheck);
		m_tbtnone->setIcon(iconNormal);
		m_tbtnone->setIconOffset({ -10.0f, -5.0f });
		m_tbtnone->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);

		m_tbtntwo = createRef<ToggleButton>(1404.0 - 610.0 - 134.0, 385.0 - 100.0 - 40.0, 320.0f, 56.0f);
		auto tbkgNormal = createRef<ImageBrush>("manual_day", "autopark_btn_changbutton_56px_nor.png");
		auto tbkgCheck = createRef<ImageBrush>("manual_day", "autopark_btn_changbutton_56px_nor.png");
		auto ticonNormal = createRef<ImageBrush>("manual_day", "autopark_btn_changbutton_56px_sel.png");
		auto rightnow = createRef<TextBlock>(u8"立刻");
		rightnow->setPosition(Point(53.0, 14.0));
		auto latter = createRef<TextBlock>(u8"30秒后");
		latter->setPosition(Point(194.0, 14.0));
		m_tbtntwo->setBkgndNormal(tbkgNormal);
		m_tbtntwo->setBkgndPress(tbkgNormal);
		m_tbtntwo->setBkgndCheck(tbkgCheck);
		m_tbtntwo->setIcon(ticonNormal);
		m_tbtntwo->setIconOffset({ 0.0f, 0.0f });
		m_tbtntwo->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);
		m_tbtntwo->addChild(rightnow);
		m_tbtntwo->addChild(latter);


		m_tbtnthree = createRef<ToggleButton>(1641.0 - 610.0 - 134.0, 508.0 - 100.0 - 40.0, 84.0f, 46.0f);
		m_tbtnthree->setBkgndNormal(bkgNormal);
		m_tbtnthree->setBkgndPress(bkgNormal);
		m_tbtnthree->setBkgndCheck(bkgCheck);
		m_tbtnthree->setIcon(iconNormal);
		m_tbtnthree->setIconOffset({ -10.0f, -5.0f });
		m_tbtnthree->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);

		m_tbtnfour = createRef<ToggleButton>(1641.0 - 610.0 - 134.0, 622.0 - 100.0 - 40.0, 84.0f, 46.0f);
		m_tbtnfour->setBkgndNormal(bkgNormal);
		m_tbtnfour->setBkgndPress(bkgNormal);
		m_tbtnfour->setBkgndCheck(bkgCheck);
		m_tbtnfour->setIcon(iconNormal);
		m_tbtnfour->setIconOffset({ -10.0f, -5.0f });
		m_tbtnfour->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);

		m_tbtnfive = createRef<ToggleButton>(1641.0 - 610.0 - 134.0, 735.0 - 100.0 - 40.0, 84.0f, 46.0f);
		m_tbtnfive->setBkgndNormal(bkgNormal);
		m_tbtnfive->setBkgndPress(bkgNormal);
		m_tbtnfive->setBkgndCheck(bkgCheck);
		m_tbtnfive->setIcon(iconNormal);
		m_tbtnfive->setIconOffset({ -10.0f, -5.0f });
		m_tbtnfive->CheckChanged += nbBindEventFunction(ManualParkingView::onTBtnClick);

		menusetbgline1 = createRef<Node2D>(804.0 - 744.0, 355.0 - 140.0, 920.0f, 2.0f);
		menusetbgline1->setBackground(SolidColorBrush::darkSlateGray());
		menusetbgline2 = createRef<Node2D>(804.0 - 744.0, 469.0 - 140.0, 920.0f, 2.0f);
		menusetbgline2->setBackground(SolidColorBrush::darkSlateGray());
		menusetbgline3 = createRef<Node2D>(804.0 - 744.0, 583.0 - 140.0, 920.0f, 2.0f);
		menusetbgline3->setBackground(SolidColorBrush::darkSlateGray());
		menusetbgline4 = createRef<Node2D>(804.0 - 744.0, 697.0 - 140.0, 920.0f, 2.0f);
		menusetbgline4->setBackground(SolidColorBrush::darkSlateGray());

		menuset_Node2D->addChild(menusetbg);
		menuset_Node2D->addChild(m_settitle);
		menuset_Node2D->addChild(m_btnmenuReturn);
		menuset_Node2D->addChild(m_settextoneline);
		menuset_Node2D->addChild(m_settexttwoline);
		menuset_Node2D->addChild(m_settextthreeline);
		menuset_Node2D->addChild(m_settextfourline);
		menuset_Node2D->addChild(m_settextfiveline);
		menuset_Node2D->addChild(m_tbtnone);
		menuset_Node2D->addChild(m_tbtntwo);
		menuset_Node2D->addChild(m_tbtnthree);
		menuset_Node2D->addChild(m_tbtnfour);
		menuset_Node2D->addChild(m_tbtnfive);
		menuset_Node2D->addChild(menusetbgline1);
		menuset_Node2D->addChild(menusetbgline2);
		menuset_Node2D->addChild(menusetbgline3);
		menuset_Node2D->addChild(menusetbgline4);
		rightView_Node2D->addChild(menuset_Node2D);
	}
	menuset_Node2D->setVisibility(VisibilityE::Visible);
}

void ManualParkingView::Parking2DView()
{
	//PageFourCamera
	/**/
	if (0 == n2DLoadState)
	{
		n2DLoadState = 1;
		m_btnFourCameraUp = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 250.0f, 44.0f);
		m_btnFourCameraUp->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnFourCameraUp->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnFourCameraUp->setTransform(createRef<RotateTransform2D>(-135.0f, 50.0f, 50.0f));
		m_btnFourCameraUp->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnFourCameraLeft = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 52.0f, 403.0f);
		m_btnFourCameraLeft->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnFourCameraLeft->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnFourCameraLeft->setTransform(createRef<RotateTransform2D>(135.0f, 50.0f, 50.0f));
		m_btnFourCameraLeft->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnFourCameraRight = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 448.0f, 403.0f);
		m_btnFourCameraRight->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnFourCameraRight->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnFourCameraRight->setTransform(createRef<RotateTransform2D>(-45.0f, 50.0f, 50.0f));
		m_btnFourCameraRight->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnFourCameraDown = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 250.0f, 736.0f);
		m_btnFourCameraDown->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnFourCameraDown->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnFourCameraDown->setTransform(createRef<RotateTransform2D>(45.0f, 50.0f, 50.0f));
		m_btnFourCameraDown->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		leftFourCameraView_Node2D->addChild(m_btnFourCameraUp);
		leftFourCameraView_Node2D->addChild(m_btnFourCameraLeft);
		leftFourCameraView_Node2D->addChild(m_btnFourCameraRight);
		leftFourCameraView_Node2D->addChild(m_btnFourCameraDown);
		leftView_Node2D->addChild(leftFourCameraView_Node2D);
	}

	leftFourCameraView_Node2D->setVisibility(VisibilityE::Visible);
}

void ManualParkingView::Parking3DView()
{
	//PageSixCamera
	/**/
	if (0 == n3DLoadState)
	{
		n3DLoadState = 1;
		m_btnSixCameraUpLeft = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 64.0f, 44.0f);
		m_btnSixCameraUpLeft->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraUpLeft->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraUpLeft->setTransform(createRef<RotateTransform2D>(0.0f, 50.0f, 50.0f));
		m_btnSixCameraUpLeft->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnSixCameraUpCenter = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 250.0f, 44.0f);
		m_btnSixCameraUpCenter->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraUpCenter->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraUpCenter->setTransform(createRef<RotateTransform2D>(45.0f, 50.0f, 50.0f));
		m_btnSixCameraUpCenter->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnSixCameraUpRight = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 436.0f, 44.0f);
		m_btnSixCameraUpRight->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraUpRight->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraUpRight->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
		m_btnSixCameraUpRight->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnSixCameraDownLeft = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 64.0f, 736.0f);
		m_btnSixCameraDownLeft->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraDownLeft->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraDownLeft->setTransform(createRef<RotateTransform2D>(-90.0f, 50.0f, 50.0f));
		m_btnSixCameraDownLeft->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnSixCameraDownCenter = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 250.0f, 736.0f);
		m_btnSixCameraDownCenter->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraDownCenter->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraDownCenter->setTransform(createRef<RotateTransform2D>(-135.0f, 50.0f, 50.0f));
		m_btnSixCameraDownCenter->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		m_btnSixCameraDownRight = Button::createWithTextureFrameName("manual_day", "cam/autopark_btn_camera2_nor.png", true, 436.0f, 736.0f);
		m_btnSixCameraDownRight->setBkgndCheck(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"ipu02/manual/day/cam/autopark_btn_camera2_pre.png")));
		m_btnSixCameraDownRight->setBkgndDisable(createRef<ImageBrush>("manual_day", "cam/autopark_btn_camera2_fault.png"));
		m_btnSixCameraDownRight->setTransform(createRef<RotateTransform2D>(180.0f, 50.0f, 50.0f));
		m_btnSixCameraDownRight->Click += nbBindEventFunction(ManualParkingView::onBtnClick);

		leftSixCameraView_Node2D->addChild(m_btnSixCameraUpLeft);
		leftSixCameraView_Node2D->addChild(m_btnSixCameraUpCenter);
		leftSixCameraView_Node2D->addChild(m_btnSixCameraUpRight);
		leftSixCameraView_Node2D->addChild(m_btnSixCameraDownLeft);
		leftSixCameraView_Node2D->addChild(m_btnSixCameraDownCenter);
		leftSixCameraView_Node2D->addChild(m_btnSixCameraDownRight);
		leftView_Node2D->addChild(leftSixCameraView_Node2D);
	}
	leftSixCameraView_Node2D->setVisibility(VisibilityE::Visible);
}



void ManualParkingView::CameraBtnClick(ref<Button> Data, int* State)
{
	if (*State == 1)
	{
		*State = 0;
		Data->setCheck(*State);
	}
	else if (0 == *State)
	{
		*State = 1;
		Data->setCheck(*State);
	}

}

void ManualParkingView::CameraBtnControl(int Data)
{
	switch (Data)
	{
	case 1:
	{
		CameraBtnClick(m_btnFourCameraUp, &nFourCameraUp);
		break;
	}
	case 2:
	{
		CameraBtnClick(m_btnFourCameraLeft, &nFourCameraLeft);
		break;
	}
	case 3:
	{
		CameraBtnClick(m_btnFourCameraRight, &nFourCameraRight);
		break;
	}
	case 4:
	{
		CameraBtnClick(m_btnFourCameraDown, &nFourCameraDown);
		break;
	}
	case 5:
	{
		CameraBtnClick(m_btnSixCameraUpLeft, &nSixCameraUpLeft);
		break;
	}
	case 6:
	{
		CameraBtnClick(m_btnSixCameraUpCenter, &nSixCameraUpCenter);
		break;
	}
	case 7:
	{
		CameraBtnClick(m_btnSixCameraUpRight, &nSixCameraUpRight);
		break;
	}
	case 8:
	{
		CameraBtnClick(m_btnSixCameraDownLeft, &nSixCameraDownLeft);
		break;
	}
	case 9:
	{
		CameraBtnClick(m_btnSixCameraDownCenter, &nSixCameraDownCenter);
		break;
	}
	case 10:
	{
		CameraBtnClick(m_btnSixCameraDownRight, &nSixCameraDownRight);
		break;
	}
	default:
	{
		break;
	}
	}
}

void ManualParkingView::CarViewDir(ViewDir Data)
{
	switch (Data)
	{
	case ManualParkingView::ViewDir::None:

		break;
	case ManualParkingView::ViewDir::left:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_2dview_left.png", true, 12.0, 3.0);
		break;
	case ManualParkingView::ViewDir::right:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_2dview_left.png", true, 12.0, 3.0);
		iconviewdir->setTransform(createRef<RotateTransform2D>(180.0f, 70.0f, 70.0f));
		break;
	case ManualParkingView::ViewDir::up:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_2dview_up.png", true, 12.0, 3.0);
		break;
	case ManualParkingView::ViewDir::down:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_2dview_up.png", true, 12.0, 3.0);
		iconviewdir->setTransform(createRef<RotateTransform2D>(180.0f, 70.0f, 70.0f));
		break;
	case ManualParkingView::ViewDir::up1:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up1.png", true, 12.0, 3.0);
		break;
	case ManualParkingView::ViewDir::up2:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up2.png", true, 12.0, 3.0);
		break;
	case ManualParkingView::ViewDir::up3:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up3.png", true, 12.0, 3.0);
		break;
	case ManualParkingView::ViewDir::down1:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up1.png", true, 12.0, 3.0);
		iconviewdir->setTransform(createRef<RotateTransform2D>(180.0f, 70.0f, 70.0f));
		break;
	case ManualParkingView::ViewDir::down2:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up2.png", true, 12.0, 3.0);
		iconviewdir->setTransform(createRef<RotateTransform2D>(180.0f, 70.0f, 70.0f));
		break;
	case ManualParkingView::ViewDir::down3:
		iconviewdir = Node2D::createWithTextureFrameName("manual_day", "icon_carview/icon_3dview_up3.png", true, 12.0, 3.0);
		iconviewdir->setTransform(createRef<RotateTransform2D>(180.0f, 70.0f, 70.0f));
		break;
	default:
		break;
	}
}
void ManualParkingView::WarningText(int data)
{
	switch (data)
	{
	case 0:
		break;
	case 1:
	{
		warningtext = createRef<Node2D>(1039.0 - 610.0, 120.0 - 100.0, 444.0f, 86.0f);
		auto warningbg = createRef<Node2D>();
		warningbg->setBackground(SolidColorBrush::floralWhite());
		auto warningicon = Node2D::createWithTextureFrameName("manual_day", "icon_alert.png", true, 74.0, 21.0);
		auto warntext = createRef<TextBlock>(u8"紧急制动已触发");
		warntext->setPosition(Point(141.0, 27.0));

		warningtext->addChild(warningbg);
		warningtext->addChild(warningicon);
		warningtext->addChild(warntext);
		rightView_Node2D->addChild(warningtext);
	}
		break;
	case 2:
	{
		warningtext = createRef<Node2D>(950.0 - 610.0, 120.0 - 100.0, 630.0f, 86.0f);
		auto warningbg = createRef<Node2D>();
		warningbg->setBackground(SolidColorBrush::floralWhite());
		auto warntext = createRef<TextBlock>(u8"驻车辅助系统出现故障，请检查！");
		warntext->setPosition(Point(81.0, 27.0));

		warningtext->addChild(warningbg);
		warningtext->addChild(warntext);
		rightView_Node2D->addChild(warningtext);
	}
		break;
	case 3:
	{
		warningtext = createRef<Node2D>(1022.0 - 610.0, 120.0 - 100.0, 486.0f, 86.0f);
		auto warningbg = createRef<Node2D>();
		warningbg->setBackground(SolidColorBrush::floralWhite());
		auto warntext = createRef<TextBlock>(u8"系统功能不可用");
		warntext->setPosition(Point(81.0, 27.0));

		warningtext->addChild(warningbg);
		warningtext->addChild(warntext);
		rightView_Node2D->addChild(warningtext);
	}
		break;
	case 4:
	{
		warningtext = createRef<Node2D>(937.0 - 610.0, 120.0 - 100.0, 630.0f, 86.0f);
		auto warningbg = createRef<Node2D>();
		warningbg->setBackground(SolidColorBrush::floralWhite());
		auto warntext = createRef<TextBlock>(u8"倒车循迹已开启，请松开刹车");
		warntext->setPosition(Point(81.0, 27.0));

		warningtext->addChild(warningbg);
		warningtext->addChild(warntext);
		rightView_Node2D->addChild(warningtext);
	}
		break;
	case 5:
	{
		warningtext = createRef<Node2D>(973.0 - 610.0, 120.0 - 100.0, 582.0f, 86.0f);
		auto warningbg = createRef<Node2D>();
		warningbg->setBackground(SolidColorBrush::floralWhite());
		auto warntext = createRef<TextBlock>(u8"检测到障碍物，自动泊车暂停");
		warntext->setPosition(Point(81.0, 27.0));

		warningtext->addChild(warningbg);
		warningtext->addChild(warntext);
		rightView_Node2D->addChild(warningtext);
	}
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
}
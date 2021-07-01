#include "MainView.h"

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(720.0f);
	Application::get()->mainWindow()->setTitle("CX620 Power By NewBrush");

	auto k = nb::getMilliseconds();

	TextureLibrary::addTextureAtlas("indicator", RES_DIR"cx62b/indicator.png", RES_DIR"cx62b/indicator.txt");
	TextureLibrary::addTextureAtlas("guage", RES_DIR"cx62b/guage.png", RES_DIR"cx62b/guage.txt");
	TextureLibrary::addTextureAtlas("menu", RES_DIR"cx62b/menu.png", RES_DIR"cx62b/menu.txt");
	BrushLibrary::addImageBrush("bgBrush", RES_DIR"cx62b/bg.png");

	Log::info("load resources cost {} ms.", nb::getMilliseconds() - k);

	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_root->setAlignmentCenter();
	m_root->setBackground(BrushLibrary::get("bgBrush"));

	////////////////
	m_LED_EleSteerLock	= Node2D::createWithTextureFrameName("indicator", "LED_EngineTheft-Red.png", false, 135, 23);
	m_LED_OilPressure	= Node2D::createWithTextureFrameName("indicator", "LED_OilPressure-Red.png", true, 86, 63);
	m_LED_BrakeFluidLv	= Node2D::createWithTextureFrameName("indicator", "LED_BrakeFluidLevel-Red.png", true, 45, 106);
	m_LED_StartStop		= Node2D::createWithTextureFrameName("indicator", "LED_StartStop-Yellow.png", true, 9, 165);
	m_LED_DayTime		= Node2D::createWithTextureFrameName("indicator", "LED_Daytime-Green.png", true, 19, 536);
	m_LED_FrontFog		= Node2D::createWithTextureFrameName("indicator", "LED_FrontFog-Green.png", true, 61, 643);
	m_LED_RearFog		= Node2D::createWithTextureFrameName("indicator", "LED_RearFog-Yellow.png", true, 9, 603);
	m_LED_HMA			= Node2D::createWithTextureFrameName("indicator", "LED_HMA-White.png", false, 62, 590);
	m_LED_HighBeam		= Node2D::createWithTextureFrameName("indicator", "LED_HighBeam.png", true, 114, 638);
	m_LED_Position		= Node2D::createWithTextureFrameName("indicator", "LED_StartStop-Yellow.png", true, 175, 670);

	////////////////
	m_LED_LeftTurn		= Node2D::createWithTextureFrameName("indicator", "LED_LeftTurn.png", false, 530.0f, 12.0f);
	m_LED_SpeedLimit	= Node2D::createWithTextureFrameName("indicator", "LED_SpeedLimit-Fault.png", true, 135.0f, 335.0f);
	m_LED_ACC			= Node2D::createWithTextureFrameName("indicator", "LED_ACCTargetObject-Green.png", true, 297.0f, 225.0f);
	m_LED_LDW			= Node2D::createWithTextureFrameName("indicator", "LED_LDWRight-Grey.png", true, 517.0f, 228.0f);
	m_LED_BSD			= Node2D::createWithTextureFrameName("indicator", "LED_BSD-Green.png", true, 538.0f, 318.0f);
	m_LED_FCW			= Node2D::createWithTextureFrameName("indicator", "LED_FCW-Red.png", true, 529.0f, 407.0f);
	m_LED_SeatBelt1		= Node2D::createWithTextureFrameName("indicator", "LED_SeatBelt-Red.png", true, 277.0f, 448.0f);
	m_LED_SeatBelt2		= Node2D::createWithTextureFrameName("indicator", "LED_PassSeatBelt-Red.png", true, 397.0f, 448.0f);
	m_LED_SeatBelt3		= Node2D::createWithTextureFrameName("indicator", "LED_RLSeatBelt-Red.png", true, 277.0f, 519.0f);
	m_LED_SeatBelt4		= Node2D::createWithTextureFrameName("indicator", "LED_RMSeatBelt-Red.png", true, 337.0f, 532.0f);
	m_LED_SeatBelt5		= Node2D::createWithTextureFrameName("indicator", "LED_RRSeatBelt-Red.png", true, 397.0f, 519.0f);
	m_LED_EPC			= Node2D::createWithTextureFrameName("indicator", "LED_EPC-Yellow.png", true, 539.0f, 660.0f);
	m_LED_MILEmission	= Node2D::createWithTextureFrameName("indicator", "LED_MILEmission-Yellow.png", true, 611.0f, 659.0f);
	m_LED_EPB			= Node2D::createWithTextureFrameName("indicator", "LED_EPB-Red.png", true, 683.0f, 656.0f);
	m_LED_DrivingMode	= Node2D::createWithTextureFrameName("indicator", "LED_DrivingModeSport.png", false, 738.0f, 664.0f);
	m_LED_Charging		= Node2D::createWithTextureFrameName("indicator", "LED_Charging-Red.png", true, 1039.0f, 660.0f);
	m_LED_RightTurn		= Node2D::createWithTextureFrameName("indicator", "LED_RightTurn.png", true, 1323.0f, 12.0f);
	m_LED_AVH			= Node2D::createWithTextureFrameName("indicator", "LED_AVH-Yellow.png", true, 1364.0f, 214.0f);
	m_LED_CoolantTemp	= Node2D::createWithTextureFrameName("indicator", "LED_CoolantTemp-Blue.png", false, 1533.0f, 605.0f);
	m_LED_GearBox		= Node2D::createWithTextureFrameName("indicator", "LED_GearBoxFault-Red.png", true, 1774.0f, 55.0f);
	m_LED_ElecStability = Node2D::createWithTextureFrameName("indicator", "LED_ElecStabilityOFF-Yellow.png", true, 1823.0f, 99.0f);
	m_LED_ABS			= Node2D::createWithTextureFrameName("indicator", "LED_ABS-Yellow.png", true, 1858.0f, 157.0f);
	m_LED_HDC			= Node2D::createWithTextureFrameName("indicator", "LED_HDC-Green.png", true, 1710.0f, 228.0f);
	m_LED_Warning		= Node2D::createWithTextureFrameName("indicator", "LED_Warning.png", true, 1741.0f, 318.0f);
	m_LED_GPF			= Node2D::createWithTextureFrameName("indicator", "LED_GPF-Green.png", true, 1728.0f, 407.0f);
	m_LED_EPS			= Node2D::createWithTextureFrameName("indicator", "LED_EPS-Red.png", true, 1851.0f, 527.0f);
	m_LED_MaintenanceTip= Node2D::createWithTextureFrameName("indicator", "LED_MaintenanceTip.png", true, 1807.0f, 581.0f);
	m_LED_AirBag		= Node2D::createWithTextureFrameName("indicator", "LED_AirBag-Red.png", true, 1753.0f, 632.0f);
	m_LED_TPMS			= Node2D::createWithTextureFrameName("indicator", "LED_TPMS-Yellow.png", true, 1692.0f, 663.0f);

	m_DialLeftRoot = Node2D::createWithTextureFrameName("guage", "Speed_BG.png", true, 29.0f, 29.0f);
	auto nodeValue = createRef<Node2D>(0.0f, 26.0f, 300.0f, 250.0f);
	nodeValue->setAlignmentCenter();
	m_SpeedValue = Node2D::createWithTextureFrameName("guage", "number/9.png", true, 0.0f, 53.0f);
	m_SpeedValue->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_SpeedPointer = Node2D::createWithTextureFrameName("guage", "pointer.png", true, 0.0f, 264.0f);
	m_SpeedPointer->setTransform(createRef<RotateTransform2D>(0.0f, 333.0f, 67.0f));
	auto kmNode = Node2D::createWithTextureFrameName("guage", "kmh.png", true, 0.0f, 170.0f);
	kmNode->setHorizontalAlignment(HorizontalAlignmentE::Center);
	nodeValue->addChild(m_SpeedValue);
	nodeValue->addChild(kmNode);
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/0_n.png", true, 57.0f, 483.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/20_n.png", true, 14.0f, 398.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/40_n.png", true, -2.0f, 280.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/60_n.png", true, 38.0f, 161.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/80_n.png", true, 118.0f, 71.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/100_n.png", true, 218.0f, 31.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/120_n.png", true, 336.0f, 31.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/140_n.png", true, 443.0f, 78.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/160_n.png", true, 522.0f, 164.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/180_n.png", true, 557.0f, 284.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/200_n.png", true, 553.0f, 389.0f));
	m_DialLeftRoot->addChild(Node2D::createWithTextureFrameName("guage", "speed number/220_n.png", true, 510.0f, 478.0f));
	m_DialLeftRoot->addChild(nodeValue);
	m_DialLeftRoot->addChild(m_SpeedPointer);

	m_DialRightRoot = Node2D::createWithTextureFrameName("guage", "RPMBig_BG.png", true, 1225.0f, 29.0f);
	auto bg_inner = Node2D::createWithTextureFrameName("guage", "Internal dial.png", true);
	bg_inner->setAlignmentCenter();
	auto bg_waterTemp = Node2D::createWithTextureFrameName("guage", "WaterTemp.png", true);
	bg_waterTemp->setAlignmentCenter();
	m_RpmValue = createRef<Node2D>(0.0f, 0.0f, 435.4f, 435.4f);
	m_RpmValue->setAlignmentCenter();
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "img_ECU_car.png", true, -20.0f, 193.0f));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ECU_horizon.png", true, 91.0f, 252.0f));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ECU_scale.png", true, 115.0f, 328.0f));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "L100km.png", true, 222.0f, 205.0f));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ic_ECU_gas station.png", true, 280.0f, 211.5f));
	m_ECU_Pointer = Node2D::createWithTextureFrameName("guage", "ECU_Pointer.png", true, 284.0f, 256.0f);
	m_RpmValue->addChild(m_ECU_Pointer);
	m_RpmPointer = Node2D::createWithTextureFrameName("guage", "pointer.png", true, 0.0f, 264.0f);
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "RPM_BG.png", true, 0.0f, 0.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "ECU_fuel consumption_n.png", true, 197.0f, 332.0f));
	m_DialRightRoot->addChild(bg_inner);
	m_DialRightRoot->addChild(m_RpmValue);
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "x1000rpm.png", true, 284.0f, 142.0f));
	//m_DialRightRoot->addChild(bg_waterTemp);
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_0_n.png", true, 84.0f, 482.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_1_n.png", true, 29.0f, 344.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_2_n.png", true, 51.0f, 191.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_3_n.png", true, 155.0f, 70.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_4_n.png", true, 310.0f, 25.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_5_n.png", true, 463.0f, 69.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_6_n.png", true, 570.0f, 191.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_7_n.png", true, 586.0f, 355.0f));
	m_DialRightRoot->addChild(Node2D::createWithTextureFrameName("guage", "rpm number/rpm_8_n.png", true, 533.0f, 486.0f));
	m_DialRightRoot->addChild(m_RpmPointer);

	m_TopMenu = Node2D::createWithTextureFrameName("menu", "pop_bg.png", true);
	m_TopMenu->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_TopMenu->addChild(Node2D::createWithTextureFrameName("menu", "ic_Answer.png", true, 206.6f, 43.9f));

	m_Menu = Node2D::createWithTextureFrameName("menu", "DrivingInfo/img_Tire pressure_car.png", true, 0.0f, 29.0f);
	m_Menu->setAlignmentCenter();

	m_root->addChild(m_DialLeftRoot);
	m_root->addChild(m_DialRightRoot);
	m_root->addChild(m_TopMenu);
	m_root->addChild(m_LED_EleSteerLock);
	m_root->addChild(m_LED_OilPressure);
	m_root->addChild(m_LED_BrakeFluidLv);
	m_root->addChild(m_LED_StartStop);
	m_root->addChild(m_LED_DayTime);
	m_root->addChild(m_LED_FrontFog);
	m_root->addChild(m_LED_RearFog);
	m_root->addChild(m_LED_HMA);
	m_root->addChild(m_LED_HighBeam);
	m_root->addChild(m_LED_Position);
	m_root->addChild(m_LED_LeftTurn);
	m_root->addChild(m_LED_SpeedLimit);
	m_root->addChild(m_LED_ACC);
	m_root->addChild(m_LED_LDW);
	m_root->addChild(m_LED_BSD);
	m_root->addChild(m_LED_FCW);
	m_root->addChild(m_LED_SeatBelt1);
	m_root->addChild(m_LED_SeatBelt2);
	m_root->addChild(m_LED_SeatBelt3);
	m_root->addChild(m_LED_SeatBelt4);
	m_root->addChild(m_LED_SeatBelt5);
	m_root->addChild(m_LED_EPC);
	m_root->addChild(m_LED_MILEmission);
	m_root->addChild(m_LED_EPB);
	m_root->addChild(m_LED_DrivingMode);
	m_root->addChild(m_LED_Charging);
	m_root->addChild(m_LED_RightTurn);
	m_root->addChild(m_LED_AVH);
	m_root->addChild(m_LED_CoolantTemp);
	m_root->addChild(m_LED_GearBox);
	m_root->addChild(m_LED_ElecStability);
	m_root->addChild(m_LED_ABS);
	m_root->addChild(m_LED_HDC);
	m_root->addChild(m_LED_Warning);
	m_root->addChild(m_LED_GPF);
	m_root->addChild(m_LED_EPS);
	m_root->addChild(m_LED_MaintenanceTip);
	m_root->addChild(m_LED_AirBag);
	m_root->addChild(m_LED_TPMS);
	m_root->addChild(m_Menu);

	initStateMachines();

	m_timerLeftTurn.Tick += nbBindEventFunction(MainView::onTick);
	m_timerRightTurn.Tick += nbBindEventFunction(MainView::onTick);
	m_timerHMA.Tick += nbBindEventFunction(MainView::onTick);
	m_timerLeftTurn.start(500);
	m_timerRightTurn.start(500);
	m_timerHMA.start(10);

	m_carAnimation = createRef<FloatAnimation>(120.0f, 284.0f);
	m_carAnimation->setTarget(m_ECU_Pointer);
	m_carAnimation->setTargetPropertyName("X");
	m_carAnimation->duration = TimeSpan::fromSeconds(2);
	m_carAnimation->setEasingFunction(createRef<ElasticEase>());
	m_carAnimation->autoReverse = true;
	m_carAnimation->repeatBehavior = RepeatBehavior::forever();
	m_carAnimation->begin();

	setSpeed(123);

	m_LED_EleSteerLock->setOpacity(0.3f);
	m_LED_OilPressure->setOpacity(0.9f);
}

void MainView::initStateMachines()
{
	m_smEleSteerLock = createRef<StateManager>(2);
	(*m_smEleSteerLock)[0]->assignProperty(m_LED_EleSteerLock, prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	(*m_smEleSteerLock)[1]->assignProperty(m_LED_EleSteerLock, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_EngineTheft-Red.png"));
	m_smEleSteerLock->gotoState(1);
	
	m_smHMA = createRef<StateManager>(4);
	(*m_smHMA)[0]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	(*m_smHMA)[1]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_HMA-Yellow.png"));
	(*m_smHMA)[2]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_HMA-Green.png"));
	(*m_smHMA)[3]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_HMA-White.png"));
	m_smHMA->gotoState(1);

	m_smLeftTurn = createRef<StateManager>(2);
	(*m_smLeftTurn)[0]->assignProperty(m_LED_LeftTurn, prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	(*m_smLeftTurn)[1]->assignProperty(m_LED_LeftTurn, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_LeftTurn.png"));
	m_smLeftTurn->gotoState(0);

	m_smRightTurn = createRef<StateManager>(2);
	(*m_smRightTurn)[0]->assignProperty(m_LED_RightTurn, prop<Node2D>("Background"), createRef<ImageBrush>("", ""));
	(*m_smRightTurn)[1]->assignProperty(m_LED_RightTurn, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_RightTurn.png"));
	m_smRightTurn->gotoState(0);

	m_smDrivingMode = createRef<StateManager>(4);
	(*m_smDrivingMode)[0]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_DrivingModeECO.png"));
	(*m_smDrivingMode)[1]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_DrivingModeNormal.png"));
	(*m_smDrivingMode)[2]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_DrivingModeSport.png"));
	(*m_smDrivingMode)[3]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_DrivingModeSnow.png"));
	m_smDrivingMode->gotoState(0);

	m_smCoolantTemp = createRef<StateManager>(3);
	(*m_smCoolantTemp)[0]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_CoolantTempNormal.png"));
	(*m_smCoolantTemp)[1]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_CoolantTemp-Blue.png"));
	(*m_smCoolantTemp)[2]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), createRef<ImageBrush>("indicator", "LED_CoolantTemp-Red.png"));
	m_smCoolantTemp->gotoState(0);
}
float angle = 0.0f;
void MainView::onTick(const EventArgs & e)
{
	if (e.sender == &m_timerLeftTurn)
	{
		m_smLeftTurn->gotoNextState();
	}
	else if (e.sender == &m_timerRightTurn)
	{
		m_smRightTurn->gotoNextState();
	}
	else if (e.sender == &m_timerHMA)
	{
		m_smHMA->gotoNextState();
		m_smDrivingMode->gotoNextState();
		m_smCoolantTemp->gotoNextState();
		angle += 0.1f;
		nb::as<RotateTransform2D>(m_SpeedPointer->getTransform())->setAngle(angle);
	}
}

void MainView::setSpeed(int speed)
{
	std::vector<ref<Node2D>> speedNodes;
	auto temp = speed;
	do
	{
		auto n = temp % 10;
		auto node = Node2D::createWithTextureFrameName("guage", "number/" + std::to_string(n) + ".png", 0, 0);
		speedNodes.push_back(node);
		temp /= 10;
	} while (temp);
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();


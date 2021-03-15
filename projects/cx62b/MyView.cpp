#include "MyView.h"

void MyView::init()
{
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(720.0f);
	Application::get()->mainWindow()->setTitle("CX620 Power By NewBrush");

	TextureLibrary::addTextureAtlas("indicator", RES_DIR"cx62b/indicator.png", RES_DIR"cx62b/indicator.txt");
	TextureLibrary::addTextureAtlas("guage", RES_DIR"cx62b/guage.png", RES_DIR"cx62b/guage.txt");
	TextureLibrary::addTextureAtlas("menu", RES_DIR"cx62b/menu.png", RES_DIR"cx62b/menu.txt");
	BrushLibrary::addImageBrush("bgBrush", RES_DIR"cx62b/bg.png");

	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_root->setAlignmentCenter();
	m_root->setBackground(BrushLibrary::get("bgBrush"));

	m_LED_EleSteerLock = Node2D::createWithTextureFrameName("indicator", "LED_EngineTheft-Red.png", false, 135, 23);
	m_LED_OilPressure = Node2D::createWithTextureFrameName("indicator", "LED_OilPressure-Red.png", true, 86, 63);
	m_LED_BrakeFluidLevel = Node2D::createWithTextureFrameName("indicator", "LED_BrakeFluidLevel-Red.png", true, 45, 106);
	m_LED_StartStop = Node2D::createWithTextureFrameName("indicator", "LED_StartStop-Yellow.png", true, 9, 165);
	m_LED_DayTime = Node2D::createWithTextureFrameName("indicator", "LED_Daytime-Green.png", true, 19, 536);
	m_LED_FrontFog = Node2D::createWithTextureFrameName("indicator", "LED_FrontFog-Green.png", true, 61, 643);
	m_LED_RearFog = Node2D::createWithTextureFrameName("indicator", "LED_RearFog-Yellow.png", true, 9, 603);
	m_LED_HMA = Node2D::createWithTextureFrameName("indicator", "LED_HMA-White.png", false, 62, 590);
	m_LED_HighBeam = Node2D::createWithTextureFrameName("indicator", "LED_HighBeam.png", true, 114, 638);
	m_LED_Position = Node2D::createWithTextureFrameName("indicator", "LED_StartStop-Yellow.png", true, 175, 670);

	////////////////
	m_LED_LeftTurn = Node2D::createWithTextureFrameName("indicator", "LED_LeftTurn.png", false, 530, 12);
	m_LED_SpeedLimit = Node2D::createWithTextureFrameName("indicator", "LED_SpeedLimit-Fault.png", true, 135, 335);
	m_LED_ACC = Node2D::createWithTextureFrameName("indicator", "LED_ACCTargetObject-Green.png", true, 297, 225);
	m_LED_LDW = Node2D::createWithTextureFrameName("indicator", "LED_LDWRight-Grey.png", true, 517, 228);
	m_LED_BSD = Node2D::createWithTextureFrameName("indicator", "LED_BSD-Green.png", true, 538, 318);
	m_LED_FCW = Node2D::createWithTextureFrameName("indicator", "LED_FCW-Red.png", true, 529, 407);
	m_LED_SeatBelt1 = Node2D::createWithTextureFrameName("indicator", "LED_SeatBelt-Red.png", true, 277, 448);
	m_LED_SeatBelt2 = Node2D::createWithTextureFrameName("indicator", "LED_PassSeatBelt-Red.png", true, 397, 448);
	m_LED_SeatBelt3 = Node2D::createWithTextureFrameName("indicator", "LED_RLSeatBelt-Red.png", true, 277, 519);
	m_LED_SeatBelt4 = Node2D::createWithTextureFrameName("indicator", "LED_RMSeatBelt-Red.png", true, 337, 532);
	m_LED_SeatBelt5 = Node2D::createWithTextureFrameName("indicator", "LED_RRSeatBelt-Red.png", true, 397, 519);
	m_LED_EPC = Node2D::createWithTextureFrameName("indicator", "LED_EPC-Yellow.png", true, 539, 660);
	m_LED_MILEmission = Node2D::createWithTextureFrameName("indicator", "LED_MILEmission-Yellow.png", true, 611, 659);
	m_LED_EPB = Node2D::createWithTextureFrameName("indicator", "LED_EPB-Red.png", true, 683, 656);
	m_LED_DrivingMode = Node2D::createWithTextureFrameName("indicator", "LED_DrivingModeSport.png", false, 738, 664);
	m_LED_Charging = Node2D::createWithTextureFrameName("indicator", "LED_Charging-Red.png", true, 1039, 660);
	m_LED_RightTurn = Node2D::createWithTextureFrameName("indicator", "LED_RightTurn.png", true, 1323, 12);
	m_LED_AVH = Node2D::createWithTextureFrameName("indicator", "LED_AVH-Yellow.png", false, 1364, 214);
	m_LED_CoolantTemp = Node2D::createWithTextureFrameName("indicator", "LED_CoolantTemp-Blue.png", false, 1533, 605);
	m_LED_GearBox = Node2D::createWithTextureFrameName("indicator", "LED_GearBoxFault-Red.png", true, 1774, 55);
	m_LED_ElecStability = Node2D::createWithTextureFrameName("indicator", "LED_ElecStabilityOFF-Yellow.png", true, 1823, 99);
	m_LED_ABS = Node2D::createWithTextureFrameName("indicator", "LED_ABS-Yellow.png", true, 1858, 157);
	m_LED_HDC = Node2D::createWithTextureFrameName("indicator", "LED_HDC-Green.png", true, 1710, 228);
	m_LED_Warning = Node2D::createWithTextureFrameName("indicator", "LED_Warning.png", true, 1741, 318);
	m_LED_GPF = Node2D::createWithTextureFrameName("indicator", "LED_GPF-Green.png", true, 1728, 407);
	m_LED_EPS = Node2D::createWithTextureFrameName("indicator", "LED_EPS-Red.png", true, 1851, 527);
	m_LED_MaintenanceTip = Node2D::createWithTextureFrameName("indicator", "LED_MaintenanceTip.png", true, 1807, 581);
	m_LED_AirBag = Node2D::createWithTextureFrameName("indicator", "LED_AirBag-Red.png", true, 1753, 632);
	m_LED_TPMS = Node2D::createWithTextureFrameName("indicator", "LED_TPMS-Yellow.png", true, 1692, 663);

	m_DialLeftRoot = Node2D::createWithTextureFrameName("guage", "Speed_BG.png", true, 29, 29);
	auto scale00 = Node2D::createWithTextureFrameName("guage", "speed number/0_n.png", true, 57, 483);
	auto scale20 = Node2D::createWithTextureFrameName("guage", "speed number/20_n.png", true, 14, 398);
	auto scale40 = Node2D::createWithTextureFrameName("guage", "speed number/40_n.png", true, -2, 280);
	auto scale60 = Node2D::createWithTextureFrameName("guage", "speed number/60_n.png", true, 38, 161);
	auto scale80 = Node2D::createWithTextureFrameName("guage", "speed number/80_n.png", true, 118, 71);
	auto scale100 = Node2D::createWithTextureFrameName("guage", "speed number/100_n.png", true, 218, 31);
	auto scale120 = Node2D::createWithTextureFrameName("guage", "speed number/120_n.png", true, 336, 31);
	auto scale140 = Node2D::createWithTextureFrameName("guage", "speed number/140_n.png", true, 443, 78);
	auto scale160 = Node2D::createWithTextureFrameName("guage", "speed number/160_n.png", true, 522, 164);
	auto scale180 = Node2D::createWithTextureFrameName("guage", "speed number/180_n.png", true, 557, 284);
	auto scale200 = Node2D::createWithTextureFrameName("guage", "speed number/200_n.png", true, 553, 389);
	auto scale220 = Node2D::createWithTextureFrameName("guage", "speed number/220_n.png", true, 510, 478);
	auto nodeValue = createRef<Node2D>(0.0f, 26.0f, 300.0f, 250.0f);
	//nodeValue->setBackground(createRef<SolidColorBrush>(Colors::red));
	nodeValue->setHorizontalAlignment(HorizontalAlignmentE::Center);
	nodeValue->setVerticalAlignment(VerticalAlignmentE::Center);
	m_SpeedValue = Node2D::createWithTextureFrameName("guage", "number/9.png", true, 0.0f, 53.0f);
	m_SpeedValue->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_SpeedPointer = Node2D::createWithTextureFrameName("guage", "pointer.png", true, 0.0f, 264.0f);
	m_SpeedPointer->setTransform(createRef<RotateTransform2D>());
	nb::as<RotateTransform2D>(m_SpeedPointer->getTransform())->setCenterX(333);
	nb::as<RotateTransform2D>(m_SpeedPointer->getTransform())->setCenterY(67);
	auto kmNode = Node2D::createWithTextureFrameName("guage", "kmh.png", true, 0.0f, 170.0f);
	kmNode->setHorizontalAlignment(HorizontalAlignmentE::Center);
	nodeValue->addChild(m_SpeedValue);
	nodeValue->addChild(kmNode);
	m_DialLeftRoot->addChild(scale00);
	m_DialLeftRoot->addChild(scale20);
	m_DialLeftRoot->addChild(scale40);
	m_DialLeftRoot->addChild(scale60);
	m_DialLeftRoot->addChild(scale80);
	m_DialLeftRoot->addChild(scale100);
	m_DialLeftRoot->addChild(scale120);
	m_DialLeftRoot->addChild(scale140);
	m_DialLeftRoot->addChild(scale160);
	m_DialLeftRoot->addChild(scale180);
	m_DialLeftRoot->addChild(scale200);
	m_DialLeftRoot->addChild(scale220);
	m_DialLeftRoot->addChild(nodeValue);
	m_DialLeftRoot->addChild(m_SpeedPointer);

	m_DialRightRoot = Node2D::createWithTextureFrameName("guage", "RPMBig_BG.png", true, 1225, 29);
	auto bg = Node2D::createWithTextureFrameName("guage", "RPM_BG.png", true, 0, 0);
	auto x1000rpm = Node2D::createWithTextureFrameName("guage", "x1000rpm.png", true, 284, 142);
	auto ecu_fuel = Node2D::createWithTextureFrameName("guage", "ECU_fuel consumption_n.png", true, 197, 332);
	auto bg_inner = Node2D::createWithTextureFrameName("guage", "Internal dial.png", true);
	bg_inner->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bg_inner->setVerticalAlignment(VerticalAlignmentE::Center);
	auto bg_waterTemp = Node2D::createWithTextureFrameName("guage", "WaterTemp.png", true);
	bg_waterTemp->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bg_waterTemp->setVerticalAlignment(VerticalAlignmentE::Bottom);
	auto rpm0 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_0_n.png", true, 84, 482);
	auto rpm1 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_1_n.png", true, 29, 344);
	auto rpm2 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_2_n.png", true, 51, 191);
	auto rpm3 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_3_n.png", true, 155, 70);
	auto rpm4 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_4_n.png", true, 310, 25);
	auto rpm5 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_5_n.png", true, 463, 69);
	auto rpm6 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_6_n.png", true, 570, 191);
	auto rpm7 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_7_n.png", true, 586, 355);
	auto rpm8 = Node2D::createWithTextureFrameName("guage", "rpm number/rpm_8_n.png", true, 533, 486);
	m_RpmValue = createRef<Node2D>(0,0,435.4, 435.4);
	m_RpmValue->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_RpmValue->setVerticalAlignment(VerticalAlignmentE::Center);
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "img_ECU_car.png", true, -20, 193));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ECU_horizon.png", true, 91, 252));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ic_ECU_gas station.png", true, 280, 211.5));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "ECU_scale.png", true, 115, 328));
	m_RpmValue->addChild(Node2D::createWithTextureFrameName("guage", "L100km.png", true, 222, 205));
	m_ECU_Pointer = Node2D::createWithTextureFrameName("guage", "ECU_Pointer.png", true, 284, 256);
	m_RpmValue->addChild(m_ECU_Pointer);
	m_RpmPointer = Node2D::createWithTextureFrameName("guage", "pointer.png", true, 0, 264);
	m_DialRightRoot->addChild(bg);
	m_DialRightRoot->addChild(x1000rpm);
	m_DialRightRoot->addChild(ecu_fuel);
	m_DialRightRoot->addChild(bg_inner);
	//m_DialRightRoot->addChild(bg_waterTemp);
	m_DialRightRoot->addChild(rpm0);
	m_DialRightRoot->addChild(rpm1);
	m_DialRightRoot->addChild(rpm2);
	m_DialRightRoot->addChild(rpm3);
	m_DialRightRoot->addChild(rpm4);
	m_DialRightRoot->addChild(rpm5);
	m_DialRightRoot->addChild(rpm6);
	m_DialRightRoot->addChild(rpm7);
	m_DialRightRoot->addChild(rpm8);
	m_DialRightRoot->addChild(m_RpmValue);
	m_DialRightRoot->addChild(m_RpmPointer);

	m_TopMenu = Node2D::createWithTextureFrameName("menu", "pop_bg.png", true);
	m_TopMenu->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_TopMenu->setVerticalAlignment(VerticalAlignmentE::Top);
	m_TopMenu->addChild(Node2D::createWithTextureFrameName("menu", "ic_Answer.png", true, 0.0f, 43.9f));

	m_Menu = Node2D::createWithTextureFrameName("menu", "DrivingInfo/img_Tire pressure_car.png", true, 0.0f, 29.0f);
	m_Menu->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_Menu->setVerticalAlignment(VerticalAlignmentE::Center);

	m_root->addChild(m_LED_EleSteerLock);
	m_root->addChild(m_LED_OilPressure);
	m_root->addChild(m_LED_BrakeFluidLevel);
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

	m_root->addChild(m_DialLeftRoot);
	m_root->addChild(m_DialRightRoot);
	m_root->addChild(m_TopMenu);
	m_root->addChild(m_Menu);

	initStateMachines();

	m_timerLeftTurn.start(500);
	m_timerRightTurn.start(500);
	m_timerHMA.start(10);
	m_timerLeftTurn.Tick += std::bind(&MyView::onTick, this, std::placeholders::_1);
	m_timerRightTurn.Tick += std::bind(&MyView::onTick, this, std::placeholders::_1);
	m_timerHMA.Tick += std::bind(&MyView::onTick, this, std::placeholders::_1);

	setSpeed(123);

	m_carAnimation.setTarget(m_ECU_Pointer);
	m_carAnimation.setTargetPropertyName("X");
	m_carAnimation.duration = TimeSpan::fromSeconds(2);
	m_carAnimation.setEasingFunction(createRef<ElasticEase>());
	m_carAnimation.autoReverse = true;
	m_carAnimation.repeatBehavior = RepeatBehavior::forever();
	m_carAnimation.setFrom(120.0f);
	m_carAnimation.setTo(284.0f);
	m_carAnimation.begin();

	//m_LED_EleSteerLock->setBackground(createRef<SolidColorBrush>(Colors::red));
	//m_LED_EleSteerLock->setPosition({ 0, 0 });
	//m_LED_EleSteerLock->setRotate({ 0.0f, 0.0f, glm::radians(90.0f) });
	//m_LED_EleSteerLock->setTranslate({ 200.0f, 0.0f, 0.0f });
	//m_LED_EleSteerLock->setScale({ 0.5f, 0.5f, 0.5f });

	//m_SpeedPointer->setRotate({ 0.0f, 0.0f, glm::radians(60.0f) });
	m_LED_EleSteerLock->setOpacity(0.3f);
	m_LED_OilPressure->setOpacity(0.9f);
}

ref<Node> MyView::getRoot()
{
	return m_root;
}

void MyView::initStateMachines()
{
	m_smEleSteerLock = createRef<StateManager>(2);
	(*m_smEleSteerLock)[0]->assignProperty(m_LED_EleSteerLock, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("", ""));
	(*m_smEleSteerLock)[1]->assignProperty(m_LED_EleSteerLock, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_EngineTheft-Red.png"));
	m_smEleSteerLock->gotoState(1);
	
	m_smHMA = createRef<StateManager>(4);
	(*m_smHMA)[0]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("", ""));
	(*m_smHMA)[1]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_HMA-Yellow.png"));
	(*m_smHMA)[2]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_HMA-Green.png"));
	(*m_smHMA)[3]->assignProperty(m_LED_HMA, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_HMA-White.png"));
	m_smHMA->gotoState(1);

	m_smLeftTurn = createRef<StateManager>(2);
	(*m_smLeftTurn)[0]->assignProperty(m_LED_LeftTurn, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("", ""));
	(*m_smLeftTurn)[1]->assignProperty(m_LED_LeftTurn, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_LeftTurn.png"));
	m_smLeftTurn->gotoState(0);

	m_smRightTurn = createRef<StateManager>(2);
	(*m_smRightTurn)[0]->assignProperty(m_LED_RightTurn, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("", ""));
	(*m_smRightTurn)[1]->assignProperty(m_LED_RightTurn, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_RightTurn.png"));
	m_smRightTurn->gotoState(0);

	m_smDrivingMode = createRef<StateManager>(4);
	(*m_smDrivingMode)[0]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_DrivingModeECO.png"));
	(*m_smDrivingMode)[1]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_DrivingModeNormal.png"));
	(*m_smDrivingMode)[2]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_DrivingModeSport.png"));
	(*m_smDrivingMode)[3]->assignProperty(m_LED_DrivingMode, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_DrivingModeSnow.png"));
	m_smDrivingMode->gotoState(0);

	m_smCoolantTemp = createRef<StateManager>(3);
	(*m_smCoolantTemp)[0]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_CoolantTempNormal.png"));
	(*m_smCoolantTemp)[1]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_CoolantTemp-Blue.png"));
	(*m_smCoolantTemp)[2]->assignProperty(m_LED_CoolantTemp, prop<Node2D>("Background"), ImageBrush::createWitchTextureFrameName("indicator", "LED_CoolantTemp-Red.png"));
	m_smCoolantTemp->gotoState(0);
}
float angle = 0.0f;
void MyView::onTick(const EventArgs & e)
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

void MyView::setSpeed(int speed)
{
	std::vector<ref<Node2D>> speedNodes;
	auto temp = speed;
	while (temp % 10)
	{
		auto n = temp % 10;
		auto node = Node2D::createWithTextureFrameName("guage", "number/" + std::to_string(n) + ".png", 0, 0);
		speedNodes.push_back(node);
		temp /= 10;

	}
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MyView>();


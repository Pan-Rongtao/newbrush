#include "AIView.h"
#include "MainView.h"
#include "AVMView.h"
#include "HPAView.h"
#include "Tr.h"

Button3D::Button3D(float x, float y, float width, float height, ref<ImageBrush> normal, ref<ImageBrush> check)
	: m_checked(false)
	, m_normal(normal)
	, m_check(check)
	, m_rc(x, y, width, height)
{
	setCheck(false);
}

void Button3D::setCheck(bool check)
{
	m_mesh = makeMesh(check ? m_check : m_normal);
	m_checked = check;
}

bool Button3D::isCheck() const
{
	return m_checked;
}

void Button3D::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	auto const &mat = getTransform() ? getTransform()->value() : Transform::identityMatrix4();
	m_mesh->draw(mat, camera, lights);
}

ref<Mesh> Button3D::makeMesh(ref<ImageBrush> brush)
{
	std::vector<Vertex> vertexs(4);
	auto texFrame = brush->frame;
	auto const &tex = texFrame.texture;
	auto rotated = texFrame.rotated;
	glm::vec2 texSourceSize = tex ? glm::vec2(tex->width(), tex->height()) : glm::vec2(0.0f);
	glm::vec2 texTargetOffset = { texFrame.frame.x, texFrame.frame.y };
	glm::vec2 texTargetSize = rotated ? glm::vec2(texFrame.frame.w, texFrame.frame.z) : glm::vec2(texFrame.frame.z, texFrame.frame.w);
	glm::vec2 uv0 = { texTargetOffset / texSourceSize };
	glm::vec2 uv1 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, texTargetOffset.y / texSourceSize.y };
	glm::vec2 uv2 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
	glm::vec2 uv3 = { texTargetOffset.x / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
	vertexs[0].uv = rotated ? uv1 : uv0;
	vertexs[1].uv = rotated ? uv2 : uv1;
	vertexs[2].uv = rotated ? uv3 : uv2;
	vertexs[3].uv = rotated ? uv0 : uv3;
	vertexs[0].position = glm::vec3(-(m_rc.width() / 2.0f) + m_rc.x(), -(m_rc.height() / 2.0f) + m_rc.y(), 0.0f);
	vertexs[1].position = glm::vec3((m_rc.width() / 2.0f) + m_rc.x(), -(m_rc.height() / 2.0f) + m_rc.y(), 0.0f);
	vertexs[2].position = glm::vec3((m_rc.width() / 2.0f) + m_rc.x(), (m_rc.height() / 2.0f) + m_rc.y(), 0.0f);
	vertexs[3].position = glm::vec3(-(m_rc.width() / 2.0f) + m_rc.x(), (m_rc.height() / 2.0f) + m_rc.y(), 0.0f);
	auto material = createRef<TextureMaterial>(texFrame);
	auto mesh = createRef<Mesh>(vertexs, std::vector<uint16_t>{ 0, 1, 2, 0, 2, 3 }, material);
	return mesh;
}

///////////////////////
AutoParkScene::AutoParkScene()
	: m_curStep(Step::Searching)
	, m_aniFrom(-3.0f)
	, m_aniTo(-0.1f)
{
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_rightSearchingParent = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_rightSearchingParent->setBackground(IMGBR(AI, "autopark_pic_bgroad.png"));
	m_rightSearchingParent->setScene(createRef<Scene>());
	m_rightTopTipParent = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_rightParkDoneParent = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_topTipBg = createRef<NinePatchImage>(0.0f, 20.0f, 584.0f, 86.0f);
	m_topTipBg->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTopTip = createRef<TextBlock>();
	m_txtTopTip->setAlignmentCenter();
	m_txtTopTip->setFontSize(32);
	m_topTipBg->addChild(m_txtTopTip);
	m_car = Node2D::createWithTextureFrameName(AI, "pic_car03.png", 0.0f, -150.0f);
	m_car->setAlignmentCenter();
	auto carRadar = Node2D::createWithTextureFrameName(AI, "pic_radar.png", 0.0f, 0.0f);
	carRadar->setAlignmentCenter();
	m_car->addChild(carRadar);
	m_btnStartPark = Button::createWithTextureFrameName(AI, "btn_62px_sel.9.png", 0.0f, 750.0f);
	m_btnStartPark->setTextColor(Colors::white, Color(255, 255, 255, 220));
	m_btnStartPark->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStartPark->setFontSize(28);
	m_btnStartPark->Click += [&](const EventArgs &e) { gotoStep(Step::RealseTheBrakeAndWheel); };
	m_txtBottomTip = createRef<TextBlock>(0.0f, 720.0f, 0.0f, 0.0f);
	m_txtBottomTip->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtBottomTip->setFontSize(28);

	m_3dbtn0 = createRef<Button3D>(0.416f, 0.0f, 0.36f, 0.18f, IMGBR(AI, "parking sapce_rightview/autopark_pic_parkright1_nor.png"), IMGBR(AI, "parking sapce_rightview/autopark_pic_parkright1_sel.png"));
	m_3dbtn1 = createRef<Button3D>(0.326f, 0.27f, 0.18f, 0.36f, IMGBR(AI, "parking sapce_rightview/autopark_pic_parkright5_nor.png"), IMGBR(AI, "parking sapce_rightview/autopark_pic_parkright5_sel.png"));
	m_rightSearchingParent->getScene()->addChild(m_3dbtn0);
	m_rightSearchingParent->getScene()->addChild(m_3dbtn1);
	m_rightSearchingParent->getScene()->setCamera(createRef<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, -1.20f), glm::vec3(2.175f, -0.049f, -0.0f)));

	m_parkDoneTipBg = createRef<Node2D>(0.0f, 0.0f, 1040.0f, 477.0f, SCBR(Color(255, 255, 255, 220)));
	m_parkDoneTipBg->setAlignmentCenter();
	auto icon = Node2D::createWithTextureFrameName(AI, "pic_steeringwheel.png", 0.0f, 40.0f);
	icon->setHorizontalAlignment(HorizontalAlignment::Center);
	m_parkDoneTipBg->addChild(icon);
	m_txtParkDone = createRef<TextBlock>(0.0f, 360.0f, 0.0f, 0.0f);
	m_txtParkDone->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtParkDone->setFontSize(32);
	m_parkDoneTipBg->addChild(m_txtParkDone);
	m_rightParkDoneParent->addChild(m_parkDoneTipBg);

	m_rightSearchingParent->addChild(m_car);
	m_rightSearchingParent->addChild(m_txtBottomTip);
	m_rightSearchingParent->addChild(m_btnStartPark);
	m_rightTopTipParent->addChild(m_topTipBg);

	addChild(m_leftArea);
	addChild(m_rightSearchingParent);
	addChild(m_rightTopTipParent);
	addChild(m_rightParkDoneParent);

	m_aniLadarOpacity.setFrom(0.1f);
	m_aniLadarOpacity.setTo(1.0f);
	m_aniLadarOpacity.setTarget(m_car->getChildAt(0));
	m_aniLadarOpacity.setTargetPropertyName("Opacity");
	m_aniLadarOpacity.duration = TimeSpan::fromMilliseconds(200);
	m_aniLadarOpacity.autoReverse = true;
	m_aniLadarOpacity.repeatBehavior = RepeatBehavior::forever();

	m_tlSearching.duration = TimeSpan::fromMilliseconds(5000);
	m_tlSearching.Process += nbBindEventFunction(AutoParkScene::onTimeLineProgress);
	m_tlSearching.Completed += [&](const EventArgs &e) { m_timer.stop(); gotoStep(Step::SearchedAndPickSlot); };
	m_rightSearchingParent->Touch += [&](const TouchEventArgs &e)
	{
		if (e.action == TouchAction::Down && (m_curStep == Step::SearchedAndPickSlot || m_curStep == Step::ToStart))
		{
			m_btnStartPark->setVisibility(VisibilityE::Visible);
			m_3dbtn0->setCheck(!m_3dbtn0->isCheck());
			m_3dbtn1->setCheck(!m_3dbtn0->isCheck());
			gotoStep(Step::ToStart);
		}
	};
	m_timer.Tick += nbBindEventFunction(AutoParkScene::onTick);
	gotoStep(Step::ToStart);
}

void AutoParkScene::start()
{
	m_aniLadarOpacity.begin();
	gotoStep(Step::Searching);
	m_3dbtn0->setTransform(createRef<Transform>(glm::vec3(0.0f, -10.0f, 0.0f)));
	m_3dbtn1->setTransform(createRef<Transform>(glm::vec3(0.0f, -10.0f, 0.0f)));
	m_timer.start(3000);
}

void AutoParkScene::stop()
{
	m_aniLadarOpacity.stop();
	m_timer.stop();
}

void AutoParkScene::gotoStep(AutoParkScene::Step step)
{
	setTopTipText(getTopTipText(step));
	if (step == Step::NotFound)
	{
		m_tlSearching.begin();
		m_timer.start((uint64_t)m_tlSearching.duration.totalMilliseconds());
	}
	else if (step == Step::RealseTheBrakeAndWheel)
	{
		m_timer.start(3000);
		m_tlSearching.stop();
	}
	else
	{
		m_tlSearching.stop();
	}
	
	m_txtBottomTip->setVisibility(step == Step::Searching || step == Step::NotFound ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnStartPark->setVisibility(step == Step::ToStart ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rightSearchingParent->setVisibility(step <= Step::ToStart ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rightTopTipParent->setVisibility(step != Step::Done ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rightParkDoneParent->setVisibility(step == Step::Done ? VisibilityE::Visible : VisibilityE::Hidden);

	m_curStep = step;
}

void AutoParkScene::setTopTipText(const std::string & txt)
{
	m_txtTopTip->setText(txt);
	auto w = m_txtTopTip->getActualFont()->measure(txt).width;
	m_topTipBg->setWidth((int)w + 100.0f);
}

void AutoParkScene::setTheme(int theme)
{
	m_txtTopTip->setColor(theme == 0 ? Colors::black : Colors::white);
	m_txtBottomTip->setColor(theme == 0 ? Colors::black : Colors::gray);
	m_topTipBg->setImages(IMGBR(AVM, theme == 0 ? "nine0.png" : "nine00.png"), IMGBR(AVM, theme == 0 ? "nine2.png" : "nine22.png"), 
		IMGBR(AVM, theme == 0 ? "nine3.png" : "nine33.png"), IMGBR(AVM, theme == 0 ? "nine1.png" : "nine11.png"), IMGBR(AVM, theme == 0 ? "nine4.png" : "nine44.png"));
}

void AutoParkScene::setLanguage(int lan)
{
	m_txtBottomTip->setText(TR(lan, TID_AutoTip));
	m_btnStartPark->setText(TR(lan, TID_Select_Txt1));
	m_txtParkDone->setText(TR(lan, TID_AutoTip_ParkDone));
	setTopTipText(getTopTipText(m_curStep));
}

void AutoParkScene::onTimeLineProgress(const EventArgs & e)
{
	auto progress = m_tlSearching.getCurrentProgress();
	auto y = m_aniFrom + (m_aniTo - m_aniFrom) * progress;
	m_3dbtn0->getTransform()->setTranslate(glm::vec3(0.0f, y, 0.0f));
	m_3dbtn1->getTransform()->setTranslate(glm::vec3(0.0f, y, 0.0f));
}

void AutoParkScene::onTick(const EventArgs & e)
{
	if ((int)m_curStep + 1 < (int)Step::Max)
	{
		gotoStep(Step((int)m_curStep + 1));
	}
	else
	{
		stop();
	}
}

std::string AutoParkScene::getTopTipText(AutoParkScene::Step step) const
{
	auto lan = LanguageManager::getLanguage();
	std::string sTxtWarn;
	switch (step)
	{
	case AutoParkScene::Step::Searching:				sTxtWarn = TR(lan, TID_AutoTip_Step1); break;
	case AutoParkScene::Step::NotFound:					sTxtWarn = TR(lan, TID_AutoTip_Step2); break;
	case AutoParkScene::Step::SearchedAndPickSlot:		sTxtWarn = TR(lan, TID_AutoTip_Step3); break;
	case AutoParkScene::Step::ToStart:					sTxtWarn = TR(lan, TID_AutoTip_Step4); break;
	case AutoParkScene::Step::RealseTheBrakeAndWheel:	sTxtWarn = TR(lan, TID_AutoTip_Step5); break;
	case AutoParkScene::Step::Parking:					sTxtWarn = TR(lan, TID_AutoTip_Step6); break;
	case AutoParkScene::Step::WatchoutEnv:				sTxtWarn = TR(lan, TID_AutoTip_Step7); break;
	case AutoParkScene::Step::GetBarrier:				sTxtWarn = TR(lan, TID_AutoTip_Step8); break;
	case AutoParkScene::Step::RemoveBarrier:			sTxtWarn = TR(lan, TID_AutoTip_Step9); break;
	case AutoParkScene::Step::Continue:					sTxtWarn = TR(lan, TID_AutoTip_Step6); break;
	default: break;
	}
	return sTxtWarn;
}
//////////
ControllerParkScene::ControllerParkScene()
	: m_curStep(Step::CheckInit)
{
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_rightArea = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_txtTitle = createRef<TextBlock>(600.0f, 230.0f, 0.0f, 0.0f);
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Left);
	m_txtTitle->setFontSize(32);
	m_rightArea->addChild(m_txtTitle);
	glm::vec2 space = { 60.0f, 7.0f };
	for (auto i = 0u; i < m_icons.size(); ++i)
	{
		m_icons[i] = Node2D::createWithTextureFrameName(AI, "number/" + std::to_string(i + 1) + "_d.png", 450.0f, m_txtTitle->y() + 80.0f + 60.0f * i);
		m_txts[i] = createRef<TextBlock>(m_icons[i]->x() + space.x, m_icons[i]->y() + space.y, 0.0f, 0.0f);
		m_txts[i]->setFontSize(32);
		m_rightArea->addChild(m_icons[i]);
		m_rightArea->addChild(m_txts[i]);
	}

	m_iconParkingState = createRef<Node2D>(0.0f, -30.0f, 240.0f, 240.0f);
	m_iconParkingState->setAlignmentCenter();
	m_txtparkingState = createRef<TextBlock>(0.0f, 650.0f, 0.0f, 0.0f);
	m_txtparkingState->setHorizontalAlignment(HorizontalAlignment::Center);

	addChild(m_leftArea);
	addChild(m_rightArea);
	addChild(m_iconParkingState);
	addChild(m_txtparkingState);

	m_timer.Tick += nbBindEventFunction(ControllerParkScene::onTick);
	m_aniTitle.setTarget(m_txtTitle);
	m_aniTitle.setTargetPropertyName("Text");
	m_aniTitle.duration = TimeSpan::fromMilliseconds(800);
	m_aniTitle.repeatBehavior = RepeatBehavior::forever();
}

void ControllerParkScene::start()
{
	gotoStep(Step::CheckInit);
	m_timer.start(1200);
	m_aniTitle.begin();
}

void ControllerParkScene::stop()
{
	m_timer.stop();
	m_aniTitle.stop();
}

void ControllerParkScene::setTheme(int theme)
{
	m_txtTitle->setColor(theme == 0 ? Colors::black : Colors::white);
	for (auto i = 0u; i < m_icons.size(); ++i)
	{
		m_icons[i]->setBackground(IMGBR(AI, std::string("number/") + std::to_string(i + 1) + (theme == 0 ? "_d.png" : "_n.png")));
	}
	m_txtparkingState->setColor(theme == 0 ? Colors::black : Colors::white);
}

void ControllerParkScene::setLanguage(int lan)
{
	std::set<StringKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromMilliseconds(0), TR(lan, TID_Control_Title0) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(200), TR(lan, TID_Control_Title1) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(400), TR(lan, TID_Control_Title2) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(600), TR(lan, TID_Control_Title3) });
	m_aniTitle.setKeyFrames(keyFrames);
	m_txtTitle->setText(TR(lan, TID_Control_Title0));
	m_txts[0]->setText(TR(lan, TID_Control_Txt0));
	m_txts[1]->setText(TR(lan, TID_Control_Txt1));
	m_txts[2]->setText(TR(lan, TID_Control_Txt2));
	m_txts[3]->setText(TR(lan, TID_Control_Txt3));
	m_txts[4]->setText(TR(lan, TID_Control_Txt4));
}

void ControllerParkScene::gotoStep(Step step)
{
	auto normalClr = ThemeManager::getTheme() == 0 ? Colors::black : Colors::white;
	auto okClr = Color(3, 156, 26);
	auto lan = LanguageManager::getLanguage();
	switch (step)
	{
	case ControllerParkScene::Step::CheckInit:		setTextColor(normalClr, normalClr, normalClr, normalClr, normalClr);	break;
	case ControllerParkScene::Step::CheckP:			setTextColor(okClr, normalClr, normalClr, normalClr, normalClr);		break;
	case ControllerParkScene::Step::CheckApp:		setTextColor(okClr, okClr, normalClr, normalClr, normalClr);			break;
	case ControllerParkScene::Step::CheckBT_Fail:	setTextColor(okClr, okClr, Color(241, 26, 26), normalClr, normalClr);	break;
	case ControllerParkScene::Step::CheckBT_Success:setTextColor(okClr, okClr, okClr, normalClr, normalClr);				break;
	case ControllerParkScene::Step::CheckDoorWindow:setTextColor(okClr, okClr, okClr, okClr, normalClr);					break;
	case ControllerParkScene::Step::CheckKeyInCar:	setTextColor(okClr, okClr, okClr, okClr, okClr);						break;
	case ControllerParkScene::Step::ParkingIng:		m_iconParkingState->setBackground(IMGBR(AI, "autopark_pic_alert.png")); m_txtparkingState->setText(TR(lan, TID_Progress_Txt0));									break;
	case ControllerParkScene::Step::ParkingPause:	m_iconParkingState->setBackground(IMGBR(AI, "autopark_pic_pause.png")); m_txtparkingState->setText(TR(lan, TID_Progress_Txt1));									break;
	case ControllerParkScene::Step::ParkingDone:	m_iconParkingState->setBackground(IMGBR(AI, "autopark_pic_compete.png")); m_txtparkingState->setText(TR(lan, TID_Progress_Txt2));									break;
	default:																																break;
	}
	m_leftArea->setVisibility(step <= Step::CheckKeyInCar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rightArea->setVisibility(step <= Step::CheckKeyInCar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_iconParkingState->setVisibility(step >= Step::ParkingIng ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtparkingState->setVisibility(step >= Step::ParkingIng ? VisibilityE::Visible : VisibilityE::Hidden);

	MainView::get()->topbar()->switchState(step >= Step::ParkingIng ? TopBar::State::Exit_Only : TopBar::State::AI_HPA_Bar);
	m_curStep = step;
}

void ControllerParkScene::onTick(const EventArgs & e)
{
	gotoStep(Step((int)m_curStep + 1));
	if (m_curStep >= Step::Max)
		stop();
}

void ControllerParkScene::setTextColor(const Color & clr0, const Color & clr1, const Color & clr2, const Color & clr3, const Color & clr4)
{
	m_txts[0]->setColor(clr0);
	m_txts[1]->setColor(clr1);
	m_txts[2]->setColor(clr2);
	m_txts[3]->setColor(clr3);
	m_txts[4]->setColor(clr4);
}

///////////////////
SelectParkScene::SelectParkScene()
{
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_selNode = Node2D::createWithTextureFrameName(AI, "parking sapce_leftview/parkingspace_fault.png", 100.0f, 100.0f);
	m_nodeP = Node2D::createWithTextureFrameName(AI, "parking sapce_leftview/icon_p_fault.png", 0.0f, 0.0f);
	m_nodeP->setAlignmentCenter();
	m_nodeR = Node2D::createWithTextureFrameName(AI, "parking sapce_leftview/btn_rotate.png", 22.0f, 22.0f);
	m_nodeR->setHorizontalAlignment(HorizontalAlignment::Right);
	m_nodeR->setVerticalAlignment(VerticalAlignment::Bottom);
	m_selNode->setTransform(createRef<RotateTransform2D>(0.0f, 151.0f, 81.0f));
	m_nodeP->setTransform(createRef<RotateTransform2D>(0.0f, 30.0f, 30.0f));
	m_nodeR->setTransform(createRef<RotateTransform2D>(0.0f, -120.0f, -55.0f));
	m_selNode->Touch += nbBindEventFunction(SelectParkScene::onTouch);
	m_nodeR->Touch += nbBindEventFunction(SelectParkScene::onTouch);
	m_selNode->addChild(m_nodeP);
	m_selNode->addChild(m_nodeR);
	m_leftArea->addChild(m_selNode);

	m_rightArea = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_txtTitle = createRef<TextBlock>(0.0f, 200.0f, 0.0f, 0.0f);
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtWarning = createRef<TextBlock>(0.0f, 280.0f, 650.0f, 200.0f);
	m_txtWarning->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtWarning->setWrap(true);
	m_txtWarning->setFontSize(32);
	m_tipBg = createRef<Node2D>(0.0f, 0.0f, 1040.0f, 477.0f, SolidColorBrush::white());
	m_tipBg->setAlignmentCenter();
	auto iconPause = Node2D::createWithTextureFrameName(AI, "pic_parkpause.png", 0.0f, 52.0f);
	iconPause->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTip = createRef<TextBlock>(0.0f, 272.0f, 0.0f, 0.0f);
	m_txtTip->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTip->setFontSize(32);
	m_btnStart = Button::createWithTextureFrameName(AI, "btn_62px_sel.9.png", 0.0f, 355.0f);
	m_btnStart->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStart->setFontSize(28);
	m_tipBg->addChild(iconPause);
	m_tipBg->addChild(m_txtTip);
	m_tipBg->addChild(m_btnStart);
	m_rightArea->addChild(m_txtTitle);
	m_rightArea->addChild(m_txtWarning);
	m_rightArea->addChild(m_tipBg);
	addChild(m_leftArea);
	addChild(m_rightArea);

	m_timerShowTip.setSingleShot(true);
	m_timerShowTip.Tick += [&](const EventArgs &e) { m_tipBg->setVisibility(VisibilityE::Visible); };
	m_timerSetClip.setSingleShot(true);
	m_timerSetClip.Tick += [&](const EventArgs &e) 
	{
		auto rc = m_leftArea->getRenderRect();
		m_selNode->setClipRect(rc);
		m_nodeP->setClipRect(rc);
		m_nodeR->setClipRect(rc);
	};
}

void SelectParkScene::start()
{
	m_tipBg->setVisibility(VisibilityE::Hidden);
	m_timerShowTip.start(3000);
	m_timerSetClip.start(1);
}

void SelectParkScene::stop()
{
	m_timerShowTip.stop();
}

void SelectParkScene::setTheme(int theme)
{
	m_txtTitle->setColor(theme == 0 ? Colors::black : Colors::white);
	m_txtWarning->setColor(theme == 0 ? Colors::black : Colors::white);
	m_tipBg->setBackground(theme == 0 ? SolidColorBrush::white() : SCBR(Color(9, 12, 15, 255)));
	m_txtTip->setColor(theme == 0 ? Colors::black : Colors::white);
	m_btnStart->setTextColor(theme == 0 ? Colors::white : Colors::black, theme == 0 ? Color(255, 255, 255, 150) : Color(0, 0, 0, 150));
}

void SelectParkScene::setLanguage(int lan)
{
	m_txtTitle->setText(TR(lan, TID_Select_Title));
	m_txtWarning->setText(TR(lan, TID_Select_Tip));
	m_txtTip->setText(TR(lan, TID_Select_Txt0));
	m_btnStart->setText(TR(lan, TID_Select_Txt1));
	m_txtWarning->setWidth(lan == 0 ? 650.0f : 800.0f);
}

void SelectParkScene::onTouch(const TouchEventArgs & e)
{
	if (e.sender == m_selNode.get())
	{
		if (e.action == TouchAction::Down)
		{
			auto rc = m_selNode->getRenderRect();
			m_ptPressOnSelectNode = Point{ e.x - rc.x(), e.y - rc.y() };
		}
		else if (e.action == TouchAction::Move && m_ptPressOnSelectNode.x != -1.0f)
		{
			auto parentRc = m_leftArea->getRenderRect();
			Point newPt = Point(e.x, e.y) - m_ptPressOnSelectNode - parentRc.leftTop();
			m_selNode->setPosition(newPt);
		}
		else if (e.action == TouchAction::Up)
		{
			m_ptPressOnSelectNode = { -1.0f };
		}
	}
	else if (e.sender == m_nodeR.get() && m_ptPressOnSelectNode.x == -1.0f)
	{
		if (e.action == TouchAction::Down)
		{
			m_ptPressedOnRNode = {e.x, e.y};
		}
		else if (e.action == TouchAction::Move && m_ptPressedOnRNode.x != -1.0f)
		{
			float xOffset = m_ptPressedOnRNode.x - e.x;
			nb::as<RotateTransform2D>(m_selNode->getTransform())->setAngle(xOffset);
			nb::as<RotateTransform2D>(m_nodeP->getTransform())->setAngle(xOffset);
			nb::as<RotateTransform2D>(m_nodeR->getTransform())->setAngle(xOffset);
		}
		else if (e.action == TouchAction::Up)
		{
			m_ptPressedOnRNode = {-1.0f};
		}
	}
}

//////////////////
AIView::AIView()
{
	TextureLibrary::addTextureAtlas(AI, RES_DIR"ipu02/ai.png", RES_DIR"ipu02/ai.txt");

	//顶部栏
	MainView::get()->topbar()->switchState(TopBar::State::AI_HPA_Bar);
	
	m_autoParkScene = createRef<AutoParkScene>();
	m_controllerParkScene = createRef<ControllerParkScene>();
	m_selectParkScene = createRef<SelectParkScene>();

	m_themeEventHandle = ThemeManager::ThemeChanged() += nbBindEventFunction(AIView::onThemeChanged);
	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(AIView::onLanguageChanged);
	onThemeChanged(ThemeManager::getTheme());
	onLanguageChanged(LanguageManager::getLanguage());

	switchScene(AIViewScene::Auto);
}

AIView::~AIView()
{
	ThemeManager::ThemeChanged() -= m_themeEventHandle;
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void AIView::switchScene(AIViewScene scene)
{
	clearChildren();
	switch (scene)
	{
	case AIViewScene::Auto: addChild(m_autoParkScene);			m_autoParkScene->start(); m_controllerParkScene->stop(); m_selectParkScene->stop(); m_curScene = m_autoParkScene;		break;
	case AIViewScene::Control:addChild(m_controllerParkScene);	m_autoParkScene->stop(); m_controllerParkScene->start(); m_selectParkScene->stop(); m_curScene = m_controllerParkScene;	break;
	case AIViewScene::Select:addChild(m_selectParkScene);		m_autoParkScene->stop(); m_controllerParkScene->stop(); m_selectParkScene->start();	m_curScene = m_selectParkScene;		break;
	default:																																											break;
	}
	MainView::get()->topbar()->switchSlideButton((int)scene, false);
}

ref<Node2D> AIView::currentScene()
{
	return m_curScene;
}

void AIView::onThemeChanged(const int &theme)
{
	m_autoParkScene->setTheme(theme);
	m_controllerParkScene->setTheme(theme);
	m_selectParkScene->setTheme(theme);
}

void AIView::onLanguageChanged(const int & lan)
{
	m_autoParkScene->setLanguage(lan);
	m_controllerParkScene->setLanguage(lan);
	m_selectParkScene->setLanguage(lan);
}

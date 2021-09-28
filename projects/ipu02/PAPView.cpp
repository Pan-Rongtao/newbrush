#include "PAPView.h"
#include "MainView.h"
#include "AVMView.h"
#include "Tr.h"

#define PAP "pap"

PAPView::PAPView()
	: m_curScene(PAPScene::Scene_None)
{
	TextureLibrary::addTextureAtlas(PAP, RES_DIR"ipu02/pap.png", RES_DIR"ipu02/pap.txt");

	m_slideBtn = createRef<SlideButton>(660.0f, 19.0f, 800.0f, 62.0f);
	m_slideBtn->setBackground(IMGBR("ap_day", "btn_62px_nor.9.png"));
	m_slideBtn->setBtn(IMGBR("ap_day", "btn_62px_sel.9.png"));
	//m_slideBtn->addItem(u8"自动泊车");
	//m_slideBtn->addItem(u8"遥控泊车");
	//m_slideBtn->addItem(u8"自选车位");
	//m_slideBtn->addItem(u8"记忆泊车");
	m_slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
	m_slideBtn->SelectChanged += nbBindEventFunction(PAPView::onSlideBtnSelectChanged);
	m_slideBtn->setCurSel(0);
	
	m_helloScene = createRef<HelloScene>();
	m_helloScene->Start += [&](const EventArgs &e) { switchScene(PAPScene::Scene_Tutorial); };
	m_tutoialScene = createRef<TutorialScene>();
	m_tutoialScene->Skip += [&](const EventArgs &e) { switchScene(PAPScene::Scene_Main); };
	m_mainScene = createRef<MainScene>();
	m_mainScene->ToTutorial += [&](const EventArgs &e) { switchScene(PAPScene::Scene_Tutorial); };
	m_rukuScene = createRef<RukuScene>();
	m_rukuScene->BackToMain += [&](const EventArgs &e) { switchScene(PAPScene::Scene_Main); };
	m_rukuScene->Save += [&](const EventArgs &e) { switchScene(PAPScene::Scene_Main); };

	switchScene(PAPScene::Scene_Main);
	
	addChild(m_slideBtn);

	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(PAPView::onLanguageChanged);
	onLanguageChanged(LanguageManager::getLanguage());
}

PAPView::~PAPView()
{
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void PAPView::switchScene(PAPScene scene)
{
	clearChildren();
	switch (scene)
	{
	case PAPScene::Scene_Hello:		addChild(m_helloScene);		break;
	case PAPScene::Scene_Tutorial:	addChild(m_tutoialScene);	break;
	case PAPScene::Scene_Main:		addChild(m_mainScene);		break;
	case PAPScene::Scene_Ruku:		addChild(m_rukuScene);		break;
	default: break;
	}
	
}

void PAPView::onLanguageChanged(const int & lan)
{
	m_helloScene->setLanguage(lan);
	m_tutoialScene->setLanguage(lan);
	m_mainScene->setLanguage(lan);
}

void PAPView::onSlideBtnSelectChanged(const int & e)
{
}

HelloScene::HelloScene()
{
	m_img = createRef<Node2D>();
	m_img->setBackground(createRef<ImageBrush>(RES_DIR"ipu02/pap_hello_bg.png"));

	auto parent = createRef<Node2D>(0.0f, 704.0f, NAN, 376.0f);
	parent->setBackground(SCBR(Color(238, 240, 245, 242)));
	m_btnAgree = createRef<Button>(0.0f, 50.0f, 850.0f, 50.0f);
	m_btnAgree->setIcon(IMGBR(PAP, "btn_off_blue.png"), nullptr, IMGBR(PAP, "btn_on_blue.png"));
	//m_btnAgree->setBackground(SolidColorBrush::red());
	m_btnAgree->setIconTextOffset({0.0f, 5.0f}, {50.0f, 10.0f});
	m_btnAgree->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnAgree->Click += [&](const EventArgs &e) { m_btnAgree->setCheck(!m_btnAgree->isChecked()); m_btnStart->setEnable(m_btnAgree->isChecked()); };

	m_btnStart = Button::createWithTextureFrameName(PAP, "autopark_btn_62px_sel2.png", 0.0f, 150.0f);
	m_btnStart->setBkgndDisable(IMGBR(PAP, "autopark_btn_62px_sel2.png"));
	m_btnStart->setTextColor(Colors::black, Color(0, 0, 0, 150), Colors::black, Colors::gray);
	m_btnStart->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnStart->Click += [&](const EventArgs &e) { Start.invoke(e); };
	parent->addChild(m_btnAgree);
	parent->addChild(m_btnStart);

	addChild(m_img);
	addChild(parent);

	m_btnAgree->setCheck(false); 
	m_btnStart->setEnable(false);
}

void HelloScene::setLanguage(int lan)
{
	m_btnAgree->setText(TR(lan, TID_PAP_Agree));
	m_btnStart->setText(TR(lan, TID_PAP_Accept));
}

TutorialScene::TutorialScene()
{
	m_btnSkip = Button::createWithTextureFrameName(PAP, "autopark_btn_56px_nor.png", 130.0f, 160.0f);
	m_btnSkip->setBkgndPress(IMGBR(PAP, "autopark_btn_56px_sel.png"));
	m_btnSkip->Click += [&](const EventArgs &e) { Skip.invoke(e);  };
	m_dotListCtrl = createRef<DotListCtrl>(0.0f, 906.0f, 140.0f, 50.0f);
	//m_dotListCtrl->setBackground(SolidColorBrush::red());
	m_dotListCtrl->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_dotListCtrl->setDotCount(5);
	m_dotListCtrl->setDotImage(IMGBR(PAP, "dot_n.png"), IMGBR(PAP, "dot_s.png"));
	m_dotListCtrl->setCurSel(0);

	addChild(m_btnSkip);
	addChild(m_dotListCtrl);
}

void TutorialScene::setLanguage(int lan)
{
	m_btnSkip->setText(TR(lan, TID_PAP_Skip));
}

MainScene::MainScene()
{
	m_txtTop = createRef<TextBlock>(0.0f, 13.0f, 0.0f, 0.0f, u8"路线因为xxx原因保存失败，路线自动进行后台学习");
	m_txtTop->setHorizontalAlignment(HorizontalAlignmentE::Center);

	m_txtPathChoose = createRef<TextBlock>(86.0f, 166.0f, 0.0f, 0.0f);
	m_btnToTutorial = Button::createWithTextureFrameName(PAP, "autopark_btn_56px_nor.png", 1650.0f, 151.0f);
	m_btnToTutorial->setBkgndPress(IMGBR(PAP, "autopark_btn_56px_sel.png"));
	m_btnToTutorial->setIcon(IMGBR(PAP, "music_search_icon_search.png"));
	m_btnToTutorial->setIconTextOffset({30.0f, 6.0f}, {78.0f, 13.0f});
	m_btnToTutorial->Click += [&](const EventArgs &e) { ToTutorial.invoke(e);  };

	addChild(m_txtTop);
	addChild(m_txtPathChoose);
	addChild(m_btnToTutorial);
}

void MainScene::setLanguage(int lan)
{
	m_txtPathChoose->setText(TR(lan, TID_PAP_ChooseRoute));
	m_btnToTutorial->setText(TR(lan, TID_PAP_Tutorial));
}

void MainScene::onBtnClick(const EventArgs & e)
{
}

RukuScene::RukuScene()
	: m_bRetried(false)
{
	m_left = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_btnBackToMain = Button::createWithTextureFrameName(PAP, "icon_back.png", 49.0f, 68.0f);
	m_btnBackToMain->Click += [&](const EventArgs &e) { BackToMain.invoke(e); };
	m_txtTitle = createRef<TextBlock>(0.0f, 80.0f, 0.0f, 0.0f);
	m_txtTitle->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_icons[0] = Node2D::createWithTextureFrameName(PAP, "pic_process_nor.png", 69.0f, 142.0f);
	m_icons[1] = Node2D::createWithTextureFrameName(PAP, "pic_process_nor.png", 225.0f, 142.0f);
	m_icons[2] = Node2D::createWithTextureFrameName(PAP, "pic_process_nor.png", 381.0f, 142.0f);
	m_txtTip = createRef<TextBlock>(69.0f, 188.0f, 462.0f, 462.0f);
	m_txtTip->setWrap(true);
	m_iconStop = Node2D::createWithTextureFrameName(PAP, "icon_stop.png", 49.0f, 315.0f);
	m_btnSet = Button::createWithTextureFrameName(PAP, "autopark_btn_62px_sel2.png", 0.0f, 800.0f);
	m_btnSet->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnSet->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnSet->Click += [&](const EventArgs &e) { gotoStep(m_curStep == StopToSetOrign ? SettingOrign : SettingEnd); };
	m_iconLoading = Node2D::createWithTextureFrameName(PAP, "icon_loading_blue_150px.png", 0.0f, 0.0f);
	m_iconLoading->setTransform(createRef<RotateTransform2D>(0.0f, 75.0f, 75.0f));
	m_iconLoading->setAlignmentCenter();
	m_iconLoading->setVisibility(VisibilityE::Hidden);
	m_rukuImg = Node2D::createWithTextureFrameName(PAP, "autopark_pic_car.png", 0.0f, 0.0f);
	m_rukuImg->setAlignmentCenter();
	m_rukuImg->Touch += [&](const TouchEventArgs &e) { if (e.action == TouchActionE::down) { m_right->setVisibility(VisibilityE::Visible); m_right->setBackground(m_rukuImg->background()); m_timerToNextStep.start(); } };

	m_tip = createRef<Node2D>(0.0f, 0.0f, 500.0f, 200.0f, SCBR(Color(0,0,0,200)));
	m_tip->setAlignmentCenter();
	m_txtTipTitle = createRef<TextBlock>(0.0f, 10.0f, 0.0f, 0.0f, u8"设置失败");
	m_txtTipContent = createRef<TextBlock>(0.0f, 60.0f, 0.0f, 0.0f, u8"车门未关闭，请关闭车门后重试");
	m_txtTipTitle->setColor(Colors::white);
	m_txtTipContent->setColor(Colors::white);
	m_txtTipTitle->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_txtTipContent->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnRetry = createRef<Button>(0.0f, 0.0f, m_tip->width() / 2, 50.0f);
	m_btnRetry->setText(u8"重试");
	m_btnRetry->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnRetry->setVerticalAlignment(VerticalAlignmentE::Bottom);
	m_btnExit = createRef<Button>(m_tip->width() / 2, 0.0f, m_tip->width() / 2, 50.0f);
	m_btnExit->setText(u8"退出");
	m_btnExit->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnExit->setVerticalAlignment(VerticalAlignmentE::Bottom);
	m_btnRetry->Click += [&](const EventArgs &e) { gotoStep(StopToSetOrign); m_bRetried = true; };
	m_btnExit->Click += [&](const EventArgs &e) { BackToMain.invoke(e); };
	m_tip->setVisibility(VisibilityE::Hidden);
	m_tip->addChild(m_txtTipTitle);
	m_tip->addChild(m_txtTipContent);
	m_tip->addChild(m_btnRetry);
	m_tip->addChild(m_btnExit);
	
	m_editBg = createRef<Node2D>(69.0f, 239.0f, 462.0f, 72.0f, SCBR(Color(242, 243, 244)));
	m_txtPathName = createRef<TextBlock>(30.0f, 0.0f, 0.0f, 0.0f);
	m_txtPathName->setVerticalAlignment(VerticalAlignmentE::Center);
	m_btnDel = Button::createWithTextureFrameName(PAP, "btn_delete.png", 398.0f, 0.0f);
	m_btnDel->setVerticalAlignment(VerticalAlignmentE::Center);
	m_btnDel->Click += [&](const EventArgs &e) {m_txtPathName->setText(""); };
	m_editBg->addChild(m_txtPathName);
	m_editBg->addChild(m_btnDel);
	m_btnCandidateHome0 = Button::createWithTextureFrameName(PAP, "autopark_btn_42px_nor.png", 75.0f, 322.0f);
	m_btnCandidateOffice = Button::createWithTextureFrameName(PAP, "autopark_btn_42px_nor.png", 241.0f, 322.0f);
	m_btnCandidateHome1 = Button::createWithTextureFrameName(PAP, "autopark_btn_42px_nor.png", 412.0f, 322.0f);
	m_btnCandidateHome0->setText(u8"家");
	m_btnCandidateOffice->setText(u8"公司");
	m_btnCandidateHome1->setText(u8"老家");
	m_btnCandidateHome0->Click += [&](const EventArgs &e) { m_txtPathName->setText(m_btnCandidateHome0->text()); };
	m_btnCandidateOffice->Click += [&](const EventArgs &e) { m_txtPathName->setText(m_btnCandidateOffice->text()); };
	m_btnCandidateHome1->Click += [&](const EventArgs &e) { m_txtPathName->setText(m_btnCandidateHome1->text()); };
	m_btnSave = Button::createWithTextureFrameName(PAP, "autopark_btn_62px_sel2.png", 180.0f, 663.0f);
	m_btnSave->setText(u8"保存");
	m_btnSave->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnSave->Click += [&](const EventArgs &e) { Save.invoke(e); };

	m_left->addChild(m_btnBackToMain);
	m_left->addChild(m_txtTitle);
	m_left->addChild(m_icons[0]);
	m_left->addChild(m_icons[1]);
	m_left->addChild(m_icons[2]);
	m_left->addChild(m_txtTip);
	m_left->addChild(m_iconStop);
	m_left->addChild(m_iconLoading);
	m_left->addChild(m_btnSet);
	m_left->addChild(m_tip);
	m_left->addChild(m_rukuImg);
	m_left->addChild(m_editBg);
	m_left->addChild(m_btnCandidateHome0);
	m_left->addChild(m_btnCandidateOffice);
	m_left->addChild(m_btnCandidateHome1);
	m_left->addChild(m_btnSave);

	m_right = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);

	addChild(m_left);
	addChild(m_right);

	m_aniSettingOrigin.setFrom(0.0);
	m_aniSettingOrigin.setTo(360.0f);
	m_aniSettingOrigin.setTarget(m_iconLoading->getTransform());
	m_aniSettingOrigin.setTargetPropertyName("Angle");
	m_aniSettingOrigin.duration = TimeSpan::fromSeconds(1);
	m_aniSettingOrigin.repeatBehavior = RepeatBehavior::fromCount(2);
	m_aniSettingOrigin.Completed += [&](const EventArgs &e) 
	{
		if (m_curStep == SettingOrign)
			gotoStep(m_bRetried ? SetOrignSuccess : SetOrignFailWithDoorOpen);
		else
			gotoStep(SetEndSuccess);
	};

	m_timerToNextStep.setSingleShot(true);
	m_timerToNextStep.setInterval(4000);
	m_timerToNextStep.Tick += [&](const EventArgs &e) { m_right->setVisibility(VisibilityE::Hidden); gotoStep(m_curStep == SetOrignSuccess ? StopToSetEnd : SavePath); };

	gotoStep(Step::StopToSetOrign);

}

void RukuScene::gotoStep(Step step)
{
	m_curStep = step;
	switch (step)
	{
	case StopToSetOrign:	m_txtTip->setText(u8"请停车后，设置当前位置为路线起点");										break;
	case SettingOrign:		m_txtTip->setText(u8"正在设置为起点，请稍后......");	m_aniSettingOrigin.begin();				break;
	case SetOrignFailWithDoorOpen:																							break;
	case SetOrignSuccess:	m_txtTip->setText(u8"起点设置成功，点击查看大图");	m_timerToNextStep.start();					break;

	case StopToSetEnd:		m_txtTip->setText(u8"请将车泊入您常用的停车位，\n停车后，点击下方按钮设置终点");				break;
	case SettingEnd:		m_txtTip->setText(u8"正在设置为终点，请稍后......"); m_aniSettingOrigin.begin();				break;
	case SetEndSuccess:		m_txtTip->setText(u8"终点设置成功，点击查看大图"); m_timerToNextStep.start();					break;

	case SavePath:			m_txtTip->setText(u8"路线名称");					break;
	default:																												break;
	};
	m_iconStop->setVisibility(step == StopToSetOrign ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSet->setVisibility(step == StopToSetOrign || step == StopToSetEnd ? VisibilityE::Visible : VisibilityE::Hidden);
	m_iconLoading->setVisibility(step == SettingOrign || step == SettingEnd ? VisibilityE::Visible : VisibilityE::Hidden);
	m_tip->setVisibility(step == SetOrignFailWithDoorOpen ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rukuImg->setVisibility(step == SetOrignSuccess || step == SetEndSuccess ? VisibilityE::Visible : VisibilityE::Hidden);
	//m_txtTip->setVisibility(step <= SetEndSuccess ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSet->setText(step <= SetOrignSuccess ? u8"设为起点" : u8"设为终点");
	m_txtTitle->setText(step == SavePath ? u8"保存入库路线" : step <= SetOrignSuccess ? u8"设置入库起点" : u8"设置入库终点");
//	auto grayBrush = IMGBR(PAP, "pic_process_nor.png");
//	auto greenBrush = IMGBR(PAP, "pic_process_sel.png");
//	m_icons[0]->setBackground(step == 0 ? greenBrush : grayBrush);
//	m_icons[1]->setBackground(step == 1 ? greenBrush : grayBrush);
//	m_icons[2]->setBackground(step == 2 ? greenBrush : grayBrush);
}

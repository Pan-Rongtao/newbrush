#include "HPAView.h"
#include "MainView.h"
#include "AVMView.h"
#include "AIView.h"
#include "Tr.h"

constexpr int CardCountPerPage = 4;

HPAView::HPAView()
	: m_curScene(HPAScene::Scene_None)
{
	TextureLibrary::addTextureAtlas(HPA, RES_DIR"ipu02/hpa.png", RES_DIR"ipu02/hpa.txt");

	MainView::get()->topbar()->switchState(TopBar::State::AI_HPA_Bar);
	MainView::get()->topbar()->switchSlideButton(3, false);

	m_helloScene = createRef<HelloScene>();
	m_helloScene->Start += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Tutorial); };
	m_tutoialScene = createRef<TutorialScene>();
	m_tutoialScene->Start += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Main); };
	m_mainScene = createRef<MainScene>();
	m_mainScene->ToTutorialScene += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Tutorial); };
	m_mainScene->ToParkingScene += [&](const MainScene::ToParkingSceneEventArgs &e) { switchScene(HPAScene::Scene_Parking); m_parkingScene->setPathType(e.pathType); m_parkingScene->setName(e.name); };
	m_mainScene->ToRukuScene += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Ruku); };
	m_mainScene->ToChukuScene += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Chuku); };
	m_mainScene->ToEditCardScene += [&](const MainScene::ToEditCardSceneEventArgs &e) { switchScene(HPAScene::Scene_Edit); m_editScene->setIndex(e.index); m_editScene->setParkingSlotType(e.psType); m_editScene->setName(e.name); };
	m_rukuChukuScene = createRef<RukuChukuScene>();
	m_rukuChukuScene->BackToMain += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Main); };
	m_rukuChukuScene->SavePath += [&](const RukuChukuScene::SavePathEventArgs &e) { switchScene(HPAScene::Scene_Main); m_mainScene->addCard(CardType::Ready, e.pathType, e.psType, e.name ); };
	m_rukuChukuScene->Delete += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Main); };
	m_parkingScene = createRef<ParkingScene>();
	m_editScene = createRef<EditCardScene>();
	m_editScene->BackToMain += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Main); };
	m_editScene->SaveCard += [&](const EventArgs &e) { switchScene(HPAScene::Scene_Main); };
	m_editScene->DeleteCard += [&](const Index &e) { switchScene(HPAScene::Scene_Main); m_mainScene->removeCard(e); };

	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(HPAView::onLanguageChanged);
	onLanguageChanged(LanguageManager::getLanguage());

	switchScene(HPAScene::Scene_Hello);
}

HPAView::~HPAView()
{
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void HPAView::switchScene(HPAScene scene)
{
	clearChildren();
	switch (scene)
	{
	case HPAScene::Scene_Hello:		addChild(m_helloScene);		break;
	case HPAScene::Scene_Tutorial:	addChild(m_tutoialScene);	break;
	case HPAScene::Scene_Main:		addChild(m_mainScene);		break;
	case HPAScene::Scene_Ruku:		addChild(m_rukuChukuScene);	m_rukuChukuScene->setPathType(PathType::Ruku);	m_rukuChukuScene->gotoStep(RukuChukuScene::Step::StopToSetOrign);	break;
	case HPAScene::Scene_Chuku:		addChild(m_rukuChukuScene);	m_rukuChukuScene->setPathType(PathType::Chuku);	m_rukuChukuScene->gotoStep(RukuChukuScene::Step::StopToSetOrign);	break;
	case HPAScene::Scene_Parking:	addChild(m_parkingScene);	break;
	case HPAScene::Scene_Edit:		addChild(m_editScene);		break;
	default: break;
	}
	if (scene == HPAScene::Scene_Parking)
		m_parkingScene->start();
	else 
		m_parkingScene->stop();
}

void HPAView::onLanguageChanged(const int & lan)
{
	m_helloScene->setLanguage(lan);
	m_tutoialScene->setLanguage(lan);
	m_mainScene->setLanguage(lan);
}

HelloScene::HelloScene()
{
	BrushLibrary::addImageBrush("bg", RES_DIR"ipu02/hpa_hello_bg.png");
	m_img = createRef<Node2D>();
	m_img->setBackground(BrushLibrary::get<ImageBrush>("bg"));

	auto parent = createRef<Node2D>(0.0f, 704.0f, NAN, 376.0f);
	parent->setBackground(SCBR(Color(238, 240, 245, 242)));
	m_btnAgree = createRef<Button>(0.0f, 50.0f, 850.0f, 50.0f);
	m_btnAgree->setIcon(IMGBR(HPA, "btn_off_blue.png"), nullptr, IMGBR(HPA, "btn_on_blue.png"));
	m_btnAgree->setIconTextOffset({0.0f, 5.0f}, {50.0f, 10.0f});
	m_btnAgree->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnAgree->setFontSize(28);
	m_btnAgree->Click += [&](const EventArgs &e) { m_btnAgree->setCheck(!m_btnAgree->isChecked()); m_btnStart->setEnable(m_btnAgree->isChecked()); };
	m_btnStart = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel2.png", 0.0f, 150.0f);
	m_btnStart->setBkgndDisable(IMGBR(HPA, "autopark_btn_62px_nor1.png"));
	m_btnStart->setTextColor(Colors::white, Color(255, 255, 255, 150), Colors::white, Colors::gray);
	m_btnStart->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStart->setFontSize(28);
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
	m_btnAgree->setText(TR(lan, TID_HPA_Agree));
	m_btnStart->setText(TR(lan, TID_HPA_Accept));
}

//////////////////////////////
TutorialScene::TutorialScene()
{
	m_btnSkip = Button::createWithTextureFrameName(HPA, "autopark_btn_56px_nor.png", 130.0f, 160.0f);
	m_btnSkip->setBkgndPress(IMGBR(HPA, "autopark_btn_56px_sel.png"));
	m_btnSkip->setFontSize(28);
	m_btnSkip->Click += [&](const EventArgs &e) { Start.invoke(e);  };
	m_btnStart = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel.png", 310.0f, 360.0f);
	m_btnStart->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnStart->setFontSize(28);
	m_btnStart->Click += [&](const EventArgs &e) { Start.invoke(e);  };
	m_txtTitle = createRef<TextBlock>(0.0f, 170.0f, 0.0f, 0.0f);
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_dotListCtrl = createRef<DotListCtrl>(0.0f, 906.0f, 140.0f, 50.0f);
	m_dotListCtrl->setHorizontalAlignment(HorizontalAlignment::Center);
	m_dotListCtrl->setDotCount(5);
	m_dotListCtrl->setDotImage(IMGBR(HPA, "dot_n.png"), IMGBR(HPA, "dot_s.png"));
	m_pageCtrl = createRef<PageCtrl>(0.0f, 293.0f, 1920.0f, 537.0f);
	m_pageCtrl->bindDotListCtrl(m_dotListCtrl);
	m_pageCtrl->CurPageChanged += [&](const int &e) { m_txtTitle->setText(getTitle(e)); };

	for (auto i = 0; i < m_dotListCtrl->dotCount(); ++i)
	{
		auto page = createRef<Node2D>(0.0f, 0.0f, m_pageCtrl->width(), m_pageCtrl->height());
		m_txts[i] = createRef<TextBlock>(130.0f, 0.0f, 600.0f, page->height());
		//m_txts[i]->setFontSize(32);
		m_txts[i]->setWrap(true);
		page->addChild(m_txts[i]);
		m_pageCtrl->addPage(page);
	}
	m_pageCtrl->getPage(4)->addChild(m_btnStart);

	addChild(m_pageCtrl);
	addChild(m_btnSkip);
	addChild(m_txtTitle);
	addChild(m_dotListCtrl);
}

void TutorialScene::setLanguage(int lan)
{
	m_btnSkip->setText(TR(lan, TID_HPA_Skip));
	m_txtTitle->setText(getTitle(m_pageCtrl->curPage()));
	m_btnStart->setText(TR(lan, TID_HPA_Tutorial_Start));
	m_txts[0]->setText(TR(0, TID_HPA_Tutorial_Page0));
	m_txts[1]->setText(TR(0, TID_HPA_Tutorial_Page1));
	m_txts[2]->setText(TR(0, TID_HPA_Tutorial_Page2));
	m_txts[3]->setText(TR(0, TID_HPA_Tutorial_Page3));
	m_txts[4]->setText(TR(0, TID_HPA_Tutorial_Page4));
}

std::string TutorialScene::getTitle(int page) const
{
	auto lan = LanguageManager::getLanguage();
	std::string ret;
	switch (page)
	{
	case 0: ret = TR(lan, TID_HPA_Tutorial_Title0); break;
	case 1: ret = TR(lan, TID_HPA_Tutorial_Title1); break;
	case 2: ret = TR(lan, TID_HPA_Tutorial_Title2); break;
	case 3: ret = TR(lan, TID_HPA_Tutorial_Title3); break;
	case 4: ret = TR(lan, TID_HPA_Tutorial_Title4); break;
	default:										break;
	}
	return ret;
}
///////////////
constexpr char vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec2 v_uv;
void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char fs[] = R"(
precision mediump float;
uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
varying vec2 v_uv;
uniform float u_progress;
uniform vec4 u_box;

void main( void )
{
	vec4 _color0 = texture2D(u_sampler0, v_uv);
	vec4 _color1 = texture2D(u_sampler1, v_uv);
	float x = (gl_FragCoord.x - u_box.x) / u_box.z;
	gl_FragColor = x < u_progress ? _color1 : _color0;
}
)";

ProgressMaterial::ProgressMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2)
	: Material(ShaderLibrary::get("shader_progress", vs, fs))
	, texture1(tex1)
	, texture2(tex2)
	, progress(0.0f)
{
	tex2->setSamplerUnit(1);
}

void ProgressMaterial::uploadUniform(ref<Camera> camera)
{
	auto box = node->getRenderRect();
	shader->setFloat4("u_box", glm::vec4(box.x(), box.y(), box.width(), box.height()));
	shader->setFloat("u_progress", progress);
	shader->setInt("u_sampler0", 0);
	shader->setInt("u_sampler1", 1);
	if (texture1) texture1->activeAndBind();
	if (texture2) texture2->activeAndBind();
}

///////////////
Card::Card(MainScene *mainScene, PathType pathType, ParkingSlotType psType, const std::string &name)
	: m_mainScene(mainScene)
	, m_pathType(pathType)
	, m_psType(psType)
	, m_name(name)
{
	setBackground(SolidColorBrush::white());
	setSize({ 395.0f, 530.0f });

	m_img = Node2D::createWithTextureFrameName(HPA, "img.png", 0.0f, 0.0f);
	m_txtPathIndex = createRef<TextBlock>(20.0f, 20.0f, 0.0f, 0.0f);
	m_txtPathIndex->setFontSize(28);
	m_btnEdit = Button::createWithTextureFrameName(HPA, "btn_detail.png", 300.0f, 10.0f);
	m_btnEdit->setText(u8"编辑");
	m_btnEdit->setFontSize(20);
	m_btnEdit->setTextColorPress(Color(0, 0, 0, 150));
	m_btnEdit->Click += [&](const EventArgs &e) { m_mainScene->ToEditCardScene.invoke({ m_index, m_psType, m_name }); };
	m_txtPathName = createRef<TextBlock>(0.0f, 288.0f, 0.0f, 0.0f);
	m_txtPathName->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtPathBrief = createRef<TextBlock>(0.0f, 338.0f, 0.0f, 0.0f);
	m_txtPathBrief->setFontSize(20);
	m_txtPathBrief->setColor(Colors::gray);
	m_txtPathBrief->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStart = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel2.png", 0.0f, 447.0f);
	m_btnStart->setBkgndDisable(IMGBR(HPA, "autopark_btn_62px_nor1.png"));
	m_btnStart->setText(u8"开始使用");
	m_btnStart->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStart->setFontSize(28);
	m_btnStart->Click += [&](const EventArgs &e) 
	{ 
		if(m_mode == CardType::Ready)	m_mainScene->ToParkingScene.invoke({ m_pathType, m_name });
		else							m_mainScene->removeCard(m_index);
	};

	m_txtTip = createRef<TextBlock>(0.0f, 412.0f, 0.0f, 0.0f);
	m_txtTip->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTip->setColor(Colors::gray);
	m_txtTip->setFontSize(20);

	m_bgDel = createRef<Node2D>(0.0f, 0.0f, NAN, NAN, SCBR(Color(240, 240, 240, 220)));
	m_txtLearnFail = createRef<TextBlock>(0.0f, 288.0f, 0.0f, 0.0f, u8"后台学习失败");
	m_txtLearnFail->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtLearnFail->setColor(Colors::red);
	m_txtDelTip = createRef<TextBlock>(0.0f, 338.0f, 0.0f, 0.0f, u8"10天后将自动删除");
	m_txtDelTip->setFontSize(20);
	m_txtDelTip->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtDelTip->setColor(Color(255, 0, 0, 150));
	m_iconDel = Node2D::createWithTextureFrameName(HPA, "icon_delete.png", 0.0f, 81.0f);
	m_iconDel->setHorizontalAlignment(HorizontalAlignment::Center);

	m_txtNewTitle = createRef<TextBlock>(0.0f, 124.0f, 0.0f, 0.0f, u8"创建路线");
	m_txtNewTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnRuku = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_nor1.png", 0.0f, 254.0f);
	m_btnRuku->setText(u8"入库");
	m_btnRuku->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnRuku->setTextColor(Color(70, 70, 70), Color(70, 70, 70, 125));
	m_btnRuku->setFontSize(28.0f);
	m_btnRuku->Click += [&](const EventArgs &e) { m_mainScene->ToRukuScene.invoke(e); };
	m_btnChuku = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_nor1.png", 0.0f, 349.0f);
	m_btnChuku->setText(u8"出库");
	m_btnChuku->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnChuku->setTextColor(Color(70, 70, 70), Color(70, 70, 70, 125));
	m_btnChuku->setFontSize(28.0f);
	m_btnChuku->Click += [&](const EventArgs &e) { m_mainScene->ToChukuScene.invoke(e); };

	static auto tex1 = createRef<Texture2D>(RES_DIR"ipu02/hpa/autopark_btn_62px_nor1.png");
	static auto tex2 = createRef<Texture2D>(RES_DIR"ipu02/hpa/autopark_btn_62px_sel2.png");;
	auto progressMaterial = createRef<ProgressMaterial>(tex1, tex2);
	progressMaterial->progress = 0.3f;
	progressMaterial->node = m_btnStart;
	m_progressBrush = createRef<EffectBrush>(progressMaterial, nullptr);

	addChild(m_img);
	addChild(m_txtPathIndex);
	addChild(m_btnEdit);

	addChild(m_bgDel);
	addChild(m_iconDel);
	addChild(m_txtLearnFail);
	addChild(m_txtDelTip);

	addChild(m_txtPathName);
	addChild(m_txtPathBrief);
	addChild(m_txtTip);
	addChild(m_btnStart);

	addChild(m_txtNewTitle);
	addChild(m_btnRuku);
	addChild(m_btnChuku);

	m_tlProgress.duration = TimeSpan::fromMilliseconds(5000);
	m_tlProgress.repeatBehavior = RepeatBehavior::forever();
	m_tlProgress.autoReverse = true;
	m_tlProgress.Process += [&](const EventArgs &e)
	{
		auto progress = m_tlProgress.getCurrentProgress();
		auto value = 0 + (100 - 0) * progress;
		auto material = as<ProgressMaterial>( as<EffectBrush>(m_progressBrush)->material );
		material->progress = value / 100.0f;
		auto s = u8"保存中   " + std::to_string((int)value) + "%";
		m_btnStart->setText(s);
	};

	updatePathBrief();
}

void Card::setCardType(CardType mode)
{
	m_img->setVisibility(mode != CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtPathIndex->setVisibility(mode != CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnEdit->setVisibility(mode != CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtPathName->setVisibility(mode != CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtPathBrief->setVisibility(mode != CardType::Delete && mode != CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	
	m_btnStart->setVisibility(mode == CardType::Ready || mode == CardType::Saving || mode == CardType::Learning || mode == CardType::Delete ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnStart->setEnable(mode != CardType::Saving && mode != CardType::Learning);
	m_btnStart->setText(mode == CardType::Ready ? u8"开始使用" : mode == CardType::Saving ? u8"" : mode == CardType::Learning ? u8"后台学习中" : u8"删除");
	m_btnStart->setBkgndNormal(IMGBR(HPA, mode == CardType::Ready ? "autopark_btn_62px_sel2.png" : mode == CardType::Learning ? "autopark_btn_62px_nor1.png" : "autopark_btn_62px_warn2.png"));
	m_btnStart->setTextColorNormal(mode == CardType::Ready ? Colors::white : mode == CardType::Learning ? Colors::black : Colors::red);
	m_btnStart->setTextColorPress(mode == CardType::Ready ? Color(255, 255, 255, 150) : mode == CardType::Learning ? Colors::black : Color(255, 0, 0, 125));
	m_btnStart->setTextColorDisable(mode == CardType::Saving ? Colors::white : Color(70, 70, 70, 255));
	if (mode == CardType::Ready)
	{
		m_btnStart->setBkgndNormal(IMGBR(HPA, "autopark_btn_62px_sel2.png"));
	}
	else if (mode == CardType::Saving)
	{
		m_btnStart->setBkgndNormal(m_progressBrush);
		m_btnStart->setBkgndDisable(m_progressBrush);
	}
	else if (mode == CardType::Learning)
	{
		m_btnStart->setBkgndNormal(IMGBR(HPA, "autopark_btn_62px_nor1.png"));
	}
	else
	{
		m_btnStart->setBkgndNormal(IMGBR(HPA, "autopark_btn_62px_warn2.png"));
	}

	m_txtTip->setVisibility(mode == CardType::Saving || mode == CardType::Learning ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtTip->setText(mode == CardType::Saving ? u8"保存后台运行，现可退出应用" : u8"路线将在后台自动学习");

	m_bgDel->setVisibility(mode == CardType::Delete ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtLearnFail->setVisibility(mode == CardType::Delete ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtDelTip->setVisibility(mode == CardType::Delete ? VisibilityE::Visible : VisibilityE::Hidden);
	m_iconDel->setVisibility(mode == CardType::Delete ? VisibilityE::Visible : VisibilityE::Hidden);

	m_txtNewTitle->setVisibility(mode == CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnRuku->setVisibility(mode == CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnChuku->setVisibility(mode == CardType::Create ? VisibilityE::Visible : VisibilityE::Hidden);

	if (mode == CardType::Saving) 
		m_tlProgress.begin();
	else 
		m_tlProgress.stop();

	m_mode = mode;
}

void Card::setIndex(const Index &index)
{
	m_index = index;
	auto n = m_index.pageIndex * CardCountPerPage + m_index.cardIndex + 1;
	m_txtPathIndex->setText(u8"路线" + std::to_string(n));
}

void Card::updatePathBrief()
{
	m_txtPathName->setText(m_name);
	std::string sBrief = (m_pathType == PathType::Ruku ? u8"入库" : u8"出库") + std::string(" | ");
	sBrief += m_psType == ParkingSlotType::Settled ? u8"固定车位" : u8"途径车位";
	m_txtPathBrief->setText(sBrief);
}

MainScene::MainScene()
{
//	m_txtTop = createRef<TextBlock>(0.0f, 13.0f, 0.0f, 0.0f, u8"路线因为xxx原因保存失败，路线自动进行后台学习");
//	m_txtTop->setHorizontalAlignment(HorizontalAlignment::Center);

	m_txtPathChoose = createRef<TextBlock>(86.0f, 166.0f, 0.0f, 0.0f);
	m_btnToTutorial = Button::createWithTextureFrameName(HPA, "autopark_btn_56px_nor.png", 1650.0f, 151.0f);
	m_btnToTutorial->setBkgndPress(IMGBR(HPA, "autopark_btn_56px_sel.png"));
	m_btnToTutorial->setIcon(IMGBR(HPA, "music_search_icon_search.png"));
	m_btnToTutorial->setIconTextOffset({30.0f, 6.0f}, {78.0f, 13.0f});
	m_btnToTutorial->setFontSize(28);
	m_btnToTutorial->Click += [&](const EventArgs &e) { ToTutorialScene.invoke(e);  };

	m_dotListCtrl = createRef<DotListCtrl>(0.0f, 906.0f, 50.0f, 50.0f);
	m_dotListCtrl->setHorizontalAlignment(HorizontalAlignment::Center);
	m_dotListCtrl->setDotCount(1);
	m_dotListCtrl->setDotImage(IMGBR(HPA, "dot_n.png"), IMGBR(HPA, "dot_s.png"));
	m_pageCtrl = createRef<PageCtrl>(0.0f, 270.0f, 1920.0f, 600.0f);
	m_pageCtrl->bindDotListCtrl(m_dotListCtrl);

	m_createCard = createRef<Card>(this, PathType::None, ParkingSlotType::None, "");
	m_createCard->setCardType(CardType::Create);
	m_createCard->setVerticalAlignment(VerticalAlignment::Center);

//	addChild(m_txtTop);
	addChild(m_txtPathChoose);
	addChild(m_btnToTutorial);
	addChild(m_pageCtrl);
	addChild(m_dotListCtrl);

	addCard(CardType::Ready, PathType::Chuku, ParkingSlotType::Settled, u8"温暖的家");
	addCard(CardType::Ready, PathType::Ruku, ParkingSlotType::Temp, u8"奋斗的公司");
	addCard(CardType::Saving, PathType::Chuku, ParkingSlotType::Settled, u8"温暖的家");
	addCard(CardType::Learning, PathType::Ruku, ParkingSlotType::Temp, u8"温暖的家");
	addCard(CardType::Delete, PathType::None, ParkingSlotType::None, "");
}

void MainScene::setLanguage(int lan)
{
	m_txtPathChoose->setText(TR(lan, TID_HPA_ChooseRoute));
	m_btnToTutorial->setText(TR(lan, TID_HPA_Tutorial));
}

void MainScene::addCard(CardType mode, PathType pathType, ParkingSlotType psType, const std::string &title)
{
	auto cardCount = getCardCount();
	auto actualCardCount = cardCount == 0 ? 0 : cardCount - 1;
	if (cardCount == CardCountPerPage * 2)
	{
		//提示满了
		int x = 10;
	}
	else
	{
		if (cardCount % CardCountPerPage == 0)	//添加一页
		{
			auto page = createRef<Node2D>(0.0f, 0.0f, NAN, NAN);
			m_pageCtrl->addPage(page);
			m_dotListCtrl->setDotCount(m_pageCtrl->pageCount());
		}

		auto cardPageIndex = actualCardCount / CardCountPerPage;
		auto cardIndex = actualCardCount % CardCountPerPage;
		auto card = createRef<Card>(this, pathType, psType, title);
		card->setCardType(mode);
		card->setIndex(Index{ cardPageIndex, cardIndex });
		card->setVerticalAlignment(VerticalAlignment::Center);
		card->setX(75.0f + (62.0f + card->width()) * (actualCardCount % CardCountPerPage));
		auto lastPage = m_pageCtrl->getChildAt(m_pageCtrl->childCount() - 1);
		auto prevPage = m_pageCtrl->pageCount() <= 1 ? nullptr : m_pageCtrl->getChildAt(m_pageCtrl->childCount() - 2);
		if (prevPage && cardCount % CardCountPerPage == 0)
		{
			prevPage->addChild(card);
		}
		else
		{
			lastPage->addChild(card);
		}
		//原来的page去掉m_creatCard
		auto parent = m_createCard->getParent();
		if (parent)
		{
			parent->removeChild(m_createCard);
		}
		cardCount = getCardCount();
		m_createCard->setX(75.0f + (62.0f + card->width()) * (cardCount % CardCountPerPage));
		lastPage->addChild(m_createCard);

	}
}

void MainScene::removeCard(const Index &index)
{
	if (index.pageIndex >= m_pageCtrl->pageCount() || index.cardIndex >= CardCountPerPage)
		return;

	//移动
	auto cardCount = getCardCount();
	for (int i = index.pageIndex * CardCountPerPage + index.cardIndex; i < cardCount - 1; ++i)
	{
		auto nPageIndex = i / CardCountPerPage;
		auto nCardIndex = i % CardCountPerPage;
		auto newCard = as<Card>( m_pageCtrl->getPage((i + 1) / CardCountPerPage)->getChildAt((i + 1) % CardCountPerPage) );
		newCard->setIndex(Index{ nPageIndex, nCardIndex });
		newCard->setX(75.0f + (62.0f + newCard->width()) * (nCardIndex % CardCountPerPage));
		m_pageCtrl->getPage(nPageIndex)->setChildAt(nCardIndex, newCard);
	}
	
	auto lastPage = m_pageCtrl->getPage(m_pageCtrl->pageCount() - 1);
	lastPage->removeChild(lastPage->childCount() - 1);
	if ((cardCount - 1) % CardCountPerPage == 0)
	{
		m_pageCtrl->removePage(m_pageCtrl->pageCount() - 1);
		m_dotListCtrl->setDotCount(m_pageCtrl->pageCount());
	}
}

int MainScene::getCardCount() const
{
	int ret = 0;
	for (auto i = 0; i < m_pageCtrl->pageCount(); ++i)
	{
		ret += m_pageCtrl->getPage(i)->childCount();
	}
	return ret;
}

int MainScene::getActualCardCount() const
{
	auto cardCount = getCardCount();
	return cardCount == 0 ? 0 : cardCount - 1;
}

////////////////
RukuChukuScene::RukuChukuScene()
	: m_bRetried(false)
{
	m_left = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_btnBackToMain = Button::createWithTextureFrameName(AVM, "day/topbar/icon_topbar_back.png", 49.0f, 68.0f);
	m_btnBackToMain->Click += [&](const EventArgs &e) { m_timerToNextStep.stop(); m_aniSettingOrigin.stop(); BackToMain.invoke(e); };
	m_txtTitle = createRef<TextBlock>(0.0f, 80.0f, 0.0f, 0.0f);
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_icons[0] = Node2D::createWithTextureFrameName(HPA, "pic_process_nor.png", 69.0f, 142.0f);
	m_icons[1] = Node2D::createWithTextureFrameName(HPA, "pic_process_nor.png", 225.0f, 142.0f);
	m_icons[2] = Node2D::createWithTextureFrameName(HPA, "pic_process_nor.png", 381.0f, 142.0f);
	m_txtTip = createRef<TextBlock>(69.0f, 188.0f, 462.0f, 462.0f);
	m_txtTip->setFontSize(32);
	m_txtTip->setWrap(true);
	m_iconStop = Node2D::createWithTextureFrameName(HPA, "icon_stop.png", 49.0f, 315.0f);
	m_btnSetBegOrEnd = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel2.png", 0.0f, 800.0f);
	m_btnSetBegOrEnd->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnSetBegOrEnd->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnSetBegOrEnd->setFontSize(28);
	m_btnSetBegOrEnd->Click += [&](const EventArgs &e) { gotoStep(m_curStep == Step::StopToSetOrign ? Step::SettingOrign : Step::SettingEnd); };
	m_iconLoading = Node2D::createWithTextureFrameName(HPA, "icon_loading_blue_150px.png", 0.0f, 0.0f);
	m_iconLoading->setTransform(createRef<RotateTransform2D>(0.0f, 75.0f, 75.0f));
	m_iconLoading->setAlignmentCenter();
	m_iconLoading->setVisibility(VisibilityE::Hidden);
	m_rukuImg = Node2D::createWithTextureFrameName(HPA, "autopark_pic_car.png", 0.0f, 0.0f);
	m_rukuImg->setAlignmentCenter();
	m_rukuImg->Touch += [&](const TouchEventArgs &e) { if (e.action == TouchAction::Down)  { m_right->setVisibility(VisibilityE::Visible); m_timerToNextStep.start(); } };

	m_tip = createRef<Node2D>(0.0f, 0.0f, 500.0f, 200.0f, SCBR(Color(0,0,0,200)));
	m_tip->setAlignmentCenter();
	m_txtTipTitle = createRef<TextBlock>(0.0f, 10.0f, 0.0f, 0.0f, u8"设置失败");
	m_txtTipContent = createRef<TextBlock>(0.0f, 80.0f, 0.0f, 0.0f, u8"车门未关闭，请关闭车门后重试");
	m_txtTipContent->setFontSize(28);
	m_txtTipTitle->setColor(Colors::white);
	m_txtTipContent->setColor(Colors::white);
	m_txtTipTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTipContent->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnRetry = createRef<Button>(0.0f, 140.0f, m_tip->width() / 2, 50.0f);
	m_btnRetry->setText(u8"重试");
	m_btnRetry->setFontSize(28);
	m_btnRetry->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnExit = createRef<Button>(m_tip->width() / 2, 140.0f, m_tip->width() / 2, 50.0f);
	m_btnExit->setText(u8"退出");
	m_btnExit->setFontSize(28);
	m_btnExit->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnRetry->Click += [&](const EventArgs &e) { gotoStep(Step::StopToSetOrign); m_bRetried = true; };
	m_btnExit->Click += [&](const EventArgs &e) { m_timerToNextStep.stop(); m_aniSettingOrigin.stop(); BackToMain.invoke(e); };
	m_tip->setVisibility(VisibilityE::Hidden);
	m_tip->addChild(m_txtTipTitle);
	m_tip->addChild(m_txtTipContent);
	m_tip->addChild(m_btnRetry);
	m_tip->addChild(m_btnExit);
	m_tip->addChild(createRef<Node2D>(1.0f, 130.0f, 498.0f, 1.0f, SolidColorBrush::white()));
	m_tip->addChild(createRef<Node2D>(249.0f, 130.0f, 1.0f, 68.0f, SolidColorBrush::white()));
	
	m_editBg = createRef<Node2D>(69.0f, 239.0f, 462.0f, 72.0f, SCBR(Color(242, 243, 244)));
	m_txtPathName = createRef<TextBlock>(30.0f, 0.0f, 0.0f, 0.0f, u8"温暖的家");
	m_txtPathName->setVerticalAlignment(VerticalAlignment::Center);
	m_txtPathName->setFontSize(28);
	m_btnDel = Button::createWithTextureFrameName(HPA, "btn_delete.png", 398.0f, 0.0f);
	m_btnDel->setVerticalAlignment(VerticalAlignment::Center);
	m_btnDel->Click += [&](const EventArgs &e) { m_txtPathName->setText(""); };
	m_editBg->addChild(m_txtPathName);
	m_editBg->addChild(m_btnDel);
	for (auto i = 0u; i < m_btnCans.size(); ++i)
	{
		m_btnCans[i] = Button::createWithTextureFrameName(HPA, "autopark_btn_42px_nor.png", 75.0f + 166.0f * i, 322.0f);
		m_btnCans[i]->setFontSize(20);
		m_btnCans[i]->Click += [=](const EventArgs &e) { m_txtPathName->setText(m_btnCans[i]->text()); };
	}
	m_btnCans[0]->setText(u8"温暖的家");
	m_btnCans[1]->setText(u8"奋斗的公司");
	m_btnCans[2]->setText(u8"家");
	m_txtSlotType = createRef<TextBlock>(79.0f, 400.0f, 0.f, 0.0f, u8"车位类型");
	m_txtSlotType->setFontSize(32);
	m_btnSlotSettled = createRef<Button>(69.0f, 450.0f, 216.0f, 360.0f);
	m_btnSlotSettled->setIcon(IMGBR(HPA, "pic_parkingspace1.png"), nullptr, IMGBR(HPA, "pic_parkingspace1.png"));
	m_btnSlotSettled->setFontSize(28);
	m_btnSlotSettled->setText(u8"固定车位");
	m_btnSlotSettled->setTextColorCheck(Colors::red);
	m_btnSlotSettled->setIconTextOffset({}, { 50.0f, 250.0f });
	m_btnSlotSettled->setCheck(true);
	m_btnSlotSettled->Click += [&](const EventArgs &e) { m_btnSlotSettled->setCheck(true); m_btnSlotTemp->setCheck(false); };
	m_btnSlotTemp = createRef<Button>(310.0f, 450.0f, 216.0f, 360.0f);
	m_btnSlotTemp->setIcon(IMGBR(HPA, "pic_parkingspace2.png"), nullptr, IMGBR(HPA, "pic_parkingspace2.png"));
	m_btnSlotTemp->setFontSize(28);
	m_btnSlotTemp->setText(u8"途径车位");
	m_btnSlotTemp->setTextColorCheck(Colors::red);
	m_btnSlotTemp->setIconTextOffset({}, { 50.0f, 250.0f });
	m_btnSlotTemp->Click += [&](const EventArgs &e) { m_btnSlotTemp->setCheck(true); m_btnSlotSettled->setCheck(false); };
	m_btnSavePath = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel.png", 79.0f, 815.0f);
	m_btnSavePath->setText(u8"保存");
	m_btnSavePath->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnSavePath->setFontSize(28);
	m_btnSavePath->Click += [&](const EventArgs &e) { SavePath.invoke({ m_pathType, m_btnSlotSettled->isChecked() ? ParkingSlotType::Settled : ParkingSlotType::Temp, m_txtPathName->text() }); };
	m_btnDelPath = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_warn.png", 319.0f, m_btnSavePath->y());
	m_btnDelPath->setText(u8"删除路线");
	m_btnDelPath->setTextColor(Colors::red, Color(255, 0, 0, 150));
	m_btnDelPath->setFontSize(28);
	m_btnDelPath->Click += [&](const EventArgs &e) { Delete.invoke(e); };

	m_left->addChild(m_btnBackToMain);
	m_left->addChild(m_txtTitle);
	m_left->addChild(m_icons[0]);
	m_left->addChild(m_icons[1]);
	m_left->addChild(m_icons[2]);
	m_left->addChild(m_txtTip);
	m_left->addChild(m_iconStop);
	m_left->addChild(m_iconLoading);
	m_left->addChild(m_btnSetBegOrEnd);
	m_left->addChild(m_tip);
	m_left->addChild(m_rukuImg);
	m_left->addChild(m_editBg);
	for (auto &btn : m_btnCans) m_left->addChild(btn);
	m_left->addChild(m_txtSlotType);
	m_left->addChild(m_btnSlotSettled);
	m_left->addChild(m_btnSlotTemp);
	m_left->addChild(m_btnSavePath);
	m_left->addChild(m_btnDelPath);

	m_right = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_right->setVisibility(VisibilityE::Hidden);
	m_bigImg = createRef<Image>();
	m_bigImg->setAlignmentCenter();
	m_bigImg->setStretch(Stretch::Uniform);
	m_bigImg->setTexture(createRef<Texture2D>(RES_DIR"ipu02/hpa/autopark_pic_car.png"));
	m_btnCloseBigImg = Button::createWithTextureFrameName(HPA, "btn_delete.png", 30.0f, 30.0f);
	m_btnCloseBigImg->Click += [&](const EventArgs &e) { m_right->setVisibility(VisibilityE::Hidden); };
	m_right->addChild(m_bigImg);
	m_right->addChild(m_btnCloseBigImg);

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
		if (m_curStep == Step::SettingOrign)
			gotoStep(m_bRetried ? Step::SetOrignSuccess : Step::SetOrignFailWithDoorOpen);
		else
			gotoStep(Step::SetEndSuccess);
	};

	m_timerToNextStep.setSingleShot(true);
	m_timerToNextStep.setInterval(4000);
	m_timerToNextStep.Tick += [&](const EventArgs &e) 
	{ 
		m_right->setVisibility(VisibilityE::Hidden); 
		gotoStep(m_curStep == Step::SetOrignSuccess ? Step::StopToSetEnd : Step::SavingPath);
	};

}

void RukuChukuScene::setPathType(PathType pathType)
{
	m_pathType = pathType;
}

void RukuChukuScene::gotoStep(Step step)
{
	m_curStep = step;
	switch (step)
	{
	case Step::StopToSetOrign:			m_txtTip->setText(u8"请停车后，设置当前位置为路线起点");								break;
	case Step::SettingOrign:			m_txtTip->setText(u8"正在设置为起点，请稍后......");	m_aniSettingOrigin.begin();		break;
	case Step::SetOrignFailWithDoorOpen:																						break;
	case Step::SetOrignSuccess:			m_txtTip->setText(u8"起点设置成功，点击查看大图");	m_timerToNextStep.start();			break;

	case Step::StopToSetEnd:			m_txtTip->setText(u8"请将车泊入您常用的停车位，\n停车后，点击下方按钮设置终点");		break;
	case Step::SettingEnd:				m_txtTip->setText(u8"正在设置为终点，请稍后......"); m_aniSettingOrigin.begin();		break;
	case Step::SetEndSuccess:			m_txtTip->setText(u8"终点设置成功，点击查看大图"); m_timerToNextStep.start();			break;

	case Step::SavingPath:				m_txtTip->setText(u8"路线名称");														break;
	default:																													break;
	};
	m_iconStop->setVisibility(step == Step::StopToSetOrign ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSetBegOrEnd->setVisibility(step == Step::StopToSetOrign || step == Step::StopToSetEnd ? VisibilityE::Visible : VisibilityE::Hidden);
	m_iconLoading->setVisibility(step == Step::SettingOrign || step == Step::SettingEnd ? VisibilityE::Visible : VisibilityE::Hidden);
	m_tip->setVisibility(step == Step::SetOrignFailWithDoorOpen ? VisibilityE::Visible : VisibilityE::Hidden);
	m_rukuImg->setVisibility(step == Step::SetOrignSuccess || step == Step::SetEndSuccess ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSetBegOrEnd->setText(step <= Step::SetOrignSuccess ? u8"设为起点" : u8"设为终点");
	if(m_pathType == PathType::Ruku)
		m_txtTitle->setText(step == Step::SavingPath ? u8"保存入库路线" : step <= Step::SetOrignSuccess ? u8"设置入库起点" : u8"设置入库终点");
	else
		m_txtTitle->setText(step == Step::SavingPath ? u8"保存出库路线" : step <= Step::SetOrignSuccess ? u8"设置出库起点" : u8"设置出库终点");
	m_editBg->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	for(auto btn : m_btnCans) btn->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtSlotType->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSlotSettled->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSlotTemp->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnSavePath->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	m_btnDelPath->setVisibility(step == Step::SavingPath ? VisibilityE::Visible : VisibilityE::Hidden);
	auto grayBrush = IMGBR(HPA, "pic_process_nor.png");
	auto greenBrush = IMGBR(HPA, "pic_process_sel.png");
	m_icons[0]->setBackground(step >= Step::StopToSetOrign ? greenBrush : grayBrush);
	m_icons[1]->setBackground(step >= Step::StopToSetEnd ? greenBrush : grayBrush);
	m_icons[2]->setBackground(step == Step::SavingPath ? greenBrush : grayBrush);
}

ParkingScene::ParkingScene()
{
	m_checkParent = createRef<Node2D>();
	m_carBg = Node2D::createWithTextureFrameName(HPA, "stagelight_nor.png", 0.0f, 200.0f);
	m_carBg->setHorizontalAlignment(HorizontalAlignment::Center);
	m_car = Node2D::createWithTextureFrameName(HPA, "autopark_pic_car.png", 0.0f, -180.0f);
	m_car->setAlignmentCenter();
	m_title = createRef<TextBlock>(0.0f, 540.0f, 0.0f, 0.0f);
	m_title->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStartPark = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel.png", 0.0f, 750.0f);
	m_btnStartPark->setTextColor(Colors::white, Color(255, 255, 255, 220));
	m_btnStartPark->setText(u8"开始泊车");
	m_btnStartPark->setFontSize(28);
	m_btnStartPark->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnStartPark->Click += [&](const EventArgs &e) { startPark(true); };

	for (auto i = 0u; i < m_items.size(); ++i)
	{
		m_items[i] = createRef<Item>();
		m_items[i]->setY(620.0f + 60.0f * i);
		m_checkParent->addChild(m_items[i]);
	}
	m_items[0]->setText(u8"已挂入P档");
	m_items[1]->setText(u8"车门、后尾门、引擎盖已关闭");
	m_items[2]->setText(u8"充电枪已断开");
	m_items[3]->setText(u8"安全带未系好");
	m_items[4]->setText(u8"路径匹配已完成");

	m_checkParent->addChild(m_carBg);
	m_checkParent->addChild(m_car);
	m_checkParent->addChild(m_title);
	m_checkParent->addChild(m_btnStartPark);

	m_left = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	auto btn = Button::createWithTextureFrameName(AVM, "day/topbar/icon_topbar_back.png", 49.0f, 68.0f);
	btn->Click += [&](const EventArgs &e) { stop(); startPark(false); };
	m_txtTitle = createRef<TextBlock>(0.0f, 80.0f, 0.0f, 0.0f, u8"入库 | 温暖的家");
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_txtTip = createRef<TextBlock>(69.0f, 188.0f, 462.0f, 462.0f);
	m_txtTip->setFontSize(32);
	m_txtTip->setWrap(true);
	m_tipParent = createRef<Node2D>(0.0f, 0.0f, NAN, NAN, SCBR(Color(238, 243, 250, 240)));
	m_txtTipTitle = createRef<TextBlock>(0.0f, -100.0f, 0.0f, 0.0f);
	m_txtTipTitle->setAlignmentCenter();
	m_txtTipContent = createRef<TextBlock>(0.0f, 90.0f, 462.0f, 300.0f);
	m_txtTipContent->setAlignmentCenter();
	m_txtTipContent->setFontSize(24);
	m_txtTipContent->setWrap(true);
	m_tipParent->addChild(m_txtTipTitle);
	m_tipParent->addChild(m_txtTipContent);
	m_tipParent->setVisibility(VisibilityE::Hidden);

	m_left->addChild(btn);
	m_left->addChild(m_txtTitle);
	m_left->addChild(m_txtTip);
	m_left->addChild(m_tipParent);

	addChild(m_left);
	addChild(m_checkParent);

	m_aniOpacity.setFrom(0.1f);
	m_aniOpacity.setTo(1.0f);
	m_aniOpacity.setTarget(m_carBg);
	m_aniOpacity.setTargetPropertyName("Opacity");
	m_aniOpacity.duration = TimeSpan::fromMilliseconds(200);
	m_aniOpacity.autoReverse = true;
	m_aniOpacity.repeatBehavior = RepeatBehavior::forever();
	m_aniOpacity.begin();

	m_timer.Tick += nbBindEventFunction(ParkingScene::onTick);
	m_timerParkStep.Tick += nbBindEventFunction(ParkingScene::onTick);

	startPark(false);
}

void ParkingScene::setPathType(PathType pathType)
{
	m_pathType = pathType;
	std::string s = (m_pathType == PathType::Ruku ? u8"入库" : u8"出库") + std::string(" | ") + m_name;
	m_txtTitle->setText(s);
}

void ParkingScene::setName(const std::string & name)
{
	m_name = name;
	std::string s = (m_pathType == PathType::Ruku ? u8"入库" : u8"出库") + std::string(" | ") + m_name;
	m_txtTitle->setText(s);
}

void ParkingScene::start()
{
	m_tick = 0;
	m_carBg->setBackground(IMGBR(HPA, "stagelight_nor.png"));
	m_title->setColor(Colors::black);
	m_title->setText(u8"条件检测中...");
	m_btnStartPark->setVisibility(VisibilityE::Hidden);
	for (auto i = 0u; i < m_items.size(); ++i)
	{
		m_items[i]->setVisibility(VisibilityE::Visible);
		m_items[i]->setMode(Checking);
	}

	m_timer.start(1000);
	m_aniOpacity.begin();
}

void ParkingScene::stop()
{
	m_carBg->setOpacity(1.0f);
	m_aniOpacity.stop();
	m_timer.stop();
	m_timerParkStep.stop();
}

void ParkingScene::startPark(bool b)
{
	m_left->setVisibility(b ? VisibilityE::Visible : VisibilityE::Hidden);
	m_checkParent->setVisibility(!b ? VisibilityE::Visible : VisibilityE::Hidden);
	if (b)
	{
		m_tickParkStep = 1;
		setParkStep(ParkingStep::Parking);
		m_timerParkStep.start(3000);
	}
}

void ParkingScene::setParkStep(ParkingStep step)
{
	m_txtTip->setText(step == ParkingStep::Done ? u8"记忆泊已完成，已为您挂至P档。" : u8"记忆泊车中，请稍候......");
	m_tipParent->setVisibility(step == ParkingStep::Pause || step == ParkingStep::Resume ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtTipTitle->setText(step == ParkingStep::Pause ? u8"泊车功能暂停" : u8"泊车功能已恢复");
	m_txtTipContent->setText(step == ParkingStep::Pause ? u8"前方有障碍物，请在两分钟内移除障碍物后                              ，继续泊车" : u8"              障碍物已移除，泊车流程继续");
}

void ParkingScene::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		if (m_tick < (int)m_items.size())
		{
			m_items[m_tick]->setMode(Ready);
		}
		else
		{
			stop();
			m_carBg->setBackground(IMGBR(HPA, "stagelight_right.png"));
			m_title->setColor(Colors::green);
			m_title->setText(u8"条件检测完成");
			m_btnStartPark->setVisibility(VisibilityE::Visible);
			for (auto i = 0u; i < m_items.size(); ++i)
			{
				m_items[i]->setVisibility(VisibilityE::Hidden);
			}
		}
		++m_tick;
	}
	else if(e.sender == &m_timerParkStep)
	{
		static int steps = 1;
		setParkStep((ParkingStep)m_tickParkStep);
		if (steps == 1 && m_tickParkStep == (int)ParkingStep::Resume)
		{
			m_tickParkStep = (int)ParkingStep::Parking;
			steps = 3;
		}
		else
		{
			m_tickParkStep += steps;
		}
		if (m_tickParkStep > (int)ParkingStep::Done)
		{
			steps = 1;
			stop();
		}
	}
}

ParkingScene::Item::Item()
{
	setRect({ 720.0f, 0.0f, 600.0f, 50.0f});
	m_icon = createRef<Node2D>(0.0f, 0.0f, 40.0f, 40.0f);
	m_icon->setVerticalAlignment(VerticalAlignment::Center);
	m_icon->setTransform(createRef<RotateTransform2D>(0.0f, 20.0f, 20.0f));
	m_txt = createRef<TextBlock>(50.0f, 10.0f, 0.0f, 0.0f);
	//m_txt->setFontSize(28);
	addChild(m_icon);
	addChild(m_txt);

	m_aniChecking.setFrom(0.0);
	m_aniChecking.setTo(360.0f);
	m_aniChecking.setTarget(m_icon->getTransform());
	m_aniChecking.setTargetPropertyName("Angle");
	m_aniChecking.duration = TimeSpan::fromSeconds(1);
	m_aniChecking.repeatBehavior = RepeatBehavior::forever();

	setMode(ItemMode::Checking);
}

void ParkingScene::Item::setText(const std::string & txt)
{
	m_txt->setText(txt);
}

void ParkingScene::Item::setMode(ItemMode mode)
{
	switch (mode)
	{
	case ParkingScene::Checking:	m_icon->setBackground(IMGBR(HPA, "icon_loading.png")); m_txt->setColor(Colors::black);	break;
	case ParkingScene::Warning:		m_icon->setBackground(IMGBR(HPA, "icon_error.png")); m_txt->setColor(Colors::red);		break;
	case ParkingScene::Ready:		m_icon->setBackground(IMGBR(HPA, "icon_pass.png")); m_txt->setColor(Color(3, 156, 26));	break;
	default:																												break;
	}
	if (mode == Checking)
	{
		m_aniChecking.begin();
	}
	else
	{
		m_aniChecking.stop();
		as<RotateTransform2D>(m_icon->getTransform())->setAngle(0.0f);
	}
}

EditCardScene::EditCardScene()
{
	m_left = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f, SolidColorBrush::white());
	m_btnBackToMain = Button::createWithTextureFrameName(AVM, "day/topbar/icon_topbar_back.png", 49.0f, 68.0f);
	m_btnBackToMain->Click += [&](const EventArgs &e) { BackToMain.invoke(e); };
	m_txtTitle = createRef<TextBlock>(0.0f, 80.0f, 0.0f, 0.0f, u8"温暖的家");
	m_txtTitle->setHorizontalAlignment(HorizontalAlignment::Center);
	m_btnEdit = Button::createWithTextureFrameName(HPA, "icon_edit_nor.png", 400.0f, 62.0f);
	m_btnEdit->Click += [&](const EventArgs &e) {};
	m_txtPsType = createRef<TextBlock>(0.0f, -120.0f, 0.0f, 0.0f, u8"固定车位");
	m_txtPsType->setAlignmentCenter();
	m_txtPsType->setFontSize(32);
	auto icon = Node2D::createWithTextureFrameName(HPA, "icon_home.png", 0.0f, 0.0f);
	icon->setAlignmentCenter();
	m_btnSave = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_sel.png", 49.0f, 768.0f);
	m_btnSave->setText(u8"保存");
	m_btnSave->setFontSize(28);
	m_btnSave->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_btnSave->Click += [&](const EventArgs &e) { SaveCard.invoke(e); };
	m_btnDel = Button::createWithTextureFrameName(HPA, "autopark_btn_62px_warn.png", 349.0f, 768.0f);
	m_btnDel->setText(u8"删除路线");
	m_btnDel->setTextColor(Colors::red, Color(255, 0, 0, 150));
	m_btnDel->setFontSize(28);
	m_btnDel->Click += [&](const EventArgs &e) { DeleteCard.invoke(m_index); };

	m_left->addChild(m_btnBackToMain);
	m_left->addChild(m_txtTitle);
	m_left->addChild(m_btnEdit);
	m_left->addChild(m_txtPsType);
	m_left->addChild(icon);
	m_left->addChild(m_btnSave);
	m_left->addChild(m_btnDel);

	addChild(m_left);
}

void EditCardScene::setIndex(const Index &index)
{
	m_index = index;
}

void EditCardScene::setName(const std::string & name)
{
	m_txtTitle->setText(name);
}

void EditCardScene::setParkingSlotType(ParkingSlotType psType)
{
	m_txtPsType->setText(psType == ParkingSlotType::Settled ? u8"固定车位" : u8"途径车位");
}

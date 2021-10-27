#include "catch2/catch.hpp"
#include "newbrush/Application.h"
#include "newbrush/Controls.h"
#include "newbrush/UserControl.h"
#include "newbrush/Components.h"
#include "newbrush/Scene.h"
#include "newbrush/Log.h"

using namespace nb;

TEST_CASE("Node2D", "[Node2D]")
{
	Application app;
	Window w;

	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(720.0f);

	TextureLibrary::addTextureAtlas("indicator", "../resource/cx62b/indicator.png", "../resource/cx62b/indicator.txt");
	TextureLibrary::addTextureAtlas("menu", "../resource/cx62b/menu.png", "../resource/cx62b/menu.txt");
	BrushLibrary::addImageBrush("bgBrush", "../resource/cx62b/bg.png");

	auto m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_root->setAlignmentCenter();
	//m_root->setBackground(BrushLibrary::get("bgBrush"));
	//auto m_LED_EleSteerLock = Node2D::createWithTextureFrameName("indicator", "LED_EngineTheft-Red.png", true, 135, 23);
	auto m_LED_OilPressure = Node2D::createWithTextureFrameName("indicator", "LED_RightTurn.png", true, 0.0f, 0.0f);
	auto node = createRef<Node2D>(0.0f, 0.0f, 70.0f, 70.0f);
	node->setBackground(SolidColorBrush::red());

	//auto m_TopMenu = Node2D::createWithTextureFrameName("menu", "pop_bg.png", true);
	//m_TopMenu->setHorizontalAlignment(HorizontalAlignment::Center);
	//m_TopMenu->addChild(Node2D::createWithTextureFrameName("menu", "ic_Answer.png", true, 0.0f, 43.9f));
	//m_root->addChild(m_LED_EleSteerLock);
	m_root->addChild(node);
	//m_root->addChild(m_LED_OilPressure);
	//m_root->addChild(m_TopMenu);
	w.root = m_root;

	app.run();
}

TEST_CASE("Image", "[Image]")
{
	Application app;

	Window w(1920.0f, 1080.0f);

	auto root = createRef<Node2D>(0.0f,0.0f,800.0f,600.0f);
	root->setAlignmentCenter();
	root->setBackground(SolidColorBrush::wheat());

	auto img = createRef<Image>();
	img->setAlignmentCenter();
	img->setStretch(Stretch::Uniform);
	img->setTexture(createRef<Texture2D>(RES_DIR"effects/hollow_knight.jpg"));

	root->addChild(img);
	w.root = root;

	app.run();
}

TEST_CASE("Rectangle", "[Rectangle]")
{
	Application app;

	Window w(800.0f, 600.0f);

	auto node = createRef<Node2D>();
	node->setX(0.0f);
	//node->setWidth(100);
	//node->setHeight(100);
	node->setBackground(createRef<SolidColorBrush>(Colors::blue));
	node->setHorizontalAlignment(HorizontalAlignment::Left);
	
	auto node1 = createRef<Image>();
//	node1->setWidth(100);
//	node1->setHeight(100);
	auto texture = createRef<Texture2D>();
//	texture->update(0, createRef<Bitmap>("f:/1.jpg"));
//	node1->setBackground(createRef<ImageBrush>(texture));
	node1->setTexture(texture);
//	node1->setHorizontalAlignment(HorizontalAlignment::Left);

	auto parent = createRef<Node2D>();

	parent->addChild(node);
	parent->addChild(node1);

	w.root = parent;

	app.run();
}

TEST_CASE("Event", "[Event]")
{
	Application app;

	Window w(800.0f, 600.0f);

	auto btn0 = createRef<Button>(0.0f, 0.0f, 100.0f, 50.0f);
	btn0->setBkgndNormal(SolidColorBrush::blue());
	btn0->setBkgndPress(SolidColorBrush::yellow());
	btn0->setBkgndCheck(SolidColorBrush::red());
	btn0->Click += [&](const EventArgs &e) { Log::info("click"); btn0->setCheck(!btn0->isChecked()); };
	auto btn1 = createRef<Button>(0.0f, 0.0f, 50.0f, 100.0f);
	btn1->setBkgndNormal(SolidColorBrush::green());
	btn1->setBkgndPress(SolidColorBrush::antiqueWhite());

	auto root = createRef<Node2D>();
	root->addChild(btn0);
	//root->addChild(btn1);
	w.root = root;

	app.run();
}

TEST_CASE("Button", "[Button]")
{
	Application app;

	Window w(800.0f, 600.0f);
	w.root = createRef<Node2D>();
	w.root->setBackground(SolidColorBrush::blue());
	TextureLibrary::addTextureAtlas("modelDIY", "../resource/modelDIY/modelDIY.png", "../resource/modelDIY/modelDIY.txt");
	TextureLibrary::addTextureAtlas("memory", RES_DIR"ipu02/memory.png", RES_DIR"ipu02/memory.txt");
	auto font = createRef<Font>(RES_DIR"fonts/siyuanheiti.otf", 28);
	
	auto p = createRef<Node2D>();

	auto btn0 = Button::createWithTextureFrameName("memory", "autopark_btn_56px_nor.png", true, 0.0f, 0.0f);
	//btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "autopark_btn_56px_nor.png"));
	btn0->setIcon(createRef<ImageBrush>("memory", "music_search_icon_search.png"));
	btn0->setText(u8"教程");
	btn0->setFont(font);
	btn0->setTextColor(Colors::black, Colors::green, Colors::red);
	btn0->setIconOffset({36.0f, 5.0f});
	btn0->setTextOffset({82.0f, 14.0f});
	btn0->Click += [&](const EventArgs &e) { Log::info("click"); btn0->setCheck(!btn0->isChecked()); };

	p->addChild(btn0);
	//p->setVisibility(VisibilityE::Hidden);

	w.root->addChild(p);

	//w.root->setVisibility(VisibilityE::Hidden);

	app.run();
}

TEST_CASE("ToggleButton", "[ToggleButton]")
{
	Application app;
	Window w(800.0f, 600.0f);
	w.root = createRef<Node2D>();
	w.root->setBackground(SolidColorBrush::white());

	TextureLibrary::addTextureAtlas("manual_day", RES_DIR"ipu02/manual_day.png", RES_DIR"ipu02/manual_day.txt");

	auto toggle = createRef<ToggleButton>(0.0f, 0.0f, 84.0f, 46.0f);
	auto bkgNormal = createRef<ImageBrush>("manual_day", "autopark_btn_button_nor.png");
	auto bkgCheck = createRef<ImageBrush>("manual_day", "autopark_btn_button_sel.png");
	auto iconNormal = createRef<ImageBrush>("manual_day", "autopark_btn_button_dot.png");
	toggle->setCheck(true);
	toggle->setBkgndNormal(bkgNormal);
	toggle->setBkgndPress(bkgNormal);
	toggle->setBkgndCheck(bkgCheck);
	toggle->setIcon(iconNormal);
	toggle->setIconOffset({ -10.0f, -5.0f });
	toggle->CheckChanged += [&](const EventArgs &e)
	{
		Log::info("on toggle changed={}", toggle->isChecked());
	};
	w.root->addChild(toggle);

	app.run();
}

TEST_CASE("TextBlock", "[TextBlock]")
{
	Application app;
	Window w;

	auto text = createRef<TextBlock>(0.0f, 0.0f, 200.0f, 200.0f, u8"abcd\n\nefghijklmnopqrstuvwxyz");
	text->setAlignmentCenter();
	text->setWrap(true);
	text->setBackground(SolidColorBrush::red());


	auto text1 = createRef<TextBlock>(u8"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	auto font = createRef<Font>(RES_DIR"fonts/siyuanheiti.otf", 16);
	//text1->setFont(font);
	text1->setFontSize(48);

	auto root = createRef<Node2D>();
	//root->setName("Root");
	//BrushLibrary::addImageBrush("bgBrush", "../resource/cxd706/img_text_colour.png");
	//root->setBackground(BrushLibrary::get("bgBrush"));
	root->setBackground(SolidColorBrush::blue());

	root->addChild(text);
	root->addChild(text1);

	w.root = root;

	app.run();
}

TEST_CASE("Brush", "[Brush]")
{
	Application app;

	Window w;

	auto p = createRef<Node2D>(100.0f, 100.0f, 1000.0f, 600.0f);
	p->setBackground(SolidColorBrush::antiqueWhite());

	auto node = createRef<nb::Polygon>();
	node->setPoints(std::vector<glm::vec2>{ {100.0f, 100.0f}, {800.0f, 100.0f}, { 800.0f, 400.0f }, { 100.0f, 400.0f } });
	node->setBackground(SolidColorBrush::red());

	auto linearGradient = createRef<LinearGradientBrush>(std::vector<GradientStop>{ {0.0f, Colors::red}, { 0.7f, Colors::green }, { 1.0f, Colors::blue } });
	linearGradient->horizontal = false;
	node->setBackground(linearGradient);

	p->addChild(node);

	w.root = p;
	
	app.run();
}


TEST_CASE("Cube", "[Cube]")
{
	Application app;

	Window w;

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::green());
	root->setScene(createRef<Scene>());

	auto cube = createRef<Cube>(glm::vec3(0.0f), 1.0f, 2.0f, 3.0f);
	cube->setTransform(createRef<Transform>());
	cube->setMaterial(createRef<FlatMaterial>(Colors::red));

	root->getScene()->addChild(cube);

	w.root = root;

	Point m_pressedPoint;
	bool m_pressed{ false };
	root->Touch += [&](const TouchEventArgs &e)
	{	
		Point p = { e.x, e.y };
		if (e.action == TouchAction::Down)
		{
			m_pressed = true;
			m_pressedPoint = p;
		}
		else if (e.action == TouchAction::Move)
		{
			if (!m_pressed) return;

			Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
			m_pressedPoint = p;

			auto rotate = cube->getTransform()->getRotate();
			rotate.y = glm::radians(glm::degrees(rotate.y) + ptOffset.x);
			rotate.x = glm::radians(glm::degrees(rotate.x) - ptOffset.y);
			cube->getTransform()->setRotate(rotate);
		}
		else if (e.action == TouchAction::Up)
		{
			m_pressed = false;
		}
	};
	root->Key += [&](const KeyEventArgs &e)
	{
		if (e.action == KeyAction::Down)
		{
			if (e.key == KeyCode::_1)		cube->setMaterial(createRef<FlatMaterial>(Colors::red));
			else if (e.key == KeyCode::_2)	cube->setMaterial(createRef<FlatMaterial>(Colors::blue));
			else if (e.key == KeyCode::_3)
			{
				auto material = createRef<TextureMaterial>();
				material->texFrame.texture = createRef<Texture2D>(RES_DIR"effects/hollow_knight.jpg");
				cube->setMaterial(material);
			}
			else if (e.key == KeyCode::_4)
			{
				auto material = createRef<PhongMaterial>();
				cube->setMaterial(material);
			}
		}
	};

	app.run();
}


TEST_CASE("SkyBox", "[SkyBox]")
{
	Application app;

	Window w;

	auto skybox = createRef<SkyBox>();
	skybox->setTransform(createRef<Transform>());
	auto material = createRef<SkyBoxMaterial>();
	auto cubemap = createRef<TextureCubemap>();
	std::string dir = RES_DIR"browser/skybox1/";
	cubemap->update(dir + "top.jpg", dir + "bottom.jpg", dir + "left.jpg", dir + "right.jpg", dir + "front.jpg", dir + "back.jpg");
	material->cubeMapping = cubemap;
	skybox->setMaterial(material);

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::green());
	root->setScene(createRef<Scene>());

	auto cube = createRef<Cube>(glm::vec3(0.0f), 2.0f);
	cube->setTransform(createRef<Transform>());
	//cube->setMaterial(createRef<FlatMaterial>(Colors::red));
	auto reflectmaterial = createRef<ReflectMaterial>();
	reflectmaterial->cubeMapping = cubemap;
	cube->setMaterial(reflectmaterial);

	root->getScene()->addChild(skybox);
	root->getScene()->addChild(cube);
	w.root = root;

	Point m_pressedPoint;
	bool m_pressed{ false };
	root->Touch += [&](const TouchEventArgs &e)
	{
		Point p = { e.x, e.y };
		if (e.action == TouchAction::Down)
		{
			m_pressed = true;
			m_pressedPoint = p;
		}
		else if (e.action == TouchAction::Move)
		{
			if (!m_pressed) return;

			Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
			m_pressedPoint = p;

			auto rotate = cube->getTransform()->getRotate();
			rotate.y = glm::radians(glm::degrees(rotate.y) + ptOffset.x);
			rotate.x = glm::radians(glm::degrees(rotate.x) - ptOffset.y);
			cube->getTransform()->setRotate(rotate);

			/*auto rotate = skybox->getTransform()->getRotate();
			rotate.y = glm::radians(glm::degrees(rotate.y) + ptOffset.x);
			rotate.x = glm::radians(glm::degrees(rotate.x) - ptOffset.y);
			skybox->getTransform()->setRotate(rotate);*/
		}
		else if (e.action == TouchAction::Up)
		{
			m_pressed = false;
		}
	};

	app.run();
}

TEST_CASE("Theme", "[Theme]")
{
	Application app;
	Window w(100.0f, 100.0f);

	auto btn = createRef<Button>();
	btn->setBkgndNormal(SolidColorBrush::blue());
	btn->setBkgndPress(SolidColorBrush::red());
	btn->Click += [](const EventArgs &e) {static int i = 0; ThemeManager::setTheme(i++); };

	ThemeManager::ThemeChanged() += [](const int &them)
	{
		Log::info("Theme changed to {}", them);
	};

	w.root = btn;
	app.run();
}

TEST_CASE("NinePatchImage", "[NinePatchImage]")
{
	Application app;
	Window w(800.0f, 600.0f);
	w.root = createRef<Node2D>();
	w.root->setBackground(SolidColorBrush::white());
	w.root->setAlignmentCenter();

	TextureLibrary::addTextureAtlas("avm", RES_DIR"ipu02/AVM.png", RES_DIR"ipu02/AVM.txt");

	auto nine = createRef<NinePatchImage>(100.0f, 100.0f, 400.0f, 86.0f);
	nine->setImages(IMGBR("avm", "nine00.png"), IMGBR("avm", "nine22.png"), IMGBR("avm", "nine33.png"), IMGBR("avm", "nine11.png"), IMGBR("avm", "nine44.png"));
	w.root->addChild(nine);

	app.run();
}

TEST_CASE("MovieImage", "[MovieImage]")
{
	Application app;
	Window w;

	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(720.0f);

	auto m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_root->setAlignmentCenter();
	m_root->setBackground(SolidColorBrush::white());
	auto node = createRef<MovieImage>(0.0f, 0.0f, 1920.0f, 720.0f);
	node->setHorizontalAlignment(HorizontalAlignment::Center);
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00000.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00001.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00002.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00003.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00004.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00005.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00006.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00007.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00008.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00009.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00010.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00011.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00012.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00013.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00014.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00015.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00016.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00017.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00018.png"));
	node->addFrame(createRef<Texture2D>(RES_DIR"cxd706/Sequence_frame/light_00019.png"));
	node->setInterval(20);
	//node->setReverse(true);
	//node->stopMovieInFrame(6);
	m_root->addChild(node);
	node->startMovie();


	w.root = m_root;

	app.run();
}

TEST_CASE("SlideButton", "[SlideButton]")
{
	Application app;
	Window w;

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::red());

	TextureLibrary::addTextureAtlas("ap", RES_DIR"ipu02/ap_day.png", RES_DIR"ipu02/ap_day.txt");
	auto slideBtn = createRef<SlideButton>(660.0f, 19.0f, 490.0f, 62.0f);
	slideBtn->setBackground(IMGBR("ap", "btn_62px_nor.9.png"));
	slideBtn->setBtn(IMGBR("ap", "btn_62px_sel.9.png"));
	slideBtn->addItem(u8"自动泊车");
	slideBtn->addItem(u8"遥控泊车");
	slideBtn->addItem(u8"自选车位");
	slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
	slideBtn->setCurSel(0);
	slideBtn->enableItem(1, false);

	root->addChild(slideBtn);
	w.root = root;
	app.run();
}

TEST_CASE("Clip", "[Clip]")
{
	Application app;
	Window w;

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::white());

	auto parent = createRef<Node2D>(50.0f, 50.0f, 400.0f, 400.0f);
	parent->setBackground(SolidColorBrush::red());

	auto rc = createRef<Node2D>(100.0f, 100.0f, 500.0f, 500.0f);
	rc->setBackground(SolidColorBrush::blue());
	rc->setClipRect(parent->rect());

	auto img = createRef<Node2D>(-100.0f, -100.0f, 200.0f, 200.0f);
	img->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"effects/hollow_knight.jpg")));
	img->setClipRect(parent->rect());

	w.Key += [&](const KeyEventArgs &e)
	{
		if (e.action == KeyAction::Down)
		{
			if (e.key == KeyCode::Space)
			{
				rc->setClipRect(rc->getClipRect().x() < 0.0f ? parent->rect() : Rect(-1.0f, -1.0f, -1.0f, -1.0f));
				img->setClipRect(img->getClipRect().x() < 0.0f ? parent->rect() : Rect(-1.0f, -1.0f, -1.0f, -1.0f));
			}
		}
	};

	parent->addChild(rc);
	parent->addChild(img);

	root->addChild(parent);

	w.root = root;
	app.run();
}

TEST_CASE("ActualOpacity", "[ActualOpacity]")
{
	Application app;
	Window w;

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::white());

	auto parent = createRef<Node2D>(50.0f, 50.0f, 400.0f, 400.0f);
	parent->setBackground(SolidColorBrush::red());
	parent->setOpacity(0.5);

	auto rc = createRef<Node2D>(100.0f, 100.0f, 500.0f, 500.0f);
	rc->setBackground(SolidColorBrush::blue());
	rc->setOpacity(0.1f);

	parent->addChild(rc);
	root->addChild(parent);
	w.root = root;
	app.run();
}

TEST_CASE("DotListCtrl", "[DotListCtrl]")
{
	Application app;
	Window w;

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::white());

	auto dotList = createRef<DotListCtrl>(0.0f, 0.0f, 140.0f, 50.0f);
	dotList->setBackground(SolidColorBrush::red());
	dotList->setAlignmentCenter();
	dotList->setDotCount(5);
	dotList->setDotImage(createRef<ImageBrush>(RES_DIR"unitests/dot_n.png"), createRef<ImageBrush>(RES_DIR"unitests/dot_s.png"));
	dotList->setCurSel(0);

	w.Key += [&](const KeyEventArgs &e)
	{
		if (e.action == KeyAction::Down)
		{
			auto nCurSel = dotList->getCurSel();
			switch (e.key)
			{
			case KeyCode::Left: --nCurSel;	break;
			case KeyCode::Right: ++nCurSel;	break;
			default:						break;
			}
			nCurSel = nb::clamp(nCurSel, 0, dotList->dotCount() -1);
			dotList->setCurSel(nCurSel);
		}
	};

	root->addChild(dotList);
	w.root = root;
	app.run();
}

TEST_CASE("PageCtrl", "[PageCtrl]")
{
	Application app;
	Window w(1280.0f, 720.0f);

	auto root = createRef<Node2D>();
	root->setBackground(SolidColorBrush::white());

	auto pageCtrl = createRef<PageCtrl>(0.0f, 0.0f, 400.0f, 400.0f);
	pageCtrl->setAlignmentCenter();
	pageCtrl->setBackground(SolidColorBrush::black());

	auto page0 = createRef<Node2D>(0.0f, 0.0f, pageCtrl->width(), pageCtrl->height() - 100.0f, SolidColorBrush::red());
	pageCtrl->CurPageChanged += [](const int &e) { Log::info("cur page={}", e); };
	pageCtrl->addPage(page0);
	auto page1 = createRef<Node2D>(0.0f, 0.0f, pageCtrl->width(), pageCtrl->height() - 100.0f, SolidColorBrush::green());
	pageCtrl->addPage(page1);
	auto page2 = createRef<Node2D>(0.0f, 0.0f, pageCtrl->width(), pageCtrl->height() - 100.0f, SolidColorBrush::blue());
	pageCtrl->addPage(page2);
	auto page3 = createRef<Node2D>(0.0f, 0.0f, pageCtrl->width(), pageCtrl->height() - 100.0f, SolidColorBrush::gray());
	pageCtrl->addPage(page3);
	auto page4 = createRef<Node2D>(0.0f, 0.0f, pageCtrl->width(), pageCtrl->height() - 100.0f, SolidColorBrush::yellow());
	pageCtrl->addPage(page4);
	auto dotListCtrl = createRef<DotListCtrl>(0.0f, 606.0f, 140.0f, 50.0f);
	dotListCtrl->setHorizontalAlignment(HorizontalAlignment::Center);
	dotListCtrl->setDotCount(5);
	dotListCtrl->setDotImage(createRef<ImageBrush>(RES_DIR"ipu02/pap/dot_n.png"), createRef<ImageBrush>(RES_DIR"ipu02/pap/dot_s.png"));
	pageCtrl->bindDotListCtrl(dotListCtrl);

	root->addChild(pageCtrl);
	root->addChild(dotListCtrl);

	w.root = root;
	app.run();
}

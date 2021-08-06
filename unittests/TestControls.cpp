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
	//m_TopMenu->setHorizontalAlignment(HorizontalAlignmentE::Center);
	//m_TopMenu->addChild(Node2D::createWithTextureFrameName("menu", "ic_Answer.png", true, 0.0f, 43.9f));
	//m_root->addChild(m_LED_EleSteerLock);
	m_root->addChild(node);
	//m_root->addChild(m_LED_OilPressure);
	//m_root->addChild(m_TopMenu);
	w.root = m_root;

	app.run();
}

TEST_CASE("TestRectangle", "[TestRectangle]")
{
	Application app;

	Window w(800, 600);

	auto node = createRef<Node2D>();
	node->setX(0.0f);
	//node->setWidth(100);
	//node->setHeight(100);
	node->setBackground(createRef<SolidColorBrush>(Colors::blue));
	node->setHorizontalAlignment(HorizontalAlignmentE::Left);
	
	auto node1 = createRef<Image>();
//	node1->setWidth(100);
//	node1->setHeight(100);
	auto texture = createRef<Texture2D>();
//	texture->update(0, createRef<Bitmap>("f:/1.jpg"));
//	node1->setBackground(createRef<ImageBrush>(texture));
	node1->setTexture(texture);
//	node1->setHorizontalAlignment(HorizontalAlignmentE::Left);

	auto parent = createRef<Node2D>();

	parent->addChild(node);
	parent->addChild(node1);

	w.root = parent;

	app.run();
}

TEST_CASE("Button", "[Button]")
{
	Application app;

	Window w(800, 600);
	w.root = createRef<Node2D>();
	w.root->setBackground(SolidColorBrush::blue());
	TextureLibrary::addTextureAtlas("modelDIY", "../resource/modelDIY/modelDIY.png", "../resource/modelDIY/modelDIY.txt");
	
	auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_face_01.png", true, 0.0f, 0.0f);
	btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_face_01_s.png"));
	btn0->Click += [&](const EventArgs &e) { Log::info("click"); btn0->setCheck(!btn0->isChecked()); };

	w.root->addChild(btn0);

	//w.root->setVisibility(VisibilityE::Hidden);

	app.run();
}

TEST_CASE("ToggleButton", "[ToggleButton]")
{
	Application app;
	Window w(800, 600);
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

	auto text = createRef<TextBlock>("OpenGL");
	text->setRect({ 0, 0, 100, 30 });
	text->setAlignmentCenter();

	auto root = createRef<Node2D>();
	BrushLibrary::addImageBrush("bgBrush", "../resource/cxd706/img_text_colour.png");
	root->setBackground(BrushLibrary::get("bgBrush"));
	//root->setBackground(SolidColorBrush::red());

	root->addChild(text);

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
		if (e.action == TouchActionE::down)
		{
			m_pressed = true;
			m_pressedPoint = p;
		}
		else if (e.action == TouchActionE::move)
		{
			if (!m_pressed) return;

			Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
			m_pressedPoint = p;

			auto rotate = cube->getTransform()->getRotate();
			rotate.y = glm::radians(glm::degrees(rotate.y) + ptOffset.x);
			rotate.x = glm::radians(glm::degrees(rotate.x) - ptOffset.y);
			cube->getTransform()->setRotate(rotate);
		}
		else if (e.action == TouchActionE::up)
		{
			m_pressed = false;
		}
	};
	root->Key += [&](const KeyEventArgs &e)
	{
		if (e.action == KeyAction::down)
		{
			if (e.key == KeyCode::_1)		cube->setMaterial(createRef<FlatMaterial>(Colors::red));
			else if (e.key == KeyCode::_2)	cube->setMaterial(createRef<FlatMaterial>(Colors::blue));
			else if (e.key == KeyCode::_3)
			{
				auto material = createRef<TextureMaterial>();
				material->texture = createRef<Texture2D>(RES_DIR"effects/hollow_knight.jpg");
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
	cube->setMaterial(createRef<FlatMaterial>(Colors::red));

	root->getScene()->addChild(skybox);
	root->getScene()->addChild(cube);
	w.root = root;

	Point m_pressedPoint;
	bool m_pressed{ false };
	root->Touch += [&](const TouchEventArgs &e)
	{
		Point p = { e.x, e.y };
		if (e.action == TouchActionE::down)
		{
			m_pressed = true;
			m_pressedPoint = p;
		}
		else if (e.action == TouchActionE::move)
		{
			if (!m_pressed) return;

			Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
			m_pressedPoint = p;

			auto rotate = cube->getTransform()->getRotate();
			rotate.y = glm::radians(glm::degrees(rotate.y) + ptOffset.x);
			rotate.x = glm::radians(glm::degrees(rotate.x) - ptOffset.y);
			cube->getTransform()->setRotate(rotate);
		}
		else if (e.action == TouchActionE::up)
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
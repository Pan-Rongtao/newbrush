#include "catch2/catch.hpp"
#include "newbrush/Application.h"
#include "newbrush/Controls.h"
#include "newbrush/UserControl.h"
#include "newbrush/Components.h"

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

	app.run(0, nullptr);
}

TEST_CASE("Button", "[Button]")
{
	Application app;

	Window w(800, 600);
	w.root = createRef<Node2D>();
	w.root->setBackground(SolidColorBrush::blue());
	TextureLibrary::addTextureAtlas("modelDIY", "../resource/modelDIY/modelDIY.png", "../resource/modelDIY/modelDIY.txt");

	auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_face_01.png", true, 0.0f, 0.0f);
	btn0->setBkgndPress(createRef<ImageBrush>("modelDIY", "parts_face_01_s.png"));

	w.root->addChild(btn0);

	app.run(0, 0);
}

TEST_CASE("TextBlock", "[TextBlock]")
{
	Application app;
	Window w;

	auto text = createRef<TextBlock>("OpenGL");

	auto root = createRef<Node2D>();
	BrushLibrary::addImageBrush("bgBrush", "../resource/cxd706/img_text_colour.png");
	root->setBackground(BrushLibrary::get("bgBrush"));
	//root->setBackground(SolidColorBrush::red());

	root->addChild(text);

	w.root = root;

	app.run(0, nullptr);
}

TEST_CASE("Brush", "[Brush]")
{
	Application app;

	Window w;

	auto p = createRef<Node2D>(100.0f, 100.0f, 1000.0f, 600.0f);
	p->setBackground(SolidColorBrush::antiqueWhite());

	auto node = createRef<Polygon>();
	node->setPoints(std::vector<glm::vec2>{ {100.0f, 100.0f}, {800.0f, 100.0f}, { 800.0f, 400.0f }, { 100.0f, 400.0f } });
	node->setBackground(SolidColorBrush::red());

	auto linearGradient = createRef<LinearGradientBrush>(std::vector<GradientStop>{ {0.0f, Colors::red}, { 0.7f, Colors::green }, { 1.0f, Colors::blue } });
	linearGradient->horizontal = false;
	node->setBackground(linearGradient);

	p->addChild(node);

	w.root = p;
	
	app.run();
}

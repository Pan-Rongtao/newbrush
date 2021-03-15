#include "catch2/catch.hpp"
#include "newbrush/Application.h"
#include "newbrush/Material.h"
#include "newbrush/Mesh.h"
#include "newbrush/Node2D.h"
#include "newbrush/Controls.h"
#include "newbrush/UserControl.h"

using namespace nb;

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

TEST_CASE("TestButton", "[TestButton]")
{
	Application app;

	Window w(800, 600);

	auto btn = createRef<Button>();
	btn->setBkgndNormal(createRef<SolidColorBrush>(Colors::red));
	btn->setBkgndPress(createRef<SolidColorBrush>(Colors::blue));

	w.root = btn;

	app.run(0, 0);
}
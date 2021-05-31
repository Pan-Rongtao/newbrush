#include "MainView.h"
#include "Effects.h"

using namespace nb;

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(1280.0f);
	Application::get()->mainWindow()->setHeight(1000.0f);
	Application::get()->mainWindow()->setTitle("Effects Power By NewBrush");

	auto tex0 = TextureLibrary::addTexture2D("gaussianBlur", RES_DIR"effects/hollow_knight.jpg");

	BrushLibrary::add("gaussianBlurBrush", createRef<EffectBrush>(createRef<GaussianBlurMateial>(tex0, 3.0f)));
	BrushLibrary::add("VortexBrush", createRef<EffectBrush>(createRef<VortexMaterial>(tex0, 0.5f, 100.0f)));
	BrushLibrary::add("FlameBrush", createRef<EffectBrush>(createRef<FlameMaterial>(tex0)));

	m_root = createRef<Node2D>();

	auto node0 = createRef<Node2D>();
	node0->setAlignmentCenter();
	node0->setSize(Size(tex0->width(), tex0->height()));
	node0->setBackground(BrushLibrary::get("gaussianBlurBrush"));

	auto node1 = createRef<Node2D>();
	node1->setAlignmentCenter();
	node1->setSize(Size(tex0->width(), tex0->height()));
	node1->setBackground(BrushLibrary::get("VortexBrush"));

	auto node2 = createRef<Node2D>();
	node2->setAlignmentCenter();
	//node2->setSize(Size(TextureLibrary::getTexture2D("gaussianBlur")->getWidth(), TextureLibrary::getTexture2D("gaussianBlur")->getHeight()));
	node2->setBackground(BrushLibrary::get("FlameBrush"));

	m_root = node1;
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();
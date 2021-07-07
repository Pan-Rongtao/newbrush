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

	m_root = createRef<Node2D>(0.0f, 0.0f, tex0->width(), tex0->height());
	m_root->setAlignmentCenter();
	m_root->setBackground(BrushLibrary::get("gaussianBlurBrush"));

	m_root->Key += nbBindEventFunction(MainView::onKey);
	m_root->Touch += nbBindEventFunction(MainView::onTouch);
}

void MainView::onKey(const KeyEventArgs &e)
{
	switch (e.key)
	{
	case KeyCode::_1: 	m_root->setBackground(BrushLibrary::get("gaussianBlurBrush"));  break;
	case KeyCode::_2: 	m_root->setBackground(BrushLibrary::get("VortexBrush"));		break;
	case KeyCode::_3: 	m_root->setBackground(BrushLibrary::get("FlameBrush"));			break;
	default:																			break;
	}
}

void MainView::onTouch(const TouchEventArgs & e)
{
	if (e.action != TouchActionE::down)
		return;

	static unsigned i = 0;
	auto index = i % 3;
	switch (index)
	{
	case 0: 	m_root->setBackground(BrushLibrary::get("gaussianBlurBrush"));  break;
	case 1: 	m_root->setBackground(BrushLibrary::get("VortexBrush"));		break;
	case 2: 	m_root->setBackground(BrushLibrary::get("FlameBrush"));			break;
	default:																	break;
	}
	++i;
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();
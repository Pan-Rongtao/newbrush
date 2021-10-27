#include "MainView.h"

static MainView *g_instance = nullptr;
void MainView::init()
{
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(720.0f);
	Application::get()->mainWindow()->setTitle("Model DIY Power By NewBrush");

	TextureLibrary::addTextureAtlas("modelDIY", RES_DIR"modelDIY/modelDIY.png", RES_DIR"modelDIY/modelDIY.txt");

	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_root->setAlignmentCenter();
	//m_root->setBackground(SolidColorBrush::green());

	modelNode = createRef<ModelView>();

	switchView(ViewE::Selector);

	g_instance = this;
}

MainView * MainView::get()
{
	return g_instance;
}

void MainView::switchView(ViewE view)
{
	if (view == m_curView)
		return;

	switch (view)
	{
	case ViewE::Home:
	{
		if (!homeNode)
		{
			homeNode = createRef<HomeView>();
			homeNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(homeNode);
		m_root->addChild(modelNode);
		modelNode->setAlignmentCenter();
	}
	break;
	case ViewE::Selector:
	{
		if (!selectNode)
		{
			selectNode = createRef<SelectorView>();
			selectNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(selectNode);
		m_root->addChild(modelNode);
		modelNode->setHorizontalAlignment(HorizontalAlignment::Left);
	}
	break;
	case ViewE::DIY:
	{
		if (!diyNode)
		{
			diyNode = createRef<DIYView>();
			diyNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(diyNode);
		m_root->addChild(modelNode);
		modelNode->setHorizontalAlignment(HorizontalAlignment::Left);
	}
	break;
	default:
		break;
	}
	m_curView = view;
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();


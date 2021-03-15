#include "MainView.h"
#include "newbrush/Shader.h"
#include "newbrush/DateTime.h"
#include "newbrush/Log.h"
#include "newbrush/Helper.h"

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(756.0f);
	Application::get()->mainWindow()->setHeight(756.0f);
	Application::get()->mainWindow()->setTitle("clock effect Power By NewBrush");

	m_root = createRef<Node2D>();
	m_root->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/eco_background.png")));

	switchDrivingMode(DrivingModeE::eco);
}

ref<Node> MainView::getRoot()
{
	return m_root;
}

void MainView::switchDrivingMode(DrivingModeE mode)
{
	if (mode == m_mode)
		return;

	switch (mode)
	{
	case DrivingModeE::eco:
	{
		if (!m_ecoNode) m_ecoNode = createRef<ECONode>();
		m_root->clearChildren();
		m_root->addChild(m_ecoNode);
	}
	break;
	default:
		break;
	}
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();
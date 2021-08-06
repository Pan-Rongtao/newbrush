#include "MainView.h"
#include "newbrush/Log.h"
#include "ManualParkingView.h"
#include "IntelligentParkingView.h"
#include "MemoryParking.h"

static MainView *g_instance = nullptr;

void MainView::init()
{
	g_instance = this;
	Application::get()->mainWindow()->setWidth(1920.0f);
#if NB_OS == NB_OS_QNX
	Application::get()->mainWindow()->setHeight(720.0f);
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
#else
	Application::get()->mainWindow()->setHeight(1080.0f);
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
#endif
	Application::get()->mainWindow()->setTitle("ipu02 Power By NewBrush");

	m_root->setBackground(SolidColorBrush::white());
	m_root->setAlignmentCenter();

	//switchView<IntelligentParkingView>();
	switchView<ManualParkingView>();

	m_root->Key += [&](const KeyEventArgs &e)
	{
		switch (e.key)
		{
		case KeyCode::_1: switchView<ManualParkingView>();			break;
		case KeyCode::_2: switchView<IntelligentParkingView>();		break;
		case KeyCode::_3: switchView<MemoryParking>();				break;
		default:													break;
		}
	};
}

MainView * MainView::get()
{
	return g_instance;
}

//一定不要少了这句
nb::ref<ViewBase> g_view = createRef<MainView>();

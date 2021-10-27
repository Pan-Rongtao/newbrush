#include "MainView.h"
#include "newbrush/Log.h"
#include "newbrush/Helper.h"

extern MessageQueue g_msgQueue;
void MainView::init()
{
	Application::get()->mainWindow()->setWidth(756.0f);
	Application::get()->mainWindow()->setHeight(756.0f);
	Application::get()->mainWindow()->setTitle("clock effect Power By NewBrush");

	m_root = createRef<Node2D>();
#ifdef WIN32
	m_root->Touch += nbBindEventFunction(MainView::onTouch);
#endif // WIN32	
	//m_root->setBackground(SolidColorBrush::white());

	m_mode = DrivingMode::None;

	m_data = buildData();
	if (m_data)
	{
		m_data->ValueChanged += [&](const DataContext::ValueChangedArgs & args)
		{
			if (args.path == "mode")
			{
				auto task = [=]()
				{
					int mode = args.value.get_value<int>();
					if (mode == 0)
					{
						switchDrivingMode(DrivingMode::None);
					}
					else if (mode == 1)
					{
						switchDrivingMode(DrivingMode::Eco);
					}
					else if (mode == 2)
					{
						switchDrivingMode(DrivingMode::Normal);
					}
					else if (mode == 3)
					{
						switchDrivingMode(DrivingMode::Sport);
					}
				};
#if NB_OS == NB_OS_ANDROID
				g_msgQueue.post(task);
#else
				task();
#endif
			}
		};
	}

	switchDrivingMode(DrivingMode::Eco);
}

float MainView::getAngleForTime()
{
	static float anglePerMS = 0.006f;
	auto now = Time::now();
	auto mses = now.second() * 1000 + now.millisecond();
	auto angle = anglePerMS * mses;
	return angle;
}

void MainView::onKey(const KeyEventArgs &e)
{
	switch (e.key)
	{
	case KeyCode::_1: switchDrivingMode(DrivingMode::Eco);		break;
	case KeyCode::_2: switchDrivingMode(DrivingMode::Normal);	break;
	case KeyCode::_3: switchDrivingMode(DrivingMode::Sport);	break;
	default:													break;
	}
}

#ifdef WIN32
void MainView::onTouch(const TouchEventArgs &e)
{
	if (e.action != TouchAction::Down)
		return;

	if (m_mode == DrivingMode::None)
	{
		switchDrivingMode(DrivingMode::Eco);
	}
	else if (m_mode == DrivingMode::Eco)
	{
		switchDrivingMode(DrivingMode::Normal);
	}
	else if (m_mode == DrivingMode::Normal)
	{
		switchDrivingMode(DrivingMode::Sport);
	}
	else if (m_mode == DrivingMode::Sport)
	{
		switchDrivingMode(DrivingMode::Eco);
	}
}
#endif // WIN32

void MainView::switchDrivingMode(DrivingMode mode)
{
	if (mode == m_mode)
		return;

	switch (mode)
	{
	case DrivingMode::None:
	{
		m_root->clearChildren();
		m_mode = DrivingMode::None;
		break;
	}
	case DrivingMode::Eco:
	{
		if (!m_ecoNode)
		{
			m_ecoNode = createRef<ECONode>();
			m_ecoNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(m_ecoNode);
		m_mode = DrivingMode::Eco;
		break;
	}
	case DrivingMode::Normal:
	{
		if (!m_normalNode)
		{
			m_normalNode = createRef<NormalNode>();
			m_normalNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(m_normalNode);
		m_mode = DrivingMode::Normal;
		break;
	}
	case DrivingMode::Sport:
	{
		if (!m_sportNode)
		{
			m_sportNode = createRef<SportNode>();
			m_sportNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(m_sportNode);
		m_mode = DrivingMode::Sport;
		break;
	}
	default:
		break;
	}
}

bool MainView::isInCircle(float x, float y, float circleX, float circleY, float r)
{
	auto dis = sqrt((x - circleX) * (x - circleX) + (y - circleY) * (y - circleY));
	return dis <= r || dis - r <= 12;
}

//获取点与x轴的夹角（0~360）
float MainView::getAngle(float x, float y, float centerX, float centerY)
{
	auto a = glm::degrees(atan2(y - centerY, x - centerX));
	return (float)((int)(a + 360) % 360);
}

ref<DataObject> MainView::buildData()
{
	auto data = nb::makeDataObject("m_root");
	data->add(makeDataInt("mode", 1));
	return data;
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();

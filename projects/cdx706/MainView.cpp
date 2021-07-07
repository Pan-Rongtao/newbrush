#include "MainView.h"
#include "newbrush/Log.h"
#include "newbrush/Helper.h"

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(756.0f);
	Application::get()->mainWindow()->setHeight(756.0f);
	Application::get()->mainWindow()->setTitle("clock effect Power By NewBrush");

	m_root = createRef<Node2D>();
	m_root->Key += nbBindEventFunction(MainView::onKey);

	switchDrivingMode(DrivingModeE::normal);
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
	case KeyCode::_1: switchDrivingMode(DrivingModeE::eco);		break;
	case KeyCode::_2: switchDrivingMode(DrivingModeE::normal);	break;
	case KeyCode::_3: switchDrivingMode(DrivingModeE::sport);	break;
	default:													break;
	}
}

void MainView::switchDrivingMode(DrivingModeE mode)
{
	if (mode == m_mode)
		return;

	switch (mode)
	{
	case DrivingModeE::eco:
	{
		if (!m_ecoNode)
		{
			m_ecoNode = createRef<ECONode>();
			m_ecoNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(m_ecoNode);
	}
	break;
	case DrivingModeE::normal:
	{
		if (!m_normalNode)
		{
			m_normalNode = createRef<NormalNode>();
			m_normalNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		m_root->addChild(m_normalNode);
	}
	break;
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

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();

#include "MainView.h"
#include "newbrush/Log.h"
#include "newbrush/Helper.h"

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(756.0f);
	Application::get()->mainWindow()->setHeight(756.0f);
	Application::get()->mainWindow()->setTitle("clock effect Power By NewBrush");

	m_root = createRef<Node2D>();
	//m_root->setBackground(SolidColorBrush::white());
	m_root->Key += nbBindEventFunction(MainView::onKey);

	m_btnEco = createRef<Button>(315, 800, 27, 26);
	auto texEco = createRef<Texture2D>(RES_DIR"cxd706/Button1.png");
	m_btnEco->setBkgndNormal(createRef<ImageBrush>(texEco));
	m_btnEco->setBkgndPress(createRef<ImageBrush>(texEco));
	m_btnEco->Click += nbBindEventFunction(MainView::onBtnClick);

	m_btnNormal = createRef<Button>(365, 800, 27, 26);
	auto texNormal = createRef<Texture2D>(RES_DIR"cxd706/Button2.png");
	m_btnNormal->setBkgndNormal(createRef<ImageBrush>(texNormal));
	m_btnNormal->setBkgndPress(createRef<ImageBrush>(texNormal));
	m_btnNormal->Click += nbBindEventFunction(MainView::onBtnClick);

	m_btnSport = createRef<Button>(415, 800, 27, 26);
	auto texSport = createRef<Texture2D>(RES_DIR"cxd706/Button3.png");
	m_btnSport->setBkgndNormal(createRef<ImageBrush>(texSport));
	m_btnSport->setBkgndPress(createRef<ImageBrush>(texSport));
	m_btnSport->Click += nbBindEventFunction(MainView::onBtnClick);

	/*m_root->addChild(m_btnEco);
	m_root->addChild(m_btnNormal);
	m_root->addChild(m_btnSport);*/
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
		/*m_root->addChild(m_btnEco);
		m_root->addChild(m_btnNormal);
		m_root->addChild(m_btnSport);*/
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
		/*m_root->addChild(m_btnEco);
		m_root->addChild(m_btnNormal);
		m_root->addChild(m_btnSport);*/
		m_root->addChild(m_normalNode);
	}
	break;
	case DrivingModeE::sport:
	{
		if (!m_sportNode)
		{
			m_sportNode = createRef<SportNode>();
			m_sportNode->setAlignmentCenter();
		}
		m_root->clearChildren();
		/*m_root->addChild(m_btnEco);
		m_root->addChild(m_btnNormal);
		m_root->addChild(m_btnSport);*/
		m_root->addChild(m_sportNode);
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

void MainView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnEco.get())
	{
		switchDrivingMode(DrivingModeE::eco);
	}
	else if (e.sender == m_btnNormal.get())
	{
		switchDrivingMode(DrivingModeE::normal);
	}
	else if (e.sender == m_btnSport.get())
	{
		switchDrivingMode(DrivingModeE::sport);
	}
}

//一定不要少了这句
ref<ViewBase> g_view = createRef<MainView>();

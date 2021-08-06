#include "MainView.h"
#include "effolkronium/random.hpp"
#include "newbrush/Log.h"

#if NB_OS == NB_OS_WINDOWS_NT
	#include "TCPClient.h"
#pragma comment(lib,"TCPConnect.lib")
#endif // 


/********************************************
* 发布给项目给出release版本，不要给debug版本
*********************************************/

#if NDEBUG && NB_OS == NB_OS_WINDOWS_NT
	#undef RES_DIR
	#define RES_DIR "./nb/win32/resource/"
#endif

using Random = effolkronium::random_static;

void MainView::init()
{
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(1080.0f);
	Application::get()->mainWindow()->setPosition(0.0f, 0.0f);
	Application::get()->mainWindow()->setWindowsStyle(WindowStyleE::None);
	Application::get()->mainWindow()->setTitle("RadarACM1 Power By NewBrush");

	TextureLibrary::addTextureAtlas("radarACM1", RES_DIR"radarACM1/radarACM1.png", RES_DIR"radarACM1/radarACM1.txt");

	m_root = createRef<Node2D>();
	m_root->setBackground(createRef<SolidColorBrush>(Color(10, 16, 30)));
	m_root->setAlignmentCenter();

	auto rightBg = Node2D::createWithTextureFrameName("radarACM1", "bg.png", true, 1187.0f, 0.0f);
	//rightBg->setBackground(SolidColorBrush::green());
	auto txtFrameNo = createRef<TextBlock>(10.0f, 30.0f, 100.0f, 36.0f);
	txtFrameNo->setColor(Colors::white);
	txtFrameNo->setText(u8"帧号:");
	m_txtFrameNum = createRef<TextBlock>(100.0f, 30.0f, 180.0f, 36.0f);
	m_txtFrameNum->setColor(Colors::white);
	m_txtFrameNum->setText(u8"123");

	m_regObjs[0].obj = Node2D::createWithTextureFrameName("radarACM1", "adult.png", true, 1367.0f - 1187.0f, 330.0f);
	m_regObjs[1].obj = Node2D::createWithTextureFrameName("radarACM1", "adult.png", true, 1586.0f - 1187.0f, 330.0f);
	m_regObjs[2].obj = Node2D::createWithTextureFrameName("radarACM1", "baby.png", true, 1330.0f - 1187.0f, 630.0f);
//	m_regObjs[3].obj = Node2D::createWithTextureFrameName("radarACM1", "pets.png", true, 1463.0f - 1187.0f, 630.0f);
//	m_regObjs[4].obj = Node2D::createWithTextureFrameName("radarACM1", "adult.png", true, 1624.0f - 1187.0f, 630.0f);

	auto x = 40.0f, y = 355.0f,  w = 26.0f;
	m_regObjs[0].breath0 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x, y);
	m_regObjs[0].breath1 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x + w * 1, y);
	x = 32.0f; y = 415.0f;
	m_regObjs[0].heartbeat0 = Node2D::createWithTextureFrameName("radarACM1", "yellow_1.png", true, x, y);
	m_regObjs[0].heartbeat1 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 1, y);
	m_regObjs[0].heartbeat2 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 2, y);
	x = 628.0f; y = 355.0f;
	m_regObjs[1].breath0 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x, y);
	m_regObjs[1].breath1 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x + w * 1, y);
	x = 615.0f; y = 415.0f;
	m_regObjs[1].heartbeat0 = Node2D::createWithTextureFrameName("radarACM1", "yellow_1.png", true, x, y);
	m_regObjs[1].heartbeat1 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 1, y);
	m_regObjs[1].heartbeat2 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 2, y);
	x = 165.0f; y = 800.0f;
	m_regObjs[2].breath0 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x, y);
	m_regObjs[2].breath1 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x + w * 1, y);
	x = 155.0f; y = 860.0f;
	m_regObjs[2].heartbeat0 = Node2D::createWithTextureFrameName("radarACM1", "yellow_1.png", true, x, y);
	m_regObjs[2].heartbeat1 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 1, y);
	m_regObjs[2].heartbeat2 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 2, y);
	x = 330.0f; y = 800.0f;
/*	m_regObjs[3].breath0 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x, y);
	m_regObjs[3].breath1 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x + w * 1, y);
	x = 320.0f; y = 860.0f;
	m_regObjs[3].heartbeat0 = Node2D::createWithTextureFrameName("radarACM1", "yellow_1.png", true, x, y);
	m_regObjs[3].heartbeat1 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 1, y);
	m_regObjs[3].heartbeat2 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 2, y);
	x = 495.0f; y = 800.0f;
	m_regObjs[4].breath0 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x, y);
	m_regObjs[4].breath1 = Node2D::createWithTextureFrameName("radarACM1", "green_0.png", true, x + w * 1, y);
	x = 485.0f; y = 860.0f;
	m_regObjs[4].heartbeat0 = Node2D::createWithTextureFrameName("radarACM1", "yellow_1.png", true, x, y);
	m_regObjs[4].heartbeat1 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 1, y);
	m_regObjs[4].heartbeat2 = Node2D::createWithTextureFrameName("radarACM1", "yellow_0.png", true, x + w * 2, y);
	*/
	m_btn = Button::createWithTextureFrameName("radarACM1", "on.png", true, 0.0f, 910.0f);
	m_btn->setBkgndCheck(createRef<ImageBrush>("radarACM1", "off.png"));
	m_btn->Click += nbBindEventFunction(MainView::onBtnClick);

	rightBg->addChild(txtFrameNo);
	rightBg->addChild(m_txtFrameNum);
	rightBg->addChild(m_regObjs[0].obj);
	rightBg->addChild(m_regObjs[0].breath0);
	rightBg->addChild(m_regObjs[0].breath1);
	rightBg->addChild(m_regObjs[0].heartbeat0);
	rightBg->addChild(m_regObjs[0].heartbeat1);
	rightBg->addChild(m_regObjs[0].heartbeat2);
	rightBg->addChild(m_regObjs[1].obj);
	rightBg->addChild(m_regObjs[1].breath0);
	rightBg->addChild(m_regObjs[1].breath1);
	rightBg->addChild(m_regObjs[1].heartbeat0);
	rightBg->addChild(m_regObjs[1].heartbeat1);
	rightBg->addChild(m_regObjs[1].heartbeat2);
	rightBg->addChild(m_regObjs[2].obj);
	rightBg->addChild(m_regObjs[2].breath0);
	rightBg->addChild(m_regObjs[2].breath1);
	rightBg->addChild(m_regObjs[2].heartbeat0);
	rightBg->addChild(m_regObjs[2].heartbeat1);
	rightBg->addChild(m_regObjs[2].heartbeat2);
/*	rightBg->addChild(m_regObjs[3].obj);
	rightBg->addChild(m_regObjs[3].breath0);
	rightBg->addChild(m_regObjs[3].breath1);
	rightBg->addChild(m_regObjs[3].heartbeat0);
	rightBg->addChild(m_regObjs[3].heartbeat1);
	rightBg->addChild(m_regObjs[3].heartbeat2);
	rightBg->addChild(m_regObjs[4].obj);
	rightBg->addChild(m_regObjs[4].breath0);
	rightBg->addChild(m_regObjs[4].breath1);
	rightBg->addChild(m_regObjs[4].heartbeat0);
	rightBg->addChild(m_regObjs[4].heartbeat1);
	rightBg->addChild(m_regObjs[4].heartbeat2);*/
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "line.png", true, 33.0f, 405.0f));
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "line.png", true, 620.0f, 405.0f));
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "line.png", true, 155.0f, 850.0f));
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "line.png", true, 320.0f, 850.0f));
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "line.png", true, 485.0f, 850.0f));
	rightBg->addChild(Node2D::createWithTextureFrameName("radarACM1", "bmp.png", true, 590.0f, 840.0f));
	rightBg->addChild(m_btn);

	m_root->addChild(rightBg);
	
	m_timerGetData.Tick += nbBindEventFunction(MainView::onTick);
	m_timerGetData.setInterval(200);

#if NB_OS == NB_OS_WINDOWS_NT
	m_tcpConnect = tcpConnect("127.0.0.1", 8888);//-1获取socket失败,-2创建socket失败，-3连接失败，1连接成功
#endif

#if NB_OS == NB_OS_WINDOWS_NT
	if (m_tcpConnect < 0)
	{
		Log::warn("tcp not ready, ret={}", m_tcpConnect);
		Application::get()->mainWindow()->setTitle("tcp not ready");
	}
#endif
	enableLadar(true);
}

void MainView::enableLadar(bool enable)
{
	m_btn->setCheck(enable);
#if NB_OS == NB_OS_WINDOWS_NT
	if (m_tcpConnect >= 0)
		tcpSend(m_btn->isChecked());
#endif

	if (m_btn->isChecked())
		m_timerGetData.start();
	else
		m_timerGetData.stop();
	for (auto &regObj : m_regObjs)
	{
		updateObjet(regObj, enable, 0, 0);
	}
}

void MainView::updateObjet(const RegObj &regObj, bool visible, int breath, int heartbeat)
{
	regObj.obj->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	regObj.breath0->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	regObj.breath1->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	regObj.heartbeat0->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	regObj.heartbeat1->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	regObj.heartbeat2->setVisibility(visible ? VisibilityE::Visible : VisibilityE::Hidden);
	if (visible)
	{
		regObj.breath0->setBackground(createRef<ImageBrush>("radarACM1", "green_" + std::to_string(breath / 10 % 10) + ".png"));
		regObj.breath1->setBackground(createRef<ImageBrush>("radarACM1", "green_" + std::to_string(breath / 1 % 10) + ".png"));
		regObj.heartbeat0->setBackground(createRef<ImageBrush>("radarACM1", "yellow_" + std::to_string(heartbeat / 100 % 10) + ".png"));
		regObj.heartbeat1->setBackground(createRef<ImageBrush>("radarACM1", "yellow_" + std::to_string(heartbeat / 10 % 10) + ".png"));
		regObj.heartbeat2->setBackground(createRef<ImageBrush>("radarACM1", "yellow_" + std::to_string(heartbeat / 1 % 10) + ".png"));
	}
}

MainView::~MainView()
{
#if NB_OS == NB_OS_WINDOWS_NT
	if (m_tcpConnect >= 0)
	{
		tcpSend(0);
		tcpClose();
	}
#endif
}

void MainView::onTick(const EventArgs &e)
{
	if (e.sender == &m_timerGetData)
	{
		if (m_tcpConnect < 0)
		{
			for (auto &regObj : m_regObjs)
			{
				int breath = Random::get(12, 20);
				int heartbeat = Random::get(60, 100);
				updateObjet(regObj, true, breath, heartbeat);
			}
		}
		else
		{
#if NB_OS == NB_OS_WINDOWS_NT
			RadarACMData radarData;
			Log::info("before tcpReceive");
			auto ret = tcpReceive(&radarData);
			for (int i = 0; i < 3; ++i)
			{
				auto const &regObj = m_regObjs[i];
				auto const &target = radarData.frameData.Target[i];
				updateObjet(regObj, target.ExistStatus ? true : false, (int)target.BreathingRate, (int)target.HeartRate);
				m_txtFrameNum->setText(std::to_string(radarData.frameHead.FrameID));
				Log::info("target[{}]: exist={}, breath={}, heartbeart={}", i, target.ExistStatus, (int)target.BreathingRate, (int)target.HeartRate);
			}
#endif
		}
	}
}

void MainView::onBtnClick(const EventArgs &e)
{
	if (e.sender == m_btn.get())
	{
		enableLadar(!m_btn->isChecked());
	}
}

//一定不要少了这句
nb::ref<ViewBase> g_view = createRef<MainView>();

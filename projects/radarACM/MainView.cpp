#include "MainView.h"
#include "effolkronium/random.hpp"
#include "newbrush/Log.h"

#include "TCPClient.h"

/********************************************
* 发布给项目给出release版本，不要给debug版本
*********************************************/

#ifdef NDEBUG
	#undef RES_DIR
	#define RES_DIR "D:/2021SH/nb/win32/resource/radarACM/"
#endif

using Random = effolkronium::random_static;
#define BreathValueCacheCount  100


void MainView::init()
{
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setHeight(1080.0f);
	Application::get()->mainWindow()->setPosition(0.0f, 0.0f);
	Application::get()->mainWindow()->setWindowsStyle(WindowStyleE::None);
	Application::get()->mainWindow()->setTitle("RadarACM Power By NewBrush");

	BrushLibrary::addImageBrush("brushBg", RES_DIR"radarACM/BG1.png");
	BrushLibrary::addImageBrush("recognition", RES_DIR"radarACM/1.png");
	BrushLibrary::addImageBrush("nonerecognition", RES_DIR"radarACM/2.png");

	m_root = createRef<Node2D>();
	//root->setBackground(SolidColorBrush::black());

	m_recognizeRect = createRef<Image>();
	m_recognizeRect->setStretch(StretchE::Origion);
	m_recognizeRect->setPosition({0, 0});
	m_recognizeRect->setAlignmentCenter();

	m_recognizeRect1 = createRef<Image>();
	m_recognizeRect1->setStretch(StretchE::Origion);
	m_recognizeRect1->setPosition({ -13.0f, -5.0f });
	m_recognizeRect1->setAlignmentCenter();
	m_recognizeRect1->setTexture(createRef<Texture2D>(RES_DIR"radarACM/ManLine2.png"));

	m_popRoot = createRef<Node2D>(1194.0f, 46.0f, 800.0f, 600.0f);
	//m_popRoot = createRef<Node2D>(-50.0f, -45.0f, 800.0f, 600.0f);
	m_popRoot->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/POP_BG.png")));
	auto popLineBg = createRef<Node2D>(0.0f, 0.0f, 700.0f, 381.0f);
	popLineBg->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/POP_BG_Line.png")));
	popLineBg->setAlignmentCenter();
	auto breathTitle = createRef<Node2D>(71.0f, 55.0f, 111.0f, 55.0f);
	breathTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/BreathTitle.png")));
	auto BPMTitle = createRef<Node2D>(71.0f, 284.0f, 50.0f, 33.0f);
	BPMTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/BPM.png")));
	auto HeartbeatTitle = createRef<Node2D>(71.0f, 493.0f, 168.0f, 55.0f);
	HeartbeatTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/HeartbeatTitle.png")));
	m_breathValueRoot = createRef<Node2D>(71.0f, 175.0f, 52.0f * 3, 124.0f);
	m_heartBeatValueRoot = createRef<Node2D>(71.0f, 297.0f, 52.0f * 3, 124.0f);
	m_breathGraph = createRef<Node2D>(197.0f, 128.8f, 483.0f, 178.0f);
	m_heartBeatGraph = createRef<Node2D>(197.0f, 352.7f, 484.0f, 140.0f);

	m_popRoot->addChild(popLineBg);
	m_popRoot->addChild(breathTitle);
	m_popRoot->addChild(BPMTitle);
	m_popRoot->addChild(HeartbeatTitle);
	m_popRoot->addChild(m_breathValueRoot);
	m_popRoot->addChild(m_heartBeatValueRoot);
	m_popRoot->addChild(m_breathGraph);
	m_popRoot->addChild(m_heartBeatGraph);

	//root->addChild(m_recognizeRect);
	//root->addChild(m_recognizeRect1);
	m_root->addChild(m_popRoot);

	//m_opacityAnimation.setTarget(m_recognizeRect1);
	//m_opacityAnimation.setTargetPropertyName("Opacity");
	//m_opacityAnimation.duration = TimeSpan::fromMilliseconds(1500);
	//m_opacityAnimation.setEasingFunction(createRef<BackEase>());
	//m_opacityAnimation.autoReverse = true;
	//m_opacityAnimation.repeatBehavior = RepeatBehavior::forever();
	//m_opacityAnimation.setFrom(0.0f);
	//m_opacityAnimation.setTo(1.0f);
	//m_opacityAnimation.begin();

	m_popAnimation.setTarget(m_popRoot);
	m_popAnimation.setTargetPropertyName("X");
	m_popAnimation.duration = TimeSpan::fromMilliseconds(300);
	m_popAnimation.setEasingFunction(createRef<LinearEase>());
	m_popAnimation.autoReverse = true;
	m_popAnimation.repeatBehavior = RepeatBehavior::forever();
	m_popAnimation.setFrom(1194.0f);
	m_popAnimation.setTo(1920.0f);
	//m_popAnimation.begin();

	m_timerGetData.Tick += nbBindEventFunction(onTick);
	m_timerGetData.start(35);
	m_timerUpdate.Tick += nbBindEventFunction(onTick);
	m_timerUpdate.start(100);

#ifdef NDEBUG
	m_tcpConnect = tcpConnect("192.168.1.100", 8888);//-1获取socket失败,-2创建socket失败，-3连接失败，1连接成功
#endif
	if (m_tcpConnect < 0)
	{
		Log::warn("tcp not ready, ret={}", m_tcpConnect);
		Application::get()->mainWindow()->setTitle("tcp not ready");
	}
	else
	{
		tcpSend(1);
		Log::info("tcp ready.");
	}

}

MainView::~MainView()
{
	tcpSend(0);
	tcpClose();
}

void MainView::setRecognitionFlag(bool flag)
{
	auto brushName = flag ? "recognition" : "nonerecognition";
	m_root->setBackground(BrushLibrary::get(brushName));
}

void MainView::setValueNodes(nb::ref<Node2D> parent, int value, const std::string &imagePrefix)
{
	parent->clearChildren();
	std::vector<nb::ref<Node2D>> nodes;
	auto temp = value;
	do
	{
		auto n = temp % 10;
		auto nodeImagePath = imagePrefix + std::to_string(n) + ".png";
		auto node = createRef<Node2D>(0.0f, 0.0f, 52.0f, 80.0f);
		node->setVerticalAlignment(VerticalAlignmentE::Center);
		node->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR + std::string("radarACM/") + nodeImagePath)));
		nodes.push_back(node);
		temp /= 10;
	} while (temp);

	auto k = 0;
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		auto node = nodes[i];
		node->setX(52.0f * k);
		parent->addChild(nodes[i]);
		++k;
	}
}

void MainView::setPoints(nb::ref<Node2D> parent, const glm::vec2 &nodeSize, const std::vector<glm::vec2>& points, nb::ref<Brush> polygonBrush, nb::ref<Brush> polylineBrush)
{
	if (points.empty())
		return;

	std::vector<glm::vec2> pointsPolygon= points;
	pointsPolygon.insert(pointsPolygon.begin(), { points[0].x, nodeSize.y });
	pointsPolygon.push_back({ points.back().x, nodeSize.y });

	parent->clearChildren();
	auto polygon = createRef<nb::Polygon>(pointsPolygon);
	polygon->setBackground(polygonBrush);
	auto polyline = createRef<nb::Polyline>(points, 5.0f);
	polyline->setBackground(polylineBrush);
	parent->addChild(polygon);
	parent->addChild(polyline);
}

void MainView::setBreathValue(int value)
{
	setValueNodes(m_breathValueRoot, value, "NumGreen");
}

void MainView::setBreathGraphic(float value)
{
	if (m_breathGraphics.size() > BreathValueCacheCount)
		m_breathGraphics.pop_front();
	m_breathGraphics.emplace_back(value);

	auto points = valuesToPoints(m_breathGraphics, { 483.0f, 123.0f }, BreathValueCacheCount);
	auto linearBrushPolygon = createRef<LinearGradientBrush>();
	linearBrushPolygon->lenght = Application::get()->mainWindow()->height();
	linearBrushPolygon->stops = { { 0.656f, Color(134, 189, 95, 0) },{ 0.8f, Color(134, 189, 95, 120) } };;// { { 0.5f, Color(134, 189, 95, 10) }, { 0.85f, Color(134, 189, 95, 120) } };
	auto linearBrushPolyline = createRef<LinearGradientBrush>();
	linearBrushPolyline->lenght = Application::get()->mainWindow()->height();
	linearBrushPolyline->stops = { { 0.7f, Colors::green },{ 0.8f, Color(184,233,134,255) } };
	setPoints(m_breathGraph, { 483.0f, 173.0f }, points, linearBrushPolygon, linearBrushPolyline);
	auto p = points.back() - glm::vec2(5.0f);
	m_breathPoint = createRef<Node2D>(p.x, p.y, 10.0f, 10.0f);
	m_breathPoint->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/BreathOrangePoint.png")));
	m_breathGraph->addChild(m_breathPoint);
}

void MainView::setHeartBeatValue(int value)
{
	setValueNodes(m_heartBeatValueRoot, value, "NumOrange");
}

void MainView::setHeartBeatGraphic(float value)
{
	if (m_heartBeatGraphics.size() > BreathValueCacheCount)
		m_heartBeatGraphics.pop_front();
	m_heartBeatGraphics.emplace_back(value);

	std::vector<glm::vec2> points = valuesToPoints(m_heartBeatGraphics, { 484.0f, 90.0f }, BreathValueCacheCount);
	auto linearBrushPolygon = createRef<LinearGradientBrush>();
	linearBrushPolygon->stops = { { 0.46f, Color(248, 178, 95, 0) },{ 0.6f, Color(248, 197, 113, 120) } };// { { 0.1f, Color(248, 178, 95, 10) }, { 0.353f, Color(248, 197, 113, 120) } };
	linearBrushPolygon->lenght = Application::get()->mainWindow()->height();
	auto linearBrushPolyline = createRef<LinearGradientBrush>();
	linearBrushPolyline->stops = { { 0.55f, Color(249, 135, 95, 255) },{ 0.6f, Color(254, 190, 60, 255) } };//{ { 0.2f, Color(249, 135, 95, 255) },{ 0.353f, Color(254,190, 60, 255) } };
	linearBrushPolyline->lenght = Application::get()->mainWindow()->height();
	setPoints(m_heartBeatGraph, { 484.0f, 140.0f }, points, linearBrushPolygon, linearBrushPolyline);
	auto p = points.back() - glm::vec2(5.0f);
	m_heartBeatPoint = createRef<Node2D>(p.x, p.y, 10.0f, 10.0f);
	m_heartBeatPoint->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"radarACM/HeartbeatOrangePoint.png")));
	m_heartBeatGraph->addChild(m_heartBeatPoint);
}

std::vector<glm::vec2> MainView::valuesToPoints(const std::list<float> &values, const glm::vec2 &nodeSize, int pointsCount)
{
	float pointSpacing = nodeSize.x / pointsCount;
	std::vector<glm::vec2> ret;
	int i = 0;
	for (auto iter = values.begin(); iter != values.end(); ++iter)
	{
		auto v = *iter;
		auto x = i * pointSpacing;
		auto y = nodeSize.y - ((v + 1.0f) / 2.0f) * nodeSize.y;
		ret.push_back({x, y});
		++i;
	}

	return ret;
}

void MainView::onTick(const EventArgs &e)
{
	if (e.sender == &m_timerGetData)
	{
		if (m_tcpConnect < 0)
		{
			m_breathValue = Random::get(12, 20);
			m_heartBeatValue = Random::get(60, 100);
			m_breathGraphic = Random::get(-1.0f, 1.0f);
			m_heartBeatGraphic = Random::get(-1.0f, 1.0f);
		}
		else
		{
			float breath = 0.0f, heart = 0.0f, breathingPhase = 0.0f, heartPhase = 0.0f;
			auto ret = tcpReceive(m_existStatus, breathingPhase, heartPhase, breath, heart);
			nb::Log::info("breath={}, heart={}", breath, heart);
			m_breathValue = (int)breath;
			m_heartBeatValue = (int)heart;
			m_breathGraphic = breathingPhase;
			m_heartBeatGraphic = heartPhase;
		}
		setRecognitionFlag(m_existStatus == 0 ? false : true);
	}
	else if (e.sender == &m_timerUpdate)
	{
		setBreathValue(m_breathValue);
		setBreathGraphic(m_breathGraphic);
		setHeartBeatValue(m_heartBeatValue);
		setHeartBeatGraphic(m_heartBeatGraphic);
	}
}

//一定不要少了这句
nb::ref<ViewBase> g_view = createRef<MainView>();
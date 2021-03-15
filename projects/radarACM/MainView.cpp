#include "MainView.h"
#include "newbrush/Shader.h"
#include "effolkronium/random.hpp"
#include "newbrush/Log.h"

#include"TCPClient.h"

#define RES_DIR "../resource/radarACM/"

using Random = effolkronium::random_static;
#define BreathValueCacheCount  50
#define BreathGraphMin 10.0f
#define BreathGraphMax 50.0f
#define HeartGraphMin 50.0f
#define HeartGraphMax 100.0f

MainView::MainView()
	: m_tcpConnect(-1)
{
	BrushLibrary::addImageBrush("brushBg", RES_DIR"BG1.png");
	BrushLibrary::addSolidColorBrush("brushRed", Colors::red);

	m_root = createRef<Node2D>();
	m_root->setBackground(BrushLibrary::get("brushBg"));

	auto recognizeRect = createRef<Image>();
	recognizeRect->setStretch(StretchE::Origion);
	recognizeRect->setPosition({0, 0});
	recognizeRect->setHorizontalAlignment(HorizontalAlignmentE::Center);
	recognizeRect->setVerticalAlignment(VerticalAlignmentE::Center);
	recognizeRect->setTexture(createRef<Texture2D>(RES_DIR"ManLine1.png"));

	m_recognizeRect1 = createRef<Image>();
	m_recognizeRect1->setStretch(StretchE::Origion);
	m_recognizeRect1->setPosition({ -13.0f, -5.0f });
	m_recognizeRect1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_recognizeRect1->setVerticalAlignment(VerticalAlignmentE::Center);
	m_recognizeRect1->setTexture(createRef<Texture2D>(RES_DIR"ManLine2.png"));

	m_popRoot = createRef<Node2D>(1194.0f, 46.0f, 800.0f, 600.0f);
	m_popRoot->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"POP_BG.png")));
	auto popLineBg = createRef<Node2D>(0.0f, 0.0f, 700.0f, 381.0f);
	popLineBg->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"POP_BG_Line.png")));
	popLineBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
	popLineBg->setVerticalAlignment(VerticalAlignmentE::Center);
	auto breathTitle = createRef<Node2D>(71.0f, 55.0f, 111.0f, 55.0f);
	breathTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"BreathTitle.png")));
	auto BPMTitle = createRef<Node2D>(71.0f, 284.0f, 50.0f, 33.0f);
	BPMTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"BPM.png")));
	auto HeartbeatTitle = createRef<Node2D>(71.0f, 493.0f, 168.0f, 55.0f);
	HeartbeatTitle->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"HeartbeatTitle.png")));
	m_breathValueRoot = createRef<Node2D>(71.0f, 175.0f, 52.0f * 3, 124.0f);
	m_heartBeatValueRoot = createRef<Node2D>(71.0f, 297.0f, 52.0f * 3, 124.0f);
	m_breathGraph = createRef<Node2D>(197.0f, 128.8f, 483.0f, 178.0f);
	//m_breathGraph->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"编组.png")));
	m_heartBeatGraph = createRef<Node2D>(197.0f, 352.7f, 484.0f, 140.0f);
	//m_heartBeatGraph->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"编组 2.png")));
	//heartBeatGraph->background()->opacity = 0.1f;

	m_popRoot->addChild(popLineBg);
	m_popRoot->addChild(breathTitle);
	m_popRoot->addChild(BPMTitle);
	m_popRoot->addChild(HeartbeatTitle);
	m_popRoot->addChild(m_breathValueRoot);
	m_popRoot->addChild(m_heartBeatValueRoot);
	m_popRoot->addChild(m_breathGraph);
	m_popRoot->addChild(m_heartBeatGraph);

	m_root->addChild(recognizeRect);
	m_root->addChild(m_recognizeRect1);
	m_root->addChild(m_popRoot);
	//m_root = m_breathLine;

	//addBreathValue(12);
	//setValueNodes(m_heartBeatValueRoot, 100, "NumOrange");

	m_opacityAnimation.setTarget(m_recognizeRect1);
	m_opacityAnimation.setTargetPropertyName("Opacity");
	m_opacityAnimation.duration = TimeSpan::fromMilliseconds(1500);
	m_opacityAnimation.setEasingFunction(createRef<BackEase>());
	m_opacityAnimation.autoReverse = true;
	m_opacityAnimation.repeatBehavior = RepeatBehavior::forever();
	m_opacityAnimation.setFrom(0.0f);
	m_opacityAnimation.setTo(1.0f);
	m_opacityAnimation.begin();

	m_popAnimation.setTarget(m_popRoot);
	m_popAnimation.setTargetPropertyName("X");
	m_popAnimation.duration = TimeSpan::fromMilliseconds(300);
	m_popAnimation.setEasingFunction(createRef<LinearEase>());
	m_popAnimation.autoReverse = true;
	m_popAnimation.repeatBehavior = RepeatBehavior::forever();
	m_popAnimation.setFrom(1194.0f);
	m_popAnimation.setTo(1920.0f);
	//m_popAnimation.begin();

	m_timer.Tick += nbBindEventFunction(onTick);
	m_timer.start(100);

	//addBreathValue(0);
	//addBreathValue(25);
	//addBreathValue(12);
	//addBreathValue(12);
	//addBreathValue(25);

	m_tcpConnect = tcpConnect("192.168.1.100", 8888);//-1获取socket失败,-2创建socket失败，-3连接失败，1连接成功
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
		node->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR + nodeImagePath)));
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
	std::vector<glm::vec2> pointsPolygon= points;
	pointsPolygon.insert(pointsPolygon.begin(), { points[0].x, nodeSize.y });
	pointsPolygon.push_back({ points.back().x, nodeSize.y });

	parent->clearChildren();
	auto polygon = createRef<nb::Polygon>(pointsPolygon);
	polygon->setBackground(polygonBrush/*createRef<SolidColorBrush>(cPolygon)*/);
	auto polyline = createRef<nb::Polyline>(points, 5.0f);
	polyline->setBackground(polylineBrush);
	parent->addChild(polygon);
	parent->addChild(polyline);
}

void MainView::setBreathValue(int value)
{
	if (m_breathValues.size() > BreathValueCacheCount)
		m_breathValues.pop_front();
	m_breathValues.emplace_back(value);

	setValueNodes(m_breathValueRoot, value, "NumGreen");
	auto points = valuesToPoints(m_breathValues, BreathGraphMin, BreathGraphMax, { 483.0f, 173.0f }, BreathValueCacheCount);
	auto linearBrushPolygon = createRef<LinearGradientBrush>();
	linearBrushPolygon->stops = { { 0.656f, Color(0, 134, 189, 95) },{ 0.8f, Color(120, 134, 189, 95) } };
	auto linearBrushPolyline = createRef<LinearGradientBrush>();
	linearBrushPolyline->stops = { { 0.7f, Colors::green },{ 0.8f, Color(255, 184,233,134) } };
	setPoints(m_breathGraph, { 483.0f, 173.0f }, points, linearBrushPolygon, linearBrushPolyline);
	auto p = points.back() - glm::vec2(5.0f);
	m_breathPoint = createRef<Node2D>(p.x, p.y, 10.0f, 10.0f);
	m_breathPoint->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"BreathOrangePoint.png")));
	m_breathGraph->addChild(m_breathPoint);
}

void MainView::setHeartBeatValue(int value)
{
	if (m_heartBeatValues.size() > BreathValueCacheCount)
		m_heartBeatValues.pop_front();
	m_heartBeatValues.emplace_back(value);

	setValueNodes(m_heartBeatValueRoot, value, "NumOrange");
	auto points = valuesToPoints(m_heartBeatValues, HeartGraphMin, HeartGraphMax, { 484.0f, 140.0f }, BreathValueCacheCount);
	auto linearBrushPolygon = createRef<LinearGradientBrush>();
	linearBrushPolygon->stops = { {0.46f, Color(0, 248, 178, 95)},{ 0.6f, Color(120, 248, 197, 113) } };
	auto linearBrushPolyline = createRef<LinearGradientBrush>();
	linearBrushPolyline->stops = { { 0.55f, Color(255, 249, 135, 95) },{ 0.6f, Color(255, 254,190,60) } };
	setPoints(m_heartBeatGraph, { 484.0f, 140.0f }, points, linearBrushPolygon, linearBrushPolyline);
	auto p = points.back() - glm::vec2(5.0f);
	m_heartBeatPoint = createRef<Node2D>(p.x, p.y, 10.0f, 10.0f);
	m_heartBeatPoint->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"HeartbeatOrangePoint.png")));
	m_heartBeatGraph->addChild(m_heartBeatPoint);
}

std::vector<glm::vec2> MainView::valuesToPoints(const std::list<int> &values, float minValue, float maxValue, const glm::vec2 &nodeSize, int pointsCount)
{
	float pointSpacing = nodeSize.x / pointsCount;
	std::vector<glm::vec2> ret;
	int i = 0;
	for (auto iter = values.begin(); iter != values.end(); ++iter)
	{
		auto v = *iter;
		auto x = i * pointSpacing;
		auto y = nodeSize.y - (v / maxValue) * nodeSize.y;
		ret.push_back({x, y});
		++i;
	}

	return ret;
}

void MainView::onTick(const EventArgs &e)
{
	if (m_tcpConnect < 0)
	{
		int breathV = Random::get(12, 20);
		int heartBeatV = Random::get(60, 100);
		setBreathValue(breathV);
		setHeartBeatValue(heartBeatV);
	}
	else
	{
		uint8_t status;
		float breath = 0.0f, heart = 0.0f, breathingPhase = 0.0f, heartPhase = 0.0f;
		auto ret = tcpReceive(status, breathingPhase, heartPhase, breath, heart);
		setBreathValue(breath);
		setHeartBeatValue(heart);
	}
}
#pragma once
#include "../Common.h"

using namespace nb;

class MainView : public ViewBase
{
public:
	~MainView();

	virtual void init() override;

	void setRecognitionFlag(bool flag);
	
	void setBreathValue(int value);
	void setBreathGraphic(float value);
	void setHeartBeatValue(int value);
	void setHeartBeatGraphic(float value);

	nb::ref<Image> m_recognizeRect;
	nb::ref<Image> m_recognizeRect1;
	nb::ref<Node2D> m_popRoot;
	nb::ref<Node2D> m_breathValueRoot;
	nb::ref<Node2D> m_heartBeatValueRoot; 
	nb::ref<Node2D> m_breathGraph;
	nb::ref<Node2D> m_heartBeatGraph;
	nb::ref<Node2D> m_breathPoint;
	nb::ref<Node2D> m_heartBeatPoint;
	FloatAnimation m_opacityAnimation;
	FloatAnimation m_popAnimation;
	
private:
	std::vector<glm::vec2> valuesToPoints(const std::list<float> &values, const glm::vec2 &nodeSize, int pointsCount);
	void setValueNodes(nb::ref<Node2D> parent, int value, const std::string &imagePrefix);
	void setPoints(nb::ref<Node2D> parent, const glm::vec2 &nodeSize, const std::vector<glm::vec2> &points, nb::ref<Brush> polygonBrush, nb::ref<Brush> polylineBrush);
	
	void onTick(const EventArgs &e);

	std::list<float> m_breathGraphics;
	std::list<float> m_heartBeatGraphics;
	Timer m_timerGetData;
	Timer m_timerUpdate;

	int m_tcpConnect{-1};

	int m_breathValue;
	int m_heartBeatValue;
	float m_breathGraphic;
	float m_heartBeatGraphic;
	uint8_t m_existStatus{0};
};
#include "newbrush/Application.h"
#include "newbrush/Node2D.h"
#include "newbrush/Controls.h"

using namespace nb;

class MainView
{
public:
	MainView();
	~MainView();

	void setBreathValue(int value);
	void setHeartBeatValue(int value);

	nb::ref<Node2D> m_root;
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
	std::vector<glm::vec2> valuesToPoints(const std::list<int> &values, float minValue, float maxValue, const glm::vec2 &nodeSize, int pointsCount);
	void setValueNodes(nb::ref<Node2D> parent, int value, const std::string &imagePrefix);
	void setPoints(nb::ref<Node2D> parent, const glm::vec2 &nodeSize, const std::vector<glm::vec2> &points, nb::ref<Brush> polygonBrush, nb::ref<Brush> polylineBrush);
	
	void onTick(const EventArgs &e);

	std::list<int> m_breathValues;
	std::list<int> m_heartBeatValues;
	Timer m_timer;

	int m_tcpConnect;
};
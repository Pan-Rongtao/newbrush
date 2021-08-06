#pragma once
#include "../Common.h"

using namespace nb;

class MainView : public ViewBase
{
public:
	~MainView();

	virtual void init() override;

	void enableLadar(bool enable);

private:
	struct RegObj
	{
		nb::ref<Node2D> obj;
		nb::ref<Node2D> breath0;
		nb::ref<Node2D> breath1;
		nb::ref<Node2D> heartbeat0;
		nb::ref<Node2D> heartbeat1;
		nb::ref<Node2D> heartbeat2;
	};

	void onTick(const EventArgs &e);
	void onBtnClick(const EventArgs &e);
	void updateObjet(const RegObj &regObj, bool visible, int breath, int heartbeat);

	std::array<RegObj, 3> m_regObjs;
	nb::ref<Button> m_btn;
	ref<TextBlock> m_txtFrameNum;

	Timer m_timerGetData;

	int m_tcpConnect{-1};
};
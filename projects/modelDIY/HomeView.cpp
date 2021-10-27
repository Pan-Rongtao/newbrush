#include "HomeView.h"
#include "MainView.h"

static bool g_move = false;
HomeView::HomeView()
{
	setWidth(1920.0f);
	setHeight(720.0f);
	setAlignmentCenter();
	setBackground(SolidColorBrush::white());

	m_area = createRef<Button>(0.0f, 0.0f, 300.0f, 300.0f);
	//m_area->setBkgndNormal(SolidColorBrush::red());
	m_area->setAlignmentCenter();
	m_area->Click += nbBindEventFunction(HomeView::onBtnClick);
	m_area->Touch += [](const TouchEventArgs &e)
	{
		if (e.action == TouchAction::Move)
			g_move = true;
		else if(e.action == TouchAction::Down)
			g_move = false;
	};
	 
	addChild(m_area);
}

void HomeView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_area.get() && !g_move)
	{
		MainView::get()->switchView(ViewE::Selector);
	}
}

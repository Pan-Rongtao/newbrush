#include "HomeView.h"
#include "MainView.h"

HomeView::HomeView()
{
	setWidth(1920.0f);
	setHeight(720.0f);
	setAlignmentCenter();
	setBackground(SolidColorBrush::white());

	m_area = createRef<Button>(0.0f, 0.0f, 300.0f, 300.0f);
	//m_area->setBkgndNormal(SolidColorBrush::red());
	m_area->setAlignmentCenter();
	m_area->Click += nbBindEventFunction(onBtnClick);
	 
	addChild(m_area);
}

void HomeView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_area.get())
	{
		MainView::get()->switchView(ViewE::Selector);
	}
}

#pragma once
#include "../Common.h"
#include "TopBar.h"

#define AVM	"avm"
#define AI	"ai"
#define HPA "hpa"

class MainView : public ViewBase
{
public:
	static MainView *get();

	ref<TopBar> topbar();

	template<class T>
	void switchView();

	ref<Node2D> getCurrentView() const;
	
protected:
	virtual void init() override;

private:
	ref<TopBar> m_topBar;
	ref<Node2D> m_current;
};

template<class T>
void MainView::switchView()
{
	auto k = nb::getMilliseconds();
	static_assert(std::is_base_of<nb::Node2D, T>::value, "[T] must be Node2D type or it's derived type.");

	auto curType = rttr::type::get(m_current);
	if (rttr::type::get<T>() == curType)
		return;

	m_current = createRef<T>();
	m_root->clearChildren();
	m_root->addChild(m_current);
	m_root->addChild(m_topBar);
	Log::info("MainView::switchView to {} cost {} ms", rttr::type::get<T>().get_name().data(), nb::getMilliseconds() - k);
}

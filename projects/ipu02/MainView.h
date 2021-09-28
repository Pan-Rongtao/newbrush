#pragma once
#include "../Common.h"

using namespace nb;

class MainView : public ViewBase
{
public:
	static MainView *get();

	template<class T>
	void switchView();
	
protected:
	virtual void init() override;

private:
	ref<Node2D> m_current;
};

template<class T>
void MainView::switchView()
{
	static_assert(std::is_base_of<nb::Node2D, T>::value, "[T] must be Node2D type or it's derived type.");

	auto curType = rttr::type::get(m_current);
	if (rttr::type::get<T>() == curType)
		return;

	m_current = createRef<T>();
	m_root->clearChildren();
	m_root->addChild(m_current);
}

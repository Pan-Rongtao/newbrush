#pragma once
#include "../Common.h"
#include "ModelView.h"
#include "DIYView.h"
#include "SelectorView.h"
#include "HomeView.h"

using namespace nb;

enum class ViewE
{
	Home,
	Selector,
	DIY,
};

class MainView : public ViewBase
{
public:
	virtual void init() override;

	static MainView *get();

	void switchView(ViewE view);

public:
	ref<HomeView> homeNode;
	ref<SelectorView> selectNode;
	ref<DIYView> diyNode;
	ref<ModelView> modelNode;
	ViewE m_curView;
};
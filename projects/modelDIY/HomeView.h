#pragma once
#include "../Common.h"

class HomeView : public Node2D
{
public:
	HomeView();

private:
	void onBtnClick(const EventArgs &e);

	ref<Button> m_area;
};
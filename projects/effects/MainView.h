#pragma once
#include "../Common.h"

class MainView : public ViewBase
{
public:
	virtual void init() override;

	void onKey(const KeyEventArgs &e);
	void onTouch(const TouchEventArgs &e);
};
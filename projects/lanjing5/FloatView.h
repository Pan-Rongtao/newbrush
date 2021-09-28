#pragma once
#include "../Common.h"

class FloatView : public ViewBase
{
public:
	virtual void init() override;
	virtual void onDataChanged(const std::string &path, const var &value) override;

private:
	void onTouch(const TouchEventArgs & e);
	void onKey(const KeyEventArgs &e);

	bool m_pressed{ false };
	Point m_pressedPoint;
	ref<Button> m_area;
};
#pragma once
#include "../Common.h"

class CarBrowser : public ViewBase
{
public:
	virtual void init() override;
	virtual void onDataChanged(const std::string &path, const var &value) override;

	void load(const std::string &path);

private:
	ref<DataObject> buildData();
	void binding();
	void onTouch(const TouchEventArgs &e);
	void onScroll(const ScrollEventArgs &e);
	void onKey(const KeyEventArgs &e);
	void onDrop(const DropEventArgs &e);

	Point m_pressedPoint;
	bool m_pressed{ false };
	ref<Scene> m_scene;
	ColorAnimationUsingKeyFrames m_lightAnimation;
};
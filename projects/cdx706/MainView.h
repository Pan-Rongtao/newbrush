#pragma once
#include "../Common.h"
#include "ECO.h"
#include "Normal.h"
#include "Sport.h"

using namespace nb;

enum class DrivingMode
{
	None,
	Eco,
	Normal,
	Sport,
};

class MainView : public ViewBase
{
public:
	virtual void init() override;

	static float getAngleForTime();

	static bool isInCircle(float x, float y, float circleX, float circleY, float r);
	static float getAngle(float x, float y, float centerX, float centerY);

private:
	void onKey(const KeyEventArgs &e);
#ifdef WIN32
	void onTouch(const TouchEventArgs &e);
#endif // Win32


	void switchDrivingMode(DrivingMode mode);

	ref<DataObject> buildData();

	ref<Node2D> m_ecoNode;
	ref<Node2D> m_normalNode;
	ref<Node2D> m_sportNode;
	DrivingMode m_mode{ DrivingMode::None };
};

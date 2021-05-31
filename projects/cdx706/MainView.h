#pragma once
#include "../Common.h"
#include "ECO.h"
#include "Normal.h"

using namespace nb;

enum class DrivingModeE
{
	none,
	eco,
	normal,
	sport,
};

class MainView : public ViewBase
{
public:
	virtual void init() override;

private:
	void onKey(const KeyEventArgs &e);
	void switchDrivingMode(DrivingModeE mode);

	ref<Node2D> m_ecoNode;
	ref<Node2D> m_normalNode;
	ref<Node2D> m_sportNode;
	DrivingModeE m_mode{ DrivingModeE::none };
};

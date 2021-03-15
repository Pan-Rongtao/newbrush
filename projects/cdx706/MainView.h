#include "newbrush/Application.h"
#include "newbrush/Node2D.h"
#include "newbrush/Controls.h"
#include "../Common.h"
#include "ECO.h"

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
	virtual ref<Node> getRoot() override;

private:
	void switchDrivingMode(DrivingModeE mode);

	ref<Node2D> m_root;
	ref<Node2D> m_ecoNode;
	ref<Node2D> m_normalNode;
	ref<Node2D> m_sportNode;
	DrivingModeE m_mode{ DrivingModeE::none };
};

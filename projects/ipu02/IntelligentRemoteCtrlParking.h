#pragma once
#include "newbrush/Node2D.h"
#include "newbrush/Components.h"
#include "newbrush/Font.h"
#include "newbrush/UserControl.h"

namespace nb {

class IntelligentRemoteCtrlParking;
typedef ref<IntelligentRemoteCtrlParking> IntelligentRemoteCtrlParkingRef;
class NB_API IntelligentRemoteCtrlParking : public Node2D
{
public:

public:
	IntelligentRemoteCtrlParking();
	virtual ~IntelligentRemoteCtrlParking();

	void onEnterMenu();
	void onExitMenu();

	void onFreshMenu(int id);

protected:
	//virtual void onTouch(const TouchEventArgs &e);
	
private:
	void onTick(const EventArgs & e);

private:
	bool m_bEnterState;
	Timer m_timerAutoParking;
	ref<Button> m_BtnParkingRightHor3;
};
}

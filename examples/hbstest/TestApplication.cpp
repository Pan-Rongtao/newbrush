#include "TestApplication.h"
#include "WrapPanelTestPage.h"
#include "StackPanelTestPage.h"
#include "PointAnimationTestPage.h"
#include "ColorAnimationTestPage.h"
#include "ScrollCtrlerTestPage.h"
#include "SliderTestPage.h"
#include "ButtonTestPage.h"


TestApplication::TestApplication(void)
{
}

TestApplication::~TestApplication(void)
{
}

void TestApplication::OnInit()
{
	//WrapPanelTestPage *p = new WrapPanelTestPage();
	//ScrollCtrlerTestPage *p = new ScrollCtrlerTestPage();
	//SliderTestPage *p = new SliderTestPage();
	ButtonTestPage *p = new ButtonTestPage();
	GetGuiWindow()->SetPage(p);
}

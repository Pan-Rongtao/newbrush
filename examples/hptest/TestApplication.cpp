#include "TestApplication.h"
#include "CommonPage.h"
#include "UseControlTestPage.h"
#include "ControlTemplateTestPage.h"
#include "AnimationPage.h"
#include "GridPage.h"
#include "ScrollViewerPage.h"
#include "VideoPage.h"
#include "ListPage.h"

#include "../../../Include/Gui/Matrix4x4.h"

TestApplication::TestApplication(void)
{
}

TestApplication::~TestApplication(void)
{
}

void TestApplication::OnInit()
{
//	nb::Media::Matrix4x4 m;
//	nb::Media::Matrix4x4 m1;

//	m = m*m1;

	GetGuiWindow()->SetPage(new CommonPage());
//	GetGuiWindow()->SetPage(new UseControlTestPage());
//	GetGuiWindow()->SetPage(new ControlTemplateTestPage());
//	GetGuiWindow()->SetPage(new AnimationPage());
	//GetGuiWindow()->SetPage(new GridPage());
//	GetGuiWindow()->SetPage(new ScrollViewerPage());
//	GetGuiWindow()->SetPage(new VideoPage());
//	GetGuiWindow()->SetPage(new ListPage());
}

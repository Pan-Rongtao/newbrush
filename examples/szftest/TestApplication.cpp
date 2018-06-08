#include "TestApplication.h"
#include "AnimationTestPage.h"

TestApplication::TestApplication(void)
{
}

TestApplication::~TestApplication(void)
{
}

void TestApplication::OnInit()
{
	GetGuiWindow()->SetPage(new AnimationTestPage());
}
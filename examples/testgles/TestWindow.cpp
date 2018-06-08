#include "TestWindow.h"
#include "gles/Display.h"
#include "gles/Egl.h"

#include "core/Exception.h"

using nb::System::SizeI;
using nb::System::PointI;
using nb::System::RectI;
using nb::System::Window;
void TestWindow::Test()
{
	nb::gl::egl::Initialize(nb::gl::egl::Display::Default());
	nb::gl::egl::SetConfigure(nb::gl::egl::Configure::FromSystemRecommend(0));
	m_Window = new Window(200, 200, 800, 480);
	m_Window->SetListener(this);

	m_Window->SetCaption("1111");

	m_Window->SetX(100);
	int x = m_Window->GetX();

	m_Window->SetY(100);
	int y = m_Window->GetY();

	m_Window->SetPos(PointI(100, 100));
	PointI pt = m_Window->GetPos();

	m_Window->SetWidth(200);
	int w = m_Window->GetWidth();

	m_Window->SetHeight(200);
	int h = m_Window->GetHeight();

	m_Window->SetRect(RectI(200, 200, 300, 300));
	RectI rc = m_Window->GetRect();

	m_Window->SetSize(SizeI(800, 480));
	SizeI sz = m_Window->GetSize();

//	m_Window->SetPos(PointI(0, 0));
	while(1) 
	{
//		m_Window->Peek();
		m_Window->Pending();
	}
}

void TestWindow::OnPrimaryAction(PrimaryAction action)
{
	printf("TestWindow::OnPrimaryAction[%d]\r\n", action);
}

void TestWindow::OnResize(int width, int height)
{
	printf("TestWindow::OnResize--width[%d], height[%d]\r\n", width, height);
}

void TestWindow::OnPointerAction(PointerAction action, int x, int y)
{
	printf("TestWindow::OnPointerAction--action[%d], x[%d], y[%d]\r\n", action, x, y);
}
void TestWindow::OnKeyAction(KeyAction action, KeyCode key, int mask)
{
	printf("TestWindow::OnKeyAction---action[%d], key[%d],mask[%d]\r\n", action, key, mask);
}

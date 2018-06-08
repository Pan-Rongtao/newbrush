#include "gles/Application.h"
#include "gles/Egl.h"
#include <GLES2/gl2.h>
#include "system/Singleton.h"
#include "system/Platform.h"
#include "BatchingsDrawcalls.h"
#include "gles/Window.h"
#include "EglMaster.h"

using nb::gl::egl::Window;
using nb::gl::egl::Display;
using nb::gl::egl::Configure;
using nb::gl::egl::Context;
using nb::gl::egl::WindowSurface;
using nb::gl::egl::WindowMaster;
using nb::gl::egl::ContextMaster;
using nb::gl::egl::SurfacesMaster;
using nb::gl::Gles::Application;

Application::Application()
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	Initialize();
}

Application::~Application()
{
}

void Application::Run()
{
	InitializeOverride();
//	glViewport(0, 0, 800, 480);
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);

	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		PreRenderOverride();
		Render();
		PostRenderOverride();
		
		for(int i = 0; i != SurfacesMaster::GetCount(); ++i)
			nb::gl::egl::SwapBuffers(SurfacesMaster::At(i));

		for(int i = 0; i != WindowMaster::GetCount(); ++i)
			WindowMaster::At(i)->Pending();

		IdledOverride();
	}
}

void Application::InitializeOverride()
{
}

void Application::PreRenderOverride()
{
}

void Application::PostRenderOverride()
{
}

void Application::IdledOverride()
{
}

void Application::Render()
{
	static int frames = 0;
	static UInt64 tick = nb::System::Platform::GetTickCount();
	BatchingsDrawcalls *bd = nb::System::Singleton<BatchingsDrawcalls>::Current();
	bd->DoBatchingsDrawcalls();
	++frames;
	UInt64 tick1 = nb::System::Platform::GetTickCount();
	if(tick1 - tick >= 2000)
	{
		float fps = frames * 1000.0f / (tick1 - tick);
		frames = 0;
		tick = tick1;
		printf("FPS[%.2f]; Batching count[%d]; Drawcalls[%d], Objects[%d], saved by batching[%d]\r\n", fps, bd->GetBatchingCount(), bd->GetBatchingCount(), bd->GetRenderObjectCount(), bd->GetRenderObjectCount() - bd->GetBatchingCount());
	}
}

void Application::Initialize()
{
	//≈‰÷√display
	nb::gl::egl::Initialize(Display::Default());

	//≈‰÷√configure

	// π”√Configure((int *)NULL)ø™∆Ù…Ó∂»÷°¬ ΩµµÕ∫‹∂‡
	nb::gl::egl::SetConfigure(Configure::FromSystemRecommend(0)/*Configure((int *)NULL)*/);

	//≈‰÷√Contexts
	//ContextMaster::CreateContex(nb::gl::egl::GetCurrentConfigure());

	//≈‰÷√Windows

	//≈‰÷√Surfaces
}

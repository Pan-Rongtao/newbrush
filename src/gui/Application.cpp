#include "gui/Application.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "WindowCollections.h"
#include "gles/Egl.h"
#include "../gles/EglMaster.h"
#include "core/Log.h"
#include <GLES2/gl2.h>
#include "gles/Window.h"

using namespace nb;
using namespace nb::gui;

Application *Application::g_app = nullptr;
Application::Application(std::shared_ptr<gl::Display> display, std::shared_ptr<gl::Configure> configure)
{
	if (g_app)
		nbThrowException(std::logic_error, "create tow application");

	//初始化GL，注意，使用Configure((int *)nullptr)开启深度帧率降低很多
	if (!display)	display = std::make_shared<nb::gl::Display>(nb::gl::Display::defaultx());
	nb::gl::initialize(display);
	if (!configure)	configure = std::make_shared<nb::gl::Configure>(nb::gl::Configure::fromSystemRecommend(0))/*Configure((int *)nullptr)*/;
	nb::gl::setConfigure(configure);
	g_app = this;
}

Application::~Application()
{
}

Application *Application::current()
{
	return g_app;
}

int Application::run()
{
	try 
	{
		for (auto w : WindowCollections::Windows)
		{
			w->updateLayout();
		}

		glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Timer::driveInLoop();
			render();

			for (auto const &w : gl::EglMaster::windows())
				w->pending();

			for (auto const &ws : gl::EglMaster::windowSurfaces())
				gl::swapBuffers(ws);
		}
	}
	catch (std::exception &e)
	{
		printf("exception:%s\r\n", e.what());
	}
	catch(...)
	{
		printf("other exception\r\n");
	}
	return 1;
}

void Application::render()
{
	static int frames = 0;
	static uint64_t k = nb::getTickCount();
	for (auto const &context : gl::EglMaster::contexts())
		context->draw();

	++frames;
	uint64_t kk = nb::getTickCount();
	if (kk - k >= 2000)
	{
		float fps = frames * 1000.0f / (kk - k);
		frames = 0;
		k = kk;
		Log::info("fps:%.2f", fps);
	}
}

#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "../../src/rpc-helper/RpcService.h"
#include "newbrush/core/Log.h"

using namespace nb;

int main(int argc, char **argv)
{
	auto x = sizeof(Object);
	Application app;

	RpcService rpc("127.0.0.1:8888");
	rpc.startup();
	Log::info("rpc service startup, address [%s]", rpc.address().data());

	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "nbplayer");
	w->setValue(Window::NameProperty(), "Window");

	return app.run(argc, argv);

}
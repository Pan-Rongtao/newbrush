#include "newbrush/Application.h"
#include "RpcHelper.h"
#include "newbrush/Log.h"

using namespace nb;

int main(int argc, char **argv)
{
	Application app;

	auto window = createRef<Window>();
	window->setTitle("player");
	//window->setTopmost(true);
	window->setWindowsStyle(WindowStyleE::None);

	RpcHelper::starup();
	Log::info("rcp-helper startup success.");

	return app.run(argc, argv);
}
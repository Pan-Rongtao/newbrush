#include "MyView.h"
#include "newbrush/Log.h"

using namespace nb;

int main(int argc, char **argv)
{
	try {
		Application app;

		Window w(1280, 1000);
		w.setTitle("CX620 Power By NewBrush");
		MyView view;
		w.root = view.getRoot();

		return app.run(0, nullptr);
	}
	catch (std::exception &e)
	{
		Log::error("{}", e.what());
	}
}
#include "MainView.h"

using namespace nb;

int main(int argc, char **argv)
{
	Application app;

	Window w(1920, 1000);
	//w.setPosition(0, 0);
	w.setTitle("radarACM Power By NewBrush");
	MainView view;
	w.root = view.m_root;

	return app.run(0, nullptr);
}
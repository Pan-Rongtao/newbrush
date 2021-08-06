#include "catch2/catch.hpp"
#include "newbrush/Application.h"
#include "newbrush/Log.h"
#include "newbrush/Font.h"
#include "newbrush/Controls.h"

using namespace nb;

TEST_CASE("TestGlobalProperties", "[TestGlobalProperties]")
{
	bool b = addGlobalProperty<int>("IntProperty", 1);
	b = addGlobalProperty<int>("IntProperty", 1);
}

TEST_CASE("Shader", "[Shader]")
{
	auto x = nb::getStarupMilliseconds();
	auto y = nb::getMilliseconds();
	auto mss = y - x;
}

TEST_CASE("TestTimer", "[TestTimer]")
{
	Timer t(0, true);
	t.Tick += [](const EventArgs &e)
	{
		Log::info("tick");
	};
	t.start();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("Texture2D", "[Texture2D]")
{
	Application app;
	Window w;

	auto tex = createRef<Texture2D>("../resource/radarACM/NumGreen0.png");
	tex->save("222.png");

	app.run(0, nullptr);
}

TEST_CASE("Font", "[Font]")
{
	auto font = FontLibrary::getDefaultFont();
	font->saveTextBitmap("text.png", "OpenGL");
}

TEST_CASE("Log", "[Log]")
{
	Log::info("point={}", Point(1.1f, 1.2f));
	Log::info("point3d={}", Point3D(2.1f, 2.2f, 2.3f));
	Log::info("size={}", Size(3.3f, 3.4f));
	Log::info("rect={}", Rect(4.4f, 4.5f, 4.6f, 4.7f));
	Log::info("color={}", Color(1, 2, 3, 4));
	Log::info("thickness={}", Thickness(0.1f, 0.2f, 0.3f, 0.4f));
	Log::info("timespan={}", -TimeSpan(1, 2, 3, 4, 5, 6));
	DateTime dt = DateTime::current();
	Log::info("date={}", dt.date());
	Log::info("time={}", dt.time());
	Log::info("date={}", dt);
	Log::info("vec2={}", glm::vec2(1.0f, 2.0f));
	Log::info("vec3={}", glm::vec3(1.0f, 2.0f, 3.0f));
	Log::info("vec4={}", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
	Log::info("mat4={}", glm::mat4(1.0f));
}
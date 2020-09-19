#include "newbrush/model/Log.h"
#include "catch2/catch.hpp"
#include "MyScene.h"
#include "simdjson.h"

using namespace nb;
using namespace simdjson;

#define MODULE_NAME		"viewer"
#define TEST_TAG		std::string("[") + MODULE_NAME + "]"

TEST_CASE(TEST_TAG, TEST_TAG)
{
	dom::parser parser;
	auto result = parser.load("../etc/cfg.json");
	if (result.second)
	{
		Log::info("error while parsing cfg file, error={}, error_message={}", result.second, error_message(result.second));
		return;
	}

	std::string_view path;
	double scale;
	int64_t width, height;
	auto root = parser.doc.root();

	auto error = result["Path"].get(path); if (error) Log::error("json has no field [Path] as string");
	error = result["Scale"].get(scale); if (error) Log::error("json has no field [Scale] as int");
	error = result["Width"].get(width); if (error) Log::error("json has no field [Width] as float");
	error = result["Height"].get(height); if (error) Log::error("json has no field [Height] as float");

	MyScene sc((int)width, (int)height);
	sc.load(path.data(), (float)scale);
	sc.loopDraw();
}
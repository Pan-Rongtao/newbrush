#include "catch2/catch.hpp"
#include "newbrush/Log.h"
#include "Tr.h"
#include "newbrush/Helper.h"

using namespace nb;

TEST_CASE("PRT_1", "[PRT_1]")
{
	Log::info("prt test 1");
	Log::info("prt test 2");
	Log::info("prt test 3");
	Log::info("prt test 4");
	Log::info("prt test 5");
	//auto s = fmt::format("{}", fmt::join(v, ","));
	Log::info("vector={}", std::vector<int>{ 1, 2, 3 });
	Log::info("vector={}", std::vector<float>{ 1.0f, 2.0f, 3.0f });
	Log::info("vector={}", std::vector<std::string>{ "1", "2", "3" });

}

TEST_CASE("TR", "[TR]")
{
	for (auto row = 0; row < TR_ID_MAX; ++row)
	{
		for (auto col = 0; col < TR_LANGUAGE_COUNT; ++col)
		{
			setLanguage(col);
			auto s = TR(row);
			printf("%s	", s);
		}
		printf("\n");
	}
}

TEST_CASE("SystemInfo", "[SystemInfo]")
{
	SystemHelper::getMemoryInfo();
	SystemHelper::getCpu();
}
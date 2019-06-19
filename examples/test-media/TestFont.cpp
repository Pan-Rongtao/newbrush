#include "TestFont.h"

void TestFont::test()
{
	for (auto font : Fonts::systemFonts())
	{
		printf("[%s]: %s\n", font.second->path().data(), font.first.data());
	}
}

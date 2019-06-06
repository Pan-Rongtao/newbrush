#include "TestFont.h"

#define RESOURCE_DIR	std::string("../../../resource/")
void TestFont::test()
{
	Font font(RESOURCE_DIR + "STKAITI.TTF");
	font.setSize(48);
	int fontSize = font.size();
	auto familyName = font.name();
	printf("familyName:%s\n", familyName.data());
}

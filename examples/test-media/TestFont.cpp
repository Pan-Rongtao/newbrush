#include "TestFont.h"

void TestFont::test()
{
	Font font("../../resource/STKAITI.TTF");
	font.setSize(48);
	int fontSize = font.size();
	auto familyName = font.name();
	printf("familyName:%s\n", familyName.data());
}

#include "TestFamilyTypeface.h"

#define RESOURCE_DIR	std::string("../../../resource/")
void TestFamilyTypeface::test()
{
	FamilyTypeface face(RESOURCE_DIR + "STKAITI.TTF");
	face.setFontSize(48);
	int fontSize = face.getFontSize();
	auto familyName = face.getFontName();
	printf("familyName:%s\n", familyName.data());
}

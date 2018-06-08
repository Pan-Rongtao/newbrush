#include "TestTexture2D.h"
#include "gles/Texture2D.h"

using namespace nb::gl::Gles;
TestTexture2D::TestTexture2D(void)
{
}

TestTexture2D::~TestTexture2D(void)
{
}

void TestTexture2D::Test()
{
//	Texture2D texture2d;
	int maxWidth = Texture2D::MaxWidthSupported();
	int maxHeight = Texture2D::MaxHeightSupported();
}
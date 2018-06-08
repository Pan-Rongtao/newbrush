#include "TestModel.h"
#include "gles/Quadrangle.h"
#include "system/Platform.h"
#include "math/Vec3.h"

using nb::gl::Gles::Model;
using nb::gl::Gles::Quadrangle;
using namespace nb::System;
void TestModel::Test()
{
	Model *model = new Model(4, Model::Vertex_Attribute_Position | Model::Vertex_Attribute_Color | Model::Vertex_Attribute_TextureCoordinate);
	int k = nb::System::Platform::GetTickCount();
	model->SetPositionAt(0, nb::Math::Vec3(0.0, 0.0, 0.0));
	model->SetPositionAt(1, nb::Math::Vec3(1.0, 0.0, 0.0));
	model->SetPositionAt(2, nb::Math::Vec3(0.0, 1.0, 0.0));
	model->SetPositionAt(3, nb::Math::Vec3(0.0, 0.0, 1.0));
	model->UnifyColor(nb::Math::Vec4(1.0, 1.0, 1.0, 1.0));
	printf("cost=%d\r\n", nb::System::Platform::GetTickCount() - k);

	while(1) {}
}
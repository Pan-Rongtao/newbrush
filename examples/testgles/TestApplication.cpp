#include "TestApplication.h"
#include "gles/Egl.h"
#include "math/Vec4.h"
#include "gles/Material.h"
#include "gles/Texture2D.h"
#include "gles/Program.h"
#include "gles/Shader.h"
#include "gles/RenderObject.h"
#include "gles/Model.h"
#include "gles/Quadrangle.h"
#include "gles/Triangle.h"
#include "gles/Ellipse.h"
#include "gles/Cube.h"
#include "gles/Sphere.h"
#include "gles/Window.h"

using nb::gl::Gles::Application;
using nb::gl::egl::Display;
using nb::gl::egl::Configure;
using nb::gl::egl::Surface;
using nb::gl::egl::Context;
using nb::gl::egl::Window;
using nb::gl::egl::WindowSurface;
using nb::gl::Gles::Program;
using nb::gl::Gles::Shader;
using nb::gl::Gles::Model;
using nb::gl::Gles::Material;
using nb::gl::Gles::Texture2D;
using nb::gl::Gles::Triangle;
using nb::gl::Gles::Quadrangle;
using nb::gl::Gles::Ellipse;
using nb::gl::Gles::Cube;
using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Painter;
using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::Math::Vec4;
MyApplication::MyApplication()
: m_Painter(m_Context)
{


}

void MyApplication::DrawTriangles()
{
	float step = 0.01;
	int objectCount = 300;
	for(int i = 0; i != objectCount; ++i)
	{
		Triangle *tri = new Triangle(Vec2(0.5 + step * i, 0.5), Vec2(0.5 + step * i, 0.0), Vec2(0.0 + step * i, 0.0), Vec4(0.0, 0.0, 1.0, 1.0));
		RenderObject *ro = new RenderObject(tri, new Material(Program::Common()));
		m_RenderObjects.push_back(ro);
		m_Painter.Paint(ro);
	}
}

void MyApplication::DrawQuadrangles()
{
	float step = 20;
	int objectCount = 100;
	Texture2D *texture = new Texture2D("f:/download/c.jpg");
	for(int i = 0; i != objectCount; ++i)
	{
		Quadrangle *quad = new nb::gl::Gles::Quadrangle(Vec2(0 + step * i, 0 + step * i), Vec2(100 + step * i, 0 + step * i), Vec2(100 + step * i, 100 + step * i), Vec2(0 + step * i, 100 + step * i),
			Vec4(1.0, 0.0, 0.0, 1.0), Vec4(0.0, 1.0, 0.0, 1.0), Vec4(0.0, 0.0, 1.0, 1.0), Vec4(0.0, 0.0, 0.0, 1.0));
		quad->SetTextureCoordinateAt(0, Vec2(0.0, 1.0));
		quad->SetTextureCoordinateAt(1, Vec2(1.0, 1.0));
		quad->SetTextureCoordinateAt(2, Vec2(1.0, 0.0));
		quad->SetTextureCoordinateAt(3, Vec2(0.0, 0.0));
	//	RenderObject *ro = new RenderObject(quad, new Material(Program::Common(), texture));
		RenderObject *ro = new RenderObject(quad, new Material(Program::Common()));
		m_Painter.Paint(ro);
		m_RenderObjects.push_back(ro);

	}
	m_RenderObjects[0]->SetRenderMode(RenderObject::RenderMode_Color);
	m_RenderObjects[0]->GetModel()->UnifyColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	m_RenderObjects[1]->GetModel()->UnifyColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	m_RenderObjects[1]->SetRenderMode(RenderObject::RenderMode_Mapping);
//	m_RenderObjects[1]->GetMaterial()->SetTexture(new Texture2D("f:/pics/75.jpg"));
//	nb::Math::Matrix4x4 modelMat = m_RenderObjects[0]->GetModel()->GetMatrix().TranslateX(200).TranslateY(100);
//	m_RenderObjects[1]->GetModel()->SetMatrix(modelMat);

}

void MyApplication::DrawEllipses()
{
	Ellipse *epse = new Ellipse(nb::Math::Vec2(200.0f, 200.0f), 100.25f, 100.25f);
	epse->UnifyColor(nb::Math::Vec4(0.0, 1.0, 0.0, 1.0));
	RenderObject *ro = new RenderObject(epse, new Material(Program::Common()));
	m_RenderObjects.push_back(ro);
	m_Painter.Paint(ro);
}

void MyApplication::DrawCubes()
{
	Cube *cube = new Cube(Vec3(-0.25f, -0.25f, 0.0f), 0.5f, 0.5f, 0.5f);
	cube->UnifyColor(nb::Math::Vec4(1.0, 0.0, 0.71, 1.0));
	RenderObject *ro = new RenderObject(cube, new Material(Program::Common()));
	m_RenderObjects.push_back(ro);

	m_Painter.Paint(ro);
}

void MyApplication::InitializeOverride()
{
	m_Context = new Context(nb::gl::egl::GetCurrentConfigure());
	Window *window = new Window();
	Surface *surface = new WindowSurface(window->GetWidth(), window->GetHeight(), window->GetWindowHandle());
	nb::gl::egl::MakeCurrent(surface, surface, m_Context);

	DrawQuadrangles();
//	DrawEllipses();
}

void MyApplication::PreRenderOverride()
{
}

MyApplication::~MyApplication()
{
	for(int i = 0; i != m_RenderObjects.size(); ++i)
	{
		delete m_RenderObjects[i]->GetModel();
		delete m_RenderObjects[i];
	}
}

void MyApplication::OnIdledOverride()
{
}

void MyApplication::OnPrimaryAction(PrimaryAction action)
{
	printf("MyApplication::OnPrimaryAction[%d]\r\n", action);
}

void MyApplication::OnResize(int width, int height)
{
	printf("MyApplication::OnResize--width[%d], height[%d]\r\n", width, height);
}

void MyApplication::OnPointerAction(PointerAction action, int x, int y)
{
	printf("MyApplication::OnPointerAction--action[%d], x[%d], y[%d]\r\n", action, x, y);
}
void MyApplication::OnKeyAction(KeyAction action, KeyCode key, int mask)
{
	printf("MyApplication::OnKeyAction---action[%d], key[%d],mask[%d]\r\n", action, key, mask);
}

//////////
void TestApplication::Test()
{
	MyApplication	m_app;
	m_app.Run();
}

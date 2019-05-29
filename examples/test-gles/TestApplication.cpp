#include "TestApplication.h"
#include "gles/Egl.h"
#include "core/Vec4.h"
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
#include "gles/Cubemap.h"
#include "core/Random.h"
#include "gles/Sphere.h"
#include "gles/Storage.h"
#include "gles/Projection.h"

using namespace nb::core;
using namespace nb::gl;
/*	float z = 480.0f / (float)(2 * Tan((22.5f * Pi()) / 180.0f));
Vec3 position(800.0f / 2.0f, 480.0f / 2.0f, -z);
Vec3 target(800.0f / 2.0f, 480.0f / 2.0f, 0.0f);
Vec3 upVec(0.0f, -1.0f, 0.0f);*/
static Vec3 cameraPosition(0.0, 0.0, 3.0);
static Vec3 cameraFront(0.0f, 0.0f, -1.0f);
static Vec3 cameraUp(0.0f, 1.0f, 0.0f);

bool g_Original = false;

MyApplication::MyApplication()
{
	m_timer.setInterval(20);
	m_timer.TickEvent.addHandler(std::bind(&MyApplication::OnTick, this, std::placeholders::_1));
//	m_timer.start();

//objs
	m_context = std::make_shared<Context>(nb::gl::getConfigure());
	m_window = std::make_shared<nb::gl::Window>();
	m_window->setWidth(800);
	m_window->setHeight(480);
	m_window->setTitle("Direction Light");
	m_window->ResizeEvent.addHandler(std::bind(&MyApplication::OnResize, this, std::placeholders::_1));
	m_window->PointerEvent.addHandler(std::bind(&MyApplication::OnPointerAction, this, std::placeholders::_1));
	m_window->KeyEvent.addHandler(std::bind(&MyApplication::OnKeyAction, this, std::placeholders::_1));
	m_surface = std::make_shared<WindowSurface>(m_window->width(), m_window->height(), m_window->handle());

	nb::gl::Window::ResizeArgs args;
	args.width = m_window->width();
	args.height = m_window->height();
	OnResize(args);

	DrawTriangles(g_Original);
	DrawQuadrangles(g_Original);
	DrawEllipses(g_Original);
	DrawCubes(g_Original);
	DrawSphere(g_Original);
	drawPhone(g_Original);
	//	drawModel(g_Original);
}

void MyApplication::DrawTriangles(bool bOrigin)
{
	int objectCount = 1;
	for(int i = 0; i != objectCount; ++i)
	{
		std::shared_ptr<Triangle> tri;
		if (bOrigin)
		{
			float step = 0.3f;
			tri = std::make_shared<Triangle>(Vec2(-1.5f + step * i, 1.5f), Vec2(-1.7f + step * i, -0.3f), Vec2(0.4f + step * i, -0.3f), Vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}
		else
		{
			float step = 50.0f;
			tri = std::make_shared<Triangle>(Vec2(200.0f + step * i, 50.0f), Vec2(100 + step * i, 200.0f), Vec2(300.0f + step * i, 200.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}
		tri->mesh(0).setTextureCoordinateAt(0, Vec2(0.5f, 1.0f));
		tri->mesh(0).setTextureCoordinateAt(1, Vec2(0.0f, 0.0f));
		tri->mesh(0).setTextureCoordinateAt(2, Vec2(1.0f, 0.0f));
		tri->mesh(0).setColorAt(0, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		tri->mesh(0).setColorAt(1, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
		tri->mesh(0).setColorAt(2, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
		std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(tri, std::make_shared<Material>(Programs::primitive()));
		ro->storage()->insert("unif_colorMode", 0);
		ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/pics/cubemap/1/front.png"));
		m_context->queue(ro);
	}
}

void MyApplication::DrawQuadrangles(bool bOrigin)
{
	float step;
	int objectCount = 2;
	for(int i = 0; i != objectCount; ++i)
	{
		std::shared_ptr<Quadrangle> quad;
		Vec2 p0, p1, p2, p3;
		if (bOrigin)
		{
			step = 0.3f;
			p0 = Vec2(-0.5f + step * i, -0.5f + step * i);
			p1 = Vec2(0.5f + step * i, -0.5f + step * i);
			p2 = Vec2(0.5f + step * i, 0.5f + step * i);
			p3 = Vec2(-0.5f + step * i, 0.5f + step * i);
		}
		else
		{
			step = 100;
			p0 = Vec2(-100 + step * i, 100 + step * i);
			p1 = Vec2(100 + step * i, 100 + step * i);
			p2 = Vec2(100 + step * i, -100 + step * i);
			p3 = Vec2(-100 + step * i, -100 + step * i);
		}
		quad = std::make_shared<Quadrangle>(p0, p1, p2, p3);
		std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::primitive()));
		m_context->queue(ro);
		if (i == 0)
		{
			ro->storage()->insert("unif_colorMode", 1);
			//ro->setRenderable(false);
			ro->model()->mesh(0).unifyColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
		}
		if (i == 1)
		{
			ro->storage()->insert("unif_colorMode", 0);
			ro->model()->mesh(0).unifyColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
			ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/Pics/5.jpg"));
		}
		if (i == 2)
		{
			ro->storage()->insert("unif_colorMode", 1);
		//	ro->setRenderable(false);
		}
	}

}

void MyApplication::DrawEllipses(bool bOrigin)
{
	std::shared_ptr<Ellipse> epse;
	if(bOrigin)
		epse = std::make_shared<Ellipse>(Vec2(-0.5f, -.5f), 0.25f, 0.25f, bOrigin);
	else
		epse = std::make_shared<Ellipse>(Vec2(100.0f, 400.0f), 50.0f, 50.0f, bOrigin);
	epse->mesh(0).unifyColor(Vec4(1.0f, 0.0f, 0.0f, 0.0f));
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(epse, std::make_shared<Material>(Programs::primitive()));
	ro->storage()->insert("unif_colorMode", 0);
	ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/Pics/5.jpg"));
	m_context->queue(ro);
}

void MyApplication::DrawCubes(bool bOrigin)
{
	std::shared_ptr<Cube> cube;
	if (bOrigin)
	{
		float w = 0.7f;
		cube = std::make_shared<Cube>(Vec3(0.0f, 0.0f, 0.0f), w, w, w);
	}
	else
	{
		float w = 100;
		cube = std::make_shared<Cube>(Vec3(400.0f, 240.0f, 0.0f), w, w, w);
	}
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(cube, std::make_shared<Material>(Programs::cube()));

	m_context->queue(ro);
	std::shared_ptr<Cubemap> cm = std::make_shared<Cubemap>();
	std::vector<std::string> paths;
	paths.push_back("e:/pics/cubemap/2/right.jpg");
	paths.push_back("e:/pics/cubemap/2/left.jpg");
	paths.push_back("e:/pics/cubemap/2/bottom.jpg");
	paths.push_back("e:/pics/cubemap/2/top.jpg");
	paths.push_back("e:/pics/cubemap/2/back.jpg");
	paths.push_back("e:/pics/cubemap/2/front.jpg");
	cm->load(paths);
	ro->material()->textures().push_back(cm);
}

void MyApplication::DrawSphere(bool bOrigin)
{
	std::shared_ptr<Sphere> sp;
	if(bOrigin)
		sp = std::make_shared<Sphere>(Vec3(0.5f, 0.5f, 0.5f), 0.5f, bOrigin);
	else
		sp = std::make_shared<Sphere>(Vec3(600.0f, 200.0f, 0.0f), 100.0f, bOrigin);
	sp->mesh(0).unifyColor(Vec4(1.0f, 0.0, 0.0, 1.0));
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(sp, std::make_shared<Material>(Programs::primitive()));

	ro->storage()->insert("unif_colorMode", 0);
	m_context->queue(ro);
	ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/pics/world4.jpg"));
	//ro->storage()->insert("unif_colorMode", 1);
}

void MyApplication::drawPhone(bool bOrigin)
{
	std::shared_ptr<Cube> quad;
	if (bOrigin)
	{
		float w = 0.5f;
		quad = std::make_shared<Cube>(Vec3(-1.0f, -0.0f, 0.0f), w, w, w);
	}
	else
	{
		float w = 80;
		quad = std::make_shared<Cube>(Vec3(600, 350, 0.0f), w, w, w);
	}
	//	std::shared_ptr<Quadrangle> quad = std::make_shared<Quadrangle>(Vec2(-0.0f, 0.0f), 2.0, 2.0);
	//quad->setTextureCoordinateAt(0, Vec2(0.0, 1.0));
	//quad->setTextureCoordinateAt(1, Vec2(1.0, 1.0));
	//quad->setTextureCoordinateAt(2, Vec2(1.0, 0.0));
	//quad->setTextureCoordinateAt(3, Vec2(0.0, 0.0));
	float f = 0.5773502691896258f;
	quad->mesh(0).setNormalAt(0, Vec3(-f, f, f));
	quad->mesh(0).setNormalAt(1, Vec3(f, f, f));
	quad->mesh(0).setNormalAt(2, Vec3(f, -f, f));
	quad->mesh(0).setNormalAt(3, Vec3(-f, -f, f));
	quad->mesh(0).setNormalAt(4, Vec3(f, f, -f));
	quad->mesh(0).setNormalAt(5, Vec3(-f, f, -f));
	quad->mesh(0).setNormalAt(6, Vec3(-f, -f, -f));
	quad->mesh(0).setNormalAt(7, Vec3(f, -f, -f));
	//	std::shared_ptr<Ellipse> epse = std::make_shared<Ellipse>(Vec2(-0.5f, -.5f), 0.25, 0.25);
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::phong()));
	m_context->queue(ro);
	ro->storage()->insert("viewPos", cameraPosition);
	ro->storage()->insert("material.shininess", 32.0);
	if(bOrigin)
		ro->storage()->insert("light.direction", Vec3(1.0f, -0.0f, 3.0f));
	else
		ro->storage()->insert("light.direction", Vec3(1.0f, -0.0f, -3.0f));
	ro->storage()->insert("light.ambient", Vec3(0.5f, 0.5f, 0.5f));
	ro->storage()->insert("light.diffuse", Vec3(0.4f, 0.4f, 0.4f));
	ro->storage()->insert("light.specular", Vec3(0.5f, 0.5f, 0.5f));
	//	ro->material()->setTexture(std::make_shared<Texture2D>("e:/pics/cubemap/1/front.png"));

	std::shared_ptr<Cubemap> cm = std::make_shared<Cubemap>();
	std::vector<std::string> paths;
	/*	paths.push_back("e:/pics/cubemap/1/left.png");
	paths.push_back("e:/pics/cubemap/1/right.png");
	paths.push_back("e:/pics/cubemap/1/bottom.png");
	paths.push_back("e:/pics/cubemap/1/top.png");
	paths.push_back("e:/pics/cubemap/1/back.png");
	paths.push_back("e:/pics/cubemap/1/front.png");*/
	paths.push_back("e:/pics/cubemap/2/right.jpg");
	paths.push_back("e:/pics/cubemap/2/left.jpg");
	paths.push_back("e:/pics/cubemap/2/bottom.jpg");
	paths.push_back("e:/pics/cubemap/2/top.jpg");
	paths.push_back("e:/pics/cubemap/2/back.jpg");
	paths.push_back("e:/pics/cubemap/2/front.jpg");
	/*	paths.push_back("e:/pics/cubemap/1/right.png");
	paths.push_back("e:/pics/cubemap/1/left.png");
	paths.push_back("e:/pics/cubemap/1/bottom.png");
	paths.push_back("e:/pics/cubemap/1/top.png");
	paths.push_back("e:/pics/cubemap/1/back.png");
	paths.push_back("e:/pics/cubemap/1/front.png");*/
	cm->load(paths);
	ro->material()->textures().push_back(cm);
}

void MyApplication::drawModel(bool bOrigin)
{
	std::shared_ptr<RenderObject> renderer = std::make_shared<RenderObject>(nullptr, std::make_shared<Material>(Programs::primitive()));
	renderer->loadFromFile("e:/model/nanosuit/nanosuit.obj");
	if (bOrigin)
	{
		renderer->model()->scale(0.05f, 0.05f, 0.05f);
	}
	else
	{
		renderer->model()->scale(10, 10, 10);
		renderer->model()->translate(200, 200, 0);
	}
	//model->load("e:/model/test/spider.obj");
	m_context->queue(renderer);
}

void MyApplication::preRender()
{
//	changeColor();
	m_timer.drive();
}

MyApplication::~MyApplication()
{
}

void MyApplication::OnResize(const nb::core::Window::ResizeArgs & args)
{
	printf("MyApplication::OnResize--width[%d], height[%d]\r\n", args.width, args.height);
	nb::gl::getProjection()->perspective(45.0f, (float)args.width / (float)args.height, 0.1f, 10000.0f);
	if (g_Original)
		nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
	else
		nb::gl::getCamera()->lookat2D(args.width, args.height);

	nb::gl::viewport(0, 0, args.width, args.height);
	nb::gl::makeCurrent(m_surface, m_surface, m_context);
}

bool bPress = false;
static int pressX = 0;
static int pressY = 0;
void MyApplication::OnPointerAction(const nb::core::Window::PointerEventArgs & args)
{
	switch (args.action)
	{
	case nb::gl::Window::PointerAction_Down:
		bPress = true;
		pressX = args.x;
		pressY = args.y;
		break;
	case nb::gl::Window::PointerAction_Up:
		bPress = false;
		break;
	case nb::gl::Window::PointerAction_Move:
	{
		for (int i = 0; i != m_context->renderObjectCount(); ++i)
		{
			m_context->renderObject(i)->model()->rotate((float)-(args.x - pressX), 0.0f, 1.0f, 0.0f);
			m_context->renderObject(i)->model()->rotate((float)-(args.y - pressY), 1.0f, 0.0f, 0.0f);
		}
		pressX = args.x;
		pressY = args.y;
		break;
	}
	default:
		break;
	}
}

void MyApplication::OnKeyAction(const nb::core::Window::KeyEventArgs & args)
{
//	printf("MyApplication::OnKeyAction---action[%d], key[%d],mask[%d]\r\n", action, key, mask);
	switch (args.action)
	{
	case nb::gl::Window::KeyAction_Down:
		switch (args.key)
		{
		case nb::gl::Window::VKey_Unknown:
			break;
		case nb::gl::Window::VKey_Esc:
			for (int i = 0; i != m_context->renderObjectCount(); ++i)
				m_context->renderObject(i)->model()->setMatrix(Matrix4x4::identity());
			break;
		case nb::gl::Window::VKey_F1:
		{
			Matrix4x4 mat = Matrix4x4::identity();
			mat.rotateAngleY(60.0);
			mat.scaleX(2);
			mat.translate(0.5, 0, 0);
			m_context->renderObject(0)->model()->setMatrix(mat);
		}
			break;
		case nb::gl::Window::VKey_F2:
			break;
		case nb::gl::Window::VKey_F3:
			break;
		case nb::gl::Window::VKey_F4:
			break;
		case nb::gl::Window::VKey_F5:
			break;
		case nb::gl::Window::VKey_F6:
			break;
		case nb::gl::Window::VKey_F7:
			break;
		case nb::gl::Window::VKey_F8:
			break;
		case nb::gl::Window::VKey_F9:
			break;
		case nb::gl::Window::VKey_F10:
			break;
		case nb::gl::Window::VKey_F11:
			break;
		case nb::gl::Window::VKey_F12:
			break;
		case nb::gl::Window::VKey_Space:
			break;
		case nb::gl::Window::VKey_A:
			m_context->renderObject(0)->model()->rotate(10, 0, 1, 0);
			break;
		case nb::gl::Window::VKey_D:
			m_context->renderObject(0)->model()->rotate(-10, 0, 1, 0);
			break;
		case nb::gl::Window::VKey_W:
			m_context->renderObject(0)->model()->rotate(10, 1, 0, 0);
			break;
		case nb::gl::Window::VKey_S:
			m_context->renderObject(0)->model()->rotate(-10, 1, 0, 0);
			break;
		case nb::gl::Window::VKey_B:
			break;
		case nb::gl::Window::VKey_C:
			break;
		case nb::gl::Window::VKey_E:
			break;
		case nb::gl::Window::VKey_F:
			break;
		case nb::gl::Window::VKey_G:
			break;
		case nb::gl::Window::VKey_H:
			break;
		case nb::gl::Window::VKey_I:
		{
			cameraPosition += 0.1f * cameraFront;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
			printf("z=%.1f\r\n", cameraPosition.z());
		}
			break;
		case nb::gl::Window::VKey_J:
		{
			Vec3 x = cameraFront.crossProduct(cameraUp) * 0.1f;
			cameraPosition -= x;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
		}
			break;
		case nb::gl::Window::VKey_K:
		{
			cameraPosition -= 0.1f * cameraFront;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
			printf("z=%.1f\r\n", cameraPosition.z());
		}
			break;
		case nb::gl::Window::VKey_L:
		{
			Vec3 x = cameraFront.crossProduct(cameraUp) * 0.1f;
			cameraPosition += x;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
		}
			break;
		case nb::gl::Window::VKey_M:
			break;
		case nb::gl::Window::VKey_N:
			break;
		case nb::gl::Window::VKey_O:
			break;
		case nb::gl::Window::VKey_P:
			break;
		case nb::gl::Window::VKey_Q:
			break;
		case nb::gl::Window::VKey_R:
			m_context->renderObject(0)->model()->rotate(-10, 0, 0, 1);
			break;
		case nb::gl::Window::VKey_T:
			m_context->renderObject(0)->model()->rotate(10, 0, 0, 1);
			break;
		case nb::gl::Window::VKey_U:
			break;
		case nb::gl::Window::VKey_V:
			break;
		case nb::gl::Window::VKey_X:
			break;
		case nb::gl::Window::VKey_Y:
			break;
		case nb::gl::Window::VKey_Z:
			break;
		case nb::gl::Window::VKey_Left:
			m_context->renderObject(0)->model()->translate(-0.01f, 0, 0);
			break;
		case nb::gl::Window::VKey_Up:
			m_context->renderObject(0)->model()->translate(0, 0.01f, 0);
			break;
		case nb::gl::Window::VKey_Right:
			m_context->renderObject(0)->model()->translate(0.01f, 0, 0);
			break;
		case nb::gl::Window::VKey_Down:
			m_context->renderObject(0)->model()->translate(0, -0.01f, 0);
			break;
		case nb::gl::Window::VKey_Add:
			m_context->renderObject(0)->model()->scale(2, 2, 2);
			break;
		case nb::gl::Window::VKey_Sub:
			m_context->renderObject(0)->model()->scale(0.5, 0.5, 0.5);
			break;
		default:
			break;
		}
		break;
	case nb::gl::Window::KeyAction_Up:
		break;
	case nb::gl::Window::KeyAction_LongPress:
		break;
	default:
		break;
	}
}

void MyApplication::OnTick(const Timer::TickArgs & param)
{
	for (int i = 0; i != m_context->renderObjectCount(); ++i)
	{
		m_context->renderObject(i)->model()->rotate(0.5, 0, 1, 0);
	}
}

//////////
void TestApplication::test()
{
	MyApplication app;
	app.run();
}

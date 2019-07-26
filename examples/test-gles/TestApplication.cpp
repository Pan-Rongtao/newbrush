#include "TestApplication.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gles/Egl.h"
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
#include "gles/TextureCubemap.h"
#include "core/Random.h"
#include "gles/Storage.h"
#include "gles/Projection.h"
#include "gles/GlyphFactory.h"
#include "gles/GlyphBunch.h"
#include "gles/Line.h"
#include "gles/Polyline.h"

using namespace nb::core;
using namespace nb::gl;
/*	
float z = 480.0f / (float)(2 * Tan((22.5f * Pi()) / 180.0f));
Vec3 position(800.0f / 2.0f, 480.0f / 2.0f, -z);
Vec3 target(800.0f / 2.0f, 480.0f / 2.0f, 0.0f);
Vec3 upVec(0.0f, -1.0f, 0.0f);
*/
static glm::vec3 cameraPosition(0.0, 0.0, 3.0);
static glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

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
	m_window->setTitle("newbrush");
	m_window->ResizeEvent.addHandler(std::bind(&MyApplication::OnResize, this, std::placeholders::_1));
	m_window->PointerEvent.addHandler(std::bind(&MyApplication::OnPointerAction, this, std::placeholders::_1));
	m_window->KeyEvent.addHandler(std::bind(&MyApplication::OnKeyAction, this, std::placeholders::_1));
	m_surface = std::make_shared<WindowSurface>(m_window->width(), m_window->height(), m_window->handle());
	nb::gl::makeCurrent(m_surface, m_surface, m_context);

	nb::gl::Window::ResizeArgs args;
	args.width = m_window->width();
	args.height = m_window->height();
	OnResize(args);
	
//	drawLines();
//	drawPolylines();
	drawTriangles();
	drawQuadrangles();
//	drawEllipses();
//	drawCubes();
//	drawSphere();
//	drawPhone();
	//	drawModel();
//	drawGlyph();
//	drawGlyphBunch();
}

void MyApplication::drawLines()
{
	auto line = std::make_shared<Line>(0.0f, 300.0f, 200.f, 300.0f);
	auto ro = std::make_shared<RenderObject>(line, std::make_shared<Material>(Programs::primitive()));
	ro->storage()->set(Program::nbColorModeLocationStr, 1);
	line->meshes()[0].vertexs()[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
	line->meshes()[0].vertexs()[1].color = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_context->queue(ro);
}

void MyApplication::drawPolylines()
{
	auto polyline = std::make_shared<Polyline>(std::vector<glm::vec2>{glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec2(50.0f, 100.0f), glm::vec2(200.0f, 150.0f), glm::vec2(300.0f, 200.0f), glm::vec2(400.0f, 0.0f)});
	auto ro = std::make_shared<RenderObject>(polyline, std::make_shared<Material>(Programs::primitive()));
	ro->storage()->set(Program::nbColorModeLocationStr, 1);
	polyline->meshes()[0].vertexs()[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
	polyline->meshes()[0].vertexs()[1].color = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_context->queue(ro);
}

void MyApplication::drawTriangles()
{
	int objectCount = 1;
	for(int i = 0; i != objectCount; ++i)
	{
		std::shared_ptr<Triangle> tri;
		if (g_Original)
		{
			float step = 0.3f;
			tri = std::make_shared<Triangle>(glm::vec2(-1.5f + step * i, 1.5f), glm::vec2(-1.7f + step * i, -0.3f), glm::vec2(0.4f + step * i, -0.3f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}
		else
		{
			float step = 50.0f;
			tri = std::make_shared<Triangle>(glm::vec2(200.0f + step * i, 50.0f), glm::vec2(100 + step * i, 200.0f), glm::vec2(300.0f + step * i, 200.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}
		tri->meshes()[0].vertexs()[0].texCoord = { 0.5f, 1.0f };
		tri->meshes()[0].vertexs()[1].texCoord = { 0.0f, 0.0f };
		tri->meshes()[0].vertexs()[2].texCoord = { 1.0f, 0.0f };
		tri->meshes()[0].vertexs()[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		tri->meshes()[0].vertexs()[1].color = { 0.0f, 1.0f, 0.0f, 1.0f };
		tri->meshes()[0].vertexs()[2].color = { 0.0f, 0.0f, 1.0f, 1.0f };
		std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(tri, std::make_shared<Material>(Programs::primitive()));
		ro->storage()->set(Program::nbColorModeLocationStr, 1);
		ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/pics/cubemap/1/front.png"));
		m_context->queue(ro);
	}
}

void MyApplication::drawQuadrangles()
{
	float step;
	int objectCount = 2;
	for(int i = 0; i != objectCount; ++i)
	{
		std::shared_ptr<Quadrangle> quad;
		glm::vec2 p0, p1, p2, p3;
		if (g_Original)
		{
			step = 0.3f;
			p0 = { -0.5f + step * i, -0.5f + step * i };
			p1 = { 0.5f + step * i, -0.5f + step * i };
			p2 = { 0.5f + step * i, 0.5f + step * i };
			p3 = { -0.5f + step * i, 0.5f + step * i };
		}
		else
		{
			step = 100;
			p0 = { -100 + step * i, 100 + step * i };
			p1 = { 100 + step * i, 100 + step * i };
			p2 = { 100 + step * i, -100 + step * i };
			p3 = { -100 + step * i, -100 + step * i };
		}
		quad = std::make_shared<Quadrangle>(p0, p1, p2, p3);
		std::shared_ptr<RenderObject> ro;
		if (i == 0)
		{
			ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::primitive()));
			ro->storage()->set(Program::nbColorModeLocationStr, 1);
			//ro->setRenderable(false);
			ro->model()->meshes()[0].unifyColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		}
		if (i == 1)
		{
			ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::primitive()));
			ro->storage()->set(Program::nbColorModeLocationStr, 0);
		//	ro->model()->meshes()[0].unifyColor(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
			ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/Pics/5.jpg"));
		//	ro->model()->meshes()[0].setPositionAt(0, Vec3(0, m_window->height(), 0));
		//	ro->model()->meshes()[0].setPositionAt(1, Vec3(m_window->width(), m_window->height(), 0));
		//	ro->model()->meshes()[0].setPositionAt(2, Vec3(m_window->width(), 0, 0));
		//	ro->model()->meshes()[0].setPositionAt(3, Vec3(0, 0, 0));
		//	auto glypTexture = std::make_shared<TextureGlyphAtlas>(m_font, L"abcdefghijklmnopqrst");
		//	ro->material()->textures().push_back(glypTexture);
		//	ro->setRenderable(false);
		}
		if (i == 2)
		{
			ro->storage()->set(Program::nbColorModeLocationStr, 1);
		//	ro->setRenderable(false);
		}
		m_context->queue(ro);
	}

}

void MyApplication::drawEllipses()
{
	std::shared_ptr<Ellipse> epse;
	if(g_Original)
		epse = std::make_shared<Ellipse>(-0.5f, -.5f, 0.25f, 0.25f, g_Original);
	else
		epse = std::make_shared<Ellipse>(100.0f, 400.0f, 50.0f, 50.0f, g_Original);
	epse->meshes()[0].unifyColor({ 1.0f, 0.0f, 0.0f, 0.0f });
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(epse, std::make_shared<Material>(Programs::primitive()));
	ro->storage()->set(Program::nbColorModeLocationStr, 0);
	ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/Pics/5.jpg"));
	m_context->queue(ro);
}

void MyApplication::drawCubes()
{
	std::shared_ptr<Cube> cube;
	if (g_Original)
	{
		float w = 0.7f;
		cube = std::make_shared<Cube>(0.0f, 0.0f, 0.0f, w, w, w);
	}
	else
	{
		float w = 100;
		cube = std::make_shared<Cube>(400.0f, 240.0f, 0.0f, w, w, w);
	}
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(cube, std::make_shared<Material>(Programs::cube()));

	m_context->queue(ro);
	std::shared_ptr<TextureCubemap> cm = std::make_shared<TextureCubemap>();
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

void MyApplication::drawSphere()
{
	std::shared_ptr<Sphere> sp;
	if(g_Original)
		sp = std::make_shared<Sphere>(0.5f, 0.5f, 0.5f, 0.5f, g_Original);
	else
		sp = std::make_shared<Sphere>(600.0f, 200.0f, 0.0f, 100.0f, g_Original);
	sp->meshes()[0].unifyColor({ 1.0f, 0.0, 0.0, 1.0 });
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(sp, std::make_shared<Material>(Programs::primitive()));

	ro->storage()->set(Program::nbColorModeLocationStr, 0);
	m_context->queue(ro);
	ro->material()->textures().push_back(std::make_shared<Texture2D>("e:/pics/world5.jpg"));
}

void MyApplication::drawPhone()
{
	std::shared_ptr<Cube> quad;
	if (g_Original)
	{
		float w = 0.5f;
		quad = std::make_shared<Cube>(-1.0f, -0.0f, 0.0f, w, w, w);
	}
	else
	{
		float w = 80;
		quad = std::make_shared<Cube>(600.0f, 350.0f, 0.0f, w, w, w);
	}
	//	std::shared_ptr<Quadrangle> quad = std::make_shared<Quadrangle>(Vec2(-0.0f, 0.0f), 2.0, 2.0);
	//quad->setTextureCoordinateAt(0, Vec2(0.0, 1.0));
	//quad->setTextureCoordinateAt(1, Vec2(1.0, 1.0));
	//quad->setTextureCoordinateAt(2, Vec2(1.0, 0.0));
	//quad->setTextureCoordinateAt(3, Vec2(0.0, 0.0));
	float f = 0.5773502691896258f;
	quad->meshes()[0].vertexs()[0].normal = { -f, f, f };
	quad->meshes()[0].vertexs()[1].normal = { f, f, f };
	quad->meshes()[0].vertexs()[2].normal = { f, -f, f };
	quad->meshes()[0].vertexs()[3].normal = { -f, -f, f };
	quad->meshes()[0].vertexs()[4].normal = { f, f, -f };
	quad->meshes()[0].vertexs()[5].normal = { -f, f, -f };
	quad->meshes()[0].vertexs()[6].normal = { -f, -f, -f };
	quad->meshes()[0].vertexs()[7].normal = { f, -f, -f };
	//	std::shared_ptr<Ellipse> epse = std::make_shared<Ellipse>(Vec2(-0.5f, -.5f), 0.25, 0.25);
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::phong()));
	m_context->queue(ro);
	ro->storage()->set("viewPos", cameraPosition);
	ro->storage()->set("material.shininess", 32.0);
	ro->storage()->set("light.direction", g_Original ? glm::vec3(1.0f, -0.0f, 3.0f) : glm::vec3(1.0f, -0.0f, -3.0f));
	ro->storage()->set("light.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	ro->storage()->set("light.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	ro->storage()->set("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	//	ro->material()->setTexture(std::make_shared<Texture2D>("e:/pics/cubemap/1/front.png"));

	std::shared_ptr<TextureCubemap> cm = std::make_shared<TextureCubemap>();
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

void MyApplication::drawModel()
{
	std::shared_ptr<RenderObject> renderer = std::make_shared<RenderObject>(nullptr, std::make_shared<Material>(Programs::primitive()));
	renderer->loadFromFile("e:/model/nanosuit/nanosuit.obj");
	if (g_Original)
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

void MyApplication::drawGlyph()
{
	auto glyph = GlyphFactory::getGlyph(Fonts::getFont(Fonts::STKaiti), L'a');
	auto w = glyph->info.bm_width;
	auto h = glyph->info.bm_height;
	glm::vec2 p0, p1, p2, p3;
	if (g_Original)
	{
		p0 = { -0.5f, -0.5f };
		p1 = { 0.5f, -0.5f };
		p2 = { 0.5f, 0.5f };
		p3 = { -0.5f, 0.5f };
	}
	else
	{
		p0 = { 300, h };
		p1 = { 300 + w, h };
		p2 = { 300 + w, 0 };
		p3 = { 300, 0 };
	}
	std::shared_ptr<Quadrangle> quad = std::make_shared<Quadrangle>(p0, p1, p2, p3);
	quad->meshes()[0].vertexs()[0].texCoord = glyph->uv[0];
	quad->meshes()[0].vertexs()[1].texCoord = glyph->uv[1];
	quad->meshes()[0].vertexs()[2].texCoord = glyph->uv[2];
	quad->meshes()[0].vertexs()[3].texCoord = glyph->uv[3];
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::glpy()));
	ro->material()->textures().push_back(std::make_shared<Texture2D>(glyph->texureId));
	m_context->queue(ro);
}

void MyApplication::drawGlyphBunch()
{
	auto glyphBunch = std::make_shared<GlyphBunch>();
	glyphBunch->arrage(Fonts::getFont(Fonts::STKaiti), 300.0f, 50.0f, "abcdefghijklmnopqrs德赛西威tuvwxyz", 1, 32, TextWrappingE::Wrap, 300);
	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(glyphBunch, std::make_shared<Material>(Programs::glpy()));
	ro->material()->textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(Fonts::getFont(Fonts::STKaiti), 'a')->texureId));
	ro->storage()->set("fontColor", glm::vec4(1.0, 0.0, 0.0, 1.0));
	m_context->queue(ro);
}

bool MyApplication::isHit(std::shared_ptr<RenderObject> obj, int x, int y) const
{
	float xNormalized = x / (m_window->clientWidth() * 0.5f) - 1.0f;
	float yNormalized = y / (m_window->clientHeight() * 0.5f) - 1.0f;
	return obj->model()->hitTest(xNormalized, yNormalized);
}

void MyApplication::hitTest(int x, int y)
{
	for (auto i = 0u; i != m_context->renderObjectCount(); ++i)
	{
		auto obj = m_context->renderObject(i);
		if (isHit(obj, x, y))
			printf("obj[%d] is hit.\n", i);
	}
}

void MyApplication::preRender()
{
//	changeColor();
	m_timer.driveInLoop();
}

void MyApplication::OnResize(const nb::core::Window::ResizeArgs & args)
{
	auto w = m_window->clientWidth();
	auto h = m_window->clientHeight();
	printf("MyApplication::OnResize--width[%d], height[%d]\r\n", w, h);
	nb::gl::getProjection()->perspective(45.0f, (float)w / h, 0.1f, 10000.0f);
	if (g_Original)
		nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
	else
		nb::gl::getCamera()->lookat2D((float)w, (float)h);

	nb::gl::viewport(0, 0, w, h);
}

bool bPress = false;
static int pressX = 0;
static int pressY = 0;
void MyApplication::OnPointerAction(const nb::core::Window::PointerEventArgs & args)
{
	switch (args.action)
	{
	case PointerActionE::Down:
		bPress = true;
		pressX = args.x;
		pressY = args.y;
		break;
	case PointerActionE::Up:
	{
		bPress = false;
		hitTest(args.x, args.y);
		break;
	}
	case PointerActionE::Move:
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
	case KeyActionE::Down:
		switch (args.key)
		{
		case KeyCodeE::Esc:
			for (int i = 0; i != m_context->renderObjectCount(); ++i)
				m_context->renderObject(i)->model()->setMatrix(glm::identity<glm::mat4x4>());
			break;
		case KeyCodeE::F1:
		{
		/*	Matrix4x4 mat = Matrix4x4::identity();
			mat.rotateAngleY(60.0);
			mat.scaleX(2);
			mat.translate(0.5, 0, 0);
			m_context->renderObject(0)->model()->setMatrix(mat);*/
		}
			break;
		case KeyCodeE::F2:
			break;
		case KeyCodeE::F3:
			break;
		case KeyCodeE::F4:
			break;
		case KeyCodeE::F5:
			break;
		case KeyCodeE::F6:
			break;
		case KeyCodeE::F7:
			break;
		case KeyCodeE::F8:
			break;
		case KeyCodeE::F9:
			break;
		case KeyCodeE::F10:
			break;
		case KeyCodeE::F11:
			break;
		case KeyCodeE::F12:
			break;
		case KeyCodeE::Space:
			break;
		case KeyCodeE::A:
			m_context->renderObject(0)->model()->rotate(10, 0, 1, 0);
			break;
		case KeyCodeE::D:
			m_context->renderObject(0)->model()->rotate(-10, 0, 1, 0);
			break;
		case KeyCodeE::W:
			m_context->renderObject(0)->model()->rotate(10, 1, 0, 0);
			break;
		case KeyCodeE::S:
			m_context->renderObject(0)->model()->rotate(-10, 1, 0, 0);
			break;
		case KeyCodeE::B:
			break;
		case KeyCodeE::C:
			break;
		case KeyCodeE::E:
			break;
		case KeyCodeE::F:
			break;
		case KeyCodeE::G:
			break;
		case KeyCodeE::H:
			break;
		case KeyCodeE::I:
		{
			cameraPosition += 0.1f * cameraFront;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
			printf("z=%.1f\r\n", cameraPosition.z);
		}
			break;
		case KeyCodeE::J:
		{
			auto x = glm::cross(cameraFront, cameraUp) * 0.1f;
			cameraPosition -= x;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
		}
			break;
		case KeyCodeE::K:
		{
			cameraPosition -= 0.1f * cameraFront;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
			printf("z=%.1f\r\n", cameraPosition.z);
		}
			break;
		case KeyCodeE::L:
		{
			auto x = glm::cross(cameraFront, cameraUp) * 0.1f;
			cameraPosition += x;
			nb::gl::getCamera()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
		}
			break;
		case KeyCodeE::M:
			break;
		case KeyCodeE::N:
			break;
		case KeyCodeE::O:
			break;
		case KeyCodeE::P:
			break;
		case KeyCodeE::Q:
			break;
		case KeyCodeE::R:
			m_context->renderObject(0)->model()->rotate(-10, 0, 0, 1);
			break;
		case KeyCodeE::T:
			m_context->renderObject(0)->model()->rotate(10, 0, 0, 1);
			break;
		case KeyCodeE::U:
			break;
		case KeyCodeE::V:
			break;
		case KeyCodeE::X:
			break;
		case KeyCodeE::Y:
			break;
		case KeyCodeE::Z:
			break;
		case KeyCodeE::Left:
			m_context->renderObject(0)->model()->translate(g_Original ? -0.01f : -10.0f, 0.0f, 0.0f);
			break;
		case KeyCodeE::Up:
			m_context->renderObject(0)->model()->translate(0.0f, g_Original ? 0.01f : 10.0f, 0.0f);
			break;
		case KeyCodeE::Right:
			m_context->renderObject(0)->model()->translate(g_Original ? 0.01f : 10.0f, 0.0f, 0.0f);
			break;
		case KeyCodeE::Down:
			m_context->renderObject(0)->model()->translate(0.0f, g_Original ? -0.01f : -10.0f, 0.0f);
			break;
		case KeyCodeE::Add:
			m_context->renderObject(0)->model()->scale(2, 2, 2);
			break;
		case KeyCodeE::Sub:
			m_context->renderObject(0)->model()->scale(0.5, 0.5, 0.5);
			break;
		default:
			break;
		}
		break;
	case KeyActionE::Up:
		break;
	case KeyActionE::LongPress:
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

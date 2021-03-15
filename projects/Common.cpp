#include "Common.h"
#ifdef __ANDROID__
#include <jni.h>
#else
#include "newbrush/Application.h"
#endif
#include "newbrush/Node2D.h"
#include "newbrush/GLUnit.h"
#include "newbrush/Camera.h"

void ViewBase::onTouchDown(const Point &p)
{
	m_pressed = true;
	m_pressedPoint = p;
}

void ViewBase::onTouchMove(const Point &p)
{
	auto root = getRoot();
	auto scene = nb::as<Scene>(root);

	if (!m_pressed || !scene) return;

	Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
	m_pressedPoint = p;
	for (auto child : scene->children())
	{
		if (nb::is<SkyBox>(child->mesh()))	continue;

		auto rotate = child->getRotate();
		auto newAngle = glm::degrees(rotate.y) + ptOffset.x;
		rotate.y = glm::radians(newAngle);
		child->setRotate(rotate);
	}
}

void ViewBase::onTouchUp(const Point &p)
{
	m_pressed = false;
}

void ViewBase::onResize(const Size &size)
{
	auto root = getRoot();
	if (nb::is<Node2D>(getRoot()))
	{
		GLUnit::viewport(0, 0, (int)size.width, (int)size.height);
		nb::sharedCamera2D()->resize(size.width, size.height);
	}
	else if (nb::is<Scene>(root))
	{
		nb::as<Scene>(root)->onResize(size.width, size.height);
	}
	else
	{
		Log::error("root is nullptr, not ready");
	}
	m_size = size;
}

void ViewBase::onRender()
{
	auto root = getRoot();
	if (nb::is<Node2D>(root))
	{
		nb::as<Node2D>(getRoot())->updateLayout(m_size);
	}
	else if (nb::is<Scene>(root))
	{
		nb::as<Scene>(root)->onRender();
	}
	else
	{
		Log::error("root is nullptr, not ready");
	}
}

void ViewBase::setData(const std::string & path, const var & value)
{
	if (!m_data)
	{
		Log::error("dataContext is nullptr, ignore");
		return;
	}

	auto targetDataNode = m_data->lookup(path);
	if (targetDataNode)
	{
		targetDataNode->set(value);
	}
	else
	{
		Log::error("invalid data path [{}]", path);
	}
}

void ViewBase::loadBackground(ref<Scene> scene, const std::string & skyboxPath)
{
	auto skyBox = createRef<SkyBox>();
	auto cubeMap = createRef<TextureCubemap>();
	std::string dir = skyboxPath;
	cubeMap->update(dir + "top.jpg", dir + "bottom.jpg", dir + "left.jpg", dir + "right.jpg", dir + "front.jpg", dir + "back.jpg");
	skyBox->material = createRef<SkyBoxMaterial>(cubeMap);

	auto background = createRef<Node>();
	background->setMesh(skyBox);
	if (scene->childCount() >= 2)
	{
		scene->removeChild(1);
	}
	scene->addChild(background);
}

void ViewBase::loadModel(ref<Scene> scene, const std::string & path, const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale)
{
	assert(scene);

	auto k = nb::getMilliseconds();

	ModelImporter importer;
	importer.load(path);
	auto model = importer.getRoot();
	auto lights = importer.getLights();
	scene->lights.insert(scene->lights.end(), lights.begin(), lights.end());
	//默认添加一个点光源，否则渲染很黑
	if (scene->lights.empty())
	{
		scene->lights.push_back(createRef<PointLight>());
	}
	scene->animations = importer.getAnimations();

	auto cost = nb::getMilliseconds() - k;
	if (model)
	{
		scene->addChild(model);
		Log::info("load [{}] success cost [{}] ms. MeshCount:[{}], TriangleCount:[{}], VertexCount=[{}]", path, cost, importer.getMeshCount(), importer.getTriangleCount(), importer.getVertexCount());
		model->setTranslate(translate);
		model->setRotate(rotate);
		model->setScale(scale);
	}
	else
	{
		Log::error("load [{}] fail cost [{}] ms.", path, cost);
	}

}

void ViewBase::changeMaterial(ref<Node> model)
{
	std::function<void(ref<Node> node, ref<Material> material)> loopSet = [&loopSet](ref<Node> node, ref<Material> material)
	{
		if (!node || !material) return;

		auto mesh = node->mesh();
		if (mesh)
		{
			mesh->material = material;
		}
		else
		{
			for (auto child : node->children())
			{
				loopSet(child, material);
			}
		}
	};

	auto cubeMaterial = createRef<CubemapMaterial>();
	auto cubeMap = createRef<TextureCubemap>();
	cubeMap->update(RES_DIR"/models/skybox1/top.jpg", RES_DIR"/models/skybox1/bottom.jpg", RES_DIR"/models/skybox1/left.jpg",
		RES_DIR"/models/skybox1/right.jpg", RES_DIR"/models/skybox1/front.jpg", RES_DIR"/models/skybox1/back.jpg");
	cubeMaterial->cubeMapping = cubeMap;

	loopSet(model, cubeMaterial);
}

MessageQueue * MessageQueue::get()
{
	static MessageQueue *p = nullptr;
	if (!p) p = new MessageQueue();
	return p;
}

void MessageQueue::post(Task task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_msgQueue.push(task);
}

Task MessageQueue::pick()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_msgQueue.empty()) return nullptr;

	Task task = m_msgQueue.front();
	m_msgQueue.pop();
	return task;
}

extern ref<ViewBase> g_view;

#ifdef __ANDROID__
bool g_OnRendering = false;
bool m_hasCache = false;
Point m_cacheMove;
extern "C"
{

	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_init(JNIEnv *env, jobject thiz)
	{
		Log::info("Java_nb_jni_Newbrush_init begin");
		auto k = getMilliseconds();
		g_view->init();
		Log::info("Java_nb_jni_Newbrush_init finish cost {} ms", getMilliseconds() - k);
	}

	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_resize(JNIEnv *env, jobject thiz, jint width, jint height)
	{
		Log::info("Java_nb_jni_Newbrush_resize, width={}, height={}", width, height);
		g_view->onResize(Size((float)width, (float)height));
	}

	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_render(JNIEnv *env, jobject thiz)
	{
		//如果有消息任务，则在GL渲染线程执行
		auto task = MessageQueue::get()->pick();
		if (task)
		{
			task();
		}
		Timer::driveInLoop();

		g_OnRendering = true;
		g_view->onRender();
		g_OnRendering = false;
		if (m_hasCache)
		{
			m_hasCache = false;
			g_view->onTouchMove(m_cacheMove);
		}
	}

	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_touch(JNIEnv *env, jobject thiz, jint action, jfloat x, jfloat y)
	{
		//0:down,1:up,2:move
		if (action == 0)
		{
			Log::info("Java_nb_jni_Newbrush_touch down, x={}, y={}", action, x, y);
			g_view->onTouchDown(Point(x, y));
		}
		else if (action == 1)
		{
			Log::info("Java_nb_jni_Newbrush_touch up, x={}, y={}", action, x, y);
		}
		else if (action == 2)
		{
			if (g_OnRendering)
			{
				m_hasCache = true;
				m_cacheMove = Point(x, y);
			}
			else
			{
				m_hasCache = false;
				g_view->onTouchMove(Point(x, y));
			}
		}

	}

	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_setData(JNIEnv *env, jobject thiz, jstring path, jstring value)
	{
		const char* _path = env->GetStringUTFChars(path, 0);
		const char* _value = env->GetStringUTFChars(value, 0);
		Log::info("Java_nb_jni_Newbrush_setData, path={}, value={}", _path, _value);
		g_view->setData(_path, std::string(_value));
	}
}

#else

int main(int argc, char **argv)
{
	Application app;
	auto window = createRef<Window>();
	nbThrowExceptionIf(!g_view, std::logic_error, "g_view is nullptr.");

	g_view->init();
	window->root = g_view->getRoot();

	window->KeyEvent += [](const KeyEventArgs &args)
	{
		if (args.action == 1 || args.action == 2)
		{
			g_view->onKey(args.key);
		}
	};

	window->TouchEvent += [](const TouchEventArgs &e)
	{
		Point p = { e.x, e.y };
		switch (e.action)
		{
		case TouchActionE::down: g_view->onTouchDown(p); break;
		case TouchActionE::move: g_view->onTouchMove(p); break;
		case TouchActionE::up: g_view->onTouchUp(p); break;
		default: break;
		}
	};

	return app.run(argc, argv);
}

#endif
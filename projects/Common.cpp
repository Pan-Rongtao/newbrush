#include "Common.h"
#include "newbrush/Helper.h"
#if NB_OS == NB_OS_ANDROID
	#include <jni.h>
#endif

MessageQueue g_msgQueue;
extern ref<ViewBase> g_view;

void ViewBase::resize(const Size &size)
{
	GLUtils::viewport(0.0f, 0.0f, size.width, size.height);
	nb::sharedCamera2D()->resize(size.width, size.height);
	m_size = size;
}

void ViewBase::render()
{
	m_root->updateLayout(m_size);
}

void ViewBase::setResourceDir(const std::string &resDir)
{
	m_resDir = resDir;
}

void ViewBase::setData(const std::string & path, const var & value)
{
	if (!m_data)
	{
		Log::error("m_data is nullptr, ignore");
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

ref<Node2D> ViewBase::getRoot() const
{
	return m_root;
}

ref<Model> loadModel(const std::string & path, const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale)
{
	auto model = createRef<Model>();
	model->load(path);
	model->setTransform(createRef<Transform>(translate, rotate, scale));
	return model;
}

#ifdef NB_USE_IMGUI
#include "imgui/ImGuiHelper.h"
class EditorView : public ImGuiView
{
public:
	using ImGuiView::ImGuiView;

	virtual void onInit() {}
	virtual void onRender()
	{
		static bool show = false;
		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin(u8"Properties", &show);

		ImGuiWidget::showPropertyEditor(instance(Obj));

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		MouseInWindow = ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + size.x, pos.y + size.y));

		ImGui::End();
	}

	ref<Object> Obj;
	bool MouseInWindow;
};
#endif


#if NB_OS == NB_OS_ANDROID

extern "C" {


static JNIEnv *g_env = nullptr;
static jclass g_javaClass;
static jmethodID g_javaCallback;
#define ANDROID_CLASS "nb/jni/NBSurfaceView"

jstring char2Jstring(JNIEnv* env, const char* pat)
{
	jclass strClass = (env)->FindClass("java/lang/String");
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = (env)->NewByteArray((jsize)strlen(pat));
	(env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
	jstring encoding = (env)->NewStringUTF("GB2312");
	return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}

/****************************************************
Java_nb_jni_Newbrush_init、Java_nb_jni_Newbrush_resize、Java_nb_jni_Newbrush_render这3个函数会在android 非UI主线程中调用
Java_nb_jni_Newbrush_touch会在android UI主线程中调用
Java_nb_jni_Newbrush_setData则在android使用的线程调用，可能是UI线程也可能是非UI线程，取决于调用者调用的地方
*****************************************************/
JNIEXPORT void JNICALL Java_nb_jni_Newbrush_init(JNIEnv *env, jobject thiz, jstring resDir)
{
	Log::info("Java_nb_jni_Newbrush_init begin");
	//记录JNIEnv、jclass、jmethodID
	g_env = env;
	jclass javaClass = env->FindClass(ANDROID_CLASS);
	g_javaClass = (jclass)env->NewGlobalRef(javaClass);	//一定要构建全局的，否则会被android GC回收，在其他地方就用就有问题了
	nbThrowExceptionIf(!g_javaClass, std::runtime_error, "can't find android class %s", ANDROID_CLASS);
	g_javaCallback = env->GetStaticMethodID(g_javaClass, "onNBEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
	nbThrowExceptionIf(!g_javaCallback, std::runtime_error, "can't find NBSurfaceView::onNBEvent(String, String)");
	
	SystemHelper::printSystemInfos();
	auto k = getMilliseconds();
	const char* _resDir = env->GetStringUTFChars(resDir, 0);
	g_view->setResourceDir(std::string(_resDir));
	g_view->init();
	
	Log::info("Java_nb_jni_Newbrush_init finish cost {} ms", getMilliseconds() - k);
}

JNIEXPORT void JNICALL Java_nb_jni_Newbrush_resize(JNIEnv *env, jobject thiz, jint width, jint height)
{
	Log::info("Java_nb_jni_Newbrush_resize, width={}, height={}", width, height);
	g_view->resize(Size((float)width, (float)height));
}

JNIEXPORT void JNICALL Java_nb_jni_Newbrush_render(JNIEnv *env, jobject thiz)
{
	//如果有消息任务，则在GL渲染线程执行
	auto task = g_msgQueue.pick();
	if (task)
	{
		task();
	}
	Timer::driveInLoop();
	g_view->render();
}

JNIEXPORT void JNICALL Java_nb_jni_Newbrush_touch(JNIEnv *env, jobject thiz, jint action, jfloat x, jfloat y)
{
	//0:down,1:up,2:move
	if (action == 0) Log::info("Java_nb_jni_Newbrush_touch down, x={}, y={}", x, y);
	if (action == 1) Log::info("Java_nb_jni_Newbrush_touch up, x={}, y={}", x, y);

	TouchEventArgs e;
	e.action = (action == 0 ? TouchAction::Down : action == 1 ? TouchAction::Up : TouchAction::Move);
	e.x = (float)x;
	e.y = (float)y;
	g_msgQueue.post([e]() {TreeHelper::touchThunk(g_view->getRoot(), e); });
}

JNIEXPORT void JNICALL Java_nb_jni_Newbrush_setData(JNIEnv *env, jobject thiz, jstring path, jstring value)
{
	const char* _path = env->GetStringUTFChars(path, 0);
	const char* _value = env->GetStringUTFChars(value, 0);
	Log::info("Java_nb_jni_Newbrush_setData, path={}, value={}", _path, _value);
	g_view->setData(_path, std::string(_value));
	//g_msgQueue.post([_path, _value]() {g_view->setData(_path, std::string(_value)); });
}

void nofityAndroid(const std::string & eventName, const std::string & args)
{
	if (g_env)
	{
		jstring s0 = char2Jstring(g_env, eventName.data());
		jstring s1 = char2Jstring(g_env, args.data());
		g_env->CallStaticVoidMethod(g_javaClass, g_javaCallback, s0, s1);
	}
}

}

#else

int main(int argc, char **argv)
{
	try
	{
		Application app;
		auto k = nb::getMilliseconds();
		Window window;
		auto windowCost = nb::getMilliseconds() - k;

		k = nb::getMilliseconds();
		g_view->init();
		auto viewCost = nb::getMilliseconds() - k;

#ifdef NB_USE_IMGUI
		auto imView = createRef<EditorView>(window.getGLFW());
#endif
		window.Touch += [&](const TouchEventArgs &e)
		{
#ifdef NB_USE_IMGUI
			if (e.action == TouchAction::Down && !imView->MouseInWindow)
				window.selectItem(e.x, e.y);
#endif
		};
		window.PostRender += [&](const EventArgs &e)
		{
#ifdef NB_USE_IMGUI
			imView->Obj = window.getSelectItem();
			ImGuiHelper::render(imView.get());
#endif
		};
		window.Key += [&window](const KeyEventArgs &e)
		{
			if (e.key == KeyCode::Escape)
				window.close();

#ifdef NB_USE_IMGUI
			if (e.action == KeyAction::down && e.key == KeyCode::F1)
			{
				ImGuiHelper::enableRender(!ImGuiHelper::isEnableRender());
				if (!ImGuiHelper::isEnableRender())
				{
					window.selectItem(-1.0f, -1.0f);
				}
			}
#endif
		};
		window.Closing += [](const CancelEventArgs &e) 
		{
#ifdef NB_USE_IMGUI
			ImGuiHelper::deinit();
#endif
			quick_exit(0);	//必须直接退出，否则imgui后续调用会出错
		};
		window.ContentRendered += [windowCost, viewCost](const EventArgs &e)
		{
			Log::info("window cost {} ms, g_view cost {} ms, first frame cost {} ms", windowCost, viewCost, nb::getMilliseconds() - nb::getStarupMilliseconds());
		};

		window.root = g_view->getRoot();
		Log::info("first view show cost {} ms", nb::getMilliseconds() - nb::getStarupMilliseconds());
		return app.run(argc, argv);
	}
	catch (const std::exception &e) { Log::error("\n\n{}\n", e.what()); }
}

#endif

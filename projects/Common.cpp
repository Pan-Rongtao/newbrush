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

extern "C"
{
	JNIEXPORT void JNICALL Java_nb_jni_Newbrush_init(JNIEnv *env, jobject thiz)
	{
		Log::info("Java_nb_jni_Newbrush_init begin");
		SystemHelper::printSystemInfos();
		auto k = getMilliseconds();
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
		e.action = (action == 0 ? TouchActionE::down : action == 1 ? TouchActionE::up : TouchActionE::move);
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
	}
}

#else

int main(int argc, char **argv)
{
	try
	{
		Application app;
		Window window;
#ifdef NB_USE_IMGUI
		auto imView = createRef<EditorView>(window.getGLFW());
#endif
		window.Touch += [&](const TouchEventArgs &e)
		{
#ifdef NB_USE_IMGUI
			if (e.action == TouchActionE::down && !imView->MouseInWindow)
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
			if (e.key == KeyCode::escape)
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

		auto k = nb::getMilliseconds();
		g_view->init();
		Log::info("g_view init cost {} ms", nb::getMilliseconds() - k);

		window.root = g_view->getRoot();
		Log::info("first view show cost {} ms", nb::getMilliseconds() - nb::getStarupMilliseconds());
		return app.run(argc, argv);
	}
	catch (const std::exception &e) { Log::error("\n\n{}\n", e.what()); }
}

#endif

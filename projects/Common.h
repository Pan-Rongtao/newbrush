#pragma once
#include "newbrush/ModelImporter.h"
#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Application.h"
#include "newbrush/Binding.h"
#include "newbrush/Animation.h"
#include "newbrush/Texture.h"

using namespace nb;

class ViewBase
{
public:
	//重写以构建初始化场景，数据等
	//函数尾部应该调用buildDone函数以确认
	virtual void init() = 0;
	virtual ref<Node> getRoot() = 0;

	//鼠标压下、移动、释放（一般无需重写）
	virtual void onTouchDown(const Point &p);
	virtual void onTouchMove(const Point &p);
	virtual void onTouchUp(const Point &p);

	//尺寸变化（一般无需重写）
	virtual void onResize(const Size &size);

	//渲染（一般无需重写）
	virtual void onRender();

	//按键（一般用于有键盘的平台，如windows等）
	virtual void onKey(int key) {};

	//事件更新，用以处理无法绑定的数据逻辑
	virtual void onDataChanged(const std::string &path, const var &value) {};
	
	//设置数据
	//value可接受任意类型，该类型需与path的数据类型保持一致
	//否则，将检查这两者类型是否可以转换（转换注册请查看RttrRegistration.cpp）
	//比如，如果path是Color类型，而value传入的是字符串"255,255,0,0"，可转换
	void setData(const std::string &path, const var &value);

protected:
	static void loadBackground(ref<Scene> scene, const std::string &skyboxPath);
	static void loadModel(ref<Scene> scene, const std::string & path, const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale);

	void changeMaterial(ref<Node> model);
	
	Point m_pressedPoint;
	bool m_pressed{false};
	ref<DataObject> m_data;
	Size m_size{500.0f, 500.0f};
};

#include <queue>
#include <mutex>

using Task = std::function<void(void)>;
class MessageQueue
{
public:
	static MessageQueue *get();
	void post(Task task);
	Task pick();

private:
	MessageQueue() = default;

	std::mutex m_mutex;
	std::queue<Task> m_msgQueue;
};

#ifdef __ANDROID__
#define RES_DIR "/storage/emulated/0/resource/"
#else
#define RES_DIR "../resource/"
#endif
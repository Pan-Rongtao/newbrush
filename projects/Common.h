#pragma once
#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Application.h"
#include "newbrush/Binding.h"
#include "newbrush/Animation.h"
#include "newbrush/Node2D.h"
#include "newbrush/Model.h"
#include "newbrush/UserControl.h"
#include "newbrush/StateManager.h"

using namespace nb;

class ViewBase
{
public:
	//重写以构建初始化视图，数据等
	virtual void init() = 0;

	//数据更新，重写以处理逻辑
	virtual void onDataChanged(const std::string &path, const var &value) {};

	//设置数据
	//value可接受任意类型，该类型需与path的数据类型保持一致
	//否则，将检查这两者类型是否可以转换（转换注册请查看RttrRegistration.cpp）
	//比如，如果path是Color类型，而value传入的是字符串"255,0,0,255"，可转换
	void setData(const std::string &path, const var &value);
	void resize(const Size &size);
	void render();
	nb::ref<Node2D> getRoot() const;

protected:
	Size m_size;
	nb::ref<Node2D> m_root;
	nb::ref<DataObject> m_data;
};

nb::ref<Model> loadModel(const std::string & path, const glm::vec3 &translate, const glm::vec3 &rotate, const glm::vec3 &scale);
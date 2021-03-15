#pragma once
#include "../Common.h"

class ModelBrowser : public ViewBase
{
public:
	virtual void init() override;
	virtual ref<Node> getRoot() override;
	virtual void onDataChanged(const std::string &path, const var &value) override;
	virtual void onKey(int key) override;

private:
	ref<DataObject> buildData();
	void binding();

	ref<Scene> m_scene;
	ColorAnimationUsingKeyFrames m_lightAnimation;
};

#pragma once
#include "../Common.h"

enum class ModelType
{
	XiaoV,
	DIY,
};

class ModelView : public Node2D
{
public:
	ModelView();

	void load(ModelType type);

	ref<Model> getModel();

private:
	void onTouch(const TouchEventArgs &e);

	bool m_pressed{ false };
	Point m_pressedPoint;
	ModelType m_type;
	ref<Model> m_xiaovModel;
	ref<Model> m_diyModel;
};
#pragma once
#include "../Common.h"

enum class ModelMode
{
	None,
	Diy,
	XiaoXi,
};

class SelectorView : public Node2D
{
public:
	SelectorView();

	void selectMode(ModelMode mode);

private:
	void onBtnClick(const EventArgs &e);

	ref<Button> m_btnBackToHome;
	ref<Button> m_btnEdit;
	ref<Button> m_btnDIYMode;
	ref<Button> m_btnXiMode;
	ModelMode m_curMode{ModelMode::None};
};
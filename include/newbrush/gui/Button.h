#pragma once
#include "newbrush/gui/ButtonBase.h"

namespace nb{

class NB_API Button : public ButtonBase
{
	RTTR_ENABLE(ButtonBase)
	NB_OBJECT
public:
	Button();
	virtual ~Button() = default;

	static DependencyPropertyPtr IsCancelProperty();	//是否是“取消”按钮依赖属性，用户可以通过按ESC键激活“取消”按钮
	static DependencyPropertyPtr IsDefaultProperty();//是否是“默认”按钮依赖属性，用户可以通过按Enter键激活“默认”按钮

private:

};

}


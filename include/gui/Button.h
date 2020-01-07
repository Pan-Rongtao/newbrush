#pragma once
#include "../gui/ButtonBase.h"

namespace nb{
namespace gui{

class NB_API Button : public ButtonBase
{
public:
	Button();
	virtual ~Button() = default;

	static DependencyProperty	IsCancelProperty();	//是否是“取消”按钮依赖属性，用户可以通过按ESC键激活“取消”按钮
	static DependencyProperty	IsDefaultProperty();//是否是“默认”按钮依赖属性，用户可以通过按Enter键激活“默认”按钮

protected:
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onMouseLeftButtonDown();
	virtual void onMouseLeftButtonUp();

private:
	bool	m_pressed;
};

}}


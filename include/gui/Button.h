#pragma once
#include "../gui/ButtonBase.h"

namespace nb{
namespace gui{

class NB_API Button : public ButtonBase
{
public:
	Button();
	virtual ~Button() = default;

	Property_rw<bool>				IsCancel;			//是否是“取消”按钮，用户可以通过按ESC键激活“取消”按钮
	Property_rw<bool>				IsDefault;			//是否是“默认”按钮，用户可以通过按Enter键激活“默认”按钮
	static const DependencyProperty IsCancelProperty();	//是否是“取消”按钮依赖属性
	static const DependencyProperty IsDefaultProperty();//是否是“默认”按钮依赖属性

protected:
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onMouseLeftButtonDown();
	virtual void onMouseLeftButtonUp();

private:
	bool	m_pressed;
};

}}


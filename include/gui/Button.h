#pragma once
#include "ContentControl.h"
#include "../core/Property.h"
#include "DependencyProperty.h"

namespace nb { namespace gui {

using nb::core::Property_rw;

class NB_API Button : public ContentControl
{
public:
	Button();
	virtual ~Button() = default;

	Property_rw<bool>				IsCancel;	//是否是“取消”按钮，用户可以通过按ESC键激活“取消”按钮
	Property_rw<bool>				IsDefault;	//是否是“默认”按钮，用户可以通过按Enter键激活“默认”按钮
	static const DependencyProperty IsCancelProperty();
	static const DependencyProperty IsDefaultProperty();

	struct ClickEventArgs {};
	core::Event<ClickEventArgs>			Click;

protected:
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onMouseLeftButtonDown();
	virtual void onMouseLeftButtonUp();

private:
	bool	m_pressed;
};

}}


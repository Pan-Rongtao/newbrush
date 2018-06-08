#pragma once
#include "core/Object.h"
#include "String.h"
#include "PointI.h"
#include "SizeI.h"
#include "RectI.h"

namespace nb{ namespace System{

class NativeWindow;
class WindowEvent;
class NB_EXPORT Window
{
public:
	//设置窗口标题
	void SetCaption(const nb::System::String &caption);

	//获取窗口标题
	nb::System::String GetCaption() const;

	//设置窗口位置x（如果在win32环境下，为边框的左边距）
	void SetX(int x);

	//获取窗口x（如果在win32环境下，为边框的左边距）
	int GetX() const;

	//设置窗口位置y（如果在win32环境下，为边框的上边距）
	void SetY(int y);

	//获取窗口y（如果在win32环境下，为边框的上边距）
	int GetY() const;

	//设置窗口位置（如果在win32环境下，为边框的左上边距）
	void SetPos(const nb::System::PointI &pos);

	//获取窗口位置（如果在win32环境下，为边框的左上边距）
	void SetPos(int x, int y);

	//获取窗口位置（如果在win32环境下，为边框的左上边距）
	nb::System::PointI GetPos() const;

	//设置窗口客户端宽度width
	//异常：width < 0
	void SetWidth(int width);

	//获取窗口客户端宽度
	int GetWidth() const;

	//设置窗口客户端高度
	//异常：height < 0
	void SetHeight(int height);

	//获取窗口客户端高度
	int GetHeight() const;		

	//设置窗口客户端尺寸
	//异常：sz中的宽或高小于0
	void SetSize(const nb::System::SizeI &size);

	//获取窗口客户端尺寸
	nb::System::SizeI GetSize() const;

	//设置窗口区域（如果在win32环境下，位置为的边框的左上边距，尺寸为客户端区域）
	//异常：rect中的宽和高任意一个值小于0
	void SetRect(const nb::System::RectI &rect);

	//获取窗口区域（如果在win32环境下，位置为的边框的左上边距，尺寸为客户端区域）
	nb::System::RectI GetRect() const;

	//检查窗口事件
	void Pending();

	//设置窗口事件监听
	void SetListener(WindowEvent *listener);
	WindowEvent *GetListener() const;

	//获取窗口句柄
	long GetWindowHandle() const;

public:
	//构建一个Window对象，它的标题为空，区域为RectI(x-middle, y-middle, 800, 480)
	Window();

	//构建一个Window对象，它的标题为空，区域为RectI(x-middle, y-middle, width, height)
	Window(int width, int height);

	//构建一个Window对象，它的标题为空，区域为RectI(x, y, width, height)
	Window(int x, int y, int width, int height);

	//构建一个Window对象，它的标题为caption，区域为RectI(x-middle, y-middle, 800, 480)
	explicit Window(const nb::System::String &caption);

	//构建一个Window对象，它的标题为caption，区域为RectI(x-middle, y-middle, width, height)
	Window(const nb::System::String &caption, int width, int height);

	//构建一个Window对象，它的标题为caption，它的区域为rect
	Window(const nb::System::String &caption, const nb::System::RectI &rect);

	virtual ~Window();

public:
//	static void Peek();

private:
	void CreateNative();
	void ReleaseNative();

	NativeWindow			*m_pNative;
	WindowEvent				*m_pListener;
};

}}

#pragma once
#include <bitset>
#include "newbrush/core/Point.h"
#include "newbrush/core/Size.h"
#include "newbrush/core/RoutedEvent.h"

namespace nb {

class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

//按键枚举
enum class KeyE
{
	None = 0,																				//无
	Cancel,																					//取消键（暂时无法找到对应键盘：TODO）
	Back,																					//Backspace退格键
	Tab,																					//Tab键
	LineFeed,																				//换行键（暂时无法找到对应键盘：TODO）
	Clear,																					//清除键（暂时无法找到对应键盘：TODO）
	Return = 6,																				//回车键
	Enter = 6,																				//回车键
	Pause,																					//暂停键/Break键，一般在右上方
	Capital = 8,																			//大小写切换键
	CapsLock = 8,																			//大小写切换键
	KanaMode = 9,																			//未知按键（暂时无法找到对应键盘：TODO）
	HangulMode = 9,																			//未知按键（暂时无法找到对应键盘：TODO）
	JunjaMode,																				//未知按键（暂时无法找到对应键盘：TODO）
	FinalMode,																				//未知按键（暂时无法找到对应键盘：TODO）
	HanjaMode = 12,																			//未知按键（暂时无法找到对应键盘：TODO）
	KanjiMode = 12,																			//未知按键（暂时无法找到对应键盘：TODO）
	Escape,																					//Esc键
	ImeConvert,																				//未知按键（暂时无法找到对应键盘：TODO）
	ImeNonConvert,																			//未知按键（暂时无法找到对应键盘：TODO）
	ImeAccept,																				//未知按键（暂时无法找到对应键盘：TODO）
	ImeModeChange,																			//未知按键（暂时无法找到对应键盘：TODO）
	Space,																					//空格键
	Prior = 19,																				//前一/上一页键
	PageUp = 19,																			//前一/上一页键
	Next = 20,																				//后一/下一页键
	PageDow = 20,																			//后一/下一页键
	End,																					//结束键
	Home,																					//Home键
	Left,																					//向左键←
	Up,																						//向上键↑
	Right,																					//向右键→
	Down,																					//向下键↓
	Select,																					//选择键（暂时无法找到对应键盘：TODO）
	Print,																					//打印键（暂时无法找到对应键盘：TODO）
	Execute,																				//执行键（暂时无法找到对应键盘：TODO）
	Snapshot = 30,																			//屏幕快照键（有键，但WPF无响应：TODO）
	PrintScreen = 30,																		//屏幕快照键（有键，但WPF无响应：TODO）
	Insert,																					//插入键
	Delete,																					//删除键
	Help,																					//帮助键（暂时无法找到对应键盘：TODO）
	D0 = 34, D1, D2, D3, D4, D5, D6, D7, D8, D9,											//数字键0-9
	A = 44, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,		//字母键A-Z
	LWin,																					//左win键
	RWin,																					//右win键
	Apps,																					//右键触发按键，在右win键和右ctrl键直接
	Sleep,																					//未知按键（暂时无法找到对应键盘：TODO）
	NumPad0 = 74, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5,
	NumPad6, NumPad7, NumPad8, NumPad9,														//数字面板数字按键
	Multiply,																				//乘
	Add,																					//加
	Separator,																				//未知按键（暂时无法找到对应键盘：TODO）
	Subtract,																				//减
	Decimal,																				//小数点
	Divide,																					//除
	F1 = 90, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,								//F*键（F8无作用，F10发出System键）
	NumLock,																				//数字面板数字键锁
	Scroll,																					//Scroll Lock键
	LeftShift,																				//左Shift
	RightShift,																				//右Shift
	LeftCtrl,																				//左Ctrl
	RightCtrl,																				//右Ctrl
	LeftAlt,																				//左Alt
	RightAlt,																				//右Alt
	BrowserBack,																			//浏览器退后浏览（暂时无法找到对应键盘：TODO）
	BrowserForward,																			//浏览器向前浏览（暂时无法找到对应键盘：TODO）
	BrowserRefresh,																			//浏览器刷新页面（暂时无法找到对应键盘：TODO）
	BrowserStop,																			//浏览器停止刷新（暂时无法找到对应键盘：TODO）
	BrowserSearch,																			//浏览器搜索（暂时无法找到对应键盘：TODO）
	BrowserFavorites,																		//浏览器收藏夹（暂时无法找到对应键盘：TODO）
	BrowserHome,																			//浏览器主页（暂时无法找到对应键盘：TODO）
	VolumeMute,																				//静音按键（暂时无法找到对应键盘：TODO）
	VolumeDown,																				//音量调小按键（暂时无法找到对应键盘：TODO）
	VolumeUp,																				//音量调大按键（暂时无法找到对应键盘：TODO）
	MediaNextTrack,																			//媒体播放器下一曲按键（暂时无法找到对应键盘：TODO）
	MediaPreviousTrack,																		//媒体播放器上一曲按键（暂时无法找到对应键盘：TODO）
	MediaStop,																				//媒体播放器停止按键（暂时无法找到对应键盘：TODO）
	MediaPlayPause,																			//媒体播放器播放/暂停按键（暂时无法找到对应键盘：TODO）
	LaunchMail,																				//启动邮件按键（暂时无法找到对应键盘：TODO）
	SelectMedia,																			//选择媒体按键（暂时无法找到对应键盘：TODO）
	LaunchApplication1,																		//启动app1按键
	LaunchApplication2,																		//启动app2按键
	Oem1 = 140,																				//分号冒号键
	OemSemicolon = 140,																		//分号冒号键
	OemPlus,																				//加号键
	OemComma,																				//逗号键
	OemMinus,																				//减号键
	OemPeriod,																				//点号/句号键
	Oem2 = 145,																				//未知按键（暂时无法找到对应键盘：TODO）
	OemQuestion = 145,																		//未知按键（暂时无法找到对应键盘：TODO）
	Oem3 = 146,																				//波浪号键
	OemTilde = 146,																			//波浪号键
	AbntC1,																					//未知按键（暂时无法找到对应键盘：TODO）
	AbntC2,																					//未知按键（暂时无法找到对应键盘：TODO）
	Oem4 = 149,																				//左方括号键
	OemOpenBrackets = 149,																	//左方括号键
	Oem5 = 150,																				//斜杠线号键
	OemPipe = 150,																			//斜杠线号键
	Oem6 = 151,																				//右方括号键
	OemCloseBrackets = 151,																	//右方括号键
	Oem7 = 152,																				//引号键
	OemQuotes = 152,																		//引号键
	Oem8,																					//未知按键（暂时无法找到对应键盘：TODO）
	Oem102 = 154,																			//未知按键（暂时无法找到对应键盘：TODO）
	OemBackslash = 154,																		//未知按键（暂时无法找到对应键盘：TODO）
	ImeProcessed,																			//未知按键（暂时无法找到对应键盘：TODO）
	System,																					//左Ctrl、右Ctrl、F10 WPF都会发该键，待核实：TODO）
	OemAttn = 157,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeAlphanumeric = 157,																	//未知按键（暂时无法找到对应键盘：TODO）
	OemFinish = 158,																		//未知按键（暂时无法找到对应键盘：TODO）
	DbeKatakana = 158,																		//未知按键（暂时无法找到对应键盘：TODO）
	OemCopy = 159,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeHiragana = 159,																		//未知按键（暂时无法找到对应键盘：TODO）
	OemAuto = 160,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeSbcsChar = 160,																		//未知按键（暂时无法找到对应键盘：TODO）
	OemEnlw = 160,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeDbcsChar = 161,																		//未知按键（暂时无法找到对应键盘：TODO）
	OemBackTab = 162,																		//未知按键（暂时无法找到对应键盘：TODO）
	DbeRoman = 162,																			//未知按键（暂时无法找到对应键盘：TODO）
	Attn = 163,																				//未知按键（暂时无法找到对应键盘：TODO）
	DbeNoRoman = 163,																		//未知按键（暂时无法找到对应键盘：TODO）
	CrSel = 164,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeEnterWordRegisterMode = 164,															//未知按键（暂时无法找到对应键盘：TODO）
	ExSel = 165,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeEnterImeConfigureMode = 165,															//未知按键（暂时无法找到对应键盘：TODO）
	EraseEof = 166,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeFlushString = 166,																	//未知按键（暂时无法找到对应键盘：TODO）
	Play = 167,																				//未知按键（暂时无法找到对应键盘：TODO）
	DbeCodeInput = 167,																		//未知按键（暂时无法找到对应键盘：TODO）
	Zoom = 168,																				//未知按键（暂时无法找到对应键盘：TODO）
	DbeNoCodeInput = 168,																	//未知按键（暂时无法找到对应键盘：TODO）
	NoName = 169,																			//未知按键（暂时无法找到对应键盘：TODO）
	DbeDetermineString = 169,																//未知按键（暂时无法找到对应键盘：TODO）
	Pa1 = 170,																				//未知按键（暂时无法找到对应键盘：TODO）
	DbeEnterDialogConversionMode = 170,														//未知按键（暂时无法找到对应键盘：TODO）
	OemClear,																				//未知按键（暂时无法找到对应键盘：TODO）
	DeadCharProcessed = 172,																//未知按键（暂时无法找到对应键盘：TODO）
};

//按键状态枚举
enum class KeyStateE : uint8_t
{
	None = 0,	//未压下
	Down,		//压下
	Toggled,	//已切换
};

enum class MouseButtonE : uint8_t
{
	Left,		//左按钮
	Middle,		//中间按钮
	Right,		//右按钮
};

enum class MouseButtonStateE : uint8_t
{
	Released,	//已释放
	Pressed,	//已压下
};

enum class ReasonSessionEnding
{
	Logoff,					//由于用户注销引发的会话终止
	Shutdown,				//由于用户关机引发的会话终止
};

struct EventArgs { Object *sender; };
struct UnhandledExceptionEventArgs { std::exception e; };
struct ExitEventArgs { int exitCode; };
struct CancelEventArgs : public EventArgs { bool cancel{ false }; };
struct SessionEndingCancelEventArgs : public CancelEventArgs { ReasonSessionEnding reason; };
struct StartupEventArgs { std::vector<std::string> args; };

class NB_API RoutedEventArgs : public EventArgs
{
public:
	RoutedEventArgs();
	RoutedEventArgs(const RoutedEvent &routedEvent);
	RoutedEventArgs(const RoutedEvent &routedEvent, Object *source);
	virtual ~RoutedEventArgs() = default;

	bool		Handled;
	RoutedEvent	Event;
	Object		*OriginalSource;
	Object		*Source;
};

struct NB_API InputEventArgs : public RoutedEventArgs
{
public:
	InputEventArgs(int timestamp);
	int		Timestamp;		//事件发生的时间
};


class InputElement;
class NB_API MouseEventArgs : public InputEventArgs
{
public:
	MouseEventArgs(int timestamp);

	Point getPosition(std::shared_ptr<InputElement> relativeTo) const;			//获取光标相对于指定元素的位置

	MouseButtonStateE	LeftButton;		//左按钮状态
	MouseButtonStateE	MiddleButton;	//中间按钮状态
	MouseButtonStateE	RightButton;	//右按钮状态
};

class NB_API MouseButtonEventArgs : public MouseEventArgs
{
public:
	MouseButtonEventArgs(int timestamp, MouseButtonE button);

	MouseButtonE		ChangedButton;	//触发的按钮
	MouseButtonStateE	ButtonState;	//按钮状态
	int					ClickCount;		//点击次数，可处理单击、双击、三击的判定
};

class NB_API MouseWheelEventArgs : public MouseEventArgs
{
public:
	MouseWheelEventArgs(int timestamp, int delta);

	int	Delta;							//滚动值
};

class InputElement;
class NB_API Keyboard
{
public:
	static KeyStateE getKeyState(KeyE key);
	static bool isKeyDown(KeyE key);
	static bool isKeyUp(KeyE key);
	static bool isKeyToggled(KeyE key);
	std::shared_ptr<InputElement> focus(std::shared_ptr<InputElement> element);
};

class NB_API KeyboardEventArgs : public InputEventArgs
{
public:
	KeyboardEventArgs(int timestamp);
};

//键盘焦点变化事件
class NB_API KeyboardFocusChangedEventArgs : public KeyboardEventArgs
{
public:
	KeyboardFocusChangedEventArgs(int timestamp, std::shared_ptr<InputElement> oldFocus, std::shared_ptr<InputElement> newFocus);

	std::shared_ptr<InputElement>	OldFocus;	//以前具有焦点的元素
	std::shared_ptr<InputElement>	NewFocus;	//已移动到的元素
};

//按键事件（该设计与WPF有差距，需要重点注意）
class NB_API KeyEventArgs : public KeyboardEventArgs
{
public:
	KeyEventArgs(int timestamp, KeyE key);

	KeyE			SystemKey;	//由系统按键引起的键（系统键有F10、左Alt、右Alt）：如果仅按下Alt，[systemKey, key]=[Alt, System]；如果按下Alt+A=[A, System]
	KeyE			Key;		//按键
	std::bitset<3>	WKeyState;	//按键状态
};

struct NB_API TouchEventArgs : public InputEventArgs
{
	TouchEventArgs(int timestamp);

	Point getTouchPoint() const;
};

struct NB_API DragEventArgs : public RoutedEventArgs
{

};

struct SizeChangedEventArgs : public RoutedEventArgs
{
	Size previousSize;
	Size newSize;
	bool widthChanged;
	bool HeightChanged;
};

struct DependencyPropertyChangedEventArgs
{
	DependencyPropertyPtr	property;
	var						oldValue;
	var						newValue;
};

class RoutedProperyChangedEventArgs : public RoutedEventArgs
{
public:
	var		oldValue;
	var		newValue;
};

class ExceptonRoutedEventArgs
{
public:
	std::exception	errorException;
};

}
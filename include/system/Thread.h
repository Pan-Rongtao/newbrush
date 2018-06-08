#pragma once
#include "core/Object.h"

namespace nb{ namespace System{

class NativeThread;
class NB_EXPORT Thread
{
public:
	enum Priority
	{
		Priority_Idle,						//空闲时
		Priority_Lowest,					//
		Priority_Low,						//
		Priority_OperatingSystem_Normal,	//操作系统系统默认
		Priority_High,						//
		Priority_Highest,					//
		Priority_Realtime,					//实时优先级
		Priority_Inherit,					//继承，依赖于创建它的线程（默认）
	};

public:
	//设置优先级（暂时无效，请勿使用）
	void SetPriority(Priority priority);

	//获取优先级
	Priority GetPriority() const;

	//启动线程，如果线程已经处于启动状态，将维持运行状态
	void Start();

	//强制终止线程（不建议使用）
	void Quit();

	//线程是否处于运行状态
	bool IsRunning();

	//
	bool Wait(unsigned long nTime = 1);

	//需要重写的线程执行函数，在调用Start后运行此函数
	virtual void Run();

protected:
	//休眠秒/毫秒/微秒
	static void Sleep(unsigned long seconds);
	static void MSleep(unsigned long milliSeconds);
	static void USleep(unsigned long uSeconds);

protected:
	//构建一个新的线程，并处于未运行状态
	Thread();
	virtual ~Thread();

private:
	NativeThread	*m_pNative;
};

}}

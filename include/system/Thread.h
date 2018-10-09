#pragma once
#include "../core/Def.h"

namespace nb{ namespace System{

class Thread_Internal;
class NB_API Thread
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
	void setPriority(Priority priority);

	//获取优先级
	Priority priority() const;

	//启动线程，如果线程已经处于启动状态，将维持运行状态
	void start();

	//强制终止线程（不建议使用）
	void quit();

	//线程是否处于运行状态
	bool isRunning();

	//
	bool wait(unsigned long nTime = 1);

	//需要重写的线程执行函数，在调用Start后运行此函数
	virtual void run();

protected:
	//休眠秒/毫秒/微秒
	static void sleep(unsigned long seconds);
	static void msleep(unsigned long milliseconds);
	static void usleep(unsigned long useconds);

protected:
	//构建一个新的线程，并处于未运行状态
	Thread();
	virtual ~Thread();

private:
	Thread_Internal	*m_internal;
};

}}

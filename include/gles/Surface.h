/*******************************************************
**	Surface|WindowSurface|PbufferSurface
**
**	表面
**		Surface是描述渲染附着表面的数据结构，
**	一般而言，它也Window和Context密切相关
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Surface
{
public:
	virtual ~Surface();
	Surface(const Surface &other) = delete;
	void operator = (const Surface &other) = delete;

	//设置宽
	void setWidth(int width);

	//设置高
	void setHeight(int height);

	//获取宽高
	int width() const;
	int height() const;

	//egl id
	void *handle() const;
	
protected:
	Surface();
	void		*m_handle;
};

class NB_API WindowSurface : public Surface
{
public:
	WindowSurface(int width, int height, long windowHandle);
	~WindowSurface();

	long windowHandle();

private:
	long		m_windowHandle;
};

class NB_API PbufferSurface : public Surface
{
public:
	PbufferSurface(int width, int height);

};

class NB_API PixmapSurface : public Surface
{
public:
	PixmapSurface(int width, int height, void *pixmapHandle);

	void *pixmapHandle();
	const void *pixmapHandle() const;

private:
	void		*m_pixmapHandle;
};

}}

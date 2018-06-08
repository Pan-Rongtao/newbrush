#pragma once
#include <vector>
#include "core/Object.h"

namespace nb{ namespace gl{ namespace egl{

class NB_EXPORT Surface
{
public:
	int GetWidth() const;
	int GetHeight() const;

	void *GetEGLHandle() const;

	virtual ~Surface();

protected:
	Surface();

	void		*m_Handle;

private:
	Surface(const Surface &other);
	void operator = (const Surface &other);
};

class NB_EXPORT WindowSurface : public Surface
{
public:
	WindowSurface(int width, int height, long windowHandle);
	~WindowSurface();

	long GetWindowHandle();

private:
	long		m_WindowHandle;
};

class NB_EXPORT PbufferSurface : public Surface
{
public:
	PbufferSurface(int width, int height);

};

class NB_EXPORT PixmapSurface : public Surface
{
public:
	PixmapSurface(int width, int height, void *pixmapHandle);

	void *GetPixmapHandle();

private:
	void		*m_PixmapHandle;
};

}}}

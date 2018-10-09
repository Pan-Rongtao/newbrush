#include "system/Window.h"
#include "Window_Internal.h"

using namespace nb::System;

Window::Window()
	: m_internal(new Window_Internal(this))
{
}

Window::Window(int width, int height)
	: m_internal(new Window_Internal(this))
{
	setWidth(width);
	setHeight(height);
}

Window::Window(int x, int y, int width, int height)
	: m_internal(new Window_Internal(this))
{
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);
}

Window::Window(const std::string &title)
	: m_internal(new Window_Internal(this))
{
	setTitle(title);
}

Window::Window(const std::string &title, int width, int height)
	: m_internal(new Window_Internal(this))
{
	setWidth(width);
	setHeight(height);
	setTitle(title);
}

Window::~Window()
{
	delete m_internal;
}

void Window::setTitle(const std::string &title)
{
	m_internal->setTitle(title);
}

std::string Window::title() const
{
	return m_internal->title();
}

void Window::setX(int x)
{
	m_internal->setX(x);
}

int Window::x() const
{
	return m_internal->x();
}

void Window::setY(int y)
{
	m_internal->setY(y);
}

int Window::y() const
{
	return m_internal->y();
}

void Window::setWidth(int width)
{
	m_internal->setWidth(width);
}

int Window::width() const
{
	return m_internal->width();
}

void Window::setHeight(int height)
{
	m_internal->setHeight(height);
}

int Window::height() const
{
	return m_internal->height();
}

void Window::pending()
{
	m_internal->pending();
}

long Window::handle() const
{
	return m_internal->handle();
}

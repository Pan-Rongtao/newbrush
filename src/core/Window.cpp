#include "core/Window.h"
#include "Window_Internal.h"

using namespace nb::core;

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

Window::Window(const std::string &title, int x, int y, int width, int height)
{
	setX(x);
	setY(y);
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

void Window::setTopMost(bool topMost)
{
	return m_internal->setTopMost(topMost);
}

bool Window::topMost() const
{
	return m_internal->topMost();
}

void Window::setWindowState(WindowStateE state)
{
	m_internal->setWindowState(state);
}

WindowStateE Window::getWindowState() const
{
	return m_internal->getWindowState();
}

void Window::setWindowStyle(WindowStyleE style)
{
	m_internal->setWindowStyle(style);
}

WindowStyleE Window::getWindowStyle() const
{
	return m_internal->getWindowStyle();
}

void Window::show(bool show)
{
	m_internal->show(show);
}

bool Window::isShow() const
{
	return m_internal->isShow();
}

void Window::active()
{
	m_internal->active();
}
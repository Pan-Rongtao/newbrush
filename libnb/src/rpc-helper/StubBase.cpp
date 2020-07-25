#include "StubBase.h"
#include "newbrush/gui/Application.h"

void StubBase::taskReady()
{
	std::unique_lock<std::mutex> lock(m_mute);
	m_ready = true;
	m_cv.notify_one();
}

Status StubBase::waitForTaskReady(std::function<void()> task)
{
	nb::Application::current()->connect(task);
	std::unique_lock<std::mutex> lock(m_mute);
	m_cv.wait(lock, [this]() {return m_ready; });
	m_ready = false;
	return Status::OK;
}

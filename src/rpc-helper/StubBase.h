#pragma once
#include <condition_variable>
#include <mutex>
#include "grpcpp/grpcpp.h"
#include "google/protobuf/service.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gles/SourceDecoder.h"
#include "newbrush/gles/Shader.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gui/Panel.h"

using namespace grpc;
using namespace google::protobuf;
using namespace nb;
using namespace rttr;
class StubBase
{
protected:
	void taskReady();
	Status waitForTaskReady(std::function<void()> task);
	
private:
	bool					m_ready;
	std::mutex				m_mute;
	std::condition_variable m_cv;
};
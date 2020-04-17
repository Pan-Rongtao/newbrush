#pragma once
#include <condition_variable>
#include <mutex>
#include "grpcpp/grpcpp.h"
#include "google/protobuf/service.h"

using namespace grpc;
using namespace google::protobuf;
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
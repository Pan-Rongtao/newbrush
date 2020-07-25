#include "ResourceDictionaryStub.h"
#include "newbrush/core/data/ResourceDictionary.h"

Status ResourceDictionaryStub::AddBool(ServerContext * context, const AddBoolRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

Status ResourceDictionaryStub::AddInt(ServerContext * context, const AddIntRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

Status ResourceDictionaryStub::AddFloat(ServerContext * context, const AddFloatRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

Status ResourceDictionaryStub::AddString(ServerContext * context, const AddStringRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

Status ResourceDictionaryStub::AddSolidSolorBrush(ServerContext * context, const AddSolidSolorBrushRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

Status ResourceDictionaryStub::AddImageBrush(ServerContext * context, const AddImageBrushRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rd = app->resources();
		try {
			rd->add(request->key(), request->value());
		}
		catch (std::logic_error &e)
		{
			response->set_msg(e.what());
			response->set_success(false);
		}
		this->taskReady();
	};
	return waitForTaskReady(task);
}

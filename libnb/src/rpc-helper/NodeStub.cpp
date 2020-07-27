#include "NodeStub.h"
#include "newbrush/core/base/DateTime.h"
#include "newbrush/core/base/Thickness.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/media/ImageBrush.h"
#include "newbrush/core/media/ImageSource.h"
#include "newbrush/core/media/GradientBrush.h"
#include "newbrush/core/DependencyProperty.h"

Status NodeStub::AddNode(ServerContext * context, const AddNodeRequest * request, CommonReply * response)
{
	auto task = [this, request, response]() 
	{
		auto const &path = request->path();
		auto parent = VisualTreeHelper::lookupNode(Application::current()->mainWindow(), path);
		auto const &childTypeName = request->childtype();
		auto childType = rttr::type::get_by_name(childTypeName);
		var child = childType.create({});
		if (!parent || !child.is_valid())
		{
			response->set_success(false);
			response->set_msg(parent ? "childType is not registered" : "parent is not exist.");
			this->taskReady();
			return;
		}

		auto childNode = child.get_value<UIElementPtr>();
		if (nb::is<ContentControl>(parent))
		{
			auto content = parent->getValue<UIElementPtr>(ContentControl::ContentProperty());
			if (content)
			{
				response->set_success(false);
				response->set_msg("parent already has content");
			}
			else
			{
				response->set_success(true);
				parent->setValue(ContentControl::ContentProperty(), childNode);
			}
		}
		else if (nb::is<Panel>(parent))
		{
			auto panel = nb::as<Panel>(parent);
			panel->children().add(childNode);
		}
		else
		{

		}
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::RemoveNode(ServerContext * context, const RemoveNodeRequest * request, CommonReply * response)
{
	return Status();
}

Status NodeStub::RenameNode(ServerContext * context, const RenameNodeRequest * request, CommonReply * response)
{
	return Status();
}

Status NodeStub::SetProperty(ServerContext * context, const SetPropertyRequest * request, CommonReply * response)
{
	response->set_success(false);
	auto task = [this, request, response]()
	{
		const auto &stringValue = request->propertyvalue();
		auto propertyType = rttr::type::get_by_name(request->propertytype());
		auto d = VisualTreeHelper::lookupNode(Application::current()->mainWindow(), request->path());
		auto const &dp = DependencyProperty::find(request->propertyid());
		if (!propertyType)
		{
			response->set_msg("type not registered");
		}
		else if (!d)
		{
			response->set_msg("node not exists");
		}
		else if (!dp)
		{
			response->set_msg("property not exists");
		}
		else
		{
			try {
				var v = stringValueToVar(propertyType, stringValue);
				d->setValue(dp, v);
				response->set_success(true);
			}
			catch (std::exception &e)
			{
				response->set_msg(e.what());
			}
		}
		this->taskReady();
	};

	return waitForTaskReady(task);
}

var NodeStub::stringValueToVar(type t, const std::string & stringValue)
{
	var v = stringValue;
	bool b = v.convert(rttr::type(t));
	if (!b)
	{
		nbThrowException(std::logic_error, "[%s] can't convert to [%s]", v.get_type().get_name().data(), t.get_name().data());
	}
	return v;
}

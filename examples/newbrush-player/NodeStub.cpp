#include "NodeStub.h"
#include "newbrush/core/MetaObject.h"

Status NodeStub::AddNode(ServerContext * context, const AddNodeRequest * request, CommonReply * response)
{
	auto task = [this, request, response]() 
	{
		auto const &path = request->path();
		auto parent = VisualTreeHelper::lookupNode(Application::current()->mainWindow(), path);
		auto childNode = MetaObject::makeObject(request->childtype());
		if (!parent || !childNode)
		{
			response->set_success(false);
			response->set_msg(parent ? "childType is not registered" : "parent is not exist.");
			this->taskReady();
			return;
		}

		auto child = nb::as<UIElement>(childNode);
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
				parent->setValue(ContentControl::ContentProperty(), child);
			}
		}
		else if (nb::is<Panel>(parent))
		{
			auto panel = nb::as<Panel>(parent);
			panel->children().add(child);
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

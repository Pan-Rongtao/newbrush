#include "NodeStub.h"
#include "newbrush/core/DateTime.h"
#include "newbrush/media/Thickness.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/GradientBrush.h"
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
			response->set_msg("类型未注册");
		}
		else if (!d)
		{
			response->set_msg("节点不存在");
		}
		else if (!dp)
		{
			response->set_msg("属性不存在");
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

void registerConvertor()
{
	static bool b = false;
	if (b)	return;

	type::register_converter_func([](const std::string &str, bool &ok)->std::shared_ptr<Brush>
	{
		ok = true;
		BrushPtr brush;

		std::vector<std::string> segms = nb::stringSplit(str, ",", true);
		if (segms.size() == 1)
		{
			auto imgSource = std::make_shared<ImageSource>();
			imgSource->load((const unsigned char *)str.data(), str.size());
			brush = std::make_shared<ImageBrush>(imgSource);
		}
		else if (segms.size() == 4)
		{
			auto r = std::stoi(segms[0]);
			auto g = std::stoi(segms[1]);
			auto b = std::stoi(segms[2]);
			auto a = std::stoi(segms[3]);
			nb::Color c = nb::Color(a, r, g, b);
			brush = std::make_shared<SolidColorBrush>(c);
		}
		return brush;
	});

	b = true;
}

var NodeStub::stringValueToVar(type t, const std::string & stringValue)
{
	registerConvertor();
	var v = stringValue;
	bool b = v.convert(rttr::type(t));
	if (!b)
	{
		nbThrowException(std::logic_error, "[%s] can't convert to [%s]", v.get_type().get_name().data(), t.get_name().data());
	}
	return v;
}

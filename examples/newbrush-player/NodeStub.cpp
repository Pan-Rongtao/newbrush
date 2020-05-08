#include "NodeStub.h"
#include "newbrush/core/MetaObject.h"
#include "newbrush/core/DateTime.h"
#include "newbrush/media/Thickness.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/GradientBrush.h"

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

Status NodeStub::SetPropertyBool(ServerContext * context, const SetPropertyBoolRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyInt8(ServerContext * context, const SetPropertyInt8Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyInt16(ServerContext * context, const SetPropertyInt16Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyInt32(ServerContext * context, const SetPropertyInt32Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyInt64(ServerContext * context, const SetPropertyInt64Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyUInt8(ServerContext * context, const SetPropertyUInt8Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyUInt16(ServerContext * context, const SetPropertyUInt16Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyUInt32(ServerContext * context, const SetPropertyUInt32Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyUInt64(ServerContext * context, const SetPropertyUInt64Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyFloat(ServerContext * context, const SetPropertyFloatRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyDouble(ServerContext * context, const SetPropertyDoubleRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyString(ServerContext * context, const SetPropertyStringRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyVec2(ServerContext * context, const SetPropertyVec2Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), glm::vec2{ request->value().x(), request->value().y() });
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyVec3(ServerContext * context, const SetPropertyVec3Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), glm::vec3{ request->value().x(), request->value().y(), request->value().z() });
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyVec4(ServerContext * context, const SetPropertyVec4Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), glm::vec4{ request->value().x(), request->value().y(), request->value().z(), request->value().w() });
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyColor(ServerContext * context, const SetPropertyColorRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), nb::Color(request->value().a(), request->value().r(), request->value().g(), request->value().b()));
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyDateTime(ServerContext * context, const SetPropertyDateTimeRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto const &ptDt = request->value();
		nb::DateTime dt(ptDt.year(), ptDt.month(), ptDt.day(), ptDt.hour(), ptDt.minute(), ptDt.second(), ptDt.millisecond(), ptDt.microsecond());
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), dt);
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyTimeSpan(ServerContext * context, const SetPropertyTimeSpanRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), nb::TimeSpan::fromMicroseconds(request->value().micros()));
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyThickness(ServerContext * context, const SetPropertyThicknessRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		nb::Thickness tn(request->value().left(), request->value().top(), request->value().right(), request->value().bottom());
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), tn);
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyEnum(ServerContext * context, const SetPropertyEnumRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), request->value());
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertySolidColorBrush(ServerContext * context, const SetPropertySolidColorBrushRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto const &color = request->value();
		auto solidColorBrush = std::make_shared<SolidColorBrush>(nb::Color(color.a(), color.r(), color.g(), color.b()));
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), solidColorBrush);
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyImageBrush(ServerContext * context, const SetPropertyImageBrushRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto const &imgStream = request->value();
		auto imgSource = std::make_shared<ImageSource>();
		auto imgBrush = std::make_shared<ImageBrush>(imgSource);
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), imgBrush);
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status NodeStub::SetPropertyLinearGradientBrush(ServerContext * context, const SetPropertyLinearGradientBrushRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto const &imgStream = request->value();
		auto linearBrush = std::make_shared<LinearGradientBrush>();
		auto ret = this->_setProperty(request->base().path(), request->base().propertyid(), linearBrush);
		response->set_success(ret.first);
		response->set_msg(ret.second);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

std::pair<bool, std::string> NodeStub::_setProperty(const std::string & path, uint64 propertyID, const Poco::Dynamic::Var & v)
{
	std::pair<bool, std::string> ret{ true, "" };
	auto d = VisualTreeHelper::lookupNode(Application::current()->mainWindow(), path);
	if (d)
	{
		auto const &dp = DependencyProperty::find(propertyID);
		try {
			d->setValue(dp, v);
		}
		catch (std::exception &e)
		{
			ret.first = false;
			ret.second = e.what();
		}
	}
	return ret;
}

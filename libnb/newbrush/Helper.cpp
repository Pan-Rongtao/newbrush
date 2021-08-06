#include "newbrush/Helper.h"
#include "newbrush/Components.h"
#include "newbrush/Animation.h"
#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Renderer2D.h"

#include "IconFontCpp/IconsFontAwesome5Pro.h"
#include "IconFontCpp/IconsMaterialDesign.h"
#include "rttr/rttr_cast.h"


using namespace nb;

Node2D * TreeHelper::getRoot(Node2D * node)
{
	auto *root = node;
	while (root->getParent())
	{
		root = root->getParent();
	}
	return root;
}

Point TreeHelper::getWolrdOffset(Node2D *node)
{
	Point pt;
	auto p = node;
	do {
		auto offset = p->getOffsetToParent();
		pt += offset;
	} while ((p->getParent()) && (p = p->getParent()));
	return pt;
}

std::vector<ref<Node2D>> TreeHelper::getAllChildren(ref<Node2D> node)
{
	std::function<void(ref<Node2D> node, std::vector<ref<Node2D>> &nodes)> loop = [&loop](ref<Node2D> node, std::vector<ref<Node2D>> &nodes)
	{
		for (auto child : node->children())
		{
			nodes.push_back(child);
			if (!child->children().empty())
				loop(child, nodes);
		}
	};
	std::vector<ref<Node2D>> ret{ node };
	loop(node, ret);
	return ret;
}

void TreeHelper::touchThunk(ref<Node2D> node, const TouchEventArgs &e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->touchThunk(e);
		}
	}

}

void TreeHelper::scrollThunk(ref<Node2D> node, const ScrollEventArgs & e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->scrollThunk(e);
		}
	}
}

void TreeHelper::keyThunk(ref<Node2D> node, const KeyEventArgs & e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->keyThunk(e);
		}
	}
}

glm::vec4 TreeHelper::getBox(const std::vector<glm::vec2>& points)
{
	if (points.empty())
	{
		return glm::vec4{ 0.0f };
	}
	else
	{
		auto xMinMax = std::minmax_element(points.begin(), points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.x > p0.x; });
		auto yMinMax = std::minmax_element(points.begin(), points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.y > p0.y; });
		auto box = glm::vec4(xMinMax.first->x, yMinMax.first->y, xMinMax.second->x - xMinMax.first->x, yMinMax.second->y - yMinMax.first->y);
		return box;
	}
}

static float g_fps = 0.0f;
std::string SystemHelper::getSystemInfos()
{
	auto sRenderer = glGetString(GL_RENDERER);
	auto sVendor = glGetString(GL_VENDOR);
	auto sGLVersion = glGetString(GL_VERSION);
	auto sLanVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	int r, g, b, a, depth, stencil;
#ifdef NB_USE_GLAD
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_BACK_LEFT, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &r);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_BACK_LEFT, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &g);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_BACK_LEFT, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &b);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_BACK_LEFT, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &a);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &depth);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencil);
#else
	glGetIntegerv(GL_RED_BITS, &r);
	glGetIntegerv(GL_GREEN_BITS, &g);
	glGetIntegerv(GL_BLUE_BITS, &b);
	glGetIntegerv(GL_ALPHA_BITS, &a);
	glGetIntegerv(GL_DEPTH_BITS, &depth);
	glGetIntegerv(GL_STENCIL_BITS, &stencil);
#endif

	int samples, samplebuffers;
	glGetIntegerv(GL_SAMPLES, &samples);
	glGetIntegerv(GL_SAMPLE_BUFFERS, &samplebuffers);

	const unsigned char *nul = (const unsigned char *)"";
	auto s = fmt::format("\n\
System Info:\n\
	OpenGL context renderer	: {}\n\
	OpenGL context vendor	: {}\n\
	OpenGL context OpenGL	: {}\n\
	OpenGL context GLSL	: {}\n\
	OpenGL context config	: r,g,b,a,depth,stencil=[{},{},{},{},{},{}]\n\
	OpenGL context samplers	: {},{}\n\
", sRenderer ? sRenderer : nul, sVendor ? sVendor : nul, sGLVersion ? sGLVersion : nul, sLanVersion ? sLanVersion : nul, r, g, b, a, depth, stencil, samples, samplebuffers);

	return s;
}

void SystemHelper::printSystemInfos()
{
	Log::info("{}", SystemHelper::getSystemInfos());
}

void SystemHelper::updateFPS()
{
	static auto lastTime = getMilliseconds();
	static auto frameCount = 0;

	++frameCount;

	auto curTime = getMilliseconds();
	if (curTime - lastTime > 1000)
	{
		g_fps = (float)frameCount;
		frameCount = 0;
		lastTime = curTime;
	}
}

float SystemHelper::getFPS()
{
	return g_fps;
}

ref<Timer> g_timerSystemInfo;
void SystemHelper::enableFPSInfo(bool enable)
{
	if (enable)
	{
		g_timerSystemInfo = createRef<Timer>();
		g_timerSystemInfo->start(5000);
		g_timerSystemInfo->Tick += [](const EventArgs &e)
		{
			auto state = Renderer2D::getStats();
			Log::info("drawCount={}, quadCount={}, batch fps:{}", state.drawCount, state.quadCount, getFPS());
		};
	}
	else
	{
		g_timerSystemInfo = nullptr;
	}
}

//enum类型需要主动注册，因为需要把枚举值注册
//控件类型需主动注册，因为需要注册构造函数和metadata
//作为Property的属性值类型不要主动注册，让RTTR自动生成（用到什么就会自动生成什么）

//name|icon|description
rttr::detail::metadata makeClassMeta(const std::string &name, const std::string &icon, const std::string &description)
{
	return rttr::detail::metadata("ClassMeta", std::tuple<std::string, std::string, std::string>{ name, icon, description });
}

RTTR_PLUGIN_REGISTRATION
{
	auto globalVarsInitCost = nb::getStarupMilliseconds() - nb::getMilliseconds();
	Log::info("global vars init cost [{}] ms.", globalVarsInitCost);
	RttrRegistration::doRegister();

	SystemHelper::enableFPSInfo(true);
}

void RttrRegistration::doRegister()
{
	static bool registered = false;
	if (registered)	return;

	auto t0 = nb::getMilliseconds();
	registerEnums();
	auto t1 = nb::getMilliseconds();
	registerTypes();
	auto t2 = nb::getMilliseconds();
	registerConverters();
	auto t3 = nb::getMilliseconds();
	registered = true;
	Log::info("rttr register [Enums|Types|Converters|All] cost [{}+{}+{}={}] ms", t1 - t0, t2 - t1, t3 - t2, t3 - t0);
#if 0
	auto range = type::get_types();
	std::vector<type> vtTypes(range.begin(), range.end());
	std::string s;
	for (auto t : vtTypes)
	{
		s = s + t.get_name().data() + "\n";
	}
#endif
}

void RttrRegistration::registerEnums()
{
	registration::enumeration<HorizontalAlignmentE>("nb::HorizontalAlignmentE")
		(
			value("Left", HorizontalAlignmentE::Left),
			value("Center", HorizontalAlignmentE::Center),
			value("Right", HorizontalAlignmentE::Right),
			value("Stretch", HorizontalAlignmentE::Stretch)
		);

	registration::enumeration<EasingModeE>("nb::EasingModeE")
		(
			value("EaseIn", EasingModeE::EaseIn),
			value("EaseOut", EasingModeE::EaseOut),
			value("EaseInOut", EasingModeE::EaseInOut)
		);

	registration::enumeration<FillBehaviorE>("nb::FillBehaviorE")
		(
			value("HoldEnd", FillBehaviorE::HoldEnd),
			value("Stop", FillBehaviorE::Stop)
		);

	registration::enumeration<TimelineStateE>("nb::TimelineStateE")
		(
			value("Active", TimelineStateE::Active),
			value("Filling", TimelineStateE::Filling),
			value("Stopped", TimelineStateE::Stopped)
		);

}

//虚基类不需要类描述（不需要创建，因此不需要再STUDIO显示）
//如果没有注册property，只会有T信息；只要注册了property就会有T,T*,std::shared<T>信息
void RttrRegistration::registerTypes()
{
	registration::class_<glm::vec2>("glm::vec2") ();
	registration::class_<glm::vec3>("glm::vec3") ();
	registration::class_<glm::vec4>("glm::vec4") ();
	registration::class_<nb::Color>("nb::Color") ();
	registration::class_<nb::TimeSpan>("nb::TimeSpan") ();

	registration::class_<nb::Object>("nb::Object") ();
	registration::class_<nb::Node>("nb::Node") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Name", &Node::getName, &Node::setName)
		;

	registration::class_<Transform>("nb::Transform") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Translate", &Transform::getTranslate, &Transform::setTranslate)
		.property("Rotate", &Transform::getRotate, &Transform::setRotate)
		.property("Scale", &Transform::getScale, &Transform::setScale)
		;

	registration::class_<Transform2D>("nb::Transform2D") ()
		;

	registration::class_<ScaleTransform2D>("nb::ScaleTransform2D") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("ScaleX", &ScaleTransform2D::getScaleX, &ScaleTransform2D::setScaleX)
		.property("ScaleY", &ScaleTransform2D::getScaleY, &ScaleTransform2D::setScaleY)
		.property("Scale", &ScaleTransform2D::getScale, &ScaleTransform2D::setScale)
		.property("CenterX", &ScaleTransform2D::getCenterX, &ScaleTransform2D::setCenterX)
		.property("CenterY", &ScaleTransform2D::getCenterY, &ScaleTransform2D::setCenterY)
		;

	registration::class_<Shader>("nb::Shader")()
		;

	registration::class_<Texture>("nb::Texture") ()
		;

	registration::class_<Material>("nb::Material")()
		.property("Name", &Material::name)
		.property("Shader", &Material::shader)
		;

	registration::class_<PhongMaterial>("nb::PhongMaterial") ()
		.property("Ambient", &PhongMaterial::ambientColor)
		.property("Diffuse", &PhongMaterial::diffuseColor)
		.property("Specular", &PhongMaterial::specularColor)
		.property("Emission", &PhongMaterial::emissionColor)
		.property("Shineness", &PhongMaterial::shineness)
		.property("DiffuseMapping", &PhongMaterial::diffuseMapping)
		.property("SpecularMapping", &PhongMaterial::specularMapping)
		.property("EmissionMapping", &PhongMaterial::emissionMapping)
		;

	registration::class_<ReflectMaterial>("nb::ReflectMaterial") ()
		.property("Ambient", &ReflectMaterial::ambient)
		.property("Diffuse", &ReflectMaterial::diffuse)
		.property("Specular", &ReflectMaterial::specular)
		.property("DiffuseMapping", &ReflectMaterial::diffuseMapping)
		.property("SpecularMapping", &ReflectMaterial::cubeMapping)
		;

	registration::class_<Timeline>("nb::Timeline") ()
		.property("BeginTime", &Timeline::beginTime)
		.property("Duration", &Timeline::duration)
		.property("AutoReverse", &Timeline::autoReverse)
		.property("Reverse", &Timeline::reverse)
		.property("FillBehavior", &Timeline::fillBehavior)
		;

	registration::class_<Animation>("nb::Animation") ()
		.property("Name", &Animation::name)
		.property("Target", &Animation::target, &Animation::setTarget)
		.property("TargetProperty", &Animation::targetProperty, &Animation::setTargetProperty)
		.property("TargetPropertyName", &Animation::targetPropertyName, &Animation::setTargetPropertyName)
		;

	registration::class_<Int32Animation>("nb::Int32Animation") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("From", &Int32Animation::from, &Int32Animation::setFrom)
		.property("To", &Int32Animation::to, &Int32Animation::setTo)
		.property("EasingFunction", &Int32Animation::easingFunction, &Int32Animation::setEasingFunction)
		;

	registration::class_<FloatAnimation>("nb::FloatAnimation") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("From", &FloatAnimation::from, &FloatAnimation::setFrom)
		.property("To", &FloatAnimation::to, &FloatAnimation::setTo)
		.property("EasingFunction", &FloatAnimation::easingFunction, &FloatAnimation::setEasingFunction)
		;

	registration::class_<PerspectiveCamera>("nb::PerspectiveCamera") (makeClassMeta("PerspectiveCamera", ICON_FA_CAMERA_ALT, "摄像机"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Fov", &PerspectiveCamera::getFov, &PerspectiveCamera::setFov)
		.property("Aspect", &PerspectiveCamera::getAspect, &PerspectiveCamera::setAspect)
		.property("NearPlane", &PerspectiveCamera::getNearPlane, &PerspectiveCamera::setNearPlane)
		.property("FarPlane", &PerspectiveCamera::getFarPlane, &PerspectiveCamera::setFarPlane)
		;

	registration::class_<Light>("nb::Light")()
		.property("Name", &Light::name)
		.property("Ambient", &Light::ambient)
		.property("Diffuse", &Light::diffuse)
		.property("Specular", &Light::specular)
		;

	registration::class_<AmbientLight>("nb::AmbientLight") ()
		;

	registration::class_<DirectionalLight>("nb::DirectionalLight") (makeClassMeta("DirectionalLight", ICON_FA_SUN_DUST, "定向光源"))
		.property("Direction", &DirectionalLight::direction)
		;

	registration::class_<PointLightBase>("nb::PointLightBase")()
		.property("Position", &PointLightBase::position)
		.property("ConstantAttenuation", &PointLightBase::constantAttenuation)
		.property("LinearAttenuation", &PointLightBase::linearAttenuation)
		.property("QuadraticAttenuation", &PointLightBase::quadraticAttenuation)
		;

	registration::class_<PointLight>("nb::PointLight") (makeClassMeta("PointLight", ICON_FA_LIGHTBULB_ON, "点光源"))
		;

	registration::class_<SpotLight>("nb::SpotLight") (makeClassMeta("SpotLight", ICON_FA_LAMP_DESK, "聚光灯光源"))
		.property("Direction", &SpotLight::direction)
		.property("InnerConeAngle", &SpotLight::innerConeAngle)
		.property("OuterConeAngle", &SpotLight::outerConeAngle)
		;

	registration::class_<Scene>("nb::Scene")(makeClassMeta("Scene", ICON_FA_OBJECT_GROUP, "场景"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		;

	registration::class_<ImageBrush>("nb::ImageBrush") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		;

	registration::class_<Node2D>("nb::Node2D") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Opacity", &Node2D::getOpacity, &Node2D::setOpacity)
		.property("Position", &Node2D::position, &Node2D::setPosition)
		.property("Size", &Node2D::size, &Node2D::setSize)
		.property("Margin", &Node2D::margin, &Node2D::setMargin)
		.property("HorizontalAlignment", &Node2D::horizontalAlignment, &Node2D::setHorizontalAlignment)
		.property("Background", &Node2D::background, &Node2D::setBackground)
		;

}

#define NB_STR_TO_OBJ(objType, str, count) \
objType ret; \
auto segms = nb::stringSplit(str, ",", true); \
if (segms.size() != count) { ok = false; } \
else { ok = true; for(auto i = 0; i < count; ++i) ret[i] = std::stof(segms[i]); } \
return ret;

#define NB_STR_TO_OBJ_I4(objType, str) \
objType ret; \
auto segms = nb::stringSplit(str, ",", true); \
if (segms.size() != 4) { ok = false; } \
else { ok = true; ret = objType(std::stoi(segms[0]), std::stoi(segms[1]), std::stoi(segms[2]), std::stoi(segms[3])); } \
return ret;

void RttrRegistration::registerConverters()
{
	type::register_wrapper_converter_for_base_classes<ref<ImageBrush>>();

	//string to glm::vec2("x,y")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec2 { NB_STR_TO_OBJ(glm::vec2, s, 2); });

	//string to glm::vec3("x,y,z")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec3 { NB_STR_TO_OBJ(glm::vec3, s, 3); });

	//string to glm::vec4("x,y,z,w")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec4 { NB_STR_TO_OBJ(glm::vec4, s, 4); });

	//string to nb::Color("r,g,b,a")
	type::register_converter_func([](const std::string &s, bool &ok)->Color { NB_STR_TO_OBJ_I4(Color, s); });

	//string to Timespan("h,m,s,ms")
	type::register_converter_func([](const std::string &s, bool &ok)->TimeSpan { NB_STR_TO_OBJ_I4(TimeSpan, s); });

	//int64_t to Timespan
	type::register_converter_func([](int64_t milliseconds, bool &ok)->TimeSpan { ok = true; return TimeSpan::fromMilliseconds((int)milliseconds); });

	//std::string to Bitmap
	type::register_converter_func([](const std::string &s, bool &ok)->ref<Bitmap> { ok = true; return createRef<Bitmap>(s); });
}

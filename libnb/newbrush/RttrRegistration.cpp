#include "newbrush/RttrRegistration.h"
#include "newbrush/Node.h"
#include "newbrush/Animation.h"
#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Mesh.h"
#include "newbrush/Transform.h"
#include "newbrush/Brush.h"
#include "newbrush/Node2D.h"
#include "newbrush/Components.h"

#include "IconFontCpp/IconsFontAwesome5Pro.h"
#include "IconFontCpp/IconsMaterialDesign.h"

#include <rttr/rttr_cast.h>
using namespace nb;

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
	RttrRegistration::doRegister();
}

void RttrRegistration::doRegister()
{
	static bool registered = false;
	if (registered)	return;

	auto t0 = nb::getMilliseconds();
	registerEnums();
	auto t1 = nb::getMilliseconds();
	Log::info("registerEnums cost [{}] ms.", t1 - t0);
	registerTypes();
	auto t2 = nb::getMilliseconds();
	Log::info("registerTypes cost [{}] ms.", t2 - t1);
	registerConverters();
	auto t3 = nb::getMilliseconds();
	Log::info("registerConverters cost [{}] ms.", t3 - t2);
	registered = true;
	Log::info("Rttr doRegister all cost [{}] ms.", t3 - t0);

	auto range = type::get_types();
	std::vector<type> vtTypes(range.begin(), range.end());
	std::string s;
	for (auto t : vtTypes)
	{
		s = s + t.get_name().data() + "\n";
	}

}

void RttrRegistration::registerEnums()
{
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

	registration::class_<CubemapMaterial>("nb::CubemapMaterial") ()
		.property("Ambient", &CubemapMaterial::ambient)
		.property("Diffuse", &CubemapMaterial::diffuse)
		.property("Specular", &CubemapMaterial::specular)
		.property("DiffuseMapping", &CubemapMaterial::diffuseMapping)
		.property("SpecularMapping", &CubemapMaterial::cubeMapping)
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
		.property("Texture", &ImageBrush::texture)
		.property("TargetOffset", &ImageBrush::targetOffset)
		.property("TargetSize", &ImageBrush::targetSize)
		.property("Rotated", &ImageBrush::rotated)
		;

	registration::class_<Node2D>("nb::Node2D") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Background", &Node2D::background, &Node2D::setBackground)
		.property("Opacity", &Node2D::getOpacity, &Node2D::setOpacity)
		.property("X", &Node2D::x, &Node2D::setX)
		;

}

void RttrRegistration::registerConverters()
{
	type::register_wrapper_converter_for_base_classes<ref<ImageBrush>>();

	//string to glm::vec2( "x,y")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec2
	{
		glm::vec2 ret;
		auto segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 2)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret = { std::stof(segms[0]), std::stof(segms[1]) };
		}
		return ret;
	});

	//string to glm::vec3( "x,y,z")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec3
	{
		glm::vec3 ret;
		auto segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 3)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret = { std::stof(segms[0]), std::stof(segms[1]), std::stof(segms[2]) };
		}
		return ret;
	});

	//string to glm::vec4( "x,y,z,w")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec4
	{
		glm::vec4 ret;
		auto segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 3)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret = { std::stof(segms[0]), std::stof(segms[1]), std::stof(segms[2]), std::stof(segms[3]) };
		}
		return ret;
	});

	//string to nb::Color( "r,g,b,a")
	type::register_converter_func([](const std::string &s, bool &ok)->Color 
	{
		Color ret;
		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 4)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret = Color(std::stoi(segms[0]), std::stoi(segms[1]), std::stoi(segms[2]), std::stoi(segms[3]));
		}
		return ret;
	});

	//string to Timespan("h,m,s,ms")
	type::register_converter_func([](const std::string &s, bool &ok)->TimeSpan 
	{
		TimeSpan ret;
		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 4)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret = { std::stoi(segms[0]), std::stoi(segms[1]), std::stoi(segms[2]), std::stoi(segms[3]) };
		}
		return ret;
	});
	//int64_t to Timespan
	type::register_converter_func([](int64_t milliseconds, bool &ok)->TimeSpan
	{
		ok = true;
		return TimeSpan::fromMilliseconds((int)milliseconds);
	});

	//std::string to Bitmap
	type::register_converter_func([](const std::string &s, bool &ok)->ref<Bitmap>
	{
		ok = true;
		return createRef<Bitmap>(s);
	});
}

#include "newbrush/model/RttrRegistration.h"
#include "newbrush/model/Node.h"
#include "newbrush/model/Animation.h"
#include "newbrush/model/Scene3D.h"
#include "newbrush/model/Log.h"
#include "newbrush/model/StringFunctions.h"
#include "newbrush/model/ModelImporter.h"

using namespace nb;
using namespace rttr;

//enum类型需要主动注册，因为需要把枚举值注册
//控件类型需主动注册，因为需要注册构造函数和metadata
//作为Property的属性值类型不要主动注册，让RTTR自动生成（用到什么就会自动生成什么）

detail::metadata nb::ClassDescriptorMetadata(const std::string &category, const std::string &dispayName, const std::string &description)
{
	return metadata(RttrMetadataIndex::ClassDescriptor, std::make_shared<ClassDescriptor>(ClassDescriptor{ category, dispayName, description }));
}

RTTR_REGISTRATION
{
	RttrRegistration::doRegister();
}

void RttrRegistration::doRegister()
{
	static bool registered = false;
	if (registered)	return;

	auto t0 = nb::getTickCount();
	registerEnums();
	auto t1 = nb::getTickCount();
	Log::info("registerEnums cost [{}] ms.", t1 - t0);
	registerTypes();
	auto t2 = nb::getTickCount();
	Log::info("registerTypes cost [{}] ms.", t2 - t1);
	registerConverters();
	auto t3 = nb::getTickCount();
	Log::info("registerConverters cost [{}] ms.", t3 - t2);
	registered = true;
	Log::info("Rttr doRegister all cost [{}] ms.", t3 - t0);

	auto range = type::get_types();
	std::vector<type> vtTypes(range.begin(), range.end());
	std::string s;
	for (auto t : vtTypes)
	{
		s = s + t.get_name().data() + "\r\n";
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

	registration::enumeration<StateE>("nb::StateE")
	(
		value("EaseIn", StateE::Active),
		value("EaseOut", StateE::Filling),
		value("EaseInOut", StateE::Stopped)
	);
	
	registration::enumeration<TextureTypeE>("nb::TextureTypeE")
	(
		value("Texture2D", TextureTypeE::Texture2D),
		value("TextureCubemap", TextureTypeE::TextureCubemap)
	);
	
	registration::enumeration<TextureWrappingE>("nb::TextureWrappingE")
	(
		value("Repeat", TextureWrappingE::Repeat),
		value("MirroredRepeat", TextureWrappingE::MirroredRepeat),
		value("ClampToEdge", TextureWrappingE::ClampToEdge),
		value("ClampToBorder", TextureWrappingE::ClampToBorder)
	);
	
	registration::enumeration<TextureFilterE>("nb::TextureFilterE")
	(
		value("Point", TextureFilterE::Point),
		value("Bilinear", TextureFilterE::Bilinear),
		value("Trilinear", TextureFilterE::Trilinear),
		value("Anisotropic", TextureFilterE::Anisotropic)
	);
	
	registration::enumeration<ShaderTypeE>("nb::ShaderType")
	(
		value("Vertex", ShaderTypeE::Vertex),
		value("Fragment", ShaderTypeE::Fragment)
	);
	
}

//虚基类不需要类描述（不需要创建，因此不需要再STUDIO显示）
void RttrRegistration::registerTypes()
{
	registration::class_<Transform>("nb::Transform") ()
		.constructor<>() ()
		.property("Position", &Transform::position, &Transform::setPosition)
		.property("Rotate", &Transform::rotate, &Transform::setRotate)
		.property("RotateX", &Transform::rotateX, &Transform::setRotateX)
		.property("RotateY", &Transform::rotateY, &Transform::setRotateY)
		.property("RotateZ", &Transform::rotateZ, &Transform::setRotateZ)
		.property("Scale", &Transform::scale, &Transform::setScale)
		.property("ScaleCenter", &Transform::scaleCenter, &Transform::setScaleCenter)
		;

	registration::class_<Camera>("nb::Camera") ( ClassDescriptorMetadata("渲染", "Camera", "摄像机") )
		.constructor<>() ( policy::ctor::as_std_shared_ptr )
		.property("Position", &Camera::position, &Camera::setPosition)
		.property("Fov", &Camera::fov, &Camera::setFOV)
		.property("Aspect", &Camera::aspect, &Camera::setAspect)
		.property("NearPlane", &Camera::nearPlane, &Camera::setNearPlane)
		.property("FarPlane", &Camera::farPlane, &Camera::setFarPlane)
		;
	/*
	auto range1 = type::get_types();
	std::vector<type> vtTypes1(range1.begin(), range1.end());
	std::string s1;
	for (auto t : vtTypes1)
	{
		s1 = s1 + t.get_name().data() + "\r\n";
	}
	*/
	registration::class_<Light>("nb::Light")()
		.property("Name", &Light::name, &Light::setName)
		.property("Ambient", &Light::ambient, &Light::setAmbient)
		.property("Diffuse", &Light::diffuse, &Light::setDiffuse)
		.property("Specular", &Light::specular, &Light::setSpecular)
		;

	registration::class_<AmbientLight>("nb::AmbientLight") (ClassDescriptorMetadata("渲染", "AmbientLight", "环境光源"))
		;

	registration::class_<DirectionalLight>("nb::DirectionalLight") (ClassDescriptorMetadata("渲染", "DirectionalLight", "方向光源"))
		.property("Direction", &DirectionalLight::direction, &DirectionalLight::setDirection)
		;

	registration::class_<PointLightBase>("nb::PointLightBase")()
		.property("Position", &PointLightBase::position, &PointLightBase::setPosition)
		.property("ConstantAttenuation", &PointLightBase::constantAttenuation, &PointLightBase::setConstantAttenuation)
		.property("LinearAttenuation", &PointLightBase::linearAttenuation, &PointLightBase::setLinearAttenuation)
		.property("QuadraticAttenuation", &PointLightBase::quadraticAttenuation, &PointLightBase::setQuadraticAttenuation)
		;

	registration::class_<PointLight>("nb::PointLight") (ClassDescriptorMetadata("渲染", "PointLight", "点光源"))
		;

	registration::class_<SpotLight>("nb::SpotLight") (ClassDescriptorMetadata("渲染", "SpotLight", "聚光灯光源"))
		.property("Direction", &SpotLight::direction, &SpotLight::setDirection)
		.property("InnerConeAngle", &SpotLight::innerConeAngle, &SpotLight::setInnerConeAngle)
		.property("OuterConeAngle", &SpotLight::outerConeAngle, &SpotLight::setOuterConeAngle)
		;

	registration::class_<Program>("nb::Program")()
		.property("VertexShaderSource", &Program::vertexShaderSource, &Program::setVertexShaderSource)
		.property("FragmentShaderSource", &Program::fragmentShaderSource, &Program::setFragmentShaderSource)
		;

	registration::class_<Material>("nb::Material")()
		.property("Name", &Material::name, &Material::setName)
		.property("Program", &Material::program, &Material::setProgram)
		;

	registration::class_<PhongMaterial>("nb::PhongMaterial") (ClassDescriptorMetadata("材质", "PhongMaterial", "冯氏光照模型材质"))
		.property("Ambient", &PhongMaterial::ambient, &PhongMaterial::setAmbient)
		.property("Diffuse", &PhongMaterial::diffuse, &PhongMaterial::setDiffuse)
		.property("Specular", &PhongMaterial::specular, &PhongMaterial::setSpecular)
		.property("Emission", &PhongMaterial::emission, &PhongMaterial::setEmission)
		.property("Shineness", &PhongMaterial::shineness, &PhongMaterial::setShineness)
		.property("DiffuseMapping", &PhongMaterial::diffuseMapping, &PhongMaterial::setDiffuseMapping)
		.property("SpecularMapping", &PhongMaterial::specularMapping, &PhongMaterial::setSpecularMapping)
		.property("EmissionMapping", &PhongMaterial::emissionMapping, &PhongMaterial::setEmissionMapping)
		;

	registration::class_<CubemapMaterial>("nb::CubemapMaterial") (ClassDescriptorMetadata("材质", "CubemapMaterial", "立方体材质"))
		.property("Ambient", &CubemapMaterial::ambient, &CubemapMaterial::setAmbient)
		.property("Diffuse", &CubemapMaterial::diffuse, &CubemapMaterial::setDiffuse)
		.property("Specular", &CubemapMaterial::specular, &CubemapMaterial::setSpecular)
		.property("DiffuseMapping", &CubemapMaterial::diffuseMapping, &CubemapMaterial::setDiffuseMapping)
		.property("SpecularMapping", &CubemapMaterial::cubeMapping, &CubemapMaterial::setCubeMapping)
		;

	registration::class_<Timeline>("nb::Timeline") (ClassDescriptorMetadata("动画", "Timeline", "时间线"))
		.property("BeginTime", &Timeline::beginTime, &Timeline::setBeginTime)
		.property("Duration", &Timeline::duration, &Timeline::setDuration)
		.property("AutoReversel", &Timeline::autoReversel, &Timeline::setAutoReversel)
		.property("FillBehavior", &Timeline::fillBehavior, &Timeline::setFillBehavior)
		;

	registration::class_<Animation>("nb::Animation") ()
		.property("Name", &Animation::name, &Animation::setName)
		.property("Target", &Animation::target, &Animation::setTarget)
		.property("TargetProperty", &Animation::targetProperty, &Animation::setTargetProperty)
		.property("TargetPropertyName", &Animation::targetPropertyName, &Animation::setTargetPropertyName)
		;

	registration::class_<Int32Animation>("nb::Int32Animation") (ClassDescriptorMetadata("动画", "Int32Animation", "整型属性动画"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("From", &Int32Animation::from, &Int32Animation::setFrom)
		.property("To", &Int32Animation::to, &Int32Animation::setTo)
		.property("EasingFunction", &Int32Animation::easingFunction, &Int32Animation::setEasingFunction)
		;

	registration::class_<FloatAnimation>("nb::FloatAnimation") (ClassDescriptorMetadata("动画", "FloatAnimation", "浮点属性动画"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("From", &FloatAnimation::from, &FloatAnimation::setFrom)
		.property("To", &FloatAnimation::to, &FloatAnimation::setTo)
		.property("EasingFunction", &FloatAnimation::easingFunction, &FloatAnimation::setEasingFunction)
		;

	registration::class_<Scene3D>("nb::Scene3D") (ClassDescriptorMetadata("3D场景", "Scene3D", "3D场景"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Width", &Scene3D::width, &Scene3D::setWidth)
		.property("Height", &Scene3D::height, &Scene3D::setHeight)
		.property("Camera", &Scene3D::camera, &Scene3D::setCamera)
		.property("Lights", select_overload<const std::vector<LightPtr>&() const>(&Scene3D::lights), &Scene3D::setLights)
		.property("Model", &Scene3D::model, &Scene3D::setModel)
		;
	registration::class_<Node>("nb::Node") (ClassDescriptorMetadata("节点", "Node", "节点"))
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Name", &Node::name, &Node::setName)
		.property("Transform", &Node::transform, &Node::setTransform)
		;

	registration::class_<Texture>("nb::Texture") ()
		.constructor<TextureTypeE>() (policy::ctor::as_std_shared_ptr)
		.property("WrappingS", &Texture::wrappingS, &Texture::setWrappingS)
		.property("WrappingT", &Texture::wrappingT, &Texture::setWrappingT)
		.property("MagnifyFilter", &Texture::magnifyFilter, &Texture::setMagnifyFilter)
		.property("NarrowFilter", &Texture::narrowFilter, &Texture::setNarrowFilter)
		.property("SamplerUnit", &Texture::samplerUnit, &Texture::setSamplerUnit)
		;

	registration::class_<ModelImporter>("nb::ModelImporter") ()
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("Path", &ModelImporter::path, &ModelImporter::setPath)
		.property_readonly("Node", &ModelImporter::getRootNode)
		;
}

void RttrRegistration::registerConverters()
{
	//string to glm::vec2( "x,y")
	type::register_converter_func([](const std::string &s, bool &ok)->glm::vec2
	{
		glm::vec2 ret;
		auto segms = StringFunctions::split(s, ",", true);
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
		auto segms = StringFunctions::split(s, ",", true);
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
		auto segms = StringFunctions::split(s, ",", true);
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

	//string to nb::Color( "a,r,g,b")
	type::register_converter_func([](const std::string &s, bool &ok)->Color 
	{
		Color ret;
		std::vector<std::string> segms = StringFunctions::split(s, ",", true);
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
		std::vector<std::string> segms = StringFunctions::split(s, ",", true);
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

	//string to transform
	type::register_converter_func([](const std::string &s, bool &ok)->TransformPtr
	{
		TransformPtr ret = std::make_shared<Transform>();
		auto segms = StringFunctions::split(s, ",", true, false);
		if (segms.size() != 9)
		{
			ok = false;
		}
		else
		{
			ok = true;
			ret->setPosition(glm::vec3(std::stof(segms[0]), std::stof(segms[1]), std::stof(segms[2])));
			ret->setRotate(glm::vec3(std::stof(segms[3]), std::stof(segms[4]), std::stof(segms[5])));
			ret->setScale(glm::vec3(std::stof(segms[6]), std::stof(segms[7]), std::stof(segms[8])));
		}
		return ret;
	});
}

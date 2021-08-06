#include "Sport.h"

constexpr char clockSPORT_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
varying vec2 v_uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char clockSPORT_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler;
uniform float u_radius;

void main( void )
{
	vec2 _uv = (v_uv + vec2(1.0,1.0))/2.0;

	_uv -= vec2(0.5, 0.5);
	float inside = step((_uv.x * _uv.x + _uv.y * _uv.y),0.25 * 0.9);
	_uv = _uv * (1.0-inside) + inside * vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
	_uv += vec2(0.5, 0.5);
					
	gl_FragColor = texture2D(u_sampler, _uv);
}
)";

class TriangleMaterial : public Material
{
public:
	TriangleMaterial(ref<Texture2D> tex)
		: Material(ShaderLibrary::get("shader_clockSPORT", clockSPORT_vs, clockSPORT_fs))
		, texture(tex)
		, angle(0.0f)
	{
		texture->setSamplerUnit(0);
		shader->use();
		shader->setInt("u_sampler", 0);
		shader->disuse();
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		shader->setFloat("u_radius", glm::radians(angle));
		if (texture) texture->activeAndBind();
	}

	ref<Texture2D> texture;
	float angle;
};

constexpr char clockpoint_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
varying vec2 v_uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char clockpoint_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler;
uniform float u_radius;

void main( void )
{
	vec2 _uv = v_uv;	

	_uv -= vec2(0.5, 0.5);
	float inside = step((_uv.x * _uv.x + _uv.y * _uv.y),0.25 * 0.9);
	_uv = _uv * (1.0-inside) + inside * vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
	_uv += vec2(0.5, 0.5);
					
	gl_FragColor = texture2D(u_sampler, _uv);
}
)";

class RectangleMaterial1 : public Material
{
public:
	RectangleMaterial1(ref<Texture2D> tex)
		: Material(ShaderLibrary::get("shader_clockpoint", clockpoint_vs, clockpoint_fs))
		, texture(tex)
		, angle(0.0f)
	{
		texture->setSamplerUnit(0);
		shader->use();
		shader->setInt("u_sampler", 0);
		shader->disuse();
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		shader->setFloat("u_radius", glm::radians(angle));
		if (texture) texture->activeAndBind();
	}

	ref<Texture2D> texture;
	float angle;
};

constexpr char halorect_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
varying vec2 v_uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char halorect_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler;
uniform float velocity;

const float PI = 3.1415926;

void main( void )
{
	vec4 color = vec4(0.0);
	float u_radius = velocity * 2.0 * PI;
	
	for(float r = 0.0;r < u_radius; r += 0.1)
	{
		vec2 _uv = v_uv;
		_uv -= vec2(0.5, 0.5);
		float inside = step((_uv.x * _uv.x + _uv.y * _uv.y),0.25 * 0.9);
		_uv = _uv * (1.0-inside) + inside * vec2(_uv.x * cos(r) + _uv.y * sin(r), _uv.x * sin(r) - _uv.y * cos(r));
		_uv += vec2(0.5, 0.5);
		vec4 temp = texture2D(u_sampler, _uv);
		if(temp.a == 0.0)
		{
			temp.rgb *= temp.a;
		}
		if(color.a == 0.0)
		{
			color += temp;
		}
	}
	vec4 color1 = color;
	color1.a = (1.5 - velocity) * 2.0;
	gl_FragColor = color * step(velocity,1.01) + color1 * step(1.01,velocity);
}
)";

class HaloMaterial : public Material
{
public:
	HaloMaterial(ref<Texture2D> tex)
		: Material(ShaderLibrary::get("shader_halorect", halorect_vs, halorect_fs))
		, texture(tex)
		, velocity(0.0f)
	{
		texture->setSamplerUnit(0);
		shader->use();
		shader->setInt("u_sampler", 0);
		shader->disuse();
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		shader->setFloat("velocity", velocity);
		if (texture) texture->activeAndBind();
	}

	ref<Texture2D> texture;
	float velocity;
};

constexpr char clockECO_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
varying vec2 v_uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char clockECO_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform float u_radius;

void main( void )
{
	vec2 _npos = (gl_FragCoord.xy - (u_resolution - vec2(756.0, 756.0))/2.0)/ vec2(756.0, 756.0);   // 0.0 .. 1.0
	vec2 _uv = (1.0 - _npos);

	_uv -= vec2(0.5, 0.5);
	float inside = step((_uv.x * _uv.x + _uv.y * _uv.y),0.25 * 0.9);
	_uv = _uv * (1.0-inside) + inside * vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
	_uv += vec2(0.5, 0.5);
					
	vec4 _color0 = texture2D(u_sampler0, _uv);
	vec4 _color1 = texture2D(u_sampler1, v_uv);
	vec4 color;
	if(_color1.r >= 0.9)
		color = mix(_color0, _color1, 0.2);
	gl_FragColor = color;
}
)";

class NumberMaterial : public Material
{
public:
	NumberMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2)
		: Material(ShaderLibrary::get("shader_clockECO", clockECO_vs, clockECO_fs))
		, texture1(tex1)
		, texture2(tex2)
		, angle(0.0f)
	{
		texture1->setSamplerUnit(0);
		texture2->setSamplerUnit(1);
		shader->use();
		shader->setInt("u_sampler0", 0);
		shader->setInt("u_sampler1", 1);
		shader->disuse();
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		float x, y, w, h;
		GLUtils::getViewport(x, y, w, h);
		shader->setFloat2("u_resolution", glm::vec2(w, h));
		shader->setFloat("u_radius", glm::radians(angle));
		if (texture1) texture1->activeAndBind();
		if (texture2) texture2->activeAndBind();
	}

	ref<Texture2D> texture1;
	ref<Texture2D> texture2;
	float angle;
};

#pragma region newest
#if 1
Trianglegroup::Trianglegroup()
{
	buildtrianglegroup();
}

void Trianglegroup::buildtrianglegroup()
{
	ref<TriangleNode> temp_node3d;
	Point pos(0.0f,0.0f);
	float Side_length = 0.1;
	const float PI = 3.1415926;
	for (int i = -7;i < 8;i++)
	{
		pos.x = i * Side_length;
		for (int j = -8;j<8;j++)
		{
			pos.y = j * Side_length * sin((60.0 / 180.0)*PI);
			temp_node3d = createRef<TriangleNode>(pos, Side_length, true);
			addChild(temp_node3d);
			temp_node3d = createRef<TriangleNode>(pos, Side_length, false);
			addChild(temp_node3d);
		}
	}
}

void Trianglegroup::setpos(Point pos)
{
	m_pos = pos;
}

Point Trianglegroup::getpos()
{
	return m_pos;
}

void Trianglegroup::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	for (auto child : children())
	{
		child->onRender(camera, lights);
	}
}

void TriangleNode::startanimation()
{
	m_Animation->setTarget(getTransform());
	m_Animation->setTargetPropertyName("Translate");
	m_Animation->setFrom(glm::vec3(0,0,0));
	m_Animation->setTo(glm::vec3(0, 0, 0.05));
	m_Animation->setEasingFunction(createRef<SineEase>());
	m_Animation->duration = TimeSpan::fromMilliseconds(3500);
	m_Animation->autoReverse = true;
	//m_Animation->repeatBehavior = RepeatBehavior::forever();
	m_Animation->begin();
}

TimelineStateE TriangleNode::isactive()
{
	return m_Animation->currentState();
}

Point TriangleNode::getpos()
{
	return m_pos;
}
ref<Material> TriangleNode::getmaterial()
{
	return m_materials;
}

TriangleNode::TriangleNode(Point pos, const float Side_length, bool up)
{
	const float PI = 3.1415926;
	std::vector<Vertex> vertexs(3);	
	if (up == true)
	{
		for (int i = 0; i < 3; i++)
		{
			if ((i % 2) == 0)
			{
				vertexs[i].position = { pos.x + Side_length * i * cos((60.0 / 180.0)*PI), pos.y ,0 };
			}
			else
			{
				vertexs[i].position = { pos.x + Side_length * i * cos((60.0 / 180.0)*PI), pos.y + Side_length * sin((60.0 / 180.0)*PI) ,0 };
			}
		}
	}
	else
	{
		for (int i = -1; i < 2; i++)
		{
			if ((i % 2) == 0)
			{
				vertexs[i+1].position = { pos.x + Side_length * i * cos((60.0 / 180.0)*PI), pos.y ,0 };
			}
			else
			{
				vertexs[i+1].position = { pos.x + Side_length * i * cos((60.0 / 180.0)*PI), pos.y + Side_length * sin((60.0 / 180.0)*PI) ,0 };
			}
		}
	}
	vertexs[0].uv = vertexs[0].position;
	vertexs[1].uv = vertexs[1].position;
	vertexs[2].uv = vertexs[2].position;

	std::vector<uint16_t> indices = { 0, 1, 2 };

	m_pos = caltrianglepos(vertexs);
	static auto tex = createRef<Texture2D>(RES_DIR"cxd706/img_clock_000021.png");
	m_materials = createRef<TriangleMaterial>(tex);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
	ref<Transform> temp_transform = createRef<Transform>();
	setTransform(temp_transform);
	m_Animation = createRef<Vec3Animation>();
}

Point TriangleNode::caltrianglepos(std::vector<Vertex> triangle)
{
	float x_pos = 0.0f;
	float y_pos = 0.0f;
	for (auto one : triangle)
	{
		x_pos += one.position.x;
		y_pos += one.position.y;
	}
	x_pos /= triangle.size();
	y_pos /= triangle.size();
	return(Point(x_pos, y_pos));
}

void TriangleNode::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	if (!m_mesh)
		return;
	else
	{
		glm::mat4 temp_matrix = getTransform()->value();
		m_mesh->draw(temp_matrix, camera, lights);
	}
}
#endif
#pragma endregion

RectangleClass::RectangleClass()
{
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = glm::vec3(-0.7, -0.7, 0.20);
	vertexs[1].position = glm::vec3(0.7, -0.7, 0.20);
	vertexs[2].position = glm::vec3(0.7, 0.7, 0.20);
	vertexs[3].position = glm::vec3(-0.7, 0.7, 0.20);

	vertexs[0].uv = glm::vec2(0.0, 0.0);
	vertexs[1].uv = glm::vec2(1.0, 0.0);
	vertexs[2].uv = glm::vec2(1.0, 1.0);
	vertexs[3].uv = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto tex = createRef<Texture2D>(RES_DIR"cxd706/img_clock_000001.png");
	m_materials = createRef<RectangleMaterial1>(tex);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);

}

void RectangleClass::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	m_mesh->draw(glm::mat4(1.0f), camera, lights);
}

ref<Material> RectangleClass::getmaterial()
{
	return m_materials;
}

HaloRectangle::HaloRectangle()
{
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = glm::vec3(-0.7, -0.7, 0.201);
	vertexs[1].position = glm::vec3(0.7, -0.7, 0.201);
	vertexs[2].position = glm::vec3(0.7, 0.7, 0.201);
	vertexs[3].position = glm::vec3(-0.7, 0.7, 0.201);

	vertexs[0].uv = glm::vec2(0.0, 0.0);
	vertexs[1].uv = glm::vec2(1.0, 0.0);
	vertexs[2].uv = glm::vec2(1.0, 1.0);
	vertexs[3].uv = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto tex = createRef<Texture2D>(RES_DIR"cxd706/Clock_60.png");
	m_materials = createRef<HaloMaterial>(tex);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
}

void HaloRectangle::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	m_mesh->draw(glm::mat4(1.0f), camera, lights);
}

ref<Material> HaloRectangle::getmaterial()
{
	return m_materials;
}

float HaloRectangle::getVelocity()
{
	return m_velocity;
}

void HaloRectangle::setVelocity(float Velocity)
{
	m_velocity = Velocity;
	as<HaloMaterial>(getmaterial())->velocity = m_velocity;
}




SportNode::SportNode()
{
	setWidth(756);
	setHeight(756);
	//Clock initial
	m_scene = createRef<Scene>();
	//设置摄像头
	ref<PerspectiveCamera> temp_camera = createRef<PerspectiveCamera>();
	glm::vec3 translate1(0.0f, 0.0f, -1.5f);
	temp_camera->setTranslate(translate1);
	temp_camera->setAspect(1.0f);
	m_scene->setCamera(temp_camera);
	//默认添加一个点光源，否则渲染很黑
	m_scene->addLight(createRef<PointLight>());

	m_Trianglegroupmodel = createRef<Trianglegroup>();
	m_Rectangle = createRef<RectangleClass>();
	m_HaloRectangle = createRef<HaloRectangle>();
	m_scene->addChild(m_Trianglegroupmodel);
	m_scene->addChild(m_Rectangle);
	m_scene->addChild(m_HaloRectangle);

	this->setScene(m_scene);
	//this->setBackground(createRef<SolidColorBrush>(Color(255, 255, 0)));
#ifndef __ANDROID__
	this->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/bg_b.png")));
#endif

	m_hourShadowParent = createRef<Node2D>(0.0f, -80.0f, 180.0f, 151.0f);
	m_hourShadowParent->setAlignmentCenter();
	m_hourShadowParent->setTransform(createRef<TranslateTransform2D>(0.0f, 0.0f));
	m_minuteShadowParent = createRef<Node2D>(0.0f, 80.0f, 180.0f, 151.0f);
	m_minuteShadowParent->setAlignmentCenter();
	m_minuteShadowParent->setTransform(createRef<TranslateTransform2D>(0.0f, 0.0f));

	m_hourParent = createRef<Node2D>(0.0f, -80.0f, 150.0f, 120.0f);
	m_hourParent->setAlignmentCenter();
	m_minuteParent = createRef<Node2D>(0.0f, 80.0f, 150.0f, 120.0f);
	m_minuteParent->setAlignmentCenter();

	addChild(m_hourShadowParent);
	addChild(m_minuteShadowParent);
	addChild(m_hourParent);
	addChild(m_minuteParent);


	//Time Action
	m_timer.start(10);
	m_timer.Tick += nbBindEventFunction(SportNode::onTick);


	m_haloanimation.setTarget(m_HaloRectangle);
	m_haloanimation.setTargetPropertyName("Velocity");
	m_haloanimation.setFrom(0.0f);
	m_haloanimation.setTo(1.5f);
	m_haloanimation.duration = TimeSpan::fromMilliseconds(1000);
	//m_haloanimation.autoReverse = true;
}

void SportNode::onKey(const KeyEventArgs &e)
{
	switch (e.key)
	{
	case KeyCode::_9:
	{
		m_haloanimation.begin();
		break;
	}
	default:													break;
	}
}

void SportNode::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		//Time Action
		static float anglePerMS = 0.006f;
		auto now = Time::now();
		auto mses = now.second() * 1000 + now.millisecond();

		curtime = mses;
		if (curtime < lasttime)
		{
			startanimation = true;
		}
		lasttime = curtime;

		auto timeAngle = anglePerMS * mses+90;

		float Radias = 0.48;
		m_Trianglegroupmodel->setpos(Point(-Radias * cos((timeAngle / 180.0)*3.1415926), Radias * sin((timeAngle / 180.0)*3.1415926)));
		
		for (auto child : m_Trianglegroupmodel->children())
		{
			if (is<TriangleNode>(child))
			{
				if (is<TriangleMaterial>(as<TriangleNode>(child)->getmaterial()))
				{
					as<TriangleMaterial>(as<TriangleNode>(child)->getmaterial())->angle = timeAngle;
				}
				Point pos = as<TriangleNode>(child)->getpos();
				Point curpos = m_Trianglegroupmodel->getpos();
				float length = sqrtf(abs(((pos.x - curpos.x) * (pos.x - curpos.x)) + ((pos.y - curpos.y) * (pos.y - curpos.y))));
				if ((length < 0.10) && ((as<TriangleNode>(child)->isactive() != TimelineStateE::Active)))
				{
					as<TriangleNode>(child)->startanimation();
				}
			}			
		}
		
		as<RectangleMaterial1>(m_Rectangle->getmaterial())->angle = timeAngle;

		static constexpr float circleR = 40.0f;
		moveShadowNumberCircle(m_hourShadowParent, 0.0f, -80.0f, circleR, timeAngle/* + 90*/);
		moveShadowNumberCircle(m_minuteShadowParent, 0.0f, 80.0f, circleR, timeAngle/* + 90*/);

		static auto lastMinute = now.minute();
		//if (lastMinute != now.minute())
		{
			setTime(m_hourShadowParent, 10, "_shadow", 50.0f, false, timeAngle);
			setTime(m_minuteShadowParent, 33, "_shadow", 75.0f, false, timeAngle);
			setTime(m_hourParent, 10, "", 50.0f, true, timeAngle-90);
			setTime(m_minuteParent, 33, "", 75.0f, true, timeAngle-90);
		}


		if (startanimation)
		{
			startanimation = false;
			m_haloanimation.begin();
		}
	}
}

void SportNode::moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle)
{
	Point pt;
	pt.x = x + r * cos(glm::radians(angle));
	pt.y = y + r * sin(glm::radians(angle));
	node->setPosition(pt);
}

void SportNode::moveEffectNumberCircle(ref<Node2D> node, float angle)
{
	auto brush = nb::as<EffectBrush>(node->background());
	if (!brush)
		return;

	auto material = nb::as<NumberMaterial>(brush->material);
	if (!material)
		return;

	material->angle = angle;
}

void SportNode::setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle)
{
	parent->clearChildren();
	std::vector<ref<Node2D>> nodes;
	auto temp = value;
	while (temp)
	{
		auto n = temp % 10;
		auto nodeImagePath = std::to_string(n) + imagePrefix + ".png";
		auto tex = createRef<Texture2D>(RES_DIR"cxd706/" + nodeImagePath);
		auto brush = createRef<ImageBrush>(tex);

		static auto tex1 = createRef<Texture2D>(RES_DIR"cxd706/img_text_colour.png");
		auto tex2 = tex;
		tex2->setSamplerUnit(1);
		auto numberMaterial = createRef<NumberMaterial>(tex1, tex2);
		numberMaterial->angle = angle;
		auto numberBrush = createRef<EffectBrush>(numberMaterial, nullptr);

		auto node = createRef<Node2D>(0.0f, 0.0f, tex->width(), tex->height());
		node->setVerticalAlignment(VerticalAlignmentE::Center);
		if (useEffect)
			node->setBackground(numberBrush);
		else
			node->setBackground(brush);
		nodes.push_back(node);
		temp /= 10;
	}
	auto k = 0;
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		auto node = nodes[i];
		node->setX(space * k);
		parent->addChild(nodes[i]);
		++k;
	}
}

RTTR_PLUGIN_REGISTRATION
{
	registration::class_<HaloRectangle>("HaloRectangle") ()
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	.property("Velocity", &HaloRectangle::getVelocity, &HaloRectangle::setVelocity)
	;
}
#include "Normal.h"
#include "MainView.h"

constexpr char Mix_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
varying vec2 v_uv;
varying vec2 global_uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	v_uv = uv;
	global_uv = position.xy;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char Mix_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
varying vec2 global_uv;
uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform float u_radius;

void main()
{	
	vec2 local_uv = v_uv;
 
	vec2 _uv = (global_uv + vec2(1.0,1.0))/2.0;

	_uv -= vec2(0.5, 0.5);
	float inside = step((_uv.x * _uv.x + _uv.y * _uv.y),0.25 * 0.9);
	_uv = _uv * (1.0-inside) + inside * vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
	_uv += vec2(0.5, 0.5);
	vec4 _color1 = texture2D(u_sampler1, _uv);

	float amplitude = _color1.a;
	float scaleX = 0.5 + (local_uv.x - 0.5) * (1.1-amplitude);
    float scaleY = 0.5 + (local_uv.y - 0.5) * (1.1-amplitude);
    vec4 _color0 = texture2D(u_sampler0, vec2(scaleX, scaleY)) * amplitude;
	
	gl_FragColor = _color0;
}
)";

MixMaterial::MixMaterial(ref<Texture2D> texture0, ref<Texture2D> texture1)
	: Material(ShaderLibrary::get("Mix", Mix_vs, Mix_fs))
	, texture0(texture0)
	, texture1(texture1)
	, angle(0.0f)
{
	texture0->setSamplerUnit(0);
	texture1->setSamplerUnit(1);
	shader->use();
	shader->setInt("u_sampler0", 0);
	shader->setInt("u_sampler1", 1);
	shader->disuse();
}

void MixMaterial::uploadUniform(ref<Camera> camera)
{
	shader->setFloat("u_radius", glm::radians(angle));
	if (texture0) texture0->activeAndBind();
	if (texture1) texture1->activeAndBind();
}

constexpr char halo_vs[] = R"(
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

constexpr char halo_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler;
uniform float u_radius;
uniform vec2 u_resolution;

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

class RectangleMaterial : public Material
{
public:
	RectangleMaterial(ref<Texture2D> tex)
		: Material(ShaderLibrary::get("shader_clockpoint", halo_vs, halo_fs))
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

constexpr char Second_vs[] = R"(
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

constexpr char Second_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler0;
uniform float Opacity;

void main()
{
	vec2 _uv = v_uv;
	
	gl_FragColor = texture2D(u_sampler0, _uv);
	gl_FragColor.a = gl_FragColor.a * Opacity;
}
)";

SecondMaterial::SecondMaterial(ref<Texture2D> texture0)
	: Material(ShaderLibrary::get("Second", Second_vs, Second_fs))
	, texture0(texture0)
	, Opacity(1.0f)
{
	texture0->setSamplerUnit(0);
	shader->use();
	shader->setInt("u_sampler0", 0);
	shader->disuse();
}

void SecondMaterial::uploadUniform(ref<Camera> camera)
{
	shader->setFloat("Opacity", Opacity);
	if (texture0) texture0->activeAndBind();
}

constexpr char shrinkrect_vs[] = R"(
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

constexpr char shrinkrect_fs[] = R"(
precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler;
uniform float velocity;

void main( void )
{
	vec2 _uv = v_uv;

	float u_radius = velocity * 0.45;
	_uv -= vec2(0.5, 0.5);

	float inside1 = step(0.25 * 0.25,pow(_uv.x,2.0)+pow(_uv.y,2.0));
	float inside2 = step(pow(_uv.x,2.0)+pow(_uv.y,2.0),u_radius * u_radius);
	float inside = step(1.5,inside1+inside2);

	_uv += vec2(0.5, 0.5);
	
	gl_FragColor = texture2D(u_sampler, _uv);
	gl_FragColor.a = inside;
}
)";

class ShrinkMaterial : public Material
{
public:
	ShrinkMaterial(ref<Texture2D> tex)
		: Material(ShaderLibrary::get("shader_shrinkrect", shrinkrect_vs, shrinkrect_fs))
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

constexpr char clockNormal_vs[] = R"(
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

constexpr char clockNormal_fs[] = R"(
precision mediump float;
uniform sampler2D texture1;
uniform sampler2D texture2;
varying vec2 v_uv;
uniform float u_radius;
uniform vec2 u_resolution;

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

constexpr float R = 278.0f;
constexpr int DotsCount = 36 * 4;
const float RadiusStep = glm::two_pi<float>() / DotsCount;
constexpr float DotsAngleRange = 360.0f;
class NumberMaterial : public Material
{
public:
	NumberMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2)
		: Material(ShaderLibrary::get("shader_clockNormal", clockNormal_vs, clockNormal_fs))
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

NormalNode::NormalNode()
{
	setWidth(756.0f);
	setHeight(756.0f);
#ifndef __ANDROID__
	setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/background.png")));
#endif
	m_scene = createRef<Scene>();
	ref<PerspectiveCamera> temp_camera = createRef<PerspectiveCamera>();
	glm::vec3 translate1(0.0f, 0.0f, -1.5f);
	temp_camera->setTranslate(translate1);
	temp_camera->setAspect(1.0f);
	m_scene->setCamera(temp_camera);
	
	m_dotPanel3D = createRef<dotPanel3D>();
	m_point = createRef<secondpoint>(glm::vec2((278.0f + 378.0f - 3.8f), (378.0f - 2.0f)), 5.0, 5.0);
	m_halo = createRef<halo>();
	m_shrinkrect = createRef<ShrinkRectangle>();
	m_scene->addChild(m_dotPanel3D);
	m_scene->addChild(m_point);
	//m_scene->addChild(m_halo);
	m_scene->addChild(m_shrinkrect);
	this->setScene(m_scene);


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

	m_timer.start(10);
	m_timer.Tick += nbBindEventFunction(NormalNode::onTick);

	m_pointanimation.setTarget(m_point);
	m_pointanimation.setTargetPropertyName("Opacity");
	m_pointanimation.setFrom(0.0f);
	m_pointanimation.setTo(1.0f);
	m_pointanimation.duration = TimeSpan::fromMilliseconds(150);
	m_pointanimation.autoReverse = true;

	m_shrinkanimation.setTarget(m_shrinkrect);
	m_shrinkanimation.setTargetPropertyName("Velocity");
	m_shrinkanimation.setFrom(1.0f);
	m_shrinkanimation.setTo(0.0f);
	m_shrinkanimation.duration = TimeSpan::fromMilliseconds(1000);
}

void NormalNode::onKey(const KeyEventArgs &e)
{
	switch (e.key)
	{
	case KeyCode::_9:
	{
		m_shrinkanimation.begin();
		break;
	}
	default:													break;
	}
}

void NormalNode::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		auto timeAngle = MainView::getAngleForTime();
		auto timeRadius = glm::radians(timeAngle);

		static float anglePerMS = 0.006f;
		auto now = Time::now();
		auto mses = now.second() * 1000 + now.millisecond();

		curtime = mses;
		if (curtime < lasttime)
		{
			startanimation = true;
		}
		lasttime = curtime;

		for (auto child : m_dotPanel3D->children())
		{			
			if (is<RectangleObj>(child))
			{
				if (is<MixMaterial>(as<RectangleObj>(child)->getmaterial()))
				{
					as<MixMaterial>(as<RectangleObj>(child)->getmaterial())->angle = timeAngle;
				}
			}
		}

		as<RectangleMaterial>(m_halo->getmaterial())->angle = timeAngle;
		setSecondPointer(-timeAngle + 90);

		//return;
		static constexpr float circleR = 40.0f;
		moveShadowNumberCircle(m_hourShadowParent, 0.0f, -80.0f, circleR, timeAngle + 90);
		moveShadowNumberCircle(m_minuteShadowParent, 0.0f, 80.0f, circleR, timeAngle + 90);

		//static auto lastMinute = now.minute();
		//if (lastMinute != now.minute())
		{
			setTime(m_hourShadowParent, 10, "_shadow", 50.0f, false, timeAngle);
			setTime(m_minuteShadowParent, 33, "_shadow", 75.0f, false, timeAngle);
			setTime(m_hourParent, 10, "", 50.0f, true, timeAngle);
			setTime(m_minuteParent, 33, "", 75.0f, true, timeAngle);
		}

		if (startanimation)
		{
			startanimation = false;
			m_shrinkanimation.begin();
		}
	}

}

void NormalNode::moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle)
{
	Point pt;
	pt.x = x + r * cos(glm::radians(angle));
	pt.y = y + r * sin(glm::radians(angle));
	node->setPosition(pt);
}

void NormalNode::moveEffectNumberCircle(ref<Node2D> node, float angle)
{
	auto brush = nb::as<EffectBrush>(node->background());
	if (!brush)
		return;

	auto material = nb::as<NumberMaterial>(brush->material);
	if (!material)
		return;

	material->angle = angle;
}

void NormalNode::setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle)
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

float lastRadius = 0.0f;
void NormalNode::setSecondPointer(float angle)
{
	angle = (float)(int(angle + 360) % 360);
	float radius = glm::radians(angle);
	for (int i = DotsCount; i >= 0; --i)
	{
		auto radiuses = RadiusStep * i;
		if (radius >= radiuses)
		{
			ref<Transform> temp_transform = createRef<Transform>();
			temp_transform->setRotate(glm::vec3(0.0f, 0.0f, radiuses));
			m_point->setTransform(temp_transform);
			if (lastRadius != radiuses)
			{
				lastRadius = radiuses;
				m_pointanimation.begin();
			}
			return;
		}
	}
}

RectangleObj::RectangleObj(glm::vec2 pos, float w, float h, glm::mat4 matrix)
{
	glm::vec4 position = { pos.x, pos.y, 0.0f, 1.0f };
	glm::vec4 p0 = { -w/2, -h/2, 0.0f, 1.0f };
	glm::vec4 p1 = { w/2, -w/2, 0.0f, 1.0f };
	glm::vec4 p2 = { w/2, h/2, 0.0f, 1.0f };
	glm::vec4 p3 = { -w/2, h/2, 0.0f, 1.0f };


	glm::mat4 temp = glm::mat4(1.0f);
	temp[0][0] = cos(45);
	temp[0][1] = -sin(45);
	temp[1][0] = sin(45);
	temp[1][1] = cos(45);
	p0 = temp * p0;
	p1 = temp * p1;
	p2 = temp * p2;
	p3 = temp * p3;


	std::vector<Vertex> vertexs(4);
	vertexs[0].position = (p0 + position - 378.0f) / 378.0f;
	vertexs[1].position = (p1 + position - 378.0f) / 378.0f;
	vertexs[2].position = (p2 + position - 378.0f) / 378.0f;
	vertexs[3].position = (p3 + position - 378.0f) / 378.0f;

	for (int i=0;i<4;i++)
	{
		auto temp = glm::vec4(vertexs[i].position,1.0f);
		temp = matrix * temp;
		vertexs[i].position = glm::vec3(temp);
	}

	/*glm::mat4 temp = glm::mat4(1.0f);
	temp[0][0] = cos(r);
	temp[0][1] = -sin(r);
	temp[1][0] = sin(r);
	temp[1][1] = cos(r);*/
	/*for (int i=0;i<4;i++)
	{
		float x_or = vertexs[i].position.x;
		float y_or = vertexs[i].position.y;
		vertexs[i].position.x = x_or *cos(r) - y_or*sin(r);
		vertexs[i].position.y = x_or *sin(r) + y_or*cos(r);
	}*/
	/*vertexs[0].position.z = 0.0f;
	vertexs[1].position.z =	0.0f;
	vertexs[2].position.z =	0.0f;
	vertexs[3].position.z =	0.0f;*/

	vertexs[0].uv = glm::vec2(0.0, 0.0);
	vertexs[1].uv = glm::vec2(1.0, 0.0);
	vertexs[2].uv = glm::vec2(1.0, 1.0);
	vertexs[3].uv = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto mixtex0 = createRef<Texture2D>(RES_DIR"cxd706/normal/spot4x4_2.png");
	static auto mixtex1 = createRef<Texture2D>(RES_DIR"cxd706/normal/NORMAL_MASK_TEST4.png");
	m_materials = createRef<MixMaterial>(mixtex0, mixtex1);

	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
}

ref<Material> RectangleObj::getmaterial()
{
	return m_materials;
}

void RectangleObj::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	m_mesh->draw(Transform::identityMatrix4(), camera, lights);
}

dotPanel3D::dotPanel3D()
{
	builddotPanel3D();
}

void dotPanel3D::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	for (auto child : children())
	{
		child->onRender(camera, lights);
	}
}

/*
void dotPanel3D::builddotPanel3D()
{
	float width_rc = 5.0f;
	float height_rc = 5.0f;

	float R = 278.0f;
	int DotsCount = 36 * 4;
	float RadiusStep = glm::two_pi<float>() / DotsCount;
	float DotsAngleRange = 360.0f;

	glm::vec2 center(756 / 2.0f, 756 / 2.0f);
	for (int k = 0; k <= 15; ++k)
	{
		for (int i = 0; i != DotsCount; ++i)
		{
			auto radiuses = RadiusStep * i;
			glm::vec2 pt = glm::vec2(R * cos(radiuses), R * sin(radiuses)) + center - glm::vec2(width_rc / 2, height_rc / 2);

			auto node = createRef<RectangleObj>(pt, width_rc, height_rc, radiuses);
			addChild(node);
		}
		R -= 8.0f;
	}
}*/

void dotPanel3D::builddotPanel3D()
{
	float width_rc = 3.5f;
	float height_rc = 3.5f;

	float R = 278.0f;
	int DotsCount = 36 * 4;
	float RadiusStep = glm::two_pi<float>() / DotsCount;
	float DotsAngleRange = 360.0f;

	glm::vec2 center(756 / 2.0f, 756 / 2.0f);
	for (int k = 0; k <= 15; ++k)
	{
		for (int i = 0; i != DotsCount; ++i)
		{
			auto radiuses = RadiusStep * i;
			glm::vec2 pt = glm::vec2(R , 0) + center - glm::vec2(width_rc / 2, height_rc / 2);

			glm::vec3 rotate = glm::vec3(0.0f, 0.0f, radiuses);
			glm::mat4 matrix =  glm::yawPitchRoll(rotate.y, rotate.x, rotate.z);

			auto node = createRef<RectangleObj>(pt, width_rc, height_rc, matrix);
			addChild(node);
		}
		R -= 8.0f;
	}
}

halo::halo()
{
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	vertexs[1].position = glm::vec3(1.0f, -1.0f, -1.0f);
	vertexs[2].position = glm::vec3(1.0f, 1.0f, -1.0f);
	vertexs[3].position = glm::vec3(-1.0f, 1.0f, -1.0f);

	vertexs[0].uv = glm::vec2(0.0, 0.0);
	vertexs[1].uv = glm::vec2(1.0, 0.0);
	vertexs[2].uv = glm::vec2(1.0, 1.0);
	vertexs[3].uv = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto tex = createRef<Texture2D>(RES_DIR"cxd706/normal/t1_normal_zz_g_1.png");
	m_materials = createRef<RectangleMaterial>(tex);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
}

void halo::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	if (getTransform())
	{
		m_mesh->draw(getTransform()->value(), camera, lights);
	}
	else
	{
		m_mesh->draw(glm::mat4(1.0f), camera, lights);
	}
}

ref<Material> halo::getmaterial()
{
	return m_materials;
}

secondpoint::secondpoint()
{}

secondpoint::secondpoint(glm::vec2 pos, float w, float h)
{
	/*glm::vec4 position = { pos.x, pos.y, 0.0f, 1.0f };
	glm::vec4 p0 = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 p1 = { w, 0.0f, 0.0f, 1.0f };
	glm::vec4 p2 = { w, h, 0.0f, 1.0f };
	glm::vec4 p3 = { 0.0f, h, 0.0f, 1.0f };*/

	glm::vec4 position = { pos.x, pos.y, 0.0f, 1.0f };
	glm::vec4 p0 = { -w / 2, -h / 2, 0.0f, 1.0f };
	glm::vec4 p1 = { w / 2, -w / 2, 0.0f, 1.0f };
	glm::vec4 p2 = { w / 2, h / 2, 0.0f, 1.0f };
	glm::vec4 p3 = { -w / 2, h / 2, 0.0f, 1.0f };

	glm::mat4 temp = glm::mat4(1.0f);
	temp[0][0] = cos(45);
	temp[0][1] = -sin(45);
	temp[1][0] = sin(45);
	temp[1][1] = cos(45);
	p0 = temp * p0;
	p1 = temp * p1;
	p2 = temp * p2;
	p3 = temp * p3;

	std::vector<Vertex> vertexs(4);
	vertexs[0].position = (p0 + position - 378.0f) / 378.0f;
	vertexs[1].position = (p1 + position - 378.0f) / 378.0f;
	vertexs[2].position = (p2 + position - 378.0f) / 378.0f;
	vertexs[3].position = (p3 + position - 378.0f) / 378.0f;

	vertexs[0].position.z = -0.98f;
	vertexs[1].position.z =	-0.98f;
	vertexs[2].position.z =	-0.98f;
	vertexs[3].position.z =	-0.98f;

	vertexs[0].uv = glm::vec2(0.0, 0.0);
	vertexs[1].uv = glm::vec2(1.0, 0.0);
	vertexs[2].uv = glm::vec2(1.0, 1.0);
	vertexs[3].uv = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto secondtex0 = createRef<Texture2D>(RES_DIR"cxd706/normal/123.png");
	
	m_materials = createRef<SecondMaterial>(secondtex0);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
}

void secondpoint::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	if (getTransform())
	{
		m_mesh->draw(getTransform()->value(), camera, lights);
	}
	else
	{
		m_mesh->draw(glm::mat4(1.0f), camera, lights);
	}
}

float secondpoint::getOpacity()
{
	return m_Opacity;
}

void secondpoint::setOpacity(float Opacity)
{
	m_Opacity = Opacity;
	as<SecondMaterial>(getmaterial())->Opacity = m_Opacity;
}

ref<Material> secondpoint::getmaterial()
{
	return m_materials;
}

ShrinkRectangle::ShrinkRectangle()
{
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = glm::vec3(-1.0, -1.0, -0.998);
	vertexs[1].position = glm::vec3(1.0, -1.0, -0.998);
	vertexs[2].position = glm::vec3(1.0, 1.0, -0.998);
	vertexs[3].position = glm::vec3(-1.0, 1.0, -0.998);
	
	vertexs[0].uv = glm::vec2(0.0, 1.0);
	vertexs[1].uv = glm::vec2(1.0, 1.0);
	vertexs[2].uv = glm::vec2(1.0, 0.0);
	vertexs[3].uv = glm::vec2(0.0, 0.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };

	static auto tex = createRef<Texture2D>(RES_DIR"cxd706/Normalpointtest2.png");
	m_materials = createRef<ShrinkMaterial>(tex);
	m_mesh = createRef<Mesh>(vertexs, indices, m_materials);
}

void ShrinkRectangle::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	m_mesh->draw(glm::mat4(1.0f), camera, lights);
}

ref<Material> ShrinkRectangle::getmaterial()
{
	return m_materials;
}

float ShrinkRectangle::getVelocity()
{
	return m_velocity;
}

void ShrinkRectangle::setVelocity(float Velocity)
{
	m_velocity = Velocity;
	as<ShrinkMaterial>(getmaterial())->velocity = m_velocity;
}

RTTR_PLUGIN_REGISTRATION
{
	registration::class_<secondpoint>("secondpoint") ()
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	.property("Opacity", &secondpoint::getOpacity, &secondpoint::setOpacity);

	registration::class_<ShrinkRectangle>("ShrinkRectangle") ()
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	.property("Velocity", &ShrinkRectangle::getVelocity, &ShrinkRectangle::setVelocity);
}
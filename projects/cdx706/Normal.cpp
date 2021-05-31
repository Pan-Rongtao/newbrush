#include "Normal.h"

constexpr char clockNormal_vs[] = R"(
attribute vec3 nbPos;
attribute vec2 nbTexCoord;
uniform mat4 nbM;
uniform mat4 nbVP;
varying vec2 vTexCoord;
void main()
{
	vTexCoord = nbTexCoord;
	gl_Position = nbVP * nbM * vec4(nbPos, 1.0);
}
)";

constexpr char clockNormal_fs[] = R"(
precision mediump float;
uniform sampler2D texture1;
uniform sampler2D texture2;
varying vec2 vTexCoord;
uniform float radius;

void main( void )
{
	vec2 pos, size;
	vec2 npos = gl_FragCoord.xy / vec2(756.0, 756.0);   // 0.0 .. 1.0
	vec2 uv = (1.0 - npos);

	uv -= vec2(0.5, 0.5);
	uv = vec2(uv.x * cos(radius) - uv.y * sin(radius), uv.x * sin(radius) + uv.y * cos(radius));
	uv += vec2(0.5, 0.5);
					
	vec4 color1 = texture2D(texture1, uv);
	vec4 color2 = texture2D(texture2, vTexCoord);
	vec4 color;
	if(color2.r >= 0.9)
		color = mix(color1, color2, 0.2);
	gl_FragColor = color;
}
)";

class NumberMaterial : public Material
{
public:
	NumberMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2)
		: Material(ShaderLibrary::get("normalShader"))
		, texture1(tex1)
		, texture2(tex2)
		, angle(0.0f)
	{
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		shader->setFloat("radius", glm::radians(angle));
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);
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
	setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/background.png")));

	ShaderLibrary::add("normalShader", clockNormal_vs, clockNormal_fs);

	m_dots0 = createRef<Node2D>(0.0f, 0.0f, 756.0f, 756.0f);
	m_dots0->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/a_00.png")));
	m_dots0->setTransform(createRef<RotateTransform2D>(0.0f, 378.0f, 378.0f));

	m_dots1 = createRef<Node2D>(0.0f, 0.0f, 756.0f, 756.0f);
	m_dots1->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/dot.png")));
	m_dots1->setTransform(createRef<RotateTransform2D>(0.0f, 378.0f, 378.0f));

	m_secondPointer = createRef<Node2D>(0.0f, 0.0f, 756.0f, 756.0f);
	m_secondPointer->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/b_00.png")));
	m_secondPointer->setTransform(createRef<RotateTransform2D>(0.0f, 378.0f, 378.0f));

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

	//addChild(m_dots0);
	addChild(m_dots1);
	addChild(m_secondPointer);
	addChild(m_hourShadowParent);
	addChild(m_minuteShadowParent);
	addChild(m_hourParent);
	addChild(m_minuteParent);

	m_timer.start(10);
	m_timer.Tick += nbBindEventFunction(NormalNode::onTick);

	m_secondPointerAnimation.setTarget(m_secondPointer);
	m_secondPointerAnimation.setTargetPropertyName("Opacity");
	m_secondPointerAnimation.setFrom(0.3f);
	m_secondPointerAnimation.setTo(1.0f);
	m_secondPointerAnimation.duration = TimeSpan::fromMilliseconds(400);
	m_secondPointerAnimation.repeatBehavior = RepeatBehavior::forever();
	m_secondPointerAnimation.begin();
}

void NormalNode::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		static float anglePerMS = 0.006f;
		auto now = Time::now();
		auto mses = now.second() * 1000 + now.millisecond();
		auto timeAngle = anglePerMS * mses;

		nb::as<RotateTransform2D>(m_dots0->getTransform())->setAngle(timeAngle + 180);
		nb::as<RotateTransform2D>(m_dots1->getTransform())->setAngle(timeAngle + 180);
		nb::as<RotateTransform2D>(m_secondPointer->getTransform())->setAngle(timeAngle + 180);

		static constexpr float circleR = 40.0f;
		moveShadowNumberCircle(m_hourShadowParent, 0.0f, -80.0f, circleR, timeAngle + 90);
		moveShadowNumberCircle(m_minuteShadowParent, 0.0f, 80.0f, circleR, timeAngle + 90);

		static auto lastMinute = now.minute();
		//if (lastMinute != now.minute())
		{
			setTime(m_hourShadowParent, 10, "_shadow", 50.0f, false, timeAngle);
			setTime(m_minuteShadowParent, 33, "_shadow", 75.0f, false, timeAngle);
			setTime(m_hourParent, 10, "", 50.0f, true, timeAngle);
			setTime(m_minuteParent, 33, "", 75.0f, true, timeAngle);
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

#include "ECO.h"

float circleR = 300.0f;

constexpr char clockECO_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec2 v_uv;
void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char clockECO_fs[] = R"(
precision mediump float;
uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
varying vec2 v_uv;
uniform float u_radius;
uniform vec2 u_resolution;

void main( void )
{
	vec2 _npos = gl_FragCoord.xy / u_resolution;   // 0.0 .. 1.0
	vec2 _uv = (1.0 - _npos);

	_uv -= vec2(0.5, 0.5);
	_uv = vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
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
		tex2->setSamplerUnit(1);
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		float x, y, w, h;
		GLUtils::getViewport(x, y, w, h);
		shader->setFloat2("u_resolution", glm::vec2(w, h));
		shader->setFloat("u_radius", glm::radians(angle));
		shader->setInt("u_sampler0", 0);
		shader->setInt("u_sampler1", 1);
		if (texture1) texture1->activeAndBind();
		if (texture2) texture2->activeAndBind();
	}

	ref<Texture2D> texture1;
	ref<Texture2D> texture2;
	float angle;
};

ECONode::ECONode()
{
	setWidth(756.0f);
	setHeight(756.0f);

#ifndef __ANDROID__
	setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cdx706/eco/eco_background.png")));
#endif	

	m_dotPanel = createRef<Node2D>(0.0f, 0.0f, 584.0f, 538.0f);
	m_dotPanel->setAlignmentCenter();
	makeDots(0.0f, 360.0f, circleR);
	setDotsAngle(0.0f, 45.0f, circleR);

	m_pionter = createRef<Node2D>(0.0f, 0.0f, 584.0f, 538.0f);
	m_pionter->setAlignmentCenter();
	m_pionter->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cdx706/eco/img_clock.png")));
	m_pionter->setTransform(createRef<RotateTransform2D>(0.0f, 278.0f, 272.0f));

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

	addChild(m_dotPanel);
	addChild(m_pionter);
	addChild(m_hourShadowParent);
	addChild(m_minuteShadowParent);
	addChild(m_hourParent);
	addChild(m_minuteParent);

	m_timer.start(10);
	m_timer.Tick += nbBindEventFunction(ECONode::onTick);


	auto timeAngle = MainView::getAngleForTime();
	nb::as<RotateTransform2D>(m_pionter->getTransform())->setAngle(timeAngle - 90);
	setDotsAngle(timeAngle - 90, 45.0f, circleR);
}

void ECONode::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		/*static float anglePerMS = 0.006f;
		auto now = Time::now();
		auto mses = now.second() * 1000 + now.millisecond();
		auto timeAngle = anglePerMS * mses;*/
		auto timeAngle = MainView::getAngleForTime();

		nb::as<RotateTransform2D>(m_pionter->getTransform())->setAngle(timeAngle - 90);
		setDotsAngle(timeAngle - 90, 45.0f, circleR);

		static constexpr float circleR = 20.0f;
		moveShadowNumberCircle(m_hourShadowParent, 0.0f, -80.0f, circleR, timeAngle + 90);
		moveShadowNumberCircle(m_minuteShadowParent, 0.0f, 80.0f, circleR, timeAngle + 90);

		//static auto lastMinute = Time::now().minute();
		//if (lastMinute != now.minute())
		{
			setTime(m_hourShadowParent, 10, "_shadow", 50.0f, false, timeAngle);
			setTime(m_minuteShadowParent, 33, "_shadow", 75.0f, false, timeAngle);
			setTime(m_hourParent, 10, "", 50.0f, true, timeAngle);
			setTime(m_minuteParent, 33, "", 75.0f, true, timeAngle);
		}

	}
}

void ECONode::moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle)
{
	Point pt;
	pt.x = x + r * cos(glm::radians(angle));
	pt.y = y + r * sin(glm::radians(angle));
	node->setPosition(pt);
}

void ECONode::moveEffectNumberCircle(ref<Node2D> node, float angle)
{
	auto brush = nb::as<EffectBrush>(node->background());
	if (!brush)
		return;

	auto material = nb::as<NumberMaterial>(brush->material);
	if (!material)
		return;

	material->angle = angle;
}

static float circleCenterX = 278.0f;
static float circleCenterY = 272.0f;
static float horSpace = 16.0f;
static float verSpace = 8.0f;
void ECONode::makeDots(float startAngle, float angleRange, float r)
{
	auto addNode = [r](ref<Node2D> parent, float x, float y, ref<Texture2D> tex)
	{
		auto node = createRef<Node2D>(0.0f, 0.0f, tex->width(), tex->height());
		node->setBackground(createRef<ImageBrush>(tex));
		node->setPosition(Point(x, y));
		node->setTransform(createRef<ScaleTransform2D>(1.0f, 1.0f, 3.0f, 3.0f));
		auto dis = sqrt((x - circleCenterX) * (x - circleCenterX) + (y - circleCenterY) * (y - circleCenterY));
		//auto dif = dis - r;
		//if (dif >= -150)
		node->setOpacity(1.05f - dis / r);
		//	node->setOpacity(1.0f);
		parent->addChild(node);
	};

	m_dotPanel->clearChildren();

	auto angleEnd = int(startAngle + 360) % 360;

	static auto tex = createRef<Texture2D>(RES_DIR"cdx706/eco/spot.png");
	float nodeDistanceX = horSpace + tex->width();
	float nodeDistanceY = verSpace + tex->height();

	auto k = 0;
	for (auto y = 0.0f; y <= m_dotPanel->height(); y += nodeDistanceY)
	{
		auto offsetX = (k % 2) * nodeDistanceX / 2;
		k++;
		for (auto x = 0.0f; x <= m_dotPanel->width(); x += nodeDistanceX)
		{
			auto xp = x + offsetX;
			if (!MainView::isInCircle(xp, y, circleCenterX, circleCenterY, r))
				continue;

			auto ptAngle = MainView::getAngle(xp, y, circleCenterX, circleCenterY);
			auto angleMin = angleEnd - angleRange;
			auto angleMax = angleEnd;
			//angleMin小于0，表示angleMin和angleMax分别在第一象限和第四象限
			if ((angleMin < 0.0f && ((ptAngle >= angleMin + 360 && ptAngle <= 360) || (ptAngle >= 0 && ptAngle <= angleMax)))
				|| (angleMin >= 0.0f && ptAngle >= angleMin && ptAngle <= angleMax))
			{
				addNode(m_dotPanel, xp, y, tex);
			}
		}
	}
}

void ECONode::setDotsAngle(float angle, float angleRange, float r)
{
	auto angleEnd = int(angle + 360) % 360;
	for (auto i = 0u; i < m_dotPanel->childCount(); ++i)
	{
		auto child = m_dotPanel->getChildAt(i);
		auto x = child->x();
		auto y = child->y();
		if (!MainView::isInCircle(x, y, circleCenterX, circleCenterY, r))
		{
			child->setVisibility(VisibilityE::Hidden);
		}
		else
		{
			auto ptAngle = MainView::getAngle(x, y, circleCenterX, circleCenterY);
			auto angleMin = angleEnd - angleRange;
			auto angleMax = angleEnd;
			child->setVisibility(VisibilityE::Hidden);
			//angleMin小于0，表示angleMin和angleMax分别在第一象限和第四象限
			if ((angleMin < 0.0f && ((ptAngle >= angleMin + 360 && ptAngle <= 360) || (ptAngle >= 0 && ptAngle <= angleMax)))
				|| (angleMin >= 0.0f && ptAngle >= angleMin && ptAngle <= angleMax))
			{
				child->setVisibility(VisibilityE::Visible);
				//for (auto &ani : m_scaleAnimations)
				//{
				//	if (ani->currentState() == StateE::Stopped)
				//	{
				//		auto target = nb::as<ScaleTransform2D>(child->getTransform());
				//		ani->setTarget(target);
				//		ani->begin();
				//		break;
				//	}
				//}
			}
		}
	}


}

void ECONode::setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle)
{
	parent->clearChildren();
	std::vector<ref<Node2D>> nodes;
	auto temp = value;
	while (temp)
	{
		auto n = temp % 10;
		auto nodeImagePath = std::to_string(n) + imagePrefix + ".png";
		auto tex = createRef<Texture2D>(RES_DIR"cdx706/" + nodeImagePath);
		auto brush = createRef<ImageBrush>(tex);

		static auto tex1 = createRef<Texture2D>(RES_DIR"cdx706/img_text_colour.png");
		auto tex2 = tex;
		auto numberMaterial = createRef<NumberMaterial>(tex1, tex2);
		numberMaterial->angle = angle;
		auto numberBrush = createRef<EffectBrush>(numberMaterial, nullptr);

		auto node = createRef<Node2D>(0.0f, 0.0f, tex->width(), tex->height());
		node->setVerticalAlignment(VerticalAlignment::Center);
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

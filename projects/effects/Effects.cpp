#include "Effects.h"

constexpr char GaussianBlur_vs[] = R"(
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

constexpr char GaussianBlur_fs[] = R"(
uniform sampler2D u_sampler0;
varying vec2 v_uv;
uniform float u_intensity;

float Blur_Gauss (float bhqp, float x) 
{
	return exp (-(x * x) / (2.0 * bhqp * bhqp));
}

vec4 Blur(vec2 uv, sampler2D source, float Intensity)
{
	const int iterations = 16;   // 常量才可以进行for循环
	int halfIterations = iterations / 2;
	float sigmaX = 0.1 + Intensity * 0.5;
	float sigmaY = sigmaX;
	float total = 0.0;
	vec4 ret = vec4 (0., 0., 0., 0.);
	float step = 0.00390625;
	// 增多到8*8个点
	for (int iy = 0; iy < iterations; ++iy) 
	{
		float fy = Blur_Gauss (sigmaY, float (iy - halfIterations));
		float offsety = float (iy - halfIterations) * step;
		for (int ix = 0; ix < iterations; ++ix)
		{
			float fx = Blur_Gauss (sigmaX, float (ix - halfIterations));
			float offsetx = float (ix - halfIterations) * step;
			total += fx * fy;
			vec4 a = texture2D (source, uv + vec2 (offsetx, offsety));
			a.rgb *= a.a;
			ret += a * fx * fy;
		}
	}
	return ret / total;
}

void main( void )
{
	vec4 _color = Blur(v_uv, u_sampler0, u_intensity);
	gl_FragColor = _color;
}
)";

GaussianBlurMateial::GaussianBlurMateial(ref<Texture2D> texture, float _intensity)
	: Material(ShaderLibrary::get("shader_GaussianBlur", GaussianBlur_vs, GaussianBlur_fs))
	, texture0(texture)
	, intensity(_intensity)
{
}

void GaussianBlurMateial::uploadUniform(ref<Camera> camera)
{
	shader->setFloat("u_intensity", intensity);
	if (texture0)	texture0->activeAndBind();
}

/////////////////////////

constexpr char Vortex_vs[] = R"(
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

constexpr char Vortex_fs[] = R"(
uniform sampler2D texture0;
varying vec2 v_uv;	//旋涡半径,范围(0 ~ 0.5)
uniform float u_r;	//旋涡旋转角度
uniform float u_angle;

void main( void )
{
    //旋涡半径
    float _radius = u_r;
    //当前纹理坐标
    vec2 _uv = v_uv;
    //当前纹理到中心点的向量
    vec2 _dxy = v_uv - vec2(0.5, 0.5);
    //当前纹理到中心点距离
    float _r = length(_dxy);
    //旋转角度变化
    float _beta = atan(_dxy.y, _dxy.x) + radians(u_angle) * 2.0 * ( 1.0 - (_r / _radius) * (_r /_radius));
    //旋涡范围内的坐标变化
    if(_r <= _radius)
    {
        _uv = 0.5 + _r * vec2(cos(_beta), sin(_beta));
    }
    vec3 _rgb = texture2D(texture0, _uv).rgb;
    gl_FragColor = vec4(_rgb, 1.0 );
}
)";

VortexMaterial::VortexMaterial(ref<Texture2D> texture, float _r, float _angle)
	: Material(ShaderLibrary::get("shader_Vortex", Vortex_vs, Vortex_fs))
	, texture0(texture)
	, r(_r)
	, angle(_angle)
{
}

void VortexMaterial::uploadUniform(ref<Camera> camera)
{
	shader->setFloat("u_r", r);
	shader->setFloat("u_angle", angle);
	if (texture0) texture0->activeAndBind();
}

///////////////

constexpr char Flame_vs[] = R"(
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

constexpr char Flame_fs[] = R"(
uniform sampler2D texture0;
varying vec2 v_uv;
uniform float u_time;
const vec2 u_center = vec2(0.5, 0.5);		// 水波纹速度
const float u_speed = 2.5;				// 水波纹强度
const float u_intensity = 36.0;
const vec2 u_resolution = vec2(1280.0, 1000.0);

void main()
{
    vec2 _uv = v_uv;//gl_FragCoord.xy / u_resolution.xy;
    // 计算u_center到各个_uv的值
    float dst = distance(_uv, u_center);
    // fragColor = vec4(vec3(dst), 1.0);
    // 计算水波纹
    // sin将对这个范围限制到[-1, 1]
    // dst范围是[0, sqrt(2)]
    // u_intensity可以理解为波纹数
    // u_time的引入让一个点可以从[-1, 1]的变化
    // u_speed是速度
    // 可以理解为dst*u_intensity是初始波纹, u_time的引入让波纹动了起来
    float _wave = sin(sqrt(dst) * u_intensity - u_time * u_speed);
    // fragColor = vec4(vec3(_wave), 1.0);

    // 接下来使用da和偏移的db来mix, 也就是水波纹白色区域取db, 黑色区域取da
    vec3 _da = texture2D(texture0, _uv).rgb;
    vec3 _db = texture2D(texture0, _uv - vec2(0.01)).rgb;
    vec3 _res = mix(_da, _db, _wave * _wave);  // _wave*_wave范围为[0, 1]
    gl_FragColor = vec4(_res, 1.0);

}

)";

FlameMaterial::FlameMaterial(ref<Texture2D> texture)
	: Material(ShaderLibrary::get("shader_Flame", Flame_vs, Flame_fs))
	, texture0(texture)
	, time(0.0f)
{
}

void FlameMaterial::uploadUniform(ref<Camera> camera)
{
	++time;
	shader->setFloat("u_time", time);
	if (texture0) texture0->activeAndBind();
}

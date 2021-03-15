#include "Effects.h"

constexpr char GaussianBlur_vs[] = R"(
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

constexpr char GaussianBlur_fs[] = R"(
uniform sampler2D texture1;
varying vec2 vTexCoord;
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
	vec4 color = Blur(vTexCoord, texture1, u_intensity);
	gl_FragColor = color;
}
)";

GaussianBlurMateial::GaussianBlurMateial(ref<Texture2D> texture, float _intensity)
	: Material(ShaderLibrary::add("GaussianBlur", GaussianBlur_vs, GaussianBlur_fs))
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

constexpr char Vortex_fs[] = R"(
uniform sampler2D texture0;
varying vec2 vTexCoord;
//旋涡半径,范围(0 ~ 0.5)
uniform float u_r;
//旋涡旋转角度
uniform float u_angle;

void main( void )
{
    //旋涡半径
    float Radius = u_r;
    //当前纹理坐标
    vec2 xy = vTexCoord;
    //当前纹理到中心点的向量
    vec2 dxy = vTexCoord - vec2(0.5, 0.5);
    //当前纹理到中心点距离
    float r = length(dxy);
    //旋转角度变化
    float beta = atan(dxy.y, dxy.x) + radians(u_angle) * 2.0 * ( 1.0 -(r/Radius)*(r/Radius));
    //旋涡范围内的坐标变化
    if(r<=Radius)
    {
        xy = 0.5 + r * vec2(cos(beta), sin(beta));
    }
    vec3 irgb = texture2D(texture0, xy).rgb;
    gl_FragColor = vec4( irgb, 1.0 );

}
)";

VortexMaterial::VortexMaterial(ref<Texture2D> texture, float _r, float _angle)
	: Material(ShaderLibrary::add("Vortex", Vortex_vs, Vortex_fs))
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

constexpr char Flame_fs[] = R"(
uniform sampler2D texture0;
varying vec2 vTexCoord;
uniform float iTime;
const vec2 center = vec2(0.5, 0.5);
// 水波纹速度
const float speed = 2.5;
// 水波纹强度
const float intensity = 36.0;

void main()
{
vec2 iResolution = vec2(1280.0, 1000.0);
    vec2 uv = vTexCoord;//gl_FragCoord.xy / iResolution.xy;
    // 计算center到各个uv的值
    float dst = distance(uv, center);
    // fragColor = vec4(vec3(dst), 1.0);
    // 计算水波纹
    // sin将对这个范围限制到[-1, 1]
    // dst范围是[0, sqrt(2)]
    // intensity可以理解为波纹数
    // iTime的引入让一个点可以从[-1, 1]的变化
    // speed是速度
    // 可以理解为dst*intensity是初始波纹, iTime的引入让波纹动了起来
    float wave = sin(sqrt(dst)*intensity-iTime*speed);
    // fragColor = vec4(vec3(wave), 1.0);

    // 接下来使用da和偏移的db来mix, 也就是水波纹白色区域取db, 黑色区域取da
    vec3 da = texture2D(texture0, uv).rgb;
    vec3 db = texture2D(texture0, uv-vec2(0.01)).rgb;
    vec3 res = mix(da, db, wave*wave);  // wave*wave范围为[0, 1]
    gl_FragColor = vec4(res, 1.0);

}

)";

FlameMaterial::FlameMaterial(ref<Texture2D> texture)
	: Material(ShaderLibrary::add("Flame", Flame_vs, Flame_fs))
	, texture0(texture)
	, time(0.0f)
{
}

void FlameMaterial::uploadUniform(ref<Camera> camera)
{
	++time;
	shader->setFloat("iTime", time);
	if (texture0) texture0->activeAndBind();
}

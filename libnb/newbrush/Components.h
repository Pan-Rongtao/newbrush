#pragma once
#include "newbrush/Bitmap.h"
#include "newbrush/Object.h"
#include "newbrush/Types.h"
#include "newbrush/Event.h"
#if NB_OS == NB_OS_ANDROID
	#include <GLES3/gl3.h>
#else
	#include "glad/glad.h"
#endif

namespace nb
{
	
/**************************************
*	OpenGL
*
****************************************/
class NB_API GLUtils
{
public:
	static void viewport(float x, float y, float width, float height);
	static void getViewport(float &x, float &y, float &width, float &height);
};

/**************************************
*	摄像头
*
*	摄像头基类 Camera
*	透视摄像头 PerspectiveCamera
*	正交摄像头 OrthographicCamera
****************************************/
class NB_API Camera : public Object
{
	RTTR_ENABLE(Object)
public:
	virtual const glm::mat4 &getViewProjectionMatrix() const = 0;

protected:
	Camera() = default;
};

class NB_API PerspectiveCamera : public Camera
{
	RTTR_ENABLE(Camera)
public:
	//构建一个摄像机，它的变换为transform
	//水平夹角为fov，宽高比为aspect，近截面为nearPlane，远截面为farPlane
	PerspectiveCamera();

	void setTranslate(const glm::vec3 &translate);
	void setRotate(const glm::vec3 &rotate);
	void setScale(const glm::vec3 &scale);
	const glm::vec3 &getTranslate() const;
	const glm::vec3 &getRotate() const;
	const glm::vec3 &getScale() const;

	void setFov(float fov);
	void setAspect(float aspect);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);
	float getFov() const;
	float getAspect() const;
	float getNearPlane() const;
	float getFarPlane() const;

	//获取观察矩阵/透视矩阵
	const glm::mat4 &getViewProjectionMatrix() const override;

private:
	void updateMatrix();

	glm::vec3 m_translate;		//平移
	glm::vec3 m_rotate;			//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	glm::vec3 m_scale;			//缩放
	float m_fov;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;
	glm::mat4 m_viewProjectionMatrix;
};

class NB_API OrthographicCamera : public Camera
{
	RTTR_ENABLE(Camera)
public:
	OrthographicCamera();

	void resize(float width, float height);
	const glm::mat4 &getViewProjectionMatrix() const override;

private:
	glm::mat4 m_matrix;
};

NB_API ref<OrthographicCamera> sharedCamera2D();

/**************************************
*	着色器
*
*	着色器 Shader
*	着色器库 ShaderLibrary
*	立方体纹理	TextureCubemap
****************************************/
class NB_API Shader
{
public:
	Shader(const Shader &other) = delete;
	void operator =(const Shader &other) = delete;
	~Shader();

	//编译链接
	//异常：std::runtime_error
	void compileLink(const std::string &vsSource, const std::string &fsSource);

	int getAttributeLocation(const char *name) const;
	int getUniformLocation(const char *name) const;
	void bindAttributeLocation(uint32_t location, const char *name);

	uint32_t id();

	//激活/反激活
	void use();
	void disuse();

	//更新位置为location的attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新位置为name的unform
	void setBool(const char *name, bool v);

	//float
	void setFloat(const char *name, float v);
	void setFloatArray(const char *name, const std::vector<float> &v);
	void setFloat2(const char *name, const glm::vec2 &v);
	void setFloat2Array(const char *name, const std::vector<glm::vec2> &v);
	void setFloat3(const char *name, const glm::vec3 &v);
	void setFloat3Array(const char *name, const std::vector<glm::vec3> &v);
	void setFloat4(const char *name, const glm::vec4 &v);
	void setFloat4Array(const char *name, const std::vector<glm::vec4> &v);

	//int
	void setInt(const char *name, int v);
	void setIntArray(const char *name, const std::vector<int> &v);
	void setIntArray(const char *name, int *v, int count);
	void setInt2(const char *name, const glm::ivec2 &vec);
	void setInt2Array(const char *name, const std::vector<glm::ivec2> &v);
	void setInt3(const char *name, const glm::ivec3 &vec);
	void setInt3Array(const char *name, const std::vector<glm::ivec3> &v);
	void setInt4(const char *name, const glm::ivec4 &vec);
	void setInt4Array(const char *name, const std::vector<glm::ivec4> &v);

	//mat
	void setMat2(const char *name, const glm::mat2 &v);
	void setMat2Array(const char *name, const std::vector<glm::mat2> &v);
	void setMat3(const char *name, const glm::mat3 &matrix);
	void setMat3Array(const char *name, const std::vector<glm::mat3> &v);
	void setMat4(const char *name, const glm::mat4 &matrix);
	void setMat4Array(const char *name, const std::vector<glm::mat4> &v);

private:
	Shader();

	uint32_t m_programHandle;
	friend class ShaderLibrary;
};

class NB_API ShaderLibrary
{
public:
	static ref<Shader> add(const std::string &name, const std::string &vsSource, const std::string &fsSource);
	static ref<Shader> addFromFile(const std::string &name, const std::string &filePath);
	static bool exists(const std::string &name);
	static ref<Shader> get(const std::string &name);

private:
	static void initSystemShader();
};

/**************************************
*	纹理
*
*	纹理基类	Texture
*	2D纹理		Texture2D
*	立方体纹理	TextureCubemap
****************************************/
enum class TextureWrappingE		//纹理环绕方式
{
	Repeat			= 0x2901,	//重复
	MirroredRepeat	= 0x8370,	//镜像重复
	ClampToEdge		= 0x812F,	//边缘延伸
	ClampToBorder	= 0xFFFF,	//用户颜色边缘延伸
};

enum class TextureFilterE		//纹理过滤方式，依次向下，纹理细节表现质量越好，性能要求越大。放大过滤只支持Point和Bilinear，缩小过滤支持所有的过滤方式
{
	Point			= 0x2600,	//最邻近过滤，指取最接近浮点的整型像素点位置
	Bilinear		= 0x2601,	//双线性过滤，对邻近的四个点进行线性插值算法，两个维度三次运算
	Trilinear		= 0x2703,	//三线性过滤。三线性过滤以双线性过滤为基础。会对pixel大小与texel大小最接近的两层Mipmap level分别进行双线性过滤，然后再对两层得到的结果进生线性插值。
	Anisotropic		= 0xFFFF,	//各向异性过滤，当需要贴图的三维表面平行于屏幕(viewport)，则是各向同性的。当要贴图的三维表面与屏幕有一定角度的倾斜，则是各向异性的。
};

class NB_API Texture
{
public:
	virtual ~Texture();

	unsigned id() const;

	//激活当前采用单元
	void active();

	//纹理采样单元，默认0
	void setSamplerUnit(unsigned unit);
	unsigned samplerUnit();

	//绑定/解除当前纹理
	virtual void bind() = 0;
	virtual void unbind() = 0;

	void activeAndBind();

	//设置纹理环绕方式
	virtual void setWrappingS(TextureWrappingE wrapping) = 0;
	virtual void setWrappingT(TextureWrappingE wrapping) = 0;
	virtual TextureWrappingE wrappingS() const = 0;
	virtual TextureWrappingE wrappingT() const = 0;

	//纹理过滤方式
	virtual void setMagnifyFilter(TextureFilterE filter) = 0;
	virtual void setNarrowFilter(TextureFilterE filter) = 0;
	virtual TextureFilterE magnifyFilter() const = 0;
	virtual TextureFilterE narrowFilter() const = 0;

protected:
	Texture();

	unsigned m_samplerUnit;
	unsigned m_handle;
};

class NB_API Texture2D : public Texture
{
public:
	Texture2D();
	Texture2D(const std::string &path);

	virtual ~Texture2D() = default;

	virtual void bind() override;
	virtual void unbind() override;
	virtual void setWrappingS(TextureWrappingE wrapping) override;
	virtual void setWrappingT(TextureWrappingE wrapping) override;
	virtual TextureWrappingE wrappingS() const override;
	virtual TextureWrappingE wrappingT() const override;
	virtual void setMagnifyFilter(TextureFilterE filter) override;
	virtual void setNarrowFilter(TextureFilterE filter) override;
	virtual TextureFilterE magnifyFilter() const override;
	virtual TextureFilterE narrowFilter() const override;

	//上传数据到GPU
	void update(const std::string &path);
	void update(ref<Bitmap> bm);

	void genMipmap();

	int32_t getChannels() const;
	bool isValid() const;

	float width() const;
	float height() const;

	bool save(const std::string &path, uint32_t quality = 1);

protected:
	float m_width{ 0.0f };
	float m_height{ 0.0f };
	int32_t m_channels{ 0 };
};

class NB_API TextureCubemap : public Texture
{
public:
	TextureCubemap();
	~TextureCubemap() = default;

	virtual void bind() override;
	virtual void unbind() override;
	virtual void setWrappingS(TextureWrappingE wrapping) override;
	virtual void setWrappingT(TextureWrappingE wrapping) override;
	virtual TextureWrappingE wrappingS() const override;
	virtual TextureWrappingE wrappingT() const override;
	virtual void setMagnifyFilter(TextureFilterE filter) override;
	virtual void setNarrowFilter(TextureFilterE filter) override;
	virtual TextureFilterE magnifyFilter() const override;
	virtual TextureFilterE narrowFilter() const override;

	//更新六面数据(右、左、底、顶、后、前)
	void update(const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back);

};

struct NB_API TextureFrame
{
	ref<Texture2D> texture;
	glm::vec2 offset;
	glm::vec2 size;
	bool rotated;
	glm::vec2 trimmedSize;
};

class NB_API TextureLibrary
{
public:
	static ref<Texture2D> addTexture2D(const std::string &name, const std::string &imagePath);
	static void addTextureAtlas(const std::string &name, const std::string &imagePath, const std::string &cfgPath);
	static ref<TextureCubemap> addTextureCubemap(const std::string &name, const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back);

	static ref<Texture2D> getTexture2D(const std::string &name);
	static const TextureFrame &getFrameFromTextureAtlas(const std::string &name, const std::string &frameName);
	static ref<TextureCubemap> getTextureCubemap(const std::string &name);

};


/*****************************************************
*	灯光
*
*	光基类 Light
*	环境光 AmbientLight
*	方向光 DirectionalLight
*	点光源 PointLight
*	聚光灯 SpotLight
******************************************************/
class Shader;
class NB_API Light : public Object
{
	RTTR_ENABLE(Object)
public:
	Light();
	virtual ~Light() = default;

	virtual void uploadUniform(ref<Shader> shader) const;

	std::string name;
	Color ambient;
	Color diffuse;
	Color specular;
};

class NB_API AmbientLight : public Light
{
	RTTR_ENABLE(Light)
public:
	AmbientLight() = default;
};

class NB_API DirectionalLight : public Light
{
	RTTR_ENABLE(Light)
public:
	DirectionalLight() : direction(glm::vec3(0.0, 0.0, -1.0)) {}

	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 direction;
};

class NB_API PointLightBase : public Light
{
	RTTR_ENABLE(Light)
public:
	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 position{ 0.0f, 0.0f, 5.0f };			//光位置
	float constantAttenuation{ 1.0f };	//光强度按其随距离减弱的常数值
	float linearAttenuation{ 0.0f };		//光强度随距离线性减弱的值
	float quadraticAttenuation{ 0.0f };	//光效果随距离而减弱的值（由二次运算计算所得）
};

class NB_API PointLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	PointLight() = default;
};

class NB_API SpotLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 direction{ 0.0f, 0.0f, -1.0f };	//投射光线的方向
	float innerConeAngle{ 90.0f };				//内圈锥形投影部分的角度
	float outerConeAngle{ 180.0f };				//外圈锥形投影部分的角度
};


/*****************************************************
*	材质
*
*	材质基类 Material
*	纯色材质 SolidColorMaterial
*	渐变色材质 LinearGrandientMaterial
*	Phong材质 PhongMaterial
*	天空盒材质 SkyBoxMaterial
*	立方体贴图材质 CubemapMaterial
******************************************************/
class Camera;
class Shader;
class Texture;
class NB_API Material : public Object
{
	RTTR_ENABLE(Object)
public:
	//执行更新uniform的动作，在mesh渲染时调用
	virtual void uploadUniform(ref<Camera> camera) = 0;

	std::string name;
	ref<Shader> shader;

protected:
	Material() = default;
	Material(ref<Shader> _shader);

};

class NB_API SolidColorMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	SolidColorMaterial();
	SolidColorMaterial(const Color &_color);

	virtual void uploadUniform(ref<Camera> camera) override;

	Color color;
};

class NB_API GradientStop
{
public:
	float offset;
	Color color;
};

class NB_API LinearGrandientMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	LinearGrandientMaterial();
	LinearGrandientMaterial(float _lenght, const std::vector<GradientStop> &_grandients);

	virtual void uploadUniform(ref<Camera> camera) override;

	bool vertical;
	float lenght;
	std::vector<GradientStop> grandients;
};

class NB_API PhongMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	PhongMaterial();

	virtual void uploadUniform(ref<Camera> camera) override;

	Color ambientColor;				//环境光影响因子
	Color diffuseColor;				//漫反射光影响因子
	Color specularColor;			//镜面高光音影响因子
	Color emissionColor;			//自发光颜色
	ref<Texture> diffuseMapping;	//漫反射贴图
	ref<Texture> specularMapping;	//高光贴图
	ref<Texture> emissionMapping;	//自发光贴图
	float shineness;				//光照强度因子
	float opacity;					//不透明度
};

class NB_API SkyBoxMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	SkyBoxMaterial();
	SkyBoxMaterial(ref<Texture> _cubeMapping);

	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture> cubeMapping;
};

class NB_API CubemapMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	CubemapMaterial();

	virtual void uploadUniform(ref<Camera> camera) override;

	Color ambient;				//环境光影响因子
	Color diffuse;				//漫反射光影响因子
	Color specular;				//镜面高光音影响因子
	Color cubeMapColor;			//底色
	ref<Texture> diffuseMapping;//漫反射贴图
	ref<Texture> cubeMapping;	//立方体贴图
};

}

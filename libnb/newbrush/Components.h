#pragma once
#include "newbrush/Bitmap.h"
#include "newbrush/Object.h"
#include "newbrush/Types.h"
#include "newbrush/Event.h"

#if (defined NB_OS_FAMILY_WINDOWS) || (NB_OS == NB_OS_LINUX && NB_ARCH != NB_ARCH_ARM)
	#define NB_USE_GLAD
	#include "glad/glad.h"
#else
	#include <GLES3/gl3.h>
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
*	变换
*
*	摄像头基类 Camera
*	透视摄像头 PerspectiveCamera
*	正交摄像头 OrthographicCamera
****************************************/

class NB_API Transform : public Object
{
	RTTR_ENABLE(Object)
public:
	Transform(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0), const glm::vec3 &scale = glm::vec3(1.0));

	//单位矩阵
	bool isIdentity() const							{ return glm::isIdentity(value(), 0.00001f); }
	static const Transform &identity()				{ static Transform t; return t; }
	static const glm::mat4 &identityMatrix4()		{ static const glm::mat4 m(1.0f); return m; };

	//矩阵（设置矩阵值后，平移、旋转、缩放会被计算）
	void setValue(const glm::mat4x4 &value);
	const glm::mat4x4 &value() const				{ return m_matrix; }

	void setTranslate(const glm::vec3 &translate)	{ m_translate = translate; updateMatrix(); }
	void setRotate(const glm::vec3 &rotate)			{ m_rotate = rotate; updateMatrix(); }
	void setRotateCenter(const glm::vec3 &center)	{ m_rotateCenter = center; updateMatrix(); }
	void setScale(const glm::vec3 &scale)			{ m_scale = scale; updateMatrix(); }
	void setScaleCenter(const glm::vec3 &center)	{ m_scaleCenter = center; updateMatrix(); }
	const glm::vec3 &getTranslate() const			{ return m_translate; }
	const glm::vec3 &getRotate() const				{ return m_rotate; }
	const glm::vec3 &getScale() const				{ return m_scale; }

private:
	void updateMatrix();

	glm::vec3 m_translate, m_rotate, m_rotateCenter, m_scale, m_scaleCenter;	//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	glm::mat4 m_matrix;
};

class NB_API Transform2D : public Object
{
	RTTR_ENABLE(Object)
public:
	Transform2D() = default;
	virtual ~Transform2D() = default;
	virtual glm::mat4x4 value() = 0;
};

class NB_API TranslateTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	TranslateTransform2D() : TranslateTransform2D(0.0f, 0.0f)	{}
	TranslateTransform2D(float x, float y) : m_x(x), m_y(y)		{}
	virtual ~TranslateTransform2D() = default;

	void setX(float x)											{ m_x = x; }
	float getX() const											{ return m_x; }
	void setY(float y)											{ m_y = y; }
	float getY() const											{ return m_y; }
	virtual glm::mat4x4 value() override;

private:
	float m_x, m_y;
};

class NB_API RotateTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	RotateTransform2D() : RotateTransform2D(0.0f, 0.0f, 0.0f) {}
	RotateTransform2D(float angle) : RotateTransform2D(angle, 0.0f, 0.0f) {}
	RotateTransform2D(float angle, float centerX, float centerY) : m_angle(angle), m_centerX(centerX), m_centerY(centerY) {}
	virtual ~RotateTransform2D() = default;

	void setAngle(float angle)									{ m_angle = angle; }
	float getAngle() const										{ return m_angle; }
	void setCenterX(float centerX)								{ m_centerX = centerX; }
	float getCenterX() const									{ return m_centerX; }
	void setCenterY(float centerY)								{ m_centerY = centerY; }
	float getCenterY() const									{ return m_centerY; }
	virtual glm::mat4x4 value() override;

private:
	float m_angle, m_centerX, m_centerY;
};

class NB_API ScaleTransform2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	ScaleTransform2D() : ScaleTransform2D(1.0f, 1.0f, 0.0f, 0.0f) {}
	ScaleTransform2D(float scaleX, float scaleY) : ScaleTransform2D(scaleX, scaleY, 0.0f, 0.0f) {}
	ScaleTransform2D(float scaleX, float scaleY, float centerX, float centerY) : m_scaleX(scaleX), m_scaleY(scaleY), m_centerX(centerX), m_centerY(centerY) {}
	virtual ~ScaleTransform2D() = default;

	void setScaleX(float scaleX)								{ m_scaleX = scaleX; }
	float getScaleX() const										{ return m_scaleX; }
	void setScaleY(float scaleY)								{ m_scaleY = scaleY; }
	float getScaleY() const										{ return m_scaleY; }
	void setScale(glm::vec2 scale)								{ m_scaleX = scale.x; m_scaleY = scale.y; }
	glm::vec2 getScale() const									{ return{ m_scaleX, m_scaleY }; }
	void setCenterX(float centerX)								{ m_centerX = centerX; }
	float getCenterX() const									{ return m_centerX; }
	void setCenterY(float centerY)								{ m_centerY = centerY; }
	float getCenterY() const									{ return m_centerY; }
	virtual glm::mat4x4 value() override;

private:
	float m_scaleX, m_scaleY, m_centerX, m_centerY;
};

class NB_API TransformGroup2D : public Transform2D
{
	RTTR_ENABLE(Transform2D)
public:
	TransformGroup2D();
	TransformGroup2D(const std::vector<ref<Transform2D>> &children) : m_children(children) {}

	void add(ref<Transform2D> t)								{ m_children.push_back(t); }
	uint32_t count() const										{ return m_children.size(); }
	virtual glm::mat4x4 value() override;

private:
	std::vector<ref<Transform2D>> m_children;
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

	void setTranslate(const glm::vec3 &translate)				{ m_translate = translate; updateMatrix(); }
	void setRotate(const glm::vec3 &rotate)						{ m_rotate = rotate; updateMatrix(); }
	void setScale(const glm::vec3 &scale)						{ m_scale = scale; updateMatrix(); }
	const glm::vec3 &getTranslate() const						{ return m_translate; }
	const glm::vec3 &getRotate() const							{ return m_rotate; }
	const glm::vec3 &getScale() const							{ return m_scale; }

	void setFov(float fov)										{ m_fov = fov; updateMatrix(); }
	void setAspect(float aspect)								{ if (std::isnan(aspect) || aspect == m_aspect) return; m_aspect = aspect; updateMatrix(); }
	void setNearPlane(float nearPlane)							{ m_nearPlane = nearPlane; updateMatrix(); }
	void setFarPlane(float farPlane)							{ m_farPlane = farPlane; updateMatrix(); }
	float getFov() const										{ return m_fov; }
	float getAspect() const										{ return m_aspect; }
	float getNearPlane() const									{ return m_nearPlane; }
	float getFarPlane() const									{ return m_farPlane; }

	//获取观察矩阵/透视矩阵
	const glm::mat4 &getViewProjectionMatrix() const override	{ return m_viewProjectionMatrix; }

private:
	void updateMatrix();

	glm::vec3 m_translate, m_rotate, m_scale;					//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	float m_fov, m_aspect, m_nearPlane, m_farPlane;
	glm::mat4 m_viewProjectionMatrix;
};

class NB_API OrthographicCamera : public Camera
{
	RTTR_ENABLE(Camera)
public:
	OrthographicCamera() : m_matrix(1.0f) {}

	void resize(float width, float height)						{ m_matrix = glm::ortho(0.0f, width, height, 0.0f, -1000.0f, 1000.0f); }
	const glm::mat4 &getViewProjectionMatrix() const override	{ return m_matrix; }

private:
	glm::mat4 m_matrix;
};

NB_API inline ref<OrthographicCamera> sharedCamera2D()			{ static auto sharedCamera = createRef<OrthographicCamera>(); return sharedCamera; }

/**************************************
*	着色器
*
*	着色器 Shader
*	着色器库 ShaderLibrary
*	
****************************************/
class NB_API Shader
{
public:
	~Shader();
	Shader(const Shader &other) = delete;
	void operator =(const Shader &other) = delete;

	//编译链接
	//异常：std::runtime_error
	void compileLink(const std::string &vsSource, const std::string &fsSource);

	int getAttributeLocation(const char *name) const;
	int getUniformLocation(const char *name) const;
	void bindAttributeLocation(uint32_t location, const char *name);

	uint32_t id() { return m_programHandle; }

	void use();
	void disuse();

	//更新的attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新uniform
	void setBool(const char *name, bool v);
	void setFloat(const char *name, float v);
	void setFloatArray(const char *name, const std::vector<float> &v);
	void setFloat2(const char *name, const glm::vec2 &v);
	void setFloat2Array(const char *name, const std::vector<glm::vec2> &v);
	void setFloat3(const char *name, const glm::vec3 &v);
	void setFloat3Array(const char *name, const std::vector<glm::vec3> &v);
	void setFloat4(const char *name, const glm::vec4 &v);
	void setFloat4Array(const char *name, const std::vector<glm::vec4> &v);
	void setInt(const char *name, int v);
	void setIntArray(const char *name, const std::vector<int> &v);
	void setIntArray(const char *name, int *v, int count);
	void setInt2(const char *name, const glm::ivec2 &vec);
	void setInt2Array(const char *name, const std::vector<glm::ivec2> &v);
	void setInt3(const char *name, const glm::ivec3 &vec);
	void setInt3Array(const char *name, const std::vector<glm::ivec3> &v);
	void setInt4(const char *name, const glm::ivec4 &vec);
	void setInt4Array(const char *name, const std::vector<glm::ivec4> &v);
	void setMat2(const char *name, const glm::mat2 &v);
	void setMat2Array(const char *name, const std::vector<glm::mat2> &v);
	void setMat3(const char *name, const glm::mat3 &v);
	void setMat3Array(const char *name, const std::vector<glm::mat3> &v);
	void setMat4(const char *name, const glm::mat4 &v);
	void setMat4Array(const char *name, const std::vector<glm::mat4> &v);

private:
	Shader() : m_programHandle(0) {}

	uint32_t m_programHandle;
	friend class ShaderLibrary;
};

class NB_API ShaderLibrary
{
public:
	static ref<Shader> get(const std::string &name, const std::string &vsSource, const std::string &fsSource);
	static ref<Shader> get(const std::string &name);
	static ref<Shader> getFromFile(const std::string &name, const std::string &filePath);
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

	unsigned id() const					{ return m_handle; }
	void active();
	void activeAndBind()				{ active(); bind(); }
	void setSamplerUnit(unsigned unit)	{ m_samplerUnit = unit; }
	unsigned samplerUnit()				{ return m_samplerUnit; }

	//绑定纹理
	virtual void bind() = 0;
	virtual void unbind() = 0;

	//纹理环绕方式
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

	bool isValid() const			{ return m_channels != 0; }
	int32_t getChannels() const		{ return m_channels; }
	float width() const				{ return m_width; }
	float height() const			{ return m_height; }

	bool save(const std::string &path, uint32_t quality = 1);

protected:
	float m_width;
	float m_height;
	int32_t m_channels;
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
	TextureFrame();
	TextureFrame(ref<Texture2D> _texture);
	TextureFrame(ref<Texture2D> _texture, const Rect &rc);

	ref<Texture2D> texture;
	glm::vec4 frame;		//x,y：帧图片相对于texture的偏移量;w,z：帧图片实际（trimmed之后）的尺寸（对应于"frame"）
	glm::vec2 sourceSize;	//图片原始的尺寸（对应于"sourceSize")
	glm::vec2 pinch;		//图片的缩进xy（对应于"spriteSourceSize.xy"）
	bool rotated;			//是否旋转（对应于"rotated"，顺时针90°）

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
*	纯色材质 FlatMaterial
*	渐变色材质 LinearGrandientMaterial
*	Phong材质 PhongMaterial
*	天空盒材质 SkyBoxMaterial
*	立方体贴图材质 CubemapMaterial
******************************************************/
class NB_API Material : public Object
{
	RTTR_ENABLE(Object)
public:
	Material() = default;
	Material(ref<Shader> _shader);

	//执行更新uniform的动作，在mesh渲染时调用
	virtual void uploadUniform(ref<Camera> camera) {}

	std::string name;
	ref<Shader> shader;
};

class NB_API FlatMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	FlatMaterial() : FlatMaterial(Colors::black) {}
	FlatMaterial(const Color &_color);

	virtual void uploadUniform(ref<Camera> camera) override;

	Color color;
};

struct GradientStop
{
	float offset;
	Color color;
};

class NB_API LinearGrandientMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	LinearGrandientMaterial();

	virtual void uploadUniform(ref<Camera> camera) override;

	glm::vec4 box;
	bool horizontal;
	std::vector<GradientStop> gradientStops;
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

/*****************************************************
*	面片
*
*	顶点类 Vertex
*	面片 Mesh
*
******************************************************/
struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec4 boneIndexs{ 0.0f };
	glm::vec4 boneWeights{ 0.0f };
	bool addBone(float boneIndex, float boneWeight);
};

class NB_API Mesh
{
public:
	Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, ref<Material> materia);
	~Mesh();

	virtual void draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>> &lights, int mode = GL_TRIANGLES) const;

	std::string name;
	ref<Material> material;
	bool hasBone;
	bool renderAble;

protected:
	void setup(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

private:
	uint32_t vao, vbo, ebo, indicesSize;
};

/*****************************************************
*	定时器
*
*	定时器类 Timer
******************************************************/
class NB_API Timer : public Object
{
public:
	//构建一个定时器，它的间隔为ms，单次触发模式为singleShot
	explicit Timer(uint64_t ms = 1000, bool singleShot = false) : m_interval(ms), m_singleShot(singleShot) {}
	~Timer()							{ stop(); }

	void setInterval(uint64_t msec)		{ m_interval = msec; }
	uint64_t interval() const			{ return m_interval; }
	void setSingleShot(bool singleShot)	{ m_singleShot = singleShot; }
	bool isSingleShot() const			{ return m_singleShot; }
	void start()						{ remove(this); add(this); }
	void start(uint64_t msec)			{ setInterval(msec); start(); }
	void stop()							{ remove(this); }
	bool isActive() const;

	Event<EventArgs> Tick;

	static void driveInLoop();			//引发定时器引擎，在循环中调用

private:
	static void add(Timer *timer);
	static std::multimap<uint64_t, Timer *>::iterator remove(Timer *timer);

	uint64_t m_interval;
	bool m_singleShot;
};

}

//粒子发射器
//粒子发射器根据自身的各种属性，来决定粒子各属性的变化规则
//粒子发射器属性有几类概念：
//1、动画值，表示发射个数，每次回计算线性动画值，而非固定的值
//2、变化度，表示一个变化区间范围，一般是浮点型，变化度取值为[-var, var]
#pragma once
#include <vector>
#include <set>
#include <array>
#include "../core/Def.h"
#include "AnimationValue.h"
#include "glm/glm.hpp"

namespace nb { namespace gl {
	
enum class ParticleFacingTypeE
{
	Billboard2D,
	Billboard3D,
};

enum class ParticleBlendModeE
{
	AlphaBlend,
	Additive,
	Multiplay,
	Mutiplay2x,
	Subtract,
};

struct ParticleEmitterDepthSettings
{
	bool	usesDepthSoftening{ false };
	float	depthFadeDistance{ 0.0f };
	float	depthFadePower{ 0.0f };
};

struct ParticleEmitterTextureAnimation
{
	bool				isAnimated					{ false };
	bool				randomizeInitialFrame		{ false };
	uint32_t			frameCountX					{ 0 };
	uint32_t			frameCountY					{ 0 };
	float				framesPersecond				{ 0.0f };
	float				frameTimeVar				{ 0.0f };
	std::array<bool, 3>	isAnimatedForTextureIndex	{ false };
};

struct ParticleEmitterWideUpdates
{
	float						rotationalVelocity{ 0.0f };
	std::array<glm::vec2, 3>	uvScrollDelta;
	glm::vec3					particleUp;
	glm::vec3					particleRight;
	glm::vec3					particleForward;
};

class Particle;
class ParticleEmitter
{
public:
	//构建一个粒子发射器，它隶属于内存池poolId，支持的最大粒子数为maxParticleCount
	ParticleEmitter();

	//
	void init(uint32_t poolId, uint32_t maxParticleCount);

	//开始/停止
	void start();
	void stop();

	//是否已经完成
	bool isComplete() const;

	//渲染
	void render();

	//发射粒子的初始化更新
	void update(float deltaTime);

private:

	uint32_t						m_poolId;						//隶属的内存池ID
	bool							m_shouldEmit;					//是否需要发射标志

	float							m_emitterLifeTime;				//发射器生命
	float							m_emitterCurrentLife;			//发射器历经时间
	uint32_t						m_maxParticleCount;				//最大粒子数
	uint32_t						m_minParticleCount;				//最小粒子数
	float							m_floatingParticle;				//发射粒子小数累积部分，大于等于1.0后成为一整个发射粒子，然后它重置为0.0，这对于在发射器发射少量粒子的case效果更加满意
	std::vector<Particle *>			m_particles;					//已发射的粒子
	AnimationValue<float>			m_emiteCountPerSecond;			//每秒发射粒子个数，线性动画值，即每次发射个数都可以是个浮动值

	float							m_particleLifeTime;				//粒子生命周期
	float							m_particleLifeTimeVar;			//粒子生命变量？
	glm::vec3						m_spawnArea;					//孵化位置
	AnimationValue<glm::vec4>		m_colorMultiplier;				//颜色乘数
	glm::vec4						m_colorVar;						//颜色动画值
	AnimationValue<float>			m_rotationalVelocity;			//旋转速率动画值
	float							m_rotationVar;					//旋转变化度
	float							m_rotationRateVar;				//旋转速度变化度
	AnimationValue<glm::vec3>		m_scale;						//缩放动画值
	float							m_scaleVar;						//缩放变化度
	std::array<AnimationValue<glm::vec2>, 3>	m_uvScroll;			//纹理坐标动画值，支持三个纹理
	std::array<glm::vec2, 3> 		m_uvScrollOffsets;				//纹理坐标偏移，支持三个纹理
	std::array<glm::vec2, 3>		m_uvScroolVar;					//纹理坐标偏移动画值，支持三个纹理
	AnimationValue<float>			m_materialIntensity;			//材质强度动画值
	float							m_materialIntensityVar;			//材质强度变化度
	ParticleEmitterTextureAnimation	m_texutreAnimation;				//纹理动画

	AnimationValue<float>			m_velocity;						//速率动画值
	glm::vec3						m_velocityVar;					//速率变化度
	glm::vec3						m_gravity;						//重力

	uint32_t						m_startVert;
	uint32_t						m_endVert;
};

}}
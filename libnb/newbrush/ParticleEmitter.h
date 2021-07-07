//粒子发射器
//粒子发射器根据自身的各种属性，来决定粒子各属性的变化规则
//粒子发射器属性有几类概念：
//1、动画值，表示发射个数，每次回计算线性动画值，而非固定的值
//2、变化度，表示一个变化区间范围，一般是浮点型，变化度取值为[-var, var]
#pragma once
#include <vector>
#include <set>
#include <array>
#include "newbrush/Types.h"

namespace nb {

/**************************************
*	动画插值
*
*	动画关键帧 AnimatedValueKey
*	值动画 AnimationValue
*	
****************************************/
template<class T>
class AnimatedValueKey
{
public:
	AnimatedValueKey() : time(0), v(T()) {}
	AnimatedValueKey(float _time, const T &_v) : time(_time), v(_v) {}
	bool operator > (const AnimatedValueKey &other) const { return time > other.time; }
	bool operator < (const AnimatedValueKey &other) const { return time < other.time; }

	float time;
	T v;
};

template<class T>
class AnimationValue
{
public:
	AnimationValue() : m_loop(false), m_currentTime(-1.0f) {}

	void add(float time, T v)
	{
		m_keyFrames.emplace_back(time, v);
		std::sort(m_keyFrames.begin(), m_keyFrames.end());
	}

	//获取时间的上下关键帧
	void getPrevNextFramesByTime(float time, uint32_t &prevFrame, uint32_t &nextFrame)
	{
		uint32_t begin = 0;
		uint32_t end = (uint32_t)m_keyFrames.size() - 1;

		while (begin != end)
		{
			int middle = (begin + end) / 2;
			if (m_keyFrames[middle].time < time)
			{
				begin = middle + 1;
			}
			else
			{
				end = middle;
			}
		}

		prevFrame = begin > 0 ? begin - 1 : 0;
		nextFrame = begin;
	}

	//获取时间点的插值：找到上下关键帧后的线性插值
	T getValueByTime(float time)
	{
		auto numKeys = m_keyFrames.size();

		if (numKeys < 2)
		{
			return T(); // we need to have at least 2 keys
		}

		if (time <= m_keyFrames[0].time)
		{
			return m_keyFrames[0].v;
		}

		if (time >= m_keyFrames[numKeys - 1].time)
		{
			return m_keyFrames[numKeys - 1].v;
		}

		uint32_t prevFrame = 0;
		uint32_t nextFrame = 0;
		getPrevNextFramesByTime(time, prevFrame, nextFrame);

		float timeBetweenFrames = m_keyFrames[nextFrame].time - m_keyFrames[prevFrame].time;
		float percentageThroughFrame = (time - m_keyFrames[prevFrame].time) / timeBetweenFrames;

		T keyValue = m_keyFrames[nextFrame].v * percentageThroughFrame + m_keyFrames[prevFrame].v * (1.0f - percentageThroughFrame);

		return keyValue;
	}

	T getValueByDelta(float deltaTime)
	{
		auto numKeys = m_keyFrames.size();

		if (numKeys < 2)
		{
			return T(); // we need to have at least 2 keys
		}

		float firstFrameTime = m_keyFrames[0].time;
		float lastFrameTime = m_keyFrames[numKeys - 1].time;

		if (m_currentTime >= lastFrameTime)
		{
			if (m_loop)
			{
				m_currentTime = firstFrameTime;
			}
			else
			{
				return m_keyFrames[numKeys - 1].v;
			}
		}

		if (m_currentTime <= firstFrameTime)
		{
			m_currentTime = firstFrameTime + deltaTime;
			return m_keyFrames[0].v;
		}

		uint32_t prevFrame = 0;
		uint32_t nextFrame = 0;
		getPrevNextFramesByTime(m_currentTime, prevFrame, nextFrame);

		float timeBetweenFrames = m_keyFrames[nextFrame].time - m_keyFrames[prevFrame].time;
		float percentageThroughFrame = timeBetweenFrames <= 0 ? 0 : (m_currentTime - m_keyFrames[prevFrame].time) / timeBetweenFrames;

		T keyValue = m_keyFrames[nextFrame].v * percentageThroughFrame + m_keyFrames[prevFrame].v * (1.0f - percentageThroughFrame);

		m_currentTime += deltaTime;

		return keyValue;
	}

	bool m_loop;
	float m_currentTime;	//0.0-1.0
	std::vector<AnimatedValueKey<T>> m_keyFrames;
};



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
	std::array<bool, 3>	isAnimatedForTextureIndex	{{ false }};
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

}

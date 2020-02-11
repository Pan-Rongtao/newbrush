#pragma once
#include <vector>
#include <set>
#include <array>
#include "newbrush/core/Def.h"
#include "newbrush/gles/AnimationValue.h"
#include "glm/glm.hpp"

namespace nb{

class Particle;
class ParticleSystem;
class ParticleEmitter;
class ParticleMemoryPool;

//粒子总管理
class ParticleManager
{
public:
	static void init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount);

	static void update();
};

//粒子内存池管理
class ParticleMemoryPoolManager
{
public:
	static void init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount);
	static ParticleMemoryPool *getMemoryPool(uint32_t index);
	static size_t getBestPoolIdForNewParticles();

private:
	static std::vector<ParticleMemoryPool *>	m_memoryPools;
};

//粒子内存池
class ParticleMemoryPool
{
public:
	ParticleMemoryPool(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount);
	
	Particle *applyParticle();
	void freeParticle(Particle *particle);
	size_t getActiveParticleCount() const;

private:
	ParticleSystem	*m_particleSystems;
	ParticleEmitter	*m_emitters;
	Particle		*m_particles;
	uint32_t 		m_particleSystemsCount;
	uint32_t 		m_emitterCount;
	uint32_t 		m_particleCount;
	uint32_t		m_curParticleSystemIndex;
	uint32_t		m_curEmitterIndex;
	uint32_t		m_curParticleIndex;
	std::vector<Particle *>	m_reusableParticles;
};

//粒子系统，管理单个效果的多个发射器
class ParticleSystem
{
public:

};

//粒子
class Particle
{
public:
	glm::vec3					position;			//位置
	glm::vec4					colorMul;			//?不是color？？
	glm::vec4					colorVar;			//？？
	std::array<glm::vec2, 3>	texOffsets;			//纹理坐标，支持三个纹理
	float						rotation;			//旋转（为啥是float不是vec3？）
	float						ratationRate;		//旋转速度
	glm::vec3					initialScale;		//初始缩放
	glm::vec3					scale;				//缩放
	glm::vec3					velocity;			//速度（x,y,z三个维度）
	glm::vec3					acceleration;		//加速度
	float						lifeTime;			//生命周期
	float						currentLife;		//当前生命
	float						intensity;			//强度
	glm::vec2					textureFrame;		//??
	float						textureFrameTime;	//??
	float						textureFrameTimeVar;//??
};

}
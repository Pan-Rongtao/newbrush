#pragma once
#include <array>
#include <vector>
#include <thread>
#include "newbrush/Types.h"

namespace nb
{
	
class Particle;
class ParticleSystem;
class ParticleEmitter;
class ParticleMemoryPool;

//粒子总管理
//它将管理粒子系统、粒子发射器、粒子的初始化
//粒子管理器可以在全局范围内处理所有事情。 
//它包含粒子系统数组的阵列，主粒子顶点缓冲区，并处理主要渲染和更新循环。 
class ParticleManager
{
public:
	//初始化
	static void init();

	//渲染更新
	static void update(float deltaTime, const glm::vec3 &cameraDirection);
};

//粒子内存池管理器
//它管理着多个ParticleMemoryPool
//负责为新的粒子系统选择最佳的内存池
class ParticleMemoryPoolManager
{
public:
	static void init(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount, uint32_t poolCount);
	static ParticleMemoryPool *getMemoryPool(uint32_t index);
	static size_t getBestPoolIdForNewParticles();

private:
	static std::vector<ParticleMemoryPool *>	m_memoryPools;
};

//粒子内存池
//复制申请粒子和释放调度
//受ParticleMemoryPoolManager
class ParticleMemoryPool
{
public:
	//构建一个粒子内存池，它将拥有粒子系统particleSystemCount个，发射器emitterCount个，粒子数particleCount
	ParticleMemoryPool(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount);

	//申请新的粒子
	Particle *applyParticle();

	//释放粒子
	void freeParticle(Particle *particle);

	//获取活动的粒子数
	size_t getActiveParticleCount() const;

private:
	Particle		*m_particles;				//粒子指针
	uint32_t 		m_particleCount;			//粒子个数
	uint32_t		m_curParticleIndex;			//粒子下标
	ParticleEmitter	*m_emitters;				//粒子发射器指针
	uint32_t 		m_emitterCount;				//粒子发射器个数
	uint32_t		m_curEmitterIndex;			//粒子发射器下标
	ParticleSystem *m_particleSystems;			//粒子系统指针
	uint32_t 		m_particleSystemsCount;		//粒子系统个数
	uint32_t		m_curParticleSystemIndex;	//粒子系统下标

	std::vector<Particle *>	m_reusableParticles;//可重复使用粒子数组
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

//////////
class NB_API ParticleVertexBuffer
{
public:
	ParticleVertexBuffer(uint32_t particleCount, uint32_t poolCount);


private:
	std::vector<float>	*m_ver;
	std::vector<int>	m_indices;
};

class ParticleUpdateJob
{
public:

};

}

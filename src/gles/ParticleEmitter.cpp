#include "gles/ParticleEmitter.h"
#include "gles/Particle.h"
#include "glm/gtc/random.hpp"

using namespace nb::gl;

ParticleEmitter::ParticleEmitter()
	: m_minParticleCount(0)
{

}

void ParticleEmitter::init(uint32_t poolId, uint32_t maxParticleCount)
{
	m_poolId = poolId;
	m_maxParticleCount = maxParticleCount;
}

void ParticleEmitter::start()
{
	m_shouldEmit = true;
}

void ParticleEmitter::stop()
{
	m_shouldEmit = false;

}

bool ParticleEmitter::isComplete() const
{
	return m_shouldEmit;
}

void ParticleEmitter::update(float deltaTime)
{
	if (m_emitterCurrentLife > m_emitterLifeTime)
		return;

	m_emitterCurrentLife += deltaTime;

	float emission = m_emiteCountPerSecond.getValueByDelta(deltaTime) * deltaTime;
	uint32_t toBeEmitCount = (uint32_t)emission;
	float p = emission - (uint32_t)emission;
	if (m_floatingParticle + p > 1.0f)
	{
		toBeEmitCount += 1;
		m_floatingParticle -= 1.0f;
	}

	//if m_minParticleCount > m_particles.size(), to fix toBeEmitCount to m_minParticleCount at least
	int diff = m_minParticleCount - (uint32_t)m_particles.size();	//感觉这里有bug，m_particles.size()应该是toBeEmitCount才对
	if (diff > 0)
	{
		toBeEmitCount += diff;
	}

	//init all emit particles
	for (size_t i = 0; i != toBeEmitCount; ++i)
	{
		if (m_particles.size() >= m_maxParticleCount)
			break;

		Particle *pNew = ParticleMemoryPoolManager::getMemoryPool(m_poolId)->applyParticle();
		if (!pNew)
			break;

		pNew->position = glm::linearRand(-m_spawnArea, m_spawnArea);	//??
		pNew->colorMul = glm::vec4(1, 1, 1, 1);
		pNew->colorVar = glm::linearRand(-m_colorVar, m_colorVar);
		pNew->rotation = glm::linearRand(-m_rotationVar, m_rotationVar);
		pNew->ratationRate = glm::linearRand(-m_rotationRateVar, m_rotationRateVar);
		float scaleRand = glm::linearRand(-m_scaleVar, m_scaleVar);
		pNew->initialScale = glm::vec3(scaleRand, scaleRand, 0);
		pNew->scale = pNew->initialScale;
		pNew->velocity = m_velocity.getValueByDelta(deltaTime) + glm::linearRand(-m_velocityVar, m_velocityVar);
		pNew->acceleration = m_gravity;
		pNew->lifeTime = m_particleLifeTime + glm::linearRand(-m_particleLifeTimeVar, m_particleLifeTimeVar);
		pNew->currentLife = 0;
		for (auto i = 0; i != pNew->texOffsets.size(); ++i)
			pNew->texOffsets[i] = m_uvScrollOffsets[i] + glm::linearRand(-m_uvScroolVar[i], m_uvScroolVar[i]);

		pNew->textureFrame = glm::vec2(0, 0);
		pNew->textureFrameTime = 0.0f;
		pNew->textureFrameTimeVar = glm::linearRand(-m_texutreAnimation.frameTimeVar, m_texutreAnimation.frameTimeVar);
		if (m_texutreAnimation.isAnimated && m_texutreAnimation.randomizeInitialFrame)
		{
			if (m_texutreAnimation.frameCountX > 0 && m_texutreAnimation.frameCountY > 0)
			{
				pNew->textureFrame = glm::vec2(glm::linearRand(0u, m_texutreAnimation.frameCountX - 1), glm::linearRand(0u, m_texutreAnimation.frameCountY - 1));
			}
		}

		m_particles.push_back(pNew);
	}

	//m_startVert = managedBuffer->GetCurrentVertCount(m_poolId);

	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		Particle *p = m_particles[i];
		if (p->currentLife > p->lifeTime)
		{
			ParticleMemoryPoolManager::getMemoryPool(m_poolId)->freeParticle(p);
			m_particles.erase(m_particles.begin() + i);
			i -= 1;
			continue;
		}

		float percentThroughLife = p->currentLife / p->lifeTime;
		glm::vec4 clolorMultiplier = m_colorMultiplier.getValueByTime(percentThroughLife);
		glm::vec3 scalar = m_scale.getValueByTime(percentThroughLife);

		p->velocity += p->acceleration * deltaTime;
		p->position += p->velocity * deltaTime;
		p->rotation += (m_rotationalVelocity.getValueByDelta(deltaTime) + p->ratationRate) * deltaTime;
		p->scale = scalar + p->initialScale;
		p->colorMul = m_colorMultiplier.getValueByTime(percentThroughLife) + p->colorVar;

		for (auto i = 0; i != p->texOffsets.size(); ++i)
			p->texOffsets[i] += m_uvScroll[i].getValueByDelta(deltaTime) * deltaTime;

		p->currentLife += deltaTime;
	}
}

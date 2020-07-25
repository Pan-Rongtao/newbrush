#include "newbrush/rvl/gles/Particle.h"
#include "newbrush/rvl/gles/ParticleEmitter.h"

using namespace nb;

ParticleMemoryPool::ParticleMemoryPool(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount)
	: m_particleSystemsCount(particleSystemCount)
	, m_emitterCount(emitterCount)
	, m_particleCount(particleCount)
	, m_curParticleSystemIndex(0)
	, m_curEmitterIndex(0)
	, m_curParticleIndex(0)
{
	m_particleSystems = new ParticleSystem[particleSystemCount];
	m_emitters = new ParticleEmitter[emitterCount];
	for (int i = 0; i != emitterCount; ++i)
		m_emitters[i].init(0, particleCount);
	m_particles = new Particle[particleCount];
}

Particle * ParticleMemoryPool::applyParticle()
{
	Particle *p = nullptr;
	if (m_curParticleIndex < m_particleCount)
	{
		p = &m_particles[m_curParticleIndex++];
	}
	else if (!m_reusableParticles.empty())
	{
		p = m_reusableParticles[m_reusableParticles.size() - 1];
		m_reusableParticles.pop_back();
	}
	return p;
}

void ParticleMemoryPool::freeParticle(Particle * particle)
{
	//partial->reset();
	m_reusableParticles.push_back(particle);
}

size_t ParticleMemoryPool::getActiveParticleCount() const
{
	if (m_curParticleIndex < m_particleCount)
		return m_curParticleIndex;
	else
		return m_particleCount - m_reusableParticles.size();
}

////////////////////////////
std::vector<ParticleMemoryPool *> ParticleMemoryPoolManager::m_memoryPools;
void ParticleMemoryPoolManager::init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount)
{
	bool bInit = false;
	if (bInit)
		nbThrowException(std::logic_error, "can't init twice.");

	for (int i = 0; i != poolCount; ++i)
	{
		ParticleMemoryPool *p = new ParticleMemoryPool(particleSystemCount / poolCount, emitterCount / poolCount, particleCount / poolCount);
		m_memoryPools.push_back(p);
	}
	bInit = true;
}

ParticleMemoryPool * ParticleMemoryPoolManager::getMemoryPool(uint32_t index)
{
	if (index >= m_memoryPools.size())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_memoryPools.size());

	return m_memoryPools[index];
}

size_t ParticleMemoryPoolManager::getBestPoolIdForNewParticles()
{
	auto iter = std::min_element(m_memoryPools.begin(), m_memoryPools.end(), [](ParticleMemoryPool *mp0, ParticleMemoryPool *mp1) {
		return mp0->getActiveParticleCount() < mp1->getActiveParticleCount();
	});
	return iter - m_memoryPools.begin();
}

void ParticleManager::init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount)
{
	ParticleMemoryPoolManager::init(particleSystemCount, emitterCount, particleCount, poolCount);
}

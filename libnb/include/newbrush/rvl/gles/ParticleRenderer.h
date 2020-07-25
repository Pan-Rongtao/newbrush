#pragma once
#include "newbrush/rvl/gles/Renderer.h"

namespace nb {

class NB_API ParticleVertexBuffer : public Renderer
{
public:
	ParticleVertexBuffer(uint32_t maxParticleCount, uint32_t poolcount);


private:
	std::vector<float>	*m_ver;
	std::vector<uint16_t>	m_indices;
};


}
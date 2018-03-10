#include "ParticlePositionAffector.h"

void ParticlePositionAffector::affect(irr::u32 now, irr::scene::SParticle *particlearray, irr::u32 count)
{
	_Positions.clear();
	for (unsigned int c = 0; c < count; c++)
	{
		_Positions.push_back(particlearray[c].pos);
	}
}

std::vector<irr::core::vector3df>* ParticlePositionAffector::GetParticlePositions()
{
	return &_Positions;
}

irr::scene::E_PARTICLE_AFFECTOR_TYPE ParticlePositionAffector::getType() const
{
	return irr::scene::E_PARTICLE_AFFECTOR_TYPE::EPAT_ATTRACT;
}
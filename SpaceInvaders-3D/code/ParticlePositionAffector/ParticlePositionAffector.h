#pragma once
#include <irrlicht.h>
#include <vector>
#include <iostream>

class ParticlePositionAffector : public irr::scene::IParticleAffector
{
	public:

		void affect(irr::u32 now, irr::scene::SParticle *particlearray, irr::u32 count) override;

		irr::scene::E_PARTICLE_AFFECTOR_TYPE getType() const override;

		std::vector<irr::core::vector3df>* GetParticlePositions();

	private:
	
		std::vector<irr::core::vector3df> _Positions;
};
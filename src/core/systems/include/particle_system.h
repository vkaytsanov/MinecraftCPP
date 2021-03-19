//
// Created by Viktor on 18.3.2021 г..
//

#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../events/cube_destroyed_event.h"




class ParticleSystem : public entityx::System<ParticleSystem>,
                       public entityx::Receiver<ParticleSystem> {
private:

	void emit();
public:
	ParticleSystem();
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void receive(const CubeDestroyedEvent& event);
};


#endif //PARTICLE_SYSTEM_H

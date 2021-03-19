//
// Created by Viktor on 18.3.2021 г..
//

#include "include/particle_system.h"
#include "../components/include/particle.h"

ParticleSystem::ParticleSystem()  {

}

void ParticleSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {


	entityx::Entity entity = entities.create();


	entity.addComponent<Particle>();
}

void ParticleSystem::receive(const CubeDestroyedEvent& event) {

}

void ParticleSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void ParticleSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void
ParticleSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}





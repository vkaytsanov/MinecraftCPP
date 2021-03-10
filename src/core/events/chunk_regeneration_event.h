//
// Created by Viktor on 7.3.2021 г..
//

#ifndef CHUNK_REGENERATION_EVENT_H
#define CHUNK_REGENERATION_EVENT_H

struct Collision {
	Collision(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}
	Collision() {}

	entityx::Entity left, right;
};

struct ChunkRegenerationEvent : public entityx::Event<ChunkRegenerationEvent>{
public:
	int x;
	int z;
	ChunkRegenerationEvent(int x, int z) : x(x), z(z){}
	ChunkRegenerationEvent() {}
};


#endif //CHUNK_REGENERATION_EVENT_H

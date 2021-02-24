//
// Created by Viktor on 19.2.2021 г..
//

#ifndef CHUNK_TICKET_EVENT_H
#define CHUNK_TICKET_EVENT_H


#include "event.h"
#include "../../../data/include/chunk.h"

class ChunkTicketEvent : public Event {
public:
	Chunk* chunk;
};


#endif //CHUNK_TICKET_EVENT_H

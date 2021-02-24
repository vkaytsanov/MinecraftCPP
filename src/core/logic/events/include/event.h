//
// Created by Viktor on 17.1.2021 г..
//

#ifndef EVENT_H
#define EVENT_H


#include <string>


class Event {
public:
	std::string name;
	Event() = default;
	explicit Event(std::string name);
	virtual ~Event();
};


#endif //EVENT_H

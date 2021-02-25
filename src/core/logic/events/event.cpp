//
// Created by Viktor on 17.1.2021 г..
//

#include "include/event.h"

#include <utility>


Event::Event(std::string name) : name(std::move(name)) {}


Event::~Event() {

}

//
// Created by Viktor on 18.12.2020 г..
//

#include "include/data_system.h"

DataSystem::DataSystem(){
	assets = new Assets();
	cubesDb = new CubesDB(assets);
}



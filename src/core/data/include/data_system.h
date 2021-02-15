//
// Created by Viktor on 18.12.2020 г..
//

#ifndef DATA_SYSTEM_H
#define DATA_SYSTEM_H


#include "assets.h"
#include "cubes_db.h"


class DataSystem {
public:
	Assets* assets;
	CubesDB* cubesDb;
	DataSystem();
};


#endif //DATA_SYSTEM_H

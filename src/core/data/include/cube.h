//
// Created by Viktor on 18.2.2021 г..
//

#ifndef CUBE_H
#define CUBE_H

enum CubeType {
	Grass,
	Dirt,
	Air,
};

enum CubeFaceType{
	Front = 0,
	Back = 1,
	Top = 2,
	Bottom = 3,
	Left = 4,
	Right = 5
};

struct Cube {
	CubeType type = Grass;

	bool isTransparent() const;
};


#endif //CUBE_H

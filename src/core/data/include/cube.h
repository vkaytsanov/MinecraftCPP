//
// Created by Viktor on 18.2.2021 г..
//

#ifndef CUBE_H
#define CUBE_H

enum CubeType {
	Gravel,
	Grass,
	Dirt,
	WoodPlank,
	StoneProcessed,
	Stone,
	Brick,
	TNT,
	Web,
	FlowerBlue,
	FlowerYellow,
	Treelet,
	BrokenStone,
	Bedrock,
	Sand,
	NetherGravel,
	Wood,
	IronProcessed,
	GoldProcessed,
	DiamondProcessed,
	ChestSingle,
	Gold,
	Iron,
	Coal,
	Diamond,

	Water,
	Lava,

	Glass,
	Air,
};

enum CubeFaceType {
	Front = 0,
	Back = 1,
	Top = 2,
	Bottom = 3,
	Left = 4,
	Right = 5
};

struct Cube {
	CubeType type = Air;

	bool isTransparent() const;
	bool isLiquid() const;
	bool isEntity() const;
};


#endif //CUBE_H

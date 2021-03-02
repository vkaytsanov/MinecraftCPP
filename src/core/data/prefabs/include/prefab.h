//
// Created by Viktor on 27.2.2021 г..
//

#ifndef PREFAB_H
#define PREFAB_H

#include <vector>
#include "../../../../lib/utils/geometry/include/vector3.h"
#include "../../terrain/include/cube.h"

enum PrefabType{
	Tree
};

struct PrefabCube{
	Vector3i m_position;
	CubeType m_type;
	PrefabCube(Vector3i& position, CubeType type) : m_position(position), m_type(type){};
	Vector3i unpackPositionAt(int x, int y, int z);
};

class Prefab {
protected:
	std::vector<PrefabCube> structure;
	void setCube(Vector3i position, CubeType type);
	void setCubesHorizontal(Vector3i position, int width, int depth, CubeType type);
public:
	const std::vector<PrefabCube>& getStructure();
};


#endif //PREFAB_H

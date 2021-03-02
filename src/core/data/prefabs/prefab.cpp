//
// Created by Viktor on 27.2.2021 г..
//

#include "include/prefab.h"

const std::vector<PrefabCube>& Prefab::getStructure() {
	return structure;
}

void Prefab::setCube(Vector3i position, CubeType type) {
	structure.emplace_back(PrefabCube(position, type));
}

void Prefab::setCubesHorizontal(Vector3i position, int width, int depth, CubeType type) {
	for (int i = position.x; i < position.x + width; i++){
		for (int j = position.z; j < position.z + depth; j++){
			setCube({i, position.y, j}, type);
		}
	}
}


Vector3i PrefabCube::unpackPositionAt(int x, int y, int z) {
	return m_position + Vector3i(x, y, z);
}

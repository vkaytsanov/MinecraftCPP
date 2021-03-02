//
// Created by Viktor on 27.2.2021 г..
//

#include "include/tree_prefab.h"

TreePrefab::TreePrefab() {
	setCube({0, 5, 0}, Leaves);
	setCubesHorizontal({-1, 4, -1}, 3, 3, Leaves);
	setCubesHorizontal({-2, 3, -2}, 5, 5, Leaves);
	setCube({0, 3, 0}, Wood);
	setCube({0, 2, 0}, Wood);
	setCube({0, 1, 0}, Wood);
	setCube({0, 0, 0}, Wood);
}

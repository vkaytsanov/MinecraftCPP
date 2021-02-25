//
// Created by Viktor on 26.12.2020 г..
//

#include "include/math_utils.h"
#include <cassert>
#include <cmath>

namespace MathUtils {
	float toRadians(float degree) {
		return degree * (PI / 180);
	}
}
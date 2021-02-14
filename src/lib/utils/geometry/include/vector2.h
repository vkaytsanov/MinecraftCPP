//
// Created by Viktor on 9.1.2021 г..
//

#ifndef VECTOR2_H
#define VECTOR2_H

template <typename T>
class Vector2{
public:
    T x;
    T y;

    Vector2() {
        this->x = 0;
        this->y = 0;
    }

    Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }

};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
#endif //VECTOR2_H

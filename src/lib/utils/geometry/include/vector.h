//
// Created by Viktor on 21.12.2020 г..
//

#ifndef DUCKHUNT_VECTOR_H
#define DUCKHUNT_VECTOR_H

template<typename T>
class Vector {
public:
    T x;
    T y;
    Vector() {
        x = 0;
        y = 0;
    }
    Vector(T x, T y) {
        this->x = x;
        this->y = y;
    }
    Vector<T> operator+(const Vector<T>& vec) {
        return Vector<T>(this->x + vec.x, this->y + vec.y);
    }
    Vector<T> operator-(const Vector<T>& vec){
        return Vector<T>(this->x - vec.x, this->y - vec.y);
    }
    Vector<T> operator*(const Vector<T>& vec){
        return Vector<T>(this->x * vec.x, this->y * vec.y);
    }
    Vector<T> operator/(const Vector<T>& vec){
        return Vector<T>(this->x / vec.x, this->y / vec.y);
    }
};


typedef Vector<float> Vector2f;
typedef Vector<int>   Vector2i;


#endif //DUCKHUNT_VECTOR_H

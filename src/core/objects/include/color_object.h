//
// Created by Viktor on 9.1.2021 г..
//

#ifndef COLOR_OBJECT_H
#define COLOR_OBJECT_H


#include "object.h"

class ColorObject : public Object{
private:
    unsigned int colorBuffer;
public:
    explicit ColorObject(const char* objFile);
    ~ColorObject() override;
    void draw() override;

};


#endif //COLOR_OBJECT_H

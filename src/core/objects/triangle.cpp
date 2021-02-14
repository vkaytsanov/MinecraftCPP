////
//// Created by Viktor on 6.1.2021 г..
////
//
//#include "GL/glew.h"
//#include "include/triangle.h"
//
//Triangle::Triangle() : Object(1, 3) {
//    float data[] = {
//            -1.f, -1.0f, -5.0f,
//            1.0f, -1.0f, -5.0f,
//            0.0f,  1.0f, -5.0f,
//    };
//    glGenBuffers(1, &vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
//
//    float colors[] = {
//            1,1,1,
//            1,1,1,
//            1,1,1
//    };
//
//    glGenBuffers(1, &colorBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//}
//
//void Triangle::draw() {
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glVertexAttribPointer(
//            0,
//            3,
//            GL_FLOAT,
//            false,
//            0,
//            nullptr
//    );
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//    glVertexAttribPointer(
//            1,
//            3,
//            GL_FLOAT,
//            false,
//            0,
//            nullptr
//    );
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//}
//
//

//
// Created by Viktor on 9.1.2021 г..
//


#include "include/object_loader.h"

void loadOBJ(const char *path, std::vector <Vector3f> &out_vertices, std::vector <Vector2f> &out_uvs,
             std::vector <Vector3f> &out_normals) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Vector3f> temp_vertices;
    std::vector<Vector2f> temp_uvs;
    std::vector<Vector3f> temp_normals;

    FILE *file;
    errno_t err = fopen_s(&file, path, "r");
    if (err) {
        Lib::app->error("TextureObject", "Impossible to open the file !");
        exit(-1);
    }

    while (true) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if (strcmp(lineHeader, "v") == 0) {
            Vector3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            Vector2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            Vector3f normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                                 &normalIndex[2]);
            if (matches != 9) {
                Lib::app->error("TextureObject", "File can't be read by the parser");
                exit(-1);
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    fclose(file);

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        Vector3f vertex = temp_vertices[ vertexIndex-1 ];
        Vector2f uv = temp_uvs[ uvIndex-1 ];
        Vector3f normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        out_normals .push_back(normal);

    }
}

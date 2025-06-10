#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>
#include <memory>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh {
public:
    std::vector <Vertex>  vertices;
    std::vector <GLuint>  indices;
    std::vector<std::shared_ptr<Texture>> textures;

    VAO VAO;
    // VBO VBO;
    // EBO EBO;

    // Constructor
    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, const std::vector<std::shared_ptr<Texture>>& textures);

    void Draw(Shader &shader, Camera &camera);

private:

};

#endif
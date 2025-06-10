#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO {

    public: 
        GLuint vboID;
        // New constructor
        VBO(std::vector<Vertex> vertices);

        // Old contructor
        VBO(GLfloat *vertices, GLsizeiptr size);

        VBO();

        void Bind();
        void Unbind();
        void Delete();



};

#endif
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
    public:
        GLuint vaoID;
        VAO();
        
        void LinkVBO(VBO VBO, GLuint layout);

        void LinkVBO(VBO& vbo, GLuint layout, GLuint size, GLuint stride, GLuint offset);

        void Bind();
        void Unbind();
        void Delete();

};


#endif
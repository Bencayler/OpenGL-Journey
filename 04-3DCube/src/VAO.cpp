#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &vaoID);
}



void VAO::LinkVBO(VBO vbo, GLuint layout) {
    this->Bind();
    vbo.Bind();
    glEnableVertexAttribArray(layout);

    glVertexAttribPointer(
        layout,
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(GLfloat), 
        (void*)0
        );
    
    
    vbo.Unbind();
    this->Unbind();
}


void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLuint size, GLuint stride, GLuint offset) {
    this->Bind();
    vbo.Bind();
    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(
        layout,
        size,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(offset)
    );
    
    vbo.Unbind();
    this->Unbind(); 

}

void VAO::Bind() {
    glBindVertexArray(vaoID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &vaoID);
}


#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

// Graphics libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

// Standard libraries
#include <iostream>

// Custom libraries
#include "shaderClass.h"

class textureClass {
    public:
        textureClass(const char* filepath, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
        
        // Assigns a texture unit to a shader uniform
        void textureUnit(Shader& shader, const char* uniform, GLuint unit);

        void Bind();

        void Unbind();

        void Delete();

        ~textureClass();
    
        GLuint getTextureID();


    private:
        GLuint textureID;
        GLenum type;

};

#endif
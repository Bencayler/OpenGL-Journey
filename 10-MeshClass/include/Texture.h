#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

// Graphics libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

// Standard libraries
#include <iostream>

// Custom libraries
#include "Shader.h"

class Texture {
    public:
        // Members
        GLuint textureID;
        const char *type;
        std::string filePath;
        GLuint unit;
        GLenum format;
        GLenum pixelType;
    
        // Constructor
        Texture(const char* filepath, const char *type, GLuint slot, GLenum format, GLenum pixelType);
        //////////////////////////////
        //   BIG 5 DECLARATIONS     //
        //////////////////////////////

        // Destructor
        ~Texture();

        // Copy constructor (deep copy)
        Texture(const Texture &other);

        // Copy assignment Operator (deep copy)
        Texture& operator=(const Texture &other);
        
        // Move Constructor
        Texture(Texture&& other) noexcept;

        // Move assignment operator
        Texture& operator=(Texture&& other) noexcept;


        // Assigns a texture unit to a shader uniform
        void textureUnit(Shader& shader, const char* uniform, GLuint unit);

        void Bind();

        void Unbind();

        void Delete();


    
        GLuint getTextureID();
        
        



    private:

};

#endif
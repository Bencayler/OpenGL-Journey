#include "textureClass.h"
#include <stb/stb_image.h>



// Constructor to load texture from file
textureClass::textureClass(const char* filePath, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType) {
    
    // set the type of texture
    this->type = textureType;
    
    // Declare the width, height, and number of channels
    int imageWidth, imageHeight, nrChannels;

    // Import the texture using stb_image - dimensions are passed by reference so any changes are reflected in the variables
    unsigned char* imageData = stbi_load(filePath, &imageWidth, &imageHeight, &nrChannels, 0);
    
    if (imageData == nullptr) {
		std::cerr << "Failed to load texture" << std::endl;
	}

    // Debugging output to check how the image was loaded
    std::cout << "Image loaded with dimensions: " << imageWidth << "x" << imageHeight << " and channels: " << nrChannels << std::endl;


    
    glGenTextures(1, &textureID); // Generate a texture ID with our member variable
    glActiveTexture(slot); // Activate the texture unit
    glBindTexture(type, textureID); // Bind the texture

    // Configures the texture parameters / algorithms to make the image fit the texture mapping
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configure texture repeat, border, or edge behavior
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // Upload the texture data to the GPU
    glTexImage2D(textureType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, imageData);

    // Generate mipmaps for the texture
    glGenerateMipmap(textureType);

    stbi_image_free(imageData); // Free the image data after uploading to the GPU

    // Unbind the texture
    glBindTexture(textureType, 0);
}

// Destructor for textureClass
textureClass::~textureClass() {
    glDeleteTextures(1, &textureID);
}

void textureClass::textureUnit(Shader &shader, const char* uniform, GLuint unit) {
    GLuint textureUnit = glGetUniformLocation(shader.getProgramID(), uniform);

    shader.Activate();

    glUniform1i(textureUnit, unit); // Set the texture unit to the shader uniform
}

void textureClass::Bind() {
    glBindTexture(this->type, textureID);
}

void textureClass::Unbind() {
    glBindTexture(type, 0);
}

void textureClass::Delete() {
    glDeleteTextures(1, &textureID);
}


GLuint textureClass::getTextureID() {
    return textureID;
}
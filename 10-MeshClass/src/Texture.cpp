#include "Texture.h"
#include <stb/stb_image.h>



// Constructor to load texture from file
Texture::Texture(const char* filePath, const char *textureType, GLuint slot, GLenum format, GLenum pixelType) :
    type(textureType),
    format(format),
    pixelType(pixelType),
    filePath(filePath)
{
    
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
    glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture unit
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    // Configures the texture parameters / algorithms to make the image fit the texture mapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Smoother minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);             // Smoother magnification

    // Configure texture repeat behavior for seamless tiling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    // Upload the texture data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, imageData);

    // Generate mipmaps for the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData); // Free the image data after uploading to the GPU

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Destructor for Texture
Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

// Copy constructor (deep copy)
Texture::Texture(const Texture &other) :   
    type(other.type),
    unit(other.unit),
    filePath(other.filePath),
    textureID(other.textureID)
{
    // Reload image
    int width, height, nrChannels;
    
    unsigned char *imageData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if(imageData == nullptr) {
        std::cerr << "Failed to copy texture from " << filePath << std::endl;
        return;
    }

    // Set up buffers and bind the textures
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
}

// Copy assignment Operator (deep copy)
Texture& Texture::operator=(const Texture& other) {
    if (this == &other) return *this;

    glDeleteTextures(1, &textureID);

    type      = other.type;
    unit      = other.unit;
    filePath  = other.filePath;
    format    = other.format;
    pixelType = other.pixelType;

    int width, height, nrChannels;
    unsigned char *imageData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if(imageData == nullptr) {
        std::cerr << "Failed to copy texture from " << filePath << std::endl;
        return *this;
    }

    // Setup the texture
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Setup parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
    return *this;
}

// Move Constructor
Texture::Texture(Texture&& other) noexcept :
    type(std::move(other.type)),
    unit(other.unit),
    filePath(std::move(other.filePath)),
    textureID(other.textureID),
    format(other.format),
    pixelType(other.pixelType)

{
    other.textureID = 0;
}


// Move assignment operator
Texture& Texture::operator=(Texture&& other) noexcept {
    if (this == &other) return *this;

    glDeleteTextures(1, &textureID);

    type      = std::move(other.type);
    unit      = other.unit;
    filePath  = std::move(other.filePath);
    format    = other.format;
    pixelType = other.pixelType;
    textureID = other.textureID;

    other.textureID = 0;
    return *this;
}



void Texture::textureUnit(Shader &shader, const char* uniform, GLuint unit) {
    GLuint textureUnit = glGetUniformLocation(shader.getProgramID(), uniform);

    shader.Activate();

    glUniform1i(textureUnit, unit); // Set the texture unit to the shader uniform
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &textureID);
}


GLuint Texture::getTextureID() {
    return textureID;
}
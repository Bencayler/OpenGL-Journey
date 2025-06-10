#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, const std::vector<std::shared_ptr<Texture>>& textures) :
    vertices(vertices),
    indices(indices),
    textures(textures)
    // // VBO(vertices),
    // // EBO(indices)


{


    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, sizeof(Vertex), 0);                   // Position attribute
	VAO.LinkAttrib(VBO, 1, 3, sizeof(Vertex), 3 * sizeof(GLfloat)); // Normal Attributes
	VAO.LinkAttrib(VBO, 2, 3, sizeof(Vertex), 6 * sizeof(GLfloat)); // Color Attributes
	VAO.LinkAttrib(VBO, 3, 2, sizeof(Vertex), 9 * sizeof(GLfloat)); // Texture attribute


    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

}

void Mesh::Draw(Shader &shader, Camera &camera) {
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;
    
    for(unsigned int i = 0; i < textures.size(); i++) {
        std::string num;
        std::string type = textures[i]->type;
        if (type == "diffuse") {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular") {
            num = std::to_string(numSpecular++);
        }
        std::string uniformName = type + num;
  
        textures[i]->textureUnit(shader, (type + num).c_str(), i);
        textures[i]->Bind();

        std::cout << "Binding " << uniformName << " to texture unit " << i << std::endl;
        GLint loc = glGetUniformLocation(shader.getProgramID(), uniformName.c_str());
        if (loc == -1) {
            std::cerr << "Warning: Uniform " << uniformName << " not found in shader!" << std::endl;
        }
    }




    // Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.getProgramID(), "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
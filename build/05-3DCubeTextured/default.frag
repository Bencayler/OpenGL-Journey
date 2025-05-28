#version 330 core

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D textureSampler;


void main() {
	FragColor = texture(textureSampler, textureCoords);
}
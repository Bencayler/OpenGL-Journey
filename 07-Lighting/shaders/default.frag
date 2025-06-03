#version 330 core

out vec4 FragColor;

in vec2 textureCoords;

// Color from the light source
uniform vec4 lightColor;

uniform sampler2D textureSampler;


void main() {
	vec4 textureColor = texture(textureSampler, textureCoords);
	FragColor = textureColor * lightColor;
}
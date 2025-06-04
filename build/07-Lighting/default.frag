#version 330 core

// Inputs
in vec2 textureCoords;
in vec3 FragPos;     // Correct name to match vertex shader output
in vec3 Normal;

// Outputs
out vec4 FragColor;

// Uniforms
// Textured
uniform sampler2D textureSampler;
// Color from the light source
uniform vec4 lightColor;
// light position
uniform vec3 lightPos;
// Camera position
uniform vec3 camPos;




void main() {
	// === Ambient Lighting === 
	float ambientStrength = 0.1;
	vec3 ambient          = ambientStrength * vec3(lightColor);

	// === Diffuse Lighting ===
	vec3 norm     = normalize(Normal); // Ensure normal is normalized
    vec3 lightDir = normalize(lightPos - FragPos); // Direction from fragment to light
	float diff    = max(dot(norm, lightDir), 0.0); // Dot product gives intensity. Clamp to 0.0 
    vec3 diffuse  = diff * vec3(lightColor); // Diffuse light color

	// === Specular Lighting ===
	float specularStrength = 0.5f; // How shiny the object is
	vec3 viewDir           = normalize(camPos - FragPos);
	vec3 reflectDir        = reflect(-lightDir, norm);
	float spec             = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular          = specularStrength * spec * vec3(lightColor);

	// Combine the results with addition
	vec3 result = ambient + diffuse + specular;

	FragColor = texture(textureSampler, textureCoords) * vec4(result, 1.0);
}
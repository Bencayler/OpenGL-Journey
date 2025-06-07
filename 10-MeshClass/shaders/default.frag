#version 330 core

// Inputs
in vec2 textureCoords;
in vec3 FragPos;     // Correct name to match vertex shader output
in vec3 Normal;

// Outputs
out vec4 FragColor;

// Uniforms
// Get the texture unit from the main function
uniform sampler2D tex0;
// Spec map of the texture
uniform sampler2D tex1;

// Color from the light source
uniform vec4 lightColor;
// light position
uniform vec3 lightPos;
// Camera position
uniform vec3 camPos;

vec4 pointLight() {
	// Get the light vector
	vec3 lightVector = lightPos - FragPos;

	// Calculate the intensity of light via a inverse quadratic
	float distance = length(lightVector); // Get the magnitude of the vector
	float a = 0.1;
	float b = 0.5;
	float intensity = 1.0f / (a * (distance * distance) + b * distance + 1.0f);

	// === Ambient Lighting === 
	float ambientStrength = 0.30f;

	// === Diffuse Lighting === 
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// === Specular Lighting ===
	float specularStrength = 0.850f;
	vec3 viewDirection = normalize(camPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularStrength;
	
	// Return the vec4
	return (texture(tex0, textureCoords) * (diffuse * intensity + ambientStrength) + texture(tex1, textureCoords).r * specular * intensity) * lightColor;

}

// Todo - Implement directional light
vec4 directionalLight() {
	// === Ambient Lighting === 
	float ambientStrength = 0.20f;

	// === Diffuse Lighting === 
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// === Specular Lighting ===
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, textureCoords) * (diffuse + ambientStrength ) + texture(tex1, textureCoords).r * specular) * lightColor;
}

vec4 spotLight() {
	
	// Establish the outer and inner cones
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// === Ambient Lighting === 
	float ambientStrength = 0.30f;

	// === Diffuse Lighting === 
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - FragPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// === Specular Lighting ===
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// Calculate the intensity of the frag pstions based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Return the vec4
	return (texture(tex0, textureCoords) * (diffuse * intensity + ambientStrength) + texture(tex1, textureCoords).r * specular * intensity) * lightColor;

	
}

void main() {
	// FragColor = spotLight();
	FragColor = directionalLight();
	// FragColor = pointLight();
}
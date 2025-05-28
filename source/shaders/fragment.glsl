#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

out vec4 FragColor;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 cameraPos;

uniform Material material;

in vec3 Normal;

void main() {
	// Diffuse light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = diff * lightColor * material.diffuse;

	// Specular light 
	float specularStrengh = 0.5;
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularStrengh * spec * lightColor;

	vec3 result = (diffuse + material.ambient + specular) * objectColor;

	FragColor = vec4(result, 1.0);
}
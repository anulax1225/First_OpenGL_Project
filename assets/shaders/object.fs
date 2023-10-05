#version 330 core
//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float mixVal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec2 textCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {
    //FragColor = mix(texture(texture1, textCoord), texture(texture2, textCoord), mixVal);
    
    //Lighting of the frangment

    //Ambient
    vec3 ambient = light.ambient * material.ambient;

    //Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
    vec3 specular = light.specular * (spec * material.specular);

    FragColor = vec4(vec3(ambient + diffuse + specular), 0.0);
}

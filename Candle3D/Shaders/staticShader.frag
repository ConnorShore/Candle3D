#version 330 core

#define NUM_POINT_LIGHTS 4

struct AmbientLight
{
    float strength;
};

struct PointLight
{
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};
// struct SpotLight 
// {
//     vec3 position;
//     vec3 direction;
//     vec3 color;

//     float cutoff;
// };

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 color;

uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform float specularValue;
uniform float ambient;

uniform PointLight pointLights[NUM_POINT_LIGHTS];
//uniform SpotLight spotLight;

//Prototypes
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{  
    vec3 norm = normalize(fragmentNormal);
    vec3 viewDir = normalize(viewPos - fragmentPosition);

    vec3 result = vec3(0.0);

    //Directional light

    //Point lights
    for(int i = 0; i < NUM_POINT_LIGHTS; i++) {
        result += calcPointLight(pointLights[i], norm, fragmentPosition, viewDir);
    }
    //Spot light

    //final calculation
    color = vec4(result.xyz, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    //specular
    vec3 reflectiveDir = reflect(-lightDir, normal);
    float specFactor = pow(max(dot(viewDir, reflectiveDir), 0.0), 32);
    vec3 specular = specularValue * specFactor * light.color;

    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance
        + light.quadratic * (distance * distance));
    
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 diffuseTotal  = max(diffuse, ambient);

    return (diffuseTotal + specular) * texture(texture_diffuse1, fragmentUV);
}
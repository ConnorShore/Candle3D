#version 330 core

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentUV;

in vec3 toCamVector;

out vec4 color;

uniform sampler2D texture_diffuse1;

uniform float ambientStrength;
uniform float specularValue;

uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{   
    //ambient
    vec3 ambient = ambientStrength * lightColor;

    //diffuse
    vec3 norm = normalize(fragmentNormal);
    vec3 lightDir = normalize(lightPosition - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular
    vec3 viewDir = normalize(toCamVector - fragmentPosition);
    vec3 reflectiveDir = reflect(-lightDir, norm);
    float specFactor = pow(max(dot(viewDir, reflectiveDir), 0.0), 32);
    vec3 specular = specularValue * specFactor * lightColor;

    //final calculation
    vec4 result = vec4((ambient + diffuse + specular), 1.0) 
        * vec4(texture(texture_diffuse1, fragmentUV));

    color = vec4(result.xyz, 1.0);
}
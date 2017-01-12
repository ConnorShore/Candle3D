#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentUV;

out vec3 toCamVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(vertexPosition, 1.0);
    gl_Position = projection * view * worldPos;

    fragmentPosition = worldPos.xyz;
    fragmentNormal = vertexNormal;
    fragmentUV = vertexUV;

    toCamVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz * worldPos.xyz;
}
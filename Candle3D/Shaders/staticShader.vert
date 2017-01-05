#version 330 core

layout (location=0) in vec3 position;
layout (location=2) in vec2 vertexUV;

out vec2 fragUV;

uniform mat4 model, view, projection;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}

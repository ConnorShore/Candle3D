#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 vertexColor;
layout (location=2) in vec2 vertexUV;

out vec3 fragColor;
out vec2 fragUV;

void main()
{
  gl_Position = vec4(position.x, position.y, position.z, 1.0);
  fragColor = vertexColor;
  fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}

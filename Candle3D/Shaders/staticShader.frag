#version 330 core

in vec2 fragUV;

out vec4 color;

uniform sampler2D mySample;

void main()
{
  color = texture(mySample, fragUV);
}

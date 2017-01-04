#version 330 core

in vec3 fragColor;
in vec2 fragUV;

out vec4 color;

uniform sampler2D mySample;

void main()
{
  color = texture(mySample, fragUV) * vec4(fragColor, 1.0);
}

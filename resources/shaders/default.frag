#version 330 core

uniform sampler2D tex0;

out vec4 FragColor;

in vec2 texCoord;
in vec4 vertexColor;

void main()
{
   FragColor = texture(tex0, texCoord);
}
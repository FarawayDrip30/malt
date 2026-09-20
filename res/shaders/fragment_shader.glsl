#version 330 core
in vec4 vertexColour;
in vec2 texCoord;

out vec4 FragColour;

uniform sampler2D texture1;

void main()
{
   FragColour = texture(texture1, texCoord) * vertexColour;
}
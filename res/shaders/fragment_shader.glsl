#version 330 core
in vec4 vertexColour;
in vec2 texCoord;

out vec4 FragColour;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   FragColour = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * vertexColour;
}
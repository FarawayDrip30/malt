#version 330 core
in vec4 vertexColour;
in vec2 texCoord;

out vec4 FragColour;

uniform sampler2D ourTexture;

void main()
{
   FragColour = texture(ourTexture, texCoord) * vec4(texCoord, 0.0, 1.0);
}
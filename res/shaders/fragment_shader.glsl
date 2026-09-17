#version 330 core
in vec4 vertexColour;

out vec4 FragColour;

void main()
{
   FragColour = vertexColour;
}
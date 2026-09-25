#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model_matrix;
uniform mat4 view_matrix;

out vec4 vertexColour;
out vec2 texCoord;

void main()
{
   gl_Position = view_matrix * model_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexColour = vec4(aColour, 1.0f);
   texCoord = aTexCoord;
}
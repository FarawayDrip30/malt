#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model_matrix;
uniform mat4 view_matrix;

out vec2 texCoord;

void main()
{
   gl_Position = view_matrix * model_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   texCoord = aTexCoord;
}
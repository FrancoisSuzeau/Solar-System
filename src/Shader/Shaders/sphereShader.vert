// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// ============ Out data ============
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));

    FragPos = vec3(model * vec4(in_Vertex, 1.0));
    Normal = mat3(transpose(inverse(model))) * in_Vertex;
}
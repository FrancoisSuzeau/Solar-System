// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
uniform mat4 light_view;
uniform mat4 light_proj;
uniform mat4 model;

// ============ Out data ============

void main()
{
    gl_Position = light_proj * light_view * (model * vec4(in_Vertex, 1.0) );
}  
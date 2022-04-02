// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
// uniform mat4 light_space_matrix;
uniform mat4 model;

// ============ Out data ============

void main()
{
    // gl_Position = light_space_matrix * (model * vec4(in_Vertex, 1.0) );
    gl_Position = model * vec4(in_Vertex, 1.0);
}  
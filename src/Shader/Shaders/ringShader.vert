// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
in vec2 in_TexCoord0;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 light_space_matrix;

// ============ Out data ============
out VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 coordTexture;
} vs_out;


void main()
{
    vs_out.FragPos = vec3(model * vec4(in_Vertex, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));
    vs_out.Normal = normalMatrice * in_Vertex;
    vs_out.coordTexture = in_TexCoord0;
    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));
}

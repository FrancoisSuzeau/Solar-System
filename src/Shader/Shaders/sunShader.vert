#version 330 core

attribute vec3 in_Vertex;
varying vec4 texCoords;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 Normal;
out vec3 FragPos;

uniform bool inverse_normals;


void main(void) {
    mat4 mp = projection * view * model;
    gl_Position = mp * vec4(in_Vertex, 1.0);
    texCoords = vec4(in_Vertex, 1.0);

    FragPos = vec3(model * vec4(in_Vertex, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));

    vec3 n = inverse_normals ? - in_Vertex : in_Vertex;
    Normal = normalize(normalMatrice * n);
    // Normal = mat3(transpose(inverse(model))) * in_Vertex;
}
#version 400 core

in vec3 in_Vertex;
// varying vec4 texCoords;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 Normal;
out vec4 texCoords;
out vec3 FragPos;

uniform bool inverse_normals;


void main(void) {

    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));
    texCoords = vec4(in_Vertex, 1.0);

    FragPos = vec3(model * vec4(in_Vertex, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));

    vec3 n = inverse_normals ? - in_Vertex : in_Vertex;
    Normal = normalize(normalMatrice * n);
}
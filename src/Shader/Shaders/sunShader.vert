// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
// uniform bool inverse_normals;

// ============ Out data ============
out vec4 texCoords;
// out vec3 FragPos;
// out vec3 Normal;

void main(void) {

    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));
    texCoords = vec4(in_Vertex, 1.0);

    // FragPos = vec3(model * vec4(in_Vertex, 1.0));

    // mat3 normalMatrice = mat3(transpose(inverse(model)));
    // vec3 n = inverse_normals ? - in_Vertex : in_Vertex;
    // Normal = normalize(normalMatrice * n);
}
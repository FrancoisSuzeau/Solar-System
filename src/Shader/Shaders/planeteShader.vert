// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
// uniform mat4 light_space_matrix;
// uniform vec3 viewPos;
// uniform vec3 sunPos;

// ============ Out data ============
out VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec4 texCoords;
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
} vs_out;

// out vec4 texCoords;
// out vec3 FragPos;
// out vec3 Normal;
// out VS_OUT {
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
// } vs_out;


void main(void) {

    vs_out.FragPos = vec3(model * vec4(in_Vertex, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(model)));
    vs_out.Normal = normalMatrice * in_Vertex;  
    vs_out.texCoords = vec4(in_Vertex, 1.0);
    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));

    // vec3 lightPos = sunPos;

    // vec3 v = vec3(Normal.x + 1, Normal.y, Normal.z);
    // vec3 k = Normal * v;
    // vec3 Tangent = v - k * Normal;

    // vec3 T = normalize(normalMatrice * Tangent);
    // vec3 N = normalize(normalMatrice * in_Vertex);
    // T = normalize(T - dot(T, N) * N);
    // vec3 B = cross(N, T);
    
    // mat3 TBN = transpose(mat3(T, B, N));    
    // vs_out.TangentLightPos = TBN * lightPos;
    // vs_out.TangentViewPos  = TBN * viewPos;
    // vs_out.TangentFragPos  = TBN * FragPos;
    
}
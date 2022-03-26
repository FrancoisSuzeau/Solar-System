// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec3 in_Vertex;
in vec2 in_TexCoord0;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
// uniform vec3 viewPos;
// uniform vec3 sunPos;

// ============ Out data ============
out vec2 coordTexture;
// out vec3 Normal;
// out vec3 FragPos;
// out VS_OUT {

//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
// } vs_out;


void main()
{
    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));

    coordTexture = in_TexCoord0;

    // FragPos = vec3(model * vec4(in_Vertex, 1.0));
    // mat3 normalMatrice = mat3(transpose(inverse(model)));
    // Normal = normalize(normalMatrice * in_Vertex);

    // // vec3 lightPos = vec3(0.1, 0.0, 0.0);
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

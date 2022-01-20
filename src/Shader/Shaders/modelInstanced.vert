#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoords;
out vec3 Normal;

out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;

uniform vec3 viewPos;
uniform vec3 sunPos;
out VS_OUT {

    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f); 

    // Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));

    mat3 normalMatrice = mat3(transpose(inverse(aInstanceMatrix)));
    Normal = normalize(normalMatrice * aNormal);

    // vec3 lightPos = vec3(0.1, 0.0, 0.0);
    vec3 lightPos = sunPos;

    vec3 v = vec3(Normal.x + 1, Normal.y, Normal.z);
    vec3 k = Normal * v;
    vec3 Tangent = v - k * Normal;

    vec3 T = normalize(normalMatrice * Tangent);
    vec3 N = normalize(normalMatrice * aPos);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * FragPos;
}
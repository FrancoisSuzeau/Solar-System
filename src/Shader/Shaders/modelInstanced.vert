// ============ GLSL version ============
#version 400 core

// ============ In data ============
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 viewPos;
uniform vec3 sunPos;

// ============ Out data ============
out VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

void main()
{
    vs_out.TexCoords = aTexCoords;
    gl_Position = projection * view * (aInstanceMatrix * vec4(aPos, 1.0f)); 
    vs_out.FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
    mat3 normalMatrice = mat3(transpose(inverse(aInstanceMatrix)));
    vs_out.Normal = normalize(normalMatrice * aNormal);

    vec3 lightPos = sunPos;

    vec3 v = vec3(vs_out.Normal.x + 1, vs_out.Normal.y, vs_out.Normal.z);
    vec3 k = vs_out.Normal * v;
    vec3 Tangent = v - k * vs_out.Normal;

    vec3 T = normalize(normalMatrice * Tangent);
    vec3 N = normalize(normalMatrice * aPos);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}
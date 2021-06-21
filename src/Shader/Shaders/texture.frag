// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;
in vec3 Normal;
in vec3 FragPos;


// Uniform

uniform sampler2D texture;


// Fonction main

void main()
{
    // Couleur du pixel
    vec4 alpha_color = texture2D(texture, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }
    
    //gl_FragColor = texture(texture, coordTexture);

    vec3 lightColor = {1.0, 1.0, 1.0};

    //diffuse light
    vec3 lightPos = {1.0f, 0.0f, 0.0f};
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lightColor;
    vec4 objectColor = texture(texture, coordTexture);
    vec3 result = (ambiant + diffuse) * vec3(objectColor.x, objectColor.y, objectColor.z);
    
    gl_FragColor = vec4(result, 1.0);
    
}

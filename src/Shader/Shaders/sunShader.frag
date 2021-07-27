#version 330 core
varying vec4 texCoords;

uniform sampler2D texture0;

in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;

struct Light {
    vec3 Position;
    vec3 Color;
};

uniform Light lights[16];

out vec4 FragColor;

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application

    // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    vec3 lightColor = {1.0, 1.0, 1.0};
    vec3 lightPos = {0.1f, 0.0f, 0.0f};

    vec3 objectColor = texture(texture0, longitudeLatitude).rgb;

    // *********************************************** ambiant light ***************************************************
    //float ambiantStrength = 0.1;
    //vec3 ambiant = ambiantStrength * objectColor;

    // *********************************************** calculate HDR ***************************************************
    //vec3 lighting = vec3(0.0);
    //vec3 result =  diffuse;
    //for(int i = 0; i < 16; i++)
    //{
        //vec3 norm = normalize(Normal);
        //vec3 lightDir = normalize(lights[i].Position - FragPos);
        //float diff = max(dot(norm, lightDir), 0.0);
        //vec3 diffuse = diff * lights[i].Color * objectColor;
        
        //vec3 result =  diffuse;

        //float distLight = length(FragPos - lights[i].Position);
        //result *= 5.0 / (distLight * distLight);
        //lighting += result;

    //}
    
    // *********************************************** only bind texture unit to fragment coordinate ***************************************************
    //FragColor = texture(texture0, longitudeLatitude);
    FragColor = vec4(objectColor, 1.0);

    //FragColor = vec4(ambiant + lighting, 1.0);


    
    // *********************************************** or a white ball ***************************************************
    //gl_FragColor = vec4(1.0);
    
        
}
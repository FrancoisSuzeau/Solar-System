#version 330 core
varying vec4 texCoords;
uniform sampler2D texture0;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;

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
    
    // *********************************************** mitigation ***************************************************
    float lightConst = 1.0f;
    float lightLin = 0.35f;
    float lightQuad = 0.44f;
    //float distance = length(lightPos - FragPos);
    //float mitigation = 1.0 / (lightConst + lightLin * distance + lightQuad * (distance * distance));

    // *********************************************** diffuse light ***************************************************
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor * objectColor;

    // *********************************************** specular light ***************************************************
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    //vec3 specular = specularStrength * spec * lightColor;

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.01;
    vec3 ambiant = ambiantStrength * objectColor;

    // *********************************************** calculate diffuse + attenuation for hdr ***************************************************
    vec3 lighting = vec3(0.0);
    for(int i = 0; i < 16; i++)
    {
        vec3 norm = normalize(Normal);

        // diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].Color * diff * objectColor;      
        vec3 result = diffuse;

        // attenuation (use quadratic as we have gamma correction)
        float distance = length(FragPos - lights[i].Position);
        result *= 1.0 / (lightConst + lightLin * distance + lightQuad * (distance * distance));
        lighting += result;
                
    }

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    //vec3 objectColor = texture(texture0, longitudeLatitude).rgb;
    //vec3 result = ( ambiant + diffuse) * vec3(objectColor.x, objectColor.y, objectColor.z);

    //ambiant *= mitigation;
    //diffuse *= mitigation;
    //specular *= mitigation;

    FragColor = vec4(ambiant + lighting, 1.0);
    
    
        
}
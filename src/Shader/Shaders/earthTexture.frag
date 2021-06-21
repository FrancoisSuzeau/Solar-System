#version 150 core
varying vec4 texCoords;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float oppacity;
in vec3 Normal;
in vec3 FragPos;

void main(void) {
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application
        
    //gl_FragColor = mix(texture(texture0, longitudeLatitude), texture(texture1, longitudeLatitude), oppacity);
    
        // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    vec3 lightColor = {1.0, 1.0, 1.0};

    //diffuse light
    vec3 lightPos = {-1.0f, 0.0f, 0.0f};
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lightColor;
    vec4 objectColor = mix(texture(texture0, longitudeLatitude), texture(texture1, longitudeLatitude), oppacity);
    vec3 result = (ambiant + diffuse) * vec3(objectColor.x, objectColor.y, objectColor.z);
    
    gl_FragColor = vec4(result, 1.0);
}
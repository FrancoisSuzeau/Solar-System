// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec4 texCoords;
uniform sampler2D texture0;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application

    // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    vec3 lightColor = vec3(3.0, 3.0, 3.0);

    vec3 objectColor = texture(texture0, longitudeLatitude).rgb;
    objectColor *= lightColor;

    FragColor = vec4(objectColor, 1.0);

    // *********************************************** for bloom effect ***************************************************
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.0)
    {   
        BrightColor = FragColor;
    }  
	else
    {
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
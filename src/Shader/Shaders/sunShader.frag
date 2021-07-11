#version 330 core
varying vec4 texCoords;

uniform sampler2D texture0;

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application

    // *********************************************** bind texture unit to fragment coordinate with blur effect ***************************************************
    //gl_FragColor = vec4(result, 1.0);

    // *********************************************** only bind texture unit to fragment coordinate ***************************************************
    gl_FragColor = texture(texture0, longitudeLatitude);

    // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"
    

    // *********************************************** or a white ball ***************************************************
    //gl_FragColor = vec4(1.0);
    
        
}
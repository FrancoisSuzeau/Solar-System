#version 400 core

in vec4 texCoords;

uniform sampler2D texture0;

uniform bool displayText;

in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform vec3 sunPos;

layout (location = 0) out vec4 FragColor;
// layout (location = 1) out vec4 BrightColor;

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application

    // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    vec3 lightColor = vec3(5.0, 5.0, 5.0);
    vec3 lightPos = sunPos;

    vec3 objectColor = texture(texture0, longitudeLatitude).rgb;
    // vec3 objectColor = vec3(1.0);

    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor * objectColor;
   
    // if(displayText)
    // {
    //     FragColor = vec4(diffuse, 1.0);
    //     if(FragColor.r > 0.05f)
    //     {
    //         FragColor.r *= 1.5f;
    //     }
    // }
    // else
    // {
    //     FragColor = vec4((lightColor * diff), 1.0);
    // }

    FragColor = vec4(objectColor, 1.0);

    

    // *********************************************** for bloom effect ***************************************************
    // float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 0.8f)
    // {   
    //     BrightColor = FragColor;
    // }  
	// else
    // {
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    // }
		
}
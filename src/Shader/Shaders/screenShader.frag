#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 textureScreen = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(textureScreen, 1.0);
}
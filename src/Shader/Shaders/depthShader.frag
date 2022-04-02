// ============ GLSL version ============
#version 400 core

// ============ In data ============
uniform vec3 sunPos;
uniform float far_plane;
in vec4 FragPos;

// ============ Out data ============


void main()
{
    float lightDistance = length(FragPos.xyz - sunPos);

    lightDistance /= far_plane;

    gl_FragDepth = lightDistance;
}
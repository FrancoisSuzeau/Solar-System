#version 120

//input vertex data, different for all execution of this shader
attribute vec3 in_Vertex;

//output data : will be interpolated for each element
varying vec2 UV;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 light_src;

uniform vec3 viewPos;

void main()
{
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
}
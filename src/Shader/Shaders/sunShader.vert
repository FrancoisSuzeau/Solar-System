#version 150 core

attribute vec3 in_Vertex;
varying vec4 texCoords;
uniform mat4 modelview;
uniform mat4 projection;


void main(void) {
    mat4 mp = projection * modelview;
    gl_Position = mp * vec4(in_Vertex, 1.0);
    texCoords = vec4(in_Vertex, 1.0);
}
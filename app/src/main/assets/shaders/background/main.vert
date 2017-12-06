#version 300 es

in vec3 vertexPosition;
in vec2 vertexTextureCord;
out vec2 textureCord;

void main()
{
    textureCord = vertexTextureCord;
    gl_Position = vec4(vertexPosition, 1.0);
}
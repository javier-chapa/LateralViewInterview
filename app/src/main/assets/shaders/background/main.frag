#version 300 es
precision mediump float;

uniform sampler2D diffuseMap;
in vec2 textureCord;
out vec4 fragmentColor;

void main()
{
   fragmentColor = texture(diffuseMap, textureCord);
}
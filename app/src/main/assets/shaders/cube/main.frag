#version 300 es
precision mediump float;

uniform sampler2D fbo;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

in vec3 worldSpaceVertex;
in vec2 textureCord;
in vec3 transformedNormal;
in vec3 transformedBinormal;
in vec3 transformedTangent;

in vec3 inverseLightDirection;
in vec3 inverseEyeDirection;

out vec4 fragmentColor;

void main()
{
    vec3 textureColor = texture(fbo, textureCord).xyz;
    vec3 normal = transformedNormal;
    vec3 specularColor = vec3(1, 1, 1);

    if (textureColor == vec3(1,0,0)){
        textureColor =  texture(diffuseMap, textureCord).xyz;
        normal =  texture(normalMap, textureCord).xyz;
        normal = normalize(normal * 2.0 -1.0);
        specularColor = texture(specularMap, textureCord).xyz;
    }

    vec3 L = normalize(vec3(0.0, 1.0, 1.0));
    vec3 E = normalize(vec3(0.0, 0.0, 1.0) - worldSpaceVertex);
    vec3 R = normalize(reflect(-L,normal));

    vec3 ambient = vec3(0.5, 0.5, 0.5) * textureColor;

    vec3 Idiff = vec3(0, 0.5, 1) * max(0.0, dot(normal,L)) * textureColor;
    Idiff = clamp(Idiff, 0.0, 1.0);

    vec3 Ispec = vec3(0, 0.5, 1) * pow(max(dot(R,E),0.0),20.0) * specularColor;
    Ispec = clamp(Ispec, 0.0, 1.0);

    fragmentColor = vec4(Idiff + ambient + Ispec, 1.0);
}
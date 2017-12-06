#version 300 es

uniform mat4 projection;
uniform mat4 modelView;

in vec3 vertexPosition;
in vec2 vertexTextureCord;
in vec3 vertexNormal;
in vec3 vertexTangent;
in vec3 vertexBinormal;

out vec3 worldSpaceVertex;
out vec2 textureCord;
out vec3 transformedNormal;
out vec3 transformedTangent;
out vec3 transformedBinormal;

out vec3 inverseLightDirection;
out vec3 inverseEyeDirection;

void main()
{
    transformedNormal = normalize((modelView *  vec4(vertexNormal, 0.0)).xyz);
    //transformedTangent = normalize((modelView * vec4(vertexTangent, 0.0)).xyz);
    //transformedBinormal = normalize((modelView * vec4(vertexBiNormal, 0.0)).xyz);

    //mat3 tangentMatrix = mat3(transformedTangent, transformedBinormal, transformedNormal);

    worldSpaceVertex = (modelView * vec4(vertexPosition, 1.0)).xyz;
    inverseLightDirection = normalize(vec3(1.0, 1.0, 1.0));
    inverseEyeDirection = normalize((vec3(0.0, 0.0, 1.0)- worldSpaceVertex ).xyz);
    //inverseLightDirection =inverseLightDirection * tangentMatrix;
    //inverseEyeDirection = inverseEyeDirection * tangentMatrix;

    textureCord = vertexTextureCord;

    gl_Position = projection * modelView * vec4(vertexPosition, 1.0);
}
#version 300 es

uniform mat4 projection;
uniform mat4 modelView;

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 binormal;
in vec2 texCoord;

out vec3 worldSpaceVertex;
out vec2 textureCord;
out vec3 transformedNormal;
out vec3 transformedBinormal;
out vec3 transformedTangent;

out vec3 inverseLightDirection;
out vec3 inverseEyeDirection;

void main()
{
    worldSpaceVertex = (modelView * vec4(position, 1.0)).xyz;
    transformedNormal = normalize((modelView *  vec4(normal, 0.0)).xyz);
    transformedTangent = normalize((modelView * vec4(tangent, 0.0)).xyz);
    transformedBinormal = normalize((modelView * vec4(binormal, 0.0)).xyz);

    mat3 tangentMatrix = transpose(mat3(transformedTangent, transformedBinormal, transformedNormal));

    inverseLightDirection = normalize(vec3(1.0, 1.0, 1.0));
    inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0) - worldSpaceVertex);
    inverseLightDirection = inverseLightDirection * tangentMatrix;
    inverseEyeDirection = inverseEyeDirection * tangentMatrix;

    textureCord = texCoord;

    gl_Position = projection * modelView * vec4(position, 1.0);
}
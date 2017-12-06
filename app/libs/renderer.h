#include <GLES3/gl3.h>
#include <Utilities/shader.h>
#include <Graphics/graphics.h>
#include <vector>

class Renderer {
private:

    struct VectorType {
        float x, y, z;
    };

    struct CoordinateType {
        float u, v;
    };

    struct VerticeType{
        VectorType position, normal, tangent, binormal;
        CoordinateType textureCoordinates;

    };

    Shader *cubeShader, *sphereShader, *backgroundShader;
    vector <VerticeType> sphereVertices;
    vector<float> cubePositions, cubeTexCoords, cubeNormals, cubeTangents, cubeBinormals;
    vector<unsigned short> cubeIndices, sphereIndices;
    GLuint fboTexture, frameBuffer, crateDiffuseMap, crateNormalMap, crateSpecularMap, earthDiffuseMap, earthNormalMap, earthSpecularMap, sphereVAO, sphereVBO[2], spaceDiffuseMap;

    vector<string> split(const string &, char);
    void ComputeCube();
    void ComputeSphere();
    void ComputeBackground();

    static float angle;

    const GLfloat backgroundVertices[12] = {
            -1.0f, -1.0f,
            1.0f,  1.0f,
            -1.0f,  1.0f,

            -1.0f, -1.0f,
            1.0f, -1.0f,
            1.0f,  1.0f,
    };

    const GLfloat backgroundTextureCoords[12] = {
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
    };

    void DrawBackground();
    void DrawSphere();
    void DrawCube();

public:
    void Init ();
    void Resize (int, int);
    void Draw ();
};



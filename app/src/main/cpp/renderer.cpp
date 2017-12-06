#include <renderer.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3platform.h>
#include <Graphics/graphics.h>
#include <Utilities/shader.h>
#include <Utilities/utilities.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

float Renderer::angle = 0;

vector<string> Renderer::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void Renderer::ComputeSphere() {
    sphereShader = new Shader("shaders/sphere/main.vert", "shaders/sphere/main.frag");

    earthDiffuseMap = loadPNG("textures/earthDiffuseMap.png", 2048, 1024, false, false, false, GL_RGBA, GL_RGBA);
    earthNormalMap = loadPNG("textures/earthNormalMap.png", 2048, 1024, false, false, false, GL_RGBA, GL_RGBA);
    earthSpecularMap = loadPNG("textures/earthSpecularMap.png", 2048, 1024, false, false, false, GL_RGBA, GL_RGBA);

    unsigned int slices = 7;
    unsigned int stacks = 7;
    float ratio = 1.0;
    float inicio = 0;
    float final = 1.0;
    
    for (unsigned int i = 0; i < slices; i++)
    {
        for (unsigned int j = 0; j < stacks; j++)
        {
            unsigned int indice = i * stacks + j;

            VerticeType vertice;

            vertice.position.x = ratio*cos(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*cos(2.0*M_PI*(float)i / (slices - 1));
            vertice.position.y = ratio*sin(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0);
            vertice.position.z = ratio*cos(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)*sin(2.0*M_PI*(float)i / (slices - 1));

            vertice.normal.x = cos(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)* cos(2.0*M_PI*(float)i / (slices - 1));
            vertice.normal.y = sin(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0);
            vertice.normal.z = cos(((float)j / (stacks - 1))*(M_PI*(final - inicio)) + M_PI*inicio - M_PI / 2.0)* sin(2.0*M_PI*(float)i / (slices - 1));

            vertice.tangent.x = 0;
            vertice.tangent.y = 0;
            vertice.tangent.z = 0;

            vertice.binormal.x = 0;
            vertice.binormal.y = 0;
            vertice.binormal.z = 0;

            vertice.textureCoordinates.u = (1 - (double)i / (stacks - 1));
            vertice.textureCoordinates.v = (1 - (double)j / (slices - 1));

            sphereVertices.push_back(vertice);
        }
    }

    int index = 0, index1 = 0, index2 = 0, index3 = 0, index4 = 0;

    for (int i = 0; i < slices - 1; i++)
    {
        for (int j = 0; j < stacks - 1; j++)
        {
            index1 = (stacks *   i) + j;    // Bottom left.
            index2 = (stacks *   i) + (j + 1);  // Bottom right.
            index3 = (stacks * (i + 1)) + j;    // Upper left.
            index4 = (stacks * (i + 1)) + (j + 1);  // Upper right.

            sphereIndices.push_back(index1);
            sphereIndices.push_back(index2);
            sphereIndices.push_back(index4);

            sphereIndices.push_back(index1);
            sphereIndices.push_back(index4);
            sphereIndices.push_back(index3);
        }
    }

    glGenBuffers(2, sphereVBO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * 14 * sizeof (GLfloat), sphereVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof (GLushort), sphereIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::ComputeCube(){
    cubeShader = new Shader("shaders/cube/main.vert", "shaders/cube/main.frag");

    crateDiffuseMap = loadPNG("textures/crateDiffuseMap.png", 512, 512, false, false, false, GL_RGBA, GL_RGBA);
    crateNormalMap = loadPNG("textures/crateNormalMap.png", 512, 512, false, false, false, GL_RGBA, GL_RGBA);
    crateSpecularMap = loadPNG("textures/crateSpecularMap.png", 512, 512, false, false, false, GL_RGBA, GL_RGBA);

    char *verticesBuffer = readAsset("models/cube/cubeVertices.txt");
    vector<string> stringVerticesVector = split(string(verticesBuffer), ',');
    for (string vertex : stringVerticesVector) {
        cubePositions.push_back(atof(vertex.c_str()));
    }

    char *texCoordsBuffer = readAsset("models/cube/cubeTexCoords.txt");
    vector<string> stringTexCoordsVector = split(string(texCoordsBuffer), ',');
    for (string texCoord : stringTexCoordsVector) {
        cubeTexCoords.push_back(atof(texCoord.c_str()));
    }

    char *normalsBuffer = readAsset("models/cube/cubeNormals.txt");
    vector<string> stringNormalsVector = split(string(normalsBuffer), ',');
    for (string normal : stringNormalsVector) {
        cubeNormals.push_back(atof(normal.c_str()));
    }

    char *binormalsBuffer = readAsset("models/cube/cubeBinormals.txt");
    vector<string> stringBinormalsVector = split(string(binormalsBuffer), ',');
    for (string binormal : stringBinormalsVector) {
        cubeBinormals.push_back(atof(binormal.c_str()));
    }

    char *tangentsBuffer = readAsset("models/cube/cubeTangents.txt");
    vector<string> stringTangentsVector = split(string(tangentsBuffer), ',');
    for (string tangent : stringTangentsVector) {
        cubeTangents.push_back(atof(tangent.c_str()));
    }

    char *indicesBuffer = readAsset("models/cube/cubeIndices.txt");
    vector<string> stringIndicesVector = split(string(indicesBuffer), ',');
    for (string index : stringIndicesVector) {
        cubeIndices.push_back(atoi(index.c_str()));
    }
}

void Renderer::ComputeBackground(){
    backgroundShader = new Shader("shaders/background/main.vert", "shaders/background/main.frag");
    spaceDiffuseMap = loadPNG("textures/spaceDiffuseMap.png", 1080, 2560, false, false, false, GL_RGBA, GL_RGBA);
}


void Renderer::Init () {
    ComputeBackground();
    ComputeCube();
    ComputeSphere();
}

void Renderer::Resize (int width, int height)
{
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);

    height = height == 0 ? 1 : height;
    glViewport(0,0,width,height);
    graphics::matrixMode(PROJECTION);
    graphics::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    graphics::matrixMode(MODELVIEW);
    graphics::lookAt(0, 0, 5, 0, 0, 4, 0, 1, 0);
}

void Renderer::DrawBackground(){
    glDisable(GL_DEPTH_TEST);

    backgroundShader->bind();

    glVertexAttribPointer(glGetAttribLocation(backgroundShader->program, "vertexPosition"), 2, GL_FLOAT, GL_FALSE, 0, backgroundVertices);
    glEnableVertexAttribArray(glGetAttribLocation(backgroundShader->program, "vertexPosition"));

    glVertexAttribPointer(glGetAttribLocation(backgroundShader->program, "vertexTextureCord"), 2,
                          GL_FLOAT, GL_FALSE, 0, backgroundTextureCoords);
    glEnableVertexAttribArray(glGetAttribLocation(backgroundShader->program, "vertexTextureCord"));

    glUniform1i(glGetUniformLocation(backgroundShader->program, "diffuseMap"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, spaceDiffuseMap);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    backgroundShader->unbind();

    glEnable(GL_DEPTH_TEST);
}

void Renderer::DrawSphere(){
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    sphereShader->bind();

    angle += 0.20;
    if (angle > 360) {
        angle -= 360;
    }

    graphics::pushMatrix();
    graphics::rotatef(-angle * 5, 0, 1, 0);


    glUniformMatrix4fv(glGetUniformLocation(sphereShader->program, "projection"), 1, GL_FALSE,  graphics::getProjectionMatrix());
    glUniformMatrix4fv(glGetUniformLocation(sphereShader->program, "modelView"), 1, GL_FALSE, graphics::getModelViewMatrix());

    graphics::popMatrix();

    glUniform1i(glGetUniformLocation(sphereShader->program, "diffuseMap"), 0);
    glUniform1i(glGetUniformLocation(sphereShader->program, "normalMap"), 1);
    glUniform1i(glGetUniformLocation(sphereShader->program, "specularMap"), 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, earthDiffuseMap);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, earthNormalMap);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, earthSpecularMap);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO[0]);

    GLushort strideLength = 14 * sizeof(GLfloat);
    GLushort normalsOffset = 3 * sizeof(GLfloat);
    GLushort coordinatesOffset = 12 * sizeof(GLfloat);

    GLuint vertexPosition = glGetAttribLocation(sphereShader->program, "vertexPosition");
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, strideLength, 0);
    glEnableVertexAttribArray(vertexPosition);

    GLuint vertexNormal = glGetAttribLocation(sphereShader->program, "vertexNormal");
    glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, strideLength, (const void *) normalsOffset);
    glEnableVertexAttribArray(vertexNormal);

    GLuint vertexTextureCord = glGetAttribLocation(sphereShader->program, "vertexTextureCord");
    glVertexAttribPointer(vertexTextureCord, 2, GL_FLOAT, GL_FALSE, strideLength, (const void *) coordinatesOffset);
    glEnableVertexAttribArray(vertexTextureCord);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereVBO[1]);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_SHORT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    sphereShader->unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawCube(){
    cubeShader->bind();

    graphics::pushMatrix();

    graphics::rotatef(angle, 0, 1, 0);

    glUniformMatrix4fv(glGetUniformLocation(cubeShader->program, "projection"), 1, GL_FALSE, graphics::getProjectionMatrix());
    glUniformMatrix4fv(glGetUniformLocation(cubeShader->program, "modelView"), 1, GL_FALSE, graphics::getModelViewMatrix());

    graphics::popMatrix();

    GLuint position = glGetAttribLocation(cubeShader->program, "position");
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, cubePositions.data());
    glEnableVertexAttribArray(position);

    GLuint texCoord = glGetAttribLocation(cubeShader->program, "texCoord");
    glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 0, cubeTexCoords.data());
    glEnableVertexAttribArray(texCoord);

    GLuint normal = glGetAttribLocation(cubeShader->program, "normal");
    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, cubeNormals.data());
    glEnableVertexAttribArray(normal);

    GLuint binormal = 3;//glGetAttribLocation(cubeShader->program, "binormal");
    glVertexAttribPointer (binormal, 3, GL_FLOAT, GL_FALSE, 0, cubeBinormals.data() );
    glEnableVertexAttribArray (binormal);

    GLuint tangent = 2;//glGetAttribLocation(cubeShader->program, "tangent");
    glVertexAttribPointer (tangent, 3, GL_FLOAT, GL_FALSE, 0, cubeTangents.data() );
    glEnableVertexAttribArray (tangent);

    glUniform1i(glGetUniformLocation(cubeShader->program, "fbo"), 0);
    glUniform1i(glGetUniformLocation(cubeShader->program, "diffuseMap"), 1);
    glUniform1i(glGetUniformLocation(cubeShader->program, "normalMap"), 2);
    glUniform1i(glGetUniformLocation(cubeShader->program, "specularMap"), 3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fboTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, crateDiffuseMap);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, crateNormalMap);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, crateSpecularMap);

    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_SHORT, cubeIndices.data());

    cubeShader->unbind();
}

void Renderer::Draw() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    DrawBackground();
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    DrawSphere();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    DrawCube();
}

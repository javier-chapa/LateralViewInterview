#include <Utilities/utilities.h>
#include <GLES3/gl3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <Utilities/asset.h>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <Utilities/lodepng.h>

#define CHANNELS_PER_PIXEL  3

using namespace std;

GLuint loadPNG(string assetName, unsigned int width, unsigned int height, bool mipmaps, bool linear, bool repeat, int informat, int outformat)
{
    GLuint textureId = 0;

    string filename;
    bool isFilePresent = asset->ExtractAssetReturnFilename(assetName, filename);
    if( !isFilePresent ) {
        return textureId;
    }

    vector<unsigned char> image;
    unsigned int error = lodepng::decode(image, width, height, filename.c_str());
    if(error != 0)
    {
        return textureId;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (linear) ? GL_LINEAR : GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (linear) ? (mipmaps) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR : (mipmaps) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (repeat) ? GL_REPEAT : GL_CLAMP_TO_EDGE );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (repeat) ? GL_REPEAT : GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, informat, width, height, 0, outformat, GL_UNSIGNED_BYTE, image.data());

    return textureId;
}

GLuint gen2DTexture(unsigned char *buffer, unsigned int width, unsigned int height, bool mipmaps, bool linear, bool repeat,  int informat, int outformat)
{
    GLuint id;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &id);

    glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (linear) ? GL_LINEAR : GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (linear) ? (mipmaps) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR : (mipmaps) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (repeat) ? GL_REPEAT : GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (repeat) ? GL_REPEAT : GL_CLAMP_TO_EDGE );

    glTexImage2D(GL_TEXTURE_2D, 0, informat, width, height, 0, outformat, GL_UNSIGNED_BYTE, buffer);
	//(mipmaps) ? gluBuild2DMipmaps(GL_TEXTURE_2D, informat, width, height, outformat, GL_UNSIGNED_BYTE, buffer) : glTexImage2D(GL_TEXTURE_2D, 0, informat, width, height, 0, outformat, GL_UNSIGNED_BYTE, buffer);
	//glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}

GLuint loadTexture(string assetName, unsigned int width, unsigned int height)
{
    GLuint textureId = 0;

    string filename;
    bool isFilePresent = asset->ExtractAssetReturnFilename(assetName, filename);
    if( !isFilePresent ) {
        return textureId;
    }

     GLubyte * theTexture;
     theTexture = (GLubyte *)malloc(sizeof(GLubyte) * width * height * CHANNELS_PER_PIXEL);

     FILE * theFile = fopen(filename.c_str(), "r");

     if(theFile == NULL) {
         return textureId;
     }

     fread(theTexture, width * height * CHANNELS_PER_PIXEL, 1, theFile);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Generate a texture object. */
    glGenTextures(1, &textureId);

    /* Activate a texture. */
    glActiveTexture(GL_TEXTURE0);

    /* Bind the texture object. */
    glBindTexture(GL_TEXTURE_2D, textureId);

     /* Load the texture. */
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, theTexture);
     /* Set the filtering mode. */
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

     free(theTexture);

    return textureId;
}

char *readAsset(string assetName)
{
    char *buffer;

    string filename;
    bool isFilePresent = asset->ExtractAssetReturnFilename(assetName, filename);
    if( !isFilePresent ) {
        return buffer;
    }

    ifstream file(filename.c_str(), ios::in);
    file.seekg (0, ios::end);
    int length = file.tellg();
    file.seekg (0, ios::beg);
    buffer = new char [length];
    file.read(buffer, length);
    length = file.gcount();
    buffer[length] = '\0';
    file.close();

    return buffer;
};
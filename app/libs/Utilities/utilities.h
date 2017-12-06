#pragma once

#include <GLES3/gl3.h>
#include <string>

using namespace std;

GLuint loadTexture(string, unsigned int, unsigned int);
GLuint gen2DTexture(unsigned char *, unsigned int, unsigned int, bool, bool, bool, int, int);
GLuint loadPNG(string, unsigned int, unsigned int, bool, bool, bool, int, int);
char *readAsset(string);
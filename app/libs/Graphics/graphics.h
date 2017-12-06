#pragma once

#include "transform.h"
#include <stack>

enum Mode { PROJECTION, MODELVIEW };

using namespace std;

class graphics : public transform
{
private:
	static stack <mat4> projection_stack, modelview_stack, texture_stack;
	static Mode mode;
	graphics();
	~graphics();

public:
	static void lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	static void perspective(float fovy, float aspect, float zNear, float zFar);
	static void translatef(float x, float y, float z);
	static void rotatef(float degrees, float x, float y, float z);
	static void scalef(float x, float y, float z);
	static void loadIdentity();
	static void matrixMode(Mode mode);
	static void pushMatrix();
	static void popMatrix();

    static float* getProjectionMatrix();
    static float* getModelViewMatrix();
    static float* getTextureMatrix();
};

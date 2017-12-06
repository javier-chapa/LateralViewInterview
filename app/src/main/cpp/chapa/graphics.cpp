#include <Graphics/graphics.h>
#include <stack>

#include "Graphics/transform.h"
#include "Graphics/mat4.h"

using namespace std;

stack<mat4> graphics::projection_stack, graphics::modelview_stack, graphics::texture_stack;
Mode graphics::mode;

graphics::graphics() {
}

graphics::~graphics() {
}

void graphics::matrixMode(Mode glmode) {
    mode = glmode;

    if (projection_stack.empty() || modelview_stack.empty() || texture_stack.empty()) {
        projection_stack.push(mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
        modelview_stack.push(mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
        texture_stack.push(mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    }
}

void
graphics::lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz,
                 float upx, float upy, float upz) {
    mat4 matrix = lookAt_transform(vec3(eyex, eyey, eyez), vec3(centerx, centery, centerz),
                                   vec3(upx, upy, upz));
    if (mode == PROJECTION) {
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        modelview_stack.top() = matrix;
    }
}

void graphics::perspective(float fovy, float aspect, float zNear, float zFar) {
    mat4 matrix = perspective_transform(fovy, aspect, zNear, zFar);
    if (mode == PROJECTION) {
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        modelview_stack.top() = matrix;
    }
}

void graphics::loadIdentity() {
    mat4 matrix = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    if (mode == PROJECTION) {
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        modelview_stack.top() = matrix;
    }
}

void graphics::translatef(float x, float y, float z) {
    mat4 matrix;
    if (mode == PROJECTION) {
        matrix = projection_stack.top() * translate_transform(x, y, z);
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        matrix = modelview_stack.top() * translate_transform(x, y, z);
        modelview_stack.top() = matrix;
    }
}

void graphics::scalef(float x, float y, float z) {
    mat4 matrix;
    if (mode == PROJECTION) {
        matrix = projection_stack.top() * scale_transform(x, y, z);
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        matrix = modelview_stack.top() * scale_transform(x, y, z);
        modelview_stack.top() = matrix;
    }
}

void graphics::rotatef(float degrees, float x, float y, float z) {
    mat4 matrix;
    if (mode == PROJECTION) {
        matrix = projection_stack.top() * rotate_transform(degrees, vec3(x, y, z));
        projection_stack.top() = matrix;
    } else if (mode == MODELVIEW) {
        matrix = modelview_stack.top() * rotate_transform(degrees, vec3(x, y, z));
        modelview_stack.top() = matrix;
    }
}

void graphics::pushMatrix() {
    if (mode == PROJECTION) {
        projection_stack.push(projection_stack.top());
    } else if (mode == MODELVIEW) {
        modelview_stack.push(modelview_stack.top());
    }
}

void graphics::popMatrix() {
    mat4 matrix;
    if (mode == PROJECTION) {
        projection_stack.pop();
        matrix = projection_stack.top();
    } else if (mode == MODELVIEW) {
        modelview_stack.pop();
        matrix = modelview_stack.top();
    }
}

float *graphics::getProjectionMatrix() {
    return &(projection_stack.top()[0][0]);
}

float *graphics::getModelViewMatrix() {
    return &(modelview_stack.top()[0][0]);
}
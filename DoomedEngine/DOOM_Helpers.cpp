#include "DOOM.h"


const GLfloat* Mat4ToConstGLFloatPtr(mat4 matrix) {
 return (const GLfloat*)&(matrix[0]);
}
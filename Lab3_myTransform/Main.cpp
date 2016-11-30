#include<gl\glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MODELVIEW 0
#define PROJECTION 1

struct VERTEX {
	float x, y, z, w;
}typedef Vertex;

struct MATRIX {
	Vertex vertices[4];
	struct MATRIX* next = NULL;
}typedef Matrix;


Vertex* MultiplyVertex(Vertex* leftVertex, Matrix* rightMatrix);
void printMatrix(Matrix* matrix);
void printMatrixAll(Matrix* root);
void clearMatrixAll(Matrix* root);

void mySetMatrixMode(int MatrixMode);
void myLoadIdentity();
void myPushMatrix(Matrix* matrix);
void myPopMatrix();
void myMatrixMul(Matrix* matrix);
void myRunMatrix(Vertex* vertex);

void myTranslateX(float d); void myTranslateY(float d); void myTranslateZ(float d);

void myRotateX(float r); void myRotateY(float r); void myRotateZ(float r);

void myScaleX(float s); void myScaleY(float s); void myScaleZ(float s);

int gCurrentMatrixMode = -1;
Matrix* gCurrentMatrix = NULL;
Matrix* gModelViewPtr = NULL;
Matrix* gProjectionPtr = NULL;

void main(int argc, char** argv) {

	mySetMatrixMode(MODELVIEW);
	myLoadIdentity();
	printMatrix(gCurrentMatrix);
	Matrix* matrix1 = (Matrix*)malloc(sizeof(Matrix));
	matrix1->next = NULL;
	matrix1->vertices[0] = { 1.0f, 1.0f, 1.0f, 0.0f };
	matrix1->vertices[1] = { 1.0f, 1.0f, 0.0f, 0.0f };
	matrix1->vertices[2] = { 1.0f, 0.0f, 0.0f, 0.0f };
	matrix1->vertices[3] = { 0.0f, 0.0f, 0.0f, 0.0f };
	myPushMatrix(matrix1);
	printMatrixAll(gCurrentMatrix);
	clearMatrixAll(gModelViewPtr);
	clearMatrixAll(gProjectionPtr);
	return;
}

void printMatrix(Matrix* matrix) {
	for(int i=0; i<4; ++i)
		printf("%.2f %.2f %.2f %.2f\n", matrix->vertices[i].x, matrix->vertices[i].y, matrix->vertices[i].z, matrix->vertices[i].w);
}

void printMatrixAll(Matrix* root) {
	Matrix* currentMatrix = gCurrentMatrix;
	while (NULL != currentMatrix) {
		printMatrix(currentMatrix);
		currentMatrix = currentMatrix->next;
	}
}

void clearMatrixAll(Matrix* root) {
	if (NULL == root)
		return;
	clearMatrixAll(root->next);
	free(root);
}

Vertex* MultiplyVertex(Vertex* leftVertex, Matrix* rightMatrix) {
	
	Vertex* resultVertex = (Vertex*)malloc(sizeof(Vertex));
	resultVertex->x = 0.0f;
	resultVertex->x += leftVertex->x*rightMatrix->vertices[0].x;
	resultVertex->x += leftVertex->y*rightMatrix->vertices[1].x;
	resultVertex->x += leftVertex->z*rightMatrix->vertices[2].x;
	resultVertex->x += leftVertex->w*rightMatrix->vertices[3].x;

	resultVertex->y = 0.0f;
	resultVertex->y += leftVertex->x*rightMatrix->vertices[0].y;
	resultVertex->y += leftVertex->y*rightMatrix->vertices[1].y;
	resultVertex->y += leftVertex->z*rightMatrix->vertices[2].y;
	resultVertex->y += leftVertex->w*rightMatrix->vertices[3].y;

	resultVertex->z = 0.0f;
	resultVertex->z += leftVertex->x*rightMatrix->vertices[0].z;
	resultVertex->z += leftVertex->y*rightMatrix->vertices[1].z;
	resultVertex->z += leftVertex->z*rightMatrix->vertices[2].z;
	resultVertex->z += leftVertex->w*rightMatrix->vertices[3].z;

	resultVertex->w = 0.0f;
	resultVertex->w += leftVertex->x*rightMatrix->vertices[0].w;
	resultVertex->w += leftVertex->y*rightMatrix->vertices[1].w;
	resultVertex->w += leftVertex->z*rightMatrix->vertices[2].w;
	resultVertex->w += leftVertex->w*rightMatrix->vertices[3].w;

	return resultVertex;
}

// Set matrix mode : ModelView or Projection Mode;
void mySetMatrixMode(int MatrixMode) {
	gCurrentMatrixMode = MatrixMode;

	switch (gCurrentMatrixMode) {
	case MODELVIEW:
		gCurrentMatrix = gModelViewPtr;
		break;

	case PROJECTION:
		gCurrentMatrix = gProjectionPtr;
		break;
	}
}

//load identity matrix to current matrix stack
void myLoadIdentity() {
	if (NULL != gCurrentMatrix)
		free(gCurrentMatrix);
	Matrix* identityMatrix = (Matrix*)malloc(sizeof(Matrix));
	identityMatrix->vertices[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	identityMatrix->vertices[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
	identityMatrix->vertices[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	identityMatrix->vertices[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	gCurrentMatrix = identityMatrix;
}

//push into current matrix stack
void myPushMatrix(Matrix* matrix) {
	if (NULL == gCurrentMatrix)
		return;
	gCurrentMatrix->next = matrix;
}

//pop from current matrix stack
void myPopMatrix() {
	if (NULL == gCurrentMatrix)
		return;
	Matrix* nextMatrix = gCurrentMatrix->next;
	free(gCurrentMatrix);
	gCurrentMatrix = nextMatrix;
}

//multiply a matrix m with current stack top & replace top with the result
void myMatrixMul(Matrix* matrix) {
	if (NULL == gCurrentMatrix)
		return;
	for (int i = 0; i < 4; ++i) {
		Vertex* resultVertex = MultiplyVertex(&gCurrentMatrix->vertices[i], matrix);
		memcpy(&gCurrentMatrix->vertices[i], resultVertex, sizeof(Vertex));
		free(resultVertex);
	}
}

//multiply a Vertex v with current stackt op
void myRunMatrix(Vertex* vertex) {

}

void myTranslateX(float d) {

}

void myTranslateY(float d) {

}

void myTranslateZ(float d) {

}


void myRotateX(float r) {

}

void myRotateY(float r) {

}

void myRotateZ(float r) {

}

void myScaleX(float s) {

}

void myScaleY(float s) {

}

void myScaleZ(float s) {

}
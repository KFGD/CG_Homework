#pragma once
#include "GApplication.h"

CGApplication app;

void display() {
	app.renderScene();
}

void idleFunc() {
	app.idleFunc();
}

void keyboardInput(unsigned char key, int x, int y) {
	app.keyboardInput(key, x, y);
}

void reshape(int w, int h) {
	float ratio = w / (float)h;	//ȭ�� ����

	glViewport(0, 0, w, h);		//Viewport(����ü)�� ȭ�� ������ ����
	glMatrixMode(GL_PROJECTION);	// ����� �������� ����
	glLoadIdentity();	//��ȯ ����� �׵� ��ķ� �ʱ�ȭ
	gluPerspective(45, ratio, 10, 100);	//���� ����� ���� �������� ����
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT ���� ���� �ʱ�ȭ
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	//���� ���۸� ���� â | RGBA����� â
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(640, 480);	//â �ʺ� �� ����
	glutCreateWindow("test");	//test��� �̸��� â ����

	app.InitLight();

	glutDisplayFunc(display);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardInput);
	glutMainLoop();
	return 0;
}
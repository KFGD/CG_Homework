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
	float ratio = w / (float)h;	//화면 비율

	glViewport(0, 0, w, h);		//Viewport(절두체)를 화면 비율에 맞춤
	glMatrixMode(GL_PROJECTION);	// 대상을 투영으로 지정
	glLoadIdentity();	//변환 행렬을 항등 행렬로 초기화
	gluPerspective(45, ratio, 10, 100);	//투영 방식을 원근 투영으로 설정
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태 변수 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//단일 버퍼를 가진 창 | RGBA모드의 창
	glutInitWindowSize(640, 480);	//창 너비 및 높이
	glutCreateWindow("test");	//test라는 이름의 창 생성

	glutDisplayFunc(display);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardInput);
	glutMainLoop();
	return 0;
}
#include<gl\glut.h>

GLdouble radius = 0.5;	//glutWireSphere의 radius값으로 이용
GLint slices = 10;	//glutWireSphere의 slices 값으로 이용
GLint stacks = 10;	//glutWireSphere의 stacks 값으로 이용

void display() {
	
	const GLfloat rotateValue = 45.0f;	//rotate할 크기 값

	/*
		gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
		위 코드를 reshape쪽으로 이동하였습니다.
	*/

	glMatrixMode(GL_MODELVIEW);	//작업 대상을 모델 뷰 행렬로 한정

	//첫번째 파란색 구
	glLoadIdentity();	//변환 행렬을 항등 행렬로 초기화
	glTranslatef(0.0f, 0.0f, 0.0f);	//ViewMatrix Stack에 Translate Matrix Push
	glScalef(1.0f, 1.0f, 1.0f);	//ViewMatrix Stack에 Scale Matrix push
	glColor3f(0.0f, 0.0f, 1.0f);	//그리려는 사물의 색을 파란색으로 지정
	glutWireSphere(radius, slices, stacks);	//구 그리기

	//두번째 빨간색 구
	glLoadIdentity();	//변환 행렬을 항등 핼렬로 초기화
	glRotatef(-rotateValue, 0.0f, 0.0f, 1.0f);	//ViewMatrix Stack에 Rotate Matrix Push
	glScalef(1.0f, 1.0f, 1.0f);	//ViewMatrix Stack에 Scale MAtrix Push
	glTranslatef(0.0f, 10.0f, 0.0f);		//ViewMatrix Stack에 Translate Matrix Push
	glRotatef(rotateValue, 0.0f, 0.0f, 1.0f);	//ViewMatrix Stack에 Rotate Matrix Push
	glColor3f(1.0f, 0.0f, 0.0f);	//그리려는 사물의 색을 빨간색으로 지정
	glutWireSphere(radius, slices, stacks);	//구 그리기

	glFlush();	//버퍼 비우기
}

void reshape(int w, int h) {
	float ratio = w / (float)h;	//화면 비율

	glViewport(0, 0, w, h);		//Viewport(절두체)를 화면 비율에 맞춤
	glMatrixMode(GL_PROJECTION);	//작업 대상을 투영으로 지정
	glLoadIdentity();	//변환 행렬을 항등 행렬로 초기화
	gluPerspective(45, ratio, 10, 100);	//투영 방식을 원근 투영으로 설정
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);	//Camera 시점 변환, display함수에서 이동
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태 변수 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//단일 버퍼를 가진 창 | RGBA모드의 창
	glutInitWindowSize(640, 480);	//창 너비 및 높이
	glutCreateWindow("test");	//test라는 이름의 창 생성

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

}
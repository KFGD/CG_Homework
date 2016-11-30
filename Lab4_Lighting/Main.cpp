#include<gl\glut.h>
#include<iostream>
#include<Windows.h>

//Planet B
//planet B의 위치
const GLfloat planet_position[] = {8.0f, -5.0f, 0.0f };
const GLdouble radius = 1;	//glutSolidSphere의 radius값으로 이용
const GLint slices = 100;	//glutSolidSphere의 slices 값으로 이용
const GLint stacks = 100;	//glutSolidSphere의 stacks 값으로 이용

//Lighting
//조명 위치 및 planet A의 위치
const GLfloat light_position[] = { 0.0F, 0.0f, 0.0f, 1.0f };
const GLfloat light_ambient[] = { 0.5f, 0.4f, 0.3f, 1.0f };	//주변광
const GLfloat light_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.0f };	//반사광
const GLfloat light_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };//경면광

//Material_A
const GLfloat material1_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };

//Material_B
const GLfloat material2_ambient[] = { 0.1f, 0.1f, 0.5f, 1.0f };
const GLfloat material2_diffuse[] = { 0.5f, 0.4f, 0.8f, 1.0f };
const GLfloat material2_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat material2_shininess[] = { 15.0f };

void display() {
	glClearColor(0, 0, 0, 0);
	//DepthBuffer활성화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);	//작업 대상을 모델 뷰 행렬로 한정

	//Planet A
	glPushMatrix();
		//ViewMatrix Stack에 Translate Matrix Push
		glTranslatef(light_position[0], light_position[1], light_position[2]);
		//ViewMatrix Stack에 Scale Matrix push
		glScalef(1.0f, 1.0f, 1.0f);
		//물체면 특성 정의
		glMaterialfv(GL_FRONT, GL_AMBIENT, material1_ambient);
		glutSolidSphere(radius, slices, stacks);//Planet A 그리기
	glPopMatrix();

	//Planet B
	glPushMatrix();
		//ViewMatrix Stack에 Translate Matrix Push
		glTranslatef(planet_position[0], planet_position[1], planet_position[2]);
		//ViewMatrix Stack에 Scale Matrix push
		glScalef(1.0f, 1.0f, 1.0f);
		//물체면 특성 정의
		glMaterialfv(GL_FRONT, GL_AMBIENT, material2_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material2_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material2_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, material2_shininess);
		glutSolidSphere(radius, slices, stacks);//Planet B 그리기
	glPopMatrix();
	
	glFlush();

}

void reshape(int w, int h) {
	float ratio = w / (float)h;	//화면 비율

	glViewport(0, 0, w, h);		//Viewport(절두체)를 화면 비율에 맞춤
	glMatrixMode(GL_PROJECTION);	// 대상을 투영으로 지정
	glLoadIdentity();	//변환 행렬을 항등 행렬로 초기화
	gluPerspective(45, ratio, 10, 100);	//투영 방식을 원근 투영으로 설정
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);	//Camera 시점 변환, display함수에서 이동
}


//void arrowInput(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_LEFT:
//		planet_position[0] -= 1.0f;
//		break;
//	case GLUT_KEY_RIGHT:
//		planet_position[0] += 1.0f;
//		break;
//	case GLUT_KEY_UP:
//		planet_position[1] += 1.0f;
//		break;
//	case GLUT_KEY_DOWN:
//		planet_position[1] -= 1.0f;
//		break;
//	}
//	std::cout << "planet의 위치 x: " << planet_position[0] << ", y: " 
//		<< planet_position[1] << ", z: " << planet_position[2] << std::endl;
//	glutPostRedisplay();
//}

void main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태 변수 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//단일 버퍼를 가진 창 | RGBA모드의 창
	glutInitWindowSize(640, 480);	//창 너비 및 높이
	glutCreateWindow("test");	//test라는 이름의 창 생성
	
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_LIGHTING);	//Lighting 기능 On
	// LIGHT0 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  //주변광 성분 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  //반사광 성분 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//경면광 성분 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);// 광원 위치 설정
	glEnable(GL_LIGHT0);	//Light0 활성화

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}



//glutSpecialFunc(arrowInput);

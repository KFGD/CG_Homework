#include<gl\glut.h>
#include<iostream>
#include<Windows.h>

//Planet B
//planet B�� ��ġ
const GLfloat planet_position[] = {8.0f, -5.0f, 0.0f };
const GLdouble radius = 1;	//glutSolidSphere�� radius������ �̿�
const GLint slices = 100;	//glutSolidSphere�� slices ������ �̿�
const GLint stacks = 100;	//glutSolidSphere�� stacks ������ �̿�

//Lighting
//���� ��ġ �� planet A�� ��ġ
const GLfloat light_position[] = { 0.0F, 0.0f, 0.0f, 1.0f };
const GLfloat light_ambient[] = { 0.5f, 0.4f, 0.3f, 1.0f };	//�ֺ���
const GLfloat light_diffuse[] = { 0.5f, 0.4f, 0.3f, 1.0f };	//�ݻ籤
const GLfloat light_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��鱤

//Material_A
const GLfloat material1_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };

//Material_B
const GLfloat material2_ambient[] = { 0.1f, 0.1f, 0.5f, 1.0f };
const GLfloat material2_diffuse[] = { 0.5f, 0.4f, 0.8f, 1.0f };
const GLfloat material2_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat material2_shininess[] = { 15.0f };

void display() {
	glClearColor(0, 0, 0, 0);
	//DepthBufferȰ��ȭ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);	//�۾� ����� �� �� ��ķ� ����

	//Planet A
	glPushMatrix();
		//ViewMatrix Stack�� Translate Matrix Push
		glTranslatef(light_position[0], light_position[1], light_position[2]);
		//ViewMatrix Stack�� Scale Matrix push
		glScalef(1.0f, 1.0f, 1.0f);
		//��ü�� Ư�� ����
		glMaterialfv(GL_FRONT, GL_AMBIENT, material1_ambient);
		glutSolidSphere(radius, slices, stacks);//Planet A �׸���
	glPopMatrix();

	//Planet B
	glPushMatrix();
		//ViewMatrix Stack�� Translate Matrix Push
		glTranslatef(planet_position[0], planet_position[1], planet_position[2]);
		//ViewMatrix Stack�� Scale Matrix push
		glScalef(1.0f, 1.0f, 1.0f);
		//��ü�� Ư�� ����
		glMaterialfv(GL_FRONT, GL_AMBIENT, material2_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material2_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material2_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, material2_shininess);
		glutSolidSphere(radius, slices, stacks);//Planet B �׸���
	glPopMatrix();
	
	glFlush();

}

void reshape(int w, int h) {
	float ratio = w / (float)h;	//ȭ�� ����

	glViewport(0, 0, w, h);		//Viewport(����ü)�� ȭ�� ������ ����
	glMatrixMode(GL_PROJECTION);	// ����� �������� ����
	glLoadIdentity();	//��ȯ ����� �׵� ��ķ� �ʱ�ȭ
	gluPerspective(45, ratio, 10, 100);	//���� ����� ���� �������� ����
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);	//Camera ���� ��ȯ, display�Լ����� �̵�
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
//	std::cout << "planet�� ��ġ x: " << planet_position[0] << ", y: " 
//		<< planet_position[1] << ", z: " << planet_position[2] << std::endl;
//	glutPostRedisplay();
//}

void main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT ���� ���� �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//���� ���۸� ���� â | RGBA����� â
	glutInitWindowSize(640, 480);	//â �ʺ� �� ����
	glutCreateWindow("test");	//test��� �̸��� â ����
	
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_LIGHTING);	//Lighting ��� On
	// LIGHT0 ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  //�ֺ��� ���� ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  //�ݻ籤 ���� ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//��鱤 ���� ����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);// ���� ��ġ ����
	glEnable(GL_LIGHT0);	//Light0 Ȱ��ȭ

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}



//glutSpecialFunc(arrowInput);

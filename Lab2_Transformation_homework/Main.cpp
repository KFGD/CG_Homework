#include<gl\glut.h>

GLdouble radius = 0.5;	//glutWireSphere�� radius������ �̿�
GLint slices = 10;	//glutWireSphere�� slices ������ �̿�
GLint stacks = 10;	//glutWireSphere�� stacks ������ �̿�

void display() {
	
	const GLfloat rotateValue = 45.0f;	//rotate�� ũ�� ��

	/*
		gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
		�� �ڵ带 reshape������ �̵��Ͽ����ϴ�.
	*/

	glMatrixMode(GL_MODELVIEW);	//�۾� ����� �� �� ��ķ� ����

	//ù��° �Ķ��� ��
	glLoadIdentity();	//��ȯ ����� �׵� ��ķ� �ʱ�ȭ
	glTranslatef(0.0f, 0.0f, 0.0f);	//ViewMatrix Stack�� Translate Matrix Push
	glScalef(1.0f, 1.0f, 1.0f);	//ViewMatrix Stack�� Scale Matrix push
	glColor3f(0.0f, 0.0f, 1.0f);	//�׸����� �繰�� ���� �Ķ������� ����
	glutWireSphere(radius, slices, stacks);	//�� �׸���

	//�ι�° ������ ��
	glLoadIdentity();	//��ȯ ����� �׵� �۷ķ� �ʱ�ȭ
	glRotatef(-rotateValue, 0.0f, 0.0f, 1.0f);	//ViewMatrix Stack�� Rotate Matrix Push
	glScalef(1.0f, 1.0f, 1.0f);	//ViewMatrix Stack�� Scale MAtrix Push
	glTranslatef(0.0f, 10.0f, 0.0f);		//ViewMatrix Stack�� Translate Matrix Push
	glRotatef(rotateValue, 0.0f, 0.0f, 1.0f);	//ViewMatrix Stack�� Rotate Matrix Push
	glColor3f(1.0f, 0.0f, 0.0f);	//�׸����� �繰�� ���� ���������� ����
	glutWireSphere(radius, slices, stacks);	//�� �׸���

	glFlush();	//���� ����
}

void reshape(int w, int h) {
	float ratio = w / (float)h;	//ȭ�� ����

	glViewport(0, 0, w, h);		//Viewport(����ü)�� ȭ�� ������ ����
	glMatrixMode(GL_PROJECTION);	//�۾� ����� �������� ����
	glLoadIdentity();	//��ȯ ����� �׵� ��ķ� �ʱ�ȭ
	gluPerspective(45, ratio, 10, 100);	//���� ����� ���� �������� ����
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);	//Camera ���� ��ȯ, display�Լ����� �̵�
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT ���� ���� �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//���� ���۸� ���� â | RGBA����� â
	glutInitWindowSize(640, 480);	//â �ʺ� �� ����
	glutCreateWindow("test");	//test��� �̸��� â ����

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

}
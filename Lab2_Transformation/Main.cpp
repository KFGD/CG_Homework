#include<gl\glut.h>

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glTranslatef(1, 0, 0);
	glScalef(2, 2, 1);

	glBegin(GL_TRIANGLES);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, -0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
	glEnd();

	glFlush();
	
}

void reshape(int w, int h){
	float ratio = w / (float)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 10, 100);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("test");

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

}
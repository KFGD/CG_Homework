#include "GApplication.h"


void CGApplication::renderScene()
{
	glClearColor(0, 0, 0, 0);
	//DepthBuffer활성화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	InitLight();

	//행성 렌더링
	for (int i = 0; i < COUNT_OF_PLANET; ++i) 
		mPlanets[i].DrawPlanet(radius, slices, stacks);
	//위성 렌더링
	for (int i = 0; i < COUNT_OF_SATELITE; ++i)
		mSatelites[i].DrawSatelite(radius, slices, stacks);
	//고리 렌더링
	mSaturnRing.DrawRing(quard);
	glFlush();
}

void CGApplication::idleFunc()
{
	//행성별 rotate값 변경
	for(int i=0; i<COUNT_OF_PLANET; ++i)
		mPlanets[i].RotatePlanet();
	//위성별 rotate값 변경
	for (int i = 0; i < COUNT_OF_SATELITE; ++i)
		mSatelites[i].RotateSatelite();
	glutPostRedisplay();
}

void CGApplication::keyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	//키보드를 이용한 카메라 이동
	case 'w':cameraZ -= 1.0f;break;
	case 's':cameraZ += 1.0f;break;
	case 'd' :cameraX += 1.0f;break;
	case 'a':cameraX -= 1.0f;break;
	case 'e':cameraY += 1.0f;break;
	case 'q':cameraY -= 1.0f;break;
	default:break;
	}
	printf("X: %f, Y: %f, Z: %f\n", cameraX, cameraY, cameraZ);
}

void CGApplication::InitLight()
{
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);	//Lighting 기능 On

	//Lighting
	const GLfloat light_ambient[4] = { 0.5f, 0.4f, 0.3f, 1.0f };	//주변광
	const GLfloat light_diffuse[4] = { 0.5f, 0.4f, 0.3f, 1.0f };	//반사광
	const GLfloat light_specular[4] = { 0.8f, 0.8f, 0.8f, 1.0f };//경면광

	const GLfloat light0_position[4] = { 0.0F, 0.0f, 0.0f, 1.0f };
	// LIGHT0 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  //주변광 성분 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  //반사광 성분 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//경면광 성분 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);// 광원 위치 설정
	glEnable(GL_LIGHT0);	//Light0 활성화
}

void CGApplication::InitPlanets()
{
	//Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune
	InitSun();
	InitMercury();
	InitVenus();
	InitEarth();
	InitMars();
	InitJupiter();
	InitSaturn();
	InitUranus();
	InitNeptune();
}

void CGApplication::InitSun()
{
	mPlanets[SUN].isDraw = true;
	//Translate
	mPlanets[SUN].sX = 5.0f;
	mPlanets[SUN].sY = 5.0f;
	mPlanets[SUN].sZ = 5.0f;
	
	//Material
	GLfloat sun_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_emission[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	*mPlanets[SUN].material_ambient = *sun_ambient;
	*mPlanets[SUN].material_diffuse = *sun_diffuse;
	*mPlanets[SUN].material_emission = *sun_emission;
}

void CGApplication::InitMercury()
{
	mPlanets[MERCURY].isDraw = true;
	//Translate
	mPlanets[MERCURY].rotateAngle = 0.47f;
	//각 행성별 거리 지정
	mPlanets[MERCURY].pX = 0.8f * AU;

	//Material
	GLfloat mercury_ambient[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
	*mPlanets[MERCURY].material_ambient = *mercury_ambient;
}

void CGApplication::InitVenus()
{
	mPlanets[VENUS].isDraw = true;
	//Translate
	mPlanets[VENUS].rotateAngle = 0.35f;
	//각 행성별 거리 지정
	mPlanets[VENUS].pX = 1.6f * AU;

	//Material
	GLfloat venus_ambient[4] = { 0.4f, 0.3f, 0.3f, 1.0f };
	*mPlanets[VENUS].material_ambient = *venus_ambient;
}

void CGApplication::InitEarth()
{
	mPlanets[EARTH].isDraw = true;

	//Translate
	mPlanets[EARTH].pX = 2.4f * AU;
	mPlanets[EARTH].rotateAngle = 0.29f;

	//Material
	GLfloat earth_ambient[4] = { 0.0f, 0.2f, 1.0f, 1.0f };
	GLfloat earth_diffuse[4] = { 0.0f, 0.2f, 1.0f, 1.0f };
	*mPlanets[EARTH].material_ambient = *earth_ambient;
	*mPlanets[EARTH].material_diffuse = *earth_diffuse;
}

void CGApplication::InitMars()
{
	mPlanets[MARS].isDraw = true;

	//Translate
	mPlanets[MARS].pX = 3.2f * AU;
	mPlanets[MARS].rotateAngle = 0.24f;

	//Material
	GLfloat mars_ambient[4] = { 0.6f, 0.4f, 0.4f, 1.0f };
	GLfloat mars_diffuse[4] = { 0.6f, 0.4f, 0.4f, 1.0f };
	*mPlanets[MARS].material_ambient = *mars_ambient;
	*mPlanets[MARS].material_diffuse = *mars_diffuse;

}

void CGApplication::InitJupiter()
{
	mPlanets[JUPITER].isDraw = true;
	//Translate
	mPlanets[JUPITER].rotateAngle = 0.13f;
	mPlanets[JUPITER].pX = 5.0f * AU;
	mPlanets[JUPITER].sX = 3.0f;
	mPlanets[JUPITER].sY = 3.0f;
	mPlanets[JUPITER].sZ = 3.0f;

	//Material
	GLfloat jupiter_ambient[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat jupiter_diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	*mPlanets[JUPITER].material_ambient = *jupiter_ambient;
	*mPlanets[JUPITER].material_diffuse = *jupiter_diffuse;
}

void CGApplication::InitSaturn()
{
	mPlanets[SATURN].isDraw = true;
	//Translate
	mPlanets[SATURN].rotateAngle = 0.09f;
	mPlanets[SATURN].pX = 6.8f * AU;
	mPlanets[SATURN].sX = 3.0f;
	mPlanets[SATURN].sY = 3.0f;
	mPlanets[SATURN].sZ = 3.0f;
	//자전축 지정
	mPlanets[SATURN].axisAngle = 45.0f;

	//Material
	GLfloat saturn_ambient[4] = { 0.3f, 0.2f, 0.2f, 1.0f };
	GLfloat saturn_diffuse[4] = { 0.3f, 0.2f, 0.2f, 1.0f };
	*mPlanets[SATURN].material_ambient = *saturn_ambient;
	*mPlanets[SATURN].material_diffuse = *saturn_diffuse;
}

void CGApplication::InitUranus()
{
	mPlanets[URANUS].isDraw = true;

	//Translate
	mPlanets[URANUS].rotateAngle = 0.06f;
	mPlanets[URANUS].pX = 8.0f * AU;
	mPlanets[URANUS].sX = 1.8f;
	mPlanets[URANUS].sY = 1.8f;
	mPlanets[URANUS].sZ = 1.8f;

	//Material
	GLfloat uranus_ambient[4] = { 0.1f, 1.0f, 0.3f, 1.0f };
	GLfloat uranus_diffuse[4] = { 0.1f, 1.0f, 0.3f, 1.0f };
	*mPlanets[URANUS].material_ambient = *uranus_ambient;
	*mPlanets[URANUS].material_diffuse = *uranus_diffuse;
}

void CGApplication::InitNeptune()
{
	mPlanets[NEPTUNE].isDraw = true;

	//Translate
	mPlanets[NEPTUNE].rotateAngle = 0.05f;
	mPlanets[NEPTUNE].pX = 9.0f * AU;
	mPlanets[NEPTUNE].sX = 1.8f;
	mPlanets[NEPTUNE].sY = 1.8f;
	mPlanets[NEPTUNE].sZ = 1.8f;

	//Material
	GLfloat neptune_ambient[4] = { 0.1f, 0.1f, 0.8f, 1.0f };
	GLfloat neptune_diffuse[4] = { 0.0f, 0.0f, 0.8f, 1.0f };
	*mPlanets[NEPTUNE].material_ambient = *neptune_ambient;
	*mPlanets[NEPTUNE].material_diffuse = *neptune_diffuse;
}

void CGApplication::InitSatelites()
{
	//Moon
	mSatelites[MOON].isDraw = true;
	mSatelites[MOON].pX = 0.2f * AU;
	mSatelites[MOON].rotateAngle = 1.0f;
	
	//Jupiter Satelites_0
	mSatelites[JUPITER_SATELITE_0].isDraw = true;
	mSatelites[JUPITER_SATELITE_0].pX = 0.3f * AU;
	mSatelites[JUPITER_SATELITE_0].rotateAngle = 1.0f;
	
	//Jupiter Satelites_1
	mSatelites[JUPITER_SATELITE_1].isDraw = true;
	mSatelites[JUPITER_SATELITE_1].pX = 0.5f * AU;
	mSatelites[JUPITER_SATELITE_1].rotateAngle = 0.8f;
}

void CGApplication::setPlanetAmbient(PLANET_TAG planet_tag, GLfloat material_ambient[4])
{
	*mPlanets[planet_tag].material_ambient = *material_ambient;
}

void CGApplication::setPlanetDiffuse(PLANET_TAG planet_tag, GLfloat material_diffuse[4])
{
	*mPlanets[planet_tag].material_diffuse = *material_diffuse;
}

void CGApplication::setPlanetSpecular(PLANET_TAG planet_tag, GLfloat material_specular[4])
{
	*mPlanets[planet_tag].material_specular = *material_specular;
}

void CGApplication::setPlanetEmission(PLANET_TAG planet_tag, GLfloat material_emission[4])
{
	*mPlanets[planet_tag].material_emission = *material_emission;
}

void CGApplication::setPlanetShiness(PLANET_TAG planet_tag, GLfloat material_shiness)
{
	mPlanets[planet_tag].material_shiness = material_shiness;
}


CGApplication::CGApplication()
{
	InitPlanets();
	InitSatelites();

	//고리 생성에 필요한 quadric객체 생성
	quard = gluNewQuadric();
	gluQuadricDrawStyle(quard, GLU_FILL);
	gluQuadricNormals(quard, GLU_SMOOTH);
	gluQuadricOrientation(quard, GLU_OUTSIDE);
	gluQuadricTexture(quard, GL_FALSE);
}


CGApplication::~CGApplication()
{
	gluDeleteQuadric(quard);
}

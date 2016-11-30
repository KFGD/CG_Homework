#pragma once
#include<gl\glut.h>
#include<iostream>
#include<Windows.h>


class CGApplication
{
public:
	struct Planet {
		//Rendering?
		bool isDraw = false;
		
		//Translate
		GLfloat pX, pY, pZ;
		GLfloat currentAngle = 0.0f;
		GLfloat rotateAngle = 0.0f;
		GLfloat axisAngle = 0.0f;
		GLfloat sX, sY, sZ;
		//Material
		GLfloat material_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat material_diffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		GLfloat material_specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_shiness = 10.0f;

		Planet() {
			pX = pY = pZ = 0.0f;
			sX = sY = sZ = 1.0f;
		}

		//태양을 중심으로 한 공전
		void RotatePlanet() {
			currentAngle += rotateAngle;
			if (currentAngle > 360.0f) {
				currentAngle -= 360.0f;
			}
		}

		//행성 렌더링
		void DrawPlanet(const GLdouble radius, const GLint slices, const GLint stacks) {
			if (!isDraw)
				return;
			glPushMatrix();
			glRotatef(currentAngle, 0, 1.0f, 0.0f);
			glTranslatef(pX, pY, pZ);
			glRotatef(-currentAngle, 0, 1.0f, 0.0f);

			glScalef(sX, sY, sZ);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
			glMaterialfv(GL_FRONT, GL_SHININESS, &material_shiness);
			glutSolidSphere(radius, slices, stacks);
			glPopMatrix();
		}
	};

	struct Satelite {
		//Rendering?
		bool isDraw = false;
		//위성을 소유한 행성 변수 포인터
		Planet& mOwnerPlanet;
		//Translate
		GLfloat pX, pY, pZ;
		GLfloat currentAngle = 0.0f;
		GLfloat rotateAngle = 0.0f;
		GLfloat sX, sY, sZ;
		//Material
		GLfloat material_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat material_diffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		GLfloat material_specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_shiness = 0.0f;

		Satelite(Planet& ownerPlanet): mOwnerPlanet(ownerPlanet){
			pX = pY = pZ = 0.0f;
			sX = sY = sZ = 0.6f;
		}
		//위성 회전
		void RotateSatelite() {
			currentAngle += rotateAngle;
			if (currentAngle > 360.0f) {
				currentAngle -= 360.0f;
			}
		}
		//위성 렌더링
		void DrawSatelite(const GLdouble radius, const GLint slices, const GLint stacks) {

			if (!isDraw)
				return;
			glPushMatrix();

			//Translate OwnerPlanet
			glRotatef(mOwnerPlanet.currentAngle, 0, 1.0f, 0.0f);
			glTranslatef(mOwnerPlanet.pX, mOwnerPlanet.pY, mOwnerPlanet.pZ);
			glRotatef(-mOwnerPlanet.currentAngle, 0, 1.0f, 0.0f);
			
			//Translate
			glRotatef(currentAngle, 0, 1.0f, 0.0f);
			glTranslatef(pX, pY, pZ);
			glScalef(sX, sY, sZ);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, &material_shiness);
			glutSolidSphere(radius, slices, stacks);
			glPopMatrix();
		}
	};

	struct Ring {
		//링을 소유한 행성
		Planet& mOwnerPlanet;
		GLdouble inner = 0.8f;
		GLdouble outer = 1.0f;
		GLint slices = 16;
		GLint loops = 4;

		//Translate
		GLfloat pX, pY, pZ;

		//Material
		GLfloat material_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat material_diffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		GLfloat material_specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat material_shiness = 0.0f;

		Ring(Planet& ownerPlanet) : mOwnerPlanet(ownerPlanet) {
			pX = pY = pZ = 0.0f;
		}

		//링 렌더링
		void DrawRing(GLUquadric* quard) {
			glPushMatrix();
			//Translate OwnerPlanet
			glRotatef(mOwnerPlanet.currentAngle, 0, 1.0f, 0.0f);
			glTranslatef(mOwnerPlanet.pX, mOwnerPlanet.pY, mOwnerPlanet.pZ);
			glRotatef(-mOwnerPlanet.currentAngle, 0, 1.0f, 0.0f);
			glRotatef(mOwnerPlanet.axisAngle, 1, 0, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, &material_shiness);
			gluDisk(quard, inner, outer, slices, loops);
			glPopMatrix();
		}
	};

	//행성ID
	enum PLANET_TAG {
		SUN,
		MERCURY,
		VENUS,
		EARTH,
		MARS,
		JUPITER,
		SATURN,
		URANUS,
		NEPTUNE,

		COUNT_OF_PLANET
	};
	//위성ID
	enum SATELITE_TAG {
		MOON,
		JUPITER_SATELITE_0,
		JUPITER_SATELITE_1,

		COUNT_OF_SATELITE
	};

public:
	void renderScene();
	void idleFunc();
	void keyboardInput(unsigned char key, int x, int y);

private:
	//Camera
	GLfloat cameraX = 0.0f;
	GLfloat cameraY = 15.0f;
	GLfloat cameraZ = 15.0f;
	void InitLight();

	//Planet
	const float AU = 2.0f;
	const GLdouble radius = 0.2;	//glutSolidSphere의 radius값으로 이용
	const GLint slices = 100;	//glutSolidSphere의 slices 값으로 이용
	const GLint stacks = 100;	//glutSolidSphere의 stacks 값으로 이용
	Planet mPlanets[PLANET_TAG::COUNT_OF_PLANET];
	void InitPlanets();
	void InitSun();
	void InitMercury();
	void InitVenus();
	void InitEarth();
	void InitMars();
	void InitJupiter();
	void InitSaturn();
	void InitUranus();
	void InitNeptune();

	//Satelites
	Satelite mSatelites[COUNT_OF_SATELITE] = 
	{ Satelite(mPlanets[EARTH]), Satelite(mPlanets[JUPITER]), Satelite(mPlanets[JUPITER]) };
	void InitSatelites();

	//Saturn's tilted
	GLUquadric* quard;
	Ring mSaturnRing = Ring(mPlanets[SATURN]);

public:
	void setPlanetAmbient(PLANET_TAG planet_tag, GLfloat material_ambient[4]);
	void setPlanetDiffuse(PLANET_TAG planet_tag, GLfloat material_diffuse[4]);
	void setPlanetSpecular(PLANET_TAG planet_tag, GLfloat material_specular[4]);
	void setPlanetEmission(PLANET_TAG planet_tag, GLfloat material_emission[4]);
	void setPlanetShiness(PLANET_TAG planet_tag, GLfloat material_shiness);


public:
	CGApplication();
	~CGApplication();
};


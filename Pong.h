#pragma once


#ifdef __APPLE__
   #include <OPENGL/gl.h>
   #include <GLUT/glut.h>
#else
   #include <stdlib.h>
   #include <GL/glut.h>
#endif
#include <vector>
#include "aruco.h"
#include "Matrices.h"

using namespace aruco;

class Pong
{
public:
	Pong(void);
	~Pong(void);
	void reinit();

	GLfloat pos[3];
	int repereId;
	GLfloat speedX;
	GLfloat speedZ;

	bool repereDetected;

	void detectRepere(int id);
	int getRepereIndex(vector<Marker> markers);
	
	void intersection(int id, double repere_matrix[16], double palet_matrix[16]);
	void intersectionMur();
private:

};


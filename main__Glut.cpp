#include <iostream>
#include <GL/glut.h>

using namespace std;
float camX = -5, camY = 0, camZ = 0;
float dirX = 0, dirY = 0, dirZ = 0;
float angleH = 0;
float angleV = 0;
int sX = 0, sY = 0;
int winX = 800, winY = 600;
int currentTime, lastTime;
float mouseSpeed = 0.01f;
float ratio;

float ver[8][3] = 
{
    {-0.5,-0.5,0.5},
    {-0.5,0.5,0.5},
    {0.5,0.5,0.5},
    {0.5,-0.5,0.5},
    {-0.5,-0.5,-0.5},
    {-0.5,0.5,-0.5},
    {0.5,0.5,-0.5},
    {0.5,-0.5,-0.5},
};

GLfloat color[8][3] = 
{
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
    {1.0,0.0,1.0},
    {1.0,1.0,1.0},
    {0.0,1.0,1.0},
};

void quad(int a,int b,int c,int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
}

void colorcube()
{
    quad(0,3,2,1);
    quad(2,3,7,6);
    quad(0,4,7,3);
    quad(1,2,6,5);
    quad(4,5,6,7);
    quad(0,1,5,4);
}

void computeDir()
{
	dirX = camX + cos(angleH) * cos(angleV);
	dirY = camY + sin(angleV);
	dirZ = camZ + sin(angleH) * cos(angleV);
}

void displayCall() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, winX, winY);
	gluPerspective(70, ratio, 1, 500);

	computeDir();
	gluLookAt(camX, camY, camZ, dirX, dirY, dirZ, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/*glScalef(.005,.005,.005);
	glRotatef(20, 0, 1, 0);
	glRotatef(30, 0, 0, 1);
	glRotatef(5, 1, 0, 0);
	glTranslatef(-300, 0, 0);*/

	for(int i=0; i<10; i++)
	{
		glTranslatef(0, 0, 1);
		glScalef(0.8,0.8,0.8);
		colorcube();
	}

	glutSwapBuffers();
}

GLvoid clavier(unsigned char touche, int x, int y) {
   
	// Suivant les touches pressees, nous aurons un comportement different de l'application
	// ESCAPE ou 'q' : fermera l'application
	// 'p' : affichage du carre plein
	// 'f' : affichage du carre en fil de fer
	// 's' : affichage des sommets du carre
   
	float pointSize;

	switch(touche) {
		case 'i' : // carre plein
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 'o' : // fil de fer
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 'p' : // sommets du carre
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case '+': // Augmenter la taille des sommets affiches
			glGetFloatv(GL_POINT_SIZE, &pointSize);
			glPointSize(pointSize+1);
			break;
		case '-': // Diminuer la taille des sommets affiches
			glGetFloatv(GL_POINT_SIZE, &pointSize);
			glPointSize(pointSize-1);
			break;

		case 'z' :
			camX += 0.1*cos(angleH);
			camZ += 0.1*sin(angleH);
			break;
		case 's' :
			camX -= 0.1*cos(angleH);
			camZ -= 0.1*sin(angleH);
			break;
		case 'q' :
			camX += 0.1*sin(angleH);
			camZ -= 0.1*cos(angleH);
			break;
		case 'd' :
			camX -= 0.1*sin(angleH);
			camZ += 0.1*cos(angleH);
			break;
		case 'r' : // Monter
			camY += 0.1;
			break;
		case 'f' : // Descendre
			camY -= 0.1;
			break;

		case 'u' :
			angleV += 0.1;
			break;
		case 'j' :
			angleV -= 0.1;
			break;
		case 'h' :
			angleH -= 0.1;
			break;
		case 'k' :
			angleH += 0.1;
			break;
		

		case 27 : // quitter
		exit(0);
		break;
	}
   
	// Demande a GLUT de reafficher la scene
	glutPostRedisplay();
}

GLvoid souris(int x, int y)
{
	if(x == winX/2 && y == winY/2) return;

	
	/*currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;*/

	
	angleH += mouseSpeed * float(x - winX/2);
	angleV -= mouseSpeed * float(y - winY/2);

	if(x != winX/2) cout << "x=" << x <<" y=" << y << " angleH=" << angleH << endl;

	glutWarpPointer(winX/2, winY/2);

	glutPostRedisplay();
}

void redim(int w, int h)
{
	winX = w;
	winY = h;

	ratio = (winY==0) ? winX : (float)winX / (float)winY;
	cout << "Ratio=" << ratio << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, winX, winY);
	gluPerspective(70, ratio, 1, 500);
	gluLookAt(camX, camY, camZ, dirX, dirY, dirZ, 0.0, 1.0, 0.0);


}

int main(int argc, char *argv[]) {
	cout << argc << endl;
	for(int i=0; i<argc; i++)
	{
		cout << argv[i] << endl;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(winX, winY);
	glutInitWindowPosition(1000, 200);
	glutCreateWindow("Hello World!");

	glutDisplayFunc(displayCall);
	glutReshapeFunc(redim);
	glutKeyboardFunc(clavier);
	glutPassiveMotionFunc(souris);

	glutMainLoop();

	return 0;
} /* end func main */
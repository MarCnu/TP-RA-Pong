#include "Pong.h"


Pong::Pong(void)
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	repereDetected = false;

	speedX = 0.04;
	speedZ = 0;
}


Pong::~Pong(void)
{
}

void Pong::detectRepere(int id)
{
	if(!repereDetected)
	{
		repereId = id;
		repereDetected = true;
	}
}

int Pong::getRepereIndex(vector<Marker> markers)
{
	for(int i=0; i<markers.size(); i++)
	{
		if(markers[i].id == repereId)
		{
			return i;
		}
	}

	return -1;
}

void Pong::intersection(int id, double repere_matrix[16], double palet_matrix[16])
{
	// Conversion double vers float pour être compatible avec Matrix4
	float repere_matrixf[16], palet_matrixf[16];
	for(int i=0; i<16; i++)
	{
		repere_matrixf[i] = repere_matrix[i];
		palet_matrixf[i] = palet_matrix[i];
	}

	Matrix4 repereBalle, reperePalet, reperePaletVersBalle;
	repereBalle.set(repere_matrixf);
	reperePalet.set(palet_matrixf);
	reperePaletVersBalle = repereBalle.invert() * reperePalet;
	Vector4 balle, palet, pointZero;
	pointZero.set(0, 0, 0, 1);
	balle.set(pos[0], pos[1], pos[2], 1);
	palet.set(0, 0, 0, 1);
	
	//pointZero = repereBalle * pointZero;
	//balle = repereBalle * balle;
	palet = reperePaletVersBalle * palet;

	/*cout << "===== " << id << " =====" << endl;
	cout << "Balle dX=" << (balle[0] - pointZero[0]) << endl;
	cout << "Balle dZ=" << (balle[2] - pointZero[2]) << endl;
	cout << "Palet dX=" << (palet[0] - pointZero[0]) << endl;
	cout << "Palet dZ=" << (palet[2] - pointZero[2]) << endl;
	cout << "xxxxx dX=" << (palet[0] - balle[0]) << endl;
	cout << "xxxxx dZ=" << (palet[2] - balle[2]) << endl;*/

	if(abs(balle[0] - palet[0]) < 3*abs(speedX) && abs(balle[2] - palet[2]) < 0.6)
	{
		float rotX, rotZ, newSpeedX, newSpeedZ, dotRotSpeed;
		rotX = reperePaletVersBalle[8];
		rotZ = reperePaletVersBalle[0];
		dotRotSpeed = (rotX*speedX + rotZ*speedZ);
		newSpeedX = -1 * (speedX - 2*dotRotSpeed*rotX);
		newSpeedZ = -1 * (speedZ - 2*dotRotSpeed*rotZ);

		speedX = newSpeedX;
		speedZ = newSpeedZ;

		pos[0] += 3*speedX;
		pos[2] += 3*speedZ;
	}
}

void Pong::intersectionMur()
{
	if(abs(pos[2] - 1) < 3*abs(speedZ))
	{
		speedZ *= -1;
		pos[0] += 3*speedX;
		pos[2] += 3*speedZ;
	}

	if(abs(pos[2] + 1) < 3*abs(speedZ))
	{
		speedZ *= -1;
		pos[0] += 3*speedX;
		pos[2] += 3*speedZ;
	}
}
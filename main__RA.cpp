#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "markerdetector.h"

#define ESC_KEY 27

using namespace cv;
using namespace std;
using namespace aruco;

int main( int argc, char** argv )
{
	Mat image;
	image = imread("C:\\Users\\eleve\\Desktop\\marker2.png");

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	
	
	MarkerDetector myDetector ;
	vector <Marker> markers ;
	myDetector.detect(image, markers) ;
	for (unsigned int i =0 ; i<markers.size(); i++)
	{
		cout << markers [i] << endl ;
		markers[i].draw(image, Scalar(0, 0, 255), 2);
	}
	imshow("Display window", image);

	int key = 0;
	while(key != ESC_KEY) {
		// On recupere le code de la touche pressee par l’utilisateur
		key = waitKey(1);
	}

	return EXIT_SUCCESS;
}
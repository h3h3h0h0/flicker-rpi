#include <raspicam/src/raspicam.h>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

class CamInterface {
    raspicam::RaspiCam *cam;
    CamInterface();

};
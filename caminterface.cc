#include "caminterface.h"

using namespace std;

CamInterface::CamInterface(): cam{new raspicam::RaspiCam()} {
    if(cam->open()) { 
        cerr<<"CAMERA NOT FOUND!"<<endl;
    }
    
    

}
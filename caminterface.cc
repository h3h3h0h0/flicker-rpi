#include "caminterface.h"

using namespace std;

const int GET_ITERATIONS = 8; //how many images worth of noise?

CamInterface::CamInterface() {
    if(cam.open()) { 
        throw CamNotFoundException();
    }
    sleep(3); //not sure if this works
    //since we are using the camera as a source of random numbers, we will make the output as shitty as possible
    //crank up the ISO, use as much sensor area as possible, and turn off all software assists
    cam.setVideoStabilization(false);
    cam.setISO(800);
    cam.setSensorMode(2);
    cam.setAWB(raspicam::RASPICAM_AWB_OFF);
}

void CamInterface::getEntropy(CryptoPP::Keccak_512 &hash) {
    size_t sz = cam.getImageTypeSize (raspicam::RASPICAM_FORMAT_RGB);
    for(int i = 0; i < GET_ITERATIONS; i++) {
        cam.grab();
        CryptoPP::SecByteBlock data(sz);
        cam.retrieve(data, raspicam::RASPICAM_FORMAT_RGB);
        hash.Update(data, sz);
    }
}
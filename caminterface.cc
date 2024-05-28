#include "caminterface.h"

using namespace std;

const int GET_ITERATIONS = 8; //how many images worth of noise?

CamInterface::CamInterface() {
    if(cam.open()) { 
        throw CamNotFoundException();
    }
    //sleep(3) //not sure if this works
}

void CamInterface::get(CryptoPP::Keccak_512 &hash) {
    hash.Restart();
    cam.grab();
    size_t sz = cam.getImageTypeSize (raspicam::RASPICAM_FORMAT_RGB);
    for(int i = 0; i < GET_ITERATIONS; i++) {
        cam.grab();
        unique_ptr<unsigned char> data(new unsigned char[sz]);
        cam.retrieve(data.get(), raspicam::RASPICAM_FORMAT_RGB);
        hash.Update(data.get(), sz);
        memset(data.get(), 0, sz); //destroy the data after you are done
    }
}
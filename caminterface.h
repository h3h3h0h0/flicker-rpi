#include "raspicam/src/raspicam.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <memory>
#include "cryptopp/keccak.h"
#include <functional>
#include <unistd.h> //raspbian is linux
#include "seedinterface.h"

using namespace std;


class CamInterface: public SeedInterface { // interface for seeding from the camera
    raspicam::RaspiCam cam;
    
    public:
    class CamNotFoundException : public exception {};
    CamInterface();
    void getEntropy(CryptoPP::Keccak_512 &hash) override;
};
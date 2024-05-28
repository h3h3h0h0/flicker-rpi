#include <raspicam/src/raspicam.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <memory>
#include <cryptopp/keccak.h>
#include <functional>

using namespace std;


class CamInterface {

    raspicam::RaspiCam cam;
    
    public:
    class CamNotFoundException : public exception {};

    CamInterface();
    void get(CryptoPP::Keccak_512 &hash);


};
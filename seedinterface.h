#pragma once

#include "cryptopp/keccak.h"

class SeedInterface { //virtual class defining an entropy source and its ability to seed a keccack sponge
    public:
    virtual void getEntropy(CryptoPP::Keccak_512 &hash) = 0;
};
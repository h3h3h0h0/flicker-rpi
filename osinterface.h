#include <cryptopp/osrng.h>
#include "seedinterface.h"

using namespace std;

class OSInterface : public SeedInterface { // interface for seeding from dev/urandom or whatever the equivalent is
    public:
    void get(CryptoPP::Keccak_512 &hash);
};

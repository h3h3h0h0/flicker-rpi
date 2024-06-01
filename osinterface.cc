#include "osinterface.h"

using namespace std;

const int GET_BYTES = 64; //how many bytes?

void OSInterface::getEntropy(CryptoPP::Keccak_512 &hash) {
    CryptoPP::SecByteBlock data(GET_BYTES);
    CryptoPP::OS_GenerateRandomBlock(true, data, data.size());
    hash.Update(data, data.size());
}
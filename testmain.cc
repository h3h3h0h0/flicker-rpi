#include "caminterface.h"
#include "osinterface.h"

#include "cryptopp/keccak.h"

using namespace std;

uint32_t extract(CryptoPP::SecByteBlock sbb, size_t ind) {
    uint32_t res = 0;
    res += static_cast<int>(sbb[ind]);
    res = res << 8;
    res += static_cast<int>(sbb[ind+1]);
    res = res << 8;
    res += static_cast<int>(sbb[ind+2]);
    res = res << 8;
    res += static_cast<int>(sbb[ind+3]);
    return res;
}

int main() {
    CryptoPP::Keccak_512 k;
    CamInterface cam{};
    OSInterface osi{};
    CryptoPP::SecByteBlock out(8192);
    for(int i = 0; i < 10000; i++) {
        cam.getEntropy(k);
        osi.getEntropy(k);
        k.TruncatedFinal(out, 8192);
        for(int j = 0; j < 8192; j += 4) {
            cout<<extract(out, j)<<endl;
        }
    }
}
#include "chacha20.h"
//chacha20 algorithm from wikipedia, wrapped for application
//some specifics are from RFC 8439's reference implementation
//since we are providing RNGs little/big endian doesn't really matter here
#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b, d ^= a, d = ROTL(d,16),	\
	c += d, b ^= c, b = ROTL(b,12),	\
	a += b, d ^= a, d = ROTL(d, 8),	\
	c += d, b ^= c, b = ROTL(b, 7))
#define ROUNDS 20

uint32_t C1 = 0x61707865;
uint32_t C2 = 0x3320646e;
uint32_t C3 = 0x79622d32;
uint32_t C4 = 0x6b206574;

using namespace std;
 
void _chacha_block(uint32_t out[16], uint32_t const in[16]){
	int i;
	uint32_t x[16];

	for (i = 0; i < 16; ++i)	
		x[i] = in[i];
	// 10 loops × 2 rounds/loop = 20 rounds
	for (i = 0; i < ROUNDS; i += 2) {
		// Odd round
		QR(x[0], x[4], x[ 8], x[12]); // column 0
		QR(x[1], x[5], x[ 9], x[13]); // column 1
		QR(x[2], x[6], x[10], x[14]); // column 2
		QR(x[3], x[7], x[11], x[15]); // column 3
		// Even round
		QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
		QR(x[1], x[6], x[11], x[12]); // diagonal 2
		QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
		QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
	}
	for (i = 0; i < 16; ++i)
		out[i] = x[i] + in[i];
}

void _prep_chacha(uint32_t out[16], uint32_t const key[8], uint32_t const nonce[3], uint32_t const ctr) {
    out[0] = C1;
    out[1] = C2;
    out[2] = C3;
    out[3] = C4;
    copy(key, key+8, out+4);
    out[12] = ctr;
    copy(nonce, nonce+3, out+13);
}


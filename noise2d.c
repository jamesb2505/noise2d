
#include "noise2d.h"

float interpolate(float a, float b, float w);
float get_value(unsigned seed, int x, int y);
unsigned hash(unsigned x);

// int main(int argc, char *argv[]) {
// 	unsigned seed = atoi(argv[1]);
	
// 	float x = 0.0, y = 0.0, step = atof(argv[2]);
// 	for (int i = 0; i < 1024; i++) {
// 		for (int j = 0; j < 160; j++) {
// 			int p = 10 * noise2d(seed, x, y) / RAND_MAX;
// 			p = (p < 10) ? p : 9;
// 			putchar(p + '0');

// 			// float p = noise2d(seed, x, y) / RAND_MAX;
// 			// putchar(((p < 0.2) ? 32 : 
// 			// 		 (p < 0.4) ? 176 :
// 			// 		 (p < 0.6) ? 177 :
// 			// 		 (p < 0.8) ? 178 : 219));
// 			x += step;
// 		}
// 		putchar('\n');
// 		y += step;
// 		x = 0.0;
// 	}

// 	return 0;
// }

float noise2d(float x, float y, unsigned seed) {
	int ix = (int)x, iy = (int)y;
	float wx = x - (float)ix, wy = y - (float)iy;
	
	return interpolate(interpolate(get_value(seed, ix,   iy  ),
    							   get_value(seed, ix+1, iy  ),
    							   wx),
    				   interpolate(get_value(seed, ix,   iy+1),
    							   get_value(seed, ix+1, iy+1),
    							   wx),
    				   wy) / RAND_MAX;
}

float perlin2d(float x, float y, unsigned seed, int iters, float persistence) { 
	float tot = 0.0, scl = 0.0, amp = 1.0, frq = 1.0;

	for (int i = 0; i < iters; i++) {
		tot += noise2d(x * frq, y * frq, seed) * amp;
		scl += amp;
		frq *= 2;
		amp *= persistence;
	}

	return tot / scl;
}

float interpolate(float a, float b, float w) {
	return a + (b - a) * w * w * (3 - 2 * w);
}

float get_value(unsigned seed, int x, int y) {
	srand(hash(hash(hash(x) ^ y) ^ seed));
	return rand();
}

unsigned hash(unsigned x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	return (x >> 16) ^ x;
}

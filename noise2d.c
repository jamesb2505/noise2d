
#include "noise2d.h"

float interpolate(float a, float b, float w);
float get_value(unsigned seed, int x, int y);
unsigned hash(unsigned x);

float noise2d(float x, float y, unsigned seed) {
	int ix = (int)x, iy = (int)y;
	float wx = x - (float)ix, wy = y - (float)iy;

	float v00 = get_value(seed, ix, iy),
		v10 = get_value(seed, ix + 1, iy),
		v01 = get_value(seed, ix, iy + 1),
		v11 = get_value(seed, ix + 1, iy + 1);

	float v00_10 = interpolate(v00, v10, wx), v01_11 = interpolate(v01, v11, wx);

	return interpolate(v00_10, v01_11, wy) / RAND_MAX;
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

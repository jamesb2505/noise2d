
#include <stdlib.h>
#include <stdio.h>
#include "noise2d.h"
#include "lodepng.h"

int main(int argc, char *argv[]) {
	if (argc != 10) {
		fprintf(stderr, "Error: incorrect usage.\n");
		fprintf(stderr, "Usage: %s <output file name> <width> <height> <x start> <y start> <step> <seed> <iters> <persistence>", argv[0]);

		exit(1);
	}

	char *outfile = argv[1];
	int w = atoi(argv[2]), h = atoi(argv[3]);
	float xs = atof(argv[4]), ys = atof(argv[5]);
	float st = atof(argv[6]);
	unsigned seed = atoi(argv[7]);
	int iters = atoi(argv[8]);
	float pers = atof(argv[9]);

	unsigned char *data = malloc(sizeof(unsigned char) * w * h * 4);
	if (!data) {
		fprintf(stderr, "Error: out of memory.");

		exit(1);
	}

	float x = xs, y = ys;
	for (int i = 0; i < w; i++, y+=st, x=xs) {
		for (int j = 0; j < h; j++, x+=st) {
			float value = perlin2d(x, y, seed, iters, pers);
			int index = 4 * (i * w + j);
			for (int c = 0; c < 3; c++) {
				data[index + c] = 256 * value;
			}
			data[index + 3] = 255;
		}
	}

    lodepng_encode32_file(outfile, data, w, h);

	return 0;
}
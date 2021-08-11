#include "butterworthFilter.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

static uint16_t fs = 0;
static uint16_t fc = 0;

int main (int argc, char** argv) {
	
	int i = 0;
	for (i = 1; i < argc; i++) {
		if ( !strcmp(argv[i], "-c") ) {
			sscanf(argv[i+1], "%hd", &fc);
		} else if ( !strcmp(argv[i], "-s") ) {
			sscanf(argv[i+1], "%hd", &fs);
		}
	}

	if (fs == 0 || fc == 0) {
		printf("invalid cutoff or sampling frequency\n");
		return -1;
	}

	float sig_in;
	float sig_out;

	uint16_t id_1st = register_bw_1st_order_lpf(fc, fs);
	uint16_t id_2nd = register_bw_2nd_order_lpf(fc, fs);

	FILE *fp;
	fp = fopen("/tmp/filter-freq-analysis.txt", "w+");

	uint16_t f_sig = 10;
	for (f_sig = 5; f_sig < 2*fc; f_sig+=5) {
		fprintf(fp, "freq = %d\n", f_sig);
		float t = 0;
		while ( t <= (2.0f / f_sig) ) {
			sig_in = sin(2*M_PI*f_sig*t);
			sig_out = bw_1st_order_lpf(id_1st, sig_in);
			fprintf(fp, "%f\t", sig_out);
			sig_out = bw_2nd_order_lpf(id_2nd, sig_in);
			fprintf(fp, "%f\n", sig_out);
			t += 1.0f/fs;
		}
	}

	fclose(fp);

	return 0;
}

#include "butterworthFilter.h"

#include <math.h>
#include <stdlib.h>

typedef struct {
	// signal sampling frequency
	float fs_hz;
	// previous input
	float p_in;
	// previous output
	float p_out;
	// 3 coefficients, 2 for input signals, 1 for output signals
	float c_in[2];
	float c_out;
} bw_1st_order_lpf_signal_t;

static uint16_t num_bw_1st_order_lpf = 0;
bw_1st_order_lpf_signal_t* bw_1st_order_lpf_sig; 

uint16_t register_bw_1st_order_lpf(const uint16_t fc_hz, const uint16_t fs_hz) {
	uint16_t flt_id = num_bw_1st_order_lpf;
	num_bw_1st_order_lpf++;
	if (num_bw_1st_order_lpf == 1) {
		bw_1st_order_lpf_sig = malloc(num_bw_1st_order_lpf*sizeof(bw_1st_order_lpf_signal_t));
	} else {
		bw_1st_order_lpf_sig = realloc(bw_1st_order_lpf_sig, num_bw_1st_order_lpf*sizeof(bw_1st_order_lpf_signal_t));
	}

	// initialize signals
	bw_1st_order_lpf_sig[flt_id].p_in = 0.0;
	bw_1st_order_lpf_sig[flt_id].p_out = 0.0;

	// store frequencies
	bw_1st_order_lpf_sig[flt_id].fs_hz = fs_hz;

	update_bw_1st_order_lpf_params(flt_id, fc_hz);

	return flt_id;
}

float bw_1st_order_lpf(const uint16_t id, const float in) {
	float out = bw_1st_order_lpf_sig[id].c_in[1] * in;
	out += bw_1st_order_lpf_sig[id].c_in[0] * bw_1st_order_lpf_sig[id].p_in;
	out += bw_1st_order_lpf_sig[id].c_out * bw_1st_order_lpf_sig[id].p_out;

	bw_1st_order_lpf_sig[id].p_in = in;
	bw_1st_order_lpf_sig[id].p_out = out;

	return out;
}

void update_bw_1st_order_lpf_params(const uint16_t id, const uint16_t fc_hz) {
	float ts_s = 1.0f / bw_1st_order_lpf_sig[id].fs_hz;
	/* Coefficient calculation*/
	float eta = tanf(M_PI*fc_hz*ts_s);
	float c_factor = 1.0 / (1 + eta);
	bw_1st_order_lpf_sig[id].c_in[0] = c_factor * eta;
	bw_1st_order_lpf_sig[id].c_in[1] = bw_1st_order_lpf_sig[id].c_in[0];
	bw_1st_order_lpf_sig[id].c_out = -c_factor * (eta - 1);
}


/// 2nd order Butterworth filter
typedef struct {
	// signal sampling frequency
	float fs_hz;
    // previous input signals
    // p_in[0]: input signal 2 steps before
    // p_in[1]: previous input signal
    float p_in[2];
    // previous output signals
    // p_out[0]: output signal 2 steps before
    // p_out[1]: previous output signal
    float p_out[2];
    // 7 coefficients, 4 for input signals, 3 for output signals
    float c_in[3];
    float c_out[2];
} bw_2nd_order_lpf_signal_t;

static bw_2nd_order_lpf_signal_t *bw_2nd_lpf_signals;

static uint16_t num_bw_2nd_order_lpfs = 0;
uint16_t register_bw_2nd_order_lpf(const uint16_t fc_hz, const uint16_t fs_hz)
{
    int16_t idx = num_bw_2nd_order_lpfs;
    num_bw_2nd_order_lpfs++;
	if (num_bw_2nd_order_lpfs == 1) {
		bw_2nd_lpf_signals = malloc(num_bw_2nd_order_lpfs*sizeof(bw_2nd_order_lpf_signal_t));
	} else {
		bw_2nd_lpf_signals = realloc(bw_2nd_lpf_signals, num_bw_2nd_order_lpfs*sizeof(bw_2nd_order_lpf_signal_t));
	}

    // initialize signals
	bw_2nd_lpf_signals[idx].fs_hz = fs_hz;
	update_bw_2nd_order_lpf_params(idx, fc_hz);

    return idx;
}

float bw_2nd_order_lpf(const uint16_t id, const float in) {
    int16_t i = 0;

    float out = bw_2nd_lpf_signals[id].c_in[2] * in;
    for (i=0; i<2; i++) {
        out += bw_2nd_lpf_signals[id].c_in[i] * bw_2nd_lpf_signals[id].p_in[i];
        out += bw_2nd_lpf_signals[id].c_out[i] * bw_2nd_lpf_signals[id].p_out[i];
    }

    bw_2nd_lpf_signals[id].p_in[0] = bw_2nd_lpf_signals[id].p_in[1];
    bw_2nd_lpf_signals[id].p_in[1] = in;
    bw_2nd_lpf_signals[id].p_out[0] = bw_2nd_lpf_signals[id].p_out[1];
    bw_2nd_lpf_signals[id].p_out[1] = out;

    return out;
}

void update_bw_2nd_order_lpf_params(const uint16_t id, const uint16_t fc_hz) {
    int16_t i = 0;
    for (i=0; i<2; i++) {
        bw_2nd_lpf_signals[id].p_in[i] = 0.0;
        bw_2nd_lpf_signals[id].p_out[i] = 0.0;
    }

    /* Coefficient calculation*/
	float ts_s = 1.0f / bw_2nd_lpf_signals[id].fs_hz;
    float eta = tan(M_PI*fc_hz*ts_s);
    float c_factor = 1.0 / (M_SQRT2*eta + pow(eta,2) + 1);
    bw_2nd_lpf_signals[id].c_in[0] = c_factor * pow(eta,2);
    bw_2nd_lpf_signals[id].c_in[1] = 2 * bw_2nd_lpf_signals[id].c_in[0];
    bw_2nd_lpf_signals[id].c_in[2] = bw_2nd_lpf_signals[id].c_in[0];
    bw_2nd_lpf_signals[id].c_out[0] = -c_factor*(pow(eta,2) - M_SQRT2*eta + 1);
    bw_2nd_lpf_signals[id].c_out[1] = -c_factor*(2*pow(eta,2) - 2);
}

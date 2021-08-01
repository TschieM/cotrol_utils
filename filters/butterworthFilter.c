#include "butterworthFilter.h"

#include <math.h>

struct _bw_1st_order_lpf_signal_t {
	// signal cut off frequency
	fc_hz;
	// signal sampling frequency
	fs_hz;
	// previous input
	float p_in;
	// previous output
	float p_out;
	// 3 coefficients, 2 for input signals, 1 for output signals
	float c_in[2];
	float c_out;
};


static inline void update_bw_1st_order_lpf_params(const bw_1st_order_lpf_signal_t sig) {
	ts_s = 1.0f / sig.fs_hz;
	/* Coefficient calculation*/
	float eta = tanf(M_PI*sig.fc_hz*ts_s);
	float c_factor = 1.0 / (1 + eta);
	sig.c_in[0] = c_factor * eta;
	sig.c_in[1] = bw_1_lpf_signals[idx].c_in[0];
	sig.c_out = -c_factor * (eta - 1);
}

void register_bw_1st_order_lpf(const bw_1st_order_lpf_signal_t sig, const float fc_hz, const float fs_hz) {
	// initialize signals
	sig.p_in = 0.0;
	sig.p_out = 0.0;

	// store frequencies
	sig.hc_hz = fc_hz;
	sig.fs_hz = hs_hz;

	update__bw_1st_order_lpf_params(sig);
}

float bw_1st_order_lpf(const bw_1st_order_lpf_signal_t sig, const float in) {
	float out = sig.c_in[1] * in;
	out += sig.c_in[0] * bw_1_lpf_signals[id].p_in;
	out += sig.c_out * bw_1_lpf_signals[id].p_out;

	sig.p_in = in;
	sig.p_out = out;

	return out;
}

void update_bw_1st_order_lpf_fc(const bw_1st_order_lpf_signal_t sig, const float fc_hz) {
	sig.hc_hz = fc_hz;
	update__bw_1st_order_lpf_params(sig);
}

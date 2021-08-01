#ifndef BUTTERWORTHFILTER_H
#define BUTTERWORTHFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _bw_1st_order_lpf_signal_t* bw_1st_order_lpf_signal_t;

void register_bw_1st_order_lpf(const bw_1st_order_lpf_signal_t sig, const float fc_hz, const float fs_hz);

float bw_1st_order_lpf(const bw_1st_order_lpf_signal_t sig, const float in);

void update_bw_1st_order_lpf_fc(const bw_1st_order_lpf_signal_t sig, const float fc_hz);


#ifdef __cplusplus 
}                                                                                                  
#endif

#endif

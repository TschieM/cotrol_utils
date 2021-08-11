#ifndef BUTTERWORTHFILTER_H
#define BUTTERWORTHFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint16_t register_bw_1st_order_lpf(const uint16_t fc_hz, const uint16_t fs_hz);

float bw_1st_order_lpf(const uint16_t id, const float in);

void update_bw_1st_order_lpf_params(const uint16_t id, const uint16_t fc_hz);

uint16_t register_bw_2nd_order_lpf(const uint16_t fc_hz, const uint16_t fs_hz);

float bw_2nd_order_lpf(const uint16_t id, const float in);

void update_bw_2nd_order_lpf_params(const uint16_t id, const uint16_t fc_hz);

#ifdef __cplusplus 
} 
#endif

#endif

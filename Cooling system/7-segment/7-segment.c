/*
 * _7_segment.c
 *
 * Created: 9/2/2023 9:04:01 AM
 *  Author: C O N N E C T
 */ 

#include "generic_macros_header.h"
#include "7-segment.h"
#include "7-segment_cfg.h"

void sevenS_init(void){
	ss_init();
}
void SS1_read(uint8_t num){
	SS_1(num);
}
void SS2_read(uint8_t num){
	SS_2(num);
}
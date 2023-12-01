/*
 * _7_segment.h
 *
 * Created: 9/2/2023 9:04:18 AM
 *  Author: C O N N E C T
 */ 


#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "generic_macros_header.h"
#define BUTTON READBIT(PIND,PD6)

void sevenS_init(void);
void SS1_read(uint8_t num);
void SS2_read(uint8_t num);

#endif /* 7-SEGMENT_H_ */
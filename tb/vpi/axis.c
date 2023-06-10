/* Copyright (c) 2023, Julia Desmazes. All rights reserved.
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 International License.
 *
 * This code is provided "as is" without any express or implied warranties. */
#include "axis.h"
#include <assert.h>

uint64_t axis_get_next_64b(const uint8_t *flat, size_t *idx, const size_t len, uint8_t *mask){
	uint64_t buff = 0;
	size_t min = ( len < *idx+8)? len : *idx+8;
	assert(*idx < len);
	assert(flat);
	for(size_t s = 0, i = *idx; i < min ; i++, s++){
		buff |= ( (uint64_t) flat[i] << s );
	}
	*idx = min;
	if ( *idx+8 > len ){
		size_t diff = len - min;
		*mask = 0xff >> diff;
	}else *mask = 0xff;

	return buff; 
} 


void axis_send_64b(const uint64_t payload, const uint8_t mask, 
	uint8_t *tvalid, uint8_t *tkeep, uint8_t *tready, uint64_t*tdata){
	if ( *tready ){
		*tvalid = 1;
		*tkeep = mask;
		*tdata = payload;
	}
	*tvalid = 0;
}

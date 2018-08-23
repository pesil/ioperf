/*
 * ringbuf_lockable.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: petersil
 */

#include "ringbuf_lockable.h"

void RingBufferLock::write(char* val, int size){
	lock_guard<mutex> lg(ring_locks[write_ptr % buf_size]);
	memcpy(&ringbuf[write_ptr % buf_size ],val,size);
	write_ptr++;
}

int RingBufferLock::read(char* val){
	lock_guard<mutex> lg(ring_locks[read_ptr % buf_size]);
	val = ringbuf[read_ptr % buf_size ];
	read_ptr++;
	return 0;
}

void RingBufferLock::test_empty(){
}

RingBufferLock::RingBufferLock(){

}



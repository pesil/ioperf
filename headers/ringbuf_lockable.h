/*
 * ringbuf_lockable.h
 *
 *  Created on: Aug 9, 2018
 *      Author: petersil
 */

#include "ioperf.h"
#include "buffer.h"

#ifndef HEADERS_RINGBUF_LOCKABLE_H_
#define HEADERS_RINGBUF_LOCKABLE_H_


class RingBufferLock: public Buffer {
private:
	int64_t write_ptr;
	int64_t read_ptr;
	char ringbuf[buf_size][word_max_len];
	mutex ring_locks[buf_size];

public:
	void write(char* val, int size);
	int read(char* val);
	void test_empty();

	RingBufferLock();
	~RingBufferLock() {};
};


#endif /* HEADERS_RINGBUF_LOCKABLE_H_ */

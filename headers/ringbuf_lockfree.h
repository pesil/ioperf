/*
 * ringbuf.h
 *
 *  Created on: Aug 8, 2018
 *      Author: petersil
 *
 *	Single Producer / Single Consumer lock-free ring buffer
 */

#include "buffer.h"
#include "ioperf.h"

#ifndef HEADERS_RINGBUF_H_
#define HEADERS_RINGBUF_H_

class RingBuffer: public Buffer {
private:
	std::atomic<int64_t> write_ptr;
	std::atomic<int64_t> read_ptr;
	char ringbuf[buf_size][word_max_len];
	int64_t out_offset = 0;

public:
	bool write_chunk(istream* res);
	bool write_chunk(FILE* res);
	int read(char* val);
	void stop_reading();
	bool is_stopped();
	void test_full();
	void test_empty();
	bool compare_write_read();
	int read_info();
	int write_info();
	void init_outbuf(int size);

	RingBuffer();
	~RingBuffer();
};



#endif /* HEADERS_RINGBUF_H_ */

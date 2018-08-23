/*
 * buffer.h
 *
 *  Created on: Aug 8, 2018
 *      Author: petersil
 */
#ifndef HEADERS_BUFFER_H_
#define HEADERS_BUFFER_H_

#include "ioperf.h"
#include "resource.h"

class Buffer {
public:
	atomic<bool> full_bit = ATOMIC_FLAG_INIT;
	atomic<bool>  empty_bit = ATOMIC_FLAG_INIT;
	bool is_read_stop = false;
	char* outbuf;

	virtual bool write_chunk(istream* res) = 0;
	virtual bool write_chunk(FILE* res) = 0;
	virtual int read(char* val) = 0;
	virtual void stop_reading() = 0;
	virtual bool is_stopped() = 0;
	virtual void test_empty() = 0;
	virtual void test_full() = 0;
	virtual int read_info() = 0;
	virtual int write_info() = 0;
	virtual void init_outbuf(int size) = 0;
	virtual ~Buffer(){};
};



#endif /* HEADERS_BUFFER_H_ */

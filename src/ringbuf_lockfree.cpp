/*
 * ringbuf_lockfree.cpp
 *
 * Lock-free realization of Single Consumer\Single Producer ring buffer
 *
 *  Created on: Aug 8, 2018
 *      Author: petersil
 */

#include <ringbuf_lockfree.h>

RingBuffer::RingBuffer(){
	write_ptr.store(0);
	read_ptr.store(0);
	empty_bit.store(true);
	full_bit.store(false);
}

//read data by word_max_len from resource and
//write by chunk_size buckets into ring buffer, while buffer is not full
bool RingBuffer::write_chunk(istream* res){
	auto cur_write_ptr = write_ptr.load(memory_order_acquire);
	int64_t write_cnt = 0;

	for(;write_cnt < chunk_size &&
	!res->eof();
	++write_cnt) {
		res->getline(ringbuf[(cur_write_ptr + write_cnt) % buf_size ],word_max_len);
	}

	cur_write_ptr += write_cnt;
	write_ptr.store(cur_write_ptr , std::memory_order_release);
	if(compare_write_read()) full_bit.store(true,memory_order_release);
	empty_bit.store(false,memory_order_release);

	return true;
}

bool RingBuffer::write_chunk(FILE* res){
	auto cur_write_ptr = write_ptr.load(memory_order_acquire);
	int64_t write_cnt = 0;

	for(;write_cnt < chunk_size &&
	!feof(res);
	++write_cnt) {
		fgets(ringbuf[(cur_write_ptr + write_cnt) % buf_size ],word_max_len,res);
	}

	cur_write_ptr += write_cnt;
	write_ptr.store(cur_write_ptr , std::memory_order_release);
	if(compare_write_read()) full_bit.store(true,memory_order_release);
	empty_bit.store(false,memory_order_release);

	return true;
}


//read data by "chunk_size" buckets while buffer is not empty
//after each read chunk cycle, shift read pointer
int RingBuffer::read(char* val){
	auto cur_read_ptr = read_ptr.load(memory_order_acquire);
	int total_read = 0;

	while(!empty_bit.load(memory_order_acquire)){
		int64_t read_cnt = 0;
		auto cur_write_ptr = write_ptr.load(std::memory_order_acquire);

		for(;read_cnt < chunk_size
		&& (cur_read_ptr + read_cnt != cur_write_ptr)
		;++read_cnt) {
			//memcpy((void*)&outbuf[word_max_len*(out_offset++)],(const void*)&ringbuf[(cur_read_ptr + read_cnt) % buf_size ][0],word_max_len);
			val = ringbuf[(cur_read_ptr + read_cnt) % buf_size ];
		}

		cur_read_ptr += read_cnt;
		total_read += read_cnt;
		read_ptr.store(cur_read_ptr , std::memory_order_release);
		if(compare_write_read()) empty_bit.store(true,memory_order_release);
		full_bit.store(false,memory_order_release);
	}
	return total_read;
}

bool RingBuffer::compare_write_read(){
	return read_ptr.load(memory_order_acquire) == write_ptr.load(memory_order_acquire);
}

void RingBuffer::test_empty(){
	if(!full_bit.load() &&
			read_ptr.load(memory_order_acquire) == write_ptr.load(memory_order_acquire)){
		empty_bit.store(true);
	}
}

void RingBuffer::test_full(){
	if(!empty_bit.load() &&
			read_ptr.load(memory_order_acquire) == write_ptr.load(memory_order_acquire)){
		full_bit.store(true);
	}
}

void RingBuffer::stop_reading(){
	is_read_stop = true;
}

bool RingBuffer::is_stopped(){
	return is_read_stop;
}

int RingBuffer::read_info(){
	return read_ptr.load();
}

int RingBuffer::write_info(){
	return write_ptr.load();
}

void RingBuffer::init_outbuf(int size){
	outbuf = (char*)malloc(size);
}


RingBuffer::~RingBuffer(){

}







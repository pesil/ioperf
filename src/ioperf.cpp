//============================================================================
// Name        : ioperf.cpp
// Author      : petersil
// Version     :
// Copyright   : 
// Description :
//============================================================================


#include "ringbuf_lockfree.h"
#include "wordstream.h"
#include "ioperf.h"
#include "util.h"
#include <unistd.h>
#include <sched.h>

void writer_job(ifstream* res,vector<Buffer*> buffer_pool){
	hr_clock::time_point t1 = hr_clock::now();
	int64_t full_cnt = 0;

	while(!res->eof()){
		for(auto &buf:buffer_pool){
			if(!buf->full_bit.load(memory_order_acquire)) buf->write_chunk(res);
			else full_cnt++;
			if(res->eof()) break;
		}
	}
	for(auto buf:buffer_pool) buf->stop_reading();

	hr_clock::time_point t2 = hr_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

	lock_guard<mutex> lg(cout_lock);
	cout<<"Writer work time = "<<duration<<"ms"<<endl;
	cout<<"Full cnt = "<<full_cnt<<endl;
	cout << "Writer on CPU " << sched_getcpu() << endl;
}

void reader_job(Buffer* buffer){
	auto wcpu_id = sched_getcpu();
	uint64_t word_handled_cnt = 0;
	char* val = new char(word_max_len);
	int64_t empty_cnt = 0;

	while(!buffer->is_read_stop){
		if(!(buffer->empty_bit.load(memory_order_acquire))) word_handled_cnt += buffer->read(val);
		else empty_cnt++;
	}
	if(!(buffer->empty_bit.load())) word_handled_cnt += buffer->read(val);

	lock_guard<mutex> lg(cout_lock);
	cout<<"Thread "<<std::this_thread::get_id()<<" handled "<<word_handled_cnt<<endl;
	cout<<"Empty cnt = "<<empty_cnt<<endl;
	cout << "Reader on CPU " << wcpu_id << endl;
}

//	Try to execute writer thread on dedicated physical core, because it may conflict with one of the reader threads,
//	resulting in performance gaps.
void set_writer_affinity(thread* _thread){
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(_thread->native_handle(),sizeof(cpu_set_t), &cpuset);
    sched_param sch_params;
    sch_params.sched_priority = 99;
	pthread_setschedparam(_thread->native_handle(), SCHED_FIFO, &sch_params);
}

cpu_set_t get_reader_affinity(){
	int logic_cores = thread::hardware_concurrency();

	//Physical core count. Assuming standard way hyperthreading usage.
    int core_cnt = logic_cores / 2;

	cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
	for(int i=0;i<logic_cores;++i){
		if(i%core_cnt) CPU_SET(i,&cpuset);
	}
	return cpuset;
}

int main() {
	vector<thread> reader_pool;
	vector<Buffer*> buffer_pool;

//	file_gen(input_data_filename);
//	numeric_file_gen(input_data_filename);

	iostream::sync_with_stdio(false);
	ifstream* res = new ifstream(input_data_filename, ios::binary);

	for(int i=0;i<thread_cnt;++i)
		buffer_pool.push_back(new RingBuffer());

//	just for test
//	for(auto &buf:buffer_pool) buf->init_outbuf(word_file_max_size*word_max_len);

	thread writer(writer_job,ref(res),ref(buffer_pool));

	for(int i=0;i<thread_cnt;++i)
		reader_pool.emplace_back(reader_job,ref(buffer_pool[i]));

	writer.join();
	for(auto &reader:reader_pool) reader.join();

//	just for test
//	int i=0;
//	for(auto &buf:buffer_pool) out_file_gen(output_data_filename+to_string(i++),buf->outbuf,buf->write_info()*word_max_len);

	return 0;
}


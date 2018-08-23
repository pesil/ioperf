/*
 * ioperf.h
 *
 *  Created on: Aug 8, 2018
 *      Author: petersil
 */

#include <iostream>
#include <fstream>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <chrono>

using namespace std;

#ifndef HEADERS_IOPERF_H_
#define HEADERS_IOPERF_H_

typedef std::chrono::high_resolution_clock hr_clock;

const string input_data_filename = "/home/pe/readtest/testdata2G";
const uint64_t word_file_max_size = 2048ll*1024ll*1024ll;

//const string input_data_filename = "/home/pe/readtest/testdata128";
//const uint64_t word_file_max_size = 128ll*1024ll*1024ll;

//const string input_data_filename = "/home/pe/readtest/testdata";
//const uint64_t word_file_max_size = 64ll*1024ll*1024ll;

const string output_data_filename = "/home/pe/readtest/resultdata";

const int thread_cnt = 3;

const int word_max_len = 16;
const int chunk_size = 4096;
const int buf_size = 16*chunk_size;

static mutex cout_lock;

#endif /* HEADERS_IOPERF_H_ */

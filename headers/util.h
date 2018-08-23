/*
 * util.h
 *
 *  Created on: Aug 15, 2018
 *      Author: root
 */

#ifndef HEADERS_UTIL_H_
#define HEADERS_UTIL_H_

#include "ioperf.h"

void reverse_string(char* str,int size);
int get_word_count(char* buf, int size);
void file_gen(const string &fname);
void out_file_gen(const string &fname, char* buf, uint64_t buf_size);
uint64_t produce_file_to_buf(const string &fname);
void numeric_file_gen(const string &fname);


#endif /* HEADERS_UTIL_H_ */

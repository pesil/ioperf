/*
 * wordstream.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: petersil
 */

#include "wordstream.h"

Wordstream::Wordstream(const string& path){
	iostream::sync_with_stdio(false);
	istream = ifstream(input_data_filename, ios::binary);
}

void Wordstream::read_data(void* dst, int size) {
	istream.getline((char*)dst,size);
}

void Wordstream::read_data(void* dst) {
	char size = 0;
	istream.read(&size,1);
	istream.read((char*)dst,size);
}

int Wordstream::read_count(){
	return istream.gcount();
}

bool Wordstream::end(){
	return istream.eof();
}

Wordstream::~Wordstream(){
	istream.close();
}



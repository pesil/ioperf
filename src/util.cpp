/*
 * util.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: petersil
 */

#include "ioperf.h"

char* raw_word_buf;
char* out_buf;

uint64_t tmp_word_count = 0;
uint64_t raw_word_buf_pos = 0;

void reverse_string(char* str,int size){
	int i=0;
	while(i<size) swap(str[i++],str[size--]);
}

int get_word_count(char* buf, int size){
	int cnt=0;
	for(int i=0;i<size;++i) {
		if(buf[i]=='\n') cnt++;
	}
	return cnt;
}

void file_gen(const string &fname){
	ofstream ofile(fname);
	srand(time(0));
	uint64_t total_size = 0;
	while(total_size < word_file_max_size){
		char wordlen = 5 + rand()%7;
		total_size+=wordlen;
		//ofile << wordlen;
		while(wordlen--) ofile << (char)('a'+rand()%26);
		ofile << '\n';
		tmp_word_count++;
	}
	cout<<"Generate "<<tmp_word_count<<" words"<<endl;
}

void numeric_file_gen(const string &fname){
	ofstream ofile(fname);
	for(uint64_t cur = 0;cur < word_file_max_size;++cur) ofile<<cur<<'\n';
	cout<<"Generated successfully."<<endl;
}

void out_file_gen(const string &fname, char* buf, uint64_t buf_size){
	ofstream ofile(fname);
	ofile.write(buf,buf_size);
	ofile.flush();
	ofile.close();
}

uint64_t produce_file_to_buf(const string &fname){
	iostream::sync_with_stdio(false);
	ifstream ifile_stream(fname, ios::binary | ios::ate);
	streamsize isize = ifile_stream.tellg();
	ifile_stream.seekg(0, ios::beg);
	raw_word_buf = (char*) malloc(isize);
	ifile_stream.read(raw_word_buf, isize);
	if (ifile_stream) cout << "all characters read successfully"<<endl;
	else cout << "error: only " << ifile_stream.gcount() << " could be read"<<endl;
	ifile_stream.close();
	return isize;
}


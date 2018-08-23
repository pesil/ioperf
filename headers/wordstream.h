/*
 * wordstream.h
 *
 *  Created on: Aug 16, 2018
 *      Author: petersil
 */

#ifndef HEADERS_WORDSTREAM_H_
#define HEADERS_WORDSTREAM_H_

#include "ioperf.h"
#include "resource.h"

class Wordstream: public Resource {
private:
public:
	ifstream istream;

	Wordstream(const string& path);
	~Wordstream();
	void read_data(void* dst, int size);

/*
	In case of usage input file format with string size given in first byte of each line
	we could avoid usage of getline function with redundant checks and possibly speed up file read
*/
	void read_data(void* dst);
	int read_count();
	bool end();
};




#endif /* HEADERS_WORDSTREAM_H_ */

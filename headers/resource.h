/*
 * resource.h
 *
 *  Created on: Aug 16, 2018
 *      Author: petersil
 */

#ifndef HEADERS_RESOURCE_H_
#define HEADERS_RESOURCE_H_

class Resource {
public:
	virtual ~Resource() {};
	virtual void read_data(void* dst) {};
	virtual void read_data(void* dst, int size) {};
	virtual int read_count() = 0;
	virtual bool end() = 0;
};



#endif /* HEADERS_RESOURCE_H_ */

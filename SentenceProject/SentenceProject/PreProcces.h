// PreProccess.h
// Jack Murdock

#ifndef __PREPROCCESS_CLASS_H__
#define __PREPROCCESS_CLASS_H__
#include <iostream>
#include <ifstream>
using namespace std;

class PreProcces{
public:
	PreProcces(string filename){
		this->filename = filename;
	}

private:
	string filename;
};



#endif /*__PREPROCCESS_CLASS_H__*/
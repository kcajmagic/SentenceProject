// PreProccess.h
// Jack Murdock

#ifndef __UNIQUENESS_CLASS_H__
#define __UNIQUENESS_CLASS_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>


class Uniqueness{
public:
	Uniqueness(){
		number_of_unique_lines = 0;
		number_of_same_lines = 0;
	}

	void increase_unique(string line){
		unordered_map<string, bool>::const_iterator got = word_mapping.find(line);
		if (got == word_mapping.end()){
			// Not Found
			number_of_unique_lines++;
			word_mapping[line] = true;
		}
		else{
			number_of_same_lines++;
		}
	}

	unsigned long long get_uniqueness(){
		return number_of_unique_lines;
	}

	unsigned long long get_similualre_lines(){
		return number_of_same_lines;
	}

//	increase get_method(){
//		return *this->increase_unique;
//	}

private:
	unordered_map<string, bool> word_mapping;
	unsigned long long number_of_unique_lines;
	unsigned long long number_of_same_lines;
};

#endif /*__UNIQUENESS_CLASS_H__*/
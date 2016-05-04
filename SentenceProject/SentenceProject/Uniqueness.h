// PreProccess.h
// Jack Murdock

#ifndef __UNIQUENESS_CLASS_H__
#define __UNIQUENESS_CLASS_H__
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
		unordered_map<string, unsigned int>::const_iterator got = word_mapping.find(line);
		if (got == word_mapping.end()){
			// Not Found
			number_of_unique_lines++;
			word_mapping[line] = 1;
		}
		else{
			word_mapping[line]++;
			number_of_same_lines++;
		}
	}

	uint32_t get_uniqueness(){
		return number_of_unique_lines;
	}

	uint32_t get_similualre_lines(){
		return number_of_same_lines;
	}

	unordered_map<string, unsigned int>& get_data() {
		return word_mapping;
	}

//	increase get_method(){
//		return *this->increase_unique;
//	}

private:
	unordered_map<string, unsigned int> word_mapping;
	uint32_t number_of_unique_lines;
	uint32_t number_of_same_lines;
};

#endif /*__UNIQUENESS_CLASS_H__*/
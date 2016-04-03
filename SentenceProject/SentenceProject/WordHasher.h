// PreProccess.h
// Jack Murdock

#ifndef __WORDHASHER_CLASS_H__
#define __WORDHASHER_CLASS_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>

using namespace std;

class WordHasher{
public:
	WordHasher(){
		next_int = 0;
	}

	unsigned long long get_next_value(string word){
		unordered_map<string, unsigned long long>::const_iterator got = word_mapping.find(word);
		if (got == word_mapping.end()){
			// Not Found
			unsigned long long ret_val = next_int;
			word_mapping[word] = ret_val;
			next_int++;
			return ret_val;
		}
		else{
			return got->second;
		}
	}
private:
	unsigned long long next_int;
	unordered_map<string, unsigned long long> word_mapping;

};

#endif /*__WORDHASHER_CLASS_H__*/
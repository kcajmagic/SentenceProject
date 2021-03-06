// WordHasher.h
// Jack Murdock

#ifndef __WORDHASHER_CLASS_H__
#define __WORDHASHER_CLASS_H__
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>

using namespace std;

class WordHasher {
public:
	WordHasher() {
		next_int = 0;
	}

	uint32_t get_next_value(string word) {
		unordered_map<string, uint32_t>::const_iterator got = word_mapping.find(word);
		if (got == word_mapping.end()) {
			// Not Found
			uint32_t ret_val = next_int;
			word_mapping[word] = ret_val;
			value_to_word_mapping[ret_val] = word;
			next_int++;
			return ret_val;
		}
		else {
			return got->second;
		}
	}

	string get_word_from_value(uint32_t val) {
		return value_to_word_mapping[val];
	}
private:
	uint32_t next_int;
	unordered_map<string, uint32_t> word_mapping;
	unordered_map<uint32_t, string> value_to_word_mapping;

};

#endif /*__WORDHASHER_CLASS_H__*/
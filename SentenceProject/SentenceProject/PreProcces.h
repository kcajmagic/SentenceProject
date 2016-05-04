// PreProccess.h
// Jack Murdock

#ifndef __PREPROCCESS_CLASS_H__
#define __PREPROCCESS_CLASS_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "Uniqueness.h"
#include "WordHasher.h"

using namespace std;

class PreProcces{
public:
	PreProcces(string filename){
		this->filename = filename;
	}
	

	vector<string> split(const string& s, const string& delim, const bool keep_empty = true) {
		vector<string> result;
		if (delim.empty()) {
			result.push_back(s);
			return result;
		}
		string::const_iterator substart = s.begin(), subend;
		while (true) {
			subend = search(substart, s.end(), delim.begin(), delim.end());
			string temp(substart, subend);
			if (keep_empty || !temp.empty()) {
				result.push_back(temp);
			}
			if (subend == s.end()) {
				break;
			}
			substart = subend + delim.size();
		}
		return result;
	}

	void read_and_count_unique(Uniqueness *counter) {
		string line;
		ifstream file(filename);
		if (file.is_open()) {
			while (getline(file, line)) {
				counter->increase_unique(line);
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
			throw 0;
		}
	}

	void read_into_memory_and_count_unique(Uniqueness *counter){
		string line;
		ifstream file(filename);
		if (file.is_open()){
			while (getline(file, line)){
				counter->increase_unique(line);
				vector<string> words = split(line, " ");
				data.push_back(words);
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
			throw 0;
		}
	}

	vector<vector<uint32_t>> read_through_lines_and_hash(){
		string line;
		ifstream file(filename);
		WordHasher hasher;
		vector<vector<uint32_t>> hashed_data;
		if (file.is_open()){
			while (getline(file, line)){
				vector<string> words = split(line, " ");
				//this->data.push_back(words);
				vector<uint32_t> hashed_words;
				for each (string word in words)
				{
					hashed_words.push_back(hasher.get_next_value(word));
				}
				hashed_data.push_back(hashed_words);
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
		}
		return hashed_data;
	}

	vector<vector<uint32_t>> read_through_lines_and_hash_and_generate_thing(unordered_map<vector<uint32_t>, unsigned int>& kv_store) {
		string line;
		ifstream file(filename);
		WordHasher hasher;
		vector<vector<uint32_t>> hashed_data;
		if (file.is_open()) {
			while (getline(file, line)) {
				vector<string> words = split(line, " ");
				//this->data.push_back(words);
				vector<uint32_t> hashed_words;
				for each (string word in words)
				{
					hashed_words.push_back(hasher.get_next_value(word));
				}
				

				unordered_map<vector<uint32_t>, unsigned int>::const_iterator got = kv_store.find(hashed_words);
				if (got == kv_store.end()) {
					// Not Found
					kv_store[hashed_words] = 0;
					hashed_data.push_back(hashed_words);
				}
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
		}
		return hashed_data;
	}


	void read_through_every_line_into_memory(void (*function)(string) = NULL){
		string line;
		ifstream file(filename);
		if (file.is_open()){
			while (getline(file, line)){
				if (function){
					function(line);
				}
				vector<string> words = split(line, " ");
				data.push_back(words);
			}
			file.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
		}
	}

	vector<vector<string>> get_data(){
		return data;
	}




private:
	string filename;
	vector<vector<string>> data;
};



#endif /*__PREPROCCESS_CLASS_H__*/
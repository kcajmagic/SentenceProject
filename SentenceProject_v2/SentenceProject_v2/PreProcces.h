// PreProccess.h
// Jack Murdock

#ifndef __PREPROCCESS_CLASS_H__
#define __PREPROCCESS_CLASS_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>

#include "Sentence.h"
#include "WordHasher.h"

using namespace std;

std::string& trim_right_inplace(
	std::string&       s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	return s.erase(s.find_last_not_of(delimiters) + 1);
}

std::string& trim_left_inplace(
	std::string&       s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	return s.erase(0, s.find_first_not_of(delimiters));
}

std::string& trim(
	std::string&       s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	return trim_left_inplace(trim_right_inplace(s, delimiters), delimiters);
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


tuple<vector<string>, uint32_t, uint32_t> read_into_memory_and_count_unique(string& filename) {
	vector<string> data;
	string line;
	unordered_map<string, uint32_t> word_mapping;
	uint32_t number_of_unique_lines = 0;
	uint32_t number_of_same_lines = 0;
	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, line)) {
			//cout << "TEST" << endl;
			trim(line);
			if (line.size() > 0) {
				unordered_map<string, uint32_t>::const_iterator got = word_mapping.find(line);
				if (got == word_mapping.end()) {
					//cout << "Not Found" << endl;
					// Not Found
					number_of_unique_lines++;
					word_mapping[line] = 1;
					data.push_back(line);
				}
				else {
					word_mapping[line]++;
					number_of_same_lines++;
				}
			}

		}
		file.close();
		return make_tuple(data, number_of_same_lines, number_of_unique_lines);
	}
	else {
		cout << "Unable to open file: " << filename << endl;
		throw 0;
	}
}


vector<Sentence> read_lines_into_memory_and_remove_dublicates(string& filename, WordHasher& hasher) {
	string line;
	ifstream file(filename);

	vector<Sentence> file_data;
	unordered_map<string, bool> word_mapping;
	if (file.is_open()) {
		while (getline(file, line)) {
			trim(line);
			if (line.size() > 0) {
				vector<string> words = split(line, " ");
				vector<uint32_t> hashed_words;
				for each (string word in words)
				{
					hashed_words.push_back(hasher.get_next_value(word));
				}

				Sentence sentence_line(hashed_words);

				if (word_mapping.find(line) == word_mapping.end()) {
					//cout << "Not Found" << endl;
					// Not Found
					word_mapping[line] = true;
				file_data.push_back(sentence_line);
				}
				else {
					// Do Nothing it is a dublicate
				}

				//auto it = find_if(file_data.begin(), file_data.end(), [&hashed_words](Sentence& obj) { return obj.sentence() == hashed_words; });
				//if (it == file_data.end()) {
				//	// Not found
				//	
				//}
				//if (find(file_data.begin(), file_data.end(), sentence_line) == file_data.end()) {
				//	// Not Found
				//	file_data.push_back(sentence_line);
				//}
			}
		}
		file.close();
		return file_data;
	}
	else {
		cout << "Unable to open file: " << filename << endl;
		throw 0;
	}
}




#endif /*__PREPROCCESS_CLASS_H__*/
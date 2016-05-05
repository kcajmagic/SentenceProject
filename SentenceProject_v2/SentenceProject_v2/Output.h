// Output.h
// Jack Murdock

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <fstream>
#include <vector>
#include <string>

#include "Sentence.h"
#include "WordHasher.h"

using namespace std;

void write_lines(vector<Sentence>& data, unsigned int n, string filename, WordHasher& hasher) {
	ofstream myfile(filename);
	if (myfile.is_open()) {
		for each (Sentence line in data)
		{
			if (line.get_times_seen() == 0) {
				for each (uint32_t val in line.sentence())
				{
					myfile << hasher.get_word_from_value(val) << " ";
				}
				myfile << endl;
			}
		}
		myfile.close();
	}
}


void write_lines(vector<string>& data, unsigned int n, string filename) {
	ofstream myfile(filename);
	if (myfile.is_open()) {
		for each (string line in data)
		{
			myfile << line << endl;
		}
		myfile.close();
	}
}

#endif // !__OUTPUT_H__

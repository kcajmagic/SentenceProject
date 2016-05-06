// main.cpp
// Jack Murdock
//
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <tuple>

#include "Timer.h"
#include "PreProcces.h"
#include "Procces.h"
#include "WordHasher.h"
#include "DamerauLevenshtein.h"
#include "MergeSort.h"
#include "Output.h"
#include "ThreadPool.h"

using namespace std;
using nbsdx::concurrent::ThreadPool;

int main(int argc, char** argv) {

	vector<string> filenames;
	vector<int> distances;
	string input_filename = "0";
	short val;
	int input_distance = 0;
	unsigned number = 0;
	bool output_file;
	
	cout << "output the file 0(do nothing) or 1(write file) ";
	cin >> val;
	output_file = (val == 0) ? false : true;
	cout << "What files shall we work with? (use 'done' to stop)  ";
	while (input_filename != "done") {
		cin >> input_filename;
		if (input_filename != "done") {
			filenames.push_back(input_filename);
		}
	}

	cout << "What number of distance do you want to know? (use '-1' to stop) ";
	while (input_distance != -1) {
		cin >> input_distance;
		if (input_distance != -1) {
			distances.push_back(input_distance);
		}
	}


	Timer mainTimer = Timer();
	cout << endl;

	for each(string filename in filenames) {
		for each (int distance in distances) {
			cout << "Starting File " << filename << endl;
			WordHasher hasher;

			vector<string> lines;
			vector<Sentence> data;
			uint32_t result = 0;

			mainTimer.startTimer();
			// Begin Computation Block
			if (distance == 0) {
				// Distance 0
				tuple<vector<string>, uint32_t, uint32_t> response = read_into_memory_and_count_unique(filename);
				lines = get<0>(response);
				result = get<1>(response);

			}
			else {
				// Distance n > 0
				data = read_lines_into_memory_and_remove_dublicates(filename, hasher);
				cout << "Completed Reading" << endl;
				merge_sort(data, 0, data.size() - 1);
				cout << "Completed Sorting" << endl;

				//cout << "Size "<< data.size() << endl;
				result = compare(data, distance);
	
			}

			// End Computation Block
			mainTimer.stopTimer();
			

			if (output_file) {
				cout << "Now to write file";
				if (distance == 0) {
					write_lines(lines, distance, (to_string(distance) + "_at_" + filename));
					result = lines.size();
				}
				else {
					write_lines(data, distance, (to_string(distance) + "_at_" + filename), hasher);
					cout << "Data Lines " << data.size() << " " << result << endl ;
					result = data.size() - result;

				}
			}
			cout << "File: " << filename << "  Comparing at Distance " << distance << endl << "Output lines: " << result << " |-Time-> " << mainTimer.get_time() << endl << endl << endl;

		}
	}


	return 0;
}
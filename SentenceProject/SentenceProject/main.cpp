// main.cpp
// Jack Murdock
//
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "Timer.h"
#include "PreProcces.h"
#include "Procces.h"
#include "WordHasher.h"
#include "Uniqueness.h"
#include "DamerauLevenshtein.h"
#include "MergeSort.h"

using namespace std;

ostream &operator<<(ostream &output, const vector<vector<uint32_t>> T){
	for each (vector<uint32_t> row in T)
	{
		for each(uint32_t data in row){
			output << data << " ";
		}
		output << endl;
	}
	return output;
}


void print(vector<uint32_t> vector){
	cout << "B";
	for (int i = 0; i < vector.size(); i++){
		cout << " -> " << vector[i];
	}
	cout << " SIZE: " << vector.size() << endl;
}

void print(vector<string> vector){
	cout << "";
	for (int i = 0; i < vector.size(); i++){
		cout << vector[i];
	}
	//cout << " -> SIZE: " << vector.size() << endl;
}

int main(int argc, char** argv) {
	
	vector<string> filenames;
	vector<int> distances;
	string input_filename = "0";
	short val;
	int input_distance = 0;
	bool output_file;
	cout << "output the file 0(do nothing) or 1(write file) " ;
	cin >> val;
	output_file = (val == 0) ? false : true;
	cout << "What files shall we work with? (use 'done' to stop)  ";
	while (input_filename != "done") {
		cin >> input_filename;
		if (input_filename != "done") {
			filenames.push_back(input_filename);
		}
	}
	
	cout << "What number of distance do you want to know? (use '-1' to stop ";
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
			Uniqueness counter;
			PreProcces preprocces = PreProcces(filename);
			unordered_map<vector<uint32_t>, unsigned int> kv_store;

			uint32_t result = 0;

			mainTimer.startTimer();
			// Begin Computation Block
			if (distance == 0) {
				preprocces.read_and_count_unique(&counter);
				result = counter.get_similualre_lines();
			}
			else {
			
				vector<vector<uint32_t>> data = preprocces.read_through_lines_and_hash_and_generate_thing(kv_store);
				cout << "Completed Reading" << endl;
				merge_sort(data, 0, data.size() - 1);
				cout << "Completed Sorting" << endl;
				//result = testting(data, 1);
				//result = find_distance_one_with_sorted_data(data, 1);
				result = compare_with_kv_data(data, 1, kv_store);

			}

			// End Computation Block
			mainTimer.stopTimer();

			if (output_file) {
				if (distance == 0) {
					write_distance_n_lines(counter.get_data(), distance, (to_string(distance) + "_at_" + filename));
				}
				else {
					write_distance_n_lines(kv_store, distance, (to_string(distance) + "_at_" + filename));

				}
			}
			cout << "File: " << filename << "  Comparing at Distance " << distance << endl << "Result: " << result << " |-Time-> " << mainTimer.get_time() << endl << endl << endl;
		}
	}
	//	cout << mainTimer << endl;

	return 0;
}
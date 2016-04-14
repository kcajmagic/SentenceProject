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
	
	
	string filename;
	int distance;
	cout << "What file shall we work with?  ";
	cin >> filename;
	cout << "What number of distance do you want to know? ";
	cin >> distance;


	Timer mainTimer = Timer();

	while (filename != "0") {
		WordHasher hasher;
		Uniqueness counter;
		PreProcces preprocces = PreProcces(filename);

		uint32_t result = 0;

		mainTimer.startTimer();
		// Begin Computation Block
		if (distance == 0) {
			preprocces.read_and_count_unique(&counter);
			result = counter.get_similualre_lines();
		}
		else {
			vector<vector<uint32_t>> data = preprocces.read_through_lines_and_hash();
			cout << "Completed Reading" << endl;
			merge_sort(data, 0, data.size() - 1);
			cout << "Completed Sorting" << endl;
			result = find_distance_one_with_sorted_data(data, 1);

		}

		// End Computation Block
		mainTimer.stopTimer();
		cout << "File: " << filename << "  Comparing at Distance " << distance << endl << "Result: " << result << " |-Time-> " << mainTimer.get_time() << endl;
	
		cout << "What file shall we work with? (0 to end)  ";
		cin >> filename;
		cout << "What number of distance do you want to know? ";
		cin >> distance;


	}
	//	cout << mainTimer << endl;

	return 0;
}
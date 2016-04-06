// main.cpp
// Jack Murdock
//
//

#include <iostream>
#include <string>
#include <vector>
#include "Timer.h"
#include "PreProcces.h"
#include "WordHasher.h"
#include "Uniqueness.h"
#include "DamerauLevenshtein.h"
#include "MergeSort.h"

using namespace std;
ostream &operator<<(ostream &output, const vector<vector<unsigned long long>> T){
	for each (vector<unsigned long long> row in T)
	{
		for each(unsigned long long data in row){
			output << data << " ";
		}
		output << endl;
	}
	return output;
}


void print(vector<unsigned long long> vector){
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

int main(int argc, char** argv){
	WordHasher hasher;
	Uniqueness counter;
	string filename;
	cout << "What file shall we work with?  ";
	cin >> filename;
	PreProcces preprocces = PreProcces(filename);




	Timer mainTimer = Timer();
	mainTimer.startTimer();
	// Begin Computation Block
	vector<vector<unsigned long long>> data = preprocces.read_through_lines_and_hash();
	cout << "Before: " << endl << data << endl;
	merge_sort(data, 0, data.size()-1);

	cout << "After" << endl << data << endl;

	for (int i = 0; i < data.size(); i++){
		for (int j = i + 1; j < data.size();j++){
			//cout << i << " " << j << " " << data[i][0] << " " << data[j][0] << endl;
			print(data[i]);
			print(data[j]);
			cout << endl << endl << "Distance between \"";
			print(preprocces.get_data()[i]);
			cout << "\' and \'";
			print(preprocces.get_data()[j]);
			cout << "\' is " << damerau_levenshtein_algorithm(data[i], data[j]) << endl;
		}
	}
	


	// End Computation Block
	mainTimer.stopTimer();
	cout << "Unique Lines: " << counter.get_uniqueness() << endl;
	cout << "Distance 0 \t\t | Distance 1 \t\t | Time " << endl;
	cout << "\t" << counter.get_similualre_lines() << "\t\t | " << "   Unknown  \t\t |  " << mainTimer.get_time() << endl;
//	cout << mainTimer << endl;

	return 0;
}
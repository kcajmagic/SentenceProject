// Proccess.h
// Jack Murdock

#ifndef __PROCCESS_CLASS_H__
#define __PROCCESS_CLASS_H__
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>

#include "DamerauLevenshtein.h"

using namespace std;

ostream &operator<<(ostream &output, const vector<unsigned long long> vector) {
	output << "B";
	for (int i = 0; i < vector.size(); i++) {
		cout << " -> " << vector[i];
	}
	output << " SIZE: " << vector.size() << endl;

	return output;
}

void compare(vector<vector<unsigned long long>>& data, unsigned long lower_index, unsigned long higher_index, vector<unsigned long long>& result, unsigned int n, vector<bool>& thread_status) {
	unsigned long long count = 0;
	thread_status.push_back(true);
	//  cout << "************** Thread " << thread_status.size() << " | " << lower_index << " <-> " << higher_index << " |---> Size " << data.size() << " n " << n << endl;
	for (int i = lower_index; i <= higher_index; i++) {
		for (int j = i + 1; j <= higher_index; j++) {
			//cout << "I: " << data[i];
			//cout << "J: " << data[j] << endl;
			unsigned long long value = damerauLevenshteinDistance(data[i], data[j]);

			if (value == n) {
				count++;
			}
		}
	}
	result.push_back(count);
	thread_status.pop_back();
}


unsigned long long find_distance_one_with_sorted_data(vector<vector<unsigned long long>>& data, unsigned int n){
	bool new_section = true;
	bool found = false;
	unsigned long lowest_size = 0;
	unsigned long lowest_index = 0;
	unsigned long highest_size = 0;
	unsigned long highest_index = 0;
	unsigned long next_index = 0;
	unsigned long next_size = 0;
	vector<bool> thread_status;
	vector<unsigned long long> result;
	

	unsigned long count = 0;
	for (int i = 0; i < data.size(); i++) {
		for (int j = i + 1; j < data.size(); j++) {
			//cout << i << "-" << j << " ";
			unsigned long long value = damerauLevenshteinDistance(data[i], data[j]);
			//cout << value << endl;
			//cout << "I: " << data[i];
			//cout << "J: " << data[j] << endl;

			if (value == n) {
				count++;
			}
		}
	}

	//cout << endl << endl << "Long Way "<< count << endl << endl;

	//cout << "Begin: " << data.size() << " N: " << n << endl;
	for (unsigned long i = 0; i < data.size(); i++) {

		if (new_section) {
			lowest_size = data[i].size();
			lowest_index = i;
			highest_size = lowest_size + 2 * n;
			next_size = highest_size;
			new_section = false;
			found = false;
			//cout << "New: " << i << "-"<<data[i].size() << " L_S " << lowest_size << " H_S " << highest_size << "  N_S " << next_size << " N_I " << next_index << endl;
		}
		else{
			//cout << "          " << i << "-" << data[i].size() << " L_I " << lowest_index << " L_S " << lowest_size << " H_I " << highest_index << " H_S " << highest_size << "  N_S " << next_size << " N_I " << next_index << endl;
		}

	
		if (data[i].size() >= next_size && !found){
			//cout << " ********* FOUND ************ I: " << i << " Size "<< data[i].size() << endl;
			next_index = i;
			found = true;
		}
		// cout << "L_I " << lowest_index << " L_S " << lowest_size << " H_I " << highest_index << " H_S " << highest_size << "  N_S " << next_size << " N_I " << next_index << endl;
		if (data[i].size() <= highest_size && i < data.size() - 1 ) {
			// cout << "Increase High " << i << endl;
			highest_index = i;
		}
		else {
			if (i == data.size() - 1) {
				highest_index = i;
			}
			else{
				i = next_index - 1;
				new_section = true;
			}
			//cout << "|----------> Starting Thread: " << lowest_index << " " << highest_index << endl;
	
			//compare(data, lowest_index, highest_index, result, n, thread_status);
			thread compareThread(compare, ref(data), lowest_index, highest_index, ref(result), n, ref(thread_status));
			if (compareThread.joinable()) {
				compareThread.join();
			}
			else {
				cout << "Unable to Join";
			}

		}

	}
	while (thread_status.size() > 0) {
		// cout <<"Thread Satus" << thread_status.size();
		// do nothing
	}
	unsigned long long count_result = 0;
	for each (unsigned long long status in result)
	{
		count_result += status;
		// cout << status << " asdf" << endl;
	}

	return count_result;
}

#endif /*__PROCCESS_CLASS_H__*/
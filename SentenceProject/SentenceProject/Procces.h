// Proccess.h
// Jack Murdock

#ifndef __PROCCESS_CLASS_H__
#define __PROCCESS_CLASS_H__
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>
#include <mutex>

#include "DamerauLevenshtein.h"

using namespace std;

mutex mtx;
mutex lock_store;


void write_distance_n_lines(unordered_map<string, unsigned int>& data, unsigned int n, string filename) {
	ofstream myfile(filename);
	if (myfile.is_open()) {
		for (const auto& kv : data) {
			if (kv.second == n + 1) {
				myfile << kv.first<<endl;
			}
		}
		myfile.close();
	}
}

void write_distance_n_lines(unordered_map<vector<uint32_t>, unsigned int>& data, unsigned int n, string filename) {
	ofstream myfile(filename);
	if (myfile.is_open()) {
		for (const auto& kv : data) {
			if (kv.second == n + 1) {
				myfile << kv.first << endl;
			}
		}
		myfile.close();
	}
}

bool should_compare(vector<vector<uint32_t>>& data, uint32_t v1, uint32_t v2, unsigned int n) {
	int not_right = 0;

	for (unsigned int i = 0; i < min(data[v1].size(), data[v2].size()); i++) {
		if (data[v1][i] != data[v2][i]) {
			not_right++;
		}
		if (not_right > n) {
			return false;
		}
	}
	return true;
}


ostream &operator<<(ostream &output, const vector<uint32_t> vector) {
	output << "B";
	for (int i = 0; i < vector.size(); i++) {
		cout << " -> " << vector[i];
	}
	output << " SIZE: " << vector.size() << endl;

	return output;
}




void compare_one_size_to_other_with_store(vector<vector<uint32_t>>& data, uint32_t low_lower_index, 
	uint32_t low_higher_index, uint32_t high_higher_index, vector<uint32_t>& result, unsigned int n, 
	unordered_map<vector<uint32_t>, unsigned int>& kv_store) {

	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << low_lower_index << ", " << low_higher_index << " <-> " << (low_higher_index +1) << ", " << high_higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;

	for (unsigned int i = low_lower_index; i <= low_higher_index; i++) {
		for (unsigned int j = low_higher_index + 1; j <= high_higher_index; j++) {
			//mtx.lock();
			//cout << "Multipe Size " << i << " - " << j << endl;
			///*cout << "I: " << data[i];
			//cout << "J: " << data[j] << endl;*/
			//mtx.unlock();
			if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i], data[j]);
			}

			if (value == n) {
				lock_store.lock();
				kv_store[data[i]]++;
				lock_store.unlock();
				count++;
			}
		}
	}
	mtx.lock();
	result.push_back(count);
	mtx.unlock();
}

void compare_with_store(vector<vector<uint32_t>>& data, uint32_t lower_index, uint32_t higher_index, vector<uint32_t>& result, unsigned int n, uint32_t index,
	unordered_map<vector<uint32_t>, unsigned int>& kv_store) {
	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << lower_index << " <-> " << higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;
	for (int i = lower_index; i <= higher_index; i++) {
		for (int j = i + 1; j <= higher_index; j++) {

			//mtx.lock();
			//cout << "Compare " << i << " - " << j << endl;
			////cout << "I: " << data[i];
			////cout << "J: " << data[j] << endl;
			//mtx.unlock();
			if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i], data[j]);
			}

			if (value == n) {
				lock_store.lock();
				kv_store[data[i]]++;
				lock_store.unlock();
				count++;
			}
		}
	}
	result.push_back(count);
	//cout << "Ending Thread: " << index << endl;
}







void compare_one_size_to_other(vector<vector<uint32_t>>& data, uint32_t low_lower_index, uint32_t low_higher_index, uint32_t high_higher_index, vector<uint32_t>& result, unsigned int n) {
	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << low_lower_index << ", " << low_higher_index << " <-> " << (low_higher_index +1) << ", " << high_higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;

	for (unsigned int i = low_lower_index; i <= low_higher_index; i++) {
		for (unsigned int j = low_higher_index + 1; j <= high_higher_index; j++) {
			//mtx.lock();
			//cout << "Multipe Size " << i << " - " << j << endl;
			///*cout << "I: " << data[i];
			//cout << "J: " << data[j] << endl;*/
			//mtx.unlock();
			if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i], data[j]);
			}

			if (value == n) {
				count++;
			}
		}
	}
	mtx.lock();
	result.push_back(count);
	mtx.unlock();
}

void compare(vector<vector<uint32_t>>& data, uint32_t lower_index, uint32_t higher_index, vector<uint32_t>& result, unsigned int n, uint32_t index) {
	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << lower_index << " <-> " << higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;
	for (int i = lower_index; i <= higher_index; i++) {
		for (int j = i + 1; j <= higher_index; j++) {
	
			//mtx.lock();
			//cout << "Compare " << i << " - " << j << endl;
			////cout << "I: " << data[i];
			////cout << "J: " << data[j] << endl;
			//mtx.unlock();
			if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i], data[j]);
			}

			if (value == n) {
				count++;
			}
		}
	}
	mtx.lock();
	result.push_back(count);
	mtx.unlock();
	//cout << "Ending Thread: " << index << endl;
}

uint32_t testting(vector<vector<uint32_t>>& data, unsigned int n) {
	vector<thread> comparingMultiple;
	uint32_t low_index = 0;
	uint32_t low_size = 0;
	uint32_t high_index = 0;
	vector<uint32_t> result;

	for (uint32_t i = 0; i < data.size(); i++) {
		if (low_size == 0) {
			low_index = i;
			low_size = data[i].size();
		}

		if (data[i].size() == low_size) {
			high_index = i;
		}
		else {
			thread compareThread(compare, ref(data), low_index, high_index, ref(result), n, i);
			comparingMultiple.push_back(move(compareThread));
			
			low_index = i;
			low_size = data[i].size();

		}
	}

	bool newSection = true;
	bool found = false;
	uint32_t low_high_index = 0;
	uint32_t high_size = 0;
	uint32_t next_index = 0;
	uint32_t next_size = 0;
	high_index = 0;

	for (uint32_t i = 0; i < data.size(); i++) {
		//mtx.lock();
		//cout << "ASDFASDF  " << i << endl;
		//mtx.unlock();
		if (newSection) {
			//mtx.lock();
			//cout << "SECTION  " << i << endl;
			//mtx.unlock();
			low_size = data[i].size();
			low_index = i;
			high_size = low_size + n;
			next_size = low_size + n;
			found = false;
			newSection = false; 
		}


		if (data[i].size() >= next_size && !found) {
	/*		mtx.lock();
			cout << "Found "<< endl;
			mtx.unlock();*/

			next_index = i;
			found = true;
		}

		if (data[i].size() == low_size) {
			low_high_index = i;
		}

		//mtx.lock();
		//cout << "L_I " << low_index << "L_H_I " << low_high_index << " L_S " << low_size << " H_I " << high_index << " H_S " << high_size << "  N_S " << next_size << " N_I " << next_index << "               " << endl;
		//mtx.unlock();

		if (data[i].size() <= high_size && i < data.size() - 1) {
	
			high_index = i;
		}
		else {
			if (i == data.size() - 1) {
				high_index = i;
			}
			else {
				i = next_index - 1;
				newSection = true;
			}

		/*	mtx.lock();
			cout << "Thread  L_I " << low_index << "  L_H_I " << low_high_index << " H_I  " << high_index << endl;
			mtx.unlock();
*/
			thread compareThread(compare_one_size_to_other, ref(data), low_index, low_high_index, high_index, ref(result), n);
			comparingMultiple.push_back(move(compareThread));

		}
	
	}

	// Finish all threads
	for (int i = 0; i < comparingMultiple.size(); i++) {
		if (comparingMultiple[i].joinable()) {
			comparingMultiple[i].join();
		}
		else {
			cout << "IDK" << endl;
		}
	}

	uint32_t count_result = 0;
	for each (uint32_t status in result)
	{
		count_result += status;
	}

	return count_result;
}


uint32_t compare_with_kv_data(vector<vector<uint32_t>>& data, unsigned int n, unordered_map<vector<uint32_t>, unsigned int>& kv_store) {
	vector<thread> comparingMultiple;
	uint32_t low_index = 0;
	uint32_t low_size = 0;
	uint32_t high_index = 0;
	vector<uint32_t> result;

	for (uint32_t i = 0; i < data.size(); i++) {
		if (low_size == 0) {
			low_index = i;
			low_size = data[i].size();
		}

		if (data[i].size() == low_size) {
			high_index = i;
		}
		else {
			thread compareThread(compare_with_kv_data, ref(data), low_index, high_index, ref(result), n, i, ref(kv_store));
			comparingMultiple.push_back(move(compareThread));

			low_index = i;
			low_size = data[i].size();

		}
	}

	bool newSection = true;
	bool found = false;
	uint32_t low_high_index = 0;
	uint32_t high_size = 0;
	uint32_t next_index = 0;
	uint32_t next_size = 0;
	high_index = 0;

	for (uint32_t i = 0; i < data.size(); i++) {
		//mtx.lock();
		//cout << "ASDFASDF  " << i << endl;
		//mtx.unlock();
		if (newSection) {
			//mtx.lock();
			//cout << "SECTION  " << i << endl;
			//mtx.unlock();
			low_size = data[i].size();
			low_index = i;
			high_size = low_size + n;
			next_size = low_size + n;
			found = false;
			newSection = false;
		}


		if (data[i].size() >= next_size && !found) {
			/*		mtx.lock();
			cout << "Found "<< endl;
			mtx.unlock();*/

			next_index = i;
			found = true;
		}

		if (data[i].size() == low_size) {
			low_high_index = i;
		}

		//mtx.lock();
		//cout << "L_I " << low_index << "L_H_I " << low_high_index << " L_S " << low_size << " H_I " << high_index << " H_S " << high_size << "  N_S " << next_size << " N_I " << next_index << "               " << endl;
		//mtx.unlock();

		if (data[i].size() <= high_size && i < data.size() - 1) {

			high_index = i;
		}
		else {
			if (i == data.size() - 1) {
				high_index = i;
			}
			else {
				i = next_index - 1;
				newSection = true;
			}

			/*	mtx.lock();
			cout << "Thread  L_I " << low_index << "  L_H_I " << low_high_index << " H_I  " << high_index << endl;
			mtx.unlock();
			*/
			thread compareThread(compare_one_size_to_other_with_store, ref(data), low_index, low_high_index, high_index, ref(result), n, ref(kv_store));
			comparingMultiple.push_back(move(compareThread));

		}

	}

	// Finish all threads
	for (int i = 0; i < comparingMultiple.size(); i++) {
		if (comparingMultiple[i].joinable()) {
			comparingMultiple[i].join();
		}
		else {
			cout << "IDK" << endl;
		}
	}

	uint32_t count_result = 0;
	for each (uint32_t status in result)
	{
		count_result += status;
	}

	return count_result;
}



uint32_t find_distance_with_sorted_data_with_more_threads(vector<vector<uint32_t>>& data, unsigned int n) {
	vector<thread> comparingMultiple; 
	bool new_section = true;
	bool found = false;
	bool started_compare_of_same_size = false;
	bool begin_low_started = false;
	uint32_t lowest_size = 0;
	uint32_t lowest_index = 0;
	uint32_t lowest_high_index = 0;
	uint32_t same_size_index = 0;
	uint32_t highest_size = 0;
	uint32_t highest_index = 0;
	uint32_t next_index = 0;
	uint32_t next_size = 0;
	uint32_t l_index = 0;
	uint32_t l_size = 0;
	uint32_t l_h_index = 0;
	vector<uint32_t> result;

	for (uint32_t i = 0; i < data.size(); i++) {
		//cout << endl << " Loop " << i;
		if (new_section) {
			//cout << " New Section ****  ";
			lowest_size = data[i].size();
			lowest_index = i;
			l_index = i;
			l_size = data[i].size();
			next_size = lowest_size + 1;
			highest_size = lowest_size + n;
			new_section = false;
			found = false;
		}

		if (data[i].size() >= next_size && !found) {
			//cout << " found    ";
			next_index = i;
			found = true;
		}

		if (data[i].size() == lowest_size) {
			lowest_high_index = i;
		}

		if (started_compare_of_same_size && begin_low_started) {
			l_index = i;
			l_size = data[i].size();
			begin_low_started = false;
		}

		if (data[i].size() == l_size) {
			l_h_index = i;
		}
		else {
			if (i == data.size() - 1) {
				l_h_index = i;
			}
			//cout << "   starting compare  ";
			started_compare_of_same_size = true;
			begin_low_started = true;
			thread compareThread(compare, ref(data), l_index, l_h_index, ref(result), n, i);
			comparingMultiple.push_back(move(compareThread));
			l_index = i;
			l_size = data[i].size();
		}

		// cout << "L_I " << lowest_index << " L_S " << lowest_size << " H_I " << highest_index << " H_S " << highest_size << "  N_S " << next_size << " N_I " << next_index << "               ";


		if (data[i].size() <= highest_size && i < data.size() - 1) {
			//cout << " increase high ";
			highest_index = i;
		}
		else {
			if (i == data.size() - 1) {
				highest_index = i;
				thread compareThread(compare, ref(data), l_index, i, ref(result), n, i);
				comparingMultiple.push_back(move(compareThread));
			}
			//else {
			//	//cout << " at end ";
			//	i = next_index - 1;
			//	new_section = true;
			//}

			new_section = true;
			thread compareThread(compare_one_size_to_other, ref(data), lowest_index, lowest_high_index, highest_index, ref(result), n);
			comparingMultiple.push_back(move(compareThread));
			
		}


	}

	// Finish all threads
	for (int i = 0; i < comparingMultiple.size(); i++) {
		if (comparingMultiple[i].joinable()) {
			comparingMultiple[i].join();
		}
		else {
			cout << "IDK" << endl;
		}
	}

	uint32_t count_result = 0;
	for each (uint32_t status in result)
	{
		count_result += status;
	}

	return count_result;
}

uint32_t find_distance_one_with_sorted_data(vector<vector<uint32_t>>& data, unsigned int n){
	bool new_section = true;
	bool found = false;
	uint32_t lowest_size = 0;
	uint32_t lowest_index = 0;
	uint32_t highest_size = 0;
	uint32_t highest_index = 0;
	uint32_t next_index = 0;
	uint32_t next_size = 0;
	vector<uint32_t> result;
	vector<thread> comparingMultiple;
	

	//uint32_t count = 0;
	//for (int i = 0; i < data.size(); i++) {
	//	for (int j = i + 1; j < data.size(); j++) {
	//		//cout << i << "-" << j << " ";
	//		uint32_t value = damerauLevenshteinDistance(data[i], data[j]);
	//		//cout << value << endl;
	//		//cout << "I: " << data[i];
	//		//cout << "J: " << data[j] << endl;

	//		if (value == n) {
	//			count++;
	//		}
	//	}
	//}

	//cout << endl << endl << "Long Way "<< count << endl << endl;

	//cout << "Begin: " << data.size() << " N: " << n << endl;
	for (uint32_t i = 0; i < data.size(); i++) {

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
			thread compareThread(compare, ref(data), lowest_index, highest_index, ref(result), n, i);
			comparingMultiple.push_back(move(compareThread));
			/*	if (compareThread.joinable()) {
				compareThread.join();
			}
			else {
				cout << "Unable to Join";
			}
			Sleep(100000);*/

		}

	}

	for (int i = 0; i < comparingMultiple.size(); i++) {
		if (comparingMultiple[i].joinable()) {
			comparingMultiple[i].join();
		}
		else {
			cout << "IDK" << endl;
		}
	}

	uint32_t count_result = 0;
	for each (uint32_t status in result)
	{
		count_result += status;
		// cout << status << " asdf" << endl;
	}

	return count_result;
}

#endif /*__PROCCESS_CLASS_H__*/
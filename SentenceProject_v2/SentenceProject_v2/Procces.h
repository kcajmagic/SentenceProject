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
#include <string>

#include "DamerauLevenshtein.h"
#include "Sentence.h"
#include "ThreadPool.h"


using namespace std;
using nbsdx::concurrent::ThreadPool;

mutex mtx;
mutex lock_store;

bool should_compare(vector<Sentence>& data, uint32_t v1, uint32_t v2, unsigned int n) {
	int not_right = 0;

	for (unsigned int i = 0; i < min(data[v1].size(), data[v2].size()); i++) {
		/*mtx.lock();
		cout << "Compare " << data[v1][i] << " vs " << data[v2][i]<< endl;
		mtx.unlock();*/
		if (data[v1][i] != data[v2][i]) {
	/*		mtx.lock();
			cout << "Wrong" << endl;
			mtx.unlock();*/
			not_right++;
		}
		if (not_right > n) {
		/*	mtx.lock();
			cout << "False Returned" << endl;
			mtx.unlock();*/
			return false;
		}
	}
	return true;
}


ostream &operator<<(ostream &output, const vector<uint32_t> vector) {
	for (int i = 0; i < vector.size(); i++) {
		output << " -> " << vector[i];
	}
	output << " SIZE: " << vector.size() << endl;

	return output;
}


void compare_one_size_to_other(vector<Sentence>& data, uint32_t low_lower_index,
	uint32_t low_higher_index, uint32_t high_higher_index, vector<uint32_t>& result, unsigned int n) {

	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << low_lower_index << ", " << low_higher_index << " <-> " << (low_higher_index +1) << ", " << high_higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;

	for (unsigned int i = low_lower_index; i <= low_higher_index; i++) {
		for (unsigned int j = low_higher_index + 1; j <= high_higher_index; j++) {
			//mtx.lock();
			//cout << "Compare " << i << " - " << j << endl;
			//cout << "I: " << data[i].sentence();
			//cout << "J: " << data[j].sentence() << endl;
			//mtx.unlock();
			if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i].sentence(), data[j].sentence());
			}
			/*else {
				value = -1;
			}*/
		/*	mtx.lock();
			cout << value << endl;
			mtx.unlock();*/
			if (value == n) {
				lock_store.lock();
				//cout << "Found" << endl;
				data[i].saw_sentence();
				lock_store.unlock();
				count++;
			}
		}
	}
	mtx.lock();
	result.push_back(count);
	mtx.unlock();
}

void compare_same_size(vector<Sentence>& data, uint32_t lower_index, uint32_t higher_index, vector<uint32_t>& result, unsigned int n, uint32_t index) {
	uint32_t count = 0;
	//mtx.lock();
	//cout << "************** Thread "<< " | " << lower_index << " <-> " << higher_index << " |---> Size " << data.size() << " n " << n << endl;
	//mtx.unlock();
	uint32_t value = 0;
	for (int i = lower_index; i <= higher_index; i++) {
		for (int j = i + 1; j <= higher_index; j++) {

			//mtx.lock();
			//cout << "Compare " << i << " - " << j << endl;
			//cout << "I: " << data[i].sentence();
			//cout << "J: " << data[j].sentence() << endl;
			//mtx.unlock();
			//if (should_compare(data, i, j, n)) {
				value = damerauLevenshteinDistance(data[i].sentence(), data[j].sentence());
			//}
			/*else {
				value = -1;
			}*/
			/*mtx.lock();
			cout << value << endl;
			mtx.unlock();*/
			if (value == n) {
				lock_store.lock();
				//cout << "Found" << endl;
				data[i].saw_sentence();
				lock_store.unlock();
				count++;
			}
		}
	}
	mtx.lock();
	result.push_back(count);
	mtx.unlock();
	//cout << "Ending Thread: " << index << endl;
}


uint32_t compare(vector<Sentence>& data, unsigned int n) {
	ThreadPool<MAX_THREADS> pool;
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
			/*thread compareThread(compare_with_store, ref(data), low_index, high_index, ref(result), n, i);
			comparingMultiple.push_back(move(compareThread));*/
			std::function<void()> doThing = [&] {
				compare_same_size(data, low_index, high_index, result, n, i);
			};
			pool.AddJob(doThing);
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
			//thread compareThread(compare_one_size_to_other_with_store, ref(data), low_index, low_high_index, high_index, ref(result), n);
			//comparingMultiple.push_back(move(compareThread));
			std::function<void()> doThing = [&] {
				compare_one_size_to_other(data, low_index, low_high_index, high_index, result, n);
			};
			pool.AddJob(doThing);

		}

	}

	// Finish all threads
	cout << "STOPPING" << endl;
	pool.JoinAll();
	//for (int i = 0; i < comparingMultiple.size(); i++) {
	//	if (comparingMultiple[i].joinable()) {
	//		comparingMultiple[i].join();
	//	}
	//	else {
	//		cout << "IDK" << endl;
	//	}
	//}

	uint32_t count_result = 0;
	for each (uint32_t status in result)
	{
		count_result += status;
	}

	return count_result;
}

#endif /*__PROCCESS_CLASS_H__*/
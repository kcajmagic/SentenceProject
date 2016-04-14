// DamerauLevenshtein.h
// Jack Murdock

#ifndef __DEAMERAULEVENSHTEIN_CLASS_H__
#define __DEAMERAULEVENSHTEIN_CLASS_H__
#include <vector>
#include <iterator>
#include <unordered_map>

#include "Matrix.h"


#define COST 1
#define SWAP_COST 2

using namespace std;

uint32_t damerauLevenshteinDistance(vector<uint32_t> source, vector<uint32_t> target){
	if (source.size() == 0){
		return target.size() * COST;
	}
	if (target.size() == 0){
		return source.size() * COST;
	}

	uint32_t m = source.size();
	uint32_t n = target.size();

	unordered_map<uint32_t, uint32_t> dictionary;
	/* For all i and j, d[i][j] holds the Damerau-Levenshtein distance
	* between the first i characters of s and the first j characters of t.
	* Note that the array has (m+1)x(n+1) values.
	*/
	Matrix d(m+1, n+1);
	for (uint32_t i = 0; i <= m; i++){
		d.at(i, 0) = i;
	}
	for (uint32_t j = 0; j <= n; j++){
		d.at(0, j) = j;
	}

	// Populate a dictionary with the alphabet of the two strings
	for (uint32_t i = 0; i < m; i++){
		dictionary[source[i]] = 0;
	}
	for (uint32_t j = 0; j < n; j++){
		dictionary[target[j]] = 0;
	}

	// Determine substring distances
	for (uint32_t i = 1; i <= m; i++){
		uint32_t db = 0;
		for (uint32_t j = 1; j <= n; j++){
			uint32_t i1 = dictionary[target[j - 1]];
			uint32_t j1 = db;
			uint32_t cost = 0;

			if (source[i - 1] == target[j - 1]){ // Subtract one to start at strings' index zero instead of index one
				db = j;
			}
			else{
				cost = 2;
			}
							// Insertion      Deletions
			d.at(i, j) = min(d.at(i, j-1) + 1, min(d.at(i-1, j) + 1, d.at(i-1, j-1)+cost));

			// Transposeition
			if (i1 > 0 && j1 > 0){
				d.at(i, j) = min(d.at(i, j), d.at(i1 - 1, j1 - 1) + (i - i1 - 1) + (j - j1 - 1) + 1);
			}

		}
		dictionary[source[i - 1]] = i;
	}
	return d.at(m, n);
}

uint32_t damerau_levenshtein_algorithm(vector<uint32_t> source, vector<uint32_t> target){
	
	if (source.size() == 0){
		return target.size() * COST;
	}
	if (target.size() == 0){
		return source.size() * COST;
	}

	uint32_t MAX_DISTANCE = source.size() + target.size();
	Matrix d(source.size() + 2, target.size() + 2);
	d.set_value(0, 0, MAX_DISTANCE);

	for (uint32_t i = 0; i <= source.size(); i++){
		d.set_value(i + 1, 1, i);
		d.set_value(i + 1, 0, INFINITY);
	}
	for (uint32_t j = 0; j <= target.size(); j++){
		d.set_value(1, j + 1, j);
		d.set_value(0, j + 1, INFINITY);
	}
	unordered_map<uint32_t, int> dictionary;
	vector<uint32_t> total;
	total.insert(total.end(), source.begin(), source.end());
	total.insert(total.end(), target.begin(), target.end());

	for each (uint32_t word in total)
	{
		unordered_map<uint32_t, int>::const_iterator got = dictionary.find(word);

		// if the diction done'st contain the source and the sentence
		if (got == dictionary.end()){
			// Not Found
			dictionary[word] = 0;
		}
	}

	for (uint32_t i = 1; i <= source.size(); i++){
		uint32_t DB = 0;
		for (uint32_t j = 1; j <= target.size(); j++){

			uint32_t k = dictionary[target[j - 1]];
			uint32_t li = DB;

			if (source[i - 1] == target[j - 1])
			{
				d.set_value(i + 1, j + 1, d.get_value(i, j));
				DB = j;
			}
			else
			{
				d.set_value(i + 1, j + 1, min(d.get_value(i, j), min(d.get_value(i+1, j), d.get_value(i, j+1)))+1);
			}
			d.set_value(i + 1, j + 1, min(d.get_value(i + 1, j + 1), d.get_value(k, li) + (i - k - 1) + 1 + (j - li - 1)));
		}

		dictionary[source[i - 1]] = i;
	}
	return d.get_value(source.size() + 1, target.size() + 1);
}


#endif /*__DEAMERAULEVENSHTEIN_CLASS_H__*/
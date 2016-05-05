// DamerauLevenshtein.h
// Jack Murdock

#ifndef __DEAMERAULEVENSHTEIN_CLASS_H__
#define __DEAMERAULEVENSHTEIN_CLASS_H__
#include <vector>
#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "Matrix.h"
#include "Sentence.h"


#define COST 1
#define SWAP_COST 2

using namespace std;




uint32_t damerauLevenshteinDistance(vector<uint32_t> source, vector<uint32_t> target) {
	if (source.size() == 0) {
		return target.size() * COST;
	}
	if (target.size() == 0) {
		return source.size() * COST;
	}

	uint32_t m = source.size();
	uint32_t n = target.size();

	unordered_map<uint32_t, uint32_t> dictionary;
	/* For all i and j, d[i][j] holds the Damerau-Levenshtein distance
	* between the first i characters of s and the first j characters of t.
	* Note that the array has (m+1)x(n+1) values.
	*/
	Matrix d(m + 1, n + 1);
	for (uint32_t i = 0; i <= m; i++) {
		d.at(i, 0) = i;
	}
	for (uint32_t j = 0; j <= n; j++) {
		d.at(0, j) = j;
	}

	// Populate a dictionary with the alphabet of the two strings
	for (uint32_t i = 0; i < m; i++) {
		dictionary[source[i]] = 0;
	}
	for (uint32_t j = 0; j < n; j++) {
		dictionary[target[j]] = 0;
	}

	// Determine substring distances
	for (uint32_t i = 1; i <= m; i++) {
		uint32_t db = 0;
		for (uint32_t j = 1; j <= n; j++) {
			uint32_t i1 = dictionary[target[j - 1]];
			uint32_t j1 = db;
			uint32_t cost = 0;

			if (source[i - 1] == target[j - 1]) { // Subtract one to start at strings' index zero instead of index one
				db = j;
			}
			else {
				cost = 2;
			}
			// Insertion      Deletions
			d.at(i, j) = min(d.at(i, j - 1) + 1, min(d.at(i - 1, j) + 1, d.at(i - 1, j - 1) + cost));

			// Transposeition
			if (i1 > 0 && j1 > 0) {
				d.at(i, j) = min(d.at(i, j), d.at(i1 - 1, j1 - 1) + (i - i1 - 1) + (j - j1 - 1) + 1);
			}

		}
		dictionary[source[i - 1]] = i;
	}
	return d.at(m, n);
}
#endif /*__DEAMERAULEVENSHTEIN_CLASS_H__*/
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


unsigned long long damerau_levenshtein_algorithm(vector<unsigned long long> source, vector<unsigned long long> target){
	
	if (source.size() == 0){
		return target.size() * COST;
	}
	if (target.size() == 0){
		return source.size() * COST;
	}

	unsigned long MAX_DISTANCE = source.size() + target.size();
	Matrix d(source.size() + 2, target.size() + 2);
	d.set_value(0, 0, MAX_DISTANCE);

	for (unsigned long i = 0; i <= source.size(); i++){
		d.set_value(i + 1, 1, i);
		d.set_value(i + 1, 0, INFINITY);
	}
	for (unsigned long j = 0; j <= target.size(); j++){
		d.set_value(1, j + 1, j);
		d.set_value(0, j + 1, INFINITY);
	}
	unordered_map<unsigned long long, int> dictionary;
	vector<unsigned long long> total;
	total.insert(total.end(), source.begin(), source.end());
	total.insert(total.end(), target.begin(), target.end());

	for each (unsigned long long word in total)
	{
		unordered_map<unsigned long long, int>::const_iterator got = dictionary.find(word);

		// if the diction done'st contain the source and the sentence
		if (got == dictionary.end()){
			// Not Found
			dictionary[word] = 0;
		}
	}

	for (unsigned long i = 1; i <= source.size(); i++){
		unsigned long long DB = 0;
		for (unsigned long j = 1; j <= target.size(); j++){

			unsigned long long k = dictionary[target[j - 1]];
			unsigned long long li = DB;

			if (source[i - 1] == target[j - 1])
			{
				d.set_value(i + 1, j + 1, d.get_value(i, j));
				DB = j;
			}
			else
			{
				d.set_value(i + 1, j + 1, min(d.get_value(i, j), min(d.get_value(i+1, j), d.get_value(i, j+1)))+2);
			}
			d.set_value(i + 1, j + 1, min(d.get_value(i + 1, j + 1), d.get_value(k, li) + (i - k - 1) + 1 + (j - li - 1)));
		}

		dictionary[source[i - 1]] = i;
	}
	return d.get_value(source.size() + 1, target.size() + 1);
}


#endif /*__DEAMERAULEVENSHTEIN_CLASS_H__*/
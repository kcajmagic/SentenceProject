// Sentence.h
// Jack Murdock

#ifndef __SENTENCE_CLASS_H__
#define __SENTENCE_CLASS_H__

#include <vector>
#include <string>

using namespace std;

class Sentence{
public:
	Sentence() {
		number_of_times_seen = 0;
	}

	Sentence(vector<uint32_t>& line) {
		hashed_sentence = line;
		number_of_times_seen = 0;
	}

	vector<uint32_t>& sentence() {
		return hashed_sentence;
	}

	unsigned int get_times_seen() {
		return number_of_times_seen;
	}

	void saw_sentence() {
		number_of_times_seen++;
	}

	uint32_t size() {
		return hashed_sentence.size();
	}

	//uint32_t operator [](uint32_t i) const {
	//	return hashed_sentence[i];
	//}
	uint32_t& operator [](uint32_t i) {
		return hashed_sentence[i];
	}

private:
	unsigned int number_of_times_seen;
	vector<uint32_t> hashed_sentence;
};

#endif // !__SENTENCE_CLASS_H__

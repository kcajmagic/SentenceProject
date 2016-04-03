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

using namespace std;

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
	preprocces.read_into_memory_and_count_unique(&counter);
	


	// End Computation Block
	mainTimer.stopTimer();
	cout << "Unique Lines: " << counter.get_uniqueness() << endl;
	cout << "Distance 0 \t\t | Distance 1 \t\t | Time " << endl;
	cout << "\t" << counter.get_similualre_lines() << "\t\t | " << "   Unknown  \t\t |" << mainTimer.get_time() << endl;
//	cout << mainTimer << endl;

	return 0;
}
// main.cpp
// Jack Murdock
//
//

#include <iostream>
#include "Timer.h"

using namespace std;

int main(int argc, char** argv){
	Timer mainTimer = Timer();
	mainTimer.startTimer();
	for (int i = 0; i < 100; i++){
		;
	}

	mainTimer.stopTimer();
	cout << mainTimer << endl;

	return 0;
}
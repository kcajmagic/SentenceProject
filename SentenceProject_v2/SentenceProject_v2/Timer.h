// Timer.h
// Jack Murdock

#ifndef __TIMER_CLASS_H__
#define __TIMER_CLASS_H__
#include "Clock.h"
#include <iostream>
#include <string>

using namespace std;

class Timer {
public:
	void startTimer() {
		this->begin_wall = get_wall_time();
		this->can_get_time = false;
	}
	void stopTimer() {
		this->can_get_time = true;
		this->end_wall = get_wall_time();
	}
	friend ostream &operator<<(ostream &output, const Timer &T) {
		if (T.can_get_time) {
			output << "Wall Time = " << (T.end_wall - T.begin_wall) << "s";
		}
		return output;
	}

	double get_time() {
		return (this->end_wall - this->begin_wall);
	}

private:
	double begin_wall;
	double end_wall;
	bool can_get_time;
};

#endif /*__TIMER_CLASS_H__*/
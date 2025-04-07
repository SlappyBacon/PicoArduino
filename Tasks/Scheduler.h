#ifndef PICO_SCHEDULER_H
#define PICO_SCHEDULER_H

#include <Arduino.h>
#include "Arduino-Lists/List.hpp"
#include "Task.h"

class Scheduler {
private:
	List<Task*> allTasks_;
public:
	unsigned int tryExecuteAll();
	void delayDeadTime();
	bool addTask(Task * task);
	bool removeTask(Task * task);
};


#endif



#include "Scheduler.h"

unsigned int Scheduler::tryExecuteAll() {
	unsigned int totalTasksExecuted = 0;

	for (int i = 0; i < allTasks_.getSize(); i++) {
		Task* task = allTasks_.get(i);
		bool didExecute = task->tryExecute();
		if (!didExecute) continue;
		totalTasksExecuted++;
	}

	return totalTasksExecuted;
}

void Scheduler::delayDeadTime() {

	bool foundOneActive = false;
	unsigned long nowMs = millis();
	unsigned long delayMs  = 4294967295UL;
	for (int i = 0; i < allTasks_.getSize(); i++) {
		Task* task = allTasks_.get(i);
		if (!task->getIsEnabled()) continue;
		
		unsigned long timeUntilTaskNextExecutionMs = task->getNextExecutionTimeMs() - nowMs;
		
		if (timeUntilTaskNextExecutionMs < 1 || timeUntilTaskNextExecutionMs > TASK_MAX_INTERVAL_MS) return;	//READY NOW

		Serial.print("Time until task ");
		Serial.print(task->getId());
		Serial.print(": ");
		Serial.print(timeUntilTaskNextExecutionMs);
		Serial.println("ms");

		//if now - lastTime < interval
		//then how much time is left until interval met

		if (delayMs <= timeUntilTaskNextExecutionMs) continue;

		delayMs = timeUntilTaskNextExecutionMs;

		foundOneActive = true;
	}

	if (!foundOneActive) return;

	Serial.print("DELAYING: ");
	Serial.print(delayMs);
	Serial.println("ms");

	delay(delayMs);

}

bool Scheduler::addTask(Task* task) {
	for (int i = 0; i < allTasks_.getSize(); i++) {
		Task* t = allTasks_.get(i);
		if (t->getId() == task->getId()) return false;
	}
	allTasks_.add(task);
	return true;
}
bool Scheduler::removeTask(Task* task) {
	for (int i = 0; i < allTasks_.getSize(); i++) {
		Task* t = allTasks_.get(i);
		if (t->getId() != task->getId()) continue;
		allTasks_.remove(i);
		return true;
	}
	return false;
}
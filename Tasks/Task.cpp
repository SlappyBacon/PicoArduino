#include "Task.h"

typedef void TaskAction();

Task::Task(TaskAction* aAction, long aExecutionCount, unsigned long aIntervalMs, bool aIsImmediate, bool aIsEnabled) {
	constrain(aIntervalMs, 0UL, TASK_MAX_INTERVAL_MS);
	id_ = nextTaskId++;
	action_ = aAction;
	executionCountRemaining_ = aExecutionCount;
	intervalMs_ = aIntervalMs;
	lastExecutionTimeMs_ = millis();
	if (aIsImmediate) lastExecutionTimeMs_ -= intervalMs_;
	isEnabled_ = aIsEnabled;
}
Task::~Task() {
	action_ = NULL;
	executionCountRemaining_ = 0;
	intervalMs_ = 0;
	lastExecutionTimeMs_ = 0;
	isEnabled_ = false;
}

bool Task::tryExecute() {
	if (!isReady()) return false;

	action_();

	if (0 < executionCountRemaining_) executionCountRemaining_--;

	lastExecutionTimeMs_ += intervalMs_;

	return true;
}

bool Task::isReady() {
	if (!action_) return false;	//No action to perform
	if (!isEnabled_) return false;	//Not enabled
	if (-1L < executionCountRemaining_ && executionCountRemaining_ < 1) return false;	//No executions left
	unsigned long ellapsedMs = millis() - lastExecutionTimeMs_;
	if (0UL < intervalMs_ && intervalMs_ > ellapsedMs) return false;	//Not time yet
	return true;
}
unsigned long Task::getId() {
	return id_;
}
void Task::setAction(TaskAction* newValue) {
	action_ = newValue;
}
void Task::setIsEnabled(bool newValue) {
	isEnabled_ = newValue;
	if (!isEnabled_) return;
}
bool Task::getIsEnabled() {
	return isEnabled_;
}
void Task::setExecutionCountRemaining(long newValue) {
	if (1 > executionCountRemaining_ && 0 < newValue) lastExecutionTimeMs_ = millis() - intervalMs_;
	executionCountRemaining_ = newValue;
}
long Task::getExecutionCountRemaining() {
	return executionCountRemaining_;
}
void Task::setIntervalMs(unsigned long newValue) {
	intervalMs_ = newValue;
}
unsigned long Task::getIntervalMs() {
	return intervalMs_;
}
unsigned long Task::getLastExecutionTimeMs() {
	return lastExecutionTimeMs_;
}
unsigned long Task::getNextExecutionTimeMs() {
	return lastExecutionTimeMs_ + intervalMs_;
}
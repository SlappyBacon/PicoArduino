#ifndef PICO_TASK_H
#define PICO_TASK_H

#include <Arduino.h>

#define TASK_MAX_INTERVAL_MS 2147483647UL

class Task {
private:
	inline static unsigned long nextTaskId;
	unsigned long id_;
	void (*action_)();
	bool isEnabled_;
	long executionCountRemaining_;
	unsigned long intervalMs_;
	unsigned long lastExecutionTimeMs_;

	bool isReady();

public:
	Task(void (*aAction)(), long aExecutionCount, unsigned long aIntervalMs, bool aIsImmediate = true, bool aIsEnabled = true);
	~Task();
	bool tryExecute();
	unsigned long getId();
	void setAction(void (* newValue)());
	void setIsEnabled(bool newValue);
	bool getIsEnabled();
	void setExecutionCountRemaining(long newValue);
	long getExecutionCountRemaining();
	void setIntervalMs(unsigned long newValue);
	unsigned long getIntervalMs();
	unsigned long getLastExecutionTimeMs();
	unsigned long getNextExecutionTimeMs();
};

#endif


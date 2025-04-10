#include <Arduino.h>

class Button {

private:

	bool enabled_;
	uint8_t pin_;
	int state_;
	bool isPressed_;
	unsigned long lastStateChangeMs_;
	bool isHeld();
	unsigned long lastUpdateTimeMs_;
	bool shouldUpdate(bool updateRequested);

public:

	Button(uint8_t pin);
	void update();

	bool getIsLow(bool update = true);
	bool getIsLowPressed(bool update = true);
	bool getIsLowHeld(bool update = true);
	bool getIsHigh(bool update = true);
	bool getIsHighPressed(bool update = true);
	bool getIsHighHeld(bool update = true);


};

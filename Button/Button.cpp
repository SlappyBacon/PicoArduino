#include "Button.h"

#define BUTTON_HELD_MS 100



Button::Button(uint8_t aPin) {

	pin_ = aPin;
	pinMode(pin_, INPUT);
	
	state_ = digitalRead(pin_);
	isPressed_ = true;
	unsigned long nowMs = millis();
	lastStateChangeMs_ = nowMs;

	lastUpdateTimeMs_ = nowMs-1;
}


void Button::update() {
	int newState = digitalRead(pin_);

	switch (newState == state_) {
	case true:
		//No Change
		isPressed_ = false;
		break;
	case false:
		//Change

		state_ = newState;
		isPressed_ = true;
		lastStateChangeMs_ = millis();
		break;
	}

	lastUpdateTimeMs_ = millis();
}


bool Button::isHeld() {
	return millis() - lastStateChangeMs_ >= BUTTON_HELD_MS;
}

bool Button::shouldUpdate(bool updateRequested) {
	return updateRequested && millis() - lastUpdateTimeMs_ > 0;
}

bool Button::getIsHigh(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == HIGH;
}
bool Button::getIsHighPressed(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == HIGH && isPressed_;
}
bool Button::getIsHighHeld(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == HIGH && isHeld();
}
bool Button::getIsLow(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == LOW;
}
bool Button::getIsLowPressed(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == LOW && isPressed_;
}
bool Button::getIsLowHeld(bool requestUpdate) {
	if (shouldUpdate(requestUpdate)) update();
	return state_ == LOW && isHeld();
}
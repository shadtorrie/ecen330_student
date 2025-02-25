/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.
Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.
For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#ifndef HITLEDTIMER_H_
#define HITLEDTIMER_H_

#include <stdbool.h>

// The lockoutTimer is active for 1/2 second once it is started.
// It is used to lock-out the detector once a hit has been detected.
// This ensure that only one hit is detected per 1/2-second interval.

#define HIT_LED_TIMER_EXPIRE_VALUE 100000 // Defined in terms of 100 kHz ticks.
#define HIT_LED_TIMER_OUTPUT_PIN 11       // JF-3

// Calling this starts the timer.
void hitLedTimer_start();

// Returns true if the timer is currently running.
bool hitLedTimer_running();

// Standard tick function.
void hitLedTimer_tick();

// Need to init things.
void hitLedTimer_init();

// Turns the gun's hit-LED on.
void hitLedTimer_turnLedOn();

// Turns the gun's hit-LED off.
void hitLedTimer_turnLedOff();

// Disables the hitLedTimer.
void hitLedTimer_disable();

// Enables the hitLedTimer.
void hitLedTimer_enable();

// Runs a visual test of the hit LED.
// The test continuously blinks the hit-led on and off.
void hitLedTimer_runTest();

#endif /* HITLEDTIMER_H_ */

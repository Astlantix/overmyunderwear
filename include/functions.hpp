#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

extern int auton;
extern int b;
extern bool flapping;
extern bool punching;

// auton selector
void autonslctr(void);

/**
 * @brief mode 0: coast, mode 1: brake, mode 2: hold
*/
void setstop(int mode = 0);

// set drivetrain velocity
void setv(double vel);

// motor coast
void msc(motor m);
/**
 * @brief motor spin
 * @param m motor
 * @param dir direction = 1, 1: forward, 0: backward
 * @param vel velocity = 100
 * @param units units = 0, 0: percent in voltage, 1: rpm, 3: voltage, 4: normal percent
*/
void msp(motor m, bool dir = 1, double vel = 100, int units = 0);

// open wings
void spread(void);

// close wings
void fold(void);

// open/close wings
void wingaction(void);

// open/close left wing
void lwing(void);

// open/close right wing
void rwing(void);

// open/close toggle left wing
void lwings(void);

// open/close toggle right wing
void rwings(void);

// open/close toggle wings
void flap(void);

// intaking
void intaking(void);

// tank drive
void tank(void);

// arcade drive
void arcade(void);

// catapult start/stop
void punch(void);

// cata start/stop toggle
void pullback(void);

// PID drivetrain
int pid(double target);

// turn right
void Right(double angle);

// turn left
void Left(double angle);

// turn right to heading (rotation)
void rgt(double angle);

// turn left to heading (rotation)
void lft(double angle);

// print to controller
void printing(std::string);

// tempcheck for over 45 ℃ all motors
bool tempcheck(void);

#endif // FUNCTIONS_HPP
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

extern int auton;
extern int b;
extern bool flapping;
extern bool punching;
extern const long double π = atan(1) * 4;

void autonslctr(void);
void setstop(int mode = 0);
void setv(double vel);
void msc(motor m);
void msp(motor m, bool dir = 1, double vel = 100);
void spread(void);
void fold(void);
void wingaction(void);
void lwing();
void rwing();
void lwings();
void rwings();
void flap(void);
void intaking(void);
void batmobile(void);
void tank(void);
void arcade(void);
void punch(void);
void pullback(void);
int pid();
void Right(double angle);
void Left(double angle);
void rgt(double angle);
void lft(double angle);
void printing(std::string);
bool tempcheck(void);


#endif // FUNCTIONS_HPP
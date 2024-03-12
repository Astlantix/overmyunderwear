#include "vex.h"
using namespace std;

speed::speed(vex::motor &fl, vex::motor &fr, vex::motor &bl, vex::motor &br, vex::motor &ml, vex::motor &mr, vex::guido &inert)
    : fl(&fl), fr(&fr), bl(&bl), br(&br), ml(&ml), mr(&mr), inert(&inert) {
}

void speed::setv(double vel, vex::percentUnits units) {
    speed::fl->setVelocity(vel, units);
    speed::fr->setVelocity(vel, units);
    speed::ml->setVelocity(vel, units);
    speed::mr->setVelocity(vel, units);
    speed::bl->setVelocity(vel, units);
    speed::br->setVelocity(vel, units);
}

void speed::setv(double vel, vex::velocityUnits units) {
    speed::fl->setVelocity(vel, units);
    speed::fr->setVelocity(vel, units);
    speed::ml->setVelocity(vel, units);
    speed::mr->setVelocity(vel, units);
    speed::bl->setVelocity(vel, units);
    speed::br->setVelocity(vel, units);
}

void speed::right(double angle) {
    speed::inert->setRotation(0,deg);
    while (fabs(speed::inert->rotation(deg)) < angle) {
        double error = angle - fabs(inert->rotation(deg));
       speed::fl->spin(rev,5 + error * 0.1,pct);
       speed::fr->spin(fwd,5 + error * 0.1,pct);
       speed::ml->spin(rev,5 + error * 0.1,pct);
       speed::mr->spin(fwd,5 + error * 0.1,pct);
       speed::bl->spin(rev,5 + error * 0.1,pct);
       speed::br->spin(fwd,5 + error * 0.1,pct);
        
    }
    speed::fl->stop(brake);
    speed::fr->stop(brake);
    speed::ml->stop(brake);
    speed::mr->stop(brake);
    speed::bl->stop(brake);
    speed::br->stop(brake);
}

void speed::left(double angle) {
    speed::inert->setRotation(0,deg);
    while (fabs(speed::inert->rotation(deg)) < angle) {
        double error = angle - fabs(inert->rotation(deg));
       speed::fl->spin(fwd,5 + error * 0.1,pct);
       speed::fr->spin(rev,5 + error * 0.1,pct);
       speed::ml->spin(fwd,5 + error * 0.1,pct);
       speed::mr->spin(rev,5 + error * 0.1,pct);
       speed::bl->spin(fwd,5 + error * 0.1,pct);
       speed::br->spin(rev,5 + error * 0.1,pct);
        
    }
    speed::fl->stop(brake);
    speed::fr->stop(brake);
    speed::ml->stop(brake);
    speed::mr->stop(brake);
    speed::bl->stop(brake);
    speed::br->stop(brake);
}

int speed::drive(double target) {
    double kP = 0.0515;
    double kI = 0.0115;
    double kD = 0.5;
    double error = 0;
    double integral = 0;
    double derivative = 0;
    double prevError = 0;

    double power = 0;
    double prevPower = 0;

    speed::fl->setPosition(0,deg);
    speed::fr->setPosition(0,deg);
    speed::ml->setPosition(0,deg);
    speed::mr->setPosition(0,deg);
    speed::bl->setPosition(0,deg);
    speed::br->setPosition(0,deg);

    while (1) {
        double currentDist = (speed::fl->position(deg) + speed::fr->position(deg) + speed::ml->position(deg) + speed::mr->position(deg) + speed::bl->position(deg) + speed::br->position(deg))/6;

        error = target - currentDist;
        if (fabs(integral) > 200) integral += error;

        derivative = error - prevError;

        power = (kP*error) + (kI*integral) + (kD*derivative);

        if (power > 1) power = 1;
        if (power < -1) power = -1;

        double slew = 0.1;

        if (power > prevPower + slew) power = prevPower + slew;
        if (power < prevPower - slew) power = prevPower - slew;

       speed::fl->spin(fwd,11*power,volt);
       speed::fr->spin(fwd,11*power,volt);
       speed::ml->spin(fwd,11*power,volt);
       speed::mr->spin(fwd,11*power,volt);
       speed::bl->spin(fwd,11*power,volt);
       speed::br->spin(fwd,11*power,volt);

        if (fabs(error) < 0.7 && fabs(prevError) < 1) break;

        prevPower = power;
        prevError = error;

        wait(10,msec);
    }
    speed::fl->stop();
    speed::fr->stop();
    speed::ml->stop();
    speed::mr->stop();
    speed::bl->stop();
    speed::br->stop();
    return 0;
}


void speed::run(vex::directionType dir) {
    speed::fl->spin(dir);
    speed::fr->spin(dir);
    speed::ml->spin(dir);
    speed::mr->spin(dir);
    speed::bl->spin(dir);
    speed::br->spin(dir);
}

void speed::calibrate(void) {
    speed::fl->resetPosition();
    speed::fr->resetPosition();
    speed::ml->resetPosition();
    speed::mr->resetPosition();
    speed::bl->resetPosition();
    speed::br->resetPosition();
    speed::inert->calibrate(0);
}

bool speed::isCalibrating(void) {
    if (speed::inert->isCalibrating()) return 1;
    return 0;
}

double speed::rot(void) {
    return speed::inert->rotation();
}

void speed::setrot(double value) {
    speed::inert->setRotation(value,deg);

}

void speed::eright(double angle) {
    while (fabs(speed::inert->rotation(deg)) < angle) {
        double error = angle - fabs(inert->rotation(deg));
        speed::fl->spin(fwd,5 + error * 0.1,pct);
        speed::fr->spin(rev,5 + error * 0.1,pct);
        speed::ml->spin(fwd,5 + error * 0.1,pct);
        speed::mr->spin(rev,5 + error * 0.1,pct);
        speed::bl->spin(fwd,5 + error * 0.1,pct);
        speed::br->spin(rev,5 + error * 0.1,pct);
        
    }
    speed::fl->stop(brake);
    speed::fr->stop(brake);
    speed::ml->stop(brake);
    speed::mr->stop(brake);
    speed::bl->stop(brake);
    speed::br->stop(brake);
}

void speed::eleft(double angle) {
    while (fabs(speed::inert->rotation(deg)) < angle) {
        double error = angle - fabs(inert->rotation(deg));
        speed::fl->spin(rev,5 + error * 0.1,pct);
        speed::fr->spin(fwd,5 + error * 0.1,pct);
        speed::ml->spin(rev,5 + error * 0.1,pct);
        speed::mr->spin(fwd,5 + error * 0.1,pct);
        speed::bl->spin(rev,5 + error * 0.1,pct);
        speed::br->spin(fwd,5 + error * 0.1,pct);
        
    }
    speed::fl->stop(brake);
    speed::fr->stop(brake);
    speed::ml->stop(brake);
    speed::mr->stop(brake);
    speed::bl->stop(brake);
    speed::br->stop(brake);
}

void speed::setstop(vex::brakeType mode) {
    speed::fl->setStopping(mode);
    speed::fr->setStopping(mode);
    speed::ml->setStopping(mode);
    speed::mr->setStopping(mode);
    speed::bl->setStopping(mode);
    speed::br->setStopping(mode);
}

void speed::stop(vex::brakeType mode) {
    speed::fl->stop(mode);
    speed::fr->stop(mode);
    speed::ml->stop(mode);
    speed::mr->stop(mode);
    speed::bl->stop(mode);
    speed::br->stop(mode);
}
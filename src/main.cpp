/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Redwood Robotics                                          */
/*    Created:      2/10/2024, 3:52:11 PM                                     */
/*    Description:  haha underwear                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "autons.hpp"
#include "functions.hpp"
#include <string>

using namespace vex;
using namespace std;


competition Competition;

bool atnslct = 0;
bool hot = 0;
bool checkhot = 0;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
    inert.calibrate();
    waitUntil(!inert.isCalibrating());
    zap.rumble("."); // rumble when calibrated
    while(!atnslct) { // select auton
        autonslctr();
        if (zap.ButtonA.pressing()) atnslct = 1;
        wait(10,msec);
    }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
    if (auton == 1) {
        rawp();
    } else if (auton == 2) {
        lawp();
    } else if (auton == 3) {
        elim();
    } else if (auton == 4) {
        skills();
    } else if (auton == 5) {
        test();
    }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                        */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void usercontrol(void) {
    fold();
    ffold();
    printing("win");
    while (1) {
        // intake
        intaking();

        // wings
        zap.ButtonY.pressed(wingaction);
        zap.ButtonY.released(flap);

        zap.ButtonL2.pressed(rwing);
        zap.ButtonL1.pressed(lwing);
        zap.ButtonL2.released(rwings);
        zap.ButtonL1.released(lwings);

        zap.ButtonLeft.pressed(flwing);
        zap.ButtonRight.pressed(frwing);
        zap.ButtonLeft.released(flwings);
        zap.ButtonRight.released(frwings);
        
        zap.ButtonA.pressed(wingactions);
        zap.ButtonA.released(flaps);

        // cata
        zap.ButtonX.pressed(punch);
        zap.ButtonX.released(pullback);

        // tempcheck
        if (tempcheck()) {
            hot = 1;
        }
        if (hot && !checkhot) {
            printing("HOT");
            checkhot = 1;
        }
        wait(10,msec);
    }
}

// according to some website, cussing in your code makes people want to hire you more, and thats fucking funny
int main(void) {

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    // Run the pre-autonomous function.
    pre_auton();
    //tank();
    arcade();

    // Prevent main from exiting with an infinite loop.
    while (true) {wait(10, msec);}
}

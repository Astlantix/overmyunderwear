#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;
brain Brain;

controller zap = controller(primary);
motor fl = motor(PORT15, ratio6_1, 1);
motor fr = motor(PORT17, ratio6_1, 0);
motor ml = motor(PORT7, ratio6_1, 0);
motor mr = motor(PORT4, ratio6_1, 1);
motor bl = motor(PORT5, ratio6_1, 1);
motor br = motor(PORT10, ratio6_1, 0);
motor_group L = motor_group(fl, ml, bl);
motor_group R = motor_group(fr, mr, br);
encoder l = encoder(Brain.ThreeWirePort.B);
encoder r = encoder(Brain.ThreeWirePort.D);
speed fast = speed(fl, fr, bl, br, ml, mr, inert);
motor intake = motor(PORT12, ratio6_1, 1);
motor cata = motor(PORT2, ratio36_1, 0);
pneumatics bat = pneumatics(Brain.ThreeWirePort.A); 
pneumatics wing = pneumatics(Brain.ThreeWirePort.H);
pneumatics redd = pneumatics(Brain.ThreeWirePort.F);
pneumatics bull = pneumatics(Brain.ThreeWirePort.G);
inertial inert = inertial(PORT16);

bool remoteControlCodeEnabled = 1;

void vexcodeInit(void) {
  // Nothing to initialize
}
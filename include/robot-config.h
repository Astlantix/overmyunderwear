using namespace vex;

extern brain Brain; // braaaiiins

extern controller zap; // primary controller
extern motor fl; // front left
extern motor fr; // front right
extern motor ml; // middle left
extern motor mr; // middle right
extern motor bl; // back left
extern motor br; // back right
extern motor_group L; // left motors
extern motor_group R; // right motors
extern motor intake; // intake
extern motor cata; // catapult
extern pneumatics bat; // right wing
extern pneumatics wing; // left wing
extern inertial inert; // inertial

// nothing to initialize
void vexcodeInit(void);
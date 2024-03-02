#include "vex.h"
#include "functions.hpp"
using namespace vex;
using namespace std;
using namespace chrono;


int auton = 1;
int numofautons = 5;
bool flapping = 0;
int b = 0; // intake control
bool punching = 0;

void autonslctr(void) {
    if (zap.ButtonRight.pressing()) {
        auton++;
        wait(200,msec);
    } else if (zap.ButtonLeft.pressing()) {
        auton--;
        wait(200,msec);
    }
    if (auton > numofautons) {
        auton = 1;
    } else if (auton < 1) {
        auton = numofautons;
    }
    if (auton == 1) {
        printing("RAWP");
    } else if (auton == 2) {
        printing("LAWP");
    } else if (auton == 3) {
        printing("ELIM");
    } else if (auton == 4) {
        printing("SKILLS");
    } else if (auton == 5) {
        printing("TEST");
    }
}

void setstop(int mode) {
    if (!mode) {
        L.setStopping(coast);
        R.setStopping(coast);
    } else if (mode == 1) {
        L.setStopping(brake);
        R.setStopping(brake);
    } else {
        L.setStopping(hold);
        R.setStopping(hold);
    }
}

void setv(double vel) {
    L.setVelocity(vel,pct);
    R.setVelocity(vel,pct);
}

void msc(motor m) {
    m.stop(coast);
}

void msp(motor m, bool dir, double vel) {
    if (dir) {
        m.spin(fwd,vel,pct);
    } else {
        m.spin(rev,vel,pct);
    }
}

void spread(void) {
    bat.open();
    wing.open();
}

void fold(void) {
    bat.close();
    wing.close();
}

void wingaction(void) {
    if (flapping) {
        fold();
    } else {
        spread();
    }
}

bool lflap = 0;
bool rflap = 0;

void lwing() {
  if (lflap) {
    wing.open();
  } else {
    wing.close();
  }
}

void rwing() {
  if (rflap) {
    bat.open();
  } else {
    bat.close();
  }
}

steady_clock::time_point lastLWing;
steady_clock::time_point lastRWing;

void lwings() {
  auto now = steady_clock::now();
  auto durLastLWing = duration_cast<milliseconds>(now - lastLWing).count();
  if (durLastLWing > 200) {
    lflap = !lflap;
    lastLWing = now;
  }
}

void rwings() {
  auto now = steady_clock::now();
  auto durLastRWing = duration_cast<milliseconds>(now - lastRWing).count();
  if (durLastRWing > 200) {
    rflap = !rflap;
    lastRWing = now;
  }
}

steady_clock::time_point lastFlap;

void flap(void) {
    auto now = steady_clock::now();
    auto durLastFlap = duration_cast<milliseconds>(now - lastFlap).count();
    if (durLastFlap > 200) {
            wingaction();
            flapping = !flapping;
            lastFlap = now;
    }
}

steady_clock::time_point printake; // time last intake pressing

// intake thing
void intaking(void) {
    auto now = steady_clock::now(); // current time
    auto durLastTake = duration_cast<milliseconds>(now-printake).count();
    if(durLastTake > 150) {
        if (b==0) {
            if (zap.ButtonR1.pressing()) {
                msp(intake,0);
                b = 1;
            } else if (zap.ButtonR2.pressing()) {
                msp(intake);
                b = 2;
            }
        } else if (b==1) {
            if (zap.ButtonR1.pressing()) {
                msc(intake);
                b = 0;
            } else if (zap.ButtonR2.pressing()) {
                msp(intake);
                b = 2;
            }
        } else if (b==2) {
            if (zap.ButtonR2.pressing()) {
                msc(intake);
                b = 0;
            } else if (zap.ButtonR1.pressing()) {
                msp(intake,0);
                b = 1;
            }
        }
        printake = now;
    }
}

void batmobile(void) {
    while (1) {

    }
    this_thread::sleep_for(10);
}

void tank(void) {
    while (1) {
        double leftspeed = pow(zap.Axis3.position(),3)/1000;
        double rightspeed = pow(zap.Axis2.position(),3)/1000;
        L.spin(fwd,leftspeed,pct);
        R.spin(fwd,rightspeed,pct);
    }
    this_thread::sleep_for(10);
}

void arcade(void) {
    while (1) {
        double leftspeed = pow((zap.Axis3.position() + zap.Axis4.position()), 3)/1000;
        double rightspeed = pow((zap.Axis3.position() - zap.Axis4.position()), 3)/1000;
        L.spin(fwd,leftspeed,pct);
        R.spin(fwd,rightspeed,pct);
    }
    this_thread::sleep_for(10);
}

steady_clock::time_point lastPunch;

void punch(void) {
    if (punching) {
        msp(cata);
    } else {
        msc(cata);
    }
}

void pullback(void) {
    auto now = steady_clock::now();
    auto durLastPunch = duration_cast<milliseconds>(now - lastPunch).count();
    if (durLastPunch > 200) {
        punching = !punching;
        lastPunch = now;
    }
}

void printing(string text) {
    zap.Screen.setCursor(2,10);
    zap.Screen.clearLine();
    zap.Screen.print(text.c_str());
}

/*Credit to Ascend Robotics for PID graphing because I don't want to type this fancy stuff out (pid by me though)*/
// graphing data, used for PID tuning
void graphPID(vector<int> errorHistory, vector<float> powerHistory, int goal, float error, int time) {
  // goal is the PID goal (target)
  // error history is a list of all of the errors (range is 0 to target)
  // powerHistory is a list of the power applied (range is -1 to 1)
  // error is the current error
  // time is the current time, in milliseconds
  
  //Setup: clear screen and draw the target line
  Brain.Screen.clearScreen();
  Brain.Screen.setPenWidth(2);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawLine(0, 60, 480, 60);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setPenColor(green);

  //display final error and time
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.clearLine(1);
  Brain.Screen.print(" Final Error: ");
  Brain.Screen.print(error);
  Brain.Screen.print("    Time: ");
  Brain.Screen.print(time);
  
  //define the borders of the graph
  int minY = 60; //error = 0 (robot is at target)
  int maxY = 230; //error = driveDistance (Robot is at start)
  int minX = 10; //time = beginning
  int maxX = 470; //time = end
  
  //loop through each data point and graph it
  for (int i = 0; i < errorHistory.size() - 1; i++) { 
    int x = minX + (maxX - minX) * i / errorHistory.size(); //find the x-value of this data point
    
    //graph velocity
    Brain.Screen.setPenColor(green);
    Brain.Screen.drawLine(x, minY + (float)errorHistory.at(i) / goal * (maxY - minY), x + (float)(maxX - minX) / errorHistory.size(), minY + (float)errorHistory.at(i + 1) / goal * (maxY - minY));
    
    //graph power, changing color based on direction
    if (powerHistory.at(i) > 0) {
      Brain.Screen.setPenColor(orange);
    } else {
      Brain.Screen.setPenColor(yellow);
    }
    
    Brain.Screen.drawLine(x, maxY - abs(powerHistory.at(i)) * (maxY - minY), x + (float)(maxX - minX) / errorHistory.size(), maxY - abs(powerHistory.at(i + 1)) * (maxY - minY));
  }
}

//
int pid(double target) {
    double kP = 0.0515;
    double kI = 0.0115;
    double kD = 0.5;
    double error = 0;
    double integral = 0;
    double derivative = 0;
    double prevError = 0;

    double power = 0;
    double prevPower = 0;

    fl.setPosition(0,deg);
    fr.setPosition(0,deg);
    ml.setPosition(0,deg);
    mr.setPosition(0,deg);
    bl.setPosition(0,deg);
    br.setPosition(0,deg);

    //lists
    vector<int> errorHistory; //keep track of error over time
    vector<float> powerHistory; //keep track of motor power over time
    int currentTime = 0; //keep track of time over time (wow!)*/

    while (1) {
        double currentDist = (fl.position(deg) + fr.position(deg) + ml.position(deg) + mr.position(deg) + bl.position(deg) + br.position(deg))/6;

        error = target - currentDist;
        if (fabs(integral) > 200) {
        integral += error;
        }

        derivative = error - prevError;

        power = (kP*error) + (kI*integral) + (kD*derivative);

        if (power > 1) power = 1;
        if (power < -1) power = -1;

        double slew = 0.1;

        if (power > prevPower + slew) power = prevPower + slew;
        if (power < prevPower - slew) power = prevPower - slew;

        fl.spin(fwd,11*power,volt);
        fr.spin(fwd,11*power,volt);
        ml.spin(fwd,11*power,volt);
        mr.spin(fwd,11*power,volt);
        bl.spin(fwd,11*power,volt);
        br.spin(fwd,11*power,volt);

        if (fabs(error) < 0.7 && fabs(prevError) < 1.2) break;

        prevPower = power;
        prevError = error;

        //update histories and current time
        errorHistory.push_back(error);
        powerHistory.push_back(fabs(power));
        currentTime += 20;

        //graph the PIDs 
        graphPID(errorHistory, powerHistory, target, error, currentTime);

        wait(20,msec);
    }
    fl.stop();
    fr.stop();
    ml.stop();
    mr.stop();
    bl.stop();
    br.stop();
    return 0;
}

void Right(double angle) {
    setstop(1);
    inert.setRotation(0,deg);
    while (fabs(inert.rotation(deg)) < angle) {
        double error = angle - fabs(inert.rotation(deg));
        L.spin(fwd,5 + error * 0.1,pct);
        R.spin(rev,5 + error * 0.1,pct);
    }
    L.stop();
    R.stop();
}

void Left(double angle) {
    setstop(1);
    inert.setRotation(0,deg);
    while (fabs(inert.rotation(deg)) < angle) {
        double error = angle - fabs(inert.rotation(deg));
        L.spin(rev,5 + error * 0.1,pct);
        R.spin(fwd,5 + error * 0.1,pct);
    }
    L.stop();
    R.stop();
}

void rgt(double angle) {
    setstop(1);
    while (fabs(inert.rotation(deg)) < angle) {
        double error = angle - fabs(inert.rotation(deg));
        L.spin(fwd,5 + error * 0.1,pct);
        R.spin(rev,5 + error * 0.1,pct);
    }
    L.stop();
    R.stop();
}

void lft(double angle) {
    setstop(1);
    while (fabs(inert.rotation(deg)) < angle) {
        double error = angle - fabs(inert.rotation(deg));
        L.spin(rev,5 + error * 0.1,pct);
        R.spin(fwd,5 + error * 0.1,pct);
    }
    L.stop();
    R.stop();
}

double temp(motor m) {return m.temperature(celsius);}

bool tempcheck(void) {
    if (temp(cata) > 45 || temp(intake) > 45 || temp(fl) > 45 || temp(fr) > 45 || temp(bl) > 45 || temp(br) > 45 || temp(ml) > 45 || temp(mr) > 45) {
        return 1;
    } else {
        return 0;
    }
}

bool tipping(void) {
    return 1;
}
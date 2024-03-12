#include "autons.hpp"
#include "vex.h"
#include "functions.hpp"
using namespace vex;
using namespace std;

void rawp(void) {
    // intake alley triball, back up, take triball out of corner, score preload and triball
    msp(intake);
    fast.drive(1);
    wait(100,msec);
    msc(intake);
    fast.drive(-24);
    wing.open();
    fast.left(45);
    wing.close();
    fast.drive(-7.5);

    // outtake triball in intake toward goal, intake triball side triball against bar, outtake toward goal, intake middle against bar, score other two with wings, outtake triball in intake and score
    fast.left(90);
    fast.drive(10);
    fast.right(90);
    fast.drive(12);
    fast.right(90);
    msp(intake,0,85);
    wait(10,msec);
    fast.left(180);
    msp(intake);
    fast.drive(18);
    wait(100,msec);
    msc(intake);
    fast.right(90);
    msp(intake,0);
    wait(100,msec);
    fast.left(30);
    msp(intake);
    fast.drive(10);
    wait(100,msec);
    fast.right(60);
    msp(intake,0);
    wait(100,msec);
    fast.left(180);
    msp(intake);
    fast.drive(10);
    wait(100,msec);
    msc(intake);
    fast.right(180);
    fspread();
    msp(intake,0);
    fast.run(fwd);
    wait(0.75,sec);
    fast.stop();
    ffold();
    fast.drive(-12);
    msc(intake);

    // rush back to touch elevation bar
    fast.right(90);
    fast.drive(12);
    redd.open();
    fast.right(92);
}

void lawp(void) {
    // take triball out of corner, score preload, back up into elevation bar
    bat.open();
    fast.left(30);
    fast.drive(7.5);
    msp(intake,0,85);
    wait(10,msec);
    fast.drive(-7.5);
    fast.left(60);
    msc(intake);
    fast.drive(-12);
}

void elim(void) {
    // same as left side win point, but go back to matchloading zone for faster bowling
    lawp();
    fast.drive(12);
}

void skills(void) {
    // score two preloads
    msp(intake,0,85);
    fast.drive(4);
    wait(200,msec);
    msc(intake);
    fast.drive(-4);
    fast.left(70);

    // matchload 44 triballs
    msp(cata);
    wait(30,sec);
    
    // push triballs on our side to the other side
    fast.drive(10);
    msc(cata);
    fast.left(20);
    fspread();
    fast.drive(10);
    wait(100,msec);
    fast.drive(-10);
    fast.right(90);
    fast.drive(7.5);
    fast.left(90);
    fast.drive(10);
    wait(100,msec);
    fast.drive(-15);
    ffold();
    fast.right(90);
    fast.drive(7.5);
    fast.left(90);
    fspread();

    // go through alleyway, score with wings sweeping
    fspread();
    fast.drive(60);
    wait(100,msec);
    fast.left(45);
    fast.drive(10);
    wait(100,msec);
    ffold();
    fast.right(90);
    fast.drive(-7.5);
    spread();
    fast.left(45);
    fast.drive(-10);
    fold();
    msp(intake);
    fast.drive(24);
    wait(100,msec);
    msc(intake);
    fast.left(45);
    spread();
    fast.run(rev);
    wait(0.75,sec);
    fast.stop();
    fold();
    fast.drive(10);
    fast.right(135);
    fspread();
    fast.drive(12);
    wait(100,msec);
    fast.right(90);
    msp(intake,0);
    fast.drive(10);
    wait(100,msec);
    ffold();
    fast.right(90);
    msp(intake);
    fast.drive(10);
    wait(100,msec);
    msc(intake);
    fast.left(180);
    fast.drive(10);
    wait(100,msec);
    fspread();
    msp(intake,0);
    fast.drive(10);
    fast.right(45);
    fast.drive(7.5);

    // hang
    wait(100,msec);
    ffold();
    fast.drive(-7.5);
    msc(intake);
    fast.right(180);
    fast.drive(12);


}

void test(void) {
    /*msp(fl);
    wait(1,sec);
    msc(fl);
    msp(fr);
    wait(1,sec);
    msc(fr);
    msp(mr);
    wait(1,sec);
    msc(mr);
    msp(ml);
    wait(1,sec);
    msc(ml);
    msp(br);
    wait(1,sec);
    msc(br);
    msp(bl);
    wait(1,sec);
    msc(bl);*/

    pid(500);

    //pid(24);

    
}
#ifndef SPEED_H
#define SPEED_H

class speed{
    protected:
        vex::motor *fl;
        vex::motor *fr;
        vex::motor *bl;
        vex::motor *br;
        vex::motor *ml;
        vex::motor *mr;
        vex::guido *inert;

    private:
        double gearRatio;
        double wheelDiameter;    
        
    public:
        /**
         * @brief Construct a new speed object
         * @param fl Front left motor
         * @param fr Front right motor
         * @param bl Back left motor
         * @param br Back right motor
         * @param ml Middle left motor
         * @param mr Middle right motor
         * @param inert Inertial/Guido sensor
        */
        speed(vex::motor &fl, vex::motor &fr, vex::motor &bl, vex::motor &br, vex::motor &ml, vex::motor &mr, vex::guido &inert);

        /**
         * @brief Sets the drivetrain velocity
         * @param vel Velocity
         * @param units Units percent, rpm, or voltage
        */
        void setv(double vel, vex::percentUnits units);
        /**
         * @brief Sets the drivetrain velocity
         * @param vel Velocity
         * @param units Units percent, rpm, or voltage
        */
        void setv(double vel, vex::velocityUnits units);
        
        // turn right
        void right(double angle);
        // turn left
        void left(double angle);
        
        // PID Function
        int drive(double target);

        // run the robot
        void run(vex::directionType dir);

        // reset and calibrate inertial sensor
        void calibrate(void);

        /**
         * @brief Checks if the inertial sensor is calibrating
         * @return true if calibrating, false if not
        */
        bool isCalibrating(void);

        /**
         * @brief Gets the rotation of the inertial sensor
         * @param units Units degrees or radians
         * @return Rotation of the inertial sensor
        */
        double rot(void);

        /**
         * @brief Sets the rotation of the inertial sensor
         * @param value Value
         * @param units Units degrees or radians
        */
        void setrot(double value);

        /**
         * @brief turn the robot right to a specific angle
         * @param angle angle to turn to
        */
        void eright(double angle);
        /**
         * @brief turn the robot left to a specific angle
         * @param angle angle to turn to
        */
        void eleft(double angle);

        // set stopping mode for the drivetrain
        void setstop(vex::brakeType mode);

        // stop the drivetrain
        void stop(vex::brakeType mode = vex::brakeType::coast);
        
};

#endif // SPEED_H
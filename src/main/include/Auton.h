#pragma once

#include "Euler.h"

#define lineToWall				1.524
#define startDistanceFromWall   0.3048
#define pixelOffsetCoefficient	0.025
#define angleOffsetCoefficient	0.01
#define distanceCoefficient		0.3
#define turningErrorThreshold	0.2
#define distanceErrorThreshold	0.2
#define maxAutonSpeed			0.5
#define radiusOfRobot           0 //this need to be measuered

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
	Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake, Spinner *spinner);
	void startGame (int mode, double period);
	
	//void AutonCase(int begin, int end); // this must be called before AutonDrive()
	void AutonDrive(double period);

	private:
	DalekDrive *m_drive;
	RaspberryPi *m_pi;
	AHRS *m_ahrs;
	BallIntake *m_ballIntake;
	Spinner *m_spinner;

	double myPeriod;
	// eventually will need delivery mechanism

	int autonStage, currentAngle;
	double exit_target_x, exit_target_y, exit_target_ang, exit_target_dist, enter_target_x, enter_target_y, enter_target_ang, enter_target_dist, traveled_dist;
	bool pickupBallEnd, pickupBallStart, firstBallLost, secondBallLost, thirdBallLost, tempCont;

	
	bool driveTo(double dist, double period);
	void turnTo(double angle, bool turnRight);
	double angleOffset(double angle);
	//int autonChallenge;
};
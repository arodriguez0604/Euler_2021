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
#define radiusOfRobot           15

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
	Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake, Spinner *spinner);
	void startGame (int mode, double period);
	void Test (double period);
	
	//void AutonCase(int begin, int end); // this must be called before AutonDrive()
	void AutonDrive(double period);

	private:
	DalekDrive *m_drive;
	RaspberryPi *m_pi;
	AHRS *m_ahrs;
	BallIntake *m_ballIntake;
	Spinner *m_spinner;

	double myPeriod;

	int autonStage, currentAngle;
	double traveled_dist;
	bool tempCont;

	
	bool driveTo(double end_dist, double period);
	bool turnTo(double angle, double period, bool turnRight);
	double angleOffset(double angle);
	//int autonChallenge;
};
// some of this should be in the DalekDrive class, but whatever
#pragma once

#include "Euler.h"

// literally every single #define is a guess, so test one at a time
#define START_DIST				2.286 // dist from line to tip of triangle
#define lineToWall				1.524
#define startDistanceFromWall   0.3048
#define red1C3x 				1.524
#define red1C3y					0.762
#define red1turn1				0.045
#define red1D5x					3.048
#define red1D5y					0.000
#define red1turn2				-1.092
#define red1A6x					4.572
#define red1A6y					2.286
#define blue1E6x				3.810
#define blue1E6y				-0.762
#define blue1B7x				4.572
#define blue1B7y				1.524
#define blue1C9x				5.334
#define blue1C9y				0.762
#define pixelOffsetCoefficient	0.025
#define angleOffsetCoefficient	0.01
#define distanceCoefficient		0.3
#define turningErrorThreshold	0.05
#define distanceErrorThreshold	0.2
#define pTurn					2 // this number depends on the speed of the robot (weight and handicap)
#define iTurn					0 // probably unnecessary and won't be used
#define dTurn					0 // probably unnecessary and won't be used
#define maxTurnSpeed			0.5

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
	Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake);
	void GalaticSearch(double period);
	void AutoNav(double period, int path);
	
	//void AutonCase(int begin, int end); // this must be called before AutonDrive()
	void AutonDrive(double period);

	private:
	DalekDrive *m_drive;
	RaspberryPi *m_pi;
	AHRS *m_ahrs;
	BallIntake *m_ballIntake;

	double p_temp, i_temp, d_temp, target_x, target_y, target_ang, myPeriod;
	// eventually will need delivery mechanism

	int autonStage;
	double exit_target_x, exit_target_y, exit_target_ang, exit_target_dist, enter_target_x, enter_target_y, enter_target_ang, enter_target_dist, travelled_dist, period;
	bool pickupBallEnd, pickupBallStart, firstBallLost, secondBallLost, thirdBallLost;

	bool driveToCoordinates(double x, double y, double angle, double period);
	bool turnToFace(double angle);
	double angleOffset(double angle);
	//int autonChallenge;
};
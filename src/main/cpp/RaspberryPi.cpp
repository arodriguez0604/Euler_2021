#include "Euler.h"

RaspberryPi::RaspberryPi(DalekDrive *drive) {
    m_drive			= drive;
}

bool RaspberryPi::FollowBall()
{
	int offset = frc::SmartDashboard::GetNumber("X Offset", 100000), distance = frc::SmartDashboard::GetNumber("Distance", -1);
	if (offset == 100000 || distance == -1) {
		m_drive->TankDrive(0.0, 0.0, false);
		SmartDashboard::PutBoolean("camera sees ball?", false);
		return false;
	}
	SmartDashboard::PutBoolean("camera sees ball?", true);
    return driveAdjusted(offset, distance, pixelOffsetCoefficient);
}


bool RaspberryPi::driveAdjusted(double offset, double distance, double coefficient)
{
	return driveAdjusted(offset, distance, coefficient, false);
}

bool RaspberryPi::driveAdjusted(double offset, double distance, double coefficient, bool inverted)
{
	if (distance < distanceErrorThreshold) {
		m_drive->TankDrive(0.0, 0.0, false);
		return true;
	}
	double ratio = exp(coefficient * offset / distance), magnatude = (distance + .3) / 8.0; // this needs to be changed
	// seans formula ->  = -.4 / (1 + 4 * exp(-distanceCoefficient * distance));
	if (magnatude > .5) {
		magnatude = .5;
	}
	if (!inverted) {
		magnatude *= -1;
	}
	if (ratio < 1) {
		m_drive->TankDrive(magnatude, magnatude * ratio, false);
	} else {
		m_drive->TankDrive(magnatude / ratio, magnatude, false);
	}
	return false;
}
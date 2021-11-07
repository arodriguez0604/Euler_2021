#include "Euler.h"

Auton::Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake, Spinner *spinner)
{
	m_drive			= drive;
	m_ahrs			= ahrs;
	m_pi            = pi; 
	m_ballIntake    = ballIntake;
	m_spinner       = spinner;

	autonStage = 0;
	traveled_dist = 0;
	myPeriod = 0;
	
	tempCont = false;
	firstBallLost = false;
	secondBallLost = false;
	thirdBallLost = false;
}

void Auton::startGame (int mode, double period) {
	frc::SmartDashboard::PutBoolean("Auton Ready", false);
	myPeriod += period;
	if (mode == 0) {
		switch (autonStage) {
			case 0:
				m_spinner->autonTick(1);
				if (myPeriod > 1 || tempCont) {
					if (!tempCont) {
						myPeriod = 0;
						tempCont = true;
					}
					if (myPeriod < 0.15) {
						m_ballIntake->Tick(1);
					}	else {
							autonStage++;
							myPeriod = 0;
							tempCont = false;
							m_ballIntake->Tick(0);
						}
				}
				break;
			case 1:
				if (myPeriod > 0.5 || tempCont) {
					if (!tempCont) {
						myPeriod = 0;
						tempCont = true;
					}
					if (myPeriod < 0.15) {
						m_ballIntake->Tick(1);
					}	else {
							autonStage++;
							myPeriod = 0;
							tempCont = false;
							m_ballIntake->Tick(0);
						}
				}
				break;
			case 2:
				if (myPeriod > 0.5 || tempCont) {
					if (!tempCont) {
						myPeriod = 0;
						tempCont = true;
					}
					if (myPeriod < 0.15) {
						m_ballIntake->Tick(1);
					}	else {
							autonStage++;
							myPeriod = 0;
							tempCont = false;
							m_ballIntake->Tick(0);
							m_spinner->autonTick(0);
						}
				}
				break;
			case 3:
				if (driveTo(2.01, period));
				autonStage++;
				break;
			case 4:
				turnTo(15.0, true);
				autonStage++;
				break;
			case 5:
				if (driveTo(1.91, period));
				autonStage++;
				break;
			default:
				m_drive->TankDrive(0.0, 0.0, false);
				m_spinner->autonTick(0);
				break;
		}
	}   else if (mode == 1) {
			switch(autonStage) {
				case 0:
					m_spinner->autonTick(1);
					if (myPeriod > 1 || tempCont) {
						if (!tempCont) {
							myPeriod = 0;
							tempCont = true;
						}
						if (myPeriod < 0.15) {
							m_ballIntake->Tick(1);
						}	else {
								autonStage++;
								myPeriod = 0;
								tempCont = false;
								m_ballIntake->Tick(0);
							}
					}
					break;
				case 1:
					if (myPeriod > 0.5 || tempCont) {
						if (!tempCont) {
							myPeriod = 0;
							tempCont = true;
						}
						if (myPeriod < 0.15) {
							m_ballIntake->Tick(1);
						}	else {
								autonStage++;
								myPeriod = 0;
								tempCont = false;
								m_ballIntake->Tick(0);
							}
					}
					break;
				case 2:
					m_spinner->autonTick(0);
					if (myPeriod > 0.5 || tempCont) {
						if (!tempCont) {
							myPeriod = 0;
							tempCont = true;
						}
						if (myPeriod < 0.15) {
							m_ballIntake->Tick(1);
						}	else {
								autonStage++;
								myPeriod = 0;
								tempCont = false;
								m_ballIntake->Tick(0);
								m_spinner->autonTick(0);
							}
					}
					break;
				case 3:
					turnTo(65, true);
					autonStage++;
					break;
				case 4:
					if (driveTo(3.1, period))
						autonStage++;
					break;
				case 5:
					turnTo(75.7, false);
					autonStage++;
					break;
				case 6:
					if (driveTo(1.92, period))
						autonStage++;
					break;
				default:
					m_drive->TankDrive(0.0, 0.0, false);
					m_spinner->autonTick(0);
					break;
			}
		}	else {
				m_drive->TankDrive(0.0, 0.0, false);
				m_ballIntake->Tick(0);
				m_spinner->autonTick(0);
			}
}

//drives to a certain position
//if reached distance, return true
//else, return false
bool Auton::driveTo(double dist, double period)
{
	m_drive->TankDrive(1.0 - 0.5 * (dist/traveled_dist), 1.0 - 0.5 * (dist/traveled_dist), false);
	m_ballIntake->Tick(2);
	traveled_dist += -1 * (m_drive->GetVelocity() * period);
	if (traveled_dist > dist) {
		m_drive->TankDrive(0.0, 0.0, false);
		m_ballIntake->Tick(0);
		return true;
	}
	return false;
}

//Turns the robot on a dot to the angle given
//positive angle (right)
//negative angle (left)
void Auton::turnTo(double angle, bool turnRight)
{
	//converts AHRS readings (in radians) to degrees
	currentAngle = m_ahrs->GetAngle() * (180 / PI);
	frc::SmartDashboard::PutNumber("Angle", currentAngle);

	//if we have turned enough, then break loop
	if (currentAngle > angle - turningErrorThreshold && currentAngle < angle + turningErrorThreshold) {
		m_drive->TankDrive(0.0, 0.0, false);
		return;
	}

	//turn right
	if (turnRight) {
		m_drive->TankDrive(1.0 - (0.5 * (angle / ((double)currentAngle + 0.01))), -1.0 + (0.5 * (angle / ((double)currentAngle + 0.01))), false); //this has to be tested
		if (currentAngle < angle)
			turnTo(angle, !turnRight);
	}
	//turn left
	else if (angle > 0) {
		m_drive->TankDrive(-1.0 + (0.5 * (angle / ((double)currentAngle + 0.01))), 1.0 - (0.5 * (angle / ((double)currentAngle + 0.01))), false); //this has to be tested
		if (currentAngle > angle)
			turnTo(angle, !turnRight);
	}

	//recursive call
	turnTo(angle, turnRight);
}

double Auton::angleOffset(double angle)
{
	SmartDashboard::PutNumber("ahrs ang", m_ahrs->GetAngle());
	double offset = fmod(angle - (m_ahrs->GetAngle()) * PI / 180, 2 * PI);
	//Josh's function = fmod(angle - (m_ahrs->GetAngle()) * PI / 180, 360)
	if (offset > PI) {
		offset -= PI * 2;
	}
	return offset;
} 
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

	frc::SmartDashboard::PutNumber("AHRS", m_ahrs->GetAngle());
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
				if (driveTo(1.90, period)) { //2.01
					autonStage++;
					traveled_dist = 0;
				}
				break;
			case 4:
				//turnTo(15.0, period, true);
				autonStage++;
				break;
			case 5:
				//if (driveTo(1.91, period)) {
					autonStage++;
					traveled_dist = 0;
				//}
				break;
			default:
				m_drive->TankDrive(0.0, 0.0, false);
				m_ballIntake->Tick(0);
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
					turnTo(65, period, true);
					autonStage++;
					break;
				case 4:
					if (driveTo(3.1, period)) {
						autonStage++;
						traveled_dist = 0;
					}
					break;
				case 5:
					turnTo(75.7, period, false);
					autonStage++;
					break;
				case 6:
					//if (driveTo(1.92, period)) {
						autonStage++;
						traveled_dist = 0;
					//}
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

void Auton::Test(double period) {
	switch (autonStage) {
		case 0:
			if (driveTo(1, period)) {
				frc::SmartDashboard::PutBoolean("Drive To", true);
				autonStage++;
			}
			else {
				frc::SmartDashboard::PutBoolean("Drive To", false);
			}
			break;
		case 1:
			if (turnTo(90, period, true)) {
				frc::SmartDashboard::PutBoolean("Turn To", true);
				autonStage++;
			}
			else
				frc::SmartDashboard::PutBoolean("Turn To", false);
			break;
	}
}

//drives to a certain position
//if reached distance, return true
//else, return false
bool Auton::driveTo(double dist, double period)
{
	//frc::SmartDashboard::PutNumber("Distance Traveled", 1.0 - 0.5 * (dist/traveled_dist));
	m_drive->TankDrive(1.0 - 0.5 * (dist/(traveled_dist + 0.01)), 1.0 - 0.5 * (dist/(traveled_dist + 0.01)), false);
	//m_ballIntake->Tick(2);
	traveled_dist += m_drive->GetVelocity() * period;
	frc::SmartDashboard::PutNumber("Distance Traveled", traveled_dist);
	if (traveled_dist > dist) {
		m_drive->TankDrive(0.0, 0.0, false);
		//m_ballIntake->Tick(0);
		return true;
	}
	return false;
}

//Turns the robot on a dot to the angle given
//positive angle (right)
//negative angle (left)
bool Auton::turnTo(double angle, double period, bool turnRight)
{
	if (turnRight)
		m_drive->TankDrive(.30, -.30, false);
	else
		m_drive->TankDrive(-.30, .30, false);

	traveled_dist += 39.37 * (m_drive->GetVelocity()) * period; //test? meters

	frc::SmartDashboard::PutNumber("Traveled Distance", traveled_dist);

	if (traveled_dist >= (PI * radiusOfRobot * angle) / 180)	
		return true;

	return false;
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
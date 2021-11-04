#include "Euler.h"

Auton::Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake)
{
	m_drive			= drive;
	m_ahrs			= ahrs;
	m_pi            = pi; 
	m_ballIntake    = ballIntake;

	autonStage = 0;
	travelled_dist = 0;
	pickupBallStart = frc::SmartDashboard::GetData("Pickup Ball Start");
	pickupBallEnd   = frc::SmartDashboard::GetData("Pickup Ball End");
	//autonChallenge    = frc::SmartDashboard::GetData("Auton Challenge");

	p_temp = 0; i_temp = 0; d_temp = 0;
	period = 0;
	firstBallLost = false;
	secondBallLost = false;
	thirdBallLost = false;
}

void Auton::GalaticSearch(double period) {
	frc::SmartDashboard::PutNumber("Auton Stage", autonStage);
	switch (autonStage) {
		case 0:
			m_ballIntake->Tick(0);
			autonStage++;
			break;
		case 1:
			if ((frc::SmartDashboard::GetNumber("Distance", -1) > 3.7 || frc::SmartDashboard::GetNumber("Distance", -1) == -1) && !firstBallLost) {
			 	m_ballIntake->Tick(1);
			 	m_pi->FollowBall();
				frc::SmartDashboard::PutBoolean("Case", true);
			}
			// else if (!m_ballIntake->GetReleaseSensor()) {
			// 	m_drive->TankDrive(0.0, 0.0, false);
			// }
			else {
				firstBallLost = true;
			 	m_ballIntake->Tick(1);
			 	m_drive->TankDrive(-0.07, -0.01, false);
				//frc::SmartDashboard::PutBoolean("Case", false);
			}			
			if (m_ballIntake->GetBallCount() == 1)
				autonStage++;
			break;
		case 2:
			m_drive->TankDrive(1.0, -1.0, false);
			if(frc::SmartDashboard::GetNumber("X Offset", 10000) != 10000)
				autonStage++;
			break;
		case 3:
			if ((frc::SmartDashboard::GetNumber("Distance", -1) > 3.7 || frc::SmartDashboard::GetNumber("Distance", -1) == -1) && !secondBallLost) {
				m_ballIntake->Tick(1);
				m_pi->FollowBall();
			}
			else {
				secondBallLost = true;
				m_ballIntake->Tick(1);
				m_drive->TankDrive(-0.07, -0.05, false);
			}
			if (m_ballIntake->GetBallCount() == 2)
				autonStage++;
			break;

		case 4:
			m_drive->TankDrive(1.0, -1.0, false);
			if(frc::SmartDashboard::GetNumber("X Offset", 10000) != 10000)
				autonStage++;
			break;
		case 5:
			if ((frc::SmartDashboard::GetNumber("Distance", -1) > 3.5 || frc::SmartDashboard::GetNumber("Distance", -1) == -1) && !thirdBallLost) {
				m_ballIntake->Tick(1);
				m_pi->FollowBall();
			}
			else {
				thirdBallLost = true;
				m_ballIntake->Tick(1);
				m_drive->TankDrive(-0.07, -0.07, false);
			}			
			if (m_ballIntake->GetBallCount() == 3) {
				autonStage++;
				myPeriod = 0;
			}
			break;
		case 6:
			myPeriod += period;
			if (myPeriod < 1.20)
				m_drive->TankDrive(0.00, -1.00, false);
			else {
				autonStage++;
				myPeriod = 0;
			}
			break;
		case 7:
			myPeriod += period;
			if (myPeriod < 2.00)
				m_drive->TankDrive(-1.00, -1.00, false);
			else {
				autonStage++;
				myPeriod = 0;
			}
			break;
		default:
			frc::SmartDashboard::PutBoolean("Auton Done", true);
			break;
	}
	frc::SmartDashboard::PutNumber("Auton Stage", autonStage);
	//frc::SmartDashboard::PutBoolean("First Ball Lost", firstBallLost);
	// std::cout << "First: " << firstBallLost << "\n";
	// std::cout << "Second: " << secondBallLost << "\n";
	// std::cout << "Third: " << thirdBallLost << "\n";
	// std::cout << "\n";
}

void Auton::AutoNav(double badPeriod, int path) {
	std::cout << "Bad-Period: " << badPeriod << std::endl;
	std::cout << "Period: " << period << std::endl;
	period += badPeriod;
	//be careful with this the first time
	switch (path) {
		//barrel
		case 0:
			if (period < 1.12)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 3.45)
				m_drive->TankDrive(-1.00, -0.30, false);
			else if (period < 6.15)
				m_drive->TankDrive(-1.00, 0.07, false);
			else if (period < 7.20)
				m_drive->TankDrive(-0.30, -1.00, false);
			else if (period < 6.20)


				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 7.25)
				m_drive->TankDrive(-0.30, -1.00, false);
			else if (period < 9.10)
				m_drive->TankDrive(-1.00, -1.00, false);
			else
				m_drive->TankDrive(0.00, 0.00, false); 
			break;

		//slamlom
		case 1:
			if (period < 0.70)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 1.75)
				m_drive->TankDrive(-0.30, -0.90, false);
			else if (period < 2.38)
				m_drive->TankDrive(-1.00, -0.30, false);
			else if (period < 3.70)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 4.40)
				m_drive->TankDrive(-0.30, -0.75, false);
			else if (period < 7.50)
				m_drive->TankDrive(-1.00, -0.152, false);
			else if (period < 8.50)
				m_drive->TankDrive(-1.00, -0.30, false);
			else if (period < 9.70)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 10.40)
				m_drive->TankDrive(-1.00, -0.30, false);
			else if (period < 10.60)
				m_drive->TankDrive(-0.30, -1.00, false);
			else
				m_drive->TankDrive(0.00, 0.00, false);
			break;

		//bounce
		case 2:
			if (period < 0.65)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 1.30)
				m_drive->TankDrive(-0.80, -1.00, false);
			else if (period < 1.70)
				m_drive->TankDrive(1.00, 1.00, false);
			else if (period < 2.30)
				m_drive->TankDrive(1.00, 0.90, false);
			else if (period < 3.15)
				m_drive->TankDrive(1.00, 0.00, false);
			else if (period < 3.60)
				m_drive->TankDrive(1.00, 0.25, false);
			else if (period < 4.40)
				m_drive->TankDrive(1.00, 1.00, false);
			else if (period < 5.35)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 6.60)
				m_drive->TankDrive(-0.25, -1.00, false);
			else if (period < 7.35)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 7.70)
				m_drive->TankDrive(-0.25, -1.00, false);
			else if (period < 8.30)
				m_drive->TankDrive(-1.00, -1.00, false);
			else if (period < 9.00)
				m_drive->TankDrive(0.30, 1.00, false);
			else if (period < 10.00)
				m_drive->TankDrive(0.00, 0.00, false);
			else
				m_drive->TankDrive(0.00, 0.00, false);
			break;
	}

}

// void Auton::AutonCase(int begin, int end)
// {
// 	switch (begin) {
// 		case 1: //right sensor
// 		enter_target_x = -2; //need sensor
// 		break;
// 		case 2: //straight on
// 		enter_target_x = 0;
// 		break;
// 		case 3: //left sensor
// 		enter_target_x = 5; //need sensor
// 		break;
// 	}

// 	enter_target_y = lineToWall;
	
// 	switch (end) {
// 		case 1: //Our trench
// 			exit_target_x = -2.009775;
// 			exit_target_y = 3.048;
// 			break;
// 		case 2: //Shield Generator
// 			exit_target_x = -3.17931851816;
// 			exit_target_y = -5.248275;
// 			break;
// 		case 3: //Enemy trench
// 			exit_target_x = 3.851275;
// 			exit_target_y = 5.248275;
// 			break;
// 	}

// 	enter_target_ang = atan2(enter_target_y, enter_target_x);
// 	exit_target_ang  = atan2(exit_target_y, exit_target_x);
// 	enter_target_dist = sqrt(enter_target_x * enter_target_x + enter_target_y * enter_target_y);
// 	exit_target_dist = sqrt(exit_target_x * exit_target_x + exit_target_y * exit_target_y);
// 	//here set up what happens at the end (after delivery)
// }

// void Auton::AutonDrive(double period)
// {
// 	// if (!m_ahrs->IsCalibrating()) {
// 		switch (auton_phase) {
// 			case 0: // turn to target
// 			if (turnToFace(enter_target_ang)) {
// 				auton_phase++;
// 				travelled_dist = 0;
// 			}
// 			break;
// 			case 1: // drive to target
// 			if (SmartDashboard::GetBoolean("Limelight Found", false) || driveToCoordinates(enter_target_x, enter_target_y, enter_target_ang, period)) { // dashboard not in yet
// 				auton_phase++;
// 			}
// 			break;
// 			case 2: // turn straight
// 			// THIS IS LIMELIGHT-CONTROLLED MOVEMENT 
// 			break;
// 			case 3: // drive to wall
// 			if (driveToCoordinates(0, .5, PI / 2, period)) { // THIS SHOULD BE DRIVING AFTER LIMELIGHT DOESN'T SENSE ANYMORE
// 				auton_phase++;
// 			}
// 			break;
// 			case 4: //delivers balls
// 			m_ballIntake->Yeet();
// 			if (m_ballIntake->GetBallCount() == 0) {
// 				auton_phase++;
// 				travelled_dist = 0;
// 			}
// 			break;
// 			case 5: //give us a little space to turn around (can be lowered)
// 			travelled_dist += m_drive->GetVelocity() * period;
// 			m_drive->TankDrive(-.5, -.5, false);
// 			if (travelled_dist < -.5) { // guess
// 				auton_phase++;
// 			}
// 			break;
// 			case 6: //turn around
// 			if (turnToFace(exit_target_ang)) {
// 				auton_phase++;
// 				travelled_dist = 0;
// 			}
// 			break;		
// 			case 7: //drive towards exit
// 			if (driveToCoordinates(exit_target_x, exit_target_y, exit_target_ang, period)) {
// 				auton_phase++;
// 			}
// 			break;
// 			case 8: //collect balls if warrented
// 			//I don't know if the followBall will work the way I put it
// 			if (m_pi->FollowBall()) {
// 				//Currently not in code
// 				m_ballIntake->StartIntake();
// 				if (m_ballIntake->GetBallCount() == 3)
// 					auton_phase++;
// 			}
// 			break;
// 			// default: //end
// 			// 	//return true;
// 			// 	break;
// 			// add more once we get there
// 		}
// 	// }
	
// 	frc::SmartDashboard::PutNumber ("Auton Phase", auton_phase);
// 	//frc::SmartDashboard::PutNumber("enterance angle offset", angleOffset(enter_target_ang) * 180 / PI);
// 	//frc::SmartDashboard::PutNumber("exit angle offset", angleOffset(exit_target_ang) * 180 / PI);
// 	frc::SmartDashboard::PutNumber("ahrs_ang", m_ahrs->GetAngle() + 90);
// 	frc::SmartDashboard::PutNumber("enter_target_ang", enter_target_ang);
// 	frc::SmartDashboard::PutNumber("exit_target_ang", exit_target_ang);
// 	frc::SmartDashboard::PutNumber("enter_target_x", enter_target_x);
// 	frc::SmartDashboard::PutNumber("exit_target_x", exit_target_x);
// 	frc::SmartDashboard::PutNumber("enter_target_y", enter_target_y);
// 	frc::SmartDashboard::PutNumber("exit_target_y", exit_target_y);
// 	frc::SmartDashboard::PutNumber("displ_x", m_ahrs->GetDisplacementX());
// 	frc::SmartDashboard::PutNumber("displ_y", m_ahrs->GetDisplacementY());
// 	frc::SmartDashboard::PutNumber("enter dist offset", sqrt(pow(enter_target_x - m_ahrs->GetDisplacementX(), 2) + pow(enter_target_y - m_ahrs->GetDisplacementY(), 2)));
// 	frc::SmartDashboard::PutNumber("exit dist offset", sqrt(pow(exit_target_x - m_ahrs->GetDisplacementX(), 2) + pow(exit_target_y - m_ahrs->GetDisplacementY(), 2)));
// }

void Auton::driveTo(double dis, double period, double recursion)
{
	travelled_dist += -1 * ((WHEEL_CIRCUMFERENCE * m_drive->GetVelocity() * period) 
	* GEAR_RATIO);
	SmartDashboard::PutNumber("velocity", -1 * (m_drive->GetVelocity()));
	SmartDashboard::PutNumber("period", period);
	SmartDashboard::PutNumber("sensesd travel", travelled_dist);
	m_drive->TankDrive(-.1*pow(E,2-4.605*(recursion/1000)),-.1*pow(E,2-4.605*(recursion/1000)),false);
	if(dis != travelled_dist){
		driveTo((dis*0.0000000511117)-travelled_dist, period, recursion+1.60943791/10);
	}
}


bool Auton::turnToFace(double angle)
{
	double prev_error = p_temp;
	p_temp = angleOffset(angle);
	frc::SmartDashboard::PutNumber("p_temp", p_temp);
	if (abs(p_temp) < turningErrorThreshold) {
		return true;
	}
	i_temp += p_temp;
	d_temp = p_temp - prev_error;
	double pid_result = pTurn * p_temp + iTurn * i_temp + dTurn * d_temp;
	if (pid_result > 0) {
		m_drive->TankDrive(min(pid_result, maxTurnSpeed), -min(pid_result, maxTurnSpeed), false);
	} else {
		m_drive->TankDrive(max(pid_result, -maxTurnSpeed), -max(pid_result, -maxTurnSpeed), false);
	}
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

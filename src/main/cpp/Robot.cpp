#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
  cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera(REAR_CAMERA);  // Initialize Camera
  // camera.SetResolution(160, 90);    // Only use these two lines if needed
  // camera.SetFPS(15);
  
    try {
      m_xbox        = new frc::XboxController(XBOX);
      m_leftStick   = new frc::Joystick(LEFT_JOY);
      m_rightStick  = new frc::Joystick(RIGHT_JOY);
      m_climb_solenoid = new frc::DoubleSolenoid(PCM, CLIMB_DEPLOY, CLIMB_EXHAUST);
      m_drive       = new DalekDrive(LEFT_FRONT_DRIVE, LEFT_REAR_DRIVE, RIGHT_FRONT_DRIVE, RIGHT_REAR_DRIVE, DalekDrive::driveType::kDifferential);
      m_ahrs        = new AHRS(SPI::Port::kMXP);
      m_pi          = new RaspberryPi(m_drive);
      m_compressor  = new frc::Compressor(PCM);
      m_ballIntake  = new BallIntake(m_xbox);
      m_spinner     = new Spinner(m_xbox,m_climb_solenoid);
      m_auton       = new Auton(m_drive, m_ahrs, m_pi, m_ballIntake, m_spinner);
      #ifndef CYAN_ROBOT
        m_climber     = new Climber(m_xbox,m_climb_solenoid);
      #endif
      //m_limelight   = new Limelight(m_drive);
    }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }
  // frc::SmartDashboard::PutNumber("Start Auton", 2);
  // frc::SmartDashboard::PutNumber("End Auton", 2);
  frc::SmartDashboard::PutNumber("Delay", 0);
  frc::SmartDashboard::PutBoolean("Auton Ready", true);
  // frc::SmartDashboard::PutNumber("Delay Phase", 0);
  // frc::SmartDashboard::PutNumber("Auton Phase", 0);
  // frc::SmartDashboard::PutBoolean("Pickup Ball End", false);
  // frc::SmartDashboard::PutBoolean("Pickup Ball Start", false);
  // frc::SmartDashboard::PutBoolean("Galactic Search", true);
  // frc::SmartDashboard::PutNumber("Path", 0);
  frc::SmartDashboard::PutNumber("Mode", 0);
  //frc::SmartDashboard::PutNumber("Starting # of Balls", 3);

  m_ahrs->ZeroYaw();
  m_ahrs->Reset();
  m_ahrs->ResetDisplacement();
  m_compressor->Start();

  timeElapsed = 0;
}

void Robot::RobotPeriodic()
{

}

// I think I have some errors here, I wanna test this
void Robot::AutonomousInit()
{
  //auton_start = 2;//(int)frc::SmartDashboard::GetData("Start Auton");
  //auton_end =   1;//(int)frc::SmartDashboard::GetData("End Auton");
  //waitSeconds = 0;//(int)frc::SmartDashboard::GetData("Delay");
  //m_auton->AutonCase((int)auton_start, (int)auton_end); // the parameters change based on what auton sequence we are going to use
  
  //This is not seeing it
  //autonChallenge = frc::SmartDashboard::GetData("Galactic Search");

  #ifndef CYAN_ROBOT
    m_climber->Reinit();
    m_spinner->Reinit();
  #endif
  m_ballIntake->Reinit();
  //frc::SmartDashboard::PutBoolean("Auton Done", false);
  //path = frc::SmartDashboard::GetNumber("Path", 0);
}

void Robot::AutonomousPeriodic() 
{
  //waits for the amount of seconds defined by "Delay" in the smart dashboard
  //after total elapsed time >= the "Delay", execute autonomous code
	timeElapsed += (double)this->GetPeriod();
	if (timeElapsed >= (double)(int)frc::SmartDashboard::GetData("Delay"))
    m_auton->startGame((int)frc::SmartDashboard::GetData("Mode"), (double)this->GetPeriod());
}

void Robot::TeleopInit()
{
  #ifndef CYAN_ROBOT
    m_climber->Reinit();
    m_spinner->Reinit();
  #endif
  m_ballIntake->Reinit();
}

void Robot::TeleopPeriodic()
{
    if (m_rightStick->GetTrigger() || m_leftStick->GetTrigger())
    m_pi->FollowBall();
    else if (m_rightStick->GetRawButton(4))
      m_drive->TankDrive(m_leftStick->GetY() * 0.30, m_rightStick->GetY() * 0.30, false);
    else
      m_drive->TankDrive(m_leftStick, m_rightStick, false);

	m_ballIntake->Tick();
  m_climber->Tick();
  if (!m_climber->isClimberEngaged())
    m_spinner->Tick();

  //m_limelight->Update();
  // if (m_drive) {
  //   if (m_rightStick->GetTrigger() || m_leftStick->GetTrigger()) {
  //       m_limelight->LineUp();
  //   }
  // }

}

void Robot::TestInit()
{

}

void Robot::TestPeriodic()
{

}

void Robot::DisabledInit()
{
  #ifndef CYAN_ROBOT
    m_climber->DisabledInit();
  #endif
}


#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif

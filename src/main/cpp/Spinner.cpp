#include "Euler.h"

Spinner::Spinner(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid)
{
    init(xbox, climb_solenoid);
}

void
Spinner:: init(frc::XboxController *xbox, DoubleSolenoid *climb_solenoid)
{
    //const int kTimeoutMs = 30;
    //const bool kSensorPhase = false;
    //const bool kInvert = false;

    m_xbox = xbox;
    //m_climb_solenoid = climb_solenoid;
	m_spinner = new WPI_TalonSRX(SPINNER);
    if(m_spinner == NULL)
        std::bad_alloc();
    //m_spinner->ConfigFactoryDefault();
	//m_spinner->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	//m_spinner->SetSensorPhase(kSensorPhase);
	//m_spinner->SetInverted(kInvert);
    //m_spinner->SetSelectedSensorPosition(0, 0, kTimeoutMs);
   	//m_spinner_solenoid = new frc::DoubleSolenoid(PCM, SPINNER_DEPLOY, SPINNER_EXHAUST);
    //if(m_spinner_solenoid == NULL)
        //std::bad_alloc();
    //m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}


Spinner::~Spinner()
{
    free(m_spinner);
    //free(m_spinner_solenoid);
}

void Spinner::Reinit()
{
    //const int kTimeoutMs = 30;
    //m_spinner->SetSelectedSensorPosition(0, 0, kTimeoutMs);
    //m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}

void
Spinner::Tick()
{
    // float encoderCnt = m_spinner->GetSensorCollection().GetQuadraturePosition();

    // frc::SmartDashboard::PutNumber("SpinnerEncoder", encoderCnt);
    // frc::SmartDashboard::PutNumber("Approx Color Wheel rotations", encoderCnt/NUM_TICKS_PER_COLOR_WHEEL_REV);

    // if (m_xbox->GetYButtonPressed()) {
    //     if (m_spinner_solenoid->Get() == frc::DoubleSolenoid::kForward){
    //         m_climb_solenoid->Set(frc::DoubleSolenoid::kOff);
    //         m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
    //     } else {
    //         m_climb_solenoid->Set(frc::DoubleSolenoid::kReverse);
    //         m_spinner_solenoid->Set(frc::DoubleSolenoid::kForward);
    //     }
    //  }

    // if (m_spinner_solenoid->Get() == frc::DoubleSolenoid::kForward) {
    //     if (m_xbox->GetXButton()) {
    //         m_spinner->Set(1);
    //     } else {
    //         m_spinner->Set(0.0);
    //     }
    // } else {
    //     m_spinner->Set(0.0);
    // }

    if (m_xbox->GetX(frc::GenericHID::kRightHand) < -0.5) {
        m_spinner->Set(0.25); //0.65
    }
    else if (m_xbox->GetY(frc::GenericHID::kRightHand) > 0.5) {
        m_spinner->Set(0.77);
    }
    else if (m_xbox->GetX(frc::GenericHID::kRightHand) > 0.5) {
        m_spinner->Set(0.85);
    }
    // else if (m_xbox->GetY(frc::GenericHID::kRightHand) < -0.5) {
    //     m_spinner->Set(0.30);
    // }
    else if (m_xbox->GetY(frc::GenericHID::kRightHand) < -0.5) {
        m_spinner->Set(-0.50);
    }
    else {
        m_spinner->Set(0.00);
    }
}

void
Spinner::autonTick(int mode) {
    switch (mode) {
        case 0:
            m_spinner->Set(0.0);
            break;
        case 1:
            m_spinner->Set(0.80);
            break;
        default:
            m_spinner->Set(0.0);
            break;
    }
}
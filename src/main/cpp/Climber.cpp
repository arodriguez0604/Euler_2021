#include "Euler.h"

Climber::Climber(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid)
{
    init(xbox, climb_solenoid);
    frc::SmartDashboard::PutNumber("Right Joystick Thing X", 0);
    frc::SmartDashboard::PutNumber("Right Joystick Thing Y", 0);
}

void
Climber:: init(frc::XboxController *xbox, DoubleSolenoid *climb_solenoid)
{
    m_xbox = xbox;
	m_trolley = new WPI_TalonSRX(TROLLEY);
    if(m_trolley == NULL)
        std::bad_alloc();
    m_trolley->ConfigFactoryDefault();
    m_lift = new WPI_TalonSRX(LIFT); //temp: LIFT
    if(m_lift == NULL)
        std::bad_alloc();
    m_lift->ConfigFactoryDefault();
	m_ratchet_solenoid = new frc::Solenoid(PCM, RATCHET_LOCK);
    if(m_ratchet_solenoid == NULL)
        std::bad_alloc();
    m_ratchet_solenoid->Set(false);
	m_climb_solenoid = climb_solenoid;
    if(m_climb_solenoid == NULL)
        std::bad_alloc();
    m_climb_solenoid->Set(frc::DoubleSolenoid::kReverse);
}

Climber::~Climber()
{
    free(m_trolley);
    free(m_lift);
    free(m_ratchet_solenoid);
    free(m_climb_solenoid);
}

void
Climber::Reinit()
{
    m_climb_solenoid->Set(frc::DoubleSolenoid::kReverse);
    m_ratchet_solenoid->Set(true); 
}

void 
Climber::DisabledInit()
{
    m_ratchet_solenoid->Set(false); 
}

void
Climber::Tick()
{
    frc::SmartDashboard::PutBoolean("ratchet solenoid:", m_ratchet_solenoid->Get());
    frc::SmartDashboard::PutNumber("Xbox POV: ", m_xbox->GetPOV(0));

    if (m_xbox->GetBackButtonPressed()) {
        if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kReverse) {
            m_climb_solenoid->Set(frc::DoubleSolenoid::kForward);
            m_ratchet_solenoid->Set(true);
        } else if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward)
            m_climb_solenoid->Set(frc::DoubleSolenoid::kOff); //do not set back to kReverse or arm crashes down
    }

    if (m_xbox->GetBButtonPressed()) {
        m_ratchet_solenoid->Set(!m_ratchet_solenoid->Get());
    }

    if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward) {
        double motorSpeed = m_xbox->GetY(frc::GenericHID::kLeftHand) * -1;
        m_ratchet_solenoid->Set(motorSpeed > 0); 
        m_lift->Set(motorSpeed);
    } else {
        m_lift->Set(0.0);
    }

    if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward) {
        // if (m_xbox->GetX(frc::GenericHID::kRightHand) < -0.5) {
        //     m_trolley->Set(0.60);
        // }
        // else if (m_xbox->GetY(frc::GenericHID::kRightHand) > 0.5) {
        //     m_trolley->Set(0.77);
        // }
        // else if (m_xbox->GetX(frc::GenericHID::kRightHand) > 0.5) {
        //     m_trolley->Set(0.85);
        // }
        // else if (m_xbox->GetY(frc::GenericHID::kRightHand) < -0.5) {
        //     m_trolley->Set(0.30);
        // }
        // else if (m_xbox->GetY(frc::GenericHID::kLeftHand) < -0.5) {
        //     m_trolley->Set(-0.50);
        // }
        // else {
        //     m_trolley->Set(0.00);
        // }

        frc::SmartDashboard::PutNumber("Right Joystick Thing X", m_xbox->GetX(frc::GenericHID::kRightHand));
        frc::SmartDashboard::PutNumber("Right Joystick Thing Y", m_xbox->GetY(frc::GenericHID::kRightHand));
        
        m_trolley->Set(m_xbox->GetX(frc::GenericHID::kRightHand) * -1);
   } else {
        m_trolley->Set(0.0);
    }
}

void
Climber::DisengageRatchet()
{
    m_ratchet_solenoid->Set(true);
}

void
Climber::EngageRatchet()
{
    m_ratchet_solenoid->Set(true);
}
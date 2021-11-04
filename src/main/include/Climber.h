#pragma once

using namespace frc;

#define RATCHETENGAGED false
#define RATCHETDISENGAGED true

class Climber {
	public:
	Climber(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid);
	~Climber();
    void Tick();
	void Reinit();
	void DisabledInit();
	void DisengageRatchet();
	void EngageRatchet();
	
	private:
	WPI_TalonSRX *m_trolley, *m_lift;
	XboxController *m_xbox;
	frc::Solenoid *m_ratchet_solenoid;
	frc::DoubleSolenoid *m_climb_solenoid;

	void init(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid);
};
#include "Euler.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
	//std::shared_ptr<NetworkTable> limelightPos = NetworkTable::GetTable("limelight");
}

// void Limelight::Update() {
//     // SmartDashboard::PutNumber("tv", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0));
//     // SmartDashboard::PutNumber("tshort", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tshort", 0.0));
// 	// SmartDashboard::PutNumber("thor", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("thor", 0.0));
//     SmartDashboard::PutNumber("tx", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0));
// 	SmartDashboard::PutNumber("ty", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0));
// 	SmartDashboard::PutNumber("ta", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0));

// 	// set a variable distance using a linear regression of ax+b using tvert on desmos
// }

// // void Limelight::LineUp() {
// // 	if (nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0) > .5) {
// // 		//m_drive->TankDrive(.2, .2, false);
// // 		SmartDashboard::PutBoolean("Limelight can see", true);
// // 	}
// // 	else {
// // 		//m_drive->TankDrive(0.0, 0.0, false);4
// // 		SmartDashboard::PutBoolean("Limelight can see", false);
// // 	}
// // }

// void Limelight::LightOff() {
// 	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
// }

// void Limelight::LightOn() {
// 	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
// }

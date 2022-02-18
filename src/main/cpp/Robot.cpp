// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/PWMTalonSRX.h>
#include <frc/motorcontrol/MotorController.h>

using namespace frc;
int L1 = 4;
int R1 = 5;
int L2 = 6;
int R2 = 7;

class Robot : public frc::TimedRobot {
  PWMTalonSRX m_frontLeft{1};
  PWMTalonSRX m_rearLeft{0};
  MotorControllerGroup m_left{m_frontLeft, m_rearLeft};

  PWMTalonSRX m_frontRight{2};
  PWMTalonSRX m_rearRight{3};
  MotorControllerGroup m_right{m_frontRight, m_rearRight};

  DifferentialDrive m_robotDrive{m_left, m_right};

  PWMTalonSRX m_storageBack{4};
  PWMTalonSRX m_storageFront{5};
  PWMTalonSRX m_rampLeft{6};
  PWMTalonSRX m_rampRight{7};
  Joystick m_stick{0};

  float deez, nuts, ballStorage, ramp;

  void storageIntake(){
    m_storageBack.Set(0.5);
    m_storageFront.Set(0.5);
  }
  void storageOuttake(){
    m_storageBack.Set(-0.8);
    m_storageFront.Set(-0.8);
  }
  void storageStationary(){
    m_storageBack.Set(0);
    m_storageFront.Set(0);
  }
  void rampIntake(){
    m_rampLeft.Set(0.5);
    m_rampRight.Set(-0.5);
  }
  void rampOuttake(){
    m_rampLeft.Set(1);
    m_rampRight.Set(-1);
  }
  void rampStationary(){
    m_rampLeft.Set(0);
    m_rampRight.Set(0);
  }

public:
  void RobotInit() override {
    m_left.SetInverted(true);
  }

  void TeleopPeriodic() override {
    /* CODE FOR THE THINGY THING
    if (m_stick.GetRawButtonPressed(L1)) {
      storageIntake();
    }else if (m_stick.GetRawButtonReleased(L1)) {
      storageStationary();
    }
    if (m_stick.GetRawButtonPressed(R1)) {
      storageOuttake();
    }else if (m_stick.GetRawButtonReleased(R1)) {
      storageStationary();
    }

    if (m_stick.GetRawButtonPressed(L2)) {
      rampIntake();
    }else if (m_stick.GetRawButtonReleased(L2)) {
      rampStationary();
    }
    if (m_stick.GetRawButtonPressed(R2)) {
      rampOuttake();
    }else if (m_stick.GetRawButtonReleased(R2)) {
      rampStationary();
    }
    */
    deez = (-m_stick.GetRawAxis(5))*1;
    nuts = m_stick.GetRawAxis(2)*1;
    m_robotDrive.ArcadeDrive(deez, nuts);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
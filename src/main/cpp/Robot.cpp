// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/PWMTalonSRX.h>
#include <frc/motorcontrol/MotorController.h>
#include <frc/Servo.h>

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
  PWMTalonSRX m_intake{6};
  PWMTalonSRX m_outtake{7};

  Servo cameraX{8};
  Servo cameraY{9};

  Joystick c_ps5{0};
  Joystick c_flightStick{1};

  float deez, nuts, ballStorage, ramp;

public:
  void RobotInit() override {
    m_left.SetInverted(true);
  }

  void TeleopPeriodic() override {
    checkButtons();
    cameraControls();

    deez = (-c_ps5.GetRawAxis(5))*1;
    nuts = c_ps5.GetRawAxis(2)*1;
    m_robotDrive.ArcadeDrive(deez, nuts);
  }

  void checkButtons(){
    if (c_ps5.GetRawButtonPressed(L1)) {
      m_storageBack.Set(0.5);
      m_storageFront.Set(0.5);
    }else if (c_ps5.GetRawButtonPressed(R1)) {
      m_storageBack.Set(-0.5);
      m_storageFront.Set(-0.5);
    }else{
      m_storageBack.Set(0);
      m_storageFront.Set(0);
    }

    if (c_ps5.GetRawButtonPressed(L2)) {
      m_intake.Set(0.5);
    }else{
      m_intake.Set(0);
    }
    if (c_ps5.GetRawButtonPressed(R2)) {
      m_outtake.Set(1);
    }else{
      m_outtake.Set(0);
    }
  }

  void cameraControls(){
    cameraX.Set(c_flightStick.GetRawAxis(0));
    cameraY.Set(-c_flightStick.GetRawAxis(1));
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
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
#include <stdio.h>
#include <iostream>

using namespace frc;

class Robot : public frc::TimedRobot {
  PWMTalonSRX m_frontLeft{0};
  PWMTalonSRX m_rearLeft{1};
  MotorControllerGroup m_left{m_frontLeft, m_rearLeft};

  PWMTalonSRX m_frontRight{2};
  PWMTalonSRX m_rearRight{3};
  MotorControllerGroup m_right{m_frontRight, m_rearRight};

  DifferentialDrive m_robotDrive{m_left, m_right};

  PWMTalonSRX m_storageBack{4};
  PWMTalonSRX m_storageFront{5};
  PWMTalonSRX m_intake{6};
  PWMTalonSRX m_outtake{7};

  Joystick c_ps5{0};

  float deez, nuts;

public:
  void RobotInit() override {
    m_left.SetInverted(true);
  }

  void TeleopPeriodic() override {
    checkButtons();

    deez = (-c_ps5.GetRawAxis(5))*1;
    nuts = c_ps5.GetRawAxis(2)*1;
    m_robotDrive.ArcadeDrive(deez, nuts);
  }

  void checkButtons(){
    if(c_ps5.GetRawButton(5)){
      m_storageBack.Set(-0.25);
      m_storageFront.Set(-0.25);
    }else if(c_ps5.GetRawButton(6)){
      m_storageBack.Set(0.25);
      m_storageFront.Set(0.25);
    }else{
      m_storageBack.Set(0);
      m_storageFront.Set(0);
    }

    if (c_ps5.GetRawButton(7)){
      m_intake.Set((c_ps5.GetRawAxis(3)+1)/4);
    }else{
      m_intake.Set(0);
    }
    if (c_ps5.GetRawButton(8)){
      m_outtake.Set(-1);
    }else{
      m_outtake.Set(0);
    }
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
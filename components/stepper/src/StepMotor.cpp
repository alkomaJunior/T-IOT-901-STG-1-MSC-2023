/**
 * \file StepMotor.cpp
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief The main purpose of this component is to drive stepper motors motor on M5stack series
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "StepMotor.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

#define STEPMOTOR_I2C_ADDR 0x70

GRBL stepper_motor_driver = GRBL(STEPMOTOR_I2C_ADDR);

void StepMotor::step_motor_configuration() {
    Wire.begin(21, 22);
    stepper_motor_driver.Init(&Wire);
    stepper_motor_driver.setMode("distance");
}

void StepMotor::step_motor_run(int axes, int speed) {
    stepper_motor_driver.setMotor(axes,axes,axes, speed);
    stepper_motor_driver.setMotor(0,0,0,speed);
}

void StepMotor::step_motor_run_back(int axes, int speed) {
    stepper_motor_driver.setMotor(axes,axes,axes, speed);
}

void StepMotor::step_motor_unlock() {
    stepper_motor_driver.unLock();
}

void StepMotor::step_motor_wait_idle() {
    stepper_motor_driver.waitIdle();
}

String StepMotor::step_motor_status() {
    return stepper_motor_driver.readStatus().c_str();
}

StepMotor::StepMotor() = default;


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/

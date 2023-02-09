/**
 * \file main.cpp
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main component that manage tasks
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "../components/base/src/Base.h"

/**********************************************************************************************************************/
/* CLASS INSTANCES                                                                                                    */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PRIVATE CONSTANTS AND VARIABLES                                                                                    */
/**********************************************************************************************************************/

Preferences preferences;

/**********************************************************************************************************************/
/* PRIVATE FUNCTION PROTOTYPE                                                                                         */
/**********************************************************************************************************************/

// Setup public function methods prototype
static void board_main_configuration();
static void menu_configuration();

/**********************************************************************************************************************/
/* PRIVATE FUNCTION CODE                                                                                              */
/**********************************************************************************************************************/

static void board_main_configuration()
{
    M5.begin(true, false, true, true);
    M5.Power.begin(); // Init power.
}

static void menu_configuration()
{
    M5ez::begin();
}

/**********************************************************************************************************************/
/* PUBLIC FUNCTION CODE                                                                                               */
/**********************************************************************************************************************/

void setup() {
    // Menu configuration
    menu_configuration();

    // Board main configuration
    board_main_configuration();

    // For restructuring packages purpose
    StepMotor::step_motor_configuration();
    StepMotor::step_motor_run_back(10, 200);

    // read last product exit from the nvs
    preferences.begin("product-info", false);

    ServoMotor::servo_motor_configuration();
    ServoMotor::servo_motor_move_arm(MIDDLE_EXIT);

    preferences.end();
}

void loop() {

    if (WiFi.isConnected()) {
        M5ez::msgBox("Date...", "SMART CONVEYOR(SC) \n (no running tasks...)", "Menu");
        ezSettings::menu();
    }
    else {
        M5ez::msgBox("Date...", "WELCOME!!! \n (Please setup a Wi-Fi connection to continue!!!)", "Menu");
        ezSettings::start_menu();
    }
}




/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/

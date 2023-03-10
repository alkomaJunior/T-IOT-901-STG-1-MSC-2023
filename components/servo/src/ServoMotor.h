/**
 * \file ServoMotor.h
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main header of the ServoMotor component
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */

/**********************************************************************************************************************/
/* MAIN DEFINITIONS                                                                                                   */
/**********************************************************************************************************************/

#ifndef T_IOT_901_STG_1_SERVOMOTOR_H
#define T_IOT_901_STG_1_SERVOMOTOR_H

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "../../base/src/Base.h"

/**********************************************************************************************************************/
/* PUBLIC CLASS                                                                                                       */
/**********************************************************************************************************************/

class ServoMotor {

private:

/**********************************************************************************************************************/
/* PRIVATE ATTRIBUTES                                                                                                 */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE METHODS PROTOTYPES                                                                                         */
/**********************************************************************************************************************/

public:

/**********************************************************************************************************************/
/* PUBLIC ATTRIBUTES                                                                                                  */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

    ServoMotor(); // Default constructor prototype
    static void servo_motor_configuration();
    static void servo_motor_move_arm(uint16_t angle);
};


#endif //T_IOT_901_STG_1_SERVOMOTOR_H



/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/
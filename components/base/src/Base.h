/**
 * \file Base.h
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main header of the Base component
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */


/**********************************************************************************************************************/
/* MAIN DEFINITIONS                                                                                                   */
/**********************************************************************************************************************/

#ifndef BASE_H
#define BASE_H

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "main.h"

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/

enum BASE_EXIT_CODE {
    SUCCESS,
    ERROR,
    ALREADY_CHECKED,
    NO_PRODUCT_FOUND,
};

/**********************************************************************************************************************/
/* PUBLIC CLASS                                                                                                       */
/**********************************************************************************************************************/
class Base {

private:

/**********************************************************************************************************************/
/* PRIVATE ATTRIBUTES                                                                                                 */
/**********************************************************************************************************************/

    string token;
    string currentProductId;
    int currentWarehouse = -1;
    int currentProductExit = -1;

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

    /**
     * Connect to Wifi
     * @param WiFiMulti
     */
    static String wifi_connect(WiFiMulti * WiFiMulti);


    /**
     * @brief Get the product reference. This reference is used to identify the package in the WMS database
     * @param rfid_param
     * @return return the product reference or null if not found
     */
    static String readerCard(MFRC522 * rfid_param);

    /**
      * @brief Read the product from the WMS db and hydrate our product model
      * @param rfid_read_product_ref
      * @return return a success code or error code
      */
    int readProduct(const String& rfid_read_product_ref);


    /**
     * @brief handle the end of the transaction making API call with the status 1
     * @param movement_id
     * @return
     */
    void commitTransaction(int movement_id);

    /**
     * @brief This method is used to login and get the token
     * @param data
     * @return
     */
    void login(const String& data);

    string getToken();

    /**
     * @brief This method is used to print messages on M5Stack LCD
     * @param message
     * @return
     */
    static void printOnLCD(const string& message);

    /**
     * @brief This method is use to create a stock movement on the warehouse
     * @return the currentMovementId
     */
    int createMovement();

    /**
     * @brief This method is used to set the current warehouse Id
     * @param warehouse
     */
    void setCurrentWareHouse(int warehouse);

    /**
     * @brief This method is used to get the current warehouse Id
     * @return currentProductWarehouse
     */
    int getCurrentWareHouse() const;

    /**
     * @brief This method is used to get the current product Id
     * @return currentProductId
     */
    string getCurrentProductId();

    /**
     * @brief This method is used to set the current product Id
     * @param productId
     * @return
     */
    void setCurrentProductId(string productId);

    /**
     * @brief This method is used to set the current product exit
     * @param exit_value
     * @return
     */
    void setCurrentProductExit(int exit_value);

    /**
     * @brief This method is used to get the current product exit
     * @return currentProductExit
     */
    int getCurrentProductExit() const;
};
#endif




/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/
/**
 * \file Request.h
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main header of the Request component
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */


/**********************************************************************************************************************/
/* MAIN DEFINITIONS                                                                                                   */
/**********************************************************************************************************************/

#ifndef T_IOT_901_STG_1_REQUEST_H
#define T_IOT_901_STG_1_REQUEST_H

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "../../base/src/Base.h"

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/

enum HTTP_METHOD {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE
};

/**********************************************************************************************************************/
/* PUBLIC CLASS                                                                                                       */
/**********************************************************************************************************************/

class Request {

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

    /**
     * @brief This method is used to send a request with the method GET/POST/PUT/DELETE
     * @param url
     * @param data
     * @param useToken
     * @return
     */
    static String requestGeneric(const String& url, enum HTTP_METHOD method, const String& token = "", const String& data = "");

    /**
     * @brief This method is used to send a get request
     * @param url
     * @param data
     * @param useToken
     * @return
     */
    static String requestGet(const String& url, const String& token = "");

    /**
     * @brief This method is used to send a post request
     * @param url
     * @param data
     * @param useToken
     * @return
     */
    static String requestPost(const String& url, const String& data, const String& token = "");

    /**
     * @brief This method is used to send a put request
     * @param url
     * @param data
     * @param useToken
     * @return
     */
    static String requestPut(const String& url, const String& data, const String& token = "");
};


#endif //T_IOT_901_STG_1_REQUEST_H




/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/
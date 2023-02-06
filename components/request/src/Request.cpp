/**
 * \file Request.cpp
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief The main purpose of this component is handle API requests
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "Request.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

String Request::requestGet(const String& url, const String& token) {
    return Request::requestGeneric(url, HTTP_GET, token);
}

String Request::requestPost(const String& url, const String& data, const String& token) {
    return Request::requestGeneric(url, HTTP_POST, token, data);
}

String Request::requestPut(const String& url, const String& data, const String& token) {
    return Request::requestGeneric(url, HTTP_PUT, token, data);
}

String Request::requestGeneric(const String& url, enum HTTP_METHOD method, const String& token, const String& data) {
    // wait for Wi-Fi connection
    if ((WiFiClass::status() == WL_CONNECTED)) {
        WiFiClient client;
        HTTPClient http;

        M5.Lcd.print("[HTTP] begin...\n");

        // configure tagged server and url
        String uri = API_URL + url;

        http.begin(client, uri); //HTTP
        http.addHeader("Content-Type", "application/json");

        if (token.length() > 0) {
            const String HEADER = String(DOLAPIKEY);
            http.addHeader(HEADER, token);
        }

        // start connection and send HTTP header and body
        int httpCode = -1;
        switch(method) {
            case HTTP_GET:
                httpCode = http.GET();
                break;
            case HTTP_POST:
                httpCode = http.POST(data);
                break;
            case HTTP_PUT:
                httpCode = http.PUT(data);
                break;
            default:
                break;
        }

        // httpCode will be negative on error
        if (httpCode > 0) {
            // file found at server
            if (httpCode == HTTP_CODE_OK) {
                const String& payload = http.getString();
                return payload;
            }
        } else {
            const String& payload = http.getString();
            Serial.printf("[HTTP] GET... failed, error: %s\n", payload.c_str());
        }

        http.end();
    }

    return "";
}


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/
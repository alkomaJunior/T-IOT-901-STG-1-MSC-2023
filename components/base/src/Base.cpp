/**
 * \file Base.cpp
 * \author T_IOT_901_STG_1_MSC_2023 (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief The main purpose of this component is handle product scanning
 * \date Dec. 2022
 * \copyright This code is under the MIT license but administrated by EPITECH Organization Github Workspace
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "Base.h"
#include <utility>

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

            /********************************  Core methods ********************************/

String Base::wifi_connect(WiFiMulti * wiFiMulti) {
    String ip = "";

    for(uint8_t t = 4; t > 0; t--) {
        delay(DELAY);
    }

    // disable Access Point mode
    if(WiFiClass::getMode() & WIFI_AP) {
        WiFi.softAPdisconnect(true);
    }

    wiFiMulti->addAP(WIFI_SSID, WIFI_PASS);

    while(wiFiMulti->run() != WL_CONNECTED) {
        delay(DELAY/10);

        return "";
    }

    ip = WiFi.localIP().toString();
    M5.Lcd.printf("[SETUP] WiFi Connected %s\n", ip.c_str());

    return ip.c_str();
}

String Base::readerCard(MFRC522 * mfrc522) {
    String rfid_read = "";
    if (!mfrc522->PICC_IsNewCardPresent() || !mfrc522->PICC_ReadCardSerial()) {
        delay(200);

        return rfid_read;
    }

    if (mfrc522->uid.size > 0) {
        for (byte i = 0; i < mfrc522->uid.size; i++) {
            rfid_read += String(mfrc522->uid.uidByte[i], HEX);
        }
    }

    Serial.println(rfid_read);

    return rfid_read;
}

int Base::readProduct(const String& rfid_read_product_ref) {
    int return_value = BASE_EXIT_CODE::SUCCESS;

    if (!rfid_read_product_ref.isEmpty()) {
        // API response
        String uri = String("/products/ref/")  + rfid_read_product_ref;
        String api_response =  Request::requestGet(uri.c_str(), this->getToken().c_str());

        if (api_response.length()) {
            // Response deserialization
            const char* response_to_be_deserialized = api_response.c_str();
            JSONVar deserialized_response = JSON.parse(response_to_be_deserialized);

            Serial.println(deserialized_response);

            // Setting current productId
            //this->currentProductId = (string) deserialized_response["id"];
            setCurrentProductId((string) deserialized_response["id"]);

            // Setting current productWh
            string currentWhToBeConverted = (string) deserialized_response["fk_default_warehouse"];
            Serial.printf("wh : %s\n", currentWhToBeConverted.c_str());

            if (strcmp(currentWhToBeConverted.c_str(), "1") == 0) {
                //this->currentWarehouse = 1;
                setCurrentWareHouse(1);
            } else if (strcmp(currentWhToBeConverted.c_str(), "2") == 0) {
                //this->currentWarehouse = 2;
                setCurrentWareHouse(2);
            } else if (strcmp(currentWhToBeConverted.c_str(), "3") == 0) {
                //this->currentWarehouse = 3;
                setCurrentWareHouse(3);
            } else {
                //this->currentWarehouse = -1;
                setCurrentWareHouse(-1);
            }

            // Setting current productExit
            switch (this->currentWarehouse) {
                case 1: // Strasbourg
                    //this->currentProductExit = LEFT_EXIT;
                    setCurrentProductExit(LEFT_EXIT);
                    break;
                case 2: // Paris
                    //this->currentProductExit = MIDDLE_EXIT;
                    setCurrentProductExit(MIDDLE_EXIT);
                    break;
                case 3: // Lyon
                    //this->currentProductExit = RIGHT_EXIT;
                    setCurrentProductExit(RIGHT_EXIT);
                    break;
                default:
                    this->currentProductExit = -1;
                    break;
            }

            int movementId = (int) deserialized_response["array_options"]["options_movement_id"];

            Serial.printf("******************************\n");
            Serial.printf("product id : %s\n", this->currentProductId.c_str());
            Serial.printf("product warehouse : %d\n", this->currentWarehouse);
            Serial.printf("product exit : %d\n", this->currentProductExit);
            Serial.printf("movement id : %d\n", movementId);
            Serial.printf("******************************\n");

            if (movementId != 0) {
                return_value = BASE_EXIT_CODE::ALREADY_CHECKED;
            }
        } else {
            Base::printOnLCD(reinterpret_cast<basic_string<char> &&>("No product found : " + api_response));
            return_value = BASE_EXIT_CODE::NO_PRODUCT_FOUND;
        }
    }

    return return_value;
}

int Base::createMovement() {

    int currentMovementId = 0;
    // NOTE : Status 400 : Bad Request
    const string uri = "/stockmovements";
    const String data = String(R"({"product_id": )")  + this->getCurrentProductId().c_str()
                        + String(R"(,"warehouse_id": )") + this->getCurrentWareHouse()
                        + String(R"(,"qty": ")") + String(1)
                        + String("\"}");
    String response = Request::requestPost(uri.c_str(), data, this->token.c_str());

    if (response.length()) {
        currentMovementId = response.toInt();
    } else {
        Base::printOnLCD(reinterpret_cast<basic_string<char> &&>("No movement created : " + response));
    }

    return currentMovementId;
}

void Base::commitTransaction(int movement_id) {
    // Prepare url and data
    const string separator = "/products/";
    string uri = separator + this->currentProductId;
    const String data = String(R"({"array_options": {"options_movement_id": )") +
                        movement_id + String("}}");

    // API Response
    String response = Request::requestPut(uri.c_str(), data, this->token.c_str());

    // Response deserialization
    const char* response_to_be_deserialized = response.c_str();
    JSONVar deserialized_response = JSON.parse(response_to_be_deserialized);

    const String updated_product_id = deserialized_response["id"];

    // Test if the put method worked
    if (updated_product_id.compareTo(this->currentProductId.c_str()) != 0)   {
        Base::printOnLCD("ERROR: Transaction not committed");
        return;
    }
    this->currentProductId = "";
}

void Base::login(const String& data) {
    // API Response
    const String response = Request::requestPost("/login", data);

    // Response deserialization
    const char* response_to_be_deserialized = response.c_str();
    JSONVar deserialized_response = JSON.parse(response_to_be_deserialized);

    this->token = (string)deserialized_response["success"]["token"];

    Serial.printf("My final token : %s\n", this->token.c_str());
}

string Base::getToken() {
    return this->token;
}

void Base::printOnLCD(const string& message) {
    M5.Lcd.printf("%s\n", message.c_str());
}


            /********************************  Getters and Setters ********************************/

string Base::getCurrentProductId() {
    return this->currentProductId;
}

void Base::setCurrentProductId(string productId) {
    this->currentProductId = std::move(productId);
}

int Base::getCurrentProductExit() const {
    return this->currentProductExit;
}

void Base::setCurrentProductExit(int exit_value) {
    this->currentProductExit = exit_value;
}

int Base::getCurrentWareHouse() const {
    return this->currentWarehouse;
}

void Base::setCurrentWareHouse(int warehouse) {
    this->currentWarehouse = warehouse;
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/

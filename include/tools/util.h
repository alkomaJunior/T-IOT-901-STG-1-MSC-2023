//
// Created by Administrator on 20/01/2023.
//

#ifndef __UTIL_H__
#define __UTIL_H__

#include <esp_log.h>
#include "M5ez.h"

#define UNUSED __attribute__((unused))

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#define LOGE(...) ESP_LOGE(__func__, __VA_ARGS__)
#define LOGD(...) ESP_LOGD(__func__, __VA_ARGS__)
#define LOGI(...) ESP_LOGI(__func__, __VA_ARGS__)
#define LOGW(...) ESP_LOGW(__func__, __VA_ARGS__)

#define esp_based_m5stack M5
#define esp_based_m5stack_gui_root M5GFX
#define esp_based_m5stack_gui_cvs M5Canvas
#define esp_based_m5stack_gui_btn LGFX_Button
#define esp_based_m5stack_lcd M5.Lcd

#endif


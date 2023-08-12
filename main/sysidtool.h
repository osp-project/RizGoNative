#ifndef SYS_ID_TOOL_H // 防止头文件重复包含
#define SYS_ID_TOOL_H

#include <stdio.h>
#include <stdint.h>
#include <esp_wifi.h>

// 获取 ESP32-C3 的 MAC 地址并转换为一个 10 位数的 ID
uint32_t get_device_id();

#endif
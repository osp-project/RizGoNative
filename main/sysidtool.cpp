#include <stdio.h>
#include <stdint.h>
#include <esp_wifi.h>
#include <esp_mac.h>
#include <string.h>
#include <cmath>

// 获取 ESP32-C3 的 MAC 地址并转换为一个 10 位数的 ID
uint32_t get_device_id() {
    // 定义一个存储 MAC 地址的数组
    uint8_t mac[6];
    // 调用 eFuse API 获取 MAC 地址
    esp_efuse_mac_get_default(mac);
    // 将 MAC 地址转换为一个 12 位的十六进制字符串
    char hex[13];
    sprintf(hex, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    // 将字符串分成两个部分，每个部分有 6 位
    char part1[7];
    char part2[7];
    strncpy(part1, hex, 6);
    strncpy(part2, hex + 6, 6);
    part1[6] = '\0';
    part2[6] = '\0';
    // 将这两个部分分别转换为十进制数
    uint32_t num1 = strtol(part1, NULL, 16);
    uint32_t num2 = strtol(part2, NULL, 16);
    // 将这两个十进制数相加，并对 $10^{10}$ 取模，得到一个 10 位数的 ID
    uint32_t id = (num1 + num2) % (uint32_t) pow(10, 10);
    return id;
}
#include <stdio.h>
#include "esp_wifi.h"
#include <string.h>
#include "nvs_flash.h"
#include <cstring> // 包含memset函数的头文件

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START) {
        printf("Wi-Fi AP 已启动\n");
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        printf("无线设备 %02x:%02x:%02x:%02x:%02x:%02x 已加入, AID=%d\n",
                 event->mac[0], event->mac[1], event->mac[2], event->mac[3], event->mac[4], event->mac[5], event->aid);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        printf("无线设备 %02x:%02x:%02x:%02x:%02x:%02x 已离开, AID=%d\n",
                 event->mac[0], event->mac[1], event->mac[2], event->mac[3], event->mac[4], event->mac[5], event->aid);
    }
}

bool createap(const char* ssid_, const char* password_, uint8_t channel, uint8_t maxconn){
    uint8_t ssid[32] = {0};
    memcpy(ssid, (uint8_t*)ssid_, 32); // 使用memcpy函数将str所指向的内容复制到arr中
    uint8_t password[64] = {0};
    memcpy(password, (uint8_t*)password_, 64);

    if(strlen(ssid_) <= 0 || maxconn <= 0){
        return false;
    }

    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize TCP/IP protocol stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Create a default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_ap();

    wifi_init_config_t apcfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&apcfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

    //设置 Wi-Fi AP 的配置参数
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = {ssid[0], ssid[1], ssid[2], ssid[3], ssid[4], ssid[5], ssid[6], ssid[7], ssid[8], ssid[9], ssid[10], ssid[11], ssid[12], ssid[13], ssid[14], ssid[15], ssid[16], ssid[17], ssid[18], ssid[19], ssid[20], ssid[21], ssid[22], ssid[23], ssid[24], ssid[25], ssid[26], ssid[27], ssid[28], ssid[29], ssid[30], ssid[31]},
            .password = {password[0], password[1], password[2], password[3], password[4], password[5], password[6], password[7], password[8], password[9], password[10], password[11], password[12], password[13], password[14], password[15], password[16], password[17], password[18], password[19], password[20], password[21], password[22], password[23], password[24], password[25], password[26], password[27], password[28], password[29], password[30], password[31], password[32], password[33], password[34], password[35], password[36], password[37], password[38], password[39], password[40], password[41], password[42], password[43], password[44], password[45], password[46], password[47], password[48], password[49], password[50], password[51], password[52], password[53], password[54], password[55], password[56], password[57], password[58], password[59], password[60], password[61], password[62], password[63]},
            .ssid_len = (uint8_t)strlen(ssid_),
            .channel = channel,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .ssid_hidden = 0,
            .max_connection = maxconn,
            .beacon_interval = 100
        },
    };
    if (strlen(password_) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config)); //修改了接口类型参数

    //启动 Wi-Fi AP
    ESP_ERROR_CHECK(esp_wifi_start());

    return true;
}
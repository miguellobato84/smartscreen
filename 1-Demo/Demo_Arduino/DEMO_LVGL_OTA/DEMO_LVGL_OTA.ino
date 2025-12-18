#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"
#include "wifi_credentials.h"

// WiFi and OTA credentials loaded from wifi_credentials.h
// Copy wifi_credentials.h.example to wifi_credentials.h and configure

#define LVGL_PORT_ROTATION_DEGREE (90)

#include <demos/lv_demos.h>

lv_obj_t *label_wifi;

void setup_wifi() {
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✓ WiFi connected");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n✗ WiFi connection failed");
    }
}

void setup_ota() {
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    
    ArduinoOTA.onStart([]() {
        Serial.println("Starting OTA update...");
    });
    
    ArduinoOTA.onEnd([]() {
        Serial.println("\nUpdate complete");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
    });
    
    ArduinoOTA.begin();
    Serial.println("✓ OTA ready");
}

void setup() {
    Serial.begin(115200);
    Serial.println("\n=== ESP32-S3 LVGL + WiFi + OTA ===\n");
    
    // 1. WiFi
    setup_wifi();
    
    // 2. OTA
    if (WiFi.status() == WL_CONNECTED) {
        setup_ota();
    }
    
    // 3. Display
    Serial.println("Initializing display...");
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = EXAMPLE_LCD_QSPI_H_RES * EXAMPLE_LCD_QSPI_V_RES,
        .rotate = LV_DISP_ROT_90,
    };
    
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();
    
    // 4. UI
    bsp_display_lock(0);
    lv_demo_widgets();
    bsp_display_unlock();
    
    // 5. WiFi info
    delay(100);
    bsp_display_lock(0);
    label_wifi = lv_label_create(lv_scr_act());
    lv_obj_align(label_wifi, LV_ALIGN_TOP_LEFT, 10, 10);
    
    if (WiFi.status() == WL_CONNECTED) {
        lv_label_set_text_fmt(label_wifi, LV_SYMBOL_WIFI " %s\n%s", OTA_HOSTNAME, WiFi.localIP().toString().c_str());
        lv_obj_set_style_text_color(label_wifi, lv_color_hex(0x00FF00), 0);
    } else {
        lv_label_set_text(label_wifi, LV_SYMBOL_WARNING " No WiFi");
        lv_obj_set_style_text_color(label_wifi, lv_color_hex(0xFF0000), 0);
    }
    bsp_display_unlock();
    
    Serial.println("\n✓ System ready\n");
}

void loop() {
    ArduinoOTA.handle();
    delay(10);
}

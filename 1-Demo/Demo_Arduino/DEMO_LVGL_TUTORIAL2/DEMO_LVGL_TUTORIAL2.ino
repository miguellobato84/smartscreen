#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"
#include "wifi_credentials.h"

#define LVGL_PORT_ROTATION_DEGREE (90)

// Fallback values if wifi_credentials.h is missing
#ifndef WIFI_SSID
#define WIFI_SSID "YourSSID"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YourPassword"
#endif
#ifndef OTA_HOSTNAME
#define OTA_HOSTNAME "esp32-panel"
#endif
#ifndef OTA_PASSWORD
#define OTA_PASSWORD "admin123"
#endif

// Screen sleep/wake settings
#define SCREEN_TIMEOUT_MS 30000  // 30 seconds of inactivity
static uint32_t last_activity_time = 0;
static bool screen_is_on = true;

// ============================================================================
// WiFi and OTA Functions
// ============================================================================

void wifi_ota_setup_wifi(void)
{
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✓ WiFi connected");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("✗ WiFi connection failed");
    }
}

void wifi_ota_setup_ota(void)
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("✗ WiFi not connected, skipping OTA setup");
        return;
    }

    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    
    ArduinoOTA.onStart([]() {
        Serial.println("\n>>> Starting OTA update...");
    });
    
    ArduinoOTA.onEnd([]() {
        Serial.println("\n>>> Update complete, restarting...");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf(">>> Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("\n>>> Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });
    
    ArduinoOTA.begin();
    Serial.printf("✓ OTA ready: %s@%s (%s)\n", OTA_HOSTNAME, WiFi.localIP().toString().c_str(), OTA_PASSWORD);
}

void wifi_ota_handle(void)
{
    if (WiFi.status() == WL_CONNECTED) {
        ArduinoOTA.handle();
    }
}

bool wifi_ota_is_connected(void)
{
    return WiFi.status() == WL_CONNECTED;
}

// ============================================================================
// Screen timeout functions
// ============================================================================

static void reset_screen_timeout()
{
    last_activity_time = millis();
    if (!screen_is_on) {
        bsp_display_backlight_on();
        screen_is_on = true;
        Serial.println("Screen wake: touch detected");
    }
}

static void screen_activity_monitor(lv_event_t * e)
{
    reset_screen_timeout();
}

// ============================================================================
// LVGL UI Functions
// ============================================================================

static void tutorial2_on_btn_clicked(lv_event_t * e)
{
    lv_obj_t * label = (lv_obj_t *)lv_event_get_user_data(e);
    if (!label) return;
    static uint32_t clicks = 0;
    clicks++;
    lv_label_set_text_fmt(label, "Button clicked: %lu", (unsigned long)clicks);
    reset_screen_timeout();
}

static void tutorial2_on_slider_changed(lv_event_t * e)
{
    lv_obj_t * label = (lv_obj_t *)lv_event_get_user_data(e);
    if (!label) return;
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t val = lv_slider_get_value(slider);
    lv_label_set_text_fmt(label, "Brightness: %d%%", (int)val);
    reset_screen_timeout();
}

static void tutorial2_create_ui()
{
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_scr_load(scr);

    lv_obj_set_style_bg_color(scr, lv_color_hex(0x101418), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t * title = lv_label_create(scr);
    lv_label_set_text(title, "Tutorial 2: Custom LVGL UI");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 8);

    lv_obj_t * btn = lv_btn_create(scr);
    lv_obj_set_size(btn, 160, 60);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, -20);

    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click me");
    lv_obj_center(btn_label);

    lv_obj_t * status = lv_label_create(scr);
    lv_label_set_text(status, "Button clicked: 0");
    lv_obj_set_style_text_color(status, lv_color_hex(0xD0E6FF), 0);
    lv_obj_align(status, LV_ALIGN_CENTER, 0, 50);

    lv_obj_add_event_cb(btn, tutorial2_on_btn_clicked, LV_EVENT_CLICKED, status);

    lv_obj_t * slider = lv_slider_create(scr);
    lv_obj_set_width(slider, 240);
    lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_slider_set_range(slider, 0, 100);
    lv_slider_set_value(slider, 30, LV_ANIM_OFF);

    lv_obj_t * slider_label = lv_label_create(scr);
    lv_label_set_text(slider_label, "Brightness: 30%");
    lv_obj_set_style_text_color(slider_label, lv_color_hex(0xA0B8FF), 0);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -10);

    lv_obj_add_event_cb(slider, tutorial2_on_slider_changed, LV_EVENT_VALUE_CHANGED, slider_label);

    // Add touch activity monitor to the screen for wake-on-touch
    lv_obj_add_event_cb(scr, screen_activity_monitor, LV_EVENT_PRESSED, NULL);
}

// ============================================================================
// Arduino Setup and Loop
// ============================================================================

void setup()
{
    Serial.begin(115200);
    Serial.println("\n=== LVGL Tutorial 2 + WiFi + OTA ===");
    Serial.println();

    Serial.println("Initialize panel device");
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = EXAMPLE_LCD_QSPI_H_RES * EXAMPLE_LCD_QSPI_V_RES,
    #if LVGL_PORT_ROTATION_DEGREE == 90
        .rotate = LV_DISP_ROT_90,
    #elif LVGL_PORT_ROTATION_DEGREE == 270
        .rotate = LV_DISP_ROT_270,
    #elif LVGL_PORT_ROTATION_DEGREE == 180
        .rotate = LV_DISP_ROT_180,
    #elif LVGL_PORT_ROTATION_DEGREE == 0
        .rotate = LV_DISP_ROT_NONE,
    #endif
    };

    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    // WiFi and OTA setup
    wifi_ota_setup_wifi();
    if (wifi_ota_is_connected()) {
        wifi_ota_setup_ota();
    }

    Serial.println("Create UI");
    bsp_display_lock(0);
    tutorial2_create_ui();
    bsp_display_unlock();

    // Initialize screen timeout
    last_activity_time = millis();
    Serial.printf("Screen timeout enabled: %d seconds\n", SCREEN_TIMEOUT_MS / 1000);

    Serial.println("\n✓ System ready\n");
}

void loop()
{
    // Handle OTA updates
    wifi_ota_handle();

    // Check screen timeout
    if (screen_is_on && (millis() - last_activity_time > SCREEN_TIMEOUT_MS)) {
        bsp_display_backlight_off();
        screen_is_on = false;
        Serial.println("Screen sleep: timeout reached");
    }

    delay(10);
}

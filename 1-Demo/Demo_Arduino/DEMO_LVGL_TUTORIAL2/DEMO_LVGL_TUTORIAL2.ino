#include <Arduino.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"

// Optional WiFi/OTA scaffold: safely compile only if credentials exist
#if __has_include("wifi_credentials.h")
#include "wifi_credentials.h"
#define WIFI_ENABLED 1
#else
#define WIFI_ENABLED 0
#endif

#if WIFI_ENABLED
#include <WiFi.h>
#if __has_include(<ArduinoOTA.h>)
#include <ArduinoOTA.h>
#define OTA_LIB_AVAILABLE 1
#else
#define OTA_LIB_AVAILABLE 0
#endif
#endif

/**
 * Set the rotation degree:
 *      - 0: 0 degree
 *      - 90: 90 degree
 *      - 180: 180 degree
 *      - 270: 270 degree
 */
#define LVGL_PORT_ROTATION_DEGREE (90)

static void tutorial2_on_btn_clicked(lv_event_t * e)
{
    lv_obj_t * label = (lv_obj_t *)lv_event_get_user_data(e);
    if (!label) return;
    static uint32_t clicks = 0;
    clicks++;
    lv_label_set_text_fmt(label, "Button clicked: %lu", (unsigned long)clicks);
}

static void tutorial2_on_slider_changed(lv_event_t * e)
{
    lv_obj_t * label = (lv_obj_t *)lv_event_get_user_data(e);
    if (!label) return;
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t val = lv_slider_get_value(slider);
    lv_label_set_text_fmt(label, "Brightness: %d%%", (int)val);
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
    // Optional: show local IP if WiFi is enabled
#if WIFI_ENABLED
    if (WiFi.isConnected()) {
        lv_obj_t * ip_label = lv_label_create(scr);
        IPAddress ip = WiFi.localIP();
        char buf[64];
        snprintf(buf, sizeof(buf), "WiFi: %s\nIP: %u.%u.%u.%u",
                 WIFI_SSID,
                 (unsigned)ip[0], (unsigned)ip[1], (unsigned)ip[2], (unsigned)ip[3]);
        lv_label_set_text(ip_label, buf);
        lv_obj_set_style_text_color(ip_label, lv_color_hex(0x8EE5FF), 0);
        lv_obj_align(ip_label, LV_ALIGN_TOP_LEFT, 8, 36);
    }
#endif
}

void setup()
{
    String title = "LVGL Tutorial 2";

    Serial.begin(115200);
    Serial.println(title + " start");

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

    // Optional: Connect WiFi and start OTA if available
#if WIFI_ENABLED
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
    uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < 15000) {
        delay(250);
        Serial.print('.');
    }
    Serial.println();
    if (WiFi.isConnected()) {
        Serial.printf("WiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
#if OTA_LIB_AVAILABLE
        ArduinoOTA.setHostname(OTA_HOSTNAME);
        ArduinoOTA.setPassword(OTA_PASSWORD);
        ArduinoOTA.begin();
        Serial.printf("OTA ready at %s (%s)\n", OTA_HOSTNAME, WiFi.localIP().toString().c_str());
#endif
    } else {
        Serial.println("WiFi connect timeout; continuing without network.");
    }
#endif

    Serial.println("Create UI");
    bsp_display_lock(0);
    tutorial2_create_ui();
    bsp_display_unlock();

    Serial.println(title + " end");
}

void loop()
{
    // Handle OTA when available; otherwise simple idle loop
#if WIFI_ENABLED && OTA_LIB_AVAILABLE
    ArduinoOTA.handle();
#endif
    delay(50);
}

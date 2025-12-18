# está tar

## 🎯 Objectives

By completing this tutorial, you will have:
- ✅ Installed and configured Arduino IDE with ESP32 support
- ✅ Installed necessary libraries for LVGL
- ✅ Compiled and run basic LVGL example
- ✅ Configured OTA for WiFi updates

## 📋 Requirements

### Hardware
- ESP32-S3 JC3248W535EN board
- USB-C cable
- Computer (Windows, macOS, or Linux)

### Software
- Internet access
- Approximately 2GB of free disk space

## ⏱️ Estimated Time

**30-45 minutes**

---

## Step 1: Install Arduino IDE

### 1.1 Download Arduino IDE

1. Go to [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Download version 2.x for your operating system
3. Install following installer instructions

> **Note:** Arduino IDE 1.8.x also works, but version 2.x is recommended for better interface and features.

### 1.2 Verify Installation

1. Open Arduino IDE
2. You should see main interface without errors

---

## Step 2: Install ESP32 Support

### 2.1 Add Board Manager URL

1. In Arduino IDE, go to **File > Preferences** (or **Arduino IDE > Settings** on macOS)
2. In **"Additional Boards Manager URLs"**, add:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
3. Click **OK**

### 2.2 Install ESP32 Package

1. Go to **Tools > Board > Boards Manager**
2. Search for **"esp32"** by **Espressif Systems**
3. Install version **3.3.4** or later (3.0.2+ compatible)
4. Wait for download to finish (may take 5-10 minutes)

### 2.3 Verify Installation

1. Go to **Tools > Board > esp32**
2. Look for and select **"ESP32S3 Dev Module Octal (WROOM2)"**
3. If it appears, installation was successful

---

## Step 3: Verify USB Connection

### macOS (Recommended)

1. Connect your ESP32-S3 board with USB-C cable
2. In Arduino IDE, go to **Tools > Port**
3. You should see a port like: `/dev/cu.usbmodem1101 (ESP32 Family Device)`
4. Select it

> **Note:** macOS generally recognizes the board automatically. If you don't see a port, try another USB cable.

### Windows
- Driver should install automatically
- If not working, download CH340 or CP2102 driver depending on your board
- Look for ports like COM3, COM4, etc.

### Linux
```bash
sudo usermod -a -G dialout $USER
# Log out and back in
```

---

## Step 4: Copy Required Libraries

### 4.1 Locate Arduino Libraries Directory

- **Windows:** `C:\Users\<YourUser>\Documents\Arduino\libraries\`
- **macOS:** `~/Documents/Arduino/libraries/`
- **Linux:** `~/Arduino/libraries/`

### 4.2 Copy Project Libraries

1. Go to project folder: `1-Demo/Demo_Arduino/libraries/`
2. Copy **ALL** folders to your Arduino libraries directory:
   - `lvgl/`
   - `ESP32_JPEG/`
   - `ESP32-audioI2S-3.0.12/`
   - `JPEGDEC-1.6.1/`

### 4.3 Copy LVGL Configuration File

1. Inside the `lvgl/` folder you just copied
2. Find `lv_conf_template.h`
3. Rename it to `lv_conf.h` (remove `_template`)

> **Important:** Without this step, LVGL will not compile correctly.

### 4.4 Restart Arduino IDE

Close and reopen Arduino IDE so it detects the new libraries.

---

## Step 5: Configure ESP32-S3 Board

### 5.1 Connect Board

1. Connect your ESP32-S3 board to computer with USB-C cable
2. Wait for computer to recognize it

### 5.2 Configure Board Parameters

In **Tools**, set:

| Parameter | Value |
|-----------|-------|
| **Board** | ESP32S3 Dev Module Octal (WROOM2) |
| **USB CDC On Boot** | Enabled |
| **CPU Frequency** | 240MHz (WiFi) |
| **Flash Mode** | QIO 80MHz |
| **Flash Size** | 16MB (128Mb) |
| **Partition Scheme** | 16MB Flash (3MB APP/9.9MB FATFS) |
| **PSRAM** | OPI PSRAM |
| **Upload Mode** | UART0 / Hardware CDC |
| **Upload Speed** | 921600 |
| **Port** | Select the COM/USB port that appears |

> **Note:** If you don't see any port, check USB drivers.

### 5.3 Save Configuration (Optional but Recommended)

Arduino IDE 2.x automatically saves these settings, but for project-specific configuration, create a file named `arduino.json` in your sketch folder with:

```json
{
  "board": "esp32:esp32:esp32s3",
  "configuration": "CDCOnBoot=cdc,FlashMode=qio,FlashFreq=80,FlashSize=16M,PartitionScheme=fatfs,PSRAM=opi,DebugLevel=none,UploadSpeed=921600",
  "port": "/dev/cu.usbmodem1101"
}
```

This ensures consistent settings when opening the project later.

---

## Step 6: Test Basic LVGL Example

### 6.1 Open Example

1. Go to folder: `1-Demo/Demo_Arduino/DEMO_LVGL/`
2. Open file: `DEMO_LVGL.ino` in Arduino IDE

### 6.2 Verify Code

Check that these lines are present:

```cpp
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"

// Screen rotation
#define LVGL_PORT_ROTATION_DEGREE (90)

void setup() {
    Serial.begin(115200);
    // ... initialization code
    lv_demo_widgets(); // Active demo
}
```

### 6.3 Compile

1. Click **✓ Verify/Compile** button
2. Wait for compilation (first time may take 2-3 minutes)
3. Verify no errors

### 6.4 Upload to Board

1. Click **→ Upload** button
2. Wait for code to upload
3. You should see:
   ```
   Leaving...
   Hard resetting via RTS pin...
   ```

### 6.5 Verify Operation

1. **Serial Monitor:** Open serial monitor (🔍 icon or Ctrl+Shift+M)
2. Set to **115200 baud**
3. You should see:
   ```
   LVGL porting example start
   Initialize panel device
   Initialize LVGL
   Create UI
   LVGL porting example end
   ```

4. **Screen:** You should see an interface with widgets (buttons, sliders, charts)

🎉 **Congratulations! Your first LVGL application is working.**

---

## Step 7: Configure OTA (WiFi Updates)

### 7.1 Install ArduinoJson Library

1. Go to **Tools > Manage Libraries**
2. Search for **"ArduinoJson"**
3. Install version **6.x** (NOT 7.x)

### 7.2 Create Project with OTA

1. Copy entire `DEMO_LVGL/` folder
2. Rename to `DEMO_LVGL_OTA/`
3. Open `DEMO_LVGL_OTA.ino`

### 7.3 Replace with OTA Code

Replace file content with this code:

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"

// ===== WIFI CONFIGURATION =====
const char* ssid = "YOUR_WIFI";          // Change to your WiFi
const char* password = "YOUR_PASSWORD";  // Change to your password

// ===== OTA CONFIGURATION =====
const char* hostname = "esp32-panel";
const char* ota_password = "admin123";   // Change to secure password

#define LVGL_PORT_ROTATION_DEGREE (90)

#include <demos/lv_demos.h>

lv_obj_t *label_wifi;

void setup_wifi() {
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
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
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA.setPassword(ota_password);
    
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
        lv_label_set_text_fmt(label_wifi, LV_SYMBOL_WIFI " %s", WiFi.localIP().toString().c_str());
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
```

### 7.4 Configure Your Data

In the code, change:

```cpp
const char* ssid = "YOUR_WIFI";          // Your WiFi network
const char* password = "YOUR_PASSWORD";  // Your WiFi password
const char* ota_password = "admin123";   // OTA password
```

### 7.5 Upload Code

1. **Connect via USB** (this first time is necessary)
2. Click **→ Upload**
3. Wait for completion

### 7.6 Verify Operation

**Serial Monitor:**
```
=== ESP32-S3 LVGL + WiFi + OTA ===

Connecting to WiFi...
✓ WiFi connected
IP: 192.168.1.XXX
✓ OTA ready
Initializing display...
✓ System ready
```

**Screen:**
- You should see LVGL demo
- Top left: WiFi connected + your IP

### 7.7 Test OTA for First Time

1. **Disconnect USB cable** (ESP32 must stay powered)
2. In Arduino IDE:
   - Go to **Tools > Port**
   - You should see: **"esp32-panel at 192.168.1.XXX"**
   - Select it

3. Make small change in code (e.g., change hostname):
   ```cpp
   const char* hostname = "esp32-panel-v2";
   ```

4. Click **→ Upload**
5. It will ask for OTA password (the one you configured)
6. Wait for WiFi upload

🎉 **OTA working! You no longer need USB cable to update.**

---

## ✅ Final Verification

Upon completing this tutorial, you should have:

- [x] Arduino IDE configured with ESP32
- [x] LVGL libraries installed
- [x] LVGL example working on screen
- [x] WiFi connected
- [x] OTA configured and tested
- [x] WiFi info displayed on screen

---

## ⚠️ Troubleshooting

### Error: "lv_conf.h: No such file"

**Solution:** Rename `lv_conf_template.h` to `lv_conf.h` in lvgl folder

### Error: "USB port not detected"

**Solution:**
- Install CH340 or CP2102 driver
- Try another USB cable
- Press BOOT button while connecting

### Error: "Failed to connect"

**Solution:**
1. Hold **BOOT** button
2. Click **Upload**
3. When upload starts, release BOOT

### Blank screen

**Solution:**
- Verify PSRAM is set to "OPI PSRAM"
- Check screen rotation (try 0, 90, 180, 270)

### WiFi not connecting

**Solution:**
- Verify SSID and password
- Verify WiFi is 2.4GHz (not 5GHz)
- Move closer to router

### Not appearing in OTA

**Solution:**
- Verify ESP32 and computer are on same network
- Wait 30 seconds after powering on
- Restart Arduino IDE

---

## 📚 Additional Resources

- [LVGL v8 Documentation](https://docs.lvgl.io/8.3/)
- [ESP32 Arduino Core Docs](https://docs.espressif.com/projects/arduino-esp32/)
- [ArduinoOTA Library](https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA)

---

## 🎯 Next Steps

Now that you have environment configured and OTA working, you can:

1. **Explore LVGL demos** - Change `lv_demo_widgets()` to other demos
2. **Modify rotation** - Try different orientations
3. **Continue to Tutorial 2** - Create your first custom interface

---

**Tutorial created:** December 2025  
**Version:** 1.0  
**Next:** [Tutorial 2: Creating Your First LVGL Interface](02_first_lvgl_interface.md) (coming soon)

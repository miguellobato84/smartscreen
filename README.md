# JC3248W535EN - ESP32-S3 Display Development Kit

Complete development package for ESP32-S3 board with 3.5" IPS capacitive touch screen (480x320).

## 🎯 Project Status

**Last Updated:** December 18, 2025

### ✅ Tutorial 1: Completed (100%)

**Environment Setup:**
- ✅ Arduino IDE 2.3.7 configured
- ✅ ESP32 Package 3.3.4 installed
- ✅ All libraries installed (LVGL, ArduinoJson, ESP32-audioI2S, JPEGDEC, ESP32_JPEG)
- ✅ USB connection verified (macOS)

**Achievements:**
- ✅ DEMO_LVGL compiled and running (lv_demo_widgets working on physical display)
- ✅ WiFi connectivity configured and tested
- ✅ **OTA (Over-The-Air) updates fully functional** - wireless firmware deployment working
- ✅ Custom LVGL modifications (WiFi status display with hostname + IP)

**Current Hardware State:**
- Board: ESP32S3 Dev Module Octal (WROOM2)
- Network: Connected via WiFi
- OTA Status: Ready for wireless updates
- Display: 480x320 LVGL interface operational with 90° rotation

### 📝 Configuration

**Important:** This project uses `wifi_credentials.h` for WiFi/OTA settings. 

To configure:
```bash
cd 1-Demo/Demo_Arduino/DEMO_LVGL_OTA/
cp wifi_credentials.h.example wifi_credentials.h
# Edit wifi_credentials.h with your WiFi credentials
```

**Security Note:** `wifi_credentials.h` is gitignored - never commit personal credentials.

## 🛒 Product Information

### Where to Buy

**AliExpress:** [JC3248W535EN - 3.5" ESP32-S3 Display](https://es.aliexpress.com/item/1005008870532063.html)

**Specifications:**
- 3.5" IPS Capacitive Touch Screen
- Resolution: 480x320 pixels
- ESP32-S3 WROOM-1 Module
- 8MB PSRAM + 16MB Flash
- WiFi & Bluetooth

### Software Package Download

**Official Package:** [JC3248W535EN.zip](http://pan.jczn1688.com/directlink/1/HMI%20display/JC3248W535EN.zip)

- **Version:** Latest (check download page for updates)
- **Contents:** Demo code, drivers, documentation, and tools
- **Size:** ~500MB (includes all libraries and examples)

---

## 🔧 Hardware Specifications

- **Microcontroller:** ESP32-S3 WROOM-1
- **Display:** 3.5" IPS capacitive touch, 480x320 pixels
- **Memory:** 8MB PSRAM + 16MB Flash
- **Connectivity:** WiFi and Bluetooth integrated
- **Audio:** I2S Amplifier (AX98357/NS4168)
- **Display Controller:** AXS15231 (high-speed QSPI interface)
- **Storage:** microSD/TF card slot

---

## 📁 Project Structure

### 1-Demo/

Functional examples for Arduino with complete code:

#### **DEMO_LVGL**

- LVGL v8 graphics library demonstration
- Interactive user interface with widgets
- Screen rotation support (0°, 90°, 180°, 270°)
- Included examples: `lv_demo_widgets()`, `lv_demo_benchmark()`, `lv_demo_music()`

#### **DEMO_MJPEG**

- MJPEG video player
- Requires files in `mjpeg/` folder on SD card
- Requires PSRAM configured at 120MHz

#### **DEMO_MP3**

- MP3 audio player
- Requires files in `music/` folder on SD card
- I2S audio output

#### **DEMO_PIC**

- Image viewer
- Requires images in `pic/` folder on SD card
- Supports JPEG formats

### 2-Specification/

- **JC3248W535 Specifications-EN.pdf**: Complete product technical specifications

### 3-Structure_Diagram/

CAD files in DXF format:
- `Slot method 1.dxf`: Mounting/slot method 1
- `Slot method 2.dxf`: Mounting/slot method 2

### 4-Driver_IC_Data_Sheet/

Component datasheets:
- `esp32-s3_datasheet_en.pdf`: ESP32-S3 microcontroller datasheet
- `esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf`: WROOM module datasheet
- `AXS15231_Datasheet_V0.5_20230306.pdf`: Display controller
- `AX98357AETE T_2021-01-06.PDF`: Audio amplifier
- `Nsiway-NS4168.pdf`: Alternative audio amplifier

### 5-IO_pin_distribution/

- Hardware pin distribution diagrams (PNG images)

### 6-User_Manual/

- **Getting started JC3248W535.pdf**: Quick start guide

### 7-Character&Picture_Molding_Tool/

- Tools for converting images and characters for display use

### 8-Burn_operation/

- **flash_download_tool_3.9.3**: Official Espressif tool for flashing firmware
- **Burn files**: Pre-compiled binary files ready to flash
- **Burn operation instructions**: Flashing instructions

---

## ⚙️ Software Requirements

### Arduino Environment

- **Arduino IDE:** Compatible version
- **ESP32 Board Package:** **v3.0.2** (specific version required)
- **LVGL:** v8.3.9 or higher (but lower than v9)

### Included Libraries

The following libraries are included in `1-Demo/Demo_Arduino/libraries/`:
- `lvgl`: Graphics library (v8.x)
- `ESP32_JPEG`: JPEG decoder
- `ESP32-audioI2S`: I2S audio playback
- `JPEGDEC`: Additional JPEG decoder

---

## 🚀 Quick Start Guide

### 📖 Step-by-Step Tutorials

If you're a **beginner** or it's your **first time** with this hardware, start here:

**➡️ [Getting Started - Tutorials](getting_started/README.md)**

Includes complete tutorials on:
1. **Initial setup** - Install everything needed
2. **First project** - Test basic LVGL example
3. **OTA WiFi** - Update code wirelessly
4. **Custom interface** - Create your own widgets
5. **Home Assistant integration** - Smart home control

**Recommended:** Follow tutorials in order for best results.

---

## 🔧 Initial Setup

### 1. Install Libraries

Copy libraries from `1-Demo/Demo_Arduino/libraries/` to Arduino libraries directory:
- **Windows:** `C:\Users\<YourUser>\Documents\Arduino\libraries\`
- **macOS:** `~/Documents/Arduino/libraries/`
- **Linux:** `~/Arduino/libraries/`

### 2. Configure PSRAM (DEMO_MJPEG only)

For MJPEG video playback, PSRAM speed must be changed to 120MHz:

1. Replace the `esp32s3` folder provided in `1-Demo/Demo_Arduino/esp32s3/`
2. Destination: `C:\Users\<User>\AppData\Local\Arduino15\packages\esp32\tools\esp32-arduino-libs\idf-release_v5.1-bd2b9390ef\esp32s3\`

### 3. Prepare SD Card

**Important:** DEMO_PIC, DEMO_MJPEG, and DEMO_MP3 require SD card inserted.

Copy corresponding folders from `1-Demo/Demo_Arduino/TF file/`:
- `pic/` → Images for DEMO_PIC
- `mjpeg/` → Videos for DEMO_MJPEG
- `music/` → MP3 files for DEMO_MP3

### 4. Configure Arduino IDE

1. Select board: **ESP32S3 Dev Module**
2. Recommended configuration:
   - **PSRAM:** OPI PSRAM
   - **Flash Size:** 16MB
   - **Partition Scheme:** As needed (minimum 3MB APP)
   - **Upload Speed:** 921600

---

## 💻 Example Usage

### LVGL Example (Graphical Interface)

```cpp
// Open: 1-Demo/Demo_Arduino/DEMO_LVGL/DEMO_LVGL.ino

// Configure screen rotation
#define LVGL_PORT_ROTATION_DEGREE (90)  // 0, 90, 180, or 270

// Activate demos in setup()
lv_demo_widgets();    // Widgets demo
// lv_demo_benchmark(); // Performance test
// lv_demo_music();     // Player interface
```

### MJPEG Example (Video Player)

```cpp
// Open: 1-Demo/Demo_Arduino/DEMO_MJPEG/DEMO_MJPEG.ino
// Insert SD card with videos in mjpeg/ folder
// Ensure PSRAM at 120MHz
```

### MP3 Example (Audio Player)

```cpp
// Open: 1-Demo/Demo_Arduino/DEMO_MP3/DEMO_MP3.ino
// Insert SD card with MP3 files in music/ folder
```

### PIC Example (Image Viewer)

```cpp
// Open: 1-Demo/Demo_Arduino/DEMO_PIC/DEMO_PIC.ino
// Insert SD card with images in pic/ folder
```

---

## 🔌 Main Pinout

See detailed diagrams in: `5-IO pin distribution/`

**Critical pins** (see diagrams for complete pinout):
- Display: QSPI Interface
- Touch: I2C
- Audio: I2S
- SD Card: SPI

---

## 📖 Additional Resources

### Documentation

- [LVGL Documentation](https://docs.lvgl.io/)
- [ESP32-S3 Technical Reference](https://www.espressif.com/en/products/socs/esp32-s3)
- [Arduino-ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/)

### Important Files

- User manual: `6-User_Manual/Getting started JC3248W535.pdf`
- Specifications: `2-Specification/JC3248W535 Specifications-EN.pdf`
- Usage notes: `1-Demo/Demo_Arduino/Must see for use.txt`

---

## ⚠️ Important Notes

1. **ESP32 Arduino Version:** Must be exactly v3.0.2
2. **SD card mandatory:** For multimedia demos (MJPEG, MP3, PIC)
3. **Black screen:** If screen stays black, verify SD card is inserted and contains necessary files
4. **PSRAM 120MHz:** Required only for MJPEG video playback
5. **Screen rotation:** Configure according to desired orientation in each demo

---

## 🛠️ Troubleshooting

### Black Screen

- Verify SD card is inserted (for multimedia demos)
- Check files are in correct folders
- Verify power connection

### Compilation Error

- Confirm ESP32 Arduino version v3.0.2
- Verify libraries are installed correctly
- Copy `lv_conf.h` to LVGL libraries directory

### MJPEG Video Not Playing

- Confirm PSRAM configured at 120MHz
- Verify MJPEG video format
- Check files are in `mjpeg/` folder

---

## 📝 License

See included documentation and individual library licenses.

---

**Manufacturer:** Compatible with ESP32-S3 development boards  
**Model:** JC3248W535EN  
**Last updated:** 2025

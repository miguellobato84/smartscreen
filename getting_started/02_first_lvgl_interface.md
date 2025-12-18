# Tutorial 2: Creating Your First LVGL Interface

**Estimated time:** 30–45 minutes  
**Level:** Beginner → Intermediate  

## Objectives

- Build a custom LVGL screen on the ESP32-S3 panel
- Add basic widgets (label, button, slider)
- Handle touch/button events to update the UI
- Understand simple layout and styling


## Requirements

- Completed [Tutorial 1](01_setup_and_first_steps.md): device, LVGL demo, OTA verified
- Arduino IDE installed, ESP32 board package configured
- Board connected via USB-C


## Steps

### 1) Open the Tutorial 2 sketch

Use the dedicated sketch for this tutorial:

- 1-Demo/Demo_Arduino/DEMO_LVGL_TUTORIAL2/DEMO_LVGL_TUTORIAL2.ino

This demo already initializes the display, LVGL, and touch.

### 2) Explore the custom screen

In the file above, we create:

- A title label
- A button that updates a status label upon click
- A slider with a label that reflects its value

The function is invoked during setup after LVGL and the display are initialized.

### 3) Build and upload

1. Open Arduino IDE and select the correct ESP32-S3 board and port.
2. Open the sketch folder for DEMO_LVGL.
3. Click "Upload" to compile and flash.
4. The screen should show the custom UI with interactive button and slider.

### 4) Verify interactions

- Tap the button: the status label updates the click count.
- Drag the slider: the brightness label updates to the current percentage.

## Troubleshooting

- If the demo widgets still show, ensure the call to `lv_demo_widgets()` is commented and `tutorial2_create_ui()` is invoked.
- If the screen is rotated incorrectly, adjust `LVGL_PORT_ROTATION_DEGREE` in DEMO_LVGL.ino.
- If touch doesn’t respond, verify your board selection and that the demo’s `esp_bsp` files match your hardware variant.

## What’s next

- Add more widgets: switches, dropdowns, keyboards
- Apply styles and themes to match your design
- Split UI code into separate files for maintainability

## Reference

- LVGL documentation: [docs.lvgl.io](https://docs.lvgl.io)
- DEMO source location: 1-Demo/Demo_Arduino/DEMO_LVGL

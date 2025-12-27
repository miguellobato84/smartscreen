# Configuración de ESPhome JC3248W535EN

Este archivo proporciona configuraciones adicionales y customización para tu proyecto ESPHome.

## 📝 Archivos de Ejemplo

### jc3248w535-demo.yaml
Configuración de demostración con ejemplos básicos:

```yaml
esphome:
  name: jc3248w535-demo
  friendly_name: JC3248W535EN Demo

# ... incluye pantalla, touch y LVGL ...
```

### jc3248w535-lvgl-minimal.yaml
Configuración minimalista solo con LVGL, sin componentes avanzados.

## 🎨 Agregar Componentes Personalizados

### Sensor de Temperatura (DHT11)

```yaml
sensor:
  - platform: dht
    pin: GPIO12
    temperature:
      name: "Temperatura"
    humidity:
      name: "Humedad"
    update_interval: 60s
```

### Control de LED

```yaml
output:
  - platform: ledc
    pin: GPIO6
    id: led_pin

light:
  - platform: monochromatic
    output: led_pin
    name: "LED Control"
```

### Botón

```yaml
binary_sensor:
  - platform: gpio
    pin: GPIO5
    name: "Botón"
    on_press:
      - lambda: |-
          ESP_LOGI("button", "Button pressed!");
```

## 🔐 Seguridad

### Cambiar contraseña OTA

```bash
esphome config jc3248w535-native-qspi_dbi.yaml
```

Esto te generará automáticamente nuevas credenciales encriptadas.

### Cambiar nombre del device

En el YAML:
```yaml
esphome:
  name: mi_device_unico
  friendly_name: Mi Dispositivo
```

## 📡 Integración con Home Assistant

Después de compilar y conectar, Home Assistant debería:

1. **Detectar automáticamente** el device
2. **Agregar la integración** cuando presiones "Permitir"
3. **Crear entidades** para:
   - Control de retroiluminación
   - Estado del WiFi
   - Acciones de pantalla táctil

### YAML para Home Assistant

```yaml
esphome:
  name: jc3248w535
  
api:
  encryption:
    key: !secret esphome_encryption_key

ota:
  password: !secret esphome_ota_password
```

En `secrets.yaml` de HA:
```yaml
esphome_encryption_key: "TU_CLAVE_GENERADA"
esphome_ota_password: "TU_PASSWORD_GENERADA"
```

## 🎛️ LVGL Personalizado

### Agregar botones y etiquetas

```yaml
lvgl:
  pages:
    - id: home_page
      widgets:
        - label:
            id: label_temp
            text: "Temperatura: 25°C"
            align: center
        - button:
            id: btn_power
            text: "Apagar"
            on_click:
              - logger.log: "Power button pressed"
```

### Temas de color

```yaml
lvgl:
  color_scheme: DARK
  theme: dark
```

## 📊 Logging y Debugging

### Habilitar logs detallados

```yaml
logger:
  level: VERY_VERBOSE
  baud_rate: 921600
  logs:
    component: DEBUG
    esphome.components.display: DEBUG
```

### Ver logs en tiempo real

```bash
esphome logs jc3248w535-native-qspi_dbi.yaml
```

## 🔄 Actualización OTA

Tras compilar y subir por USB una vez, puedes actualizar wirelessly:

```bash
# Con WiFi conectada
esphome upload jc3248w535-native-qspi_dbi.yaml --device 192.168.1.100
```

O a través de Home Assistant Dashboard directamente.

## 📦 Respaldo y Restauración

### Respaldo de configuración

```bash
esphome config jc3248w535-native-qspi_dbi.yaml > backup.json
```

### Restaurar de respaldo

```bash
esphome restore-flasher jc3248w535-native-qspi_dbi.yaml /path/to/backup.json
```

## 🚀 Comandos Útiles

```bash
# Ver estado del device
esphome info jc3248w535-native-qspi_dbi.yaml

# Limpiar caché de compilación
esphome clean jc3248w535-native-qspi_dbi.yaml

# Compilar sin subir
esphome compile jc3248w535-native-qspi_dbi.yaml

# Monitorear logs
esphome logs jc3248w535-native-qspi_dbi.yaml

# Generar nuevo dashboard
esphome dashboard .
```

## 📚 Recursos Adicionales

- [ESPhome Official Components](https://esphome.io/components/)
- [LVGL Widget Reference](https://docs.lvgl.io/master/widgets/)
- [ESP32-S3 Pinout](https://www.espressif.com/en/products/socs/esp32-s3)

---

Para más información, revisa los archivos principales en esta carpeta.

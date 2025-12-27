# ESPHome Configuration for JC3248W535EN

Esta carpeta contiene la configuración de ESPHome para el dispositivo **JC3248W535EN** (ESP32-S3 con pantalla táctil 3.5" 320x480).

## 📋 Requisitos

- **ESPHome**: v2024.10.0 o superior (versión DEV recomendada para soporte nativo QSPI)
- **Python 3**: v3.7 o superior
- **USB**: Cable USB-C para conexión y programación

## 🚀 Instalación Rápida

### 1. Instalar ESPHome

```bash
# Con pip (recomendado)
pip install esphome

# Con conda
conda install -c conda-forge esphome

# Con Docker (alternativa)
docker run -it -v $(pwd):/config --device=/dev/ttyUSB0 ghcr.io/esphome/esphome:latest
```

### 2. Configurar credenciales WiFi

```bash
# Copiar archivo de ejemplo
cp secrets.yaml.example secrets.yaml

# Editar con tus credenciales WiFi
# Edita el archivo secrets.yaml y reemplaza:
# - YOUR_SSID: Tu red WiFi
# - YOUR_PASSWORD: Tu contraseña WiFi
```

### 3. Compilar y descargar el firmware

```bash
# Validar configuración
esphome config jc3248w535-native-qspi_dbi.yaml

# Compilar
esphome compile jc3248w535-native-qspi_dbi.yaml

# Descargar (requiere conexión USB)
esphome run jc3248w535-native-qspi_dbi.yaml
```

## 📁 Archivos de Configuración

### `jc3248w535-native-qspi_dbi.yaml` ⭐ **RECOMENDADO**

Configuración completa usando el soporte nativo QSPI de ESPHome.

**Características:**
- ✅ Pantalla: Controlador AXS15231 (320x480) - soporte nativo QSPI/DBI
- ✅ Pantalla táctil: Soporte I2C nativo
- ✅ Retroiluminación: Control PWM (GPIO1)
- ✅ WiFi y OTA integrados
- ✅ LVGL para interfaz gráfica completa
- ✅ Requiere ESPHome v2024.10.0+

**Pinout:**
- Display QSPI: CLK=47, DATA=[21,48,40,39], CS=45
- Touchscreen I2C: SDA=4, SCL=8
- Backlight PWM: GPIO1
- Serial: 921600 baud

### `jc3248w535-lvgl-minimal.yaml`

Configuración minimalista solo con LVGL (sin soporte avanzado).

### `jc3248w535-demo.yaml`

Configuración de demostración con ejemplos.

## 🔧 Configuración Personalizada

### Cambiar orientación de pantalla

En `jc3248w535-native-qspi_dbi.yaml`:

```yaml
display:
  - platform: qspi_dbi
    rotation: 0    # 0 = portrait, 90 = landscape
```

### Modificar velocidad de conectividad

```yaml
ota:
  - platform: esphome
    password: "tu_contraseña"
```

### Ajustar brillo de pantalla

```yaml
light:
  - platform: monochromatic
    output: backlight
    name: "backlight Light"
    restore_mode: ALWAYS_ON  # O usar RESTORE_DEFAULT_ON
```

## 🎨 Personalizar con LVGL

Después de compilar exitosamente, puedes:

1. **Crear interfaces gráficas** usando LVGL directamente en la config:

```yaml
lvgl:
  pages:
    - id: main_page
      widgets:
        - label:
            text: "¡Hola JC3248W535EN!"
            align: center
```

2. **Integrar con Home Assistant** automáticamente tras conectar WiFi
3. **Usar automaciones** basadas en eventos de pantalla táctil

## 🐛 Solución de Problemas

### "Error: Cannot find axs15231 support"
- ESPHome DEV requerido. Actualiza: `pip install --upgrade esphome`

### Pantalla negra tras compilación
- Verificar conexión USB
- Cambiar puerto: `esphome run ... --device /dev/ttyUSB0`
- Verificar voltaje (3.3V) en pines de pantalla

### WiFi no conecta
- Revisar SSID/password en `secrets.yaml`
- Comprobar rango de WiFi (5GHz no soportado en algunos configuraciones)
- Ver logs: `esphome logs jc3248w535-native-qspi_dbi.yaml`

### Touch no funciona
- Verificar pines I2C (SDA=4, SCL=8)
- Ejecutar calibración touch si es necesario

## 📚 Referencias

- **ESPHome Documentation**: https://esphome.io/
- **LVGL Docs**: https://docs.lvgl.io/
- **Repositorio Original**: https://github.com/clowrey/ESPhome-JC3248W535EN
- **Datasheet ESP32-S3**: https://www.espressif.com/en/products/socs/esp32-s3

## 📝 Notas Importantes

1. **Encriptación**: El archivo YAML contiene claves de ejemplo. Genera las tuyas con `esphome config`.
2. **Seguridad**: Nunca commits `secrets.yaml` al repositorio.
3. **Versión ESPHome**: Se requiere versión reciente para soporte QSPI/AXS15231 nativo.
4. **OTA**: Una vez compilado y subido, puedes actualizar wirelessly sin USB.

## 🤝 Contribuciones

Para reportar problemas o mejoras, consulta:
- Este proyecto: [JC3248W535EN](../../)
- Repositorio original: [clowrey/ESPhome-JC3248W535EN](https://github.com/clowrey/ESPhome-JC3248W535EN)

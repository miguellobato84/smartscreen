# ESPHome JC3248W535EN - Guía de Inicio Rápido

## ✅ Estado de la Instalación

**ESPHome Versión:** 2025.11.1  
**Python:** 3.13.0  
**Instalado:** ✅ Completamente

## 🚀 Pasos Siguientes

### 1. Crear archivo de secretos

```bash
cd 9-esphome/
cp secrets.yaml.example secrets.yaml
# Edita secrets.yaml con tus credenciales WiFi
```

### 2. Validar configuración

```bash
esphome config jc3248w535-native-qspi_dbi.yaml
```

### 3. Compilar firmware

```bash
esphome compile jc3248w535-native-qspi_dbi.yaml
```

### 4. Descargar a la placa (requiere USB)

```bash
esphome run jc3248w535-native-qspi_dbi.yaml
```

O si ya está compilado:

```bash
esphome upload jc3248w535-native-qspi_dbi.yaml
```

## 📂 Estructura de Carpetas

```
9-esphome/
├── README.md                              # Esta documentación
├── QUICK_START.md                         # Guía de inicio rápido
├── secrets.yaml.example                   # Ejemplo de credenciales
├── jc3248w535-native-qspi_dbi.yaml       # ⭐ CONFIG PRINCIPAL (recomendada)
├── jc3248w535-lvgl-minimal.yaml          # Config minimalista
└── jc3248w535-demo.yaml                  # Config de demostración
```

## 🔌 Conexión USB

Para que el comando `esphome run` funcione:

1. Conecta la placa ESP32-S3 vía USB-C
2. macOS debería detectarla automáticamente como `/dev/tty.usbserial-*`
3. Si hay problemas, instala [CH340 drivers](https://sparks.gogo.co.nz/ch340.html)

## 💡 Tips Importantes

- **Primer compile:** Tardará 5-10 minutos la primera vez (descarga componentes)
- **Siguiente compiles:** Mucho más rápido (caché de compilación)
- **OTA updates:** Tras la primera carga USB, puedes actualizar wirelessly
- **WiFi 2.4GHz:** Solo soportado (no 5GHz)

## 🆘 Problemas Comunes

**"Command not found: esphome"**
```bash
# Asegúrate de estar en el entorno correcto
pip install esphome
```

**"Serial port not found"**
- Verifica que el cable USB es de datos (no solo carga)
- Intenta un puerto USB diferente
- En macOS: `ls /dev/tty.*` para ver puertos disponibles

**Conexión WiFi falla**
- Verifica SSID/password en `secrets.yaml`
- El AP debe estar en 2.4GHz
- La placa está cerca del router

## 📖 Para Más Información

Consulta la [documentación completa](README.md) en esta carpeta o visita:
- https://esphome.io/
- https://docs.lvgl.io/

---

¡Listo para empezar con ESPHome! 🎉

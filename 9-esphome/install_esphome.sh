#!/bin/bash

# Script de instalación de ESPHome para JC3248W535EN
# Uso: bash install_esphome.sh

set -e

echo "================================"
echo "ESPHome JC3248W535EN - Setup"
echo "================================"
echo ""

# Verificar Python
echo "✓ Verificando Python..."
python_version=$(python3 --version 2>&1 | awk '{print $2}')
echo "  Python $python_version encontrado"
echo ""

# Verificar/Instalar pip
echo "✓ Verificando pip..."
if ! command -v pip &> /dev/null; then
    echo "  Instalando pip..."
    python3 -m ensurepip --default-pip
fi
echo ""

# Instalar ESPHome
echo "✓ Instalando ESPHome..."
pip install --upgrade esphome
echo "  ✅ ESPHome instalado"
echo ""

# Verificar instalación
esphome_version=$(esphome version 2>&1 | head -1 | awk '{print $2}')
echo "✓ ESPHome $esphome_version instalado correctamente"
echo ""

# Crear secrets.yaml si no existe
if [ ! -f "secrets.yaml" ]; then
    echo "⚠️  secrets.yaml no encontrado"
    echo "Creando desde plantilla..."
    cp secrets.yaml.example secrets.yaml
    echo "✓ secrets.yaml creado (EDITA CON TUS CREDENCIALES)"
else
    echo "✓ secrets.yaml ya existe"
fi
echo ""

echo "================================"
echo "✅ Instalación completada!"
echo "================================"
echo ""
echo "Próximos pasos:"
echo "1. Edita secrets.yaml con tus credenciales WiFi"
echo "2. Ejecuta: esphome config jc3248w535-native-qspi_dbi.yaml"
echo "3. Ejecuta: esphome compile jc3248w535-native-qspi_dbi.yaml"
echo "4. Conecta USB y ejecuta: esphome run jc3248w535-native-qspi_dbi.yaml"
echo ""
echo "Para más información, consulta README.md"

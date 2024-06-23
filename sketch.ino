#include <WiFi.h>
#include <HTTPClient.h>
#include "LCDManager.h"
#include "Devices.h"

// Configuraciones de WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Instancia de dispositivos
Devices devices;  // Configura los pines apropiados para DHT, Ultrasonic y Pulse

// Instancia del LCD
LCDManager lcdManager(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.print("Conectando a WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ¡Conectado!");

  devices.begin(23, 5, 18, 35, 4); // Inicializar dispositivos con los pines apropiados
  lcdManager.init(); // Iniciar el LCD
}

void loop() {
  devices.updateSensors();  // Actualiza todos los sensores al comienzo del loop
  // Leer y mostrar los datos del sensor
  float temperature = devices.readTemperature();
  float humidity = devices.readHumidity();
  float pulseVoltage = devices.readPulseVoltage();
  long distance = devices.readDistance();

  Serial.print("Temperatura: "); Serial.print(temperature); Serial.print(" °C, ");
  Serial.print("Humedad: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Voltaje del pulso: "); Serial.println(pulseVoltage);
  Serial.print("Distancia: "); Serial.println(distance);

  // Envío de datos al servidor
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://tu-servidor/temp");
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"temperature\":\"" + String(temperature, 2) +
                      "\", \"humidity\":\"" + String(humidity, 1) +
                      "\", \"distance\":\"" + String(distance) +
                      "\", \"pulse\":\"" + String(pulseVoltage) + "\"}";
    int httpCode = http.POST(jsonData);
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error en la petición: "); Serial.println(httpCode);
    }
    http.end();
  }

  // Actualizar el LCD con los últimos datos
  lcdManager.displayMessage("Temp: " + String(temperature, 2) + " C", 
                            "Hum: " + String(humidity, 1) + "%");
  delay(2000); // Refresco de pantalla cada 2 segundos
  lcdManager.displayMessage("Pulse: " + String(pulseVoltage) + "V", 
                            "Dist: " + String(distance) + "cm");
  delay(2000);
}

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTSensor.h"
#include "UltrasonicSensor.h"
#include "PulseSensor.h"
#include "LCDManager.h"

// Configuraciones de WiFi
const char *ssid = "Wokwi-GUEST";
const char *password = "";

// Instancias de los sensores
DHTSensor dhtSensor(15);  // Asegúrate de que el pin es correcto
UltrasonicSensor ultrasonicSensor(5, 18);
PulseSensor pulseSensor(35, 4);

// Instancia del LCD
LCDManager lcdManager(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ¡Conectado!");

  lcdManager.init(); // Iniciar el LCD
}

void loop() {
  // Leer y mostrar los datos del sensor de pulso simulado
  float voltage = pulseSensor.readVoltage();
  pulseSensor.updateLed();
  Serial.print("Voltaje del pulso: ");
  Serial.println(voltage);

  // Leer y mostrar los datos del DHT22
  TempAndHumidity values = dhtSensor.readValues();
  if (!isnan(values.temperature)) {
    Serial.print("Temperatura: ");
    Serial.print(values.temperature);
    Serial.print(" °C, Humedad: ");
    Serial.print(values.humidity);
    Serial.println(" %");
  }

  // Leer y mostrar la distancia
  long distance = ultrasonicSensor.measureDistance();
  Serial.print("Distancia: ");
  Serial.println(distance);

  // Envío de datos al servidor
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://tu-servidor.com/api/data");
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"temperature\":" + String(values.temperature, 2) +
                      ",\"humidity\":" + String(values.humidity, 1) +
                      ",\"pulse\":" + String(voltage) +
                      ",\"distance\":" + String(distance) + "}";
    int httpCode = http.POST(jsonData);
    http.end();
  }

  // Actualizar el LCD con los últimos datos
  lcdManager.displayMessage("Temp: " + String(values.temperature, 2) + " C", 
                            "Hum: " + String(values.humidity, 1) + "%");

  delay(2000);

  lcdManager.displayMessage("Pulse: " + String(voltage) + "V", 
                            "Dist: " + String(distance) + "cm");

  delay(2000);  // Delay entre lecturas
}

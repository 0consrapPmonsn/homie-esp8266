#include <Homie.h>

const int TEMPERATURE_INTERVAL = 300;

unsigned long last_temperature_sent = 0;

HomieNode temperatureNode("temperature", "temperature");

void setupHandler() {
  // Do what you want to prepare your sensor
}

void loopHandler() {
  if (millis() - last_temperature_sent >= TEMPERATURE_INTERVAL * 1000UL || last_temperature_sent == 0) {
    float temperature = 22; // Fake temperature here, for the example
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    if (Homie.setNodeProperty(temperatureNode, "temperature", String(temperature), true)) {
      last_temperature_sent = millis();
    } else {
      Serial.println("Sending failed");
    }
  }
}

void setup() {
  Homie.setFirmware("awesome-temperature", "1.0.0");
  Homie.registerNode(temperatureNode);
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  Homie.setup();
}

void loop() {
  Homie.loop();
}

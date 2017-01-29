#include <LightManager.h>
#include <SoftwareSerial.h>

const int colors[4] = {3, 5, 6, 9};

#define DEBUG true

LightManager LightManager(colors, DEBUG);

void setup() {
    Serial.begin(115200);
    Serial.println("---Lya---");
}

void loop() {
    LightManager.Manager();
}
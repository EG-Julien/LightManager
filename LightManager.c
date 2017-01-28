#include "SoftwareSerial.h"

#define DEBUG true

const int colors[4] = {3, 5, 6, 9};
int colors_s[4] = {0, 0, 0, 0};

int choosed = 0;
int choosed_s = 0;

SoftwareSerial rpiSerial(10, 11);

void setup() {
    for (int i = 0; i < 4; ++i) {
        pinMode(colors[i], OUTPUT);
    }

    rpiSerial.begin(115200);
    Serial.begin(115200);

    rpiSerial.println("---Lya---");
    Serial.println("---Lya---");
}

void loop() {

    lightManager();
    delay(50);
}

void lightManager() {
    if (DEBUG == true) {
        if (Serial.available()) {
            char inByte = Serial.read();

            if (inByte == 'c') { //Chooser
                Serial.println("Choose led's id you want to control : [1, 2, 3, 4]");
                delay(10);
                if (Serial.available()) {
                    int chooser = Serial.read();
                    int ids[4] = {49, 50, 51, 52};
                    Serial.println(chooser);
                    if (in_array(chooser, ids, 4) == false) {
                        Serial.println("This ID does not exist !");
                    } else {
                        choosed = chooser - '1';
                        Serial.print("You choosed the LED with id :: ");
                        Serial.println(choosed + 1);
                    }
                } else {
                    Serial.println("Can't read data !");
                }
            }

            if (inByte == '+') {
                if (colors_s[choosed] < 255) {
                    colors_s[choosed]++;
                    Serial.print("LED :: ");
                    Serial.print(colors[choosed]);
                    Serial.print(" | LEVEL :: ");
                    Serial.println(colors_s[choosed]);
                }
            } else if (inByte == '-') {
                if (colors_s[choosed] > 0) {
                    colors_s[choosed]--;
                    Serial.print("LED :: ");
                    Serial.print(colors[choosed]);
                    Serial.print(" | LEVEL :: ");
                    Serial.println(colors_s[choosed]);
                }
            } else if (inByte == '0') {
                colors_s[choosed] = 0;
                Serial.print("LED :: ");
                Serial.print(colors[choosed]);
                Serial.print(" | LEVEL :: ");
                Serial.println(colors_s[choosed]);

            } else if (inByte == '1') {
                colors_s[choosed] = 255;
                Serial.print("LED :: ");
                Serial.print(colors[choosed]);
                Serial.print(" | LEVEL :: ");
                Serial.println(colors_s[choosed]);
            }
        }
        analogWrite(colors[choosed], colors_s[choosed]);
    } else {
        if (rpiSerial.available()) {
            char inByte = rpiSerial.read();

            if (inByte == 'c') { //Chooser
                rpiSerial.println("Choose led's id you want to control : [1, 2, 3, 4]");
                char chooser = rpiSerial.read();
                int ids[4] = {1, 2, 3, 4};
                if (in_array(chooser, ids, 4) == false) {
                    rpiSerial.println("This ID does not exist !");
                } else {
                    choosed = chooser - 1;
                    rpiSerial.print("You choosed the LED with id :: ");
                    rpiSerial.println(choosed + 1);
                }
            }

            if (inByte == '+') {
                if (colors_s[choosed] < 255) {
                    colors_s[choosed];
                    rpiSerial.print("LEVEL :: ");
                    rpiSerial.println(colors_s[choosed]);
                }
            } else if (inByte == '-') {
                if (colors_s[choosed] > 0) {
                    colors_s[choosed]--;
                    rpiSerial.print("LED :: ");
                    rpiSerial.print(colors[choosed]);
                    rpiSerial.print(" | LEVEL :: ");
                    rpiSerial.println(colors_s[choosed]);
                }
            }
        }
        analogWrite(colors[choosed], colors_s[choosed]);
    }
}

int in_array(int val, int *arr, int size) {
    Serial.println(size);
    for (int i = 0; i < size; ++i) {
        if (arr[i] == val) {
            return true;
        }
    }
    return false;
}
#include "LightManager.h"
#include <Arduino.h>


const int colors[4] = {3, 5, 6, 9};
int colors_s[4] = {0, 0, 0, 0};

int choosed = 0;

void LightManager(int DEBUG) {
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
            } else if (inByte == '%') {
                int percentage = cmd.toInt();
                percentage = map(percentage, 0, 100, 0, 255);
                cmd = "";
                if (percentage > 255 || percentage < 0) {
                    Serial.println("This value can't be assign !");
                } else if (percentage > colors_s[choosed]) {
                    int to = colors_s[choosed];
                    for (int i = 0; i < percentage - to; ++i) {
                        colors_s[choosed]++;
                        Serial.print("LED :: ");
                        Serial.print(colors[choosed]);
                        Serial.print(" | LEVEL :: ");
                        Serial.println(colors_s[choosed]);
                        analogWrite(colors[choosed], colors_s[choosed]);
                        delay(10);
                    }
                } else {
                    int to = colors_s[choosed];
                    for (int i = 0; i < to - percentage; ++i) {
                        colors_s[choosed]--;
                        Serial.print("LED :: ");
                        Serial.print(colors[choosed]);
                        Serial.print(" | LEVEL :: ");
                        Serial.println(colors_s[choosed]);
                        analogWrite(colors[choosed], colors_s[choosed]);
                        delay(10);
                    }
                }

            } else {
                cmd = cmd + inByte;
            }
        }
        analogWrite(colors[choosed], colors_s[choosed]);
    } else {
        if (rpiSerial.available()) {
            char inByte = rpiSerial.read();

            if (inByte == 'c') { //Chooser
                delay(10);
                if (rpiSerial.available()) {
                    int chooser = Serial.read();
                    int ids[4] = {49, 50, 51, 52};

                    if (in_array(chooser, ids, 4) == false) {
                        //Nothing to do in this mod
                    } else {
                        choosed = chooser - '1';
                    }
                }
            } else if (inByte == '%') {
                int percentage = cmd.toInt();
                percentage = map(percentage, 0, 100, 0, 255);
                cmd = "";
                if (percentage > 255 || percentage < 0) {
                } else if (percentage > colors_s[choosed]) {
                    int to = colors_s[choosed];
                    for (int i = 0; i < percentage - to; ++i) {
                        colors_s[choosed]++;
                        analogWrite(colors[choosed], colors_s[choosed]);
                        delay(10);
                    }
                } else {
                    int to = colors_s[choosed];
                    for (int i = 0; i < to - percentage; ++i) {
                        colors_s[choosed]--;
                        analogWrite(colors[choosed], colors_s[choosed]);
                        delay(10);
                    }
                }

            } else {
                cmd = cmd + inByte;
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
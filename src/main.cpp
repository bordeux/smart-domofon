#include <Arduino.h>
#include <Ticker.h>

#define STATE_SLEEP 0
#define STATE_DIALING 1
#define STATE_CALLING 2


Ticker timer;

const int inputPin = D1;

int signalCount = 0;
int lastCalledNumber = 0;

int STATE = STATE_SLEEP;

void stopCalling() {
    lastCalledNumber = signalCount;
    STATE = STATE_CALLING;
}

void IRAM_ATTR handleInterrupt() {
    if (STATE == STATE_DIALING) {
        signalCount++;
        return;
    }

    if (STATE == STATE_SLEEP) {
        STATE = STATE_DIALING;
        signalCount = 0;
        timer.once_ms(58, stopCalling);
    }
};

void setup() {
    pinMode(inputPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(inputPin), handleInterrupt, RISING);

    Serial.begin(9600);
    Serial.print("Starting the program");
}


void loop() {
    if (STATE == STATE_CALLING) {
        Serial.println();
        Serial.print("==== Wybrano numer  ");
        Serial.print(lastCalledNumber);
        Serial.println("=====");

        lastCalledNumber = 0;

        Serial.println("Czekanie 4s");
        delay(4000);
        Serial.println("Odblokowanie lock'a");
        STATE = STATE_SLEEP;
    };
};
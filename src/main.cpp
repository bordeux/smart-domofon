#include <Arduino.h>
#include <Ticker.h>

#define STATE_SLEEP 0
#define STATE_DIALING 1
#define STATE_POST_DIALING 2
#define STATE_DETECTING_SIGNAL 3
#define STATE_CALLING 4
#define STATE_GATE_WRONG_PIN 5
#define STATE_GATE_UNLOCK 5

#define DIALING_TIME_MS 58
#define DIGITAL_INPUT_PIN D1

#define SIGNALS_CALLING 10
#define SIGNALS_WRONG_GATE_PING 5
#define SIGNALS_CORRECT_GATE_PING 23

Ticker timer;
int signalCount = 0;
int lastCalledNumber = 0;
int STATE = STATE_SLEEP;

bool isSignal(int signalsCount, int expected, int tolerance = 1) {
    return signalsCount > expected - tolerance
           && signalsCount < expected + tolerance;
}

void detectSignalType() {
    if (STATE != STATE_DETECTING_SIGNAL) {
        return;
    }

    if (isSignal(signalCount, SIGNALS_CALLING)) {
        STATE = STATE_CALLING;
        return;
    }

    if (isSignal(signalCount, SIGNALS_WRONG_GATE_PING)) {
        STATE = STATE_GATE_WRONG_PIN;
        return;
    }

    if (isSignal(signalCount, SIGNALS_CORRECT_GATE_PING)) {
        STATE = STATE_GATE_UNLOCK;
        return;
    }
}

void stopDialing() {
    if (STATE != STATE_DIALING) {
        return;
    }

    lastCalledNumber = signalCount;
    STATE = STATE_POST_DIALING;
}

void IRAM_ATTR handleInterrupt() {
    if (STATE == STATE_DIALING) {
        signalCount++;
        return;
    }

    if (STATE == STATE_DETECTING_SIGNAL) {
        signalCount++;
        return;
    }

    if (STATE == STATE_SLEEP) {
        STATE = STATE_DIALING;
        signalCount = 0;
        timer.once_ms(DIALING_TIME_MS, stopDialing);
        return;
    }

    // after dialing, wait for next pull up
    // to start counting signal type
    if (STATE == STATE_POST_DIALING) {
        STATE = STATE_DETECTING_SIGNAL;
        signalCount = 0;
        timer.once_ms(10, detectSignalType);
    }
};

void setup() {
    Serial.begin(9600);
    pinMode(DIGITAL_INPUT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DIGITAL_INPUT_PIN), handleInterrupt, RISING);

    Serial.println();
    Serial.println("Starting the program");
}


void loop() {
    if (STATE == STATE_CALLING) {
        Serial.println();
        Serial.print("==== Wybrano numer  ");
        Serial.print(lastCalledNumber);
        Serial.println("=====");

        lastCalledNumber = 0;

        Serial.println("Czekanie 4s");
        delay(7000);
        Serial.println("Odblokowanie lock'a");
        STATE = STATE_SLEEP;
    };
};
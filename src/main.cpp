/**
 * @author Club Arduino 2018-2019 Collège Jean-Georges REBER
 */
#include <Arduino.h>
#include <Servo.h>

#define bp1 11
#define bp2 A1
#define bp3 A2
#define bp4 A3
#define bp5 A4
#define bpverif A5


#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define ledverif 12

#define a 7
#define b 8
#define c 9
#define d 10

#define SERVO 13

int valeurbp1;
int valeurbp2;
int valeurbp3;
int valeurbp4;
int valeurbp5;
int valeurbpverif;

bool bp1_Avant = 0;
bool bp2_Avant = 0;
bool bp3_Avant = 0;
bool bp4_Avant = 0;
bool bp5_Avant = 0;
bool bpverif_Avant = 0;

bool bp1_b = false;
bool bp2_b = false;
bool bp3_b = false;
bool bp4_b = false;
bool bp5_b = false;
bool bpverif_b = false;


bool etatLed1 = false;
bool etatLed2 = false;
bool etatLed3 = false;
bool etatLed4 = false;
bool etatLed5 = false;
bool etatLedverif = false;

int chiffrebcd = 0;

Servo monServo;

void setup() {
    monServo.attach(SERVO);
    monServo.write(0);
    Serial.begin(9600);


    pinMode(bp1, INPUT);
    pinMode(bp2, INPUT);
    pinMode(bp3, INPUT);
    pinMode(bp4, INPUT);
    pinMode(bp5, INPUT);
    pinMode(bpverif, INPUT);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(ledverif, OUTPUT);

    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);


    randomSeed(analogRead(A0));
    valeurbp1 = random(0, 2);
    valeurbp2 = random(0, 2);
    valeurbp3 = random(0, 2);
    valeurbp4 = random(0, 2);
    valeurbp5 = random(0, 2);


    Serial.println(valeurbp1);
    Serial.println(valeurbp2);
    Serial.println(valeurbp3);
    Serial.println(valeurbp4);
    Serial.println(valeurbp5);
}

void zero() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
}

void un() {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
}

void deux() {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
}

void trois() {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
}

void quatre() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
}

void cinq() {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
}


void bcd() {
    if (chiffrebcd == 0) {
        zero();
    }
    if (chiffrebcd == 1) {
        un();
    }
    if (chiffrebcd == 2) {
        deux();
    }
    if (chiffrebcd == 3) {
        trois();
    }
    if (chiffrebcd == 4) {
        quatre();
    }
}


void valeurdesboutons() {

    if (!bp1_b && (bp1_Avant == 1)) {
        bp1_Avant = 0;
        etatLed1 = !etatLed1;
    }
    if (!bp1_b && (bp1_Avant == 0)) {
        bp1_Avant = 1;
        bp1_b = !bp1_b;
    }

    if (bp2_b && (bp2_Avant == 1)) {
        bp2_Avant = 0;
        etatLed2 = !etatLed2;
    }
    if (!bp2_b && (bp2_Avant == 0)) {
        bp2_Avant = 1;
        bp2_b = !bp2_b;
    }

    if (bp3_b && (bp3_Avant == 1)) {
        bp3_Avant = 0;
        etatLed3 = !etatLed3;
    }
    if (!bp3_b && (bp3_Avant == 0)) {
        bp3_Avant = 1;
        bp3_b = !bp3_b;
    }

    if (bp4_b && (bp4_Avant == 1)) {
        bp4_Avant = 0;
        etatLed4 = !etatLed4;
    }
    if (!bp4_b && (bp4_Avant == 0)) {
        bp4_Avant = 1;
        bp4_b = !bp4_b;
    }

    if (bp5_b && (bp5_Avant == 1)) {
        bp5_Avant = 0;
        etatLed5 = !etatLed5;
    }
    if (!bp5_b && (bp5_Avant == 0)) {
        bp5_Avant = 1;
        bp5_b = !bp5_b;
    }
}


void chiffrebcdvoid() {
    if (etatLed1 == valeurbp1) {
        chiffrebcd++;
    }
    if (etatLed2 == valeurbp2) {
        chiffrebcd++;
    }
    if (etatLed3 == valeurbp3) {
        chiffrebcd++;
    }
    if (etatLed4 == valeurbp4) {
        chiffrebcd++;
    }
    if (etatLed5 == valeurbp5) {
        chiffrebcd++;
    }
}

void poweroff_leds() {
    etatLed1 = LOW;
    etatLed2 = LOW;
    etatLed3 = LOW;
    etatLed4 = LOW;
    etatLed5 = LOW;
}

void loop() {

    bp1_b = digitalRead(bp1);
    bp2_b = digitalRead(bp2);
    bp3_b = digitalRead(bp3);
    bp4_b = digitalRead(bp4);
    bp5_b = digitalRead(bp5);
    valeurdesboutons();


    digitalWrite(led1, etatLed1);
    digitalWrite(led2, etatLed2);
    digitalWrite(led3, etatLed3);
    digitalWrite(led4, etatLed4);
    digitalWrite(led5, etatLed5);
    delay(10);


    if ((etatLed1 == valeurbp1)
        && (etatLed2 == valeurbp2)
        && (etatLed3 == valeurbp3)
        && (etatLed4 == valeurbp4)
        && (etatLed5 == valeurbp5)
        && (digitalRead(bpverif) == LOW)) {

        cinq();


        for (int i = 0; i < 10; i++) {
            digitalWrite(ledverif, HIGH);
            delay(100);
            digitalWrite(ledverif, LOW);
            delay(100);
        }

        poweroff_leds();
        delay(1000);
        monServo.write(170);
        delay(1000);
        chiffrebcd = 0;
    } else if ((digitalRead(bpverif) == LOW)) {
        chiffrebcdvoid();
        bcd();
        delay(1000);
        poweroff_leds();
        chiffrebcd = 0;
    }
    bcd();
}

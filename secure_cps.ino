#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensors
#define TRIG1 9
#define ECHO1 10
#define TRIG2 11
#define ECHO2 12

// Outputs
#define LED 6
#define BUZZER 7

// Counters
int intrusionCount = 0;
int cyberAttackCount = 0;
bool highAlert = false;

// Secret key
int SECRET_KEY = 123;

// Toggle this to simulate tampering
bool simulateTamper = false;  // 👉 change to true to test attack

// Secure validation
int getSecureDistance(long distance) {
  int key;

  if (simulateTamper) {
    key = 999;  // fake key (attack)
  } else {
    key = SECRET_KEY;  // normal
  }

  if (key != SECRET_KEY) {
    return -1;  // invalid data
  }

  return distance;
}

// Distance function
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Secure CPS System");
  delay(2000);
  lcd.clear();
}

void loop() {
  long raw1 = getDistance(TRIG1, ECHO1);
  long raw2 = getDistance(TRIG2, ECHO2);

  int d1 = getSecureDistance(raw1);
  int d2 = getSecureDistance(raw2);

  lcd.clear();

  // 🔐 DATA TAMPERING
  if (d1 == -1 || d2 == -1) {
    cyberAttackCount++;

    lcd.setCursor(0, 0);
    lcd.print("DATA TAMPER!");
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.print(cyberAttackCount);

    Serial.println("⚠️ DATA TAMPERING DETECTED!");

    digitalWrite(LED, HIGH);
    tone(BUZZER, 1500);
    delay(300);
    digitalWrite(LED, LOW);
    noTone(BUZZER);
    delay(300);
  }

  // ⚠️ SPOOFING ATTACK
  else if ((d1 < 100 && d2 > 300) || (d2 < 100 && d1 > 300)) {
    cyberAttackCount++;

    lcd.setCursor(0, 0);
    lcd.print("SPOOF ATTACK!");
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.print(cyberAttackCount);

    Serial.println("⚠️ SPOOFING DETECTED!");

    digitalWrite(LED, HIGH);
    tone(BUZZER, 1200);
    delay(200);
    digitalWrite(LED, LOW);
    noTone(BUZZER);
    delay(200);
  }

  // 🚨 INTRUSION
  else if (d1 < 100 || d2 < 100) {
    intrusionCount++;

    lcd.setCursor(0, 0);
    lcd.print("INTRUSION!");
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.print(intrusionCount);

    Serial.println("🚨 INTRUSION DETECTED!");

    digitalWrite(LED, HIGH);
    tone(BUZZER, 800);
  }

  // 🔥 SAFE / HIGH ALERT
  else {
    if (intrusionCount >= 3 || cyberAttackCount >= 2) {
      highAlert = true;
    }

    if (highAlert) {
      lcd.setCursor(0, 0);
      lcd.print("HIGH ALERT!");
      lcd.setCursor(0, 1);
      lcd.print("System Locked");

      digitalWrite(LED, HIGH);
      tone(BUZZER, 1500);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("SAFE ZONE");
      lcd.setCursor(0, 1);
      lcd.print("Monitoring");

      digitalWrite(LED, LOW);
      noTone(BUZZER);
    }
  }

  delay(500);
}

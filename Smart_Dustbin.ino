#define BLYNK_TEMPLATE_ID "TMPL3Kvp1Nsr4"
#define BLYNK_TEMPLATE_NAME "Dustbin"
#define BLYNK_AUTH_TOKEN 
"BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi
char ssid[] = "F****A";
char pass[] = "8*******5";

// Pins
#define IR_PIN 15
#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 19

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo
Servo servo;

// GPS
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// Variables
long duration;
int distance;
int fillPercent;

bool autoMode = true;
bool manualLid = false;
String lidStatus = "Closed";

bool alertSent = false;

// -------- BLYNK INPUTS --------
BLYNK_WRITE(V5) {
  manualLid = param.asInt();
}

BLYNK_WRITE(V6) {
  autoMode = param.asInt();
}

void setup() {
  Serial.begin(115200);

  // ---------------- I2C INIT (MOST IMPORTANT FIX) ----------------
  Wire.begin(14, 13);   // SDA = 14, SCL = 13
  delay(100);

  // ---------------- LCD INIT EARLY ----------------
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Dustbin");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1500);
  lcd.clear();

  // ---------------- PIN SETUP ----------------
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // ---------------- SERVO ----------------
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);

  // Default position
  servo.write(90);

  // ---------------- GPS ----------------
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  // ---------------- BLYNK ----------------
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // ---------------- ULTRASONIC (20 CM RANGE) ----------------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  int maxHeight = 20;

  if (distance > maxHeight) distance = maxHeight;
  if (distance < 0) distance = 0;

  int garbageLevel = maxHeight - distance;
  fillPercent = (garbageLevel * 100) / maxHeight;

  Blynk.virtualWrite(V1, fillPercent);

  // ---------------- ALERT ----------------
  if (fillPercent > 80 && !alertSent) {
    Blynk.logEvent("bin_full", "Dustbin is almost full!");
    alertSent = true;
  }

  if (fillPercent < 50) {
    alertSent = false;
  }

  // ---------------- LID CONTROL ----------------
  if (autoMode) {
    if (digitalRead(IR_PIN) == LOW) {
      servo.write(180);
      lidStatus = "Open";
    } else {
      servo.write(90);
      lidStatus = "Closed";
    }
  } else {
    if (manualLid == 1) {
      servo.write(180);
      lidStatus = "Open";
    } else {
      servo.write(90);
      lidStatus = "Closed";
    }
  }

  Blynk.virtualWrite(V2, lidStatus);

  // ---------------- GPS ----------------
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    float lat = gps.location.lat();
    float lng = gps.location.lng();

    Blynk.virtualWrite(V3, lat);
    Blynk.virtualWrite(V4, lng);
  }

  // ---------------- LCD UPDATE (FIXED REFRESH) ----------------
  lcd.setCursor(0, 0);
  lcd.print("Fill:");
  lcd.print(fillPercent);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print(lidStatus);
  lcd.print("        ");

  // ---------------- SERIAL ----------------
  Serial.print("Fill %: ");
  Serial.print(fillPercent);
  Serial.print(" | Mode: ");
  Serial.print(autoMode ? "AUTO" : "MANUAL");
  Serial.print(" | Lid: ");
  Serial.println(lidStatus);

  Serial.println("----------------");

  delay(300);
}

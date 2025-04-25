#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID" // make a template on blynk console
#define BLYNK_TEMPLATE_NAME "YOUR_DEVICE_NAME" 
#define BLYNK_AUTH_TOKEN "AUTHENTICATION_TOKEN"

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

char ssid[] = "YOUR WIFI/HOTSPOT NAME";
char pass[] = "WIFI/HOTSPOT PASSWORD";

#define ENA D7
#define IN1 D1
#define IN2 D2
#define LED_PIN D4  // Built-in LED

int direction = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Blynk.run();
  blinkLED();
}

BLYNK_WRITE(V1) {
  direction = param.asInt();  // 1 = Forward, 0 = Reverse
  Serial.print("Direction: ");
  Serial.println(direction);

  if (direction == 1) {
    analogWrite(ENA, 1023);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Serial.println("Actuator: FORWARD");
  } else {
    analogWrite(ENA, 1023);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Serial.println("Actuator: REVERSE");
  }

  delay(1500);  // Run actuator for 1.5 sec only to secure it from excessive heat

  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("Power OFF");
}

// LED Blink Function
void blinkLED() {
  static unsigned long lastMillis = 0;
  static bool ledState = LOW;
  if (millis() - lastMillis >= 500) {
    lastMillis = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}
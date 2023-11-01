#include <Arduino.h>

// Measuring distance with the HC-SR04 Ultrasonic Sensor

const int trig_pin = 6; // Pin to send the ping from
const int echo_pin = 5; // Pin to read the ping from
const int led_pin = LED_BUILTIN;
const int measurement_interval = 60; // Datasheet recommends waiting at least 60ms between measurements
unsigned long previous_time = 0;
unsigned long previous_micros = 0;
bool led_state = false; // Initialise LED to off
int distance;


int calculate_distance(int trig_pin) {
  long duration; // This will store the measured duration of the pulse
  unsigned long current_time = millis();
  if (current_time - previous_time >= measurement_interval) {
    previous_time = current_time;
    if (led_state == false) {
      led_state = true;
    } else {
      led_state = false;
    }

    trigger_pulse();

    // Read the duration of the response pulse
    duration = pulseIn(echo_pin, HIGH);

    // Convert time into distance in cm
    distance = (duration / 58);

    // Print
    Serial.print("Distance: ");
    Serial.println(distance);
  }
}

void trigger_pulse() {
  digitalWrite(trig_pin, LOW);
  unsigned long current_micros = micros();
  if(current_micros - previous_micros >= 2) {
    digitalWrite(trig_pin, HIGH);
  }
  previous_micros = current_micros;
  if(current_micros - previous_micros >= 10) {
    digitalWrite(trig_pin, LOW);
  }
  previous_micros = current_micros;
}

void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  calculate_distance(trig_pin);
}

#include <Arduino.h>

#define PWM_IN_PIN          0
#define BLINK_PIN           1
#define WING_PIN            2

#define BLINK_START_VAL     4
#define WING_START_VAL      6

bool blink_state = false;
bool wing_state = false;

void setup() {
  pinMode(PWM_IN_PIN, INPUT);
  pinMode(BLINK_PIN, OUTPUT);
  pinMode(WING_PIN, OUTPUT);

  delay(10);
  
  digitalWrite(BLINK_PIN, blink_state);
  digitalWrite(WING_PIN, wing_state);
}

uint8_t GetPWM(byte pin) {
  unsigned long highTime = pulseIn(pin, HIGH, 50000UL);  // 50 millisecond timeout
  unsigned long lowTime = pulseIn(pin, LOW, 50000UL);  // 50 millisecond timeout

  if (highTime == 0 || lowTime == 0)
    return 0;

  return (100 * highTime) / (highTime + lowTime);  // highTime as percentage of total cycle time
}

void loop() {
  uint8_t pwm_value = GetPWM(PWM_IN_PIN);
  if (pwm_value < 10) {
    if ( (pwm_value > BLINK_START_VAL) &&  !blink_state) {
      blink_state = true;
      digitalWrite(BLINK_PIN, HIGH);
    }
    else if ( (pwm_value <= BLINK_START_VAL) &&  blink_state) {
      blink_state = false;
      digitalWrite(BLINK_PIN, LOW);
    }
    if ( (pwm_value > WING_START_VAL) &&  !wing_state) {
      wing_state = true;
      digitalWrite(WING_PIN, HIGH);
    }
    else if ( (pwm_value <= WING_START_VAL) &&  wing_state) {
      wing_state = false;
      digitalWrite(WING_PIN, LOW);
    }
  }
}
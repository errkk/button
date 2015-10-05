#include <RCSwitch.h>

RCSwitch rc = RCSwitch();

int channel = 1;

// Button
int buttonPin = 8;
int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  // Transmitter
  rc.enableTransmit(9);
  rc.setPulseLength(320);  
  
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);  
}

void sendTrigger() {
  Serial.println("Sending");  
  digitalWrite(13, HIGH);
  rc.switchOn(channel, 3);
  delay(200);
  digitalWrite(13, LOW);
  rc.switchOff(channel, 3);
}

void loop() {


  int reading = digitalRead(buttonPin);
  Serial.println(reading);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if(!reading) {

      sendTrigger();  
    }
  }

  lastButtonState = reading;  
}

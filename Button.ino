#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


const int buttonPin = 8;
const int red = 11;
const int green = 10;


int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  // pin 10
  mySwitch.enableTransmit(13);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);

  // set initial LED state
  digitalWrite(red, ledState);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }

      if(ledState == HIGH) {
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);  
        
        mySwitch.switchOff("11111", "00010");
      } else {
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);      
        
        mySwitch.switchOn("11111", "00010");
      }
    }
  }

  lastButtonState = reading;
}


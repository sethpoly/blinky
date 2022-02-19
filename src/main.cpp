#include <Arduino.h>

#define led1 0
#define led2 1
#define led3 2
#define led4 3
#define led5 4

bool state = true;
int leds [5];
int ledArrayLength = 5;

// Set all LEDs a specific state except for a certain one
void setAllExcept(bool state, int arrayLength, int ledToIgnore) {
  for(int i = 0; i < arrayLength; i++) {
    if(leds[i] == ledToIgnore) {
      digitalWrite(leds[i], !state);
      continue;
    }

    digitalWrite(leds[i], state);
  }
}

void snake(int arrayLength, int millisecondsBetween) {
  for(int i = 0; i < arrayLength; i++) {
    digitalWrite(leds[i], 1);
    delay(millisecondsBetween);
    digitalWrite(leds[i], 0);
  }

  for(int i = arrayLength - 1; i >= 0; i--) {
    digitalWrite(leds[i], 1);
    delay(millisecondsBetween);
    digitalWrite(leds[i], 0);
  }
}

void doubleSnake(int arrayLength, int millisecondsBetween) {
  for(int i = 0; i < arrayLength; i++) {
    int startPin = i;
    int endPin = arrayLength - i - 1;

    if(startPin == 0) {
      endPin = arrayLength - 1;
    }
    digitalWrite(leds[startPin], 1);
    digitalWrite(leds[endPin], 1);
    delay(millisecondsBetween);
    digitalWrite(leds[startPin], 0);
    digitalWrite(leds[endPin], 0);
  }
}

// Simulate a broken bulb on a neon sign or something
void brokenLight(int led, int millisecondsBetween) {
  setAllExcept(1, ledArrayLength, led);  

  int delayMilliseconds = 800;
  int ledState = true;
  bool hasRestarted = false;
  while(delayMilliseconds > 50) {
    digitalWrite(led, ledState);
    delay(delayMilliseconds);

    // Decrement delay
    int delayRange = delayMilliseconds * .5;
    delayMilliseconds -= rand() % delayRange;

    // Change led state
    ledState = !ledState;

    if(delayMilliseconds < 70 && !hasRestarted) {
      delayMilliseconds = 300;
      hasRestarted = true;
    }
  }
}

void setPattern(int arg1, int arg2, void ( *f )( int, int )) {
  for(int i = 0; i < 6; i++) {
    f(arg1, arg2);
  }
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  // add leds to array
  leds[0] = led1;
  leds[1] = led2;
  leds[2] = led3;
  leds[3] = led4;
  leds[4] = led5;
}

void loop() {
  // Cycle through patterns
  setPattern(ledArrayLength, 50, snake);
  setPattern(ledArrayLength, 80, doubleSnake);
  setPattern(leds[rand() % ledArrayLength], 0, brokenLight);
}
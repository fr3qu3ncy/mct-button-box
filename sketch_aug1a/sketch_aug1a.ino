#include "Keyboard.h"
#include "Mouse.h"

// Pin Assignments
const int buttonA = 2;
const int buttonB = 3;

// Key Assignments
const int keyA = 97; // 'a'
const int keyB = 98; // 'b'

int prevButtonStateA = HIGH;
int prevButtonStateB = HIGH;

void setup() {
  // pull up pins
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  Keyboard.begin();

}

void loop() {
prevButtonStateA = checkButtonOnce(buttonA, keyA, prevButtonStateA);
prevButtonStateB = checkLatchButton(buttonB, keyB, prevButtonStateB);
  
  // Add a small delay to avoid bouncing issues
  delay(10);
  
}

// Single key press per button press
int checkButtonOnce(int button, int key, int prevButtonState){
  // Check state of button
  int buttonState = digitalRead(button);

  //Button Logic - one key press per button press
  if (buttonState == LOW && prevButtonState == HIGH) {
    Keyboard.press(key);
    delay(50);
    Keyboard.release(key);
  }  
  prevButtonState = buttonState;
  return prevButtonState;
}

// Repeat key press while button is held down
int checkButtonRepeat(int button, int key, int prevButtonState){
  // Check state of button
  int buttonState = digitalRead(button);

  //Button Logic - repeate keypress
  if (buttonState == LOW && prevButtonState == HIGH) {
    Keyboard.press(key);
    delay(50);
  }
  else if (buttonState == HIGH && prevButtonState == LOW) {
    Keyboard.release(key);
    delay(50);
  }
  prevButtonState = buttonState;
  return prevButtonState;
}

// Single key press when latching sqitch changes state
int checkLatchButton(int button, int key, int prevButtonState){
  // Check state of button
  int buttonState = digitalRead(button);

  //Button Logic - one key press when button changes state
  if (buttonState == LOW && prevButtonState == HIGH) {
    Keyboard.press(key);
    delay(50);
    Keyboard.release(key);
  }
  else if (buttonState == HIGH && prevButtonState == LOW) {
    Keyboard.press(key);
    delay(50);
    Keyboard.release(key);
  }
  prevButtonState = buttonState;
  return prevButtonState;
}
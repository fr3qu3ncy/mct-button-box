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
prevButtonStateA = checkButton(buttonA, keyA, prevButtonStateA);
prevButtonStateB = checkButton(buttonB, keyB, prevButtonStateB);
  
  // Add a small delay to avoid bouncing issues
  delay(10);
  
}

int checkButton(int button, int key, int prevButtonState){
  // Check state of button
  int buttonState = digitalRead(button);

  //Button Logic
  if (buttonState == LOW && prevButtonState == HIGH) {
    Keyboard.press(key);
    delay(50);
  }
  if (buttonState == HIGH && prevButtonState == LOW) {
    Keyboard.release(key);
    delay(50);
  }
  prevButtonState = buttonState;
  return prevButtonState;
}

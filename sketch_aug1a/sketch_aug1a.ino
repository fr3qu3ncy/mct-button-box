#include "Keyboard.h"
#include "Mouse.h"

// Pin Assignments
// Keyboard pins
const int buttonA = 2;
const int buttonB = 3;
const int buttonC = 4;
const int buttonD = 5;
const int buttonE = 6;
const int buttonF = 7;
const int buttonG = 8;
const int buttonH = 9;
const int buttonI = 10; 
const int buttonJ = 11;
const int buttonEsc = 12;
// Mouse pins
const int buttonLeftClick = 18;
const int buttonMouseLeft = 19;
const int buttonMouseRight = 20;
const int buttonMouseUp = 21;
const int buttonMouseDown = 22;

// Key Assignments
const int keyA = 97; // 'a'
const int keyB = 98; // 'b'
const int keyC = 99; // 'c'
const int keyD = 100; // 'd'
const int keyE = 101; // 'e'
const int keyF = 102; // 'f'
const int keyG = 103; // 'g'
const int keyH = 104; // 'h'
const int KeyI = 105; // 'i'
const int keyJ = 106; // 'j'
const int keyEsc = 0xB1; // 'esc'
// const int keyLeftClick = 0x01; // Mouse left click
// const int keyMouseLeft = 0x02; // Mouse left movement
// const int keyMouseRight = 0x03; // Mouse right movement
// const int keyMouseUp = 0x04; // Mouse up movement
// const int keyMouseDown = 0x05; // Mouse down movement

// Mouse hold count
// This variable is used to count how many times the mouse buttons are held down
int buttonMouseHoldCount = 0;


int prevButtonStateA = HIGH;
int prevButtonStateB = HIGH;
int prevButtonStateC = HIGH;
int prevButtonStateD = HIGH;
int prevButtonStateE = HIGH;
int prevButtonStateF = HIGH;
int prevButtonStateG = HIGH;
int prevButtonStateH = HIGH;
int prevButtonStateI = HIGH;
int prevButtonStateJ = HIGH;
int prevButtonStateEsc = HIGH;
int prevButtonStateLeftClick = HIGH;
int prevButtonStateMouseMove = HIGH;

void setup() {
  // pull up pins
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(buttonD, INPUT_PULLUP);
  pinMode(buttonE, INPUT_PULLUP);
  pinMode(buttonF, INPUT_PULLUP);
  pinMode(buttonG, INPUT_PULLUP);
  pinMode(buttonH, INPUT_PULLUP);
  pinMode(buttonI, INPUT_PULLUP);
  pinMode(buttonJ, INPUT_PULLUP);
  pinMode(buttonEsc, INPUT_PULLUP);
  pinMode(buttonLeftClick, INPUT_PULLUP);
  pinMode(buttonMouseLeft, INPUT_PULLUP);
  pinMode(buttonMouseRight, INPUT_PULLUP);
  pinMode(buttonMouseUp, INPUT_PULLUP);
  pinMode(buttonMouseDown, INPUT_PULLUP);
  // Initialize Keyboard and Mouse  
  Keyboard.begin();
  Mouse.begin();

}

void loop() {
  prevButtonStateA = checkButtonOnce(buttonA, keyA, prevButtonStateA);
  prevButtonStateB = checkButtonOnce(buttonB, keyB, prevButtonStateB);
  prevButtonStateA = checkButtonOnce(buttonC, keyC, prevButtonStateC);
  prevButtonStateD = checkButtonOnce(buttonD, keyD, prevButtonStateD);
  prevButtonStateE = checkButtonOnce(buttonE, keyE, prevButtonStateE);
  prevButtonStateF = checkButtonOnce(buttonF, keyF, prevButtonStateF);
  prevButtonStateG = checkButtonOnce(buttonG, keyG, prevButtonStateG);
  prevButtonStateH = checkButtonOnce(buttonH, keyH, prevButtonStateH);
  prevButtonStateI = checkLatchButton(buttonI, KeyI, prevButtonStateI);
  prevButtonStateJ = checkLatchButton(buttonJ, keyJ, prevButtonStateJ);
  prevButtonStateEsc = checkButtonOnce(buttonEsc, keyEsc, prevButtonStateEsc);
  // Mouse buttons
  moveMouse(buttonMouseLeft, buttonMouseRight, buttonMouseUp, buttonMouseDown);
  prevButtonStateLeftClick = mouseClick(buttonLeftClick, prevButtonStateLeftClick);
  
  
  // Add a small delay to avoid bouncing issues
  //delay(10);
  
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

// Mouse left click
int mouseClick(int button, int prevButtonState) {
  // Check state of button
  int buttonState = digitalRead(button);

  //Button Logic - mouse click
  if (buttonState == LOW && prevButtonState == HIGH) {
    Mouse.click(MOUSE_LEFT);
    delay(50); // Delay to prevent too fast clicking
  }
  prevButtonState = buttonState;
  return prevButtonState;
} 

// Move mouse all directions based on button states
void moveMouse(int buttonMouseLeft, int buttonMouseRight, int buttonMouseUp, int buttonMouseDown) {
  // Check state of buttons
  int leftState = digitalRead(buttonMouseLeft);
  int rightState = digitalRead(buttonMouseRight);
  int upState = digitalRead(buttonMouseUp);
  int downState = digitalRead(buttonMouseDown);

  int buttonState = leftState * rightState * upState * downState; // Sum of button states to determine if any button is pressed

  if (prevButtonStateMouseMove == HIGH) {
    buttonMouseHoldCount = 0; // Reset hold count when mouse movement starts
  }
  else if (prevButtonStateMouseMove == LOW) {
    buttonMouseHoldCount = buttonMouseHoldCount + 1; // Increment hold count
    Mouse.move((leftState*-10)+(rightState*10), (downState*-10)+(upState*10), 0); // Move mouse based on button states
    if (buttonMouseHoldCount > 5)
    {
      delay(8); // Shorter delay to for faster movement
    }
    else {
      delay(50); // Loger delay for smoother movement
    }
  }
  
  prevButtonStateMouseMove = buttonState; // Update previous button state for mouse movement
  
}


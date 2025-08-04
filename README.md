# mct-button-box

This project implements a custom button box for controlling keyboard and mouse actions using an Arduino Micro. Each button press sends a specific keyboard key or mouse movement/click to the connected computer.

## Features

- 10 keyboard buttons (A-J, Esc)
- Mouse movement in 4 directions (Left, Right, Up, Down)
- Mouse left click
- Latching support for I and J buttons

## Pin Assignments

| Function         | Arduino Pin |
|------------------|------------|
| Button A         | 2          |
| Button B         | 3          |
| Button C         | 4          |
| Button D         | 5          |
| Button E         | 6          |
| Button F         | 7          |
| Button G         | 8          |
| Button H         | 9          |
| Button I         | 10         |
| Button J         | 11         |
| Button Esc       | 12         |
| Mouse Left Click | 18         |
| Mouse Left       | 19         |
| Mouse Right      | 20         |
| Mouse Up         | 21         |
| Mouse Down       | 22         |

## Wiring Instructions

1. **Buttons**: Connect one terminal of each button to the corresponding Arduino pin (see table above). Connect the other terminal to GND.
2. **Pull-up Resistors**: The code uses `INPUT_PULLUP`, so no external pull-up resistors are needed.
3. **Mouse/Keyboard Libraries**: Make sure your Arduino IDE has the `Keyboard` and `Mouse` libraries available (these are included by default for Arduino Micro).
4. **Upload**: Flash the code in [`sketch_aug1a/sketch_aug1a.ino`](sketch_aug1a/sketch_aug1a.ino) to your Arduino Micro.

## Usage

- Pressing a button sends the corresponding key or mouse action.
- Mouse movement buttons move the cursor while held.
- Mouse left click button sends a single click per press.
- I and J buttons act as latching switches (send key on both press and release).

## Notes

- All buttons should be momentary push buttons except I and J, which can be latching switches.
- The board must be connected to a computer via USB for HID functionality.

For more details, see the source code in [`sketch_aug1a/sketch_aug1a.ino`](sketch_aug1a/sketch_aug1a.ino).